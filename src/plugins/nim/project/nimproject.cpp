/****************************************************************************
**
** Copyright (C) Filippo Cucchetto <filippocucchetto@gmail.com>
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "nimproject.h"
#include "nimbuildconfiguration.h"
#include "nimprojectnode.h"
#include "nimprojectmanager.h"

#include "../nimconstants.h"

#include <coreplugin/progressmanager/progressmanager.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/target.h>
#include <texteditor/textdocument.h>

#include <utils/algorithm.h>
#include <utils/qtcassert.h>
#include <utils/runextensions.h>

#include <QFileInfo>
#include <QQueue>

using namespace ProjectExplorer;
using namespace Utils;

namespace Nim {

const int MIN_TIME_BETWEEN_PROJECT_SCANS = 4500;

NimProject::NimProject(NimProjectManager *projectManager, const QString &fileName)
{
    setId(Constants::C_NIMPROJECT_ID);
    setProjectManager(projectManager);
    setDocument(new TextEditor::TextDocument);
    document()->setFilePath(FileName::fromString(fileName));
    QFileInfo fi = QFileInfo(fileName);
    QDir dir = fi.dir();
    setRootProjectNode(new NimProjectNode(*this, FileName::fromString(dir.absolutePath())));
    rootProjectNode()->setDisplayName(dir.dirName());

    m_projectScanTimer.setSingleShot(true);
    connect(&m_projectScanTimer, &QTimer::timeout, this, &NimProject::collectProjectFiles);

    connect(&m_futureWatcher, &QFutureWatcher<QList<FileNode *>>::finished, this, &NimProject::updateProject);

    collectProjectFiles();
}

QString NimProject::displayName() const
{
    return rootProjectNode()->displayName();
}

QStringList NimProject::files(FilesMode) const
{
    return m_files;
}

bool NimProject::needsConfiguration() const
{
    return targets().empty();
}

void NimProject::scheduleProjectScan()
{
    auto elapsedTime = m_lastProjectScan.elapsed();
    if (elapsedTime < MIN_TIME_BETWEEN_PROJECT_SCANS) {
        if (!m_projectScanTimer.isActive()) {
            m_projectScanTimer.setInterval(MIN_TIME_BETWEEN_PROJECT_SCANS - elapsedTime);
            m_projectScanTimer.start();
        }
    } else {
        collectProjectFiles();
    }
}

void NimProject::collectProjectFiles()
{
    m_lastProjectScan.start();
    QTC_ASSERT(!m_futureWatcher.future().isRunning(), return);
    FileName prjDir = projectDirectory();
    QFuture<QList<ProjectExplorer::FileNode *>> future = Utils::runAsync([prjDir] {
        return FileNode::scanForFiles(prjDir, [](const FileName &fn) { return new FileNode(fn, FileType::Source, false); });
    });
    m_futureWatcher.setFuture(future);
    Core::ProgressManager::addTask(future, tr("Scanning for Nim files"), "Nim.Project.Scan");
}

void NimProject::updateProject()
{
    QStringList oldFiles = m_files;
    m_files.clear();

    QList<FileNode *> fileNodes = Utils::filtered(m_futureWatcher.future().result(),
                                                  [](const FileNode *fn) {
        const QString fileName = fn->filePath().fileName();
        const bool keep = !fileName.endsWith(".nimproject", HostOsInfo::fileNameCaseSensitivity())
                && !fileName.contains(".nimproject.user", HostOsInfo::fileNameCaseSensitivity());
        if (!keep)
            delete fn;
        return keep;
    });

    m_files = Utils::transform(fileNodes, [](const FileNode *fn) { return fn->filePath().toString(); });
    Utils::sort(m_files, [](const QString &a, const QString &b) { return a < b; });

    if (oldFiles == m_files)
        return;

    rootProjectNode()->buildTree(fileNodes);

    emit fileListChanged();

    emit parsingFinished();
}

bool NimProject::supportsKit(Kit *k, QString *) const
{
    return k->isValid();
}

FileNameList NimProject::nimFiles() const
{
    FileNameList result;

    QQueue<FolderNode *> folders;
    folders.enqueue(rootProjectNode());

    while (!folders.isEmpty()) {
        FolderNode *folder = folders.takeFirst();
        for (FileNode *file : folder->fileNodes()) {
            if (file->displayName().endsWith(QLatin1String(".nim")))
                result.append(file->filePath());
        }
        folders.append(folder->folderNodes());
    }

    return result;
}

}

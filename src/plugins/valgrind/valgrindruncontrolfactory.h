/****************************************************************************
**
** Copyright (C) 2016 Kläralvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
** Contact: https://www.qt.io/licensing/
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

#ifndef VALGRINDRUNCONTROLFACTORY_H
#define VALGRINDRUNCONTROLFACTORY_H

#include <projectexplorer/runconfiguration.h>

namespace Valgrind {
namespace Internal {

class ValgrindRunControlFactory : public ProjectExplorer::IRunControlFactory
{
    Q_OBJECT
public:
    typedef ProjectExplorer::RunConfiguration RunConfiguration;

    explicit ValgrindRunControlFactory(QObject *parent = 0);

    // IRunControlFactory implementation
    bool canRun(RunConfiguration *runConfiguration, Core::Id mode) const override;

    ProjectExplorer::RunControl *create(RunConfiguration *runConfiguration, Core::Id mode,
                                        QString *errorMessage) override;
    ProjectExplorer::IRunConfigurationAspect *createRunConfigurationAspect(ProjectExplorer::RunConfiguration *rc) override;
};

} // namespace Internal
} // namespace Valgrind

#endif // VALGRINDRUNCONTROLFACTORY_H

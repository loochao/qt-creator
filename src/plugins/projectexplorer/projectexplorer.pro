TEMPLATE = lib
TARGET = ProjectExplorer
QT += xml \
    script \
    network
include(../../qtcreatorplugin.pri)
include(projectexplorer_dependencies.pri)
include(../../shared/scriptwrapper/scriptwrapper.pri)
include(../../libs/utils/utils.pri)
include(customwizard/customwizard.pri)
INCLUDEPATH += $$PWD/../../libs/utils
HEADERS += projectexplorer.h \
    projectexplorer_export.h \
    projectwindow.h \
    buildmanager.h \
    buildsteplist.h \
    compileoutputwindow.h \
    deployconfiguration.h \
    deployconfigurationmodel.h \
    namedwidget.h \
    target.h \
    targetsettingspanel.h \
    task.h \
    itaskhandler.h \
    copytaskhandler.h \
    showineditortaskhandler.h \
    showoutputtaskhandler.h \
    vcsannotatetaskhandler.h \
    taskwindow.h \
    outputwindow.h \
    persistentsettings.h \
    projectfilewizardextension.h \
    session.h \
    dependenciespanel.h \
    allprojectsfilter.h \
    ioutputparser.h \
    projectconfiguration.h \
    gnumakeparser.h \
    projectexplorerconstants.h \
    projectexplorersettings.h \
    corelistenercheckingforrunningbuild.h \
    project.h \
    pluginfilefactory.h \
    iprojectmanager.h \
    currentprojectfilter.h \
    scriptwrappers.h \
    allprojectsfind.h \
    buildstep.h \
    buildconfiguration.h \
    iprojectproperties.h \
    buildsettingspropertiespage.h \
    environmenteditmodel.h \
    processstep.h \
    editorconfiguration.h \
    editorsettingspropertiespage.h \
    runconfiguration.h \
    applicationlauncher.h \
    applicationrunconfiguration.h \
    runsettingspropertiespage.h \
    projecttreewidget.h \
    foldernavigationwidget.h \
    customexecutablerunconfiguration.h \
    buildprogress.h \
    projectnodes.h \
    sessiondialog.h \
    projectwizardpage.h \
    buildstepspage.h \
    removefiledialog.h \
    nodesvisitor.h \
    projectmodels.h \
    currentprojectfind.h \
    toolchain.h \
    userfileaccessor.h \
    cesdkhandler.h \
    gccparser.h \
    msvcparser.h \
    filewatcher.h \
    debugginghelper.h \
    projectexplorersettingspage.h \
    projectwelcomepage.h \
    projectwelcomepagewidget.h \
    baseprojectwizarddialog.h \
    miniprojecttargetselector.h \
    targetselector.h \
    targetsettingswidget.h \
    doubletabwidget.h \
    buildenvironmentwidget.h \
    buildconfigdialog.h \
    ldparser.h \
    linuxiccparser.h \
    outputformatter.h \
    runconfigurationmodel.h \
    buildconfigurationmodel.h \
    processparameters.h \
    abstractprocessstep.h \
    taskhub.h \
    localapplicationruncontrol.h \
    customexecutableconfigurationwidget.h \
    sessionnodeimpl.h
SOURCES += projectexplorer.cpp \
    projectwindow.cpp \
    buildmanager.cpp \
    buildsteplist.cpp \
    compileoutputwindow.cpp \
    deployconfiguration.cpp \
    deployconfigurationmodel.cpp \
    namedwidget.cpp \
    target.cpp \
    targetsettingspanel.cpp \
    ioutputparser.cpp \
    projectconfiguration.cpp \
    gnumakeparser.cpp \
    task.cpp \
    copytaskhandler.cpp \
    showineditortaskhandler.cpp \
    showoutputtaskhandler.cpp \
    vcsannotatetaskhandler.cpp \
    taskwindow.cpp \
    outputwindow.cpp \
    persistentsettings.cpp \
    projectfilewizardextension.cpp \
    session.cpp \
    dependenciespanel.cpp \
    allprojectsfilter.cpp \
    currentprojectfilter.cpp \
    scriptwrappers.cpp \
    allprojectsfind.cpp \
    project.cpp \
    pluginfilefactory.cpp \
    buildstep.cpp \
    buildconfiguration.cpp \
    buildsettingspropertiespage.cpp \
    environmenteditmodel.cpp \
    processstep.cpp \
    abstractprocessstep.cpp \
    editorconfiguration.cpp \
    editorsettingspropertiespage.cpp \
    runconfiguration.cpp \
    applicationrunconfiguration.cpp \
    runsettingspropertiespage.cpp \
    projecttreewidget.cpp \
    foldernavigationwidget.cpp \
    customexecutablerunconfiguration.cpp \
    buildprogress.cpp \
    projectnodes.cpp \
    sessiondialog.cpp \
    projectwizardpage.cpp \
    buildstepspage.cpp \
    removefiledialog.cpp \
    nodesvisitor.cpp \
    projectmodels.cpp \
    currentprojectfind.cpp \
    toolchain.cpp \
    cesdkhandler.cpp \
    userfileaccessor.cpp \
    gccparser.cpp \
    msvcparser.cpp \
    filewatcher.cpp \
    debugginghelper.cpp \
    projectexplorersettingspage.cpp \
    projectwelcomepage.cpp \
    projectwelcomepagewidget.cpp \
    corelistenercheckingforrunningbuild.cpp \
    baseprojectwizarddialog.cpp \
    miniprojecttargetselector.cpp \
    targetselector.cpp \
    targetsettingswidget.cpp \
    doubletabwidget.cpp \
    buildenvironmentwidget.cpp \
    buildconfigdialog.cpp \
    ldparser.cpp \
    linuxiccparser.cpp \
    outputformatter.cpp \
    runconfigurationmodel.cpp \
    buildconfigurationmodel.cpp \
    taskhub.cpp \
    processparameters.cpp \
    localapplicationruncontrol.cpp \
    customexecutableconfigurationwidget.cpp \
    sessionnodeimpl.cpp
FORMS += processstep.ui \
    editorsettingspropertiespage.ui \
    runsettingspropertiespage.ui \
    sessiondialog.ui \
    projectwizardpage.ui \
    removefiledialog.ui \
    projectexplorersettingspage.ui \
    projectwelcomepagewidget.ui \
    targetsettingswidget.ui \
    doubletabwidget.ui

equals(TEST, 1) {
    SOURCES += \
        outputparser_test.cpp
    HEADERS += \
        outputparser_test.h
}

win32 {
    SOURCES += applicationlauncher_win.cpp \
        winguiprocess.cpp
    HEADERS += winguiprocess.h
} else {
    SOURCES += applicationlauncher_x11.cpp
    macx:LIBS += -framework Carbon
}
RESOURCES += projectexplorer.qrc
DEFINES += PROJECTEXPLORER_LIBRARY

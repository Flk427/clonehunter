#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T15:30:18
#
# Copyright © 2015 Alexey Kudrin. All rights reserved.
# Licensed under the Apache License, Version 2.0
#
#-------------------------------------------------

QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG -= qt

TARGET = clonehunter
TEMPLATE = app

VERSION = 0.1.4

CONFIG += console

CONFIG(release, release|debug) {
    win32-msvc* {
#        MSVC_VER = $$(VisualStudioVersion)
#        equals(MSVC_VER, 14.0) {
#            message("msvc 2015")
#        }
#        equals(MSVC_VER, 10.0) {
#            message("msvc 2010")
#        }
#        message($$MSVC_VER)

        contains(QMAKE_COMPILER_DEFINES, _MSC_VER=1800) {
        # MSVS2013
        }

        contains(QMAKE_COMPILER_DEFINES, _MSC_VER=1600) {
            # MSVS2010
            message(Compiler: MSVC)
            DESTDIR = $${PWD}/bin/windows
        }

    }

#	win32-mingw {
#	}

    message(Place release binaries to $$DESTDIR)
}

TRANSLATIONS = i18n/clonehunter_ru.ts

SOURCES += main.cpp \
	src/getFiles.cpp \
	src/calcMd5.cpp \
	src/programParams.cpp \
	src/consoleMode/consoleMode.cpp \
	src/quickSearch.cpp \
	src/guiMode/MainWindow.cpp \
    src/guiMode/ui/FilesDecisionListView/FilesDecisionListView.cpp \
    src/guiMode/ui/AutoToolTipDelegate.cpp \
    src/guiMode/ui/FilesDecisionListView/FilesDecisionModel.cpp \
    src/guiMode/ui/FilesDecisionListWidget/FilesDecisionListWidget.cpp \
    src/guiMode/ui/DirectoryListSelectorWidget/DirectoryListSelectorWidget.cpp \
    src/guiMode/ui/PreviewWidget/PreviewWidget.cpp \
    src/guiMode/ui/ScanControlWidget/ScanControlWidget.cpp

HEADERS += \
	src/getFiles.h \
	src/types.h \
	src/calcMd5.h \
	src/programParams.h \
	src/consoleMode/consoleMode.h \
	src/quickSearch.h \
	src/guiMode/MainWindow.h \
    src/guiMode/ui/FilesDecisionListView/FilesDecisionListView.h \
    src/guiMode/ui/AutoToolTipDelegate.h \
    src/guiMode/ui/FilesDecisionListView/FilesDecisionModel.h \
    src/guiMode/ui/FilesDecisionListView/FilesDecisionFileInfo.h \
    src/guiMode/ui/FilesDecisionListWidget/FilesDecisionListWidget.h \
    src/guiMode/ui/DirectoryListSelectorWidget/DirectoryListSelectorWidget.h \
    src/guiMode/ui/PreviewWidget/PreviewWidget.h \
    src/guiMode/ui/ScanControlWidget/ScanControlWidget.h

FORMS += \
	src/guiMode/MainWindow.ui \
    src/guiMode/ui/FilesDecisionListWidget/FilesDecisionListWidget.ui \
    src/guiMode/ui/DirectoryListSelectorWidget/DirectoryListSelectorWidget.ui \
    src/guiMode/ui/PreviewWidget/PreviewWidget.ui \
    src/guiMode/ui/ScanControlWidget/ScanControlWidget.ui

RESOURCES += \
	res/clonehunter.qrc

OTHER_FILES += \
	i18n/clonehunter_ru.ts \
	i18n/clonehunter_ru.qm

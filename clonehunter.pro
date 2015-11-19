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

TRANSLATIONS = i18n/clonehunter_ru.ts

SOURCES += main.cpp \
	src/getFiles.cpp \
	src/crc16.cpp \
	src/calcMd5.cpp \
	src/programParams.cpp \
	src/consoleMode/consoleMode.cpp \
	src/quickSearch.cpp \
	src/guiMode/MainWindow.cpp

HEADERS += \
	src/getFiles.h \
	src/types.h \
	src/crc16.h \
	src/calcMd5.h \
	src/programParams.h \
	src/consoleMode/consoleMode.h \
	src/quickSearch.h \
	src/guiMode/MainWindow.h

FORMS += \
	src/guiMode/MainWindow.ui

RESOURCES += \
	res/clonehunter.qrc

OTHER_FILES += \
	i18n/clonehunter_ru.ts \
	i18n/clonehunter_ru.qm

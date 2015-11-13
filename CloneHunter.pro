#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T15:30:18
#
# Copyright © 2015 Alexey Kudrin. All rights reserved.
# Licensed under the Apache License, Version 2.0
#
#-------------------------------------------------

#QT       += core
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG -= qt

TARGET = CloneHunter
TEMPLATE = app

VERSION = 0.1.0

CONFIG += console

SOURCES += main.cpp \
	src/getFiles.cpp \
	src/crc16.cpp \
	src/calcMd5.cpp \
	src/programParams.cpp \
	src/consoleMode/consoleMode.cpp

HEADERS += \
	src/getFiles.h \
	src/types.h \
	src/crc16.h \
	src/calcMd5.h \
	src/programParams.h \
	src/consoleMode/consoleMode.h
# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

QT -= gui

TEMPLATE = lib

TARGET = QLibbsarch

HEADERS = \
   $$PWD/dds.h \
   $$PWD/libbsarch.h \
   QLibbsarch.h

SOURCES = \
   QLibbsarch.cpp

#DEFINES = 


unix|win32: LIBS += -L$$PWD/./ -llibbsarch

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

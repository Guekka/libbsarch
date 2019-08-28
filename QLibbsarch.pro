QT -= gui

TEMPLATE = lib

CONFIG += c++17

TARGET = QLibbsarch

HEADERS = \
   BSArchiveAuto.h \
   dds.h \
   libbsarch.h \
   BSArchive.h \
   BSArchiveEntries.h \
   QLibbsarch.h

SOURCES = \
   BSArchive.cpp \
   BSArchiveAuto.cpp \
   BSArchiveEntries.cpp \

#DEFINES = 

LIBS += -L$$PWD/./ -llibbsarch

QT -= gui

TEMPLATE = lib

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
   QLibbsarch.cpp

#DEFINES = 

IBS += -L$$PWD/./ -llibbsarch

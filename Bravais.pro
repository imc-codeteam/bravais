#-------------------------------------------------
#
# Project created by QtCreator 2018-03-18T15:17:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bravais
TEMPLATE = app

gcc {
  QMAKE_CXXFLAGS += -fopenmp
  QMAKE_LFLAGS += -fopenmp
  QMAKE_CXXFLAGS_RELEASE *= -O3
}

msvc {
  QMAKE_CXXFLAGS += -openmp
  QMAKE_CXXFLAGS_RELEASE *= -O2
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp\
           src/mainwindow.cpp \
    src/poscartab.cpp \
    src/inputtab.cpp \
    src/elementselector.cpp \
    src/crystal_database.cpp \
    src/surface_creator.cpp

HEADERS  += src/mainwindow.h \
    src/poscartab.h \
    src/inputtab.h \
    src/elementselector.h \
    src/crystal_database.h \
    src/surface_creator.h \
    src/config.h

win32 {
    INCLUDEPATH += ../../Libraries/boost-1.64.0-win-x64/include
    INCLUDEPATH += ../../Libraries/glm-0.9.8.4-win-x64
}

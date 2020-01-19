#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T17:26:49
#
#-------------------------------------------------

QT       += script
QT       -= gui

TARGET = ASN1_Qt_Script_lib
TEMPLATE = lib

DEFINES += ASN1_QT_SCRIPT_LIBRARY
DEFINES += DLLCOMPIL

CONFIG += console c++14

INCLUDEPATH += $$PWD/../ASN1_lib

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_Qt_Script_lib_d
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/debug/ -lASN1_lib_64d
}
CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_Qt_Script_lib
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/release/ -lASN1_lib_64
}

SOURCES += \
     Script.cpp \
     ASN1_Script_Node.cpp \
    Nodes/ASN1_Script_Basic_Nodes.cpp \
    Nodes/ASN1_Script_Choice.cpp \
    Nodes/ASN1_Script_Sequence.cpp \
    Nodes/ASN1_Script_SequenceOf.cpp \
    Nodes/ASN1_Script_Set.cpp \
    EngineInit.cpp

HEADERS +=\
    Script.h \
    ASN1_Script_Node.h \
    Nodes/ASN1_Script_Basic_Nodes.h \
    Nodes/ASN1_Script_Choice.h \
    Nodes/ASN1_Script_Sequence.h \
    Nodes/ASN1_Script_SequenceOf.h \
    Nodes/ASN1_Script_Set.h \
    EngineInit.h

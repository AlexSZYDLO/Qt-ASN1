TEMPLATE = lib
CONFIG += console c++14
QT += script
QT -= gui

INCLUDEPATH += $$PWD/../ASN1_lib

DEFINES += MODULE_API_EXPORTS

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_Qt_Script_libd
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../build-ASN1_lib/debug/ -lASN1d
}
CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_Qt_Script_lib
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../build-ASN1_lib/release/ -lASN1
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

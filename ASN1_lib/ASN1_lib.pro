TEMPLATE = lib
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += MODULE_API_EXPORTS

#TARGET = ASN1_lib

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_lib_64d
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
}

CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_lib_64
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
}

SOURCES += \
   ASN1_Value.cpp \
   ASN1_Object.cpp \
   ByteArray.cpp \
   Utils.cpp \
   C_Interface.cpp \
   Values/ASN1_ValueBitString.cpp \
   Values/ASN1_ValueBoolean.cpp \
   Values/ASN1_ValueUTCTime.cpp \
   Values/ASN1_ValueObjectID.cpp \
   Values/ASN1_ValueInteger.cpp \
   Values/ASN1_ValueIA5String.cpp \
   Values/ASN1_ValueSequence.cpp \
   Values/ASN1_ValueNull.cpp \
   Values/ASN1_ValueChoice.cpp \
   Values/ASN1_ValueUTF8String.cpp \
   Values/ASN1_ValueEnumerated.cpp \
   Values/ASN1_ValueOctetString.cpp \
   Values/ASN1_ValueReal.cpp \
   Values/ASN1_ValueSequenceOf.cpp \
   Values/ASN1_ValueSet.cpp \
   \
   Objects/ASN1_Object_Nodes.cpp \
   Objects/ASN1_Choice.cpp \
   Objects/ASN1_Sequence.cpp \
   Objects/ASN1_Set.cpp \
   Objects/ASN1_SequenceOf.cpp

HEADERS += \
   ASN1_includes.h \
   ASN1_Value.h \
   ASN1_Object.h \
   Exceptions.h \
   ByteArray.h \
   Utils.h \
   C_Interface.h \
   \
   Values/ASN1_Value_Nodes.h \
   Values/ASN1_ValueChoice.h \
   Values/ASN1_ValueSequence.h \
   Values/ASN1_ValueSequenceOf.h \
   Values/ASN1_ValueSet.h \
   \
   Objects/ASN1_Object_Nodes.h \
   Objects/ASN1_Choice.h \
   Objects/ASN1_Sequence.h \
   Objects/ASN1_SequenceOf.h \
   Objects/ASN1_Set.h

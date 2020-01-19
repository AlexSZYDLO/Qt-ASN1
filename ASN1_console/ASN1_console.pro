TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
#ICON = icon.png

TARGET = ASN1_console

QMAKE_LFLAGS += -Wl,-rpath='${ORIGIN}'

INCLUDEPATH += $$PWD/../ASN1_lib
INCLUDEPATH += $$PWD/../ASN1_parser

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../build-ASN1_lib/debug/ -lASN1d
   LIBS += -L$$OUT_PWD/../build-ASN1_parser/debug/ -lASN1_parserd
}
CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../build-ASN1_lib/release/ -lASN1
   LIBS += -L$$OUT_PWD/../build-ASN1_parser/release/ -lASN1_parser
}


SOURCES += main.cpp

HEADERS += \
    DLL_Interface.h

conf_files.files = Config/* ../Grammar/*.asn

# COPY ASN1_LIB.DLL ASN1_PARSER.DLL
CONFIG(debug, debug|release) {
  dlls.files = $$OUT_PWD/../../ASN1_lib/qtcreator/debug/ASN1_lib_64d.dll \
               $$OUT_PWD/../../ASN1_parser/qtcreator/debug/ASN1_parser_64d.dll
  dlls.path  = $$OUT_PWD/debug
  conf_files.path = $$OUT_PWD/debug/config

}
CONFIG(release, debug|release) {
  dlls.files = $$OUT_PWD/../../ASN1_lib/qtcreator/release/ASN1_lib_64.dll
               $$OUT_PWD/../../ASN1_parser/qtcreator/release/ASN1_parser_64.dll
  dlls.path  = $$OUT_PWD/release
  conf_files.path = $$OUT_PWD/release/config
}

#INSTALLS += dlls conf_files


TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
#ICON = icon.png


INCLUDEPATH += $$PWD/../ASN1_lib

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_console
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/debug/ -lASN1_lib_64d
   LIBS += -L$$OUT_PWD/../../ASN1_parser/qtcreator/debug/ -lASN1_parser_64d
}
CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_console
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/release/ -lASN1_lib_64
   LIBS += -L$$OUT_PWD/../../ASN1_parser/qtcreator/release/ -lASN1_parser_64
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

INSTALLS += dlls conf_files


TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += DLLCOMPIL

#TARGET = ASN1_lib

INCLUDEPATH += $$PWD/../../_bin/win_flex_bison
INCLUDEPATH += $$PWD/../ASN1_lib

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_parser_64d
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/debug/ -lASN1_lib_64d
}

CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_parser_64
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/release/ -lASN1_lib_64
}

SOURCES += Generator.cpp \
    JSGenerator.cpp \
    grammar/Lexer.cpp \
    grammar/Parser.cpp \
    ASN1_parser.cpp \
    CPPGenerator.cpp

HEADERS += \
    Generator.h \
    global.h \
    JSGenerator.h \
    grammar/Lexer.h \
    grammar/Parser.h \
    ASN1_parser.h \
    CPPGenerator.h

DISTFILES += \
    grammar.asn \
    Lexer.l \
    Parser.y

#flex.commands = .\..\..\..\_bin\win_flex_bison\win_flex.exe --wincompat $$quote($$PWD\Lexer.l)
#bison.commands = .\..\..\..\_bin\win_flex_bison\win_bison -v $$quote($$PWD/Parser.y)
#
#QMAKE_EXTRA_TARGETS += flex bison
#PRE_TARGETDEPS += flex bison

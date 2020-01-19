TEMPLATE = lib
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += DLLCOMPIL

INCLUDEPATH += $$PWD/../ASN1_lib

#INCLUDEPATH += $$PWD/../../_bin/win_flex_bison

flex.target += $$PWD/grammar/Lexer.cpp #$$PWD/grammar/Parser.cpp $$PWD/grammar/Lexer.h $$PWD/grammar/Parser.h
flex.depends += $$PWD/Lexer.l $$PWD/Parser.y
flex.commands += cd $$PWD ;
flex.commands += bison $$PWD/Parser.y ;
flex.commands += flex $$PWD/Lexer.l
QMAKE_EXTRA_TARGETS += flex
PRE_TARGETDEPS += $$PWD/grammar/Lexer.cpp #$$PWD/grammar/Parser.cpp $$PWD/grammar/Lexer.h $$PWD/grammar/Parser.h

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_parserd
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../build-ASN1_lib/debug/ -lASN1d
}

CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_parser
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../build-ASN1_lib/release/ -lASN1
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

#flex_bison_hook.depends = flex_bison
#CONFIG(debug,debug|release):flex_bison_hook.target = Makefile.Debug
#CONFIG(release,debug|release):flex_bison_hook.target = Makefile.Release
#QMAKE_EXTRA_TARGETS += flex_bison_hook

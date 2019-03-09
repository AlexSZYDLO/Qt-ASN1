#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T21:09:52
#
#-------------------------------------------------

QT       += core gui widgets
QT       += script scripttools

TARGET = ASN1_Qt
TEMPLATE = app

SOURCES += main.cpp\
    ASN1_TreeModel.cpp \
    UI_Main.cpp \
    Converters/UI_ASN1_Converter_BitString.cpp \
    Converters/UI_ASN1_Converter_Boolean.cpp \
    Converters/UI_ASN1_Converter_Enumerated.cpp \
    Converters/UI_ASN1_Converter_IA5String.cpp \
    Converters/UI_ASN1_Converter_Integer.cpp \
    Converters/UI_ASN1_Converter_ObjectID.cpp \
    Converters/UI_ASN1_Converter_OctetString.cpp \
    Converters/UI_ASN1_Converter_Real.cpp \
    Converters/UI_ASN1_Converter_UTCTime.cpp \
    Converters/UI_ASN1_Converter_UTF8String.cpp \
    Converters/UI_Converter.cpp \
    Nodes/UI_ASN1_Node_BitString.cpp \
    Nodes/UI_ASN1_Node_Boolean.cpp \
    Nodes/UI_ASN1_Node_Choice.cpp \
    Nodes/UI_ASN1_Node_Enumerated.cpp \
    Nodes/UI_ASN1_Node_IA5String.cpp \
    Nodes/UI_ASN1_Node_Integer.cpp \
    Nodes/UI_ASN1_Node_Null.cpp \
    Nodes/UI_ASN1_Node_ObjectID.cpp \
    Nodes/UI_ASN1_Node_OctetString.cpp \
    Nodes/UI_ASN1_Node_Real.cpp \
    Nodes/UI_ASN1_Node_Sequence.cpp \
    Nodes/UI_ASN1_Node_SequenceOf.cpp \
    Nodes/UI_ASN1_Node_Set.cpp \
    Nodes/UI_ASN1_Node_UTCTime.cpp \
    Nodes/UI_ASN1_Node_UTF8String.cpp \
    Nodes/UI_ASN1_Value_Main.cpp \
    UI_GrammarJS.cpp \
    JSHighlighter.cpp \
    UI_GrammarASN.cpp \
    Widgets/CustomWidgets.cpp \
    Widgets/DropablePlainTextEdit.cpp \
    Widgets/DraggableTreeWidget.cpp \
    UI_GrammarComp.cpp \
    ASNHighlighter.cpp \
    UI_TreePanel.cpp \
    UI_Editor.cpp \
    UI_Editor_Menus.cpp

HEADERS  += \
    ASN1_TreeModel.h \
    UI_Main.h \
    Converters/UI_Converter.h \
    Nodes/UI_ASN1_Value_Main.h \
    Nodes/UI_ASN1_Value_Node_Base.h \
    UI_GrammarJS.h \
    JSHighlighter.h \
    UI_GrammarASN.h \
    Widgets/CustomWidgets.h \
    Widgets/DropablePlainTextEdit.h \
    Widgets/DraggableTreeWidget.h \
    UI_GrammarComp.h \
    ASNHighlighter.h \
    UI_Editor.h \
    UI_TreePanel.h \
    UI_Editor_Menus.h


#FORMS += \
#    Forms/MainWindow.ui \
#    Forms/ValueMain.ui

INCLUDEPATH += $$PWD/../ASN1_lib
INCLUDEPATH += $$PWD/../ASN1_Qt_Script_lib
INCLUDEPATH += $$PWD/../ASN1_parser

CONFIG(debug, debug|release) {
   DESTDIR = $$OUT_PWD/debug
   TARGET = ASN1_Qt_gui
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/debug/ -lASN1_lib_64d
   LIBS += -L$$OUT_PWD/../../ASN1_parser/qtcreator/debug/ -lASN1_parser_64d
   LIBS += -L$$OUT_PWD/../../ASN1_Qt_Script_lib/qtcreator/debug/ -lASN1_Qt_Script_lib_d
}
CONFIG(release, debug|release) {
   DESTDIR = $$OUT_PWD/release
   TARGET = ASN1_Qt_gui
   OBJECTS_DIR = $$DESTDIR/obj
   MOC_DIR = $$DESTDIR/moc
   LIBS += -L$$OUT_PWD/../../ASN1_lib/qtcreator/release/ -lASN1_lib_64
   LIBS += -L$$OUT_PWD/../../ASN1_parser/qtcreator/release/ -lASN1_parser_64
   LIBS += -L$$OUT_PWD/../../ASN1_Qt_Script_lib/qtcreator/release/ -lASN1_Qt_Script_lib
}

DISTFILES += \
    StyleSheet.css \
    LICENSE.txt \
    README.txt \
    ../Grammar/modif_script.js \
    ../Grammar/test.js \
    ../Grammar/test_NEW.js \
    Config/StyleSheet.css \
    img/icon_set_2/binary.png \
    img/icon_set_2/cancel.png \
    img/icon_set_2/collapse.png \
    img/icon_set_2/compare.png \
    img/icon_set_2/cpp.png \
    img/icon_set_2/down.png \
    img/icon_set_2/expand.png \
    img/icon_set_2/help.png \
    img/icon_set_2/info.png \
    img/icon_set_2/js.png \
    img/icon_set_2/minus.png \
    img/icon_set_2/ok.png \
    img/icon_set_2/open.png \
    img/icon_set_2/plus.png \
    img/icon_set_2/read.png \
    img/icon_set_2/run.png \
    img/icon_set_2/save.png \
    img/icon_set_2/search.png \
    img/icon_set_2/select.png \
    img/icon_set_2/settings.png \
    img/icon_set_2/tool.png \
    img/icon_set_2/toolbox.png \
    img/icon_set_2/up.png \
    img/icon_set_2/write.png

RESOURCES += resource.qrc

conf_files.files = Config/* ../Grammar/*.js ../Grammar/*.asn

CONFIG(debug, debug|release) {
  dlls.files = $$OUT_PWD/../../ASN1_lib/qtcreator/debug/ASN1_lib_64d.dll \
               $$OUT_PWD/../../ASN1_parser/qtcreator/debug/ASN1_parser_64d.dll \
               $$OUT_PWD/../../ASN1_Qt_Script_lib/qtcreator/debug/ASN1_Qt_Script_lib_d.dll
  dlls.path  = $$OUT_PWD/debug
  conf_files.path = $$OUT_PWD/debug/config
}
CONFIG(release, debug|release) {
  dlls.files = $$OUT_PWD/../../ASN1_lib/qtcreator/release/ASN1_lib_64.dll \
               $$OUT_PWD/../../ASN1_parser/qtcreator/release/ASN1_parser_64.dll \
               $$OUT_PWD/../../ASN1_Qt_Script_lib/qtcreator/release/ASN1_Qt_Script_lib.dll
  dlls.path  = $$OUT_PWD/release
  conf_files.path = $$OUT_PWD/release/config
}

INSTALLS += dlls conf_files

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(asn1_qt_gui_SRCS
  main.cpp
  UI_Main.cpp
  UI_GrammarASN.cpp
  UI_GrammarJS.cpp
  UI_GrammarComp.cpp
  UI_TreePanel.cpp

  UI_Editor.cpp
  UI_Editor_Menus.cpp

  Widgets/CustomWidgets.cpp
  Widgets/DropablePlainTextEdit.cpp
  Widgets/DraggableTreeWidget.cpp

  ASN1_TreeModel.cpp
  JSHighlighter.cpp
  ASNHighlighter.cpp

  Converters/UI_Converter.cpp

  Converters/UI_ASN1_Converter_BitString.cpp
  Converters/UI_ASN1_Converter_Boolean.cpp
  Converters/UI_ASN1_Converter_Enumerated.cpp
  Converters/UI_ASN1_Converter_IA5String.cpp
  Converters/UI_ASN1_Converter_Integer.cpp
  Converters/UI_ASN1_Converter_ObjectID.cpp
  Converters/UI_ASN1_Converter_OctetString.cpp
  Converters/UI_ASN1_Converter_Real.cpp
  Converters/UI_ASN1_Converter_UTCTime.cpp
  Converters/UI_ASN1_Converter_UTF8String.cpp

  Nodes/UI_ASN1_Value_Main.cpp
  Nodes/UI_ASN1_Value_Node_Base.cpp

  Nodes/UI_ASN1_Node_BitString.cpp
  Nodes/UI_ASN1_Node_Boolean.cpp
  Nodes/UI_ASN1_Node_Choice.cpp
  Nodes/UI_ASN1_Node_Enumerated.cpp
  Nodes/UI_ASN1_Node_IA5String.cpp
  Nodes/UI_ASN1_Node_Integer.cpp
  Nodes/UI_ASN1_Node_Null.cpp
  Nodes/UI_ASN1_Node_ObjectID.cpp
  Nodes/UI_ASN1_Node_OctetString.cpp
  Nodes/UI_ASN1_Node_Real.cpp
  Nodes/UI_ASN1_Node_Sequence.cpp
  Nodes/UI_ASN1_Node_SequenceOf.cpp
  Nodes/UI_ASN1_Node_Set.cpp
  Nodes/UI_ASN1_Node_UTCTime.cpp
  Nodes/UI_ASN1_Node_UTF8String.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(asn1_qt_gui ${asn1_qt_gui_SRCS} resource.qrc)
target_include_directories(asn1_qt_gui PRIVATE . .. ../ASN1_lib ../ASN1_parser ../ASN1_Qt_Script_lib)
target_link_libraries(asn1_qt_gui PRIVATE asn1 asn1_parser asn1_qt_script Qt6::Widgets)

install(TARGETS asn1_qt_gui DESTINATION bin)

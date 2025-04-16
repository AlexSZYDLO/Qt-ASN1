find_package(Qt6 REQUIRED COMPONENTS Core Qml)


set(asn1_qt_script_SRCS
  Script.cpp
  # EngineInit.cpp
  ASN1_Script_Node.cpp

  Nodes/ASN1_Script_Basic_Nodes.cpp
  # Nodes/ASN1_Script_Choice.cpp
  Nodes/ASN1_Script_Sequence.cpp
  # Nodes/ASN1_Script_SequenceOf.cpp
  # Nodes/ASN1_Script_Set.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(asn1_qt_script SHARED ${asn1_qt_script_SRCS})

target_include_directories(asn1_qt_script PRIVATE .. ../ASN1_lib)
target_link_libraries(asn1_qt_script PUBLIC asn1 Qt6::Qml)

add_executable(asn1_qt_script_test exe.cpp)
target_include_directories(asn1_qt_script_test PRIVATE .. ../ASN1_lib)
target_link_libraries(asn1_qt_script_test PUBLIC asn1_qt_script)

install(TARGETS asn1_qt_script DESTINATION lib)

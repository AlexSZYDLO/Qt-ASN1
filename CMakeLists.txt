PROJECT(asn1)

cmake_minimum_required(VERSION 3.22)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug) # RelWithDebInfo/Debug

# From the bin directory, let the executables find libraries in the lib directory
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib") # From the bin directory, let the exe find the .so in the lib directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build)

# do not expose instantiated template functions outside libraries # ADD_DEFINITIONS(-fvisibility-inlines-hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN true)
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)

install(FILES
  ${CMAKE_SOURCE_DIR}/Grammar/ASNambigous_case.asn
  ${CMAKE_SOURCE_DIR}/Grammar/ASNgrammar1.asn
  ${CMAKE_SOURCE_DIR}/Grammar/gramm_test.asn
  "${CMAKE_SOURCE_DIR}/Grammar/PEDefinitions V1.0.asn"
  "${CMAKE_SOURCE_DIR}/Grammar/PEDefinitions V1.0_edit.asn"
  "${CMAKE_SOURCE_DIR}/Grammar/JS1.js"
  DESTINATION Grammar)

add_subdirectory(src/ASN1_lib)
add_subdirectory(src/ASN1_parser)
add_subdirectory(src/ASN1_console)
add_subdirectory(src/ASN1_Qt_Script_lib)
add_subdirectory(src/ASN1_Qt_gui)

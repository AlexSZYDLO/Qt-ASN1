PROJECT(asn1)

cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug) # RelWithDebInfo/Debug
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN true) # do not expose instantiated template functions outside libraries # ADD_DEFINITIONS(-fvisibility-inlines-hidden)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build)

# From the bin directory, let the executables find libraries in the lib directory
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib") # From the bin directory, let the exe find the .so in the lib directory

install(FILES
  ${CMAKE_SOURCE_DIR}/Grammar/ASNambigous_case.asn
  ${CMAKE_SOURCE_DIR}/Grammar/ASNgrammar1.asn
  ${CMAKE_SOURCE_DIR}/Grammar/gramm_test.asn
  "${CMAKE_SOURCE_DIR}/Grammar/PEDefinitions V1.0.asn"
  "${CMAKE_SOURCE_DIR}/Grammar/PEDefinitions V1.0_edit.asn"
  DESTINATION Grammar)

add_subdirectory(src/ASN1_lib)
add_subdirectory(src/ASN1_parser)
add_subdirectory(src/ASN1_console)

# SET(asn1_lib_SRCS  ASN1_Value.cpp ..... )

# add_library(asn1_lib SHARED ${asn1_lib_SRCS})
# add_executable(asn1 main.cpp)
# add_dependencies(asn1 asn1_lib)

# target_link_libraries(asn1 dl pthread)
# target_link_libraries(asn1 asn1_lib)

# install(TARGETS asn1_lib DESTINATION lib)
# install(TARGETS asn1 DESTINATION bin)



# target_include_directories(fgm PUBLIC .. PRIVATE . ${PUGI_XML_INCLUDE_DIRS})
# target_compile_options(fgm PRIVATE ${DIRECTOR_WARNING_FLAGS})
# target_link_libraries(fgm cu ${PUGI_XML_LIBRARIES} MagicEnum::MagicEnum)

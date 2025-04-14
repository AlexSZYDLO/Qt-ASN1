find_package(FLEX)
find_package(BISON)

flex_target(MyLexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/Lexer.h)

  bison_target(MyParser Parser.y ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/Parser.h)

add_flex_bison_dependency(MyLexer MyParser)

set(asn1_parser_SRCS
  ASN1_parser.cpp
  CPPGenerator.cpp
  JSGenerator.cpp
  Generator.cpp

  ${FLEX_MyLexer_OUTPUTS}
  ${BISON_MyParser_OUTPUTS}
)

add_library(asn1_parser SHARED ${asn1_parser_SRCS})

# include "." so that the flex and bison generated files can find the headers
target_include_directories(asn1_parser PRIVATE . .. ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(asn1_parser PUBLIC asn1)

install(TARGETS asn1_parser DESTINATION lib)

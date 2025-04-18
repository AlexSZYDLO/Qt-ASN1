set(asn1_console_SRCS main.cpp)

add_executable(asn1_console ${asn1_console_SRCS})

target_include_directories(asn1_console PRIVATE .. ../ASN1_lib ../ASN1_parser)
target_link_libraries(asn1_console PUBLIC asn1 asn1_parser)

install(TARGETS asn1_console DESTINATION bin)

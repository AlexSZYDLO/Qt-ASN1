set(asn1_SRCS
  ASN1_Value.cpp
  ASN1_Object.cpp
  ByteArray.cpp
  Utils.cpp
  Values/ASN1_Value_Nodes.cpp
  Values/ASN1_ValueBitString.cpp
  Values/ASN1_ValueBoolean.cpp
  Values/ASN1_ValueUTCTime.cpp
  Values/ASN1_ValueObjectID.cpp
  Values/ASN1_ValueInteger.cpp
  Values/ASN1_ValueIA5String.cpp
  Values/ASN1_ValueSequence.cpp
  Values/ASN1_ValueNull.cpp
  Values/ASN1_ValueChoice.cpp
  Values/ASN1_ValueUTF8String.cpp
  Values/ASN1_ValueEnumerated.cpp
  Values/ASN1_ValueOctetString.cpp
  Values/ASN1_ValueReal.cpp
  Values/ASN1_ValueSequenceOf.cpp
  Values/ASN1_ValueSet.cpp
  Objects/ASN1_Object_Nodes.cpp
  Objects/ASN1_Choice.cpp
  Objects/ASN1_Sequence.cpp
  Objects/ASN1_Set.cpp
  Objects/ASN1_SequenceOf.cpp

  # C_Interface.cpp
)

add_library(asn1 SHARED ${asn1_SRCS})

install(TARGETS asn1 DESTINATION lib)

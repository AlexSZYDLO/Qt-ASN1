/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#include "ASN1_Object_Nodes.h"
#include "../Values/ASN1_Value_Nodes.h"

using namespace Value;

#ifndef OBJECT_CONSTRUCTOR_IMPL
#define OBJECT_CONSTRUCTOR_IMPL(name) \
ASN1_##name::ASN1_##name(const char* objectName, \
  const ByteArray& tag, \
  bool optional, \
  bool explicitTag, \
  const ASN1_##name *defaultValue) { \
  ASN1_Value##name *def = static_cast<ASN1_Value##name *>(defaultValue != nullptr ? defaultValue->GetValue() : nullptr); \
    Value = new ASN1_Value##name(objectName, this, tag, optional, explicitTag, def); \
}
#endif

#ifndef OBJECT_DESTRUCTOR_IMPL
#define OBJECT_DESTRUCTOR_IMPL(name) ASN1_##name::~ASN1_##name() {}
#endif

#ifndef OBJECT_SET_VALUE_FUNCTION_IMPL
#define OBJECT_SET_VALUE_FUNCTION_IMPL(name, type) void ASN1_##name::Set##name##Value(const type &val) \
{ std::string error; static_cast<ASN1_Value##name *>(GetValue())->Set##name##Value(val, error); }
#endif

#ifndef OBJECT_SET_VALUE_CHECK_FUNCTION_IMPL
#define OBJECT_SET_VALUE_CHECK_FUNCTION_IMPL(name, type) void ASN1_##name::Set##name##Value(const type &val, std::string &error) \
{ static_cast<ASN1_Value##name *>(GetValue())->Set##name##Value(val, error); }
#endif

#ifndef OBJECT_GET_VALUE_FUNCTION_IMPL
#define OBJECT_GET_VALUE_FUNCTION_IMPL(name, type) type ASN1_##name::Get##name##Value() const \
{ return static_cast<ASN1_Value##name *>(GetValue())->Get##name##Value(); }
#endif

#ifndef STATIC_CONVERT_TYPE_TO_HEX_FUNCTION_IMPL
#define STATIC_CONVERT_TYPE_TO_HEX_FUNCTION_IMPL(name, type) \
void ASN1_##name::name##ToHex(const type &input, ByteArray &output, std::string &error) { \
  ASN1_Value##name::name##ToHex(input, output, error); \
}
#endif

#ifndef STATIC_CONVERT_HEX_TO_TYPE_FUNCTION_IMPL
#define STATIC_CONVERT_HEX_TO_TYPE_FUNCTION_IMPL(name, type) \
void ASN1_##name::HexTo##name(const ByteArray &input, type &output, std::string &error) { \
  ASN1_Value##name::HexTo##name(input, output, error); \
}
#endif

#ifndef OBJECT_CLASS_IMPL
#define OBJECT_CLASS_IMPL(name, type) \
OBJECT_CONSTRUCTOR_IMPL(name) \
OBJECT_DESTRUCTOR_IMPL(name) \
OBJECT_SET_VALUE_FUNCTION_IMPL(name, type) \
OBJECT_SET_VALUE_CHECK_FUNCTION_IMPL(name, type)  \
OBJECT_GET_VALUE_FUNCTION_IMPL(name, type) \
STATIC_CONVERT_TYPE_TO_HEX_FUNCTION_IMPL(name, type) \
STATIC_CONVERT_HEX_TO_TYPE_FUNCTION_IMPL(name, type)
#endif

OBJECT_CLASS_IMPL(BitString, std::string)
OBJECT_CLASS_IMPL(IA5String, std::string)
OBJECT_CLASS_IMPL(ObjectID, std::string)
OBJECT_CLASS_IMPL(UTCTime, std::string)
OBJECT_CLASS_IMPL(UTF8String, std::string)
OBJECT_CLASS_IMPL(Null, bool)
OBJECT_CLASS_IMPL(Boolean, bool)
OBJECT_CLASS_IMPL(Enumerated, int)
OBJECT_CLASS_IMPL(Integer, int)
OBJECT_CLASS_IMPL(OctetString, ByteArray)
OBJECT_CLASS_IMPL(Real, double)

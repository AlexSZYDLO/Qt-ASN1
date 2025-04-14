/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#pragma once
#include "../ASN1_Value.h"

//#ifndef NODE_CONSTRUCTOR
#define NODE_CONSTRUCTOR(name, defTag, initValue) \
ASN1_Value##name(const std::string& name, \
  ASN1_Object* grammarObject, \
  const ByteArray& tag, \
  bool optional, \
  bool explicitTag, \
  const ASN1_Value##name* defaultValue) \
  : ASN1_Value(name, grammarObject, tag, defTag, optional, explicitTag, defaultValue) { \
    std::string err; \
    Set##name##Value(initValue, err); \
}
//#endif

//#ifndef NODE_DESTRUCTOR
#define NODE_DESTRUCTOR(name) virtual ~ASN1_Value##name() override {}
//#endif

//#ifndef GET_TYPE_FUNCTION
#define GET_TYPE_FUNCTION(name) virtual Utils::eNodeType GetType() const override { return Utils::c##name; }
//#endif

//#ifndef GET_FUNCTION
#define GET_FUNCTION(name, type) type Get##name##Value() const { return m_Value##name; }
//#endif

//#ifndef SET_FUNCTION
#define SET_FUNCTION(name, type) \
void Set##name##Value(const type &value, std::string &error) { \
  error.clear(); \
  ByteArray output; \
  name##ToHex(value, output, error); \
  if (error.empty()) { \
    m_Value##name = value; \
    m_Value = output; \
  } \
}
//#endif

//#ifndef TYPE_TO_HEX_FUNCTION_DECL
#define TYPE_TO_HEX_FUNCTION_DECL(name, type) \
static void name##ToHex(const type &input, ByteArray &output, std::string &error);
//#endif

//#ifndef HEX_TO_TYPE_FUNCTION_DECL
#define HEX_TO_TYPE_FUNCTION_DECL(name, type) \
static void HexTo##name(const ByteArray &input, type &output, std::string &error);
//#endif

//#ifndef SET_HEX_VALUE_FUNCTION
#define SET_HEX_VALUE_FUNCTION(name, type) \
virtual void SetHexValue(const ByteArray &rawValue, std::string &error) override { \
  type output; \
  error.clear(); \
  HexTo##name(rawValue, output, error); \
  if (error.empty()) { \
    m_Value = rawValue; \
    m_Value##name = output; \
  } \
}
//#endif

//#ifndef NODE_CLASS
#define NODE_CLASS(name, type, defTag, initValue) \
class ASN1_Value##name : public ASN1_Value { \
protected: \
  type m_Value##name; \
  \
public: \
  NODE_CONSTRUCTOR(name, defTag, initValue) \
  NODE_DESTRUCTOR(name) \
  \
  GET_TYPE_FUNCTION(name) \
  \
  GET_FUNCTION(name, type) \
  SET_FUNCTION(name, type) \
  \
  SET_HEX_VALUE_FUNCTION(name, type) \
  \
  TYPE_TO_HEX_FUNCTION_DECL(name, type) \
  HEX_TO_TYPE_FUNCTION_DECL(name, type) \
};
//#endif

namespace Value {
  NODE_CLASS(Boolean, bool, "01", false)
  NODE_CLASS(BitString, std::string, "03", "")
  NODE_CLASS(Enumerated, int, "0A", 0)
  NODE_CLASS(Integer, int, "02", 0)
  NODE_CLASS(Null, bool, "05", true)
  NODE_CLASS(IA5String, std::string, "16", "")
  NODE_CLASS(UTF8String, std::string, "0C", "")
  NODE_CLASS(UTCTime, std::string, "17", "0000000000Z")
  NODE_CLASS(Real, double, "09", 0.0)
  NODE_CLASS(OctetString, ByteArray, "04", "")
  NODE_CLASS(ObjectID, std::string, "06", "")
}

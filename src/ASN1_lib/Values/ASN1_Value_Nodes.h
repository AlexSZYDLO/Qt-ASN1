/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#pragma once
#include "ASN1_Value_Nodes_Interface.h"

namespace Value
{

template<Utils::eNodeType type> struct InitValue { static constexpr UnderlyingType<type>::T V = {}; };
template<> struct InitValue<Utils::cBitString> { static constexpr const char *V = ""; };
template<> struct InitValue<Utils::cIA5String> { static constexpr const char *V = ""; };
template<> struct InitValue<Utils::cObjectID> { static constexpr const char *V = ""; };
template<> struct InitValue<Utils::cOctetString> { static constexpr const char *V = ""; };
template<> struct InitValue<Utils::cUTCTime> { static constexpr const char *V = "0000000000Z"; };
template<> struct InitValue<Utils::cUTF8String> { static constexpr const char *V = ""; };

constexpr const char *DefaultTag(Utils::eNodeType type)
{
  switch (type)
  {
    case Utils::cBitString:  return "03";
    case Utils::cBoolean:    return "01";
    case Utils::cEnumerated: return "0A";
    case Utils::cIA5String:  return "16";
    case Utils::cInteger:    return "02";
    case Utils::cNull:       return "05";
    case Utils::cObjectID:   return "06";
    case Utils::cOctetString:return "04";
    case Utils::cReal:       return "09";
    case Utils::cUTCTime:    return "17";
    case Utils::cUTF8String: return "0C";
  }
  return "";
}

template <Utils::eNodeType T>
class ASN1_ValueDer : public ASN1_Value
{
protected:
  using U = UnderlyingType<T>::T;
  U m_TypedValue = InitValue<T>::V;

public:
  ASN1_ValueDer(const std::string &name,
                ASN1_Object *grammarObject,
                const ByteArray &tag,
                bool optional,
                bool explicitTag,
                const ASN1_ValueDer *defaultValue);

  Utils::eNodeType GetType() const override;
  U GetTypedValue() const;

  void SetHexValue(const ByteArray &rawValue, std::string &error) override;
  void SetValue(const U &value, std::string &error);

  static void ToHex(const U &input, ByteArray &output, std::string &error);
  static void FromHex(const ByteArray &input, U &output, std::string &error);
};

using ASN1_ValueBitString = ASN1_ValueDer<Utils::cBitString>;
using ASN1_ValueBoolean = ASN1_ValueDer<Utils::cBoolean>;
using ASN1_ValueEnumerated = ASN1_ValueDer<Utils::cEnumerated>;
using ASN1_ValueIA5String = ASN1_ValueDer<Utils::cIA5String>;
using ASN1_ValueInteger = ASN1_ValueDer<Utils::cInteger>;
using ASN1_ValueNull = ASN1_ValueDer<Utils::cNull>;
using ASN1_ValueObjectID = ASN1_ValueDer<Utils::cObjectID>;
using ASN1_ValueOctetString = ASN1_ValueDer<Utils::cOctetString>;
using ASN1_ValueReal = ASN1_ValueDer<Utils::cReal>;
using ASN1_ValueUTCTime = ASN1_ValueDer<Utils::cUTCTime>;
using ASN1_ValueUTF8String = ASN1_ValueDer<Utils::cUTF8String>;

} // namespace Value

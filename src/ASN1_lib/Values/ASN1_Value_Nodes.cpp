/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#include "ASN1_Value_Nodes.h"

namespace Value
{

template <Utils::eNodeType T>
ASN1_ValueDer<T>::ASN1_ValueDer(const std::string &name,
                                ASN1_Object *grammarObject,
                                const ByteArray &tag,
                                bool optional,
                                bool explicitTag,
                                const ASN1_ValueDer *defaultValue)
    : ASN1_Value(name, grammarObject, tag, DefaultTag(T), optional, explicitTag, defaultValue)
{
  std::string err;
  SetValue(m_TypedValue, err);
}

template <Utils::eNodeType T>
Utils::eNodeType ASN1_ValueDer<T>::GetType() const
{
  return T;
}

template <Utils::eNodeType T>
ASN1_ValueDer<T>::U ASN1_ValueDer<T>::GetTypedValue() const
{
  return m_TypedValue;
}

template <Utils::eNodeType T>
void ASN1_ValueDer<T>::SetHexValue(const ByteArray &rawValue, std::string &error)
{
  error.clear();
  U output;
  FromHex(rawValue, output, error);
  if (error.empty())
  {
    m_TypedValue = output;
    m_Value = rawValue;
  }
}

template <Utils::eNodeType T>
void ASN1_ValueDer<T>::SetValue(const U &value, std::string &error)
{
  error.clear();
  ByteArray output;
  ToHex(value, output, error);
  if (error.empty())
  {
    m_TypedValue = value;
    m_Value = output;
  }
}

template class ASN1_ValueDer<Utils::cBitString>;
template class ASN1_ValueDer<Utils::cBoolean>;
template class ASN1_ValueDer<Utils::cEnumerated>;
template class ASN1_ValueDer<Utils::cInteger>;
template class ASN1_ValueDer<Utils::cNull>;
template class ASN1_ValueDer<Utils::cIA5String>;
template class ASN1_ValueDer<Utils::cUTF8String>;
template class ASN1_ValueDer<Utils::cUTCTime>;
template class ASN1_ValueDer<Utils::cReal>;
template class ASN1_ValueDer<Utils::cOctetString>;
template class ASN1_ValueDer<Utils::cObjectID>;

}
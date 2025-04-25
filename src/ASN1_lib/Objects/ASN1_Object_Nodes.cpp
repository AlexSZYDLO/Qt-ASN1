/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#include "ASN1_Object_Nodes.h"
#include "../Values/ASN1_Value_Nodes.h"

using namespace Value;

template <Utils::eNodeType T>
ASN1_ObjectDer<T>::ASN1_ObjectDer(const char *objectName,
                                  const ByteArray &tag,
                                  bool optional,
                                  bool explicitTag,
                                  const ASN1_ObjectDer<T> *defaultValue)
    : ASN1_Object(objectName)
{
  V *def = defaultValue ? static_cast<V *>(defaultValue->GetPrivateObject()) : nullptr;
  Value = new V(objectName, this, tag, optional, explicitTag, def);
}

template <Utils::eNodeType T>
void ASN1_ObjectDer<T>::SetValue(const U &val)
{
  std::string error;
  static_cast<V *>(GetPrivateObject())->SetValue(val, error);
}

template <Utils::eNodeType T>
void ASN1_ObjectDer<T>::SetValue(const U &val, std::string &error)
{
  static_cast<V *>(GetPrivateObject())->SetValue(val, error);
}

template <Utils::eNodeType T>
ASN1_ObjectDer<T>::U ASN1_ObjectDer<T>::GetValue() const
{
  return static_cast<V *>(GetPrivateObject())->GetTypedValue();
}

template <Utils::eNodeType T>
void ASN1_ObjectDer<T>::ToHex(const U &input, ByteArray &output, std::string &error)
{
  V::ToHex(input, output, error);
}

template <Utils::eNodeType T>
void ASN1_ObjectDer<T>::FromHex(const ByteArray &input, U &output, std::string &error)
{
  V::FromHex(input, output, error);
}

template class ASN1_ObjectDer<Utils::cBitString>;
template class ASN1_ObjectDer<Utils::cBoolean>;
template class ASN1_ObjectDer<Utils::cEnumerated>;
template class ASN1_ObjectDer<Utils::cInteger>;
template class ASN1_ObjectDer<Utils::cNull>;
template class ASN1_ObjectDer<Utils::cIA5String>;
template class ASN1_ObjectDer<Utils::cUTF8String>;
template class ASN1_ObjectDer<Utils::cUTCTime>;
template class ASN1_ObjectDer<Utils::cReal>;
template class ASN1_ObjectDer<Utils::cOctetString>;
template class ASN1_ObjectDer<Utils::cObjectID>;
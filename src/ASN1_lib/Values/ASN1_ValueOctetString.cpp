/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value
{
template <>
void ASN1_ValueOctetString::ToHex(const ByteArray &input, ByteArray &output, std::string &error)
{
  error.clear();
  output = input;
}

template <>
void ASN1_ValueOctetString::FromHex(const ByteArray &input, ByteArray &output, std::string &error)
{
  error.clear();
  output = input;
}

} // namespace Value
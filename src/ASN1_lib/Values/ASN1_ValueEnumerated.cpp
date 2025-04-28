/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value
{
template <>
void ASN1_ValueEnumerated::ToHex(const int &input, ByteArray &output, std::string &error)
{
  ASN1_ValueInteger::ToHex(input, output, error);
}

template <>
void ASN1_ValueEnumerated::FromHex(const ByteArray &input, int &output, std::string &error)
{
  ASN1_ValueInteger::FromHex(input, output, error);
}

} // namespace Value

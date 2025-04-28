/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value
{
template <>
void ASN1_ValueUTF8String::ToHex(const std::string &input, ByteArray &output, std::string &error)
{
  error.clear();
  output = "";
  if (Utils::IsValidUTF8String(input))
    output = Utils::StringToHex(input);
  else
    error = "Input string does not match the UTF8 format";
}

template <>
void ASN1_ValueUTF8String::FromHex(const ByteArray &input, std::string &output, std::string &error)
{
  error.clear();
  output = "";
  std::string s = Utils::HexToString(input);
  if (Utils::IsValidUTF8String(s))
    output = s;
  else
    error = "Input string does not match the UTF8 format";
}

} // namespace Value

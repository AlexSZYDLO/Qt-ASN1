/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value
{
template <>
void ASN1_ValueUTCTime::ToHex(const std::string &input, ByteArray &output, std::string &error)
{
  error.clear();
  if (IsValidUTCTime(input))
    output = StringToHex(input);
  else
    error = "The input does not match the UTC Time format";
}

template <>
void ASN1_ValueUTCTime::FromHex(const ByteArray &input, std::string &output, std::string &error)
{
  error.clear();
  std::string s = HexToString(input);
  if (IsValidUTCTime(s))
    output = s;
  else
    error = "The input does not match the UTC Time format";
}

} // namespace Value
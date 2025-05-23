/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value
{

template <>
void ASN1_ValueBoolean::ToHex(const bool &input, ByteArray &output, std::string &error)
{
  error.clear();
  output = input ? "FF" : "00";
}

template <>
void ASN1_ValueBoolean::FromHex(const ByteArray &input, bool &output, std::string &error)
{
  error.clear();
  if (input == "00")
    output = false;
  else if (input == "FF")
    output = true;
  else
    error = "Boolean value can only be 00 (false) or FF(true)";
}

} // namespace Value

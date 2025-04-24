/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value
{
template <>
void ASN1_ValueNull::ToHex(const bool &, ByteArray &output, std::string &error)
{
  output = "";
  error = "To use the Null node, set it ignored or not directly on the node";
}

template <>
void ASN1_ValueNull::FromHex(const ByteArray &input, bool &, std::string &error)
{
  if (input != "")
    error = "The value of a Null node must be empty";
}

} // namespace Value
/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value {

  void ASN1_ValueIA5String::IA5StringToHex(const std::string& input, ByteArray& output, std::string& error) {
    error.clear();
    output = "";
    if (Utils::IsValidIA5String(input))
      output = Utils::StringToHex(input);
    else
      error = "Input string does not match the IA5 format";
  }

  void ASN1_ValueIA5String::HexToIA5String(const ByteArray& input, std::string& output, std::string& error) {
    error.clear();
    output = "";
    std::string s = Utils::HexToString(input);
    if (Utils::IsValidIA5String(s))
      output = s;
    else
      error = "Input string does not match the IA5 format";
  }

}

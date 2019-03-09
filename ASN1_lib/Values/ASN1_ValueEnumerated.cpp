/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value {

  void ASN1_ValueEnumerated::EnumeratedToHex(const int& input, ByteArray& output, std::string& error) {
    ASN1_ValueInteger::IntegerToHex(input, output, error);
  }

  void ASN1_ValueEnumerated::HexToEnumerated(const ByteArray& input, int& output, std::string& error) {
    ASN1_ValueInteger::HexToInteger(input, output, error);
  }

}

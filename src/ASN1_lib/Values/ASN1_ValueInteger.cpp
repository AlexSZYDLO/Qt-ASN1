/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value {

  void ASN1_ValueInteger::IntegerToHex(const int& input, ByteArray& output, std::string& error) {
    error.clear();
    output.Clear();
    // Based on two's complement. ASN1 doesn't use all the bytes of the integer. we remove the '00' or 'FF' that are useless. The sign is coded by the first 'usefull' byte
    // ex: FF FF FF 05 -> FF 05     -     00 00 00 50 -> 50

    unsigned char b1, b2;
    output = IntAsHex(input);

    bool Stop = false;
    while (!Stop) {
      Stop = true;
      if (output.Size() > 1) {
        b1 = static_cast<unsigned char>(HexAsInt(output[0]));
        b2 = static_cast<unsigned char>(HexAsInt(output[1]));
        if (((b1 == 0) && ((b2 & 128) == 0)) || ((b1 == 255) && ((b2 & 128) == 128))) {
          ByteArray tempHex;
          output.GetBytesAtRank(1, output.Size() - 1, tempHex);
          output = tempHex;
          Stop = false;
        }
      }
    }
    b1 = static_cast<unsigned char>(HexAsInt(output[0]));
    if ((input > 0) && ((b1 & 128) == 128)) {
      output.InsertAt("00");
    }
  }

  void ASN1_ValueInteger::HexToInteger(const ByteArray& input, int& output, std::string& error) {
    error.clear();
    // Based on two's complement. ASN1 doesn't use all the bytes of the integer. we remove the '00' or 'FF' that are useless. The sign is coded by the first 'usefull' byte
    // The 'not' is done manually as we dont know the number of bytes that code the integer value
    if (input.Size() > 0 && input.Size() < 5) {
      unsigned char b1 = static_cast<unsigned char>(HexAsInt(input[0]));
      if ((b1 & 128) == 128) { // if negative integer
        ByteArray longValue = input;
        while (longValue.Size() < sizeof(int))
          longValue.InsertAt("FF");
        output = static_cast<int>(HexAsInt(longValue));
      }
      else {
        output = static_cast<int>(HexAsInt(input));
      }
    }
    else error = "Input buffer must have a size between 1 and 4";
  }

}

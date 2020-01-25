/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value {

  void ASN1_ValueBitString::BitStringToHex(const std::string& input, ByteArray& output, std::string& error) {
    error.clear();
    output.Clear();
    if (IsBinary(input)) {
      std::string tempBinary = input;

      int uselessBits = 0;
      while (tempBinary.size() % 8 != 0) {
        tempBinary.push_back('0');
        uselessBits++;
      }
      if (tempBinary.size() > 0) {
        output.Append(IntAsHex(uselessBits));
        output.Append(BinaryAsHex(tempBinary));
      }
    }
    else {
      error = "BitString input must be a string of 0 and 1";
    }
  }

  void ASN1_ValueBitString::HexToBitString(const ByteArray& input, std::string& output, std::string& error) {
    // first byte of bitstring contains the number of bits to remove. It is a value contained between 0 and 8
    error.clear();
    output.clear();
    unsigned int uselessBits = 0;
    ByteArray uselessBitsAsHex, data;

    if (input.Size() == 0)
      return; //output empty - OK
    if (input.Size() == 1) {
      error = "BitString has a length of 1 byte, which is not valid. First byte encodes the number of unused bits, and the rest encodes the data.";
      return;
    }

    // get first byte to extract the nummber of bits that will have to be removed.
    input.GetByteAtRank(0, uselessBitsAsHex);
    uselessBits = HexAsInt(uselessBitsAsHex);

    if (uselessBits > 7) {
      error = "The first byte of a BitString must be convertible into an integer in the range 0-7";
      return;
    }

    // Get the rest that contains the data
    input.GetBytesAtRank(1, input.Size() - 1, data);
    output = HexAsBinary8Padded(data);

    // remove the unused bits
    for (unsigned int i = 0; i < uselessBits; i++) output.pop_back();
  }

}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value_Nodes.h"

using namespace Utils;
using namespace std;

namespace Value {

  unsigned int GetNextNodeInDotString(string& DotString) {
    string IntStr;
    size_t position = DotString.find('.');
    if (position != string::npos) {
      IntStr = DotString.substr(0, position);
      DotString = DotString.substr(position + 1, DotString.size() - position);
    }
    else {
      IntStr = DotString;
      DotString = "";
    }
    try {
      return stoul(IntStr);
    }
    catch (exception&) {
      return 0;
    }
  }

  ByteArray GetNextNodeInHexString(ByteArray& OIDAsHexString) {
    ByteArray tmpByte;
    OIDAsHexString.GetByteAtRank(0, tmpByte);
    ByteArray subByteAsStr(tmpByte);
    ByteArray Result = subByteAsStr;

    OIDAsHexString.GetBytesAtRank(1, OIDAsHexString.Size() - 1, tmpByte);
    OIDAsHexString = tmpByte;
    while ((HexAsInt(subByteAsStr) & 128) == 128) {
      OIDAsHexString.GetByteAtRank(0, tmpByte);
      subByteAsStr = tmpByte;
      if (subByteAsStr != "") {
        Result.Append(subByteAsStr);
        OIDAsHexString.GetBytesAtRank(1, OIDAsHexString.Size() - 1, tmpByte);
        OIDAsHexString = tmpByte;
      }
      else {
        // ERROR, NOT COHERENT
        Result = ByteArray("");
      }
    }
    return Result;
  }

  ByteArray ConvertIntToHexNode(unsigned int integer) {
    string resultAsBinary = "";
    bool FirstLoopDone = false;

    string integerAsBinary = IntAsBinary(integer);
    if (integerAsBinary == "") integerAsBinary = "0";

    while (integerAsBinary.size() > 0) {
      string resultByteAsBinary;

      // get 7 next bits and remove them in the remaining bits
      if (integerAsBinary.size() > 6) {
        resultByteAsBinary = string(integerAsBinary.end() - 7, integerAsBinary.end());
        integerAsBinary = string(integerAsBinary.begin(), integerAsBinary.end() - 7);
      }
      else {
        resultByteAsBinary = string(integerAsBinary.begin(), integerAsBinary.end());
        integerAsBinary = "";
      }

      int pos = (int)integerAsBinary.size() - 7;
      if (pos < 0) pos = 0;
      //integerAsBinary = string(integerAsBinary.begin() + pos, integerAsBinary.end());

      while (resultByteAsBinary.size() < 7)
        resultByteAsBinary = "0" + resultByteAsBinary; // Pad result to 7 bits if result is shorter

      // add bit 8 to indicate if there is more to follow (1) or not (0)
      if (!FirstLoopDone) {
        FirstLoopDone = true;
        resultByteAsBinary = "0" + resultByteAsBinary;
      }
      else
        resultByteAsBinary = "1" + resultByteAsBinary;
      resultAsBinary = resultByteAsBinary + resultAsBinary;
    }
    return BinaryAsHex(resultAsBinary);
  }

  unsigned int ConvertHexToIntNode(const ByteArray& Node) {
    string resultAsBinary;
    string NodeAsBinary = HexAsBinary8Padded(Node);

    while ((NodeAsBinary.size() > 0)) {
      // insert 7 most right bit at the beginning of result
      resultAsBinary = string(NodeAsBinary.end() - 7, NodeAsBinary.end()) + resultAsBinary;
      // remove 8 right most bit from input
      NodeAsBinary = string(NodeAsBinary.begin(), NodeAsBinary.end() - 8);
    }
    return BinaryAsInt(resultAsBinary);
  }

  void ASN1_ValueObjectID::ObjectIDToHex(const string& input, ByteArray& output, string& error) {
    error.clear();
    output.Clear();

    if (input.size() > 0) {
      if (IsValidObjectID(input)) {
        string DotNotation = input;

        // part 1 and part 2 processed together
        unsigned int firstInt, secondInt, tempResult;
        firstInt = GetNextNodeInDotString(DotNotation); // first int is 0, 1 or 2, otherwise, undefined behavior
        secondInt = GetNextNodeInDotString(DotNotation);

        tempResult = firstInt * 40;
        if ((firstInt == 0 || firstInt == 1) && (secondInt > 39)) {
          error = "if the first node is 0 or 1, the second node must be between 0 and 39."; return;
        }
        else if (firstInt > 2) {
          error = "error in object ID, first int must be 0,1 or 2."; return;
        }
        tempResult += secondInt;

        ByteArray HexNotation = ConvertIntToHexNode(tempResult); // will code on one byte if nextint < 128 -> OID rule
        while (DotNotation != "") {
          tempResult = GetNextNodeInDotString(DotNotation);
          HexNotation.Append(ConvertIntToHexNode(tempResult));
        }
        output = HexNotation;
      }
      else error = "Object ID does not have a correct format.";
    }
  }

  void ASN1_ValueObjectID::HexToObjectID(const ByteArray& input, string& output, string& error) {
    error.clear();
    ByteArray  OIDAsHexString = input;
    if (OIDAsHexString.Size() > 0) {
      ByteArray subIntegerAsHexStr = GetNextNodeInHexString(OIDAsHexString);

      if (subIntegerAsHexStr != "") {
        // first node cannot be higher than 2, and if first node is 0 or 1, second node cannot be higher than 40 (OID rules)
        unsigned int tempInt = ConvertHexToIntNode(subIntegerAsHexStr);
        unsigned int firstNode, secondNode;
        if (tempInt < 128) {
          firstNode = tempInt / 40;
          if (firstNode > 2)
            firstNode = 2;
          secondNode = tempInt - firstNode * 40;
        }
        else {
          firstNode = 2;
          secondNode = tempInt - firstNode * 40;
        }
        output = to_string(firstNode) + '.' + to_string(secondNode);

        while (OIDAsHexString.Size() > 0) {
          subIntegerAsHexStr = GetNextNodeInHexString(OIDAsHexString);
          if (subIntegerAsHexStr != "")
            output += '.' + to_string(ConvertHexToIntNode(subIntegerAsHexStr));
          else error = "Byte array cannot be converted into an OID";
        }
      }
      else error = "Byte array cannot be converted into an OID";
    }
  }

}

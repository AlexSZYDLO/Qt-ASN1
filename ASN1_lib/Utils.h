/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <string>
#include <regex>
#include "ByteArray.h"

/*
This file contains some global methods that are usefull for ASN1 such like conversion function to different base,
tag and length encoding, and some specific node practical conversions.
*/

#if defined DLLCOMPIL
#define DLLSPEC __declspec(dllexport)
#else
#define DLLSPEC __declspec(dllimport)
#endif

namespace Utils {

  enum eNodeType {
    cBitString, cBoolean, cChoice, cEnumerated, cIA5String, cInteger, cNull, cObjectID,
    cOctetString, cReal, cSequence, cSequenceOf, cSet, cUTCTime, cUTF8String
  };

  DLLSPEC std::string NodeTypeToString(eNodeType t);

  enum eTagClass { cTagClassUniversal, cTagClassApplication, cTagClassContextSpecific, cTagClassPrivate };
  enum eTagForm { cTagFormPrimitive, cTagFormConstructed };
  enum eUTCTimeZone { cGMT, cPlus, cMinus };

  extern const std::regex rxUTCTime;
  extern const std::regex rxOID;
  extern const std::regex rxIA5String;

  DLLSPEC ByteArray IntAsHex(int i);
  DLLSPEC unsigned int HexAsInt(const ByteArray& hexStr);

  DLLSPEC ByteArray BinaryAsHex(const std::string& binary);
  DLLSPEC std::string HexAsBinary(const ByteArray& hexString);
  DLLSPEC std::string HexAsBinary8Padded(const ByteArray& hexString);

  DLLSPEC std::string IntAsBinary(unsigned int i);
  DLLSPEC std::string IntAsBinary8Padded(unsigned int i);
  DLLSPEC unsigned int BinaryAsInt(const std::string& BinaryStr);

  DLLSPEC ByteArray StringToHex(const std::string& str);
  DLLSPEC std::string HexToString(const ByteArray& hex);

  DLLSPEC bool IsHex(const std::string& str);
  DLLSPEC bool IsBinary(const std::string& str);

  DLLSPEC bool IsComplexType(eNodeType type);

  // Extracts the Tag. It read the buffer "fromBuffer" at position "pos", and if it can read a tag (based on ASN1 specification),
  // it returns it in the "tag" variable, and returns true or false
  DLLSPEC bool GetTagFromBuffer(const ByteArray& fromBuffer, unsigned int& pos, ByteArray& tag);
  //Extracts the length, see GetTagFromBuffer
  DLLSPEC bool GetLengthFromBuffer(const ByteArray& FromBuffer, unsigned int& pos, unsigned int& L);

  // Makes the length ByteArray based on ASN1 specification from an integer value.
  DLLSPEC ByteArray MakeLength(unsigned int sizeAsInt);
  // Makes the tag ByteArray based on ASN1 specification from the class, type, and label
  DLLSPEC ByteArray MakeTag(eTagClass tagClass, eTagForm tagForm, const ByteArray& label);
  DLLSPEC bool DecomposeTag(const ByteArray tag, eTagClass& tagClass, eTagForm& tagForm, ByteArray& label);

  // convenient UTC Time conversion methods
  DLLSPEC void UTCTimeToValues(const std::string& input, int& year_YY, int& month_MM, int& day_DD, int& hours_HH,
                               int& minutes_MM, int& seconds_SS, eUTCTimeZone& zone, int& zoneHours_HH, int& zoneMinutes_MM, std::string& error);
  DLLSPEC void ValuesToUTCTime(int year_YY, int month_MM, int day_DD, int hours_HH,
                               int minutes_MM, int seconds_SS, eUTCTimeZone zone, int zoneHours_HH, int zoneMinutes_MM, std::string& output, std::string& error);

  // convenient value check functions. They are only indicative, a wrong value will not be accepted in the nodes anyway
  DLLSPEC bool IsValidUTCTime(const std::string& utcTime);
  DLLSPEC bool IsValidObjectID(const std::string& objectID);
  DLLSPEC bool IsValidIA5String(const std::string& ia5String);
  DLLSPEC bool IsValidUTF8String(const std::string& utf8String);

}

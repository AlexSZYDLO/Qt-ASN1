/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <regex>
#include <string>
#include "ByteArray.h"

/*
This file contains some global methods that are usefull for ASN1 such like conversion function to different base,
tag and length encoding, and some specific node practical conversions.
*/

#ifdef _MSC_VER
#ifdef MODULE_API_EXPORTS
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif

namespace Utils {

  enum eNodeType {
    cBitString,
    cBoolean,
    cChoice,
    cEnumerated,
    cIA5String,
    cInteger,
    cNull,
    cObjectID,
    cOctetString,
    cReal,
    cSequence,
    cSequenceOf,
    cSet,
    cUTCTime,
    cUTF8String
  };

  MODULE_API std::string NodeTypeToString(eNodeType t);

  enum eTagClass {
    cTagClassUniversal,
    cTagClassApplication,
    cTagClassContextSpecific,
    cTagClassPrivate
  };
  enum eTagForm {
    cTagFormPrimitive,
    cTagFormConstructed
  };
  enum eUTCTimeZone {
    cGMT,
    cPlus,
    cMinus
  };

  extern const std::regex rxUTCTime;
  extern const std::regex rxOID;
  extern const std::regex rxIA5String;

  MODULE_API ByteArray IntAsHex(int i);
  MODULE_API unsigned int HexAsInt(const ByteArray& hexStr);

  MODULE_API ByteArray BinaryAsHex(const std::string& binary);
  MODULE_API std::string HexAsBinary(const ByteArray& hexString);
  MODULE_API std::string HexAsBinary8Padded(const ByteArray& hexString);

  MODULE_API std::string IntAsBinary(unsigned int i);
  MODULE_API std::string IntAsBinary8Padded(unsigned int i);
  MODULE_API unsigned int BinaryAsInt(const std::string& BinaryStr);

  MODULE_API ByteArray StringToHex(const std::string& str);
  MODULE_API std::string HexToString(const ByteArray& hex);

  MODULE_API bool IsHex(const std::string& str);
  MODULE_API bool IsBinary(const std::string& str);

  MODULE_API bool IsComplexType(eNodeType type);

  // Extracts the Tag. It read the buffer "fromBuffer" at position "pos", and if it can read a tag (based on ASN1 specification),
  // it returns it in the "tag" variable, and returns true or false
  MODULE_API bool GetTagFromBuffer(const ByteArray& fromBuffer, unsigned int& pos, ByteArray& tag);
  //Extracts the length, see GetTagFromBuffer
  MODULE_API bool GetLengthFromBuffer(const ByteArray& FromBuffer, unsigned int& pos, unsigned int& L);

  // Makes the length ByteArray based on ASN1 specification from an integer value.
  MODULE_API ByteArray MakeLength(unsigned int sizeAsInt);
  // Makes the tag ByteArray based on ASN1 specification from the class, type, and label
  MODULE_API ByteArray MakeTag(eTagClass tagClass, eTagForm tagForm, const ByteArray& label);
  MODULE_API bool DecomposeTag(const ByteArray tag, eTagClass& tagClass, eTagForm& tagForm, ByteArray& label);

  // convenient UTC Time conversion methods
  MODULE_API void UTCTimeToValues(const std::string& input, int& year_YY, int& month_MM, int& day_DD, int& hours_HH,
                                  int& minutes_MM, int& seconds_SS, eUTCTimeZone& zone, int& zoneHours_HH, int& zoneMinutes_MM, std::string& error);
  MODULE_API void ValuesToUTCTime(int year_YY, int month_MM, int day_DD, int hours_HH,
                                  int minutes_MM, int seconds_SS, eUTCTimeZone zone, int zoneHours_HH, int zoneMinutes_MM, std::string& output, std::string& error);

  // convenient value check functions. They are only indicative, a wrong value will not be accepted in the nodes anyway
  MODULE_API bool IsValidUTCTime(const std::string& utcTime);
  MODULE_API bool IsValidObjectID(const std::string& objectID);
  MODULE_API bool IsValidIA5String(const std::string& ia5String);
  MODULE_API bool IsValidUTF8String(const std::string& utf8String);

} // namespace Utils

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "Utils.h"
#include <bitset>
#include <codecvt>
#include <iomanip>
#include <sstream>
#include "Exceptions.h"


namespace Utils
{

const std::regex rxUTCTime(R"(^(\d{2})(\d{2})(\d{2})(\d{2})(\d{2})(\d{2})?(Z|([+-])(\d{2})(\d{2}))$)");
const std::regex rxIA5String(R"(^[ -~]*$)");

const std::string firstBytes = R"(((([01])\.([0-3][0-9]|[0-9]))|(2\.[0-9]+)))"; // if first = 0 or 1, second must be in range 0-39. if first = 2, no restriction on second
const std::string dotGroup = R"((\.\d+)*)";
const std::regex rxOID("^" + firstBytes + dotGroup + "$");

std::string NodeTypeToString(eNodeType t)
{
  switch (t)
  {
    case cBitString:
      return "BitString";
    case cBoolean:
      return "Boolean";
    case cChoice:
      return "Choice";
    case cEnumerated:
      return "Enumerated";
    case cIA5String:
      return "IA5String";
    case cInteger:
      return "Integer";
    case cNull:
      return "Null";
    case cObjectID:
      return "ObjectID";
    case cOctetString:
      return "OctetString";
    case cReal:
      return "Real";
    case cSequence:
      return "Sequence";
    case cSequenceOf:
      return "SequenceOf";
    case cSet:
      return "Set";
    case cUTCTime:
      return "UTCTime";
    case cUTF8String:
      return "UTF8String";
    default:
      return "";
  }
}

ByteArray BinaryByteToHex(std::string binary)
{
  if (binary.size() == 8)
  {
    return IntAsHex(BinaryAsInt(binary));
  }
  else
    return ByteArray("");
}

std::string HexByteToBinary(ByteArray hex)
{
  if (hex.Size() == 1)
  {
    return IntAsBinary(HexAsInt(hex));
  }
  else
    return "";
}

std::string HexByteToBinary8Padded(ByteArray hex)
{
  if (hex.Size() == 1)
  {
    return IntAsBinary8Padded(HexAsInt(hex));
  }
  else
    return "";
}

ByteArray IntAsHex(int i)
{
  std::stringstream s;
  s << std::hex << i;
  return ByteArray(s.str().c_str());
}

std::string IntAsHexStr(int i)
{
  std::stringstream s;
  s << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << i;
  return s.str();
}

unsigned int HexAsInt(const ByteArray &hexStr)
{
  unsigned int result = 0;
  std::stringstream s;
  s << std::hex << hexStr.GetString();
  s >> result;
  return result;
}

unsigned int HexAsInt(const std::string &hexStr)
{
  unsigned int result = 0;
  std::stringstream s;
  s << std::hex << hexStr;
  s >> result;
  return result;
}

ByteArray BinaryAsHex(const std::string &binary)
{
  std::string tempBinary = binary;
  if (tempBinary.size() % 8 != 0)
    tempBinary.insert(0, 8 - (tempBinary.size() % 8), '0');
  ByteArray result;
  while (tempBinary.size() > 0)
  {
    ByteArray hexByte = BinaryByteToHex(tempBinary.substr(0, 8));
    result.Append(hexByte);
    tempBinary = tempBinary.substr(8);
  }
  return result;
}

std::string HexAsBinary8Padded(const ByteArray &hexString)
{
  ByteArray remainingHex = hexString;
  std::string result;
  while (remainingHex.Size() > 0)
  {
    ByteArray tmpHex;
    remainingHex.GetByteAtRank(remainingHex.Size() - 1, tmpHex);
    std::string binaryByte = HexByteToBinary8Padded(tmpHex);
    result.insert(0, binaryByte);
    tmpHex = "";
    remainingHex.GetBytesAtRank(0, remainingHex.Size() - 1, tmpHex);
    remainingHex = tmpHex;
  }
  return result;
}

std::string HexAsBinary(const ByteArray &hexString)
{
  std::string result = HexAsBinary8Padded(hexString);
  if (result.find('1') >= result.size())
    return "";
  return result.substr(result.find('1')); // removes 0 at beginning
}

std::string IntAsBinary8Padded(unsigned int i)
{
  std::string s = std::bitset<sizeof(long) * 8>(i).to_string();
  size_t pos = s.find('1');
  if (pos >= s.size())
    return "00000000";
  while (pos > 7)
  {
    s = s.substr(8);
    pos = s.find('1');
  }
  return s;
}

std::string IntAsBinary(unsigned int i)
{
  std::string s = IntAsBinary8Padded(i);
  if (s.find('1') >= s.size())
    return "";
  return s.substr(s.find('1')); // removes 0 at beginning
}

unsigned int BinaryAsInt(const std::string &BinaryStr)
{
  //return bitset<sizeof(long) * 8>(BinaryStr).to_ulong();
  if (BinaryStr.size() < sizeof(long) * 8 + 1)
    return stoul(BinaryStr, nullptr, 2);
  else
    return 0;
}

bool IsHex(char c)
{
  return (c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || (c == '6') || (c == '7')
         || (c == '8') || (c == '9') || (c == 'A') || (c == 'B') || (c == 'C') || (c == 'D') || (c == 'E') || (c == 'F')
         || (c == 'a') || (c == 'b') || (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f');
}

bool IsHex(const std::string &str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
    bool res = IsHex(str.at(i));
    if (!res)
      return false;
  }
  return true;
}

bool IsBinary(char c)
{
  return (c == '0') || (c == '1');
}

bool IsBinary(const std::string &str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
    bool res = IsBinary(str.at(i));
    if (!res)
      return false;
  }
  return true;
}

bool IsComplexType(eNodeType type)
{
  return type == cChoice || type == cSequence || type == cSequenceOf || type == cSet;
}

ByteArray MakeLength(unsigned int sizeAsInt)
{
  ByteArray hexL = IntAsHex((int)sizeAsInt);

  if (sizeAsInt > 127)
  {
    ByteArray hexL1stPart = IntAsHex((int)hexL.Size() + 128);
    hexL.InsertAt(hexL1stPart);
  }
  return hexL;
}

ByteArray MakeTag(eTagClass tagClass, eTagForm tagForm, const ByteArray &tagLabel)
{
  std::string SecondPartLongTagAsBinary("");

  unsigned char FirstPartTag = (unsigned char)tagClass;
  FirstPartTag = FirstPartTag << 1;
  FirstPartTag += (unsigned char)tagForm;
  FirstPartTag = FirstPartTag << 5;

  if (HexAsInt(tagLabel) <= 30)
    FirstPartTag += (unsigned char)HexAsInt(tagLabel);
  else
  {
    FirstPartTag += 31;
    std::string LabelAsBinary = HexAsBinary(tagLabel);

    bool FirstLoopDone = false;
    while (LabelAsBinary.size() > 0)
    {
      std::string NextTagByteAsBinary;

      // get 7 next bits and remove them in the remaining bits
      if (LabelAsBinary.size() > 6)
      {
        NextTagByteAsBinary = std::string(LabelAsBinary.end() - 7, LabelAsBinary.end());
        LabelAsBinary = std::string(LabelAsBinary.begin(), LabelAsBinary.end() - 7);
      }
      else
      {
        NextTagByteAsBinary = std::string(LabelAsBinary.begin(), LabelAsBinary.end());
        LabelAsBinary = "";
      }

      while (NextTagByteAsBinary.size() < 7)
      {
        // Pad result to 7 bits if result is shorter
        NextTagByteAsBinary = '0' + NextTagByteAsBinary;
      }

      // add next bit 8 to indicate if there is more to follow(1) or not (0)
      if (!FirstLoopDone)
      {
        FirstLoopDone = true;
        NextTagByteAsBinary = '0' + NextTagByteAsBinary;
      }
      else
        NextTagByteAsBinary = '1' + NextTagByteAsBinary;

      SecondPartLongTagAsBinary = NextTagByteAsBinary + SecondPartLongTagAsBinary;
    }
  }

  ByteArray Tag = IntAsHex(FirstPartTag);
  if (SecondPartLongTagAsBinary != "")
    Tag.Append(BinaryAsHex(SecondPartLongTagAsBinary));
  return Tag;
}

bool DecomposeTag(const ByteArray tag, eTagClass &tagClass, eTagForm &tagForm, ByteArray &label)
{
  std::string binary = HexAsBinary(tag);
  tagClass = (eTagClass)BinaryAsInt(binary.substr(0, 2));
  tagForm = (eTagForm)BinaryAsInt(binary.substr(2, 1));
  if (binary.substr(3, 5) == "11111")
  {
    std::string binLabel;

    for (unsigned int i = 1; i < tag.Size(); i++)
    {
      binLabel.append(binary.substr(8 * i + 1, 7));
    }
    label = BinaryAsHex(binLabel);
  }
  else if (tag.Size() > 1)
    return false;
  else
    label = BinaryAsHex(binary.substr(3, 5));
  return true;
}

bool GetTagFromBuffer(const ByteArray &fromBuffer, unsigned int &pos, ByteArray &tag)
{
  const unsigned int cLongTag = 31;
  ByteArray TagSubPart;
  ByteArray Tag;

  bool bRes = fromBuffer.GetByteAtRank(pos, TagSubPart);
  if (bRes)
  {
    Tag.Append(TagSubPart);
    pos++;

    if ((HexAsInt(TagSubPart) & cLongTag) == cLongTag)
    {
      bool ReadNextByte = true;
      while (ReadNextByte)
      {
        bRes = fromBuffer.GetByteAtRank(pos, TagSubPart);
        if (bRes)
        {
          pos++;
          if ((HexAsInt(TagSubPart) & 128) != 128)
            ReadNextByte = false;
          Tag.Append(TagSubPart);
        }
        else
          break;
      }
    }
  }
  if (bRes)
    tag = Tag;
  return bRes;
}

bool GetLengthFromBuffer(const ByteArray &FromBuffer, unsigned int &pos, unsigned int &L)
{
  const unsigned int cLongForm = 128;
  ByteArray LByte;

  bool bRes = FromBuffer.GetByteAtRank(pos, LByte);
  if (bRes)
  {
    pos++;
    unsigned int LByteAsInt = HexAsInt(LByte);
    if ((LByteAsInt & cLongForm) == cLongForm)
    {
      ByteArray Llong;
      LByteAsInt -= cLongForm;
      bRes = FromBuffer.GetBytesAtRank(pos, LByteAsInt, Llong);
      if (bRes)
      {
        pos += LByteAsInt;
        L = HexAsInt(Llong);
      }
    }
    else
      L = LByteAsInt;
  }
  return bRes;
}

ByteArray StringToHex(const std::string &str)
{
  ByteArray returnVal;
  for (size_t i = 0; i < str.size(); i++)
  {
    unsigned char c = static_cast<unsigned char>(str[i]);
    returnVal.Append(IntAsHex(c));
  }
  return returnVal;
}

std::string HexToString(const ByteArray &hex)
{
  std::string returnVal;
  for (unsigned int i = 0; i < hex.Size(); i++)
  {
    ByteArray hexByte;
    hex.GetByteAtRank(i, hexByte);
    unsigned char c = static_cast<unsigned char>(HexAsInt(hexByte));
    returnVal += static_cast<char>(c);
  }
  return returnVal;
}

void UTCTimeToValues(const std::string &input,
                     int &year_YY,
                     int &month_MM,
                     int &day_DD,
                     int &hours_HH,
                     int &minutes_MM,
                     int &seconds_SS,
                     eUTCTimeZone &zone,
                     int &zoneHours_HH,
                     int &zoneMinutes_MM,
                     std::string &error)
{
  std::smatch match;
  if (regex_match(input, match, rxUTCTime))
  {
    year_YY = stoi(match.str(1));
    month_MM = stoi(match.str(2));
    day_DD = stoi(match.str(3));
    hours_HH = stoi(match.str(4));
    minutes_MM = stoi(match.str(5));
    seconds_SS = (match[6].matched) ? stoi(match.str(6)) : 0;

    if (match.str(7) == "Z")
    {
      zone = cGMT;
      zoneHours_HH = zoneMinutes_MM = 0;
    }
    else
    {
      zone = (match.str(8) == "+") ? cPlus : cMinus;
      zoneHours_HH = stoi(match.str(9));
      zoneMinutes_MM = stoi(match.str(10));
    }
  }
  else
    error = "The input string does not match the UTC Time format";
}

void ValuesToUTCTime(int year_YY,
                     int month_MM,
                     int day_DD,
                     int hours_HH,
                     int minutes_MM,
                     int seconds_SS,
                     eUTCTimeZone zone,
                     int zoneHours_HH,
                     int zoneMinutes_MM,
                     std::string &output,
                     std::string &error)
{
  output.clear();
  if (year_YY < -1 || year_YY > 100)
  {
    error = "Year must be between 0 and 99";
    return;
  }
  if (month_MM < 0 || month_MM > 13)
  {
    error = "Month must be between 1 and 12";
    return;
  }
  if (day_DD < 0 || day_DD > 32)
  {
    error = "Day must be between 0 and 99";
    return;
  }
  if (hours_HH < -1 || hours_HH > 24)
  {
    error = "Hours must be between 0 and 23";
    return;
  }
  if (minutes_MM < -1 || minutes_MM > 61)
  {
    error = "Minutes must be between 0 and 60";
    return;
  }
  if (seconds_SS < -1 || seconds_SS > 61)
  {
    error = "Seconds must be between 0 and 60";
    return;
  }
  if (zoneHours_HH < -1 || zoneHours_HH > 13)
  {
    error = "Time Zone Hours must be between 0 and 23";
    return;
  }
  if (zoneMinutes_MM < -1 || zoneMinutes_MM > 60)
  {
    error = "Time Zone Minutes must be between 0 and 60";
    return;
  }

  std::stringstream s;
  s << std::setfill('0') << std::setw(2) << year_YY << std::setw(2) << month_MM << std::setw(2) << day_DD << std::setw(2) << hours_HH << std::setw(2)
    << minutes_MM;
  if (seconds_SS != 0)
    s << std::setw(2) << seconds_SS; // seconds are optional
  if (zone == cGMT)
    s << "Z";
  else
    s << (zone == cPlus ? "+" : "-") << std::setw(2) << zoneHours_HH << std::setw(2) << zoneMinutes_MM;
  output = s.str();
}

bool IsValidUTCTime(const std::string &utcTime)
{
  return regex_match(utcTime, rxUTCTime) ? true : false;
}

bool IsValidObjectID(const std::string &objectID)
{
  if (objectID == "")
    return true;
  return regex_match(objectID, rxOID) ? true : false;
}

bool IsValidIA5String(const std::string &ia5String)
{
  return regex_match(ia5String, rxIA5String) ? true : false;
}

bool IsValidUTF8String(const std::string &utf8String)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;

  try
  {
    conv.from_bytes(utf8String);
    //u32string str = reinterpret_cast<const char32_t*>(conv.from_bytes(utf8String).c_str());
  }
  catch (const std::range_error &e)
  {
    std::string s = e.what();
    return false;
  }
  return true;
}
} // namespace Utils

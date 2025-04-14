/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ByteArray.h"
#include <algorithm>
#include <sstream>
#include "Utils.h"

using namespace Utils;

ByteArray::~ByteArray() {}

ByteArray::ByteArray(const ByteArray& hexStr) {
  m_HexValue = hexStr.m_HexValue;
}

ByteArray::ByteArray(const char* str) {
  std::string s;

  // Pad value if size is not even
  if(strlen(str) % 2 != 0)
    s.append("0");
  s.append(str);

  if(IsHex(s)) {
    for (int i = 0; i < s.size(); i += 2)
    {
      std::string hex_byte;
      hex_byte.push_back(s[i]);
      hex_byte.push_back(s[i + 1]);
      m_HexValue.push_back(HexAsInt(hex_byte));
    }
  }
}

unsigned int ByteArray::Size() const {
  return static_cast<unsigned int>(m_HexValue.size());
}

std::string ByteArray::GetString() const {
  std::string res;
  for (int i = 0; i < m_HexValue.size(); i++)
  {
    res += IntAsHexStr(m_HexValue.at(i));
  }
  return res;
}

bool ByteArray::GetByteAtRank(unsigned int ByteRank, ByteArray& theByte) const {
  if(ByteRank < Size()) {
    theByte.Append(m_HexValue.at(ByteRank));
    return true;
  }
  return false;
}

bool ByteArray::GetBytesAtRank(unsigned int firstByteRank, unsigned int nbOfBytes, ByteArray& theBytes) const {
  if(firstByteRank + nbOfBytes <= Size()) {
    for(unsigned int i = firstByteRank; i < firstByteRank + nbOfBytes; i++) {
      theBytes.Append(m_HexValue.at(i));
    }
    return true;
  }
  return false;
}

void ByteArray::Clear() {
  m_HexValue.clear();
}

void ByteArray::Append(unsigned char ByteToAppend) {
  m_HexValue.push_back(ByteToAppend);
}

void ByteArray::Append(const ByteArray& bufferToAppend) {
  m_HexValue.insert(m_HexValue.end(), bufferToAppend.m_HexValue.begin(), bufferToAppend.m_HexValue.end());
}

bool ByteArray::InsertAt(const ByteArray& bufferToAppend, unsigned int pos) {
  std::string s = bufferToAppend.GetString();

  if(Size() >= pos) {
    m_HexValue.insert(m_HexValue.begin() + pos, bufferToAppend.m_HexValue.begin(), bufferToAppend.m_HexValue.end());
    return true;
  }
  return false;
}

ByteArray ByteArray::operator[](unsigned int index) const {
  ByteArray byte;
  GetByteAtRank(index, byte);
  return byte;
}

bool ByteArray::Equals(const ByteArray& hex) const {
  return *this == hex;
}

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
  std::string s(str);
  if(IsHex(s)) {
    std::string strUpper = s;
    std::transform(strUpper.begin(), strUpper.end(), strUpper.begin(), toupper);
    m_HexValue += strUpper;

    // Pad value if size is not even
    if(m_HexValue.size() % 2 != 0)
      m_HexValue.insert(m_HexValue.begin(), '0');
  }
}

unsigned int ByteArray::Size() const {
  return static_cast<unsigned int>(m_HexValue.size() / 2);
}

const char* ByteArray::GetString() const {
  return m_HexValue.c_str();
}

bool ByteArray::GetByteAtRank(unsigned int ByteRank, ByteArray& theByte) const {
  if(ByteRank < Size()) {
    unsigned int j = ByteRank * 2;
    std::string s;
    s = m_HexValue.at(j);
    s += m_HexValue.at(++j);
    theByte = ByteArray(s.c_str());
    return true;
  }
  return false;
}

bool ByteArray::GetBytesAtRank(unsigned int firstByteRank, unsigned int nbOfBytes, ByteArray& theBytes) const {
  if(firstByteRank + nbOfBytes <= Size()) {
    ByteArray hexS;
    for(unsigned int i = firstByteRank; i < firstByteRank + nbOfBytes; i++) {
      size_t j = i * 2;
      std::string s;
      s = m_HexValue.at(j);
      s += m_HexValue.at(++j);
      hexS.Append(ByteArray(s.c_str()));
    }
    theBytes = hexS;
    return true;
  }
  return false;
}


void ByteArray::Clear() {
  m_HexValue.clear();
}

void ByteArray::Append(const ByteArray& bufferToAppend) {
  m_HexValue += std::string(bufferToAppend.GetString());
}

bool ByteArray::InsertAt(const ByteArray& bufferToAppend, unsigned int pos) {
  std::string s(bufferToAppend.GetString());

  if(Size() >= pos) {
    for(size_t i = s.size(); i > 0; i--) {
      m_HexValue.insert(m_HexValue.begin() + pos * 2, s.at(i - 1));
    }
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

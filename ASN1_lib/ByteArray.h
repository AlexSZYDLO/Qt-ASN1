/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <string>

/*
The ByteArray class is an hexadecimal buffer. It works internally with a std::string, that can be read with GetString()
It provides functions to access specific byte(s), and to edit the string.

This class ensures that it only contains hexadecimal characters.
*/

#if defined DLLCOMPIL
#define DLLSPEC __declspec(dllexport)
#else
#define DLLSPEC __declspec(dllimport)
#endif

class ByteArray {
  friend bool operator==(const ByteArray& hexStr, const ByteArray& hexStr2);

 private:
  std::string m_HexValue;

 public:
  DLLSPEC ~ByteArray();
  DLLSPEC ByteArray(const ByteArray& hexStr);
  DLLSPEC ByteArray(const char* str = "");

  DLLSPEC unsigned int Size() const;
  DLLSPEC bool Equals(const ByteArray& hex) const;

  DLLSPEC const char* GetString() const;
  DLLSPEC bool GetByteAtRank(unsigned int ByteRank, ByteArray& theByte) const;
  DLLSPEC bool GetBytesAtRank(unsigned int firstByteRank, unsigned int nbOfBytes, ByteArray& theBytes) const;
  DLLSPEC ByteArray operator[](unsigned int index) const;

  DLLSPEC void Clear();
  DLLSPEC void Append(const ByteArray& bufferToAppend);
  DLLSPEC bool InsertAt(const ByteArray& bufferToAppend, unsigned int pos = 0);
};

inline bool operator==(const ByteArray& hexStr, const ByteArray& hexStr2) { return hexStr.m_HexValue == hexStr2.m_HexValue; }
inline bool operator!=(const ByteArray& hexStr, const ByteArray& hexStr2) { return !(hexStr == hexStr2); }

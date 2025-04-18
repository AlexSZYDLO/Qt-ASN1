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

#ifdef _MSC_VER
#ifdef MODULE_API_EXPORTS
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif


class ByteArray {
  friend bool operator==(const ByteArray& hexStr, const ByteArray& hexStr2);

 private:
  std::string m_HexValue;

 public:
  MODULE_API ~ByteArray();
  MODULE_API ByteArray(const ByteArray& hexStr);
  MODULE_API ByteArray(const char* str = "");

  MODULE_API unsigned int Size() const;
  MODULE_API bool Equals(const ByteArray& hex) const;

  MODULE_API const char* GetString() const;
  MODULE_API bool GetByteAtRank(unsigned int ByteRank, ByteArray& theByte) const;
  MODULE_API bool GetBytesAtRank(unsigned int firstByteRank, unsigned int nbOfBytes, ByteArray& theBytes) const;
  MODULE_API ByteArray operator[](unsigned int index) const;

  MODULE_API void Clear();
  MODULE_API void Append(const ByteArray& bufferToAppend);
  MODULE_API bool InsertAt(const ByteArray& bufferToAppend, unsigned int pos = 0);
};

inline bool operator==(const ByteArray& hexStr, const ByteArray& hexStr2) { return hexStr.m_HexValue == hexStr2.m_HexValue; }
inline bool operator!=(const ByteArray& hexStr, const ByteArray& hexStr2) { return !(hexStr == hexStr2); }

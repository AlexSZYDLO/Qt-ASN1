/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <exception>
#include <sstream>
#include <string>
#include <vector>
#include "ASN1_Object.h"

namespace Utils {
  class ParsingEx : public std::exception {
   protected:
    std::string m_ConcatenatedErrors;
    ASN1_Object* m_Obj;
    unsigned int m_BufferIndex;

   public:
    ParsingEx(std::string error, ASN1_Object* obj, unsigned int index)
        : m_Obj(obj), m_BufferIndex(index) {
      AddError(error);
    }

    void AddError(std::string error) { m_ConcatenatedErrors.append(error + '\n'); }

    virtual const char* what() const noexcept override { return m_ConcatenatedErrors.c_str(); }
    ASN1_Object* GetFailingObject() { return m_Obj; }
    unsigned int GetIndex() { return m_BufferIndex; }
    bool ErrorEmptyBuffer();
  };
} // namespace Utils

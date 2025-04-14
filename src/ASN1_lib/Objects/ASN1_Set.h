/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Object.h"

/*
ASN1 nodes definition for set. See comment in ASN1_Object_Nodes.h for further explanations.
The set must be initialized with an array of object(s), and as second parameter, the size of the array.
If the number does not correspond, it may lead to undefined behavior.

The set can support extensibility. While reading a buffer, if more data than expected is present, it will be put into an Extensibility Octet String
*/

class MODULE_API ASN1_Set : public ASN1_Object {
 public:
  ASN1_Set(ASN1_Object* valuesArray[],
           unsigned int numberOfValues,
           const char* name = "",
           const ByteArray& tag = "",
           bool optional = false,
           bool explicitTag = false,
           const ASN1_Set* defaultSet = nullptr,
           bool extensibility = false);
  virtual ~ASN1_Set();

  bool IsExtensible() const;

  ASN1_Object* GetObjectAt(unsigned int pos) const;
  ASN1_Object* GetExtensibilityObjectAt(unsigned int pos) const;

  unsigned int GetSize() const;
  unsigned int GetExtensibilitySize() const;

  //void AppendExtensibilityObject(ASN1_Object* obj);
};

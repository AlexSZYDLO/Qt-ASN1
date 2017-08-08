/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Object.h"

/*
ASN1 nodes definition for sequence of. See comment in ASN1_Object_Nodes.h for further explanations.
The sequence of works with a callback just like choice (see ASN1_Choice.h)
Unlike choices, the callback of a sequence of must always return the same object. It is appended to a list and kept in the sequence of.
It is accessible by its index, can be moved up and down, or deleted.

The GetDummyNewObject() function returns an object that is not appended to the sequence of. Its only purpose is to give a preview of what the object looks like.
The dummy object must be deleted after use to clean the memory.
*/

class DLLSPEC ASN1_SequenceOf : public ASN1_Object {
 public:
  struct callbackSequenceOf {
    typedef ASN1_Object* (*callbackFunctionType)(void* context);

    callbackFunctionType f;
    void* context;
  };

  ASN1_SequenceOf(callbackSequenceOf newSeqOfObject,
                  const char* name = "",
                  const ByteArray& tag = "",
                  bool optional = false,
                  bool explicitTag = false,
                  const ASN1_SequenceOf* defaultSequenceOf = nullptr);
  virtual ~ASN1_SequenceOf();

  ASN1_Object* GetObjectAt(int pos) const;
  unsigned int GetSequenceOfSize() const;

  ASN1_Object* AppendNewObject();
  void DeleteObjectAt(int pos);
  void MoveUpObject(int pos);
  void MoveDownObject(int pos);

  ASN1_Object* GetDummyNewObject() const;
};

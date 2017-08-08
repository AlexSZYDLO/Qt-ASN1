/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Sequence.h"
#include "../Values/ASN1_ValueSequence.h"

using namespace Value;

ASN1_Sequence::ASN1_Sequence(ASN1_Object* valuesArray[],
                             unsigned int numberOfValues,
                             const char* name,
                             const ByteArray& tag,
                             bool optional,
                             bool explicitTag,
                             const ASN1_Sequence* defaultSequence,
                             bool extensibility) {
  ASN1_ValueSequence* defaultValue = static_cast<ASN1_ValueSequence*>(defaultSequence != nullptr ? defaultSequence->GetValue() : nullptr);

  typedef ASN1_Value* tpVal;
  tpVal* arr = new tpVal[numberOfValues];
  for (unsigned int i = 0; i < numberOfValues; i++)
    arr[i] = valuesArray[i]->GetValue();

  Value = new ASN1_ValueSequence(arr, numberOfValues, name, this, tag, optional, explicitTag, defaultValue, extensibility);
  delete[] arr;
}

ASN1_Sequence::~ASN1_Sequence() {}

bool ASN1_Sequence::IsExtensible() const { return static_cast<ASN1_ValueSequence*>(GetValue())->IsExtensible(); }

//void ASN1_Sequence::AppendExtensibilityObject(ASN1_Object* obj) {
//  static_cast<ASN1_ValueSequence*>(GetValue())->AppendExtensibilityObject((obj)->GetValue());
//}

ASN1_Object* ASN1_Sequence::GetObjectAt(unsigned int pos) const {
  return static_cast<ASN1_ValueSequence*>(GetValue())->GetObjectAt(pos)->GetGrammarObject();
}

ASN1_Object* ASN1_Sequence::GetExtensibilityObjectAt(unsigned int pos) const {
  return static_cast<ASN1_ValueSequence*>(GetValue())->GetExtensibilityObjectAt(pos)->GetGrammarObject();
}

unsigned int ASN1_Sequence::GetSize() const {
  return static_cast<ASN1_ValueSequence*>(GetValue())->GetSize();
}

unsigned int ASN1_Sequence::GetExtensibilitySize() const {
  return static_cast<ASN1_ValueSequence*>(GetValue())->GetExtensibilitySize();
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Set.h"
#include "../Values/ASN1_ValueSet.h"

using namespace Value;

ASN1_Set::ASN1_Set(ASN1_Object* valuesArray[],
                   unsigned int numberOfValues,
                   const char* name,
                   const ByteArray& tag,
                   bool optional,
                   bool explicitTag,
                   const ASN1_Set* defaultSet,
                   bool extensibility) {
  ASN1_ValueSet* defaultValue = static_cast<ASN1_ValueSet*>(defaultSet != nullptr ? defaultSet->GetValue() : nullptr);

  typedef ASN1_Value* tpVal;
  tpVal* arr = new tpVal[numberOfValues];
  for (unsigned int i = 0; i < numberOfValues; i++)
    arr[i] = valuesArray[i]->GetValue();

  Value = new ASN1_ValueSet(arr, numberOfValues, name, this, tag, optional, explicitTag, defaultValue, extensibility);
  delete[] arr;
}

ASN1_Set::~ASN1_Set() {}

bool ASN1_Set::IsExtensible() const { return static_cast<ASN1_ValueSet*>(GetValue())->IsExtensible(); }


//void ASN1_Set::AppendExtensibilityObject(ASN1_Object* obj) {
//  static_cast<ASN1_ValueSet*>(GetValue())->AppendExtensibilityObject((obj)->GetValue());
//}

ASN1_Object* ASN1_Set::GetObjectAt(unsigned int pos) const {
  return static_cast<ASN1_ValueSet*>(GetValue())->GetObjectAt(pos)->GetGrammarObject();
}

ASN1_Object* ASN1_Set::GetExtensibilityObjectAt(unsigned int pos) const {
  return static_cast<ASN1_ValueSet*>(GetValue())->GetExtensibilityObjectAt(pos)->GetGrammarObject();
}

unsigned int ASN1_Set::GetSize() const {
  return static_cast<ASN1_ValueSet*>(GetValue())->GetSize();
}

unsigned int ASN1_Set::GetExtensibilitySize() const {
  return static_cast<ASN1_ValueSet*>(GetValue())->GetExtensibilitySize();
}

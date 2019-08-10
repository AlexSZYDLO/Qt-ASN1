/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Choice.h"
#include "../Values/ASN1_ValueChoice.h"

using namespace Value;

ASN1_Choice::ASN1_Choice(callbackChoice choiceFromIdx,
                         unsigned int numberOfChoices,
                         const char* name,
                         const ByteArray& tag,
                         bool optional,
                         bool explicitTag,
                         const ASN1_Choice* defaultChoice) {
  ASN1_ValueChoice* defaultValue = static_cast<ASN1_ValueChoice*>(defaultChoice != nullptr ? defaultChoice->GetValue() : nullptr);
  Value = new ASN1_ValueChoice(choiceFromIdx, numberOfChoices, name, this, tag, optional, explicitTag, defaultValue);
}

ASN1_Choice::~ASN1_Choice() {}

unsigned int ASN1_Choice::AvailableChoices() const {
  return static_cast<ASN1_ValueChoice*>(GetValue())->GetNumberOfPossibleChoices();
}

const ASN1_Object* ASN1_Choice::GetChoiceFromIndex(unsigned int pos) const {
  const ASN1_Value* value = static_cast<ASN1_ValueChoice*>(GetValue())->GetDummyChoiceFromIndex(pos);
  return (value != nullptr) ? value->GetGrammarObject() : nullptr;
}

void ASN1_Choice::DeleteDummyChoiceList() const {
  static_cast<ASN1_ValueChoice*>(GetValue())->DeleteDummyChoiceList();
}

void ASN1_Choice::MakeDummyChoiceList() const {
  static_cast<ASN1_ValueChoice*>(GetValue())->MakeDummyChoiceList();
}

ASN1_Object*  ASN1_Choice::SetSelectedChoice(int idx) {
  ASN1_Value* val = static_cast<ASN1_ValueChoice*>(GetValue())->SetSelectedChoice(idx);
  return val != nullptr ? val->GetGrammarObject() : nullptr;
}

ASN1_Object* ASN1_Choice::GetSelectedChoice() const {
  const ASN1_Value* value = static_cast<ASN1_ValueChoice*>(GetValue())->GetSelectedChoice();
  return (value != nullptr) ? value->GetGrammarObject() : nullptr;
}


unsigned int ASN1_Choice::GetSelectedChoiceIndex() const {
  return static_cast<ASN1_ValueChoice*>(GetValue())->GetSelectedChoiceIndex();
}

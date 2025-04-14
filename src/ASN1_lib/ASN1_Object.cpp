/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Object.h"
#include "ASN1_Value.h"
#include "Exceptions.h"

using namespace Utils;
using namespace Value;

unsigned int ASN1_Object::static_ObjectCount = 0;
bool ASN1_Object::memoryCheck() { return ASN1_Object::static_ObjectCount == 0 && ASN1_Value::static_ObjectCount == 0; }

ASN1_Object::ASN1_Object() {} // std::cout << "ctor: ASN1_Object"<< " : " << ++static_ObjectCount << std::endl;

ASN1_Object::~ASN1_Object() {
  if(Value->GetDefaultValue() != nullptr) {
    delete Value->GetDefaultValue()->GetGrammarObject();
  }
  // std::cout << "dest: ASN1_Object " << GetName() << " : " << --static_ObjectCount << std::endl;
  delete Value;
}

ASN1_Value* ASN1_Object::GetValue() const {
  return Value;
}

const ASN1_Object* ASN1_Object::GetMyOwner() const {
  if(Value->GetMyOwner() != nullptr)
    return Value->GetMyOwner()->GetGrammarObject();
  else
    return nullptr;
}

const ASN1_Object* ASN1_Object::GetDefaultValue() const {
  if(Value->GetDefaultValue() != nullptr)
    return Value->GetDefaultValue()->GetGrammarObject();
  else
    return nullptr;
}

ByteArray ASN1_Object::GetDefaultTag() const {
  return Value->GetDefaultTag();
}

ByteArray ASN1_Object::GetTag() const {
  return Value->GetTag();
}

std::string ASN1_Object::GetName() const {
  return Value->GetName();
}

std::string ASN1_Object::GetDescription() const {
  return Value->GetDescription();
}

std::string ASN1_Object::StringExtract() const {
  return Value->StringExtractForBusinessAndValue();
}

std::string ASN1_Object::StringExtractForResearch() const {
  return GetValue()->StringExtractForReasearch();
}


eNodeType ASN1_Object::GetType() const {
  return Value->GetType();
}

unsigned int ASN1_Object::GetLastLength() const {
  return Value->GetLastLength();
}

bool ASN1_Object::IsMandatory() const {
  return Value->IsMandatory();
}

bool ASN1_Object::IsIgnored() const {
  return Value->IsIgnored();
}

bool ASN1_Object::IsExplicit() const {
  return Value->IsExplicit();
}

void ASN1_Object::SetDescription(const char* desc) {
  Value->SetDescription(desc);
}

void ASN1_Object::Ignore(bool ignore) {
  if(!Value->IsMandatory())
    Value->Ignore(ignore);
}

ByteArray ASN1_Object::GetHexBuffer() const {
  return Value->GetValue();
}

void ASN1_Object::ClearDynamicData() {
  GetValue()->ClearDynamicData();
}

void ASN1_Object::WriteIntoBuffer(ByteArray& buffer) const {
  buffer.Clear();
  Value->WriteIntoBuffer(buffer);
}

bool ASN1_Object::ReadFromBuffer(const ByteArray& buffer, char* error, size_t errorBufferSize) {
  try {
    unsigned int pos = 0;
    ClearDynamicData();
    Value->ReadFromBuffer(buffer, pos);
    return true;
  } catch(ParsingEx& e) {
    std::string what(e.what());
    if(what.size() < errorBufferSize)
      strncpy(error, what.c_str(), what.size());
    else
      strncpy(error, what.c_str(), errorBufferSize - 1);
    return false;
  }
}

bool ASN1_Object::Compare(const ASN1_Object& secondTree, unsigned int& nbDiffs, char* error, size_t errorBufferSize) const {
  std::string err;
  if(Value->CompareTree(secondTree.GetValue(), nbDiffs, err)) {
    if(err.size() < errorBufferSize)
      strncpy(error, err.c_str(), err.size());
    else
      strncpy(error, err.c_str(), errorBufferSize - 1);
    return true;
  }
  return false;
}

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
bool ASN1_Object::memoryCheck()
{
  return ASN1_Object::static_ObjectCount == 0 && ASN1_Value::static_ObjectCount == 0;
}

ASN1_Object::ASN1_Object(const char *objectName)
{
  if (ASN1_DEBUG_MEMORY)
    std::cout << "ctor: ASN1_Object " << objectName << " : " << ++static_ObjectCount << std::endl;
}

ASN1_Object::~ASN1_Object()
{
  if (Value->GetDefaultValue() != nullptr)
  {
    delete Value->GetDefaultValue()->GetGrammarObject();
  }
  if (ASN1_DEBUG_MEMORY)
    std::cout << "dest: ASN1_Object " << GetName() << " : " << --static_ObjectCount << std::endl;
  delete Value;
}

ASN1_Value *ASN1_Object::GetPrivateObject() const
{
  return Value;
}

const ASN1_Object *ASN1_Object::GetMyOwner() const
{
  if (Value->GetMyOwner() != nullptr)
    return Value->GetMyOwner()->GetGrammarObject();
  else
    return nullptr;
}

const ASN1_Object *ASN1_Object::GetDefaultValue() const
{
  if (Value->GetDefaultValue() != nullptr)
    return Value->GetDefaultValue()->GetGrammarObject();
  else
    return nullptr;
}

ByteArray ASN1_Object::GetDefaultTag() const
{
  return Value->GetDefaultTag();
}

ByteArray ASN1_Object::GetTag() const
{
  return Value->GetTag();
}

std::string ASN1_Object::GetName() const
{
  return Value->GetName();
}

std::string ASN1_Object::GetDescription() const
{
  return Value->GetDescription();
}

std::string ASN1_Object::StringExtract() const
{
  return Value->StringExtractForBusinessAndValue();
}

std::string ASN1_Object::StringExtractForResearch() const
{
  return GetPrivateObject()->StringExtractForReasearch();
}

eNodeType ASN1_Object::GetType() const
{
  return Value->GetType();
}

unsigned int ASN1_Object::GetLastLength() const
{
  return Value->GetLastLength();
}

bool ASN1_Object::IsMandatory() const
{
  return Value->IsMandatory();
}

bool ASN1_Object::IsIgnored() const
{
  return Value->IsIgnored();
}

bool ASN1_Object::IsExplicit() const
{
  return Value->IsExplicit();
}

void ASN1_Object::SetDescription(const char *desc)
{
  Value->SetDescription(desc);
}

void ASN1_Object::Ignore(bool ignore)
{
  if (!Value->IsMandatory())
    Value->Ignore(ignore);
}

ByteArray ASN1_Object::GetHexBuffer() const
{
  return Value->GetValue();
}

void ASN1_Object::ClearDynamicData()
{
  GetPrivateObject()->ClearDynamicData();
}

void ASN1_Object::WriteIntoBuffer(ByteArray &buffer) const
{
  buffer.Clear();
  Value->WriteIntoBuffer(buffer);
}

bool ASN1_Object::ReadFromBuffer(const ByteArray &buffer, std::string &error)
{
  try
  {
    unsigned int pos = 0;
    ClearDynamicData();
    Value->ReadFromBuffer(buffer, pos);
    return true;
  }
  catch (ParsingEx &e)
  {
    error = e.what();
    return false;
  }
}

bool ASN1_Object::Compare(const ASN1_Object &secondTree, unsigned int &nbDiffs, std::string &diffReport) const
{
  return Value->CompareTree(secondTree.GetPrivateObject(), nbDiffs, diffReport);
}

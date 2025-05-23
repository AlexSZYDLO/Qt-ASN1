/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_SequenceOf.h"
#include "../Values/ASN1_ValueSequenceOf.h"

using namespace Value;

ASN1_SequenceOf::ASN1_SequenceOf(callbackSequenceOf newSeqOfObject,
                                 const char *name,
                                 const ByteArray &tag,
                                 bool optional,
                                 bool explicitTag,
                                 const ASN1_SequenceOf *defaultSequenceOf)
    : ASN1_Object(name)
{
  ASN1_ValueSequenceOf *defaultValue = static_cast<ASN1_ValueSequenceOf *>(
      defaultSequenceOf != nullptr ? defaultSequenceOf->GetPrivateObject() : nullptr);
  Value = new ASN1_ValueSequenceOf(newSeqOfObject, name, this, tag, optional, explicitTag, defaultValue);
}
ASN1_SequenceOf::~ASN1_SequenceOf()
{
}

ASN1_Object *ASN1_SequenceOf::GetObjectAt(unsigned int pos) const
{
  return static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->GetObjectAt(pos)->GetGrammarObject();
}

unsigned int ASN1_SequenceOf::GetSequenceOfSize() const
{
  return static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->GetSize();
}

ASN1_Object *ASN1_SequenceOf::AppendNewObject()
{
  return static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->AppendNewObject()->GetGrammarObject();
}

void ASN1_SequenceOf::DeleteObjectAt(unsigned int pos)
{
  static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->DeleteObjectAt(pos);
}

void ASN1_SequenceOf::MoveUpObject(unsigned int pos)
{
  static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->MoveUpObject(pos);
}

void ASN1_SequenceOf::MoveDownObject(unsigned int pos)
{
  static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->MoveDownObject(pos);
}

ASN1_Object *ASN1_SequenceOf::GetDummyNewObject() const
{
  return static_cast<ASN1_ValueSequenceOf *>(GetPrivateObject())->GetDummyNewObject()->GetGrammarObject();
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Value.h"
#include "../Objects/ASN1_SequenceOf.h"

namespace Value {
  class ASN1_ValueSequenceOf : public ASN1_Value {
   protected:
    std::vector<ASN1_Value*> m_Objects;

    ASN1_SequenceOf::callbackSequenceOf m_Callback;

   public:
    ASN1_ValueSequenceOf(ASN1_SequenceOf::callbackSequenceOf newSeqOfObject,
                         const std::string& name,
                         ASN1_SequenceOf* grammarObject,
                         const ByteArray& tag,
                         bool optional,
                         bool explicitTag,
                         const ASN1_ValueSequenceOf* defaultValue);
    virtual ~ASN1_ValueSequenceOf() override;
    virtual void SetHexValue(const ByteArray& rawValue, std::string& error) override;
    virtual void ClearDynamicData() override;

    virtual Utils::eNodeType GetType() const override;

    const ASN1_Value* GetObjectAt(unsigned int pos) const;
    unsigned int GetSize() const;

    ASN1_Value* AppendNewObject();
    void DeleteObjectAt(unsigned int pos);
    void MoveUpObject(unsigned int pos);
    void MoveDownObject(unsigned int pos);

    ASN1_Value* GetDummyNewObject();

    virtual void GetContentValue(ByteArray& buffer) const override;
    virtual void ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) override;

    virtual bool CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const override;
  };
}

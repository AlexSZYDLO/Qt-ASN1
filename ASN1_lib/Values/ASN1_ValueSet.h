/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Value.h"

namespace Value {
  class ASN1_ValueSet : public ASN1_Value {
   protected:
    const bool m_Extensibility;

    std::vector<ASN1_Value*> m_Objects;
    std::vector<ASN1_Value*> m_ExtensibilityObjects;

   public:
    ASN1_ValueSet(ASN1_Value* values[],
                  unsigned int numberOfValues,
                  const std::string& name,
                  ASN1_Object* grammarObject,
                  const ByteArray& tag,
                  bool optional,
                  bool explicitTag,
                  const ASN1_ValueSet* defaultValue,
                  bool extensibility);
    virtual ~ASN1_ValueSet() override;
    virtual void SetHexValue(const ByteArray& rawValue, std::string& error) override;
    virtual void ClearDynamicData() override;

    virtual Utils::eNodeType GetType() const override;
    bool IsExtensible() const;

    const ASN1_Value* GetObjectAt(unsigned int pos) const;
    unsigned int GetSize() const;

    //extensibility
    void AppendExtensibilityObject(ASN1_Value* obj);
    const ASN1_Value* GetExtensibilityObjectAt(unsigned int pos) const;
    unsigned int GetExtensibilitySize() const;

    virtual void GetContentValue(ByteArray& buffer) const override;
    virtual void ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) override;

    virtual bool CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const override;
  };
}

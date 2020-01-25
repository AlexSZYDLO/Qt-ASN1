/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Value.h"
#include "../Objects/ASN1_Choice.h"

namespace Value {
  class ASN1_ValueChoice : public ASN1_Value {
   protected:
    ASN1_Value* m_TheChoice;
    unsigned int m_TheChoiceIndex;
    std::vector<ASN1_Value*> m_AvailableChoices;

    ASN1_Choice::callbackChoice m_Callback;
    unsigned int m_NumberOfChoices;

    bool IsTagAvailableInChoices(ByteArray m_Tag);

   public:
    ASN1_ValueChoice(ASN1_Choice::callbackChoice choiceFromIdx,
                     unsigned int numberOfChoices,
                     const std::string& name,
                     ASN1_Object* grammarObject,
                     const ByteArray& tag,
                     bool optional,
                     bool explicitTag,
                     const ASN1_ValueChoice* defaultValue);
    ~ASN1_ValueChoice() override;
    virtual void SetHexValue(const ByteArray& rawValue, std::string& error) override;
    virtual void ClearDynamicData() override;

    virtual Utils::eNodeType GetType() const override;

    ASN1_Value* GetSelectedChoice() const;
    unsigned int GetSelectedChoiceIndex() const;
    ASN1_Value* SetSelectedChoice(unsigned int idx);

    // functions to access available choices
    unsigned int GetNumberOfPossibleChoices();
    const ASN1_Value* GetDummyChoiceFromIndex(unsigned int idx);

    void MakeDummyChoiceList();
    void DeleteDummyChoiceList();

    //encoding
    virtual void GetContentValue(ByteArray& buffer) const override;
    virtual void ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) override;
    virtual bool CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const override;
  };
}

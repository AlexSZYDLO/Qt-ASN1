/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ByteArray.h"
#include "Exceptions.h"
#include "Utils.h"

/*
This class is not exposed in the DLL. It contains all the technical "information" about the node.
It is the base class of each ASN1 type. The child class implements the encoding of the node.
*/

class ASN1_Object;
//enum Utils::eNodeType : int; // dont remember why it used that...

namespace Value {
  class ASN1_Value {
   public:
    static unsigned int static_ObjectCount;

   protected:
    ByteArray m_Value;

    const std::string m_Name;
    std::string m_Description;
    bool m_IgnoredByUser;

    ASN1_Object* const m_GrammarObject;
    const ASN1_Value* const m_DefaultValue;
    const ASN1_Value* m_ParentValue;
    const ByteArray m_Tag;
    const ByteArray m_DefaultTag;
    const bool m_Optional;
    const bool m_Explicit;

    mutable unsigned int m_TmpLength;

   protected:
    ASN1_Value(const std::string& name,
               ASN1_Object* grammarObject,
               const ByteArray& tag,
               const ByteArray& defaultTag,
               bool optional,
               bool explicitTag,
               const ASN1_Value* defaultValue);

   public:
    virtual ~ASN1_Value() = 0;
    virtual void ClearDynamicData();

    virtual Utils::eNodeType GetType() const = 0;
    bool IsComplexNode() const;

    ASN1_Object* GetGrammarObject() const;
    std::string GetName() const;
    std::string GetDescription() const;
    const ByteArray GetValue() const;
    const ByteArray GetTag() const;
    const ByteArray GetDefaultTag() const;
    const ASN1_Value* GetMyOwner() const;
    const ASN1_Value* GetDefaultValue() const;
    unsigned int GetLastLength() const;
    bool IsMandatory() const;
    bool IsExplicit() const;

    bool HasDefaultValue() const;
    bool IsIgnored() const;

    void SetDescription(const std::string& desc);
    void SetParentValue(const ASN1_Value* newOwner);
    void Ignore(bool ignore);
    virtual void SetHexValue(const ByteArray& rawValue, std::string& error) = 0;

    bool ReadNextTags(const ByteArray& buffer, unsigned int& pos, ByteArray& implTag, ByteArray& explTag) const;
    bool CheckTags(const ByteArray& implTag, const ByteArray& explTag, bool throwException, unsigned int pos) const;
    void AppendTagAndLength(ByteArray& toBuffer) const;
    virtual void GetContentValue(ByteArray& inBuffer) const;

    void WriteIntoBuffer(ByteArray& inBuffer) const;
    virtual void ReadFromBuffer(const ByteArray& fromBuffer, unsigned int& fromPos);
    virtual bool CompareTree(const ASN1_Value* secondTree, unsigned int& nbDiff, std::string& errorReport) const;

    std::string GetValueExtract() const;
    std::string StringExtractForReasearch() const;
    std::string StringExtractForLowLevel() const;
    std::string StringExtractForBusinessLevel() const;
    std::string StringExtractForBusinessAndValue() const;
  };
} // namespace Value

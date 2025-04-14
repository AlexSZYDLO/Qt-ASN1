/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Value.h"
#include <sstream>
#include <stdexcept>
#include "ASN1_Object.h"
#include "Values/ASN1_ValueChoice.h"
#include "Values/ASN1_ValueSequenceOf.h"

using namespace Utils;

namespace Value {
  unsigned int ASN1_Value::static_ObjectCount = 0;

  ASN1_Value::ASN1_Value(const std::string& name,
                         ASN1_Object* grammarObject,
                         const ByteArray& tag,
                         const ByteArray& defaultTag,
                         bool optional,
                         bool explicitTag,
                         const ASN1_Value* defaultValue) : m_Value(""),
                                                           m_Name(name),
                                                           m_Description(""),
                                                           m_IgnoredByUser(false),
                                                           m_GrammarObject(grammarObject),
                                                           m_DefaultValue(defaultValue),
                                                           m_ParentValue(nullptr),
                                                           m_Tag(tag),
                                                           m_DefaultTag(defaultTag),
                                                           m_Optional(optional),
                                                           m_Explicit(explicitTag) {
    /*std::cout << "ctor: ASN1_Value " << GetName() << " : " << ++static_ObjectCount << std::endl;*/
  }

  ASN1_Value::~ASN1_Value() { /*std::cout << "dest: ASN1_Value " << GetName() << " : " << --static_ObjectCount << std::endl;*/
  }

  void ASN1_Value::ClearDynamicData() {}

  bool ASN1_Value::IsComplexNode() const {
    return IsComplexType(GetType());
  }

  ASN1_Object* ASN1_Value::GetGrammarObject() const { return m_GrammarObject; }
  const ASN1_Value* ASN1_Value::GetMyOwner() const { return m_ParentValue; }
  const ASN1_Value* ASN1_Value::GetDefaultValue() const { return m_DefaultValue; }
  const ByteArray ASN1_Value::GetTag() const { return m_Tag; }
  const ByteArray ASN1_Value::GetDefaultTag() const { return m_DefaultTag; }
  std::string ASN1_Value::GetName() const { return m_Name; }
  std::string ASN1_Value::GetDescription() const { return m_Description; }
  unsigned int ASN1_Value::GetLastLength() const { return m_TmpLength; }
  bool ASN1_Value::HasDefaultValue() const { return m_DefaultValue != nullptr; }
  bool ASN1_Value::IsMandatory() const { return !m_Optional; }
  bool ASN1_Value::IsExplicit() const { return m_Explicit; }

  const ByteArray ASN1_Value::GetValue() const { return m_Value; }
  bool ASN1_Value::IsIgnored() const { return m_IgnoredByUser; }

  void ASN1_Value::SetDescription(const std::string& desc) {
    m_Description = desc;
  }

  void ASN1_Value::SetParentValue(const ASN1_Value* parent) {
    m_ParentValue = parent;
  }

  void ASN1_Value::Ignore(bool Ignore) {
    if(!IsMandatory() || (HasDefaultValue() && Ignore))
      m_IgnoredByUser = Ignore;
#ifdef DEBUG
    else
      throw ValueEx("Trying to ignore a mandatory variable ! " + GetName() + " - " + GetDescription());
#endif
  }

  // -------------- encoding ---------------------

  bool ASN1_Value::ReadNextTags(const ByteArray& buffer, unsigned int& pos, ByteArray& ImplTag, ByteArray& ExplTag) const {
    try {
      unsigned int dummyL;
      if(!GetTagFromBuffer(buffer, pos, ImplTag))
        throw ParsingEx("Cannot get first tag from buffer. No data to read.", this->GetGrammarObject(), pos);
      if(IsExplicit() && m_Tag != "" && m_DefaultTag != "") {
        if(!GetLengthFromBuffer(buffer, pos, dummyL))
          throw ParsingEx("Cannot read length between implicit and explicit tag. No data to read.", this->GetGrammarObject(), pos);
        if(!GetTagFromBuffer(buffer, pos, ExplTag))
          throw ParsingEx("Cannot get second tag from buffer. No data to read.", this->GetGrammarObject(), pos);
      }
    } catch(ParsingEx& e) {
      if(IsMandatory() && !HasDefaultValue()) { // buffer empty but value is optional (it will be handled later)
        e.AddError("Cannot read object tag: " + GetName());
        throw e;
      }
    }
    return true;
  }

  bool ASN1_Value::CheckTags(const ByteArray& ImplTag, const ByteArray& ExplTag, bool throwEx, unsigned int pos) const {
    // the check does not necessarily need to raise an error, it depends on when it is called

    if(m_Tag != "") {
      if(m_Tag != ImplTag) {
        if(throwEx)
          throw ParsingEx("First tag check failed: read " + std::string(ImplTag.GetString()) + ", expecting " + std::string(m_Tag.GetString()), this->GetGrammarObject(), pos);
        return false;
      }
    } else if(m_DefaultTag != "") {
      if(m_DefaultTag != ImplTag) {
        if(throwEx)
          throw ParsingEx("First tag check failed: read " + std::string(ImplTag.GetString()) + ", expecting " + std::string(m_DefaultTag.GetString()), this->GetGrammarObject(), pos);
        return false;
      }
      return true;
    }
    if(IsExplicit()) {
      if(m_DefaultTag != "" && m_DefaultTag != ExplTag) {
        if(throwEx)
          throw ParsingEx("Second tag check failed: read " + std::string(ImplTag.GetString()) + ", expecting " + std::string(m_DefaultTag.GetString()), this->GetGrammarObject(), pos);
        return false;
      }
    }
    return true;
  }

  void ASN1_Value::GetContentValue(ByteArray& buffer) const {
    buffer = GetValue();
  }

  void ASN1_Value::AppendTagAndLength(ByteArray& buffer) const {
    if(IsExplicit()) {
      // default tag empty for choices: use only associated tag in explicit case
      if(m_DefaultTag != "") {
        buffer.InsertAt(MakeLength(buffer.Size()));
        buffer.InsertAt(m_DefaultTag);
      }
      if(m_Tag != "") {
        buffer.InsertAt(MakeLength(buffer.Size()));
        buffer.InsertAt(m_Tag);
      }
    } else {
      // use tag, except if not set. In case of a choice with no tag and no default tag, set nothing
      if(m_Tag != "") {
        buffer.InsertAt(MakeLength(buffer.Size()));
        buffer.InsertAt(m_Tag);
      } else if(m_DefaultTag != "") {
        buffer.InsertAt(MakeLength(buffer.Size()));
        buffer.InsertAt(m_DefaultTag);
      }
    }
  }

  void ASN1_Value::WriteIntoBuffer(ByteArray& buffer) const {
    if(IsMandatory() || (!IsMandatory() && !IsIgnored())) {
      ByteArray thisBuffer;

      GetContentValue(thisBuffer);
      m_TmpLength = thisBuffer.Size();

      AppendTagAndLength(thisBuffer);
      buffer.Append(thisBuffer);
    }
  }

  void ASN1_Value::ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) {
    ByteArray ImplTag, ExplTag;

    unsigned int oldPos = pos;

    ReadNextTags(buffer, pos, ImplTag, ExplTag);

    if(CheckTags(ImplTag, ExplTag, false, 0)) {
      unsigned int L;
      unsigned int oldPosL = pos;
      if(!GetLengthFromBuffer(buffer, pos, L))
        throw ParsingEx("Cannot read length of object: " + GetName(), this->GetGrammarObject(), oldPosL);

      ByteArray V;
      buffer.GetBytesAtRank(pos, L, V);
      pos += L;
      try {
        std::string error;
        SetHexValue(V, error);
        if(!error.empty())
          throw ParsingEx(error, this->GetGrammarObject(), pos);

        if(IsIgnored())
          Ignore(false); // if the node was marked as ignored, enable it
      } catch(ParsingEx& e) {
        e.AddError("Illegal value in object: " + GetName());
        throw e;
      }
    } else {
      if(IsMandatory() && !HasDefaultValue()) {
        try {
          CheckTags(ImplTag, ExplTag, true, oldPos);
        } // send oldPos because tag is already read, but if the check fails we want the initial position
        catch(ParsingEx& e) {
          e.AddError("Tag checking failed for object, or object missing: " + GetName());
          throw e;
        }
      } else {
        Ignore(true); // parameter is not present but optional->OK
        pos = oldPos; // reset position to beginning of last object
      }
    }
  }

  bool ASN1_Value::CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const {
    // We assume the grammar is correct : no need to check the tag, if the variable is optional, if it is implicit, and the default value
    // if a grammar issue occurs, we return false
    if(GetType() == SecondTree->GetType()) {
      if(!IsMandatory())
        if(IsIgnored() != SecondTree->IsIgnored()) {
          errorReport.append("Node: " + GetName() + " - Ignored by user check failed.\n");
          errorReport.append("Tree Node: " + std::to_string(IsIgnored()) + " - Compared Node: " + std::to_string(SecondTree->IsIgnored()) + "\n\n");
          NbDiff++;
        }

      // Don't check value for complex nodes (comparing simple nodes is enough)
      if(!IsComplexNode()) {
        const ByteArray& SecondValue = SecondTree->GetValue();
        if(m_Value != SecondValue) {
          errorReport.append("Node: " + GetName() + " - Value check failed.\n");
          errorReport.append("Tree Node: " + std::string(m_Value.GetString()) + "\n");
          errorReport.append("Compared Node: " + std::string(SecondValue.GetString()) + "\n\n");
          NbDiff++;
        }
      }
      return true;
    }
    errorReport.append("Grammar incompatibility: not same kind of node - COMPARISON ABORTED.\n\n");
    return false;
  }

  // ------------------ String extract --------------------

  std::string ASN1_Value::GetValueExtract() const {
    const int cMaxLengthValue = 64;
    std::stringstream s;

    unsigned int ValueSize = m_Value.Size();
    if(ValueSize > 0) {
      s << "L=" << ValueSize << " Value=0x";

      if(ValueSize <= cMaxLengthValue)
        s << std::string(m_Value.GetString());
      else
        s << std::string(m_Value.GetString()).substr(0, cMaxLengthValue) << "...";
    }
    return s.str();
  }

  std::string ASN1_Value::StringExtractForReasearch() const {
    std::stringstream s;

    // NOT DISPLAYED - just fill the information the user might look for
    if(IsIgnored())
      s << "[IGNORED]";

    if(m_Tag.Size() > 0)
      s << "[Tag" << m_Tag.GetString() << "]";

    if(m_DefaultTag.Size() > 0)
      s << "[Default Tag" << m_DefaultTag.GetString() << "]";

    if(NodeTypeToString(GetType()) != "")
      s << "[" << NodeTypeToString(GetType()) << "]";

    if(m_Description != "")
      s << "[" << m_Name << " " << m_Description << "]";
    else
      s << "[" << m_Name << "]";

    s << std::string(IsMandatory() ? " [Mandatory, " : " [Optional, ");
    if(HasDefaultValue())
      s << "Use Default, ";
    s << std::string(IsExplicit() ? "Explicit]" : "Implicit]");

    return s.str();
  }

  std::string ASN1_Value::StringExtractForLowLevel() const {
    std::stringstream s;

    if(IsIgnored())
      s << "[IGNORED] ";

    if(m_Tag.Size() > 0)
      s << "[ Tag " << m_Tag.GetString() << " ]";

    if(NodeTypeToString(GetType()) != "")
      s << " [ " << NodeTypeToString(GetType()) << " ]";

    if(m_Description != "")
      s << " [ " << m_Name << " - " << m_Description << " ]";
    else
      s << " [ " << m_Name << " ]";

    if(GetType() == cChoice) {
      const ASN1_ValueChoice* ChoiceValue = static_cast<const ASN1_ValueChoice*>(this);
      if(ChoiceValue->GetSelectedChoice() != nullptr) {
        std::string choiceValueName;
        if(ChoiceValue->GetSelectedChoice()->GetName() != "")
          choiceValueName = "[ " + ChoiceValue->GetSelectedChoice()->GetName() + " ]";
        else
          choiceValueName = "[ " + ChoiceValue->GetSelectedChoice()->StringExtractForLowLevel() + " ]";
        s << " [ "
          << "Chosen value:"
          << " Tag " << ChoiceValue->GetSelectedChoice()->GetTag().GetString() << " - "
          << "Name " << choiceValueName << " ]";
      }
    } else if(GetType() == cSequenceOf) {
      const ASN1_ValueSequenceOf* SeqOfValue = static_cast<const ASN1_ValueSequenceOf*>(this);
      s << " [ " << SeqOfValue->GetSize() << " Object(s)"
        << " ]";
    }

    s << std::string(IsMandatory() ? " [Mandatory, " : " [Optional, ");
    if(HasDefaultValue())
      s << "Use Default, ";
    s << std::string(IsExplicit() ? "Explicit]" : "Implicit]");

    std::string value = GetValueExtract();
    if(value != "")
      s << "  (" << value << ")";

    return s.str();
  }

  std::string ASN1_Value::StringExtractForBusinessLevel() const {
    std::stringstream s;

    if(IsIgnored())
      s << "[IGNORED] ";

    if(m_Description != "")
      s << " " << m_Name << " - " << m_Description;
    else
      s << " " << m_Name;

    if(m_Tag.Size() > 0)
      s << "  [Tag " << m_Tag.GetString() << "]";

    s << std::string(IsMandatory() ? "" : " (Optional) ");

    if(GetType() == cChoice) {
      const ASN1_ValueChoice* ChoiceValue = static_cast<const ASN1_ValueChoice*>(this);
      if(ChoiceValue->GetSelectedChoice() != nullptr) {
        std::string choiceValueName;
        choiceValueName = ChoiceValue->GetSelectedChoice()->GetName();
        s << " [ "
          << "Chosen value: " << choiceValueName << " [Tag " << ChoiceValue->GetSelectedChoice()->GetTag().GetString() << "]"
          << " ] ";
      }
    }
    return s.str();
  }

  std::string ASN1_Value::StringExtractForBusinessAndValue() const {
    std::stringstream s;

    s << StringExtractForBusinessLevel();
    if(!IsComplexNode()) {
      // dont show value for complex nodes
      std::string value = GetValueExtract();
      if(value != "")
        s << " (" << value << ')';
    }
    return s.str();
  }
} // namespace Value

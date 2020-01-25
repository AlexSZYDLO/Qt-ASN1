/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_ValueSequenceOf.h"

using namespace Utils;

namespace Value {
  ASN1_ValueSequenceOf::ASN1_ValueSequenceOf(ASN1_SequenceOf::callbackSequenceOf newSeqOfObject,
      const std::string& name,
      ASN1_SequenceOf* grammarObject,
      const ByteArray& tag,
      bool optional,
      bool explicitTag,
      const ASN1_ValueSequenceOf* defaultValue)
    : ASN1_Value(name, grammarObject, tag, "30", optional, explicitTag, defaultValue),
      m_Callback(newSeqOfObject) {}

  ASN1_ValueSequenceOf::~ASN1_ValueSequenceOf() {
    for (unsigned int i = 0; i < m_Objects.size(); i++)
      delete m_Objects.at(i)->GetGrammarObject();
  }

  void ASN1_ValueSequenceOf::SetHexValue(const ByteArray&, std::string&) {}

  void ASN1_ValueSequenceOf::ClearDynamicData() {
    for (unsigned int i = 0; i < m_Objects.size(); i++)
      delete m_Objects.at(i)->GetGrammarObject();
    m_Objects.clear();
  }

  eNodeType ASN1_ValueSequenceOf::GetType() const {
    return cSequenceOf;
  }

  unsigned int ASN1_ValueSequenceOf::GetSize() const {
    return static_cast<unsigned int>(m_Objects.size());
  }

  const ASN1_Value* ASN1_ValueSequenceOf::GetObjectAt(unsigned int pos) const {
    if (GetSize() > pos)
      return m_Objects.at(pos);
    else return nullptr;
  }

  ASN1_Value* ASN1_ValueSequenceOf::AppendNewObject() {
    ASN1_Value* newObj = GetDummyNewObject();
    if (newObj != nullptr) {
      m_Objects.push_back(newObj);
      newObj->SetParentValue(this);
    }
    return newObj;
  }

  void ASN1_ValueSequenceOf::DeleteObjectAt(unsigned int pos) {
    ASN1_Object* toDelete = m_Objects.at(pos)->GetGrammarObject();
    m_Objects.erase(m_Objects.begin() + pos);
    delete toDelete;
  }

  void ASN1_ValueSequenceOf::MoveUpObject(unsigned int pos) {
    if (pos > 0 && pos < GetSize()) {
      ASN1_Value* temp = m_Objects.at(pos);
      m_Objects.erase(m_Objects.begin() + pos);
      m_Objects.insert(m_Objects.begin() + pos - 1, temp);
    }
  }

  void ASN1_ValueSequenceOf::MoveDownObject(unsigned int pos) {
    if (pos < GetSize() - 1) {
      ASN1_Value* temp = m_Objects.at(pos);
      m_Objects.erase(m_Objects.begin() + pos);
      m_Objects.insert(m_Objects.begin() + pos + 1, temp);
    }
  }

  ASN1_Value* ASN1_ValueSequenceOf::GetDummyNewObject() {
    ASN1_Object* obj = m_Callback.f(m_Callback.context);
    if (obj != nullptr) {
      ASN1_Value* val = obj->GetValue();
      val->SetParentValue(this);
      return val;
    }
    return nullptr;
  }

  void ASN1_ValueSequenceOf::GetContentValue(ByteArray& buffer) const {
    for (size_t i = 0; i < m_Objects.size(); i++)
      m_Objects.at(i)->WriteIntoBuffer(buffer);
  }

  void ASN1_ValueSequenceOf::ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) {
    ByteArray ImplTag, ExplTag;

    unsigned int oldPos = pos;

    ReadNextTags(buffer, pos, ImplTag, ExplTag);

    if (CheckTags(ImplTag, ExplTag, false, 0)) {
      if (IsIgnored())
        Ignore(false); // if the node was marked as ignored, enable it

      unsigned int L;
      if (!GetLengthFromBuffer(buffer, pos, L))
        throw ParsingEx("Cannot read length of object: " + GetName(), this->GetGrammarObject(), pos);

      unsigned int dataFieldPos = pos; unsigned int nb = 0;
      while (pos < dataFieldPos + L) {
        nb++;
        ASN1_Object* newGrammarObj = AppendNewObject()->GetGrammarObject();
        if (newGrammarObj != nullptr) {
          ASN1_Value* newObj = newGrammarObj->GetValue();
          try { newObj->ReadFromBuffer(buffer, pos); }
          catch (ParsingEx& e) {
            e.AddError("Cannot read object at position " + std::to_string(nb) + " - " + GetName());
            throw e;
          }
        }
      }
    }
    else {
      if (IsMandatory() && !HasDefaultValue()) {
        try { CheckTags(ImplTag, ExplTag, true, oldPos); }
        catch (ParsingEx& e) {
          e.AddError("Tag checking failed for object: " + GetName());
          throw e;
        }
      }
      else {
        Ignore(true); // parameter is not present but optional->OK
        pos = oldPos;
      }
    }
  }

  bool ASN1_ValueSequenceOf::CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const {
    if (SecondTree->GetType() != Utils::cSequenceOf) {
      errorReport.append("Grammar incompatibility: not same kind of node - COMPARISON ABORTED.\n\n");
      return false;
    }

    // We assume the grammar is correct : no need to check the tag, if the variable is optional, if it is implicit, and the default value
    const ASN1_ValueSequenceOf* SecondTreeAsSeqOf = static_cast<const ASN1_ValueSequenceOf*>(SecondTree);

    // Check the sequence node first
    bool result = ASN1_Value::CompareTree(SecondTree, NbDiff, errorReport);
    if (result) {
      if (!IsIgnored()) {
        if (m_Objects.size() != SecondTreeAsSeqOf->GetSize()) {
          errorReport.append("Node: " + GetName() + " - Object count check failed.\n\n");
          errorReport.append("Tree Node: " + std::to_string(GetSize()) + " - Compared Node: " + std::to_string(SecondTreeAsSeqOf->GetSize()) + "\n\n");
          NbDiff++;
        }
        for (unsigned int i = 0; i < GetSize(); i++) {
          if (SecondTreeAsSeqOf->GetSize() - 1 >= i) {
            unsigned int oldNbDiff = NbDiff;
            result = GetObjectAt(i)->CompareTree(SecondTreeAsSeqOf->GetObjectAt(i), NbDiff, errorReport);
            if (oldNbDiff != NbDiff) {
              errorReport.append("Node: " + GetName() + " - Object comparison failed at index " + std::to_string(i) + ".\n\n");
              NbDiff++;
            }
            if (!result)
              break;
          }
        }
      }
    }
    return result;
  }
}

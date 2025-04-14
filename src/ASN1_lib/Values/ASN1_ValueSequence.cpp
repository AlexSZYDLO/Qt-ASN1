/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_ValueSequence.h"
#include "../ASN1_Object.h"
#include "../Objects/ASN1_Object_Nodes.h"

using namespace Utils;

namespace Value {
  ASN1_ValueSequence::ASN1_ValueSequence(ASN1_Value* values[],
                                         unsigned int numberOfValues,
                                         const std::string& name,
                                         ASN1_Object* grammarObject,
                                         const ByteArray& tag,
                                         bool optional,
                                         bool explicitTag,
                                         const ASN1_ValueSequence* defaultValue,
                                         bool extensibility)
    : ASN1_Value(name, grammarObject, tag, "30", optional, explicitTag, defaultValue),
      m_Extensible(extensibility) {
    for (unsigned int i = 0; i < numberOfValues; i++) {
      m_Objects.push_back(values[i]);
      values[i]->SetParentValue(this);
    }
  }

  ASN1_ValueSequence::~ASN1_ValueSequence() {
    for (unsigned int i = 0; i < m_Objects.size(); i++)
      delete m_Objects.at(i)->GetGrammarObject();
    for (unsigned int i = 0; i < m_ExtensibilityObjects.size(); i++)
      delete m_ExtensibilityObjects.at(i)->GetGrammarObject();
  }

  void ASN1_ValueSequence::SetHexValue(const ByteArray&, std::string&) {}

  void ASN1_ValueSequence::ClearDynamicData() {
    for (unsigned int i = 0; i < m_Objects.size(); i++)
      m_Objects.at(i)->ClearDynamicData();
    for (unsigned int i = 0; i < m_ExtensibilityObjects.size(); i++)
      delete m_ExtensibilityObjects.at(i)->GetGrammarObject();
    m_ExtensibilityObjects.clear();
  }

  eNodeType ASN1_ValueSequence::GetType() const {
    return Utils::cSequence;
  }

  bool ASN1_ValueSequence::IsExtensible() const {
    return m_Extensible;
  }

  unsigned int ASN1_ValueSequence::GetSize() const {
    return static_cast<unsigned int>(m_Objects.size());
  }

  const ASN1_Value* ASN1_ValueSequence::GetObjectAt(unsigned int pos) const {
    if (GetSize() > pos)
      return m_Objects.at(pos);
    else return nullptr;
  }

  void ASN1_ValueSequence::AppendExtensibilityObject(ASN1_Value* obj) {
    if (IsExtensible()) {
      m_ExtensibilityObjects.push_back(obj);
      obj->SetParentValue(this);
    }
  }

  unsigned int ASN1_ValueSequence::GetExtensibilitySize() const {
    return static_cast<unsigned int>(m_ExtensibilityObjects.size());
  }

  const ASN1_Value* ASN1_ValueSequence::GetExtensibilityObjectAt(unsigned int pos) const {
    if (GetExtensibilitySize() > pos)
      return m_ExtensibilityObjects.at(pos);
    else return nullptr;
  }


  void ASN1_ValueSequence::GetContentValue(ByteArray& buffer) const {
    for (size_t i = 0; i < m_Objects.size(); i++)
      m_Objects.at(i)->WriteIntoBuffer(buffer);
    for (size_t i = 0; i < m_ExtensibilityObjects.size(); i++)
      m_ExtensibilityObjects.at(i)->WriteIntoBuffer(buffer);
  }

  void ASN1_ValueSequence::ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) {
    ByteArray ImplTag, ExplTag;

    unsigned int oldPos = pos;

    ReadNextTags(buffer, pos, ImplTag, ExplTag);

    if (CheckTags(ImplTag, ExplTag, false, 0)) {
      if (IsIgnored())
        Ignore(false); // if the node was marked as ignored, enable it

      unsigned int L;
      if (!GetLengthFromBuffer(buffer, pos, L))
        throw ParsingEx("Cannot read length of object: " + GetName(), this->GetGrammarObject(), pos);

      unsigned int dataFieldPos = pos;
      for (std::vector<ASN1_Value*>::iterator i = m_Objects.begin(); i < m_Objects.end(); i++) {
        if (pos < dataFieldPos + L) {
          try { (*i)->ReadFromBuffer(buffer, pos); }
          catch (ParsingEx& e) {
            e.AddError("Cannot read object in " + GetName() + ": " + (*i)->GetName());
            throw e;
          }
        }
        else {
          // Data Field finished and object not found
          if (!(*i)->IsMandatory() || (*i)->HasDefaultValue())
            (*i)->Ignore(true);
          else
            throw ParsingEx("Cannot find mandatory object in " + GetName() + ": " + (*i)->GetName(), this->GetGrammarObject(), pos);
        }
      }
      if (pos < dataFieldPos + L) {
        if (IsExtensible()) {
          //pos = dataFieldPos + L;  // to be used to ignore totally the unknown field
          while (pos < dataFieldPos + L) {
            unsigned int oldPos2 = pos;
            ByteArray TagExtensibility, TagDummy;

            try { ReadNextTags(buffer, pos, TagExtensibility, TagDummy); }
            catch (ParsingEx& e) {
              e.AddError("Cannot read extensibility object tag: " + GetName());
              throw e;
            }
            pos = oldPos2; // tag will be read again

            ASN1_OctetString* OctetStringExtensibility = new ASN1_OctetString("Extensibility Object", TagExtensibility);
            m_ExtensibilityObjects.push_back(OctetStringExtensibility->GetValue());

            try { OctetStringExtensibility->GetValue()->ReadFromBuffer(buffer, pos); }
            catch (ParsingEx& e) {
              e.AddError("Cannot read extensibility object in " + GetName() + ": " + OctetStringExtensibility->GetName());
              throw e;
            }
          }
        }
        else
          throw ParsingEx("Sequence too long. There is more to read but the sequence is finished: sequence " + GetName(), this->GetGrammarObject(), pos);
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

  bool ASN1_ValueSequence::CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const {
    if (SecondTree->GetType() != Utils::cSequence) {
      errorReport.append("Grammar incompatibility: not same kind of node - COMPARISON ABORTED.\n\n");
      return false;
    }

    // We assume the grammar is correct : no need to check the tag, if the variable is optional, if it is implicit, and the default value
    // Check the sequence node first
    const ASN1_ValueSequence* SecondTreeAsSeq = static_cast<const ASN1_ValueSequence*>(SecondTree);

    bool result = ASN1_Value::CompareTree(SecondTreeAsSeq, NbDiff, errorReport);
    if (result && !IsIgnored()) {
      for (unsigned int i = 0; i < GetSize(); i++) {
        unsigned int oldNbDiff = NbDiff;
        result = GetObjectAt(i)->CompareTree(SecondTreeAsSeq->GetObjectAt(i), NbDiff, errorReport);
        if (oldNbDiff != NbDiff) {
          errorReport.append("Node: " + GetName() + " - Object comparison failed at index " + std::to_string(i) + ".\n\n");
          NbDiff++;
        }
        if (!result)
          break;
      }
      if (IsExtensible()) {
        if (GetExtensibilitySize() == SecondTreeAsSeq->GetExtensibilitySize())
          for (unsigned int i = 0; i < GetExtensibilitySize(); i++) {
            unsigned int oldNbDiff = NbDiff;
            result = GetExtensibilityObjectAt(i)->CompareTree(SecondTreeAsSeq->GetExtensibilityObjectAt(i), NbDiff, errorReport);
            if (oldNbDiff != NbDiff) {
              errorReport.append("Node: " + GetName() + " - Object comparison failed in extensibility at index " + std::to_string(i) + ".\n\n");
              NbDiff++;
            }
            if (!result)
              break;
          }
        else {
          result = false;
          // ErrorReport: report error here ! extensibility different size
        }
      }
    }
    return result;
  }
}

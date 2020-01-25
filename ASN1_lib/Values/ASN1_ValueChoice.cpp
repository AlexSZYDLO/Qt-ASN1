/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_ValueChoice.h"

using namespace Utils;

namespace Value {
  ASN1_ValueChoice::ASN1_ValueChoice(ASN1_Choice::callbackChoice choiceFromIdx,
                                     unsigned int numberOfChoices,
                                     const std::string& name,
                                     ASN1_Object* grammarObject,
                                     const ByteArray& tag,
                                     bool optional,
                                     bool explicitTag,
                                     const ASN1_ValueChoice* defaultValue)
    : ASN1_Value(name, grammarObject, tag, "", optional, explicitTag, defaultValue),
      m_TheChoice(nullptr),
      m_TheChoiceIndex(0),
      m_Callback(choiceFromIdx),
      m_NumberOfChoices(numberOfChoices) {
    SetSelectedChoice(0);
  }

  ASN1_ValueChoice::~ASN1_ValueChoice() {
    DeleteDummyChoiceList();
    delete m_TheChoice->GetGrammarObject();
  }

  void ASN1_ValueChoice::SetHexValue(const ByteArray&, std::string&) {}

  void ASN1_ValueChoice::ClearDynamicData() {
    SetSelectedChoice(0);
  }

  eNodeType ASN1_ValueChoice::GetType() const {
    return cChoice;
  }

  ASN1_Value* ASN1_ValueChoice::GetSelectedChoice() const {
    return m_TheChoice;
  }

  unsigned int ASN1_ValueChoice::GetSelectedChoiceIndex() const {
    return m_TheChoiceIndex;
  }

  ASN1_Value* ASN1_ValueChoice::SetSelectedChoice(unsigned int idx) {
    ASN1_Object* obj = m_Callback.f(idx, m_Callback.context);
    if (obj != nullptr) {
      ASN1_Value* newChoice = obj->GetValue();
      if (m_TheChoice != nullptr)
        delete m_TheChoice->GetGrammarObject();
      if (newChoice != nullptr) {
        m_TheChoice = newChoice;
        m_TheChoice->SetParentValue(this);
      }
      m_TheChoiceIndex = idx;
      return newChoice;
    }
    return nullptr;
  }

// ---------- dummy choices ------------------

  unsigned int ASN1_ValueChoice::GetNumberOfPossibleChoices() {
    return m_NumberOfChoices;
  }

  const ASN1_Value* ASN1_ValueChoice::GetDummyChoiceFromIndex(unsigned int idx) {
    if (idx < GetNumberOfPossibleChoices())
      return m_AvailableChoices.at(idx);
    else return nullptr;
  }

  void ASN1_ValueChoice::DeleteDummyChoiceList() {
    // delete list of available choices, except the selected one that is kept
    for (unsigned int i = 0; i < m_AvailableChoices.size(); i++)
      if (m_AvailableChoices.at(i) != m_TheChoice)
        delete m_AvailableChoices.at(i)->GetGrammarObject();
    m_AvailableChoices.clear();
  }

  void ASN1_ValueChoice::MakeDummyChoiceList() {
    DeleteDummyChoiceList();
    for (unsigned int i = 0; i < m_NumberOfChoices; i++) {
      ASN1_Value* val = m_Callback.f(i, m_Callback.context)->GetValue();
      if (val != nullptr) {
        val->SetParentValue(this);
        m_AvailableChoices.push_back(val);
      }
    }
  }


// ---------- read/write functions ----------

  bool ASN1_ValueChoice::IsTagAvailableInChoices(ByteArray TagToCheck) {
    for (std::vector<ASN1_Value*>::const_iterator i = m_AvailableChoices.cbegin(); i < m_AvailableChoices.cend(); i++)
      if ((*i)->GetTag() == TagToCheck) {
        return true;
        break;
      }
    return false;
  }

  void ASN1_ValueChoice::GetContentValue(ByteArray& buffer) const {
    if (m_TheChoice != nullptr)
      m_TheChoice->WriteIntoBuffer(buffer);
    else if (IsMandatory()) {
      //throw ValueEx("Missing value in choice: " + GetName());
    }
  }

  void ASN1_ValueChoice::ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) {
    ByteArray ExplTag, ImplTag;
    bool choiceIgnored = false;

    if (GetTag() != "") {
      unsigned int oldPos = pos;
      ReadNextTags(buffer, pos, ImplTag, ExplTag);

      if (CheckTags(ImplTag, ExplTag, false, 0)) {
        unsigned int L;
        if (!GetLengthFromBuffer(buffer, pos, L))
          throw ParsingEx("Cannot read length of object: " + GetName(), this->GetGrammarObject(), pos);
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
          choiceIgnored = true;
        }
      }
    }

    if (!choiceIgnored) {
      if (IsIgnored())
        Ignore(false); // maybe set to true later if choices don't match

      MakeDummyChoiceList();
      int oldPos = pos;
      bool ObjectFound = false;

      for (unsigned int i = 0; i < m_AvailableChoices.size(); i++) {

        try {
          m_AvailableChoices.at(i)->ReadNextTags(buffer, pos, ImplTag, ExplTag);
        }
        catch (ParsingEx&) {
          // buffer empty, but it can be that the choice is optional. It will be checked later
          break;
        }
        pos = oldPos; //tags will be read again in ReadFromBuffer()

        ObjectFound = m_AvailableChoices.at(i)->CheckTags(ImplTag, ExplTag, false, 0);
        if (ObjectFound) {
          SetSelectedChoice(i);
          try {
            m_TheChoice->ReadFromBuffer(buffer, pos);
            break;
          }
          catch (ParsingEx& e) {
            e.AddError("Cannot read choice selection : " + GetName());
            throw e;
          }
        }
      }
      if (!ObjectFound) {
        if (IsMandatory() && !HasDefaultValue()) {
          try { CheckTags(ImplTag, ExplTag, true, oldPos); }
          catch (ParsingEx& e) {
            e.AddError("Cannot find a matching tag in choice: " + GetName() + ". Read tags are: first tag " + std::string(ImplTag.GetString()) + ", second tag (to be ignored for implicit objects) " +
                       std::string(ExplTag.GetString()));
            throw e;
          }
        }
        else {
          Ignore(true); // parameter is not present but optional->OK
          pos = oldPos;
        }
      }
      DeleteDummyChoiceList();
    }
  }

  bool ASN1_ValueChoice::CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const {
    if (SecondTree->GetType() != Utils::cChoice) {
      errorReport.append("Grammar incompatibility: not same kind of node - COMPARISON ABORTED.\n\n");
      return false;
    }
    // We assume the grammar is correct : no need to check the tag, if the variable is optional, if it is implicit, and the default value
    const ASN1_ValueChoice* SecondTreeAsChoice = static_cast<const ASN1_ValueChoice*>(SecondTree);

    // Check the choice node first
    bool result = ASN1_Value::CompareTree(SecondTreeAsChoice, NbDiff, errorReport);
    if (result && !IsIgnored()) {
      if ((SecondTreeAsChoice->GetSelectedChoice() != nullptr) && (m_TheChoice->GetTag() == SecondTreeAsChoice->GetSelectedChoice()->GetTag()))
        result = m_TheChoice->CompareTree(SecondTreeAsChoice->GetSelectedChoice(), NbDiff, errorReport);
      else {
        errorReport.append("Node: " + GetName() + " - Chosen Value check failed.\n");
        errorReport.append("Tree Node: " + GetSelectedChoice()->GetName() + " - Compared Node: " + SecondTreeAsChoice->GetSelectedChoice()->GetName() + "\n\n");
        NbDiff++;
      }
    }
    return result;
  }
}

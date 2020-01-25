/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_ValueSet.h"
#include "../ASN1_Object.h"

using namespace Utils;

namespace Value {
  ASN1_ValueSet::ASN1_ValueSet(ASN1_Value* values[],
                               unsigned int numberOfValues,
                               const std::string& name,
                               ASN1_Object* grammarObject,
                               const ByteArray& tag,
                               bool optional,
                               bool explicitTag,
                               const ASN1_ValueSet* defaultValue,
                               bool extensibility)
    : ASN1_Value(name, grammarObject, tag, "31", optional, explicitTag, defaultValue),
      m_Extensibility(extensibility) {
    for (unsigned int i = 0; i < numberOfValues; i++) {
      m_Objects.push_back(values[i]);
      values[i]->SetParentValue(this);
    }
  }

  ASN1_ValueSet::~ASN1_ValueSet() {
    for (unsigned int i = 0; i < m_Objects.size(); i++)
      delete m_Objects.at(i)->GetGrammarObject();
    for (unsigned int i = 0; i < m_ExtensibilityObjects.size(); i++)
      delete m_ExtensibilityObjects.at(i)->GetGrammarObject();
  }

  void ASN1_ValueSet::SetHexValue(const ByteArray&, std::string&) {}

  void ASN1_ValueSet::ClearDynamicData() {
    for (unsigned int i = 0; i < m_Objects.size(); i++)
      m_Objects.at(i)->ClearDynamicData();
    for (unsigned int i = 0; i < m_ExtensibilityObjects.size(); i++)
      delete m_ExtensibilityObjects.at(i)->GetGrammarObject();
    m_ExtensibilityObjects.clear();
  }

  eNodeType ASN1_ValueSet::GetType() const {
    return cSet;
  }

  bool ASN1_ValueSet::IsExtensible() const {
    return m_Extensibility;
  }

  unsigned int ASN1_ValueSet::GetSize() const {
    return static_cast<unsigned int>(m_Objects.size());
  }

  const ASN1_Value* ASN1_ValueSet::GetObjectAt(unsigned int pos) const {
    if (GetSize() > pos)
      return m_Objects.at(pos);
    else return nullptr;
  }

  void ASN1_ValueSet::AppendExtensibilityObject(ASN1_Value* obj) {
    if (IsExtensible()) {
      m_ExtensibilityObjects.push_back(obj);
      obj->SetParentValue(this);
    }
  }

  unsigned int ASN1_ValueSet::GetExtensibilitySize() const {
    return static_cast<unsigned int>(m_ExtensibilityObjects.size());
  }

  const ASN1_Value* ASN1_ValueSet::GetExtensibilityObjectAt(unsigned int pos) const {
    if (GetExtensibilitySize() > pos)
      return m_ExtensibilityObjects.at(pos);
    else return nullptr;
  }



  void ASN1_ValueSet::GetContentValue(ByteArray& buffer) const {
    for (size_t i = 0; i < m_Objects.size(); i++)
      m_Objects.at(i)->WriteIntoBuffer(buffer);
    for (size_t i = 0; i < m_ExtensibilityObjects.size(); i++)
      m_ExtensibilityObjects.at(i)->WriteIntoBuffer(buffer);
  }

  void ASN1_ValueSet::ReadFromBuffer(const ByteArray& buffer, unsigned int& pos) {
    ByteArray ImplTag, ExplTag;
    std::vector<ASN1_Value*> MyObjectsToFill(m_Objects);

    unsigned int oldPos = pos;

    try { ReadNextTags(buffer, pos, ImplTag, ExplTag); }
    catch (ParsingEx& e) {
      e.AddError("Cannot read object tag: " + GetName());
      throw e;
    }

    if (CheckTags(ImplTag, ExplTag, false, 0)) {
      if (IsIgnored())
        Ignore(false); // if the node was marked as ignored, enable it

      unsigned int L;
      if (!GetLengthFromBuffer(buffer, pos, L))
        throw ParsingEx("Cannot read length of object: " + GetName(), this->GetGrammarObject(), pos);

      while (pos < oldPos + L) {
        unsigned int oldPos2 = pos;

        try { ReadNextTags(buffer, pos, ImplTag, ExplTag); }
        catch (ParsingEx& e) {
          e.AddError("Cannot read object tag in set: " + GetName());
          throw e;
        }
        pos = oldPos2; //tags will be read again in Object.ReadFromBuffer

        bool TagNotFound = true;
        for (unsigned int i = 0; i < m_Objects.size(); i++) {
          ASN1_Value* Object = m_Objects.at(i);

          if (Object->CheckTags(ImplTag, ExplTag, false, 0)) {
            TagNotFound = false;

            bool found = false;
            unsigned int j;
            for (j = 0; j < MyObjectsToFill.size(); j++)
              if (MyObjectsToFill.at(j) == Object) {
                found = true;
                break;
              }

            if (found) {
              try {
                Object->ReadFromBuffer(buffer, pos);
                MyObjectsToFill.erase(MyObjectsToFill.begin() + j);
                break;
              }
              catch (ParsingEx& e) {
                e.AddError("Cannot read object in " + GetName() + ": " + Object->GetName());
                throw e;
              }
            }
            else throw ParsingEx("The object has already been processed in set: set" + GetName() + ", object " + Object->GetName(), this->GetGrammarObject(), pos);
          }
        }

        //if (TagNotFound && IsExtensibility())
        //  int oldPos2 = pos;
        //   new(OctetStringForExtensibility)
        //   OctetStringForExtensibility.SetName('Unknown value (not in object model) - Extensibility implied option activated')
        //   self.MyObjectsExtensibilityImplied.AppendObject(OctetStringForExtensibility)
        //   ;
        //   _Result = self.GetTagFromBuffer(buffer, pos, TagExtensibility, ErrorReport)
        //   OctetStringForExtensibility.SetTag(TagExtensibility)
        //   pos = oldPos2 ; tag will be read again
        //   ;
        //   _Result = _Result and OctetStringForExtensibility.ReadFromBuffer(buffer,
        //      pos, ErrorReport)
        //   if not _Result
        //      ErrorReport.type.WriteLn('Extensibility impmlied in sequence failed: sequence' &&
        //         self.Name, @ErrorReport)
        //   endIf
        //   ;
        //elseif not _Result
        //   ErrorReport.type.WriteLn('Cannot find a matching tag in set:' && self.Name &
        //      '. Tags read are: first tag' && ImplTag & ', second tag (to be ignored for implicit objects)' &&
        //      ExplTag, @ErrorReport)
        //endIf
      }

      for (unsigned int i = 0; i < MyObjectsToFill.size(); i++) {
        ASN1_Value* Object = MyObjectsToFill.at(0);
        if (Object->IsMandatory() || (Object->IsMandatory() && !Object->HasDefaultValue()))
          throw ParsingEx("Missing mandatory object in set: " + GetName() + ", object " + Object->GetName(), this->GetGrammarObject(), oldPos);
        else
          Object->Ignore(true);
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

  bool ASN1_ValueSet::CompareTree(const ASN1_Value* SecondTree, unsigned int& NbDiff, std::string& errorReport) const {
    if (SecondTree->GetType() != Utils::cSet) {
      errorReport.append("Grammar incompatibility: not same kind of node - COMPARISON ABORTED.\n\n");
      return false;
    }

    // We assume the grammar is correct : no need to check the tag, if the variable is optional, if it is implicit, and the default value
    // Check the set node first
    const ASN1_ValueSet* SecondTreeAsSeq = static_cast<const ASN1_ValueSet*>(SecondTree);

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

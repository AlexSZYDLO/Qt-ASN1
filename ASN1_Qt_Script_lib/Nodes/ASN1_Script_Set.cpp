/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_Set.h"
#include "ASN1_Script_Basic_Nodes.h"
#include "Script.h"

ASN1_Script_Set::ASN1_Script_Set(QObjectList objects,
                                 const QString& name,
                                 const QString& tag,
                                 bool optional,
                                 bool explicitTag,
                                 ASN1_Script_Set* defaultValue,
                                 bool extensibility) {

  typedef ASN1_Object* tpObj;
  tpObj* arr = new tpObj[objects.size()];
  for (int i = 0; i < objects.size(); i++) {
    ASN1_Script_Node* sGram = static_cast<ASN1_Script_Node*>(objects.at(i));
    m_Objects.push_back(sGram);
    arr[i] = sGram->getGrammar();
  }

  m_GrammarSpe =
    new ASN1_Set(arr,
                 objects.size(),
                 name.toStdString().c_str(),
                 ByteArray(tag.toStdString().c_str()),
                 optional,
                 explicitTag,
                 defaultValue != nullptr ? static_cast<ASN1_Set*>(defaultValue->getGrammar()) : nullptr,
                 extensibility);
}

ASN1_Script_Set::~ASN1_Script_Set() {
  m_Objects.clear();
}

ASN1_Set* ASN1_Script_Set::getGrammar() const {
  return m_GrammarSpe;
}

QObject* ASN1_Script_Set::GetObjectAt(unsigned int pos) const {
  return m_Objects.at(pos);
}

unsigned int ASN1_Script_Set::GetSetSize() const {
  return m_GrammarSpe->GetSize();
}

QObject* ASN1_Script_Set::getExtensibilityObjectAt(unsigned int pos) const {
  // Create the object in the script environment if needed, and add it to clean list
  return engine()->toScriptValue(
           Add(engine(), new ASN1_Script_OctetString(m_GrammarSpe->GetExtensibilityObjectAt(pos)->GetName().c_str(),
               m_GrammarSpe->GetExtensibilityObjectAt(pos)->GetTag().GetString()))
         ).toQObject();
  //return nullptr;
}

unsigned int ASN1_Script_Set::getExtensibilityeSize() const {
  return m_GrammarSpe->GetExtensibilitySize();
}

bool ASN1_Script_Set::isExtensible() const {
  return m_GrammarSpe->IsExtensible();
}

void ASN1_Script_Set::clearDynamicData() {
  m_GrammarSpe->ClearDynamicData();
  for (int i = 0; i < m_Objects.size(); i++)
    m_Objects.at(i)->clearDynamicData();
}

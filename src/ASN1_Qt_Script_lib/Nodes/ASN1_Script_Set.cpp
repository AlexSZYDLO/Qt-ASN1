/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_Set.h"
#include "ASN1_Script_Basic_Nodes.h"

ASN1_Script_Set::ASN1_Script_Set(QObjectList objects, const QString& name, const QString& tag, bool optional,
                                 bool explicitTag, ASN1_Script_Set* defaultValue, bool extensibility)
    : ASN1_Script_Node_Base(name)
{
  typedef ASN1_Object* tpObj;

  tpObj* arr = new tpObj[objects.size()];
  for (int i = 0; i < objects.size(); i++) {
    ASN1_Script_Node_Base* sGram = static_cast<ASN1_Script_Node_Base*>(objects.at(i));
    sGram->setUsed();
    m_Objects.push_back(sGram);
    arr[i] = sGram->getGrammar();
  }

  ASN1_Set* def = (defaultValue && !defaultValue->used) ? static_cast<ASN1_Set*>(defaultValue->getGrammar()) : nullptr;
  if (def) defaultValue->setUsed();

  m_GrammarSpe = new ASN1_Set(arr, objects.size(), name.toStdString().c_str(), ByteArray(tag.toStdString().c_str()),
                 optional, explicitTag, def, extensibility);
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

void ASN1_Script_Set::clearDynamicData() {
  m_GrammarSpe->ClearDynamicData();
  for (int i = 0; i < m_Objects.size(); i++)
    m_Objects.at(i)->clearDynamicData();
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_SequenceOf.h"

ASN1_SequenceOf::callbackSequenceOf MakeCallback(ASN1_Script_SequenceOf* pointerToThis) {
  return {
    [](void* ptr) -> ASN1_Object* {
      ASN1_Script_SequenceOf* thisPtr = static_cast<ASN1_Script_SequenceOf*>(ptr);
      return thisPtr->Callback();
    }, pointerToThis};
}

ASN1_Script_SequenceOf::ASN1_Script_SequenceOf(QScriptValue callback,
    const QString& name,
    const QString& tag,
    bool optional,
    bool explicitTag,
    ASN1_Script_SequenceOf* defaultValue) :
  m_Callback(callback) {
  m_GrammarSpe =
    new ASN1_SequenceOf(MakeCallback(this),
                        name.toStdString().c_str(),
                        ByteArray(tag.toStdString().c_str()),
                        optional,
                        explicitTag,
                        defaultValue != nullptr ? static_cast<ASN1_SequenceOf*>(defaultValue->getGrammar()) : nullptr);
}

ASN1_SequenceOf* ASN1_Script_SequenceOf::getGrammar() const {
  return m_GrammarSpe;
}

ASN1_Object* ASN1_Script_SequenceOf::Callback() {
  QScriptValue global = m_Callback.engine()->globalObject();
  QScriptValueList args;

  QScriptValue ret = m_Callback.call(global, args);
  QObject* retObj = ret.toQObject();

  // keep track of newly created script value
  m_LastCreatedObject = static_cast<ASN1_Script_Node*>(retObj);
  return m_LastCreatedObject != nullptr ? m_LastCreatedObject->getGrammar() : nullptr;
}

QObject* ASN1_Script_SequenceOf::getObjectAt(unsigned int i) const {
  if (i < (unsigned int) m_Objects.size())
    return m_Objects.at(i);
  else return nullptr;
}

unsigned int ASN1_Script_SequenceOf::getSequenceOfSize() const {
  return m_GrammarSpe->GetSequenceOfSize();
}

QObject* ASN1_Script_SequenceOf::getNewDummyObject() {
  m_GrammarSpe->GetDummyNewObject();
  return m_LastCreatedObject;
}

QObject* ASN1_Script_SequenceOf::appendNewObject() {
  m_GrammarSpe->AppendNewObject();
  m_Objects.push_back(m_LastCreatedObject);
  return m_LastCreatedObject;
}

void ASN1_Script_SequenceOf::deleteObjectAt(unsigned int pos) {
  m_GrammarSpe->DeleteObjectAt(pos);
  m_Objects.removeAt(pos);
}

void ASN1_Script_SequenceOf::moveUpObject(unsigned int pos) {
  if (pos > 0 && pos < getSequenceOfSize()) {
    m_GrammarSpe->MoveUpObject(pos);
    ASN1_Script_Node* temp = m_Objects.at(pos);
    deleteObjectAt(pos);
    m_Objects.insert(m_Objects.begin() + pos - 1, temp);
  }
  else context()->throwError("moveUpObject invalid index");
}

void ASN1_Script_SequenceOf::moveDownObject(unsigned int pos) {
  if (pos < getSequenceOfSize() - 1) {
    m_GrammarSpe->MoveDownObject(pos);
    ASN1_Script_Node* temp = m_Objects.at(pos);
    deleteObjectAt(pos);
    m_Objects.insert(m_Objects.begin() + pos + 1, temp);
  }
  else context()->throwError("moveDownObject invalid index");
}

void ASN1_Script_SequenceOf::clearDynamicData() {
  m_GrammarSpe->ClearDynamicData();
  m_Objects.clear();
}

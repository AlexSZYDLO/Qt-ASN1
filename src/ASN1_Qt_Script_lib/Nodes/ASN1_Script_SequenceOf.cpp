/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_SequenceOf.h"


ASN1_Script_SequenceOf::ASN1_Script_SequenceOf(QJSValue callback, const QString& name, const QString& tag,
                                               bool optional, bool explicitTag, ASN1_Script_SequenceOf* defaultValue)
    : ASN1_Script_Node_Base(name), m_Callback(callback)
{
  ASN1_SequenceOf* def = (defaultValue && !defaultValue->used) ? static_cast<ASN1_SequenceOf*>(defaultValue->getGrammar()) : nullptr;
  if (def) defaultValue->setUsed();

  auto _callback = [](void* ptr) -> ASN1_Object* {
    ASN1_Script_SequenceOf* thisPtr = static_cast<ASN1_Script_SequenceOf*>(ptr);
    if (!thisPtr->m_Callback.isCallable())
      return nullptr;

    QJSValue ret = thisPtr->m_Callback.call();
    if (ret.isError())
      std::cout << ret.toString().toStdString() << std::endl;

    thisPtr->m_LastCreatedObject = static_cast<ASN1_Script_Node_Base*>(ret.toQObject());
    thisPtr->m_LastCreatedObject->setUsed();

    return thisPtr->m_LastCreatedObject != nullptr ? thisPtr->m_LastCreatedObject->getGrammar() : nullptr;
  };

  m_GrammarSpe = new ASN1_SequenceOf({_callback, this}, name.toStdString().c_str(), ByteArray(tag.toStdString().c_str()),
                                     optional, explicitTag, def);
  m_GrammarSpeBase = m_GrammarSpe;
}

ASN1_SequenceOf* ASN1_Script_SequenceOf::getGrammar() const {
  return m_GrammarSpe;
}

QObject* ASN1_Script_SequenceOf::getObjectAt(unsigned int i) const {
  if (i < (unsigned int) m_Objects.size())
    return m_Objects.at(i);
  else return nullptr;
}

unsigned int ASN1_Script_SequenceOf::getSequenceOfSize() const {
  return m_GrammarSpe->GetSequenceOfSize();
}

QObject* ASN1_Script_SequenceOf::appendNewObject() {
  m_GrammarSpe->AppendNewObject();
  m_Objects.push_back(m_LastCreatedObject);
  return m_LastCreatedObject;
}

void ASN1_Script_SequenceOf::deleteObjectAt(unsigned int pos) {
  // the underlying ASN1_object automatically deletes the value
  // so make sure not to flag it as "unused", otherwise it would get deleted twice
  m_GrammarSpe->DeleteObjectAt(pos);
  m_Objects.removeAt(pos);
}

void ASN1_Script_SequenceOf::moveUpObject(unsigned int pos) {
  if (pos > 0 && pos < getSequenceOfSize()) {
    m_GrammarSpe->MoveUpObject(pos);
    ASN1_Script_Node_Base* temp = m_Objects.at(pos);
    deleteObjectAt(pos);
    m_Objects.insert(m_Objects.begin() + pos - 1, temp);
  }
}

void ASN1_Script_SequenceOf::moveDownObject(unsigned int pos) {
  if (pos < getSequenceOfSize() - 1) {
    m_GrammarSpe->MoveDownObject(pos);
    ASN1_Script_Node_Base* temp = m_Objects.at(pos);
    deleteObjectAt(pos);
    m_Objects.insert(m_Objects.begin() + pos + 1, temp);
  }
}

void ASN1_Script_SequenceOf::clearDynamicData() {
  m_GrammarSpe->ClearDynamicData();
  m_Objects.clear();
}

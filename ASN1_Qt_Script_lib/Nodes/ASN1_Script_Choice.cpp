/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_Choice.h"

ASN1_Choice::callbackChoice MakeCallback(ASN1_Script_Choice* pointerToThis) {
  return {
    [](unsigned int idx, void* ptr) -> ASN1_Object* {
      ASN1_Script_Choice* thisPtr = static_cast<ASN1_Script_Choice*>(ptr);
      return thisPtr->Callback(idx);
    }, pointerToThis};
}

ASN1_Script_Choice::ASN1_Script_Choice(QScriptValue callback,
                                       int numberOfChoices,
                                       const QString& name,
                                       const QString& tag,
                                       bool optional,
                                       bool explicitTag,
                                       ASN1_Script_Choice* defaultValue):
  m_Callback(callback) {
  m_GrammarSpe =
    new ASN1_Choice(MakeCallback(this),
                    numberOfChoices,
                    name.toStdString().c_str(),
                    ByteArray(tag.toStdString().c_str()),
                    optional,
                    explicitTag,
                    defaultValue != nullptr ? static_cast<ASN1_Choice*>(defaultValue->getGrammar()) : nullptr);
}

ASN1_Script_Choice::~ASN1_Script_Choice() {
  deleteDummyChoiceList();
}

ASN1_Choice* ASN1_Script_Choice::getGrammar() const {
  return m_GrammarSpe;
}

ASN1_Object* ASN1_Script_Choice::Callback(int idx) {
  if (m_Callback.isValid()) {
    QScriptValue global = m_Callback.engine()->globalObject();
    QScriptValueList args;
    args << idx;

    QScriptValue ret = m_Callback.call(global, args);
    QObject* retObj = ret.toQObject();

    // keep track of newly created script value
    ASN1_Script_Node* tmp = static_cast<ASN1_Script_Node*>(retObj);
    m_ObjectBuffer.push_back(tmp);
    return tmp != nullptr ? tmp->getGrammar() : nullptr;
  }
  return nullptr;
}

QObject* ASN1_Script_Choice::setSelectedChoice(int idx) {
  m_ObjectBuffer.clear();
  m_GrammarSpe->SetSelectedChoice(idx);
  m_ChosenValue = m_ObjectBuffer.at(0);
  m_ObjectBuffer.clear();
  return m_ChosenValue;
}

QObject* ASN1_Script_Choice::getSelectedChoice() const {
  return m_ChosenValue;
}

unsigned int ASN1_Script_Choice::getSelectedChoiceIndex() const {
  return m_GrammarSpe->GetSelectedChoiceIndex();
}

unsigned int ASN1_Script_Choice::getAvailableChoices() const {
  return m_ChoicesList.size();
}

void ASN1_Script_Choice::makeDummyChoiceList() {
  m_ChoicesList.clear();
  m_GrammarSpe->MakeDummyChoiceList();
  m_ChoicesList = m_ObjectBuffer;
  m_ObjectBuffer.clear();
}

void ASN1_Script_Choice::deleteDummyChoiceList() {
  m_ChoicesList.clear();
  //m_GrammarSpe->DeleteDummyChoiceList();
}

QObject* ASN1_Script_Choice::dummyChoiceFromIndex(unsigned int i) {
  return m_ChoicesList.at(i);
}

void ASN1_Script_Choice::clearDynamicData() {
  setSelectedChoice(0);
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"
#include <QScriptEngine>

class ASN1_Script_Choice : public ASN1_Script_Node {
  Q_OBJECT
 public:
  ASN1_Script_Choice(QScriptValue m_Callback = QScriptValue(),
                     int numberOfChoices = 0,
                     const QString& name = "",
                     const QString& tag = "",
                     bool optional = false,
                     bool explicitTag = false,
                     ASN1_Script_Choice* defaultValue = nullptr);
  virtual ~ASN1_Script_Choice();

  virtual ASN1_Choice* getGrammar() const override;

 public slots:
  QObject* setSelectedChoice(int idx);
  QObject* getSelectedChoice() const;
  unsigned int getSelectedChoiceIndex() const;

  void makeDummyChoiceList();
  void deleteDummyChoiceList();
  unsigned int getAvailableChoices() const;
  QObject* dummyChoiceFromIndex(unsigned int i);

  virtual void clearDynamicData() override;
 protected:
  ASN1_Choice* m_GrammarSpe;

  QScriptEngine* m_Engine;
  QScriptValue m_Callback;

  ASN1_Script_Node* m_ChosenValue;
  QList<ASN1_Script_Node*> m_ChoicesList;

  QList<ASN1_Script_Node*> m_ObjectBuffer;

  ASN1_Object* Callback(int idx);
  friend ASN1_Choice::callbackChoice MakeCallback(ASN1_Script_Choice* pointerToThis);
};

Q_DECLARE_METATYPE(ASN1_Script_Choice*)


/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"
#include <QScriptEngine>

class ASN1_Script_SequenceOf : public ASN1_Script_Node {
  Q_OBJECT

 public:
  ASN1_Script_SequenceOf(QScriptValue callback = QScriptValue(),
                         const QString& name = "",
                         const QString& tag = "",
                         bool optional = false,
                         bool explicitTag = false,
                         ASN1_Script_SequenceOf* defaultValue = nullptr);

  virtual ASN1_SequenceOf* getGrammar() const override;

 public slots:
  QObject* getObjectAt(unsigned int pos) const;
  unsigned int getSequenceOfSize() const;

  QObject* appendNewObject();
  void deleteObjectAt(unsigned int pos);
  void moveUpObject(unsigned int pos);
  void moveDownObject(unsigned int pos);

  QObject* getNewDummyObject();

  virtual void clearDynamicData() override;

 protected:
  ASN1_SequenceOf* m_GrammarSpe;

  QScriptEngine* m_Engine;
  QScriptValue m_Callback;

  QList<ASN1_Script_Node*> m_Objects;
  ASN1_Script_Node* m_LastCreatedObject;

  ASN1_Object* Callback();
  friend ASN1_SequenceOf::callbackSequenceOf MakeCallback(ASN1_Script_SequenceOf* pointerToThis);
};

Q_DECLARE_METATYPE(ASN1_Script_SequenceOf*)


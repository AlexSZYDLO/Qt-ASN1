/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"
#include <QObject>
#include <QList>
#include <QJSValue>

class ASN1_Script_SequenceOf : public ASN1_Script_Node_Base {
  Q_OBJECT

 public:
  Q_INVOKABLE ASN1_Script_SequenceOf(QJSValue callback = QJSValue(),
                         const QString& name = "",
                         const QString& tag = "",
                         bool optional = false,
                         bool explicitTag = false,
                         ASN1_Script_SequenceOf* defaultValue = nullptr);

  ASN1_SequenceOf* getGrammar() const override;

 public slots:
  QObject* getObjectAt(unsigned int pos) const;
  unsigned int getSequenceOfSize() const;

  QObject* appendNewObject();
  void deleteObjectAt(unsigned int pos);
  void moveUpObject(unsigned int pos);
  void moveDownObject(unsigned int pos);

  void clearDynamicData() override;

 protected:
  ASN1_SequenceOf* m_GrammarSpe{};

  QJSValue m_Callback;

  QList<ASN1_Script_Node_Base*> m_Objects;
  ASN1_Script_Node_Base* m_LastCreatedObject{};
};

Q_DECLARE_METATYPE(ASN1_Script_SequenceOf*)


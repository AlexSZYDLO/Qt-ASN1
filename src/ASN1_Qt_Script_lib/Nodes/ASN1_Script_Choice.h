/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"
#include <QObject>
#include <QJSValue>

class ASN1_Script_Choice : public ASN1_Script_Node_Base {
  Q_OBJECT
 public:
  Q_INVOKABLE ASN1_Script_Choice(QJSValue m_Callback = QJSValue(),
                     int numberOfChoices = 0,
                     const QString& name = "",
                     const QString& tag = "",
                     bool optional = false,
                     bool explicitTag = false,
                     ASN1_Script_Choice* defaultValue = nullptr);

  ASN1_Choice* getGrammar() const override;

 public slots:
  QObject* setSelectedChoice(int idx);
  QObject* getSelectedChoice() const;
  unsigned int getSelectedChoiceIndex() const;

  void clearDynamicData() override;

 protected:
  ASN1_Choice* m_GrammarSpe{};

  QJSValue m_Callback;

  ASN1_Script_Node_Base* m_ChosenValue{};
};

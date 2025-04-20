/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QList>
#include <QObject>
#include "../ASN1_Script_Node.h"

class ASN1_Script_Sequence : public ASN1_Script_Node_Base
{
  Q_OBJECT
public:
  Q_INVOKABLE ASN1_Script_Sequence(QObjectList _objects = QObjectList(),
                                   const QString &name = "",
                                   const QString &tag = "",
                                   bool optional = false,
                                   bool explicitTag = false,
                                   ASN1_Script_Sequence *defaultValue = nullptr,
                                   bool extensibility = false);
  ASN1_Object *getGrammar() const override;

public slots:
  QObject *getObjectAt(unsigned int pos) const;
  unsigned int getSize() const;

  void clearDynamicData() override;

protected:
  ASN1_Sequence *m_GrammarSpe{};

  QList<ASN1_Script_Node_Base *> m_Objects;
};

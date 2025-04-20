/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QJSEngine>
#include "../ASN1_Script_Node.h"

class ASN1_Script_Set : public ASN1_Script_Node_Base
{
  Q_OBJECT
public:
  Q_INVOKABLE ASN1_Script_Set(QObjectList _objects = QObjectList(),
                              const QString &name = "",
                              const QString &tag = "",
                              bool optional = false,
                              bool explicitTag = false,
                              ASN1_Script_Set *defaultValue = nullptr,
                              bool extensibility = false);
  ASN1_Set *getGrammar() const override;

public slots:
  QObject *GetObjectAt(unsigned int pos) const;
  unsigned int GetSetSize() const;

  void clearDynamicData() override;

protected:
  ASN1_Set *m_GrammarSpe{};

  QList<ASN1_Script_Node_Base *> m_Objects;
};

Q_DECLARE_METATYPE(ASN1_Script_Set *)

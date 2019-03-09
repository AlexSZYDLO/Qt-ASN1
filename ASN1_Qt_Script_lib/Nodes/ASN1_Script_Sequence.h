/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"
#include <QScriptEngine>

class ASN1_Script_Sequence : public ASN1_Script_Node {
  Q_OBJECT
 public:
  ASN1_Script_Sequence(QObjectList _objects = QObjectList(),
                       const QString& name = "",
                       const QString& tag = "",
                       bool optional = false,
                       bool explicitTag = false,
                       ASN1_Script_Sequence* defaultValue = nullptr,
                       bool extensibility = false);
  virtual ~ASN1_Script_Sequence();
  virtual ASN1_Sequence* getGrammar() const override;

 public slots:
  QObject* getObjectAt(unsigned int pos) const;
  unsigned int getSize() const;

  QObject* getExtensibilityObjectAt(unsigned int pos) const;
  unsigned int getExtensibilityeSize() const;

  bool isExtensible() const;

  virtual void clearDynamicData() override;

 protected:
  ASN1_Sequence* m_GrammarSpe;
  QList<ASN1_Script_Node*> m_Objects;
};

Q_DECLARE_METATYPE(ASN1_Script_Sequence*)


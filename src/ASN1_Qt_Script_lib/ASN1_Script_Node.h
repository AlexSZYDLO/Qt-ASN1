/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QObject>
#include <concepts>
#include <iostream>
#include "ASN1_includes.h"

extern std::shared_ptr<ASN1_Object> TheGrammar;

class ASN1_Script_Node_Base : public QObject
{
  Q_OBJECT

protected:
  static int ObjectCount;
  std::string name;
  bool used = false;
  ASN1_Object *m_GrammarSpeBase{};

public:
  static bool memoryCheck();

  ASN1_Script_Node_Base(const QString &name);
  virtual ~ASN1_Script_Node_Base() = 0;
  virtual ASN1_Object *getGrammar() const = 0;
  void setUsed(bool used = true);

public slots:
  void registerGrammar();

  void setDescription(const QString &desc);
  void setIgnoredByUser(bool Ignore = true);

  virtual void clearDynamicData();
};

template <class T>
class ASN1_Script_Template_Base : public ASN1_Script_Node_Base
{
protected:
  T *m_GrammarSpe{};

public:
  Q_INVOKABLE ASN1_Script_Template_Base(const QString &name = "",
                                        const QString &tag = "",
                                        bool optional = false,
                                        bool explicitTag = false,
                                        ASN1_Script_Template_Base<T> *defaultValue = nullptr)
      : ASN1_Script_Node_Base(name)
  {
    T *def = (defaultValue && !defaultValue->used) ? static_cast<T *>(defaultValue->getGrammar()) : nullptr;
    if (def)
      defaultValue->setUsed();

    m_GrammarSpe = new T(name.toStdString().c_str(), ByteArray(tag.toStdString().c_str()), optional, explicitTag, def);
    m_GrammarSpeBase = m_GrammarSpe;
  }

  Q_INVOKABLE ASN1_Object *getGrammar() const override
  {
    return m_GrammarSpe;
  }
};

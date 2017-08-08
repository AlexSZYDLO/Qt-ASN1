/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <iostream>
#include <QObject>
#include <QScriptable>
#include "ASN1_includes.h"

extern ASN1_Object* TheGrammar;

class ASN1_Script_Node : public QObject, protected QScriptable {
  Q_OBJECT
  static int ObjectCount;
 public:
  static bool memoryCheck();

  ASN1_Script_Node() { /*std::cout << "ctor: Script : " << ++ObjectCount << std::endl;*/ }
  virtual ~ASN1_Script_Node() { /*std::cout << "dest: Script : " << --ObjectCount << std::endl;*/ }
  virtual ASN1_Object* getGrammar() const;

 public slots:
  void registerGrammar() const;

  void setDescription(const QString& desc);
  void setIgnoredByUser(bool Ignore = true);

  virtual void clearDynamicData();
};
Q_DECLARE_METATYPE(ASN1_Script_Node*)


template <class T>
class ASN1_Script_Template_Base : public ASN1_Script_Node {
 protected:
  T* m_GrammarSpe;

 public:
  ASN1_Script_Template_Base(const QString& name = "",
                            const QString& tag = "",
                            bool optional = false,
                            bool explicitTag = false,
                            ASN1_Script_Template_Base* defaultValue = nullptr);
  virtual ~ASN1_Script_Template_Base();
  virtual T* getGrammar() const override;
};

template<class T>
ASN1_Script_Template_Base<T>::ASN1_Script_Template_Base(const QString& name = "",
    const QString& tag = "",
    bool optional = false,
    bool explicitTag = false,
    ASN1_Script_Template_Base* defaultValue = nullptr) {
  m_GrammarSpe = new T(name.toStdString().c_str(),
                       ByteArray(tag.toStdString().c_str()),
                       optional,
                       explicitTag,
                       defaultValue != nullptr ? static_cast<T*>(defaultValue->getGrammar()) : nullptr);
}

template<class T>
ASN1_Script_Template_Base<T>::~ASN1_Script_Template_Base() {}

template<class T>
T* ASN1_Script_Template_Base<T>::getGrammar() const {
  return m_GrammarSpe;
}

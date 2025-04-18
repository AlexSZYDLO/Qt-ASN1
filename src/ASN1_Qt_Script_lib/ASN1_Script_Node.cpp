/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "ASN1_Script_Node.h"

std::shared_ptr<ASN1_Object> TheGrammar;

int ASN1_Script_Node_Base::ObjectCount = 0;

ASN1_Script_Node_Base::ASN1_Script_Node_Base(const QString& _name) : name(_name.toStdString()) {
  if (ASN1_DEBUG_MEMORY)
    std::cout << "ctor: Script " << name << " : " << ++ObjectCount << std::endl;
}

ASN1_Script_Node_Base::~ASN1_Script_Node_Base() {
  if (ASN1_DEBUG_MEMORY)
    std::cout << "dest: Script " << name << " : " << --ObjectCount << std::endl;
  if (!used) delete m_GrammarSpeBase;
}

bool ASN1_Script_Node_Base::memoryCheck() {
  return ObjectCount == 0;
}

void ASN1_Script_Node_Base::registerGrammar() {
  if (!used)
  {
    TheGrammar.reset(getGrammar());
    setUsed();
  }
}

void ASN1_Script_Node_Base::setDescription(const QString& desc) {
  getGrammar()->SetDescription(desc.toStdString().c_str());
}

void ASN1_Script_Node_Base::setIgnoredByUser(bool Ignore) {
  getGrammar()->Ignore(Ignore);
}

void ASN1_Script_Node_Base::clearDynamicData() {}

void ASN1_Script_Node_Base::setUsed(bool used) { this->used = used; }

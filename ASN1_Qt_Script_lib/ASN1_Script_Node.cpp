/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "ASN1_Script_Node.h"

ASN1_Object* TheGrammar;

int ASN1_Script_Node::ObjectCount = 0;

bool ASN1_Script_Node::memoryCheck() {
  return ObjectCount == 0;
}

void ASN1_Script_Node::registerGrammar() const {
  TheGrammar = getGrammar();
}

void ASN1_Script_Node::setDescription(const QString& desc) {
  getGrammar()->SetDescription(desc.toStdString().c_str());
}

void ASN1_Script_Node::setIgnoredByUser(bool Ignore) {
  getGrammar()->Ignore(Ignore);
}

void ASN1_Script_Node::clearDynamicData() {}


ASN1_Object* ASN1_Script_Node::getGrammar() const {
  return nullptr;
}

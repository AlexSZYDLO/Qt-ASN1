/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_OctetString::MakeWidget(QGroupBox *inBox, bool readOnly)
{
  inBox->setTitle(inBox->title() + " - Octet String");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  hexaText = new myQTextEdit(inBox, myQTextEdit::cLineEditHexa);
  inBox->setLayout(vLayValueLayout);
  vLayValueLayout->addWidget(hexaText);
  vLayValueLayout->addItem(verticalSpacer);
  hexaText->setPlainText(m_Grammar->GetOctetStringValue().GetString().c_str());
  if (readOnly)
    hexaText->setReadOnly(true);
}

bool UI_ASN1_Node_OctetString::accept(ASN1_Object *val)
{
  // must recast from non const value
  ASN1_OctetString *octetStringVal = static_cast<ASN1_OctetString *>(val);
  QString hex = hexaText->toTextWithoutSpace();

  if (hexaText->CorrectOddHexa())
  {
    octetStringVal->SetOctetStringValue(hex.toStdString());
    return true;
  }
  return false;
}

bool UI_ASN1_Node_OctetString::GetHexValue(ASN1_Object *val, ByteArray &hex)
{
  // must recast from non const value
  ASN1_OctetString *octetStringVal = static_cast<ASN1_OctetString *>(val);
  // temporary set new value to calculate, and reset to old value
  QString temp(m_Grammar->GetOctetStringValue().GetString().c_str());
  octetStringVal->SetOctetStringValue(hexaText->toTextWithoutSpace().toStdString());
  octetStringVal->WriteIntoBuffer(hex);
  octetStringVal->SetOctetStringValue(temp.toStdString());
  return true;
}
} // namespace UI

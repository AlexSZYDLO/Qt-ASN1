/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_Boolean::MakeWidget(QGroupBox *inBox, bool readOnly)
{
  m_ParentWidget = inBox;
  inBox->setTitle(inBox->title() + " - Boolean");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  check = new QCheckBox("Value (checked=true)", inBox);
  vLayValueLayout->addWidget(check);
  vLayValueLayout->addItem(verticalSpacer);
  check->setChecked(m_Grammar->GetBooleanValue());
  if (readOnly)
    check->setEnabled(false);
}

bool UI_ASN1_Node_Boolean::accept(ASN1_Object *val)
{
  // must recast from non const value
  ASN1_Boolean *boolVal = static_cast<ASN1_Boolean *>(val);
  boolVal->SetBooleanValue(check->isChecked());
  return true;
}

bool UI_ASN1_Node_Boolean::GetHexValue(ASN1_Object *val, ByteArray &hex)
{
  // must recast from non const value
  ASN1_Boolean *boolVal = static_cast<ASN1_Boolean *>(val);
  // temporary set new value to calculate, and reset to old value
  bool temp = m_Grammar->GetBooleanValue();
  boolVal->SetBooleanValue(check->isChecked());
  boolVal->WriteIntoBuffer(hex);
  boolVal->SetBooleanValue(temp);
  return true;
}
} // namespace UI

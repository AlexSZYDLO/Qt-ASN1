/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include <limits>
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_Integer::MakeWidget(QGroupBox *inBox, bool readOnly)
{
  inBox->setTitle(inBox->title() + " - Integer");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  integer = new QSpinBox(inBox);
  inBox->setLayout(vLayValueLayout);
  vLayValueLayout->addWidget(integer);
  vLayValueLayout->addItem(verticalSpacer);
  integer->setMinimum(std::numeric_limits<int>::min());
  integer->setMaximum(std::numeric_limits<int>::max());
  integer->setValue(m_Grammar->GetIntegerValue());
  if (readOnly)
    integer->setReadOnly(true);
}

bool UI_ASN1_Node_Integer::accept(ASN1_Object *val)
{
  // must recast from non const value
  ASN1_Integer *intVal = static_cast<ASN1_Integer *>(val);
  intVal->SetIntegerValue(integer->value());
  return true;
}

bool UI_ASN1_Node_Integer::GetHexValue(ASN1_Object *val, ByteArray &hex)
{
  // must recast from non const value
  ASN1_Integer *intVal = static_cast<ASN1_Integer *>(val);
  // temporary set new value to calculate, and reset to old value
  int temp = m_Grammar->GetIntegerValue();
  intVal->SetIntegerValue(integer->value());
  intVal->WriteIntoBuffer(hex);
  intVal->SetIntegerValue(temp);
  return true;
}
} // namespace UI

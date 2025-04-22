/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_Null::MakeWidget(QGroupBox *inBox, bool)
{
  inBox->setTitle(inBox->title() + " - Null");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  inBox->setLayout(vLayValueLayout);
  vLayValueLayout->addItem(verticalSpacer);
}

bool UI_ASN1_Node_Null::accept(ASN1_Object *)
{
  return true;
}

bool UI_ASN1_Node_Null::GetHexValue(ASN1_Object *, ByteArray &output)
{
  output = "";
  return true;
}
} // namespace UI

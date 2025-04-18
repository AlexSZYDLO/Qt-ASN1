/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI {
  void UI_ASN1_Node_Enumerated::MakeWidget(QGroupBox* inBox, bool readOnly) {
    inBox->setTitle(inBox->title() + " - Enumerated");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    QSpacerItem* verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    enumerated = new QSpinBox(inBox);
    inBox->setLayout(vLayValueLayout);
    vLayValueLayout->addWidget(enumerated);
    vLayValueLayout->addItem(verticalSpacer);
    enumerated->setMinimum(std::numeric_limits<int>::min());
    enumerated->setMaximum(std::numeric_limits<int>::max());
    enumerated->setValue(m_Grammar->GetEnumeratedValue());
    if (readOnly)
      enumerated->setReadOnly(true);
  }

  bool UI_ASN1_Node_Enumerated::accept(ASN1_Object* val) {
    // must recast from non const value
    ASN1_Enumerated* enumVal = static_cast<ASN1_Enumerated*>(val);
    enumVal->SetEnumeratedValue(enumerated->value());
    return true;
  }

  bool UI_ASN1_Node_Enumerated::GetHexValue(ASN1_Object* val, ByteArray& hex) {
    // must recast from non const value
    ASN1_Enumerated* enumVal = static_cast<ASN1_Enumerated*>(val);
    // temporary set new value to calculate, and reset to old value
    //QString temp = grammar->GetBitStringValue();
    int temp = m_Grammar->GetEnumeratedValue();
    enumVal->SetEnumeratedValue(enumerated->value());
    enumVal->WriteIntoBuffer(hex);
    enumVal->SetEnumeratedValue(temp);
    return true;
  }
}

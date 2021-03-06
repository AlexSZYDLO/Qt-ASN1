/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"
#include <limits>

namespace UI {
  void UI_ASN1_Node_Real::MakeWidget(QGroupBox* inBox, bool readOnly) {
    inBox->setTitle(inBox->title() + " - Real");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    QSpacerItem* verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    real = new QDoubleSpinBox(inBox);
    inBox->setLayout(vLayValueLayout);
    vLayValueLayout->addWidget(real);
    vLayValueLayout->addItem(verticalSpacer);
    real->setMinimum(std::numeric_limits<double>::lowest());
    real->setMaximum(std::numeric_limits<double>::max());
    real->setDecimals(10);
    real->setValue(m_Grammar->GetRealValue());
    if (readOnly)
      real->setReadOnly(true);
  }

  bool UI_ASN1_Node_Real::accept(ASN1_Object* val) {
    // must recast from non const value
    ASN1_Real* realVal = static_cast<ASN1_Real*>(val);
    realVal->SetRealValue(real->value());
    return true;
  }

  bool UI_ASN1_Node_Real::GetHexValue(ASN1_Object* val, ByteArray& hex) {
    // must recast from non const value
    ASN1_Real* realVal = static_cast<ASN1_Real*>(val);
    // temporary set new value to calculate, and reset to old value
    double temp = m_Grammar->GetRealValue();
    realVal->SetRealValue(real->value());
    realVal->WriteIntoBuffer(hex);
    realVal->SetRealValue(temp);
    return true;
  }
}

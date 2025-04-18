/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI {
  void UI_ASN1_Node_BitString::MakeWidget(QGroupBox* inBox, bool readOnly) {
    m_ParentWidget = inBox;
    inBox->setTitle(inBox->title() + " - Bit String");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    QSpacerItem* verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    binaryText = new myQTextEdit(inBox, myQTextEdit::cLineEditBinary);
    vLayValueLayout->addWidget(binaryText);
    vLayValueLayout->addItem(verticalSpacer);
    binaryText->setPlainText(m_Grammar->GetBitStringValue().c_str());
    if (readOnly)
      binaryText->setReadOnly(true);
  }

  bool UI_ASN1_Node_BitString::accept(ASN1_Object* val) {
    // must recast from non const value
    ASN1_BitString* bitStringVal = static_cast<ASN1_BitString*>(val);
    bitStringVal->SetBitStringValue(binaryText->toTextWithoutSpace().toStdString().c_str());
    return true;
  }

  bool UI_ASN1_Node_BitString::GetHexValue(ASN1_Object* val, ByteArray& hex) {
    // must recast from non const value
    ASN1_BitString* bitStringVal = static_cast<ASN1_BitString*>(val);
    // temporary set new value to calculate, and reset to old value
    QString temp = m_Grammar->GetBitStringValue().c_str();
    bitStringVal->SetBitStringValue(binaryText->toTextWithoutSpace().toStdString().c_str());
    bitStringVal->WriteIntoBuffer(hex);
    bitStringVal->SetBitStringValue(temp.toStdString().c_str());
    return true;
  }
}

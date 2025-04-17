/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI {
  void UI_ASN1_Node_ObjectID::MakeWidget(QGroupBox* inBox, bool readOnly) {
    inBox->setTitle(inBox->title() + " - Object ID");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    QSpacerItem* verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    OIDText = new myQTextEdit(inBox, myQTextEdit::cLineEditOID);
    inBox->setLayout(vLayValueLayout);
    vLayValueLayout->addWidget(OIDText);
    vLayValueLayout->addItem(verticalSpacer);
    OIDText->setPlainText(m_Grammar->GetObjectIDValue().c_str());
    if (readOnly)
      OIDText->setReadOnly(true);
  }

  bool UI_ASN1_Node_ObjectID::accept(ASN1_Object* val) {
    // must recast from non const value
    ASN1_ObjectID* oidVal = static_cast<ASN1_ObjectID*>(val);

    bool b;
    if (b = Utils::IsValidObjectID(OIDText->toPlainText().toStdString().c_str()))
      oidVal->SetObjectIDValue(OIDText->toPlainText().toStdString().c_str());
    else
      QMessageBox::warning(nullptr, "Wrong value format", "The value must be a valid Object ID.\n"
                           "Exemple: 1.25.4567.89");
    return b;
  }

  bool UI_ASN1_Node_ObjectID::GetHexValue(ASN1_Object* val, ByteArray& hex) {
    // must recast from non const value
    ASN1_ObjectID* oidVal = static_cast<ASN1_ObjectID*>(val);
    // temporary set new value to calculate, and reset to old value
    QString temp = m_Grammar->GetObjectIDValue().c_str();
    bool b;
    if (b = Utils::IsValidObjectID(OIDText->toPlainText().toStdString().c_str())) {
      oidVal->SetObjectIDValue(OIDText->toPlainText().toStdString().c_str());
      oidVal->WriteIntoBuffer(hex);
      oidVal->SetObjectIDValue(temp.toStdString().c_str());
    }
    else
      QMessageBox::warning(nullptr, "Wrong value format", "The value must be a valid Object ID."
                           "Exemple: 1.25.4567.89");
    return b;
  }
}

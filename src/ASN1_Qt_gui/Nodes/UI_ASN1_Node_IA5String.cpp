/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_IA5String::MakeWidget(QGroupBox *inBox, bool readOnly)
{
  inBox->setTitle(inBox->title() + " - IA5 String");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  str = new myQTextEdit(inBox, myQTextEdit::cLineEditIA5String);
  inBox->setLayout(vLayValueLayout);
  vLayValueLayout->addWidget(str);
  vLayValueLayout->addItem(verticalSpacer);

  str->setPlainText(m_Grammar->GetIA5StringValue().c_str());
  if (readOnly)
    str->setReadOnly(true);
}

bool UI_ASN1_Node_IA5String::accept(ASN1_Object *val)
{
  // must recast from non const value
  ASN1_IA5String *stringVal = static_cast<ASN1_IA5String *>(val);

  bool b;
  if (b = Utils::IsValidIA5String(str->toPlainText().toStdString().c_str()))
    stringVal->SetIA5StringValue(str->toPlainText().toStdString().c_str());
  else
    QMessageBox::warning(nullptr, "Wrong value format", "The string does not match IA5 String format");
  return b;
}

bool UI_ASN1_Node_IA5String::GetHexValue(ASN1_Object *val, ByteArray &hex)
{
  // must recast from non const value
  ASN1_IA5String *stringVal = static_cast<ASN1_IA5String *>(val);
  // temporary set new value to calculate, and reset to old value
  QString temp = m_Grammar->GetIA5StringValue().c_str();
  if (Utils::IsValidIA5String(str->toPlainText().toStdString().c_str()))
  {
    stringVal->SetIA5StringValue(str->toPlainText().toStdString().c_str());
    stringVal->WriteIntoBuffer(hex);
    stringVal->SetIA5StringValue(temp.toStdString().c_str());
  }
  else
    QMessageBox::warning(nullptr, "Wrong value format", "The string does not match IA5 String format");
  return true;
}
} // namespace UI

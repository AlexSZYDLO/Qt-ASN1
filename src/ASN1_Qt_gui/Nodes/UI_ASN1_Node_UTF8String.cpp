/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_UTF8String::MakeWidget(QGroupBox *inBox, bool readOnly)
{
  inBox->setTitle(inBox->title() + " - UTF8 String");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  str = new myQTextEdit(inBox, myQTextEdit::cLineEditUTF8String);
  inBox->setLayout(vLayValueLayout);
  vLayValueLayout->addWidget(str);
  vLayValueLayout->addItem(verticalSpacer);
  str->setPlainText(QString::fromUtf8(m_Grammar->GetUTF8StringValue().c_str()));
  if (readOnly)
    str->setReadOnly(true);
}

bool UI_ASN1_Node_UTF8String::accept(ASN1_Object *val)
{
  // must recast from non const value
  ASN1_UTF8String *stringVal = static_cast<ASN1_UTF8String *>(val);

  QString text = str->toPlainText();
  QByteArray s(text.toUtf8());

  bool b;
  std::string s2 = s.constData();
  if (b = Utils::IsValidUTF8String(s2))
    stringVal->SetUTF8StringValue(s2);
  else
    QMessageBox::warning(nullptr, "Wrong value format", "The string does not match UTF8 format");
  return b;
}

bool UI_ASN1_Node_UTF8String::GetHexValue(ASN1_Object *val, ByteArray &hex)
{
  // must recast from non const value
  ASN1_UTF8String *stringVal = static_cast<ASN1_UTF8String *>(val);
  // temporary set new value to calculate, and reset to old value
  QString temp = m_Grammar->GetUTF8StringValue().c_str();
  QString text = str->toPlainText();
  QByteArray s(text.toUtf8());
  std::string s2 = s.constData();

  if (Utils::IsValidUTF8String(s2))
  {
    stringVal->SetUTF8StringValue(s2);
    stringVal->WriteIntoBuffer(hex);
    stringVal->SetUTF8StringValue(temp.toStdString().c_str());
  }
  else
    QMessageBox::warning(nullptr, "Wrong value format", "The string does not match UTF8 format");
  return true;
}
} // namespace UI

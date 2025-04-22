/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_UTF8String::UI_ASN1_Converter_UTF8String(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("UTF8 String");
  utf8StringTextEdit = new myQTextEdit(valueBox, myQTextEdit::cLineEditUTF8String);
  valueLay->addWidget(utf8StringTextEdit);
  utf8StringTextEdit->setPlainText("");
  MakeUIBase();
}

void UI_ASN1_Converter_UTF8String::ConvertTypeToHex()
{
  QByteArray s(utf8StringTextEdit->toPlainText().toUtf8());
  std::string str = s.constData();
  std::string err;
  ByteArray hex;
  ASN1_UTF8String::UTF8StringToHex(str, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString().c_str());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_UTF8String::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString());
  std::string utf8str;
  std::string err;
  ASN1_UTF8String::HexToUTF8String(hex, utf8str, err);
  if (err.empty())
    utf8StringTextEdit->setPlainText(QString::fromUtf8(utf8str.c_str()));
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

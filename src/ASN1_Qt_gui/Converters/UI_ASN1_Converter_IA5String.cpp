/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_IA5String::UI_ASN1_Converter_IA5String(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("IA5 String");
  ia5StringTextEdit = new myQTextEdit(valueBox, myQTextEdit::cLineEditIA5String);
  valueLay->addWidget(ia5StringTextEdit);
  ia5StringTextEdit->setPlainText("");
  MakeUIBase();
}

void UI_ASN1_Converter_IA5String::ConvertTypeToHex()
{
  std::string str = ia5StringTextEdit->toPlainText().toStdString();
  std::string err;
  ByteArray hex;
  ASN1_IA5String::ToHex(str, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString().c_str());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_IA5String::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString());
  std::string ia5str;
  std::string err;
  ASN1_IA5String::FromHex(hex, ia5str, err);
  if (err.empty())
    ia5StringTextEdit->setPlainText(ia5str.c_str());
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

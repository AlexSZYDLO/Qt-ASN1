/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_OctetString::UI_ASN1_Converter_OctetString(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("Octet String");
  octetStringTextEdit = new myQTextEdit(valueBox, myQTextEdit::cLineEditHexa);
  valueLay->addWidget(octetStringTextEdit);
  octetStringTextEdit->setPlainText("");

  MakeUIBase();
}

void UI_ASN1_Converter_OctetString::ConvertTypeToHex()
{
  ByteArray val(octetStringTextEdit->toTextWithoutSpace().toStdString());
  std::string err;
  ByteArray hex;
  ASN1_OctetString::ToHex(val, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString().c_str());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_OctetString::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString());
  ByteArray val;
  std::string err;
  ASN1_OctetString::FromHex(hex, val, err);
  if (err.empty())
    octetStringTextEdit->setPlainText(val.GetString().c_str());
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

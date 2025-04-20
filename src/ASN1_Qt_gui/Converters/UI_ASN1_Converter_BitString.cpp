/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_BitString::UI_ASN1_Converter_BitString(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("Bit String");
  binaryTextEdit = new myQTextEdit(valueBox, myQTextEdit::cLineEditBinary);
  valueLay->addWidget(binaryTextEdit);
  //valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

  binaryTextEdit->setPlainText("");

  MakeUIBase();
}

void UI_ASN1_Converter_BitString::ConvertTypeToHex()
{
  std::string str = binaryTextEdit->toTextWithoutSpace().toStdString().c_str();
  std::string err;
  ByteArray hex;
  ASN1_BitString::BitStringToHex(str, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_BitString::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString().c_str());
  std::string bitstring;
  std::string err;
  ASN1_BitString::HexToBitString(hex, bitstring, err);
  if (err.empty())
    binaryTextEdit->setPlainText(bitstring.c_str());
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_Boolean::UI_ASN1_Converter_Boolean(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("Bit String");
  booleanCheckBox = new QCheckBox("Boolean value", valueBox);
  valueLay->addWidget(booleanCheckBox);
  valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

  booleanCheckBox->setChecked(false);
  hexaTextEdit->setPlainText("00");

  MakeUIBase();
}

void UI_ASN1_Converter_Boolean::ConvertTypeToHex()
{
  bool b = booleanCheckBox->isChecked();
  std::string err;
  ByteArray hex;
  ASN1_Boolean::BooleanToHex(b, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_Boolean::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString().c_str());
  bool b;
  std::string err;
  ASN1_Boolean::HexToBoolean(hex, b, err);
  if (err.empty())
    booleanCheckBox->setChecked(b);
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

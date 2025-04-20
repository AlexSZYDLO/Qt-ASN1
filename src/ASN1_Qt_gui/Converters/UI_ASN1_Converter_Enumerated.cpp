/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_Enumerated::UI_ASN1_Converter_Enumerated(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("Enumerated");
  enumeratedSpinBox = new QSpinBox(valueBox);
  enumeratedSpinBox->setMinimum(std::numeric_limits<int>::min());
  enumeratedSpinBox->setMaximum(std::numeric_limits<int>::max());
  valueLay->addWidget(enumeratedSpinBox);
  valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

  enumeratedSpinBox->setValue(0);

  MakeUIBase();
}

void UI_ASN1_Converter_Enumerated::ConvertTypeToHex()
{
  int val = enumeratedSpinBox->value();
  std::string err;
  ByteArray hex;
  ASN1_Enumerated::EnumeratedToHex(val, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_Enumerated::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString().c_str());
  int val;
  std::string err;
  ASN1_Enumerated::HexToEnumerated(hex, val, err);
  if (err.empty())
    enumeratedSpinBox->setValue(val);
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

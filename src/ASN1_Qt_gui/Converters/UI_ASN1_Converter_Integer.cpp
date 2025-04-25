/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_Integer::UI_ASN1_Converter_Integer(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("Integer");
  integerSpinBox = new QSpinBox(valueBox);
  integerSpinBox->setMinimum(std::numeric_limits<int>::min());
  integerSpinBox->setMaximum(std::numeric_limits<int>::max());
  valueLay->addWidget(integerSpinBox);
  valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

  integerSpinBox->setValue(0);

  MakeUIBase();
}

void UI_ASN1_Converter_Integer::ConvertTypeToHex()
{
  int val = integerSpinBox->value();
  std::string err;
  ByteArray hex;
  ASN1_Integer::ToHex(val, hex, err);
  if (err.empty())
    hexaTextEdit->setPlainText(hex.GetString().c_str());
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_Integer::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString());
  int val;
  std::string err;
  ASN1_Integer::FromHex(hex, val, err);
  if (err.empty())
    integerSpinBox->setValue(val);
  errorLineEdit->setText(err.c_str());
}
} // namespace UI

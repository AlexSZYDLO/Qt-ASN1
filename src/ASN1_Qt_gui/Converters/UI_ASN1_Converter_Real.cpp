/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"
#include <limits>

namespace UI {
  UI_ASN1_Converter_Real::UI_ASN1_Converter_Real(QWidget* parent) : UI_Converter(parent) {
    valueBox->setTitle("Real");
    realSpinBox = new QDoubleSpinBox(valueBox);
    realSpinBox->setMinimum(std::numeric_limits<double>::lowest());
    realSpinBox->setMaximum(std::numeric_limits<double>::max());
    realSpinBox->setDecimals(10);
    valueLay->addWidget(realSpinBox);
    valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    realSpinBox->setValue(0.0);

    MakeUIBase();
  }

  void UI_ASN1_Converter_Real::ConvertTypeToHex() {
    double val = realSpinBox->value();
    std::string err;
    ByteArray hex;
    ASN1_Real::RealToHex(val, hex, err);
    if (err.empty())
      hexaTextEdit->setPlainText(hex.GetString());
    errorLineEdit->setText(err.c_str());
  }

  void UI_ASN1_Converter_Real::ConvertHexToType() {
    ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString().c_str());
    double val;
    std::string err;
    ASN1_Real::HexToReal(hex, val, err);
    if (err.empty())
      realSpinBox->setValue(val);
    errorLineEdit->setText(err.c_str());
  }
}

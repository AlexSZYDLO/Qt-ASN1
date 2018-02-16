/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"
#include <QRegExp>

namespace UI {
  UI_ASN1_Converter_ObjectID::UI_ASN1_Converter_ObjectID(QWidget* parent) : UI_Converter(parent) {
    valueBox->setTitle("Object ID");
    oidTextEdit = new myQTextEdit(valueBox, myQTextEdit::cLineEditOID);
    valueLay->addWidget(oidTextEdit);
    valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    oidTextEdit->setPlainText("");

    MakeUIBase();
  }

  void UI_ASN1_Converter_ObjectID::ConvertTypeToHex() {
    ByteArray hex;
    std::string oid, err;
    oid = oidTextEdit->toPlainText().toStdString();
    ASN1_ObjectID::ObjectIDToHex(oid, hex, err);
    if (err.empty()) {
      hexaTextEdit->setPlainText(hex.GetString());
    }
    errorLineEdit->setText(err.c_str());
  }

  void UI_ASN1_Converter_ObjectID::ConvertHexToType() {
    ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString().c_str());
    std::string oid;
    std::string err;
    ASN1_ObjectID::HexToObjectID(hex, oid, err);
    if (err.empty())
      oidTextEdit->setPlainText(oid.c_str());
    errorLineEdit->setText(err.c_str());
  }
}

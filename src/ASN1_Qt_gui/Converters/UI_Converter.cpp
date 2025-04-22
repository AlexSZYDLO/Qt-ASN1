/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"
#include <QVBoxLayout>

namespace UI
{
void UI_Converter::MakeUIBase()
{
  this->resize(400, 300);
  QVBoxLayout *lay = new QVBoxLayout(this);

  QGroupBox *HexBox = new QGroupBox(this);
  HexBox->setObjectName("valueBox");
  HexBox->setTitle("Hexadecimal");
  QVBoxLayout *layHexBox = new QVBoxLayout(HexBox);

  layHexBox->addWidget(hexaTextEdit);

  QString p = ":/img/icon_set_2/";
  ClickableLabel *buttonTypeToHex = MakeClickableLabel("commonButton", "To Hex", p + "up.png", this);
  ClickableLabel *buttonHexToType = MakeClickableLabel("commonButton", "From Hex", p + "down.png", this);

  QHBoxLayout *buttonLay = new QHBoxLayout();
  buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
  buttonLay->addWidget(buttonTypeToHex);
  buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
  buttonLay->addWidget(buttonHexToType);
  buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

  errorLineEdit->setReadOnly(true);

  QHBoxLayout *errLay = new QHBoxLayout();
  errLay->addWidget(new QLabel("Error:", this));
  errLay->addWidget(errorLineEdit);

  lay->addWidget(HexBox);
  lay->addLayout(buttonLay);
  lay->addWidget(valueBox);
  lay->addLayout(errLay);

  QObject::connect(buttonHexToType, SIGNAL(clicked(bool)), this, SLOT(ConvertHexToType_base()));
  QObject::connect(buttonTypeToHex, SIGNAL(clicked(bool)), this, SLOT(ConvertTypeToHex()));
}

void UI_Converter::ConvertHexToType_base()
{
  if (hexaTextEdit->CorrectOddHexa())
    ConvertHexToType();
}

UI_Converter::UI_Converter(QWidget *parent)
    : ValueDialog(parent)
{
  valueBox = new QGroupBox(this);
  valueBox->setObjectName("valueBox");
  valueLay = new QVBoxLayout(valueBox);
  hexaTextEdit = new myQTextEdit(this, myQTextEdit::cLineEditHexa);
  errorLineEdit = new QLineEdit(this);
}

UI_Converter::~UI_Converter()
{
}
} // namespace UI

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Converter.h"

namespace UI
{
UI_ASN1_Converter_UTCTime::UI_ASN1_Converter_UTCTime(QWidget *parent)
    : UI_Converter(parent)
{
  valueBox->setTitle("UTC Time");

  dateTimeEdit = new QDateTimeEdit(valueBox);
  zoneHoursSpinBox = new QSpinBox(valueBox);
  zoneMinutesSpinBox = new QSpinBox(valueBox);
  zoneSignComboBox = new QComboBox(valueBox);

  QHBoxLayout *hLayValueLayout = new QHBoxLayout();
  hLayValueLayout->addWidget(new QLabel("Zone:", this));
  hLayValueLayout->addWidget(zoneSignComboBox);
  hLayValueLayout->addWidget(new QLabel("hours:", this));
  hLayValueLayout->addWidget(zoneHoursSpinBox);
  hLayValueLayout->addWidget(new QLabel("minutes:", this));
  hLayValueLayout->addWidget(zoneMinutesSpinBox);
  hLayValueLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
  valueLay->addWidget(dateTimeEdit);
  valueLay->addLayout(hLayValueLayout);
  valueLay->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));

  QObject::connect(zoneSignComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(signChanged()));

  zoneHoursSpinBox->setMaximum(12);
  zoneMinutesSpinBox->setMaximum(60);
  zoneSignComboBox->addItems({"GMT", "+", "-"});

  QDate date(2000, 1, 1);
  QTime time(0, 0, 0);
  QDateTime dt(date, time);
  dateTimeEdit->setDisplayFormat("yy MMM dd - hh:mm:ss");
  dateTimeEdit->setDateTime(dt);
  zoneHoursSpinBox->setValue(0);
  zoneMinutesSpinBox->setValue(0);
  zoneSignComboBox->setCurrentText(signToString(Utils::cGMT));

  MakeUIBase();
}

void UI_ASN1_Converter_UTCTime::ConvertTypeToHex()
{
  ByteArray hex;
  std::string UTCTimeStringTmp, err;
  QString year = QString::number(dateTimeEdit->date().year());
  year = year.right(2);
  Utils::ValuesToUTCTime(year.toInt(),
                         dateTimeEdit->date().month(),
                         dateTimeEdit->date().day(),
                         dateTimeEdit->time().hour(),
                         dateTimeEdit->time().minute(),
                         dateTimeEdit->time().second(),
                         stringToSign(zoneSignComboBox->currentText()),
                         zoneHoursSpinBox->value(),
                         zoneMinutesSpinBox->value(),
                         UTCTimeStringTmp,
                         err);
  if (err.empty())
  {
    ASN1_UTCTime::UTCTimeToHex(UTCTimeStringTmp, hex, err);
    if (err.empty())
    {
      hexaTextEdit->setPlainText(hex.GetString());
    }
  }
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_UTCTime::ConvertHexToType()
{
  ByteArray hex(hexaTextEdit->toTextWithoutSpace().toStdString().c_str());

  std::string UTCTimeString, err;
  ASN1_UTCTime::HexToUTCTime(hex, UTCTimeString, err);
  if (err.empty())
  {
    int y, m, d, h, min, s, zh, zm;
    Utils::eUTCTimeZone z;
    Utils::UTCTimeToValues(UTCTimeString, y, m, d, h, min, s, z, zh, zm, err);
    if (err.empty())
    {
      // add 2000 to year, but will stay hidden and will not be encoded (QDate limitation)
      QDate date(y + 2000, m, d);
      QTime time(h, min, s);
      QDateTime dt(date, time);
      dateTimeEdit->setDateTime(dt);
      zoneHoursSpinBox->setValue(zh);
      zoneMinutesSpinBox->setValue(zm);
      zoneSignComboBox->setCurrentText(signToString(z));
    }
  }
  errorLineEdit->setText(err.c_str());
}

void UI_ASN1_Converter_UTCTime::signChanged()
{
  if (zoneSignComboBox->currentText() == "GMT")
  {
    zoneHoursSpinBox->setEnabled(false);
    zoneMinutesSpinBox->setEnabled(false);
  }
  else
  {
    zoneHoursSpinBox->setEnabled(true);
    zoneMinutesSpinBox->setEnabled(true);
  }
}

QString UI_ASN1_Converter_UTCTime::signToString(Utils::eUTCTimeZone sign)
{
  if (sign == Utils::cPlus)
    return "+";
  if (sign == Utils::cMinus)
    return "-";
  return "GMT";
}

Utils::eUTCTimeZone UI_ASN1_Converter_UTCTime::stringToSign(QString str)
{
  if (str == "+")
    return Utils::cPlus;
  if (str == "-")
    return Utils::cMinus;
  return Utils::cGMT;
}

} // namespace UI

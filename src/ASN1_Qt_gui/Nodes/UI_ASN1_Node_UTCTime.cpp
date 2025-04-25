/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
void UI_ASN1_Node_UTCTime::MakeWidget(QGroupBox *inBox, bool readOnly)
{
  inBox->setTitle(inBox->title() + " - UTC Time");
  QVBoxLayout *vLayValueLayout = new QVBoxLayout(inBox);
  QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  edit = new QDateTimeEdit(inBox);
  Zhours = new QSpinBox(inBox);
  ZMin = new QSpinBox(inBox);
  ZSign = new QComboBox(inBox);

  inBox->setLayout(vLayValueLayout);
  QHBoxLayout *hLayValueLayout = new QHBoxLayout();
  hLayValueLayout->addWidget(new QLabel("Zone:", inBox));
  hLayValueLayout->addWidget(ZSign);
  hLayValueLayout->addWidget(new QLabel("hours:", inBox));
  hLayValueLayout->addWidget(Zhours);
  hLayValueLayout->addWidget(new QLabel("minutes:", inBox));
  hLayValueLayout->addWidget(ZMin);
  hLayValueLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
  vLayValueLayout->addWidget(edit);
  vLayValueLayout->addLayout(hLayValueLayout);
  vLayValueLayout->addItem(verticalSpacer);

  QObject::connect(ZSign, SIGNAL(currentTextChanged(QString)), this, SLOT(signChanged()));

  Zhours->setMaximum(12);
  ZMin->setMaximum(60);
  ZSign->addItems({"GMT", "+", "-"});

  int y, m, d, h, min, s, zh, zm;
  Utils::eUTCTimeZone z;
  std::string UTCTimeString, error;
  UTCTimeString = m_Grammar->GetValue();
  Utils::UTCTimeToValues(UTCTimeString, y, m, d, h, min, s, z, zh, zm, error);

  // add 2000 to year, but will stay hidden and will not be encoded (QDate limitation)
  QDate date(y + 2000, m, d);
  QTime time(h, min, s);
  QDateTime dt(date, time);
  edit->setDisplayFormat("yy MMM dd - hh:mm:ss");
  edit->setDateTime(dt);
  Zhours->setValue(zh);
  ZMin->setValue(zm);
  ZSign->setCurrentText(signToString(z));

  if (readOnly)
  {
    edit->setReadOnly(true);
    Zhours->setReadOnly(true);
    ZMin->setReadOnly(true);
    ZSign->setEnabled(false);
  }
}

bool UI_ASN1_Node_UTCTime::accept(ASN1_Object *val)
{
  // must recast from non const value
  ASN1_UTCTime *timeVal = static_cast<ASN1_UTCTime *>(val);
  std::string UTCTimeStringTmp, errorBuffer;
  QString year = QString::number(edit->date().year());
  year = year.right(2);
  Utils::ValuesToUTCTime(year.toInt(),
                         edit->date().month(),
                         edit->date().day(),
                         edit->time().hour(),
                         edit->time().minute(),
                         edit->time().second(),
                         stringToSign(ZSign->currentText()),
                         Zhours->value(),
                         ZMin->value(),
                         UTCTimeStringTmp,
                         errorBuffer);
  timeVal->SetValue(UTCTimeStringTmp);
  return true;
}

bool UI_ASN1_Node_UTCTime::GetHexValue(ASN1_Object *val, ByteArray &hex)
{
  // must recast from non const value
  ASN1_UTCTime *timeVal = static_cast<ASN1_UTCTime *>(val);
  // temporary set new value to calculate, and reset to old value

  std::string UTCTimeString, UTCTimeStringTmp, errorBuffer;

  UTCTimeString = m_Grammar->GetValue();

  Utils::ValuesToUTCTime(edit->date().year() - 2000,
                         edit->date().month(),
                         edit->date().day(),
                         edit->time().hour(),
                         edit->time().minute(),
                         edit->time().second(),
                         stringToSign(ZSign->currentText()),
                         Zhours->value(),
                         ZMin->value(),
                         UTCTimeStringTmp,
                         errorBuffer);
  timeVal->SetValue(UTCTimeStringTmp);
  timeVal->WriteIntoBuffer(hex);
  timeVal->SetValue(UTCTimeString);
  return true;
}

void UI_ASN1_Node_UTCTime::signChanged()
{
  if (ZSign->currentText() == "GMT")
  {
    Zhours->setEnabled(false);
    ZMin->setEnabled(false);
  }
  else
  {
    Zhours->setEnabled(true);
    ZMin->setEnabled(true);
  }
}

QString UI_ASN1_Node_UTCTime::signToString(Utils::eUTCTimeZone sign)
{
  if (sign == Utils::cPlus)
    return "+";
  if (sign == Utils::cMinus)
    return "-";
  return "GMT";
}

Utils::eUTCTimeZone UI_ASN1_Node_UTCTime::stringToSign(QString str)
{
  if (str == "+")
    return Utils::cPlus;
  if (str == "-")
    return Utils::cMinus;
  return Utils::cGMT;
}

} // namespace UI

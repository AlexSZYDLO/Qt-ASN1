/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "ASN1_includes.h"
#include "Widgets/CustomWidgets.h"

//enum eConverterNodeKind {
//  cBoolean, cBitString, cEnumerated, cIA5String, cInteger, cObjectID, cOctetString, cReal, cUTCTime, cUTF8String
//};

#ifndef UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS
#define UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(name)                                                                     \
public:                                                                                                                \
  UI_ASN1_Converter_##name(QWidget *parent = 0);                                                                       \
public slots:                                                                                                          \
  virtual void ConvertTypeToHex() override;                                                                            \
  virtual void ConvertHexToType() override;
#endif

namespace UI
{
class UI_Converter : public ValueDialog
{
  Q_OBJECT
public:
  explicit UI_Converter(QWidget *parent = 0);
  virtual ~UI_Converter();

protected:
  void MakeUIBase();
  QGroupBox *valueBox;
  QVBoxLayout *valueLay;
  myQTextEdit *hexaTextEdit;
  QLineEdit *errorLineEdit;

public slots:
  void ConvertHexToType_base();
  virtual void ConvertTypeToHex() = 0;
  virtual void ConvertHexToType() = 0;
};

class UI_ASN1_Converter_BitString : public UI_Converter
{
  myQTextEdit *binaryTextEdit;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(BitString)
};

class UI_ASN1_Converter_Boolean : public UI_Converter
{
  QCheckBox *booleanCheckBox;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(Boolean)
};

class UI_ASN1_Converter_IA5String : public UI_Converter
{
  myQTextEdit *ia5StringTextEdit;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(IA5String)
};

class UI_ASN1_Converter_Integer : public UI_Converter
{
  QSpinBox *integerSpinBox;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(Integer)
};

class UI_ASN1_Converter_Enumerated : public UI_Converter
{
  QSpinBox *enumeratedSpinBox;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(Enumerated)
};

class UI_ASN1_Converter_OctetString : public UI_Converter
{
  myQTextEdit *octetStringTextEdit;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(OctetString)
};

class UI_ASN1_Converter_ObjectID : public UI_Converter
{
  myQTextEdit *oidTextEdit;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(ObjectID)
};

class UI_ASN1_Converter_Real : public UI_Converter
{
  QDoubleSpinBox *realSpinBox;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(Real)
};

class UI_ASN1_Converter_UTCTime : public UI_Converter
{
  Q_OBJECT
  QDateTimeEdit *dateTimeEdit;
  QSpinBox *zoneHoursSpinBox;
  QSpinBox *zoneMinutesSpinBox;
  QComboBox *zoneSignComboBox;

  QString signToString(Utils::eUTCTimeZone sign);
  Utils::eUTCTimeZone stringToSign(QString str);
public slots:
  void signChanged();
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(UTCTime)
};

class UI_ASN1_Converter_UTF8String : public UI_Converter
{
  myQTextEdit *utf8StringTextEdit;
  UI_CONVERTER_COMMON_PUBLIC_FUNCTIONS(UTF8String)
};

} // namespace UI

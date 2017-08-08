/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"

// -------- BITSTRING --------
class ASN1_Script_BitString : public ASN1_Script_Template_Base<ASN1_BitString> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  QString getBitStringValue() const;
  void setBitStringValue(const QString& val);
};

// -------- BOOLEAN --------
class ASN1_Script_Boolean : public ASN1_Script_Template_Base<ASN1_Boolean> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  bool getBooleanValue() const;
  void setBooleanValue(bool val);
};

// -------- ENUMERATED --------
class ASN1_Script_Enumerated : public ASN1_Script_Template_Base<ASN1_Enumerated> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  int getEnumeratedValue() const;
  void setEnumeratedValue(int val);
};

// -------- IA5STRING --------
class ASN1_Script_IA5String : public ASN1_Script_Template_Base<ASN1_IA5String> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  QString getIA5StringValue() const;
  void setIA5StringValue(const QString& val);
};

// -------- INTEGER --------
class ASN1_Script_Integer : public ASN1_Script_Template_Base<ASN1_Integer> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  int getIntegerValue() const;
  void setIntegerValue(int val);
};

// -------- NULL --------
class ASN1_Script_Null : public ASN1_Script_Template_Base<ASN1_Null> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;
};

// -------- OBJECTID --------
class ASN1_Script_ObjectID : public ASN1_Script_Template_Base<ASN1_ObjectID> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  QString getObjectIDValue() const;
  void setObjectIDValue(const QString& val);
};

// -------- OCTETSTRING --------
class ASN1_Script_OctetString : public ASN1_Script_Template_Base<ASN1_OctetString> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  QString getOctetStringValue() const;
  void setOctetStringValue(const QString& val);
};

// -------- REAL --------
class ASN1_Script_Real : public ASN1_Script_Template_Base<ASN1_Real> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  double getRealValue() const;
  void setRealValue(double val);
};

// -------- UTCTIME --------
class ASN1_Script_UTCTime : public ASN1_Script_Template_Base<ASN1_UTCTime> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public:
  enum TimeZoneSign {
    Minus,
    Plus,
    GMT
  };
  Q_ENUMS(TimeZoneSign)

 public slots:
  QString getUTCTimeValue() const;
  void setUTCTimeValue(const QString& val);

  void setUTCTimeValue(int year, int month, int day, int hours, int minutes, int seconds, TimeZoneSign TZSign, int TZHours, int TZMinutes);
  void getUTCTimeValue(int& year, int& month, int& day, int& hours, int& minutes, int& seconds, TimeZoneSign& TZSign, int& TZHours, int& TZMinutes) const;
};

// -------- UTF8STRING --------
class ASN1_Script_UTF8String : public ASN1_Script_Template_Base<ASN1_UTF8String> {
  Q_OBJECT
  using ASN1_Script_Template_Base::ASN1_Script_Template_Base;

 public slots:
  QString getUTF8StringValue() const;
  void setUTF8StringValue(const QString& val);
};

Q_DECLARE_METATYPE(ASN1_Script_BitString*)
Q_DECLARE_METATYPE(ASN1_Script_Boolean*)
Q_DECLARE_METATYPE(ASN1_Script_Enumerated*)
Q_DECLARE_METATYPE(ASN1_Script_IA5String*)
Q_DECLARE_METATYPE(ASN1_Script_Integer*)
Q_DECLARE_METATYPE(ASN1_Script_Null*)
Q_DECLARE_METATYPE(ASN1_Script_ObjectID*)
Q_DECLARE_METATYPE(ASN1_Script_OctetString*)
Q_DECLARE_METATYPE(ASN1_Script_Real*)
Q_DECLARE_METATYPE(ASN1_Script_UTCTime*)
Q_DECLARE_METATYPE(ASN1_Script_UTCTime::TimeZoneSign)
Q_DECLARE_METATYPE(ASN1_Script_UTF8String*)


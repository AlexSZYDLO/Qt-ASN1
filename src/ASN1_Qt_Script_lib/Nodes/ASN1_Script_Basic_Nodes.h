/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Script_Node.h"

#define NODE_HEADER(TYPE) \
  Q_OBJECT \
 public: \
  Q_INVOKABLE ASN1_Script_##TYPE (const QString& name = "", const QString& tag = "", bool optional = false, bool explicitTag = false, \
    ASN1_Script_##TYPE* defaultValue = nullptr);

// -------- BITSTRING --------
class ASN1_Script_BitString : public ASN1_Script_Template_Base<ASN1_BitString> {
  NODE_HEADER(BitString)
 public slots:
  QString getBitStringValue() const;
  void setBitStringValue(const QString& val);
};

// -------- BOOLEAN --------
class ASN1_Script_Boolean : public ASN1_Script_Template_Base<ASN1_Boolean> {
  NODE_HEADER(Boolean)
 public slots:
  bool getBooleanValue() const;
  void setBooleanValue(bool val);
};

// -------- ENUMERATED --------
class ASN1_Script_Enumerated : public ASN1_Script_Template_Base<ASN1_Enumerated> {
  NODE_HEADER(Enumerated)
 public slots:
  int getEnumeratedValue() const;
  void setEnumeratedValue(int val);
};

// -------- IA5STRING --------
class ASN1_Script_IA5String : public ASN1_Script_Template_Base<ASN1_IA5String> {
  NODE_HEADER(IA5String)
 public slots:
  QString getIA5StringValue() const;
  void setIA5StringValue(const QString& val);
};

// -------- INTEGER --------
class ASN1_Script_Integer : public ASN1_Script_Template_Base<ASN1_Integer> {
  NODE_HEADER(Integer)
 public slots:
  int getIntegerValue() const;
  void setIntegerValue(int val);
};

// -------- NULL --------
class ASN1_Script_Null : public ASN1_Script_Template_Base<ASN1_Null> {
  NODE_HEADER(Null)
};

// -------- OBJECTID --------
class ASN1_Script_ObjectID : public ASN1_Script_Template_Base<ASN1_ObjectID> {
  NODE_HEADER(ObjectID)
 public slots:
  QString getObjectIDValue() const;
  void setObjectIDValue(const QString& val);
};

// -------- OCTETSTRING --------
class ASN1_Script_OctetString : public ASN1_Script_Template_Base<ASN1_OctetString> {
  NODE_HEADER(OctetString)
 public slots:
  QString getOctetStringValue() const;
  void setOctetStringValue(const QString& val);
};

// -------- REAL --------
class ASN1_Script_Real : public ASN1_Script_Template_Base<ASN1_Real> {
  NODE_HEADER(Real)
 public slots:
  double getRealValue() const;
  void setRealValue(double val);
};

// -------- UTCTIME --------
class ASN1_Script_UTCTime : public ASN1_Script_Template_Base<ASN1_UTCTime> {
  NODE_HEADER(UTCTime)

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
  NODE_HEADER(UTF8String)
 public slots:
  QString getUTF8StringValue() const;
  void setUTF8StringValue(const QString& val);
};

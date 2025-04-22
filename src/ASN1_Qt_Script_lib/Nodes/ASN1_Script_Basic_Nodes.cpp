/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_Basic_Nodes.h"

#define CTOR_IMPL(TYPE)                                                                                                \
  ASN1_Script_##TYPE::ASN1_Script_##TYPE(                                                                              \
      const QString &name, const QString &tag, bool optional, bool explicitTag, ASN1_Script_##TYPE *defaultValue)      \
      : ASN1_Script_Template_Base<ASN1_##TYPE>(name, tag, optional, explicitTag, defaultValue)                         \
  {                                                                                                                    \
  }

// -------- BITSTRING --------
CTOR_IMPL(BitString)

QString ASN1_Script_BitString::getBitStringValue() const
{
  return QString(m_GrammarSpe->GetBitStringValue().c_str());
}
void ASN1_Script_BitString::setBitStringValue(const QString &val)
{
  m_GrammarSpe->SetBitStringValue(val.toStdString().c_str());
}

// -------- BOOLEAN --------
CTOR_IMPL(Boolean)

bool ASN1_Script_Boolean::getBooleanValue() const
{
  return m_GrammarSpe->GetBooleanValue();
}
void ASN1_Script_Boolean::setBooleanValue(bool val)
{
  m_GrammarSpe->SetBooleanValue(val);
}

// -------- ENUMERATED --------
CTOR_IMPL(Enumerated)

int ASN1_Script_Enumerated::getEnumeratedValue() const
{
  return m_GrammarSpe->GetEnumeratedValue();
}
void ASN1_Script_Enumerated::setEnumeratedValue(int val)
{
  m_GrammarSpe->SetEnumeratedValue(val);
}

// -------- IA5STRING --------
CTOR_IMPL(IA5String)

QString ASN1_Script_IA5String::getIA5StringValue() const
{
  return QString(m_GrammarSpe->GetIA5StringValue().c_str());
}
void ASN1_Script_IA5String::setIA5StringValue(const QString &val)
{
  m_GrammarSpe->SetIA5StringValue(val.toStdString().c_str());
}

// -------- INTEGER --------
CTOR_IMPL(Integer)

int ASN1_Script_Integer::getIntegerValue() const
{
  return m_GrammarSpe->GetIntegerValue();
}
void ASN1_Script_Integer::setIntegerValue(int val)
{
  m_GrammarSpe->SetIntegerValue(val);
}

// -------- NULL --------
CTOR_IMPL(Null)

// -------- OBJECTID --------
CTOR_IMPL(ObjectID)

QString ASN1_Script_ObjectID::getObjectIDValue() const
{
  return QString(m_GrammarSpe->GetObjectIDValue().c_str());
}
void ASN1_Script_ObjectID::setObjectIDValue(const QString &val)
{
  m_GrammarSpe->SetObjectIDValue(val.toStdString().c_str());
}

// -------- OCTETSTRING --------
CTOR_IMPL(OctetString)

QString ASN1_Script_OctetString::getOctetStringValue() const
{
  return QString(m_GrammarSpe->GetOctetStringValue().GetString());
}
void ASN1_Script_OctetString::setOctetStringValue(const QString &val)
{
  m_GrammarSpe->SetOctetStringValue(ByteArray(val.toStdString().c_str()));
}

// -------- REAL --------
CTOR_IMPL(Real)

double ASN1_Script_Real::getRealValue() const
{
  return m_GrammarSpe->GetRealValue();
}
void ASN1_Script_Real::setRealValue(double val)
{
  m_GrammarSpe->SetRealValue(val);
}

// -------- UTCTIME --------
CTOR_IMPL(UTCTime)

ASN1_Script_UTCTime::TimeZoneSign ConvertGrammarToSelfEnum(Utils::eUTCTimeZone zone)
{
  if (zone == Utils::cPlus)
    return ASN1_Script_UTCTime::Plus;
  if (zone == Utils::cMinus)
    return ASN1_Script_UTCTime::Minus;
  return ASN1_Script_UTCTime::GMT;
}

Utils::eUTCTimeZone ConvertSelfToGrammarEnum(ASN1_Script_UTCTime::TimeZoneSign zone)
{
  if (zone == ASN1_Script_UTCTime::Plus)
    return Utils::cPlus;
  if (zone == ASN1_Script_UTCTime::Minus)
    return Utils::cMinus;
  return Utils::cGMT;
}

QString ASN1_Script_UTCTime::getUTCTimeValue() const
{
  return QString(m_GrammarSpe->GetUTCTimeValue().c_str());
}
void ASN1_Script_UTCTime::setUTCTimeValue(const QString &val)
{
  m_GrammarSpe->SetUTCTimeValue(val.toStdString().c_str());
}

void ASN1_Script_UTCTime::setUTCTimeValue(int year,
                                          int month,
                                          int day,
                                          int hours,
                                          int minutes,
                                          int seconds,
                                          TimeZoneSign TZSign,
                                          int TZHours,
                                          int TZMinutes)
{
  std::string str, err;
  Utils::ValuesToUTCTime(
      year, month, day, hours, minutes, seconds, ConvertSelfToGrammarEnum(TZSign), TZHours, TZMinutes, str, err);
  m_GrammarSpe->SetUTCTimeValue(str);
}

void ASN1_Script_UTCTime::getUTCTimeValue(int &year,
                                          int &month,
                                          int &day,
                                          int &hours,
                                          int &minutes,
                                          int &seconds,
                                          TimeZoneSign &TZSign,
                                          int &TZHours,
                                          int &TZMinutes) const
{
  Utils::eUTCTimeZone tempZone;
  std::string str, err;
  str = m_GrammarSpe->GetUTCTimeValue().c_str();
  Utils::UTCTimeToValues(
      m_GrammarSpe->GetUTCTimeValue().c_str(), year, month, day, hours, minutes, seconds, tempZone, TZHours, TZMinutes, err);
  TZSign = ConvertGrammarToSelfEnum(tempZone);
}

// -------- UTF8STRING --------
CTOR_IMPL(UTF8String)

QString ASN1_Script_UTF8String::getUTF8StringValue() const
{
  return QString(m_GrammarSpe->GetUTF8StringValue().c_str());
}
void ASN1_Script_UTF8String::setUTF8StringValue(const QString &val)
{
  m_GrammarSpe->SetUTF8StringValue(val.toStdString().c_str());
}

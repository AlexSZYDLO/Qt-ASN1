/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "UI_ASN1_Value_Node_Base.h"

namespace UI
{
// ABSTRACT BASE VALUE
class UI_ASN1_ValueMain : public ValueDialog
{
  Q_OBJECT
public:
  explicit UI_ASN1_ValueMain(const ASN1_Object *val, QWidget *parent = 0);
  virtual ~UI_ASN1_ValueMain() = 0;

public slots:
  virtual void reject() override;
  virtual void ShowHexaValue() const;
  void ShowDefaultValue();
  void ShowParentValue();

  void UIShowValue(ByteArray hex) const;

protected:
  const ASN1_Object *value;
  UI_ASN1_Value_Node *valueEdit;

  QVBoxLayout *mainLayout;
  QCheckBox *checkBox_IgnoreValue;
  QLineEdit *lineEdit_Description;
  QGroupBox *groupBox_value;
};

// EDITABLE VALUE
class UI_ASN1_ValueMain_Editable : public UI_ASN1_ValueMain
{
  Q_OBJECT
public:
  explicit UI_ASN1_ValueMain_Editable(ASN1_Object *val, QWidget *parent = 0);
  virtual ~UI_ASN1_ValueMain_Editable()
  {
  }

public slots:
  virtual void accept() override;
  virtual void ShowHexaValue() const override;

protected:
  ASN1_Object *value;
};

// READ ONLY VALUE
class UI_ASN1_ValueMain_ReadOnly : public UI_ASN1_ValueMain
{
  Q_OBJECT
public:
  explicit UI_ASN1_ValueMain_ReadOnly(const ASN1_Object *val, QWidget *parent = 0);
  virtual ~UI_ASN1_ValueMain_ReadOnly()
  {
  }
};
} // namespace UI

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Main.h"
#include "UI_ASN1_Value_Node_Base.h"

using namespace Utils;

// UI creation functions
namespace UI {
  namespace UI_Main {
    void MakeNameLayout(QGroupBox* groupBox_Grammar, QVBoxLayout* vLayGrammarLayout, const ASN1_Object* val) {
      QHBoxLayout* hLay_NameLayout = new QHBoxLayout();
      QLabel* label_Name = new QLabel(groupBox_Grammar);
      QLineEdit* lineEdit_Name = new QLineEdit(groupBox_Grammar);

      label_Name->setText(QApplication::translate("UI_ASN1_ValueMain", "Name", 0));
      lineEdit_Name->setText(val->GetName().c_str());
      lineEdit_Name->setReadOnly(true);

      hLay_NameLayout->addWidget(label_Name);
      hLay_NameLayout->addWidget(lineEdit_Name);
      vLayGrammarLayout->addLayout(hLay_NameLayout);
    }

    void MakeTagLayout(QGroupBox* groupBox_Grammar, QVBoxLayout* vLayGrammarLayout, const ASN1_Object* val) {
      QHBoxLayout* hLay_TagLayout = new QHBoxLayout();
      QLabel* label_Tag = new QLabel(groupBox_Grammar);
      QLineEdit* lineEdit_Tag = new QLineEdit(groupBox_Grammar);
      QLabel* label_DefaultTag = new QLabel(groupBox_Grammar);
      QLineEdit* lineEdit_DefaultTag = new QLineEdit(groupBox_Grammar);
      QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      label_Tag->setText(QApplication::translate("UI_ASN1_ValueMain", "Tag", 0));
      label_DefaultTag->setText(QApplication::translate("UI_ASN1_ValueMain", "Default Tag", 0));
      lineEdit_Tag->setText(val->GetTag().GetString());
      lineEdit_DefaultTag->setText(val->GetDefaultTag().GetString());

      lineEdit_Tag->setReadOnly(true);
      lineEdit_DefaultTag->setReadOnly(true);

      hLay_TagLayout->addWidget(label_Tag);
      hLay_TagLayout->addWidget(lineEdit_Tag);
      hLay_TagLayout->addWidget(label_DefaultTag);
      hLay_TagLayout->addWidget(lineEdit_DefaultTag);
      hLay_TagLayout->addItem(horizontalSpacer);
      vLayGrammarLayout->addLayout(hLay_TagLayout);
    }

    void MakeOptionsLayout(QGroupBox* groupBox_Grammar, QVBoxLayout* vLayGrammarLayout, const ASN1_Object* val) {
      QHBoxLayout* hLay_OptionsLayout = new QHBoxLayout();
      QLabel* label_Optional = new QLabel(groupBox_Grammar);
      QSpacerItem* horizontalSpacer_1 = new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
      QLabel* label_TaggingConvention = new QLabel(groupBox_Grammar);
      QSpacerItem* horizontalSpacer_2 = new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

      label_Optional->setText(QApplication::translate("UI_ASN1_ValueMain", "Optional", 0));
      label_TaggingConvention->setText(QApplication::translate("UI_ASN1_ValueMain", "Tagging convention", 0));

      QFont font;
      font.setPointSize(10);
      font.setBold(true);
      //font.setWeight(50);
      label_Optional->setFont(font);
      label_TaggingConvention->setFont(font);

      if (val->IsMandatory())   label_Optional->setText("Mandatory");
      else                      label_Optional->setText("Optional");

      if (val->IsExplicit())    label_TaggingConvention->setText("Explicit tagging");
      else                      label_TaggingConvention->setText("Implicit tagging");

      hLay_OptionsLayout->addWidget(label_Optional);
      hLay_OptionsLayout->addItem(horizontalSpacer_1);
      hLay_OptionsLayout->addWidget(label_TaggingConvention);
      hLay_OptionsLayout->addItem(horizontalSpacer_2);
      vLayGrammarLayout->addLayout(hLay_OptionsLayout);
    }

    void MakeLinkValuesLayout(QGroupBox* groupBox_Grammar, QVBoxLayout* vLayGrammarLayout, const ASN1_Object* val, QWidget* sigConnection) {
      QHBoxLayout* hLay_DefaultValueLayout;
      if (val->GetMyOwner() || val->GetDefaultValue())
        hLay_DefaultValueLayout = new QHBoxLayout();

      // parent link
      if (val->GetMyOwner()) {
        QLabel* label_parentVal = new QLabel("Parent node:", groupBox_Grammar);
        QString valText = val->GetMyOwner()->GetName().c_str();
        QString hValText = "<a href=\"" + valText + "\">" + valText + "</a>";
        QLabel* label_parentValLink = new QLabel(hValText, groupBox_Grammar);
        QSpacerItem* horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        hLay_DefaultValueLayout->addWidget(label_parentVal);
        hLay_DefaultValueLayout->addWidget(label_parentValLink);
        hLay_DefaultValueLayout->addItem(horizontalSpacer2);

        QObject::connect(label_parentValLink, SIGNAL(linkActivated(QString)), sigConnection, SLOT(ShowParentValue()));
      }
      //default value link
      if (val->GetDefaultValue() != nullptr) {
        QLabel* label_defaultVal = new QLabel("Default value:", groupBox_Grammar);
        QString valText = val->GetDefaultValue()->GetName().c_str();
        QString hValText = "<a href=\"" + valText + "\">" + valText + "</a>";
        QLabel* label_defaultValLink = new QLabel(hValText, groupBox_Grammar);
        QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        hLay_DefaultValueLayout->addWidget(label_defaultVal);
        hLay_DefaultValueLayout->addWidget(label_defaultValLink);
        hLay_DefaultValueLayout->addItem(horizontalSpacer);

        QObject::connect(label_defaultValLink, SIGNAL(linkActivated(QString)), sigConnection, SLOT(ShowDefaultValue()));
      }
      if (val->GetMyOwner() || val->GetDefaultValue())
        vLayGrammarLayout->addLayout(hLay_DefaultValueLayout);
    }

    QHBoxLayout* MakeButtonBar_ReadOnly(const ASN1_Object* val, UI_ASN1_ValueMain_ReadOnly* parent) {
      QHBoxLayout* hLay_ButtonsLayout = new QHBoxLayout();
      QSpacerItem* horizontalSpacer = new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

      QString p = ":/img/icon_set_2/";
      ClickableLabel* CloseButton = MakeClickableLabel("commonButton", "Close", p + "cancel.png", parent);

      hLay_ButtonsLayout->addItem(horizontalSpacer);
      switch (val->GetType()) {
      case cChoice: case cSequence: case cSequenceOf: case cSet: break;
      default:
        ClickableLabel* showHexaButton = MakeClickableLabel("commonButton", "Show Hexadecimal", p + "binary.png", parent);
        hLay_ButtonsLayout->addWidget(showHexaButton);
        QObject::connect(showHexaButton, SIGNAL(clicked(bool)), parent, SLOT(ShowHexaValue()));
      }
      hLay_ButtonsLayout->addWidget(CloseButton);
      QObject::connect(CloseButton, SIGNAL(clicked(bool)), parent, SLOT(reject()));

      return hLay_ButtonsLayout;
    }

    QHBoxLayout* MakeButtonBar_Edit(const ASN1_Object* val, UI_ASN1_ValueMain_Editable* parent) {
      QHBoxLayout* hLay_ButtonsLayout = new QHBoxLayout();
      QSpacerItem* horizontalSpacer = new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

      QString p = ":/img/icon_set_2/";
      ClickableLabel* OkButton = MakeClickableLabel("commonButton", "Ok", p + "ok.png", parent);
      ClickableLabel* CancelButton = MakeClickableLabel("commonButton", "Cancel", p + "cancel.png", parent);

      hLay_ButtonsLayout->addItem(horizontalSpacer);
      switch (val->GetType()) {
      case cChoice: case cSequence: case cSequenceOf: case cSet: break;
      default:
        ClickableLabel* showHexaButton = MakeClickableLabel("commonButton", "Show Hexadecimal", p + "binary.png", parent);
        hLay_ButtonsLayout->addWidget(showHexaButton);
        QObject::connect(showHexaButton, SIGNAL(clicked(bool)), parent, SLOT(ShowHexaValue()));
      }
      hLay_ButtonsLayout->addWidget(OkButton);
      hLay_ButtonsLayout->addWidget(CancelButton);

      QObject::connect(OkButton, SIGNAL(clicked(bool)), parent, SLOT(accept()));
      QObject::connect(CancelButton, SIGNAL(clicked(bool)), parent, SLOT(reject()));

      return hLay_ButtonsLayout;
    }

    QHBoxLayout* MakeIgnoreLayoutReadOnly(const ASN1_Object* val, QCheckBox* checkBox_IgnoreValue) {
      QHBoxLayout* ignoreLayout = new QHBoxLayout();

      checkBox_IgnoreValue->setText(QApplication::translate("UI_ASN1_ValueMain", "Ignore value", 0));
      checkBox_IgnoreValue->setEnabled(false);
      checkBox_IgnoreValue->setChecked(val->IsIgnored());
      ignoreLayout->addWidget(checkBox_IgnoreValue);
      return ignoreLayout;
    }

    QHBoxLayout* MakeIgnoreLayout(const ASN1_Object* val, QCheckBox* checkBox_IgnoreValue) {
      QHBoxLayout* ignoreLayout = MakeIgnoreLayoutReadOnly(val, checkBox_IgnoreValue);

      checkBox_IgnoreValue->setEnabled(!val->IsMandatory());
      return ignoreLayout;
    }

    QHBoxLayout* MakeDescriptionLayoutReadOnly(QLineEdit* lineEdit_Description) {
      QHBoxLayout* ignoreLayout = new QHBoxLayout();

      lineEdit_Description->setReadOnly(true);
      ignoreLayout->addWidget(new QLabel("Description:"));
      ignoreLayout->addWidget(lineEdit_Description);
      return ignoreLayout;
    }

    QHBoxLayout* MakeDescriptionLayout(QLineEdit* lineEdit_Description) {
      QHBoxLayout* ignoreLayout = MakeDescriptionLayoutReadOnly(lineEdit_Description);
      lineEdit_Description->setReadOnly(false);
      return ignoreLayout;
    }

    QGroupBox* MakeGrammarBox(QWidget* parent, const ASN1_Object* val) {
      QGroupBox* groupBox_Grammar = new QGroupBox(parent);
      groupBox_Grammar->setObjectName("grammarBox");
      QVBoxLayout* vLayGrammarLayout = new QVBoxLayout(groupBox_Grammar);

      groupBox_Grammar->setTitle(QApplication::translate("UI_ASN1_ValueMain", "Grammar Values", 0));
      QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
      groupBox_Grammar->setSizePolicy(sizePolicy);

      MakeNameLayout(groupBox_Grammar, vLayGrammarLayout, val);
      MakeTagLayout(groupBox_Grammar, vLayGrammarLayout, val);
      MakeOptionsLayout(groupBox_Grammar, vLayGrammarLayout, val);
      MakeLinkValuesLayout(groupBox_Grammar, vLayGrammarLayout, val, parent);
      return groupBox_Grammar;
    }

    void MakeValueBox(QGroupBox* parent, UI_ASN1_Value_Node* valueEdit, bool readOnly) {
      parent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      parent->setTitle(QApplication::translate("UI_ASN1_ValueMain", "Editable Values", 0));
      parent->setCheckable(false);
      if (valueEdit != nullptr)
        valueEdit->MakeWidget(parent, readOnly);
    }
  }
  using namespace UI_Main;

  UI_ASN1_ValueMain::UI_ASN1_ValueMain(const ASN1_Object* val, QWidget* parent) :
    ValueDialog(parent), value(val) {
    if (val->GetType() == cBitString)
      valueEdit = new UI_ASN1_Node_BitString(static_cast<const ASN1_BitString*>(val), this);
    if (val->GetType() == cBoolean)
      valueEdit = new UI_ASN1_Node_Boolean(static_cast<const ASN1_Boolean*>(val), this);
    if (val->GetType() == cChoice)
      valueEdit = new UI_ASN1_Node_Choice(static_cast<const ASN1_Choice*>(val), this);
    if (val->GetType() == cEnumerated)
      valueEdit = new UI_ASN1_Node_Enumerated(static_cast<const ASN1_Enumerated*>(val), this);
    if (val->GetType() == cIA5String)
      valueEdit = new UI_ASN1_Node_IA5String(static_cast<const ASN1_IA5String*>(val), this);
    if (val->GetType() == cInteger)
      valueEdit = new UI_ASN1_Node_Integer(static_cast<const ASN1_Integer*>(val), this);
    if (val->GetType() == cNull)
      valueEdit = new UI_ASN1_Node_Null(static_cast<const ASN1_Null*>(val), this);
    if (val->GetType() == cObjectID)
      valueEdit = new UI_ASN1_Node_ObjectID(static_cast<const ASN1_ObjectID*>(val), this);
    if (val->GetType() == cOctetString)
      valueEdit = new UI_ASN1_Node_OctetString(static_cast<const ASN1_OctetString*>(val), this);
    if (val->GetType() == cReal)
      valueEdit = new UI_ASN1_Node_Real(static_cast<const ASN1_Real*>(val), this);
    if (val->GetType() == cSequence)
      valueEdit = new UI_ASN1_Node_Sequence(static_cast<const ASN1_Sequence*>(val), this);
    if (val->GetType() == cSequenceOf)
      valueEdit = new UI_ASN1_Node_SequenceOf(static_cast<const ASN1_SequenceOf*>(val), this);
    if (val->GetType() == cSet)
      valueEdit = new UI_ASN1_Node_Set(static_cast<const ASN1_Set*>(val), this);
    if (val->GetType() == cUTCTime)
      valueEdit = new UI_ASN1_Node_UTCTime(static_cast<const ASN1_UTCTime*>(val), this);
    if (val->GetType() == cUTF8String)
      valueEdit = new UI_ASN1_Node_UTF8String(static_cast<const ASN1_UTF8String*>(val), this);

    groupBox_value = new QGroupBox(this);
    groupBox_value->setObjectName("valueBox");
    resize(400, 400);

    checkBox_IgnoreValue = new QCheckBox(this);
    checkBox_IgnoreValue->setChecked(val->IsIgnored());
    lineEdit_Description = new QLineEdit(this);
    lineEdit_Description->setToolTip("Description is only a comment, it is not part of ASN1 standard, "
                                     "and will not be part of the binary output.");
    lineEdit_Description->setText(val->GetDescription().c_str());

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(3);
  }

  UI_ASN1_ValueMain::~UI_ASN1_ValueMain() {
    delete valueEdit;
  }

  UI_ASN1_ValueMain_Editable::UI_ASN1_ValueMain_Editable(ASN1_Object* val, QWidget* parent) :
    UI_ASN1_ValueMain(val, parent), value(val) {
    setWindowTitle(QApplication::translate("UI_ASN1_ValueMain", "ASN1 Value", 0));
    mainLayout->addWidget(MakeGrammarBox(this, val));
    mainLayout->addLayout(MakeDescriptionLayout(lineEdit_Description));
    mainLayout->addLayout(MakeIgnoreLayout(val, checkBox_IgnoreValue));
    MakeValueBox(groupBox_value, valueEdit, false);
    mainLayout->addWidget(groupBox_value);
    mainLayout->addLayout(MakeButtonBar_Edit(val, this));
    QObject::connect(this, SIGNAL(EnterPressed()), this, SLOT(accept()));
    QObject::connect(this, SIGNAL(EscapePressed()), this, SLOT(reject()));
  }

  UI_ASN1_ValueMain_ReadOnly::UI_ASN1_ValueMain_ReadOnly(const ASN1_Object* val, QWidget* parent) :
    UI_ASN1_ValueMain(val, parent) {
    setWindowTitle(QApplication::translate("UI_ASN1_ValueMain", "ASN1 Value - Read Only", 0));
    mainLayout->addWidget(MakeGrammarBox(this, val));
    mainLayout->addLayout(MakeDescriptionLayoutReadOnly(lineEdit_Description));
    mainLayout->addLayout(MakeIgnoreLayoutReadOnly(val, checkBox_IgnoreValue));
    MakeValueBox(groupBox_value, valueEdit, true);
    mainLayout->addWidget(groupBox_value);
    mainLayout->addLayout(MakeButtonBar_ReadOnly(val, this));
    QObject::connect(this, SIGNAL(EnterPressed()), this, SLOT(reject()));
    QObject::connect(this, SIGNAL(EscapePressed()), this, SLOT(reject()));
  }

  void UI_ASN1_ValueMain::ShowDefaultValue() {
    UI_ASN1_ValueMain_ReadOnly valueWindow(value->GetDefaultValue(), this);
    valueWindow.exec();
  }

  void UI_ASN1_ValueMain::ShowParentValue() {
    UI_ASN1_ValueMain_ReadOnly valueWindow(value->GetMyOwner(), this);
    valueWindow.exec();
  }

  void UI_ASN1_ValueMain::UIShowValue(ByteArray hex) const {
    QDialog d(this->parentWidget());
    QVBoxLayout* l = new QVBoxLayout(&d);
    myQTextEdit* t = new myQTextEdit(&d, myQTextEdit::cLineEditHexa);
    t->setReadOnly(true);
    d.setWindowTitle("Hexadecimal value");
    l->addWidget(t);
    t->setPlainText(hex.GetString());
    d.exec();
  }

  void UI_ASN1_ValueMain::ShowHexaValue() const {
    ByteArray hex;
    value->WriteIntoBuffer(hex);
    UIShowValue(hex);
  }

  void UI_ASN1_ValueMain_Editable::ShowHexaValue() const {
    ByteArray hex;
    if (valueEdit->GetHexValue(value, hex))
      UIShowValue(hex);
  }

  void UI_ASN1_ValueMain_Editable::accept() {
    if (valueEdit->accept(value)) {
      value->Ignore(checkBox_IgnoreValue->isChecked());
      value->SetDescription(lineEdit_Description->text().toStdString().c_str());
      QDialog::accept();
    }
  }

  void UI_ASN1_ValueMain::reject() {
    QDialog::reject();
  }
}

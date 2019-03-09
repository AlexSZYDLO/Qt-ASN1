/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "ASN1_includes.h"
#include "Widgets/CustomWidgets.h"

#ifndef UI_NODE_COMMON_PUBLIC_FUNCTIONS
#define UI_NODE_COMMON_PUBLIC_FUNCTIONS \
public: \
    using  UI_ASN1_Value_Node_Template::UI_ASN1_Value_Node_Template; \
    /*UI_ASN1_Node_##name(const ASN1_##name * grammar, QWidget* parent) : UI_ASN1_Value_Node_Template(grammar, parent) {}*/ \
    virtual void MakeWidget(QGroupBox* inBox, bool readOnly) override; \
    virtual bool accept(ASN1_Object* val) override; \
    virtual bool GetHexValue(ASN1_Object* val, ByteArray& hex) override;
#endif

namespace UI {
  class UI_ASN1_Value_Node : public QObject {
    Q_OBJECT
   protected:
    QWidget* m_ParentWidget;

   public:
    UI_ASN1_Value_Node(QWidget* parent) : m_ParentWidget(parent) {}
    virtual ~UI_ASN1_Value_Node() {}
    virtual bool accept(ASN1_Object*) = 0;
    virtual void MakeWidget(QGroupBox* inBox, bool readOnly) = 0;
    virtual bool GetHexValue(ASN1_Object* value, ByteArray& hex) = 0;
  };

  template<class nodeType>
  class UI_ASN1_Value_Node_Template : public UI_ASN1_Value_Node {
   protected:
    const nodeType* m_Grammar;

   public:
    UI_ASN1_Value_Node_Template(const nodeType* grammar, QWidget* parent)
      : UI_ASN1_Value_Node(parent), m_Grammar(grammar) {}

    virtual bool accept(ASN1_Object*) = 0;
    virtual void MakeWidget(QGroupBox* inBox, bool readOnly) = 0;
    virtual bool GetHexValue(ASN1_Object*, ByteArray&) = 0;
  };

  // NODES UI CLASSES

  class UI_ASN1_Node_BitString : public UI_ASN1_Value_Node_Template<ASN1_BitString> {
    myQTextEdit* binaryText;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Boolean : public UI_ASN1_Value_Node_Template<ASN1_Boolean> {
    QCheckBox* check;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Choice : public UI_ASN1_Value_Node_Template<ASN1_Choice> {
    Q_OBJECT
    QLabel* label_ChoiceValLink;
    MyListView* listView;
    int newChoiceIndex;
    const ASN1_Object*  tempChoice;

    void UpdateSelectedChoiceLabel();

   public slots:
    void ShowChosenValue();
    void ShowChoiceInList(QModelIndex i);
    void SetChoice();

    UI_NODE_COMMON_PUBLIC_FUNCTIONS
    UI_ASN1_Node_Choice(const ASN1_Choice* grammar, QWidget* parent);
    virtual ~UI_ASN1_Node_Choice();
  };

  class UI_ASN1_Node_IA5String : public UI_ASN1_Value_Node_Template<ASN1_IA5String> {
    myQTextEdit* str;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Integer : public UI_ASN1_Value_Node_Template<ASN1_Integer> {
    QSpinBox* integer;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Enumerated : public UI_ASN1_Value_Node_Template<ASN1_Enumerated> {
    QSpinBox* enumerated;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Null : public UI_ASN1_Value_Node_Template<ASN1_Null> {
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_OctetString : public UI_ASN1_Value_Node_Template<ASN1_OctetString> {
    myQTextEdit* hexaText;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_ObjectID : public UI_ASN1_Value_Node_Template<ASN1_ObjectID> {
    myQTextEdit* OIDText;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Sequence : public UI_ASN1_Value_Node_Template<ASN1_Sequence> {
    Q_OBJECT
    MyListView* listView;
   public slots:
    void ShowObjInList(QModelIndex i);
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Real : public UI_ASN1_Value_Node_Template<ASN1_Real> {
    QDoubleSpinBox* real;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_UTCTime : public UI_ASN1_Value_Node_Template<ASN1_UTCTime> {
    Q_OBJECT
    QDateTimeEdit* edit;
    QSpinBox* Zhours;
    QSpinBox* ZMin;
    QComboBox* ZSign;

    QString signToString(Utils::eUTCTimeZone sign);
    Utils::eUTCTimeZone stringToSign(QString str);
   public slots:
    void signChanged();
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_SequenceOf : public UI_ASN1_Value_Node_Template<ASN1_SequenceOf> {
    Q_OBJECT
    MyListView* listView;
    QList<const ASN1_Object*> tempObjectList;
    QModelIndex GetSelectedIndex() const;
    void MoveSelected(bool up);

    struct seqOfAction {
      enum ActionKind {
        eMoveUp, eMoveDown, eDelete, eAdd
      };
      ActionKind kind;
      int atIndex;
    };
    QList<seqOfAction> pendingActions;

   public slots:
    void Add();
    void Delete();
    void MoveUp();
    void MoveDown();
    void ShowObjInList(QModelIndex i);

    UI_NODE_COMMON_PUBLIC_FUNCTIONS
    UI_ASN1_Node_SequenceOf(const ASN1_SequenceOf* grammar, QWidget* parent);
  };

  class UI_ASN1_Node_UTF8String : public UI_ASN1_Value_Node_Template<ASN1_UTF8String> {
    myQTextEdit* str;
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };

  class UI_ASN1_Node_Set : public UI_ASN1_Value_Node_Template<ASN1_Set> {
    Q_OBJECT
    MyListView* listView;
   public slots:
    void ShowObjInList(QModelIndex i);
    UI_NODE_COMMON_PUBLIC_FUNCTIONS
  };
}

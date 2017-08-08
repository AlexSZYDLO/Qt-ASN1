/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once
#include "ASN1_includes.h"
#include "Widgets/CustomWidgets.h"

namespace UI {
  class UI_TreePanel;
  class UI_Editor_ButtonBar;
  class UI_Main;

  class UI_Editor : public QWidget {
    Q_OBJECT

   public:
    UI_Editor(UI_Main* main);
    ~UI_Editor();

    void RefreshTree();
    void SetGrammar(ASN1_Object* obj);
    void SetMainStatus(const QString& s);

   protected:
    // functions
    void Write(ASN1_Object* obj);
    void Read(ASN1_Object* obj);

    QWidget* CreateButtonBar();
    QWidget* MakeLeftPanel(QWidget* parent);
    QWidget* MakeRightPanel(QWidget* parent);
    QWidget* MakeSplitter(QWidget* parent);

    void CreateMenuBar();
    void CreateStatusBar();
    void MakeEditorPane();

    // variables
    UI_Main* m_Main;

    ASN1_Object* m_Grammar;

    myQTextEdit* m_HexaTextEdit;
    UI_TreePanel* m_Tree;
    UI_Editor_ButtonBar* m_ButtonBar;

   public slots:
    void action_Write();
    void action_Read();
    void action_WriteAll();
    void action_ReadAll();
    void action_Compare();

    void action_OpenHex();
    void action_OpenASN();
    void action_OpenScript();
    void action_RunScript();
    void action_Save();

    void action_ConvertBitString();
    void action_ConvertBoolean();
    void action_ConvertEnumerated();
    void action_ConvertIA5String();
    void action_ConvertInteger();
    void action_ConvertObjectID();
    void action_ConvertOctetString();
    void action_ConvertReal();
    void action_ConvertUTCTime();
    void action_ConvertUTF8String();
  };
}

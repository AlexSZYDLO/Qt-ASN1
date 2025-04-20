/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once
#include "Widgets/CustomWidgets.h"
#include "Widgets/DraggableTreeWidget.h"
#include "Widgets/DropablePlainTextEdit.h"

namespace UI
{
class UI_Main;

class UI_GrammarJS : public QWidget
{
  Q_OBJECT

public:
  UI_GrammarJS(UI_Main *main);
  virtual ~UI_GrammarJS()
  {
  }

  void SetScript(const QString &script);

protected:
  // functions
  QGroupBox *MakeJSEditor(QWidget *parent);
  QGroupBox *MakeHintPanel(QWidget *parent);
  QWidget *MakeMenuBar();
  void MakeJSGrammarPane();

  // variables
  UI_Main *m_Main;
  DropablePlainTextEdit *JSedit;
  DraggableTreeWidget *HintPanel;
  QLabel *HintText;
  bool m_JSDebug;

  QString m_LoadedScriptFile;

public slots:
  void RefreshHint(const QModelIndex &i);
  void ToggleJSDebugMode();
  void debugMenu();
  void RunJSScript();
  void RunAdditionalJSScript();
  void LoadJSScript();
  void SaveJSScript();
};

} // namespace UI

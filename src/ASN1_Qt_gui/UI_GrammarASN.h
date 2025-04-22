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

class UI_GrammarASN : public QWidget
{
  Q_OBJECT

public:
  UI_GrammarASN(UI_Main *main);
  virtual ~UI_GrammarASN()
  {
  }

  void SetASNGrammar(const QString &path);

protected:
  // functions
  QGroupBox *MakeASNEditor(QWidget *parent);
  QGroupBox *MakeHintPanel(QWidget *parent);
  QWidget *MakeMenuBar();
  void MakeASNGrammarPane();

  // variables
  UI_Main *m_Main;

  QPlainTextEdit *ASNedit;
  DraggableTreeWidget *HintPanel;
  QLabel *HintText;

  QString m_LoadedASNFile;
  QString m_CppFile;

public slots:
  void RefreshHint(const QModelIndex &i);

  void ToJS();
  void ToCPP();
  void ToEditor();
  void LoadASN();
  void SaveASN();
};

} // namespace UI

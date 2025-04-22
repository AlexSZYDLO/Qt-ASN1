/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once
#include "Widgets/CustomWidgets.h"

namespace UI
{
class UI_Main;

class UI_GrammarComp : public QWidget
{
  Q_OBJECT

public:
  UI_GrammarComp(UI_Main *main);
  virtual ~UI_GrammarComp()
  {
  }

protected:
  // functions
  QWidget *MakeMenuBar();
  void MakeCompGrammarPane();

  // variables
  UI_Main *m_Main;
  QComboBox *m_List;

public slots:
  void LoadGrammar();
};

} // namespace UI

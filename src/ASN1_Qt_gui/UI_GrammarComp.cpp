/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "UI_GrammarComp.h"
#include "UI_Main.h"

namespace UI
{
UI_GrammarComp::UI_GrammarComp(UI_Main *main)
    : QWidget(main)
    , m_Main(main)
{
  MakeCompGrammarPane();
}

QWidget *UI_GrammarComp::MakeMenuBar()
{
  QWidget *buttonBarWidget = new QWidget(this);
  buttonBarWidget->setObjectName("actionBox");
  buttonBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  QString p = ":/img/icon_set_2/";
  ClickableLabel *buttonLoad = MakeClickableLabel("actionButton", "Load grammar", p + "run.png", this);

  QHBoxLayout *buttonLay = new QHBoxLayout();
  buttonLay->setContentsMargins(1, 1, 1, 1); // l, t, r, b
  buttonLay->addWidget(buttonLoad);
  buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));

  buttonBarWidget->setLayout(buttonLay);

  connect(buttonLoad, SIGNAL(clicked(bool)), this, SLOT(LoadGrammar()));
  return buttonBarWidget;
}

void UI_GrammarComp::MakeCompGrammarPane()
{
  QVBoxLayout *vLay = new QVBoxLayout(this);
  vLay->setContentsMargins(1, 1, 1, 2); // l, t, r, b
  vLay->setSpacing(2);

  m_List = new QComboBox(this);
  m_List->addItems({"Test_1", "SIM Alliance"});

  vLay->addWidget(MakeMenuBar());
  vLay->addWidget(m_List);
  vLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
}

void UI_GrammarComp::LoadGrammar()
{
  std::shared_ptr<ASN1_Object> obj = m_Main->CompToObj(m_List->currentText());
  if (obj != nullptr)
  {
    m_Main->SetLastCompGramm(m_List->currentText());
    *m_Main->GetScriptEngine() = nullptr;
    m_Main->SetEditorObj(obj);
    m_Main->SelectTab(3);
  }
}

} // namespace UI

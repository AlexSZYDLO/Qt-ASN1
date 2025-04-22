/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "UI_Editor_Menus.h"
#include "Converters/UI_Converter.h"
#include "UI_Editor.h"
#include "Widgets/CustomWidgets.h"

namespace UI
{

UI_Editor_ButtonBar::UI_Editor_ButtonBar(UI_Main *m, UI_Editor *main)
    : QWidget(m)
    , m_Main(main)
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  QString p = ":/img/icon_set_2/";
  QString name = "actionButton";
  ClickableLabel *buttonOpen = MakeClickableLabel(name, "Open menu", p + "open.png", this);
  ClickableLabel *buttonSave = MakeClickableLabel(name, "Save to .der", p + "save.png", this);
  ClickableLabel *buttonWrite = MakeClickableLabel(name, "Serialize", p + "binary.png", this);
  ClickableLabel *buttonRead = MakeClickableLabel(name, "Deserialize", p + "read.png", this);
  ClickableLabel *buttonCompare = MakeClickableLabel(name, "Compare hexadecimal with tree", p + "compare.png", this);
  ClickableLabel *buttonTools = MakeClickableLabel(name, "Converter tools", p + "toolbox.png", this);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  setLayout(buttonLayout);
  buttonLayout->setContentsMargins(1, 1, 1, 1); // l, t, r, b

  buttonLayout->addWidget(buttonOpen);
  buttonLayout->addWidget(buttonSave);
  buttonLayout->addItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
  buttonLayout->addWidget(buttonWrite);
  buttonLayout->addWidget(buttonRead);
  buttonLayout->addWidget(buttonCompare);
  buttonLayout->addItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
  buttonLayout->addWidget(buttonTools);
  buttonLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

  QObject::connect(buttonOpen, SIGNAL(clicked(bool)), this, SLOT(openClicked()));
  QObject::connect(buttonSave, SIGNAL(clicked(bool)), this, SLOT(saveClicked()));
  QObject::connect(buttonWrite, SIGNAL(clicked(bool)), m_Main, SLOT(action_WriteAll()));
  QObject::connect(buttonRead, SIGNAL(clicked(bool)), m_Main, SLOT(action_ReadAll()));
  QObject::connect(buttonCompare, SIGNAL(clicked(bool)), m_Main, SLOT(action_Compare()));
  QObject::connect(buttonTools, SIGNAL(clicked(bool)), this, SLOT(toolsClicked()));
}

void UI_Editor_ButtonBar::openClicked()
{
  QMenu *menuFile = new QMenu("File", m_Main);
  menuFile->addAction("Load Hexadecimal File", m_Main, SLOT(action_OpenHex()));
  menuFile->addAction("Load Grammar From ASN", m_Main, SLOT(action_OpenASN()));
  menuFile->addAction("Load Grammar From Script", m_Main, SLOT(action_OpenScript()));
  menuFile->addAction("Run Script", m_Main, SLOT(action_RunScript()));
  menuFile->addAction("Quit", m_Main, SLOT(close()));

  QWidget *button = static_cast<QWidget *>(sender());
  menuFile->exec(button->mapToGlobal(button->rect().bottomLeft()));
}

void UI_Editor_ButtonBar::saveClicked()
{
  m_Main->action_Save();
}

void UI_Editor_ButtonBar::toolsClicked()
{
  QMenu *menuConvert = new QMenu("Convert", m_Main);
  menuConvert->addAction("BitString", m_Main, SLOT(action_ConvertBitString()));
  menuConvert->addAction("Boolean", m_Main, SLOT(action_ConvertBoolean()));
  menuConvert->addAction("Enumerated", m_Main, SLOT(action_ConvertEnumerated()));
  menuConvert->addAction("IA5String", m_Main, SLOT(action_ConvertIA5String()));
  menuConvert->addAction("Integer", m_Main, SLOT(action_ConvertInteger()));
  menuConvert->addAction("ObjectID", m_Main, SLOT(action_ConvertObjectID()));
  menuConvert->addAction("OctetString", m_Main, SLOT(action_ConvertOctetString()));
  menuConvert->addAction("Real", m_Main, SLOT(action_ConvertReal()));
  menuConvert->addAction("UTCTime", m_Main, SLOT(action_ConvertUTCTime()));
  menuConvert->addAction("UTF8String", m_Main, SLOT(action_ConvertUTF8String()));

  QAction *test = new QAction("debug", m_Main);
  test->setCheckable(true);
  test->setChecked(debug);
  QObject::connect(test, SIGNAL(toggled(bool)), this, SLOT(toggleDebug()));
  //menuConvert->addAction(test);

  QWidget *button = static_cast<QWidget *>(sender());
  menuConvert->exec(button->mapToGlobal(button->rect().bottomLeft()));
}

void UI_Editor_ButtonBar::toggleDebug()
{
  debug = !debug;
}

} // namespace UI

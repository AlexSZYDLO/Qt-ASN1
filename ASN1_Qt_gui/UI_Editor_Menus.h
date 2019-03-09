/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once
#include "UI_Main.h"

namespace UI {
  class UI_Editor;

  class UI_Editor_ButtonBar : public QWidget {
    Q_OBJECT

   public:
    UI_Editor_ButtonBar(UI_Main* m, UI_Editor* main);

   private:
    UI_Editor* m_Main;
    bool debug;

    void paintEvent(QPaintEvent*) {
      QStyleOption o;
      o.initFrom(this);
      QPainter p(this);
      style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    }

   public slots:
    void saveClicked();
    void openClicked();
    void toolsClicked();

    void toggleDebug();

  };
}

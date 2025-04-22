/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include <QApplication>
#include <QTextStream>
#include <iostream>
#include "UI_Main.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  //QFile cssFile("../../../../ASN1/ASN1_Qt_gui/Config/StyleSheet.css");
  //if (!cssFile.exists())
  QFile cssFile(":/StyleSheet.css");

  QString cssContent;
  if (cssFile.exists())
  {
    cssFile.open(QFile::ReadOnly);
    cssContent = QTextStream(&cssFile).readAll();
    cssFile.close();
  }

  UI::UI_Main w;
  w.setStyleSheet(cssContent);
  w.show();
  app.exec();

  bool memCheck = ASN1_Object::memoryCheck() && ScriptMemoryCheck();
  std::cout << "memCheck: " << (memCheck ? "OK" : "NOK") << std::endl;

  return memCheck;
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QPlainTextEdit>

class DropablePlainTextEdit : public QPlainTextEdit
{
public:
  DropablePlainTextEdit(QWidget *parent);

protected:
  //virtual void dragEnterEvent(QDragEnterEvent* event) override;
  //virtual void dragMoveEvent(QDragMoveEvent* event) override;
  virtual void dropEvent(QDropEvent *event) override;
};

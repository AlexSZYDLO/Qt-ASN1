/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "DropablePlainTextEdit.h"
#include <QMimeData>

DropablePlainTextEdit::DropablePlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
  setAcceptDrops(true);
  setCursorWidth(2);
}

void DropablePlainTextEdit::dropEvent(QDropEvent *event)
{
  setFocus();
  QPlainTextEdit::dropEvent(event);
}

/*
void DropablePlainTextEdit::dragEnterEvent(QDragEnterEvent* event) {
  QStringList l = event->mimeData()->formats();
  //if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
  if (event->mimeData()->hasText()) {
    event->acceptProposedAction();
  }
}

void DropablePlainTextEdit::dragMoveEvent(QDragMoveEvent* event) {
}
*/

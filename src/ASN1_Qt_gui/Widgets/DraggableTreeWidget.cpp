/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "DraggableTreeWidget.h"
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QTreeWidgetItem>

DraggableTreeWidget::DraggableTreeWidget(QWidget *parent)
    : QTreeView(parent)
{
  setDragEnabled(true);
  setModel(new customModel);
}

void DraggableTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
  QTreeView::dragMoveEvent(event);
}

void DraggableTreeWidget::mousePressEvent(QMouseEvent *event)
{
  QTreeView::mousePressEvent(event);
  /*
    if (event->button() == Qt::LeftButton) {
      QDrag* drag = new QDrag(this);
      QMimeData* mimeData = new QMimeData;

      QTreeWidgetItem* i = itemAt(event->pos());

      mimeData->setText(i->text(0));
      drag->setMimeData(mimeData);

      drag->exec();
    }
  */
}

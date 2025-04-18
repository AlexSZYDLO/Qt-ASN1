/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QMimeData>

class DraggableStandardItem : public QStandardItem {
 public:
  DraggableStandardItem(const QString& _func, const QString& _desc, const QString& toolTip = "", const QString& _customDrop = "", bool draggable = true)
    : QStandardItem(_func), desc(_desc), customDrop(_customDrop) {
    setEditable(false);
    setToolTip(toolTip.isEmpty() ? _func : toolTip);
    if (!draggable)
      setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
  }
  QString GetDesc() { return desc; }
  QString GetCustomDrop() { return customDrop; }
 private:
  QString desc;
  QString customDrop;
};

class customModel : public QStandardItemModel {
  using QStandardItemModel::QStandardItemModel;

 protected:
  virtual QMimeData* mimeData(const QModelIndexList& indexes) const override {
    QMimeData* d = new QMimeData;
    QModelIndex i = indexes.at(0);
    DraggableStandardItem* item = static_cast <DraggableStandardItem*>(itemFromIndex(i));
    if (item->GetCustomDrop().isEmpty())
      d->setText(item->text());
    else
      d->setText(item->GetCustomDrop());
    return d;
  }
  virtual QStringList mimeTypes() const override {
    return {"text/plain"};
  }

};

class DraggableTreeWidget : public QTreeView {
 public:
  DraggableTreeWidget(QWidget* parent);

 protected:
//    void dragEnterEvent(QDragEnterEvent *event);
  virtual void dragMoveEvent(QDragMoveEvent* event) override;
//    void dropEvent(QDropEvent *event);
  virtual void mousePressEvent(QMouseEvent* event) override;
};

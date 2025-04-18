/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"
#include "UI_ASN1_Value_Main.h"
#include "../ASN1_TreeModel.h"

namespace UI {


  UI_ASN1_Node_SequenceOf::UI_ASN1_Node_SequenceOf(const ASN1_SequenceOf* grammar, QWidget* parent)
    : UI_ASN1_Value_Node_Template<ASN1_SequenceOf>(grammar, parent) {}

  void UI_ASN1_Node_SequenceOf::MakeWidget(QGroupBox* inBox, bool readOnly) {
    inBox->setTitle(inBox->title() + " - Sequence Of");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    QHBoxLayout* hLayValueLayout = new QHBoxLayout();
    listView = new MyListView(inBox);
    listView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QStandardItemModel* listModel = new QStandardItemModel(this);
    for (unsigned int i = 0; i < m_Grammar->GetSequenceOfSize(); i++) {
      ASN1_ItemReadOnly* item = new ASN1_ItemReadOnly(m_Grammar->GetObjectAt(i)->StringExtract().c_str(), m_Grammar->GetObjectAt(i));
      item->setEditable(false);
      listModel->appendRow(item);
    }
    listView->setModel(listModel);

    QString p = ":/img/icon_set_2/";
    ClickableLabel* addButton = MakeClickableLabel("commonButton", "Add", p + "plus.png", inBox);
    ClickableLabel* deleteButton = MakeClickableLabel("commonButton", "Delete", p + "minus.png", inBox);
    ClickableLabel* moveUpButton = MakeClickableLabel("commonButton", "Move Up", p + "up.png", inBox);
    ClickableLabel* moveDownButton = MakeClickableLabel("commonButton", "Move Down", p + "down.png", inBox);

    QObject::connect(listView, SIGNAL(EnterPressed(QModelIndex)), this, SLOT(ShowObjInList(QModelIndex)));
    QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ShowObjInList(QModelIndex)));
    QObject::connect(addButton, SIGNAL(clicked(bool)), this, SLOT(Add()));
    QObject::connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(Delete()));
    QObject::connect(moveUpButton, SIGNAL(clicked(bool)), this, SLOT(MoveUp()));
    QObject::connect(moveDownButton, SIGNAL(clicked(bool)), this, SLOT(MoveDown()));

    if (readOnly) {
      addButton->setEnabled(false);
      deleteButton->setEnabled(false);
      moveUpButton->setEnabled(false);
      moveDownButton->setEnabled(false);
    }

    hLayValueLayout->addWidget(addButton);
    hLayValueLayout->addWidget(deleteButton);
    hLayValueLayout->addWidget(moveUpButton);
    hLayValueLayout->addWidget(moveDownButton);
    hLayValueLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Ignored));
    vLayValueLayout->addLayout(hLayValueLayout);
    vLayValueLayout->addWidget(listView);
  }

  QModelIndex UI_ASN1_Node_SequenceOf::GetSelectedIndex() const {
    QModelIndexList l = listView->selectionModel()->selectedIndexes();
    return l.size() > 0 ? l.at(0) : QModelIndex();
  }

  void UI_ASN1_Node_SequenceOf::Add() {
    ASN1_Object* dummyObj = m_Grammar->GetDummyNewObject();
    ASN1_ItemReadOnly* item = new ASN1_ItemReadOnly(dummyObj->StringExtract().c_str(), dummyObj);
    item->setEditable(false);
    static_cast<QStandardItemModel*>(listView->model())->appendRow(item);
    listView->scrollTo(item->index());
    pendingActions.push_back({seqOfAction::eAdd, 0});
  }

  void UI_ASN1_Node_SequenceOf::Delete() {
    QModelIndex i = GetSelectedIndex();
    listView->model()->removeRow(i.row());
    listView->scrollTo(i);
    pendingActions.push_back({seqOfAction::eDelete, });
  }

  void UI_ASN1_Node_SequenceOf::MoveSelected(bool up) {
    QModelIndex i = GetSelectedIndex();
    QStandardItemModel* mod = static_cast<QStandardItemModel*>(listView->model());
    if ((i.row() > 0 && up) || (i.row() < mod->rowCount() - 1 && !up)) {
      ASN1_ItemReadOnly* it = static_cast<ASN1_ItemReadOnly*>(mod->itemFromIndex(i));
      ASN1_ItemReadOnly* newIt = new ASN1_ItemReadOnly(it->getGrammarObject()->StringExtract().c_str(), it->getGrammarObject());
      mod->removeRow(i.row());
      if (up) mod->insertRow(i.row() - 1, newIt);
      else    mod->insertRow(i.row() + 1, newIt);
      listView->scrollTo(newIt->index());
      listView->selectionModel()->select(newIt->index(), QItemSelectionModel::ClearAndSelect);
      pendingActions.push_back({ up ? seqOfAction::eMoveUp : seqOfAction::eMoveDown, i.row()});
    }
  }

  void UI_ASN1_Node_SequenceOf::MoveUp() {
    MoveSelected(true);
  }

  void UI_ASN1_Node_SequenceOf::MoveDown() {
    MoveSelected(false);
  }

  void UI_ASN1_Node_SequenceOf::ShowObjInList(QModelIndex i) {
    UI_ASN1_ValueMain_ReadOnly valueWindow(
      static_cast<ASN1_Item*>(
        static_cast<QStandardItemModel*>(listView->model())->itemFromIndex(i))->getGrammarObject(), m_ParentWidget);
    valueWindow.exec();
  }

  bool UI_ASN1_Node_SequenceOf::accept(ASN1_Object* val) {
    // must recast from non const value
    ASN1_SequenceOf* seqOfVal = static_cast<ASN1_SequenceOf*>(val);

    for (int i = 0; i < pendingActions.size(); i++) {
      seqOfAction act = pendingActions.at(i);
      if (act.kind == seqOfAction::eAdd)
        seqOfVal->AppendNewObject();
      else if (act.kind == seqOfAction::eMoveUp)
        seqOfVal->MoveUpObject(act.atIndex);
      else if (act.kind == seqOfAction::eMoveDown)
        seqOfVal->MoveDownObject(act.atIndex);
      else
        seqOfVal->DeleteObjectAt(act.atIndex);
    }
    return true;
  }

  bool UI_ASN1_Node_SequenceOf::GetHexValue(ASN1_Object*, ByteArray&) {
    QMessageBox::information(nullptr, "Cannot preview choice", "Complex nodes do not support the hexadecimal preview.");
    return false;
  }
}

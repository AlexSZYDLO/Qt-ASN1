/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"
#include "UI_ASN1_Value_Main.h"
#include "../ASN1_TreeModel.h"

namespace UI {
  void UI_ASN1_Node_Sequence::MakeWidget(QGroupBox* inBox, bool) {
    inBox->setTitle(inBox->title() + " - Sequence");
    if (m_Grammar->IsExtensible())
      inBox->setTitle(inBox->title() + " - Extensible");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    listView = new MyListView(inBox);
    listView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QStandardItemModel* listModel = new QStandardItemModel(this);
    for (unsigned int i = 0; i < m_Grammar->GetSize(); i++) {
      ASN1_ItemReadOnly* item = new ASN1_ItemReadOnly(m_Grammar->GetObjectAt(i)->StringExtract().c_str(), m_Grammar->GetObjectAt(i));
      item->setEditable(false);
      listModel->appendRow(item);
    }
    for (unsigned int i = 0; i < m_Grammar->GetExtensibilitySize(); i++) {
      ASN1_ItemReadOnly* item = new ASN1_ItemReadOnly(m_Grammar->GetExtensibilityObjectAt(i)->StringExtract().c_str(), m_Grammar->GetExtensibilityObjectAt(i));
      item->setEditable(false);
      listModel->appendRow(item);
    }
    listView->setModel(listModel);

    QObject::connect(listView, SIGNAL(EnterPressed(QModelIndex)), this, SLOT(ShowObjInList(QModelIndex)));
    QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ShowObjInList(QModelIndex)));

    vLayValueLayout->addWidget(listView);
  }

  void UI_ASN1_Node_Sequence::ShowObjInList(QModelIndex i) {
    UI_ASN1_ValueMain_ReadOnly valueWindow(
      static_cast<ASN1_Item*>(
        static_cast<QStandardItemModel*>(listView->model())->itemFromIndex(i))->getGrammarObject(), m_ParentWidget);
    valueWindow.exec();
  }

  bool UI_ASN1_Node_Sequence::accept(ASN1_Object*) {
    // nothing can be edited there for a sequence
    return true;
  }

  bool UI_ASN1_Node_Sequence::GetHexValue(ASN1_Object*, ByteArray&) {
    QMessageBox::information(nullptr, "Cannot preview choice", "Complex nodes do not support the hexadecimal preview.");
    return false;
  }
}

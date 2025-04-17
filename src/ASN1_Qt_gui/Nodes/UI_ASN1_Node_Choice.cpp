/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_ASN1_Value_Node_Base.h"
#include "UI_ASN1_Value_Main.h"
#include "../ASN1_TreeModel.h"

namespace UI {
  UI_ASN1_Node_Choice::UI_ASN1_Node_Choice(const ASN1_Choice* grammar, QWidget* parent)
    : UI_ASN1_Value_Node_Template<ASN1_Choice>(grammar, parent),
      tempChoice(m_Grammar->GetSelectedChoice()),
      newChoiceIndex(-1) {}

  void UI_ASN1_Node_Choice::MakeWidget(QGroupBox* inBox, bool readOnly) {
    inBox->setTitle(inBox->title() + " - Choice");
    QVBoxLayout* vLayValueLayout = new QVBoxLayout(inBox);
    QHBoxLayout* hLayValueLayout = new QHBoxLayout();

    QString p = ":/img/img/icon_set_2/";
    ClickableLabel* setChoiceWid = MakeClickableLabel("commonButton", "Set Selected Choice", p + "run.png", inBox);

    listView = new MyListView(inBox);
    listView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    if (readOnly)
      setChoiceWid->setEnabled(false);

    label_ChoiceValLink = new QLabel(inBox);
    UpdateSelectedChoiceLabel();

    QObject::connect(label_ChoiceValLink, SIGNAL(linkActivated(QString)), this, SLOT(ShowChosenValue()));
    QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ShowChoiceInList(QModelIndex)));
    QObject::connect(listView, SIGNAL(EnterPressed(QModelIndex)), this, SLOT(ShowChoiceInList(QModelIndex)));
    QObject::connect(setChoiceWid, SIGNAL(clicked(bool)), this, SLOT(SetChoice()));

    hLayValueLayout->addWidget(setChoiceWid);
    hLayValueLayout->addWidget(label_ChoiceValLink);
    hLayValueLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Ignored));
    vLayValueLayout->addLayout(hLayValueLayout);
    vLayValueLayout->addWidget(listView);

    m_Grammar->MakeDummyChoiceList();
    QStandardItemModel* listModel = new QStandardItemModel(this);
    for (unsigned int i = 0; i < m_Grammar->AvailableChoices(); i++) {
      ASN1_ItemReadOnly* item = new ASN1_ItemReadOnly(m_Grammar->GetChoiceFromIndex(i)->StringExtract().c_str(), m_Grammar->GetChoiceFromIndex(i));
      item->setEditable(false);
      listModel->appendRow(item);
    }
    listView->setModel(listModel);
  }

  UI_ASN1_Node_Choice::~UI_ASN1_Node_Choice() {
    m_Grammar->DeleteDummyChoiceList();
  }

  void UI_ASN1_Node_Choice::UpdateSelectedChoiceLabel() {
    QString valText;
    if (tempChoice != nullptr)
      valText = tempChoice->GetName().c_str();
    else
      valText = "no choice selected.";

    QString hValText = "<a href=\"" + valText + "\">" + valText + "</a>";
    label_ChoiceValLink->setText(hValText);
  }

  void UI_ASN1_Node_Choice::ShowChosenValue() {
    UI_ASN1_ValueMain_ReadOnly valueWindow(tempChoice, m_ParentWidget);
    valueWindow.exec();
  }

  void UI_ASN1_Node_Choice::ShowChoiceInList(QModelIndex i) {
    UI_ASN1_ValueMain_ReadOnly valueWindow(
      static_cast<ASN1_Item*>(
        static_cast<QStandardItemModel*>(listView->model())->itemFromIndex(i))->getGrammarObject(), m_ParentWidget);
    valueWindow.exec();
  }

  void UI_ASN1_Node_Choice::SetChoice() {
    QModelIndexList l = listView->selectionModel()->selectedIndexes();
    QModelIndex i = l.size() > 0 ? l.at(0) : QModelIndex();
    int j = i.row();
    newChoiceIndex = j;
    if (j != -1) {
      tempChoice = m_Grammar->GetChoiceFromIndex(j);
      UpdateSelectedChoiceLabel();
    }
  }

  bool UI_ASN1_Node_Choice::accept(ASN1_Object* val) {
    // must recast from non const value
    ASN1_Choice* choiceVal = static_cast<ASN1_Choice*>(val);
    if (newChoiceIndex != -1)
      choiceVal->SetSelectedChoice(newChoiceIndex);
    return true;
  }

  bool UI_ASN1_Node_Choice::GetHexValue(ASN1_Object*, ByteArray&) {
    QMessageBox::information(nullptr, "Cannot preview choice", "Complex nodes do not support the hexadecimal preview.");
    return false;
  }
}

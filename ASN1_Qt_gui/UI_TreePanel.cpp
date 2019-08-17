/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "UI_TreePanel.h"
#include "UI_Editor.h"

namespace UI {
  using namespace Utils;

  UI_TreePanel::UI_TreePanel(UI_Editor* parent, ASN1_Object* grammar = nullptr) :
    m_Parent(parent),
    m_Model(nullptr),
    m_Grammar(grammar),
    m_SearchPattern(""),
    m_ShowChoices(true),
    m_SearchInValue(false) {
    m_Tree = new MyTreeView(parent);
    m_Tree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_Tree->header()->hide();
    m_Tree->setSelectionMode(QAbstractItemView::SingleSelection);

    if (m_Grammar) LoadGrammar(m_Grammar);
    m_Tree->setExpandsOnDoubleClick(false);

    m_Tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_Tree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onCustomContextMenu(const QPoint&)));

    QObject::connect(m_Tree, SIGNAL(EnterPressed(QModelIndex)), this, SLOT(ShowNode(QModelIndex)));
    QObject::connect(m_Tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ShowNode(QModelIndex)));

    m_TreeLayout = new QHBoxLayout();
    m_TreeLayout->setContentsMargins(8, 8, 8, 8);
    m_TreeLayout->addWidget(CreateTreeOptions(parent));
    m_TreeLayout->addWidget(m_Tree);
  }

  QLayout* UI_TreePanel::GetTreeLayout() {
    return m_TreeLayout;
  }

  // ---------  CONTEXT MENU ----------
  QMenu* UI_TreePanel::MakeContextMenu(const ASN1_Item* node) const {
    QMenu* contextMenu = new QMenu(m_Tree);
    if (node->getGrammarObject() != nullptr) {
      contextMenu->addAction("Write From Node", m_Parent, SLOT(action_Write()));
      contextMenu->addAction("Read On Node", m_Parent, SLOT(action_Read()));
      contextMenu->addSeparator();

      switch (node->getGrammarObject()->GetType()) {
      case cBitString: contextMenu->addAction("Bit String Converter", m_Parent, SLOT(action_ConvertBitString())); break;
      case cBoolean: contextMenu->addAction("Boolean Converter", m_Parent, SLOT(action_ConvertBoolean())); break;
      case cEnumerated: contextMenu->addAction("Enumerated Converter", m_Parent, SLOT(action_ConvertEnumerated())); break;
      case cInteger: contextMenu->addAction("Integer Converter", m_Parent, SLOT(action_ConvertInteger())); break;
      case cIA5String: contextMenu->addAction("IA5 String Converter", m_Parent, SLOT(action_ConvertIA5String())); break;
      case cObjectID: contextMenu->addAction("Object ID Converter", m_Parent, SLOT(action_ConvertObjectID())); break;
      case cOctetString: contextMenu->addAction("Octet String Converter", m_Parent, SLOT(action_ConvertOctetString())); break;
      case cReal: contextMenu->addAction("Real Converter", m_Parent, SLOT(action_ConvertReal())); break;
      case cUTCTime: contextMenu->addAction("UTC Time Converter", m_Parent, SLOT(action_ConvertUTCTime())); break;
      case cUTF8String: contextMenu->addAction("UTF8 String Converter", m_Parent, SLOT(action_ConvertUTF8String())); break;
      case cChoice: contextMenu->addAction("Select Choice", this, SLOT(QuickActionChoiceSelect())); break;
      case cSequenceOf: contextMenu->addAction("Add Object", this, SLOT(QuickActionSeqOfAddObject())); break;
      default: break;
      }

      contextMenu->addSeparator();
      if (node->getGrammarObject()->GetMyOwner() != nullptr && node->getGrammarObject()->GetMyOwner()->GetType() == cSequenceOf) {
        contextMenu->addAction("Move Up", this, SLOT(QuickActionSeqOfMoveUp()));
        contextMenu->addAction("Move Down", this, SLOT(QuickActionSeqOfMoveDown()));
        contextMenu->addAction("Delete", this, SLOT(QuickActionSeqOfDelete()));
      }
    }
    return contextMenu;
  }

  void UI_TreePanel::onCustomContextMenu(const QPoint& point) {
    QModelIndex index = m_Tree->indexAt(point);
    if (index.isValid()) {
      ASN1_Item* node = static_cast<ASN1_Item*>(m_Model->itemFromIndex(index));
      MakeContextMenu(node)->exec(m_Tree->mapToGlobal(point));
    }
  }

  // ---------  OPTIONS  ---------
  void UI_TreePanel::ToggleSearchInValue(bool searchInValue) {
    m_SearchInValue = searchInValue;
  }

  void UI_TreePanel::SetPatternText(QString pattern) {
    m_SearchPattern = pattern;
  }


  // ---------  TREE ACTIONS  ---------
  void UI_TreePanel::SearchPattern(const QString& pat, bool InVal) {
    QString localPattern = pat.toUpper();
    bool IsHexPattern = IsHex(localPattern.toStdString().c_str());

    ASN1_Item* node = GetNextNode(GetCurrentSelectedItem());
    ASN1_Item* initialNode = node;

    while (true) {
      ASN1_Object* obj = node->getGrammarObject();

      QString stExtr = QString(obj->StringExtractForResearch().c_str()).toUpper();

      if (stExtr.contains(localPattern)) {
        SelectAndExpandNode(node);
        break;
      }

      if (InVal && IsHexPattern && QString(obj->GetHexBuffer().GetString()).contains(localPattern)) {
        SelectAndExpandNode(node);
        break;
      }

      node = GetNextNode(node);
      if (node == initialNode) {
        QMessageBox alert(QMessageBox::Information, "Search", "Pattern not found.", QMessageBox::Ok);
        alert.exec();
        break;
      }
    }
  }

  void UI_TreePanel::ButtonSearchPressed() {
    if (m_SearchPattern.isEmpty())
      return;
    m_Parent->SetMainStatus("search...");
    SearchPattern(m_SearchPattern, m_SearchInValue);
  }

  void UI_TreePanel::ToggleShowChoiceNodes(bool show) {
    m_ShowChoices = show;
    SelectAndExpandNode(RefreshBranch(static_cast<ASN1_Item*>(m_Model->item(0, 0))));
  }

  // ---------  QUICK ACTIONS  ---------
  void UI_TreePanel::QuickActionSeqOfAddObject() {
    static_cast<ASN1_SequenceOf*>(m_SelectedItem->getGrammarObject())->AppendNewObject();
    QModelIndex idx = m_SelectedItem->index();
    RefreshBranch(m_SelectedItem);
    ASN1_Item* tmp = static_cast<ASN1_Item*>(m_Model->itemFromIndex(idx));
    SelectAndExpandNode(tmp);
  }

  void UI_TreePanel::QuickActionChoiceSelect() {
    ASN1_Choice* choice = static_cast<ASN1_Choice*>(m_SelectedItem->getGrammarObject());

    QDialog d(m_Parent);
    QDialogButtonBox* b = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &d);

    QVBoxLayout* l = new QVBoxLayout(&d);
    QListWidget* listWid = new QListWidget(&d);
    l->addWidget(listWid);
    l->addWidget(b);
    connect(b, SIGNAL(accepted()), &d, SLOT(accept()));
    connect(b, SIGNAL(rejected()), &d, SLOT(reject()));
    connect(listWid, SIGNAL(doubleClicked(QModelIndex)), &d, SLOT(accept()));

    choice->MakeDummyChoiceList();
    for (unsigned int i = 0; i < choice->AvailableChoices(); i++)
      listWid->addItem(choice->GetChoiceFromIndex(i)->GetName().c_str());

    if (d.exec() == QDialog::Accepted) {
      QModelIndexList l = listWid->selectionModel()->selectedIndexes();
      QModelIndex listIdx = l.size() > 0 ? l.at(0) : QModelIndex();
      int choiceIdx = listIdx.row();
      choice->SetSelectedChoice(choiceIdx);

      QModelIndex idxInTree = m_SelectedItem->index();
      RefreshBranch(m_SelectedItem);
      ASN1_Item* tmp = static_cast<ASN1_Item*>(m_Model->itemFromIndex(idxInTree));
      SelectAndExpandNode(tmp);
    }
    choice->DeleteDummyChoiceList();
  }

  void UI_TreePanel::QuickActionSeqOfMoveUp() {
    ASN1_Item* par = static_cast<ASN1_Item*>(m_SelectedItem->parent());
    ASN1_SequenceOf* seqOf = static_cast<ASN1_SequenceOf*>(par->getGrammarObject());
    unsigned int idx = m_SelectedItem->row();

    if (idx > 0) {
      QModelIndex parIdx = par->index();
      seqOf->MoveUpObject(idx);
      RefreshBranch(par);

      par = static_cast<ASN1_Item*>(m_Model->itemFromIndex(parIdx));
      SelectNode(static_cast<ASN1_Item*>(par->child(idx - 1)));
    }
  }

  void UI_TreePanel::QuickActionSeqOfMoveDown() {
    ASN1_Item* par = static_cast<ASN1_Item*>(m_SelectedItem->parent());
    ASN1_SequenceOf* seqOf = static_cast<ASN1_SequenceOf*>(par->getGrammarObject());
    unsigned int idx = m_SelectedItem->row();

    if (idx < seqOf->GetSequenceOfSize() - 1) {
      QModelIndex parIdx = par->index();
      seqOf->MoveDownObject(idx);
      RefreshBranch(par);

      par = static_cast<ASN1_Item*>(m_Model->itemFromIndex(parIdx));
      SelectNode(static_cast<ASN1_Item*>(par->child(idx + 1)));
    }
  }

  void UI_TreePanel::QuickActionSeqOfDelete() {
    ASN1_Item* seqOfItem = static_cast<ASN1_Item*>(m_SelectedItem->parent());
    ASN1_SequenceOf* seqOf = static_cast<ASN1_SequenceOf*>(seqOfItem->getGrammarObject());
    unsigned int idx_row = m_SelectedItem->row();
    QModelIndex parIdx = seqOfItem->index();

    seqOf->DeleteObjectAt(idx_row);
    RefreshBranch(seqOfItem);

    seqOfItem = static_cast<ASN1_Item*>(m_Model->itemFromIndex(parIdx));
    if (idx_row > 0)
      SelectNode(static_cast<ASN1_Item*>(seqOfItem->child(idx_row - 1)));
    else if (idx_row == 0 && seqOf->GetSequenceOfSize() > 0)
      SelectNode(static_cast<ASN1_Item*>(seqOfItem->child(0)));
    else
      SelectNode(seqOfItem);
  }


  // ---------  DISPLAY  ---------
  void UI_TreePanel::SelectNode(ASN1_Item* item) {
    QStandardItem* tempItem = item;
    while (tempItem->parent() != nullptr) {
      tempItem = tempItem->parent();
      m_Tree->expand(tempItem->index());
    }
    m_Tree->scrollTo(item->index());
    m_Tree->selectionModel()->setCurrentIndex(item->index(), QItemSelectionModel::ClearAndSelect);
  }

  void UI_TreePanel::SelectAndExpandNode(ASN1_Item* item) {
    m_Tree->expand(item->index());
    SelectNode(item);
  }

  ASN1_Item* UI_TreePanel::RefreshBranch(ASN1_Item* fromItem) {
    ASN1_Object* grammar = fromItem->getGrammarObject();
    QStandardItem* parent = fromItem->parent() ? fromItem->parent() : nullptr;
    ASN1_Item* newItem;

    QItemSelectionModel* treeSel = m_Tree->selectionModel();
    QObject::disconnect(treeSel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(RefreshQuickActions(QModelIndex)));

    if (parent != nullptr) {
      int idx = fromItem->row();
      parent->removeRow(idx);
      newItem = ASN1_ItemModel::BuildModelRecurent(grammar, m_ShowChoices);
      parent->insertRow(idx, newItem);
    }
    else {
      m_Model->removeRow(0, QModelIndex());
      newItem = ASN1_ItemModel::BuildModelRecurent(grammar, m_ShowChoices);
      m_Model->insertRow(0, newItem);
    }
    QObject::connect(treeSel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(RefreshQuickActions(QModelIndex)));
    return newItem;
  }

  void UI_TreePanel::RefreshSelectedNode() {
    ASN1_Item* item = GetCurrentSelectedItem();
    item = RefreshBranch(item);
    SelectAndExpandNode(item);
  }

  void UI_TreePanel::RefreshTree() {
    SelectAndExpandNode(RefreshBranch(static_cast<ASN1_Item*>(m_Model->item(0, 0))));
  }

  void UI_TreePanel::ShowNode(QModelIndex idx) {
    QStandardItem* qsi = static_cast<QStandardItemModel*>(m_Tree->model())->itemFromIndex(idx);
    ASN1_Object* GrammarNode = static_cast<ASN1_Item*>(qsi)->getGrammarObject();

    UI_ASN1_ValueMain_Editable valueWindow(GrammarNode, m_Parent);
    if (valueWindow.exec() == QDialog::Accepted) {
      if (m_Tree->isExpanded(qsi->index()))
        SelectAndExpandNode(RefreshBranch(GetCurrentSelectedItem()));
      else
        SelectNode(RefreshBranch(GetCurrentSelectedItem()));
    }
  }

  void UI_TreePanel::RefreshQuickActions(QModelIndex idx) {
    QStandardItem* qsi = static_cast<QStandardItemModel*>(m_Tree->model())->itemFromIndex(idx);

    QItemSelectionModel* treeSel = m_Tree->selectionModel();
    QObject::disconnect(treeSel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(RefreshQuickActions(QModelIndex)));

    QLayoutItem* child;
    while ((child = m_UIQuickActionsLayout->takeAt(0)) != nullptr) {
      if (child->widget()) child->widget()->setParent(nullptr);
      delete child;
    }

    m_SelectedItem = static_cast<ASN1_Item*>(qsi);
    if (m_SelectedItem == nullptr) return;

    ASN1_Object* grammar = m_SelectedItem->getGrammarObject();
    if (!grammar) return;

    QString p = ":/img/img/icon_set_2/";
    bool empty = true;
    if (grammar->GetType() == cChoice) {
      ClickableLabel* selectChoice = MakeClickableLabel("commonButton", "Select choice", p + "select.png", m_UIQuickActionsBox, QSize(25, 25));
      QObject::connect(selectChoice, SIGNAL(clicked(bool)), this, SLOT(QuickActionChoiceSelect()));
      m_UIQuickActionsLayout->addWidget(selectChoice, 0, 0);
      empty = false;
    }
    else if (grammar->GetType() == cSequenceOf) {
      ClickableLabel* addObject = MakeClickableLabel("commonButton", "Add Object", p + "plus.png", m_UIQuickActionsBox, QSize(25, 25));
      QObject::connect(addObject, SIGNAL(clicked(bool)), this, SLOT(QuickActionSeqOfAddObject()));
      m_UIQuickActionsLayout->addWidget(addObject, 0, 0);
      empty = false;
    }
    if (grammar->GetMyOwner() != nullptr && grammar->GetMyOwner()->GetType() == cSequenceOf) {
      ClickableLabel* moveUp = MakeClickableLabel("commonButton", "Move Up", p + "up.png", m_UIQuickActionsBox, QSize(25, 25));
      ClickableLabel* moveDown = MakeClickableLabel("commonButton", "Move Down", p + "down.png", m_UIQuickActionsBox, QSize(25, 25));
      ClickableLabel* deleteObj = MakeClickableLabel("commonButton", "Delete", p + "minus.png", m_UIQuickActionsBox, QSize(25, 25));

      QObject::connect(moveUp, SIGNAL(clicked(bool)), this, SLOT(QuickActionSeqOfMoveUp()));
      QObject::connect(moveDown, SIGNAL(clicked(bool)), this, SLOT(QuickActionSeqOfMoveDown()));
      QObject::connect(deleteObj, SIGNAL(clicked(bool)), this, SLOT(QuickActionSeqOfDelete()));

      if (m_UIQuickActionsLayout->count() > 0) {
        m_UIQuickActionsLayout->addWidget(deleteObj, 0, 1);
        m_UIQuickActionsLayout->addWidget(moveUp, 1, 0);
        m_UIQuickActionsLayout->addWidget(moveDown, 1, 1);
      }
      else {
        m_UIQuickActionsLayout->addWidget(moveUp, 0, 0);
        m_UIQuickActionsLayout->addWidget(moveDown, 0, 1);
        m_UIQuickActionsLayout->addWidget(deleteObj, 1, 0);
      }

      empty = false;
    }
    if (empty)
      m_UIQuickActionsLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Maximum), 0, 0);

    treeSel = m_Tree->selectionModel();
    QObject::connect(treeSel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(RefreshQuickActions(QModelIndex)));
  }

  void UI_TreePanel::LoadGrammar(ASN1_Object* newGrammar) {
    ASN1_ItemModel* prevmodel = m_Model;
    m_Model = new ASN1_ItemModel(newGrammar, m_ShowChoices);
    m_Tree->setModel(m_Model);
    m_Grammar = newGrammar;

    QItemSelectionModel* treeSel = m_Tree->selectionModel();
    QObject::connect(treeSel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(RefreshQuickActions(QModelIndex)));

    delete prevmodel;
    SelectAndExpandNode(static_cast<ASN1_Item*>(m_Model->itemFromIndex(m_Model->index(0, 0))));
  }

  // --------- SELECTION ---------
  QModelIndex UI_TreePanel::GetCurrentSelectedIndex() const {
    QModelIndexList list = m_Tree->selectionModel()->selectedIndexes();
    return list.size() > 0 ? list.at(0) : QModelIndex();
  }

  ASN1_Item* UI_TreePanel::GetCurrentSelectedItem() const {
    QModelIndex node = GetCurrentSelectedIndex();
    return static_cast<ASN1_Item*>(node.isValid() ? m_Model->itemFromIndex(node) : m_Model->item(0, 0));
  }

  ASN1_Object* UI_TreePanel::SelectedGrammarNode() {
    return GetCurrentSelectedItem()->getGrammarObject();
  }

  ASN1_Item* UI_TreePanel::GetNextNode(ASN1_Item* OfNode) const {
    QModelIndex node = OfNode->index();

    // try to get a child
    QStandardItem* result = m_Model->itemFromIndex(node.child(0, 0));

    // try to get next node on same level
    if (result == nullptr) result = m_Model->itemFromIndex(node.parent().child(node.row() + 1, 0));

    // if no more node, step back to father and get next (may need to go back on several fathers if we go several levels higher)
    while (result == nullptr && node != QModelIndex()) {
      node = node.parent();
      result = m_Model->itemFromIndex(node.parent().child(node.row() + 1, 0));
    }

    // if still null, return root node
    if (result == nullptr) result = m_Model->item(0, 0);

    return static_cast<ASN1_Item*>(result);
  }

  ASN1_Item* UI_TreePanel::GetPrevNode(ASN1_Item* OfNode) const {
    QModelIndex node = OfNode->index();
    QStandardItem* result = m_Model->itemFromIndex(node.child(0, 0));

    result = m_Model->itemFromIndex(node.parent().child(node.row() - 1, 0));
    if (result == nullptr) result = m_Model->itemFromIndex(node.parent().child(node.row(), 0));
    return static_cast<ASN1_Item*>(result);
  }


  // --------- UI CREATION ---------
  QWidget* UI_TreePanel::CreateSearchBox(QWidget* parent) {
    QGroupBox* box = new QGroupBox("Search", parent);
    box->setObjectName("treeOptBox");
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    QVBoxLayout* verticalLayout = new QVBoxLayout(box);
    QCheckBox* SearchInVal = new QCheckBox("In values", box);
    SearchInVal->setToolTip("Include the values in the research.");
    SearchLineEdit* patternEdit = new SearchLineEdit(box);

    QString p = ":/img/img/icon_set_2/";
    ClickableLabel* pushButtonSearch = MakeClickableLabel("commonButton", "Search", p + "search.png", box, QSize(25, 25));

    QHBoxLayout* hl = new QHBoxLayout();
    hl->addWidget(pushButtonSearch);
    hl->addWidget(SearchInVal);

    verticalLayout->addWidget(new QLabel("Pattern:", box));
    verticalLayout->addWidget(patternEdit);
    verticalLayout->addLayout(hl);

    QObject::connect(SearchInVal, SIGNAL(clicked(bool)), this, SLOT(ToggleSearchInValue(bool)));
    QObject::connect(patternEdit, SIGNAL(textChanged(QString)), this, SLOT(SetPatternText(QString)));
    QObject::connect(patternEdit, SIGNAL(EnterPressed()), this, SLOT(ButtonSearchPressed()));
    QObject::connect(pushButtonSearch, SIGNAL(clicked(bool)), this, SLOT(ButtonSearchPressed()));
    return box;
  }

  QWidget* UI_TreePanel::CreateViewOptionsBox(QWidget* parent) {
    QGroupBox* box = new QGroupBox("View options", parent);
    box->setObjectName("treeOptBox");
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QVBoxLayout* verticalLayout = new QVBoxLayout(box);
    QCheckBox* showChoiceNodes = new QCheckBox("Show Choices", box);

    QString p = ":/img/img/icon_set_2/";
    ClickableLabel* collapseAll = MakeClickableLabel("commonButton", "Collapse Tree", p + "collapse.png", box, QSize(25, 25));
    ClickableLabel* expandAll = MakeClickableLabel("commonButton", "Expand Tree", p + "expand.png", box, QSize(25, 25));

    QHBoxLayout* hl = new QHBoxLayout();

    hl->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
    hl->addWidget(collapseAll);
    hl->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
    hl->addWidget(expandAll);
    hl->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));

    showChoiceNodes->setChecked(m_ShowChoices);

    verticalLayout->addWidget(showChoiceNodes);
    verticalLayout->addLayout(hl);

    QObject::connect(showChoiceNodes, SIGNAL(clicked(bool)), this, SLOT(ToggleShowChoiceNodes(bool)));
    QObject::connect(collapseAll, SIGNAL(clicked(bool)), m_Tree, SLOT(collapseAll()));
    QObject::connect(expandAll, SIGNAL(clicked(bool)), m_Tree, SLOT(expandAll()));

    return box;
  }

  QWidget* UI_TreePanel::CreateQuickActionsBox(QWidget* parent) {
    m_UIQuickActionsBox = new QGroupBox("Node actions", parent);
    m_UIQuickActionsBox->setObjectName("treeOptBox");
    m_UIQuickActionsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    m_UIQuickActionsLayout = new QGridLayout(m_UIQuickActionsBox);
    return m_UIQuickActionsBox;
  }

  QWidget* UI_TreePanel::CreateTreeOptions(QWidget* parent) {
    QWidget* wid = new QWidget(parent);
    wid->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    QVBoxLayout* verticalLayout = new QVBoxLayout(wid);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(CreateSearchBox(wid));
    verticalLayout->addWidget(CreateViewOptionsBox(wid));
    verticalLayout->addWidget(CreateQuickActionsBox(wid));
    QSpacerItem* verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    verticalLayout->addItem(verticalSpacer);

    return wid;
  }

}

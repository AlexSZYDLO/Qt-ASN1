/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once
#include "Nodes/UI_ASN1_Value_Main.h"
#include "ASN1_TreeModel.h"

namespace UI {
  class UI_Editor;

  class UI_TreePanel : public QObject {
    Q_OBJECT

   private:
    UI_Editor* m_Parent;
    QLayout* m_TreeLayout;
    MyTreeView* m_Tree;

    ASN1_ItemModel* m_Model;
    std::shared_ptr<ASN1_Object> m_Grammar;

    ASN1_Item* m_SelectedItem;
    QString m_SearchPattern;
    bool m_ShowChoices;
    bool m_SearchInValue;


    void SelectNode(ASN1_Item* item);
    void SelectAndExpandNode(ASN1_Item* item);
    ASN1_Item* RefreshBranch(ASN1_Item* fromItem);

    QModelIndex GetCurrentSelectedIndex() const;
    ASN1_Item* GetCurrentSelectedItem() const;
    ASN1_Item* GetNextNode(ASN1_Item* OfNode) const;
    ASN1_Item* GetPrevNode(ASN1_Item* OfNode) const;
    void SearchPattern(const QString& pat, bool InVal);

    // UI creation
    QGroupBox* m_UIQuickActionsBox;
    QGridLayout* m_UIQuickActionsLayout;

    QWidget* CreateSearchBox(QWidget* parent);
    QWidget* CreateTreeOptions(QWidget* parent);
    QWidget* CreateViewOptionsBox(QWidget* parent);
    QWidget* CreateQuickActionsBox(QWidget* parent);

    QMenu* MakeContextMenu(const ASN1_Item* node) const;

   public slots:
    void ToggleSearchInValue(bool searchInValue);
    void ToggleShowChoiceNodes(bool show);
    void SetPatternText(QString pattern);

    void ShowNode(QModelIndex idx);
    void RefreshQuickActions(QModelIndex idx);

    void QuickActionSeqOfAddObject();
    void QuickActionChoiceSelect();
    void QuickActionSeqOfMoveUp();
    void QuickActionSeqOfMoveDown();
    void QuickActionSeqOfDelete();

    void ButtonSearchPressed();
    void onCustomContextMenu(const QPoint& point);

   public:
    UI_TreePanel(UI_Editor* parent, std::shared_ptr<ASN1_Object>);

    void LoadGrammar(std::shared_ptr<ASN1_Object> newGrammar);
    QLayout* GetTreeLayout();
    ASN1_Object* SelectedGrammarNode();
    void RefreshSelectedNode();
    void RefreshTree();
  };
}

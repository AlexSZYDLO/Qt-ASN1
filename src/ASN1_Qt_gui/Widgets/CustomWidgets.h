/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QtWidgets>

namespace UI {
  class myQTextEdit : public QPlainTextEdit {
    Q_OBJECT
    using QPlainTextEdit::QPlainTextEdit;
   public:
    enum  cLineEditType {
      cLineEditBinary,
      cLineEditNumeric,
      cLineEditHexa,
      cLineEditOID,
      cLineEditIA5String,
      cLineEditUTF8String
    };
    myQTextEdit(QWidget* parent, cLineEditType aType);
    QString toTextWithoutSpace() const;

    bool CorrectOddHexa();

   protected:
    cLineEditType filterType;
    const int cPackSize;

    QString prevText;
    int prevCursorPos;

    bool bCheckText;
    bool bInsertSpaces;

    static int GetPackSize(myQTextEdit::cLineEditType type);
    int CalculateCursorLocation(int textSizeWithoutSpaces) const;
    bool CheckValue(QString& text) const;

   public slots:
    void OnTextChanged();
  };

  class SearchLineEdit : public QLineEdit {
    Q_OBJECT
    using QLineEdit::QLineEdit;
   protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
   signals:
    void EnterPressed();
  };

  class MyTreeView : public QTreeView {
    Q_OBJECT
    using QTreeView::QTreeView;
   protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
   signals:
    void EnterPressed(QModelIndex);
  };

  class MyListView : public QListView {
    Q_OBJECT
    using QListView::QListView;
   protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
   signals:
    void EnterPressed(QModelIndex);
  };

  class ValueDialog : public QDialog {
    Q_OBJECT
    using QDialog::QDialog;
   protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
   signals:
    void EnterPressed();
    void EscapePressed();
  };

  class ClickableLabel : public QLabel {
    Q_OBJECT
    Q_PROPERTY(bool pressed READ IsPressed WRITE SetPressed)

   public:
    explicit ClickableLabel(QWidget* parent = 0);
    ~ClickableLabel();
    bool m_Clicked; // keeps the press event until it is released
   signals:
    void clicked(bool);
    void rightClicked(bool);
   protected:
    bool pressed; // true while m_Clicked is true, AND mouse is on the widget
    bool IsPressed() const;
    void SetPressed(bool _pressed);

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    // void mouseMoveEvent(QMouseEvent* event) override;
  };

  ClickableLabel* MakeClickableLabel(const QString& name, const QString& tooltip, const QString& icon, QWidget* parent, QSize size = QSize(30, 30));
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "CustomWidgets.h"
#include "Utils.h"
#include <limits>

namespace UI {

// ------------------- myQTextEdit --------------------

  int myQTextEdit::GetPackSize(myQTextEdit::cLineEditType type) {
    if (type == cLineEditBinary) return 8;
    if (type == cLineEditHexa) return 2;
    else return std::numeric_limits<int>::max(); // should be enough not to be reached
  }

  myQTextEdit::myQTextEdit(QWidget* parent, cLineEditType aType) : QPlainTextEdit(parent), filterType(aType),
    bCheckText(true), bInsertSpaces(true), cPackSize(GetPackSize(aType)) {
    QObject::connect(this, SIGNAL(textChanged()), this, SLOT(OnTextChanged()));
  }

  QString myQTextEdit::toTextWithoutSpace() const {
    return toPlainText().replace(" ", "");
  }

  int myQTextEdit::CalculateCursorLocation(int textSizeWithoutSpaces) const {
    int spaceCount = floor(textSizeWithoutSpaces / cPackSize); // text does not contain spaces
    spaceCount += (spaceCount != 0 && textSizeWithoutSpaces % cPackSize == 0) ? -1 : 0; // remove 1 if even since we must not count the space at end

    int cursorPos =  textSizeWithoutSpaces + spaceCount;
    if (cursorPos < 0) cursorPos = 0;
    return cursorPos;
  }

  bool myQTextEdit::CorrectOddHexa() {
    if (filterType == cLineEditHexa) {
      if (toTextWithoutSpace().size() % 2 != 0) {
        if (QMessageBox::question(nullptr, "Wrong Hexadecimal format", "The value must be a sequence of 8 bits octets."
                                  "Do you want the value to be padded ? It will add a zero at the beginning.")
            == QMessageBox::Yes) {

          QString text = toPlainText();
          text.replace(' ', ""); text.replace('\n', ""); text.replace('\t', ""); text.replace('\r', "");

          ByteArray tempHex(text.toStdString().c_str());
          text = QString(tempHex.GetString()); // add padding if size is odd

          bCheckText = false;
          prevText = text;
          setPlainText(text);
          bCheckText = true;
          return true;
        }
        else return false;
      }
    }
    return true;
  }

  bool myQTextEdit::CheckValue(QString& text) const {
    if (filterType == cLineEditBinary || filterType == cLineEditNumeric || filterType == cLineEditHexa || filterType == cLineEditOID) {
      QRegExp regEx;
      if (filterType == cLineEditBinary) 	regEx.setPattern("^[01]*$");
      if (filterType == cLineEditNumeric) regEx.setPattern("^[0-9]*$");
      if (filterType == cLineEditHexa) 	regEx.setPattern("^[0-9a-fA-F]*$");
      if (filterType == cLineEditOID) 	regEx.setPattern("^[0-9.]*$");
      return regEx.exactMatch(text);
    }
    else if (filterType == cLineEditIA5String) {
      return Utils::IsValidIA5String(text.toUtf8().constData());
    }
    else if (filterType == cLineEditUTF8String) {
      return Utils::IsValidUTF8String(text.toUtf8().constData());
    }
    else return true;
  }

  void myQTextEdit::OnTextChanged() {
    QString textWithSpaces, text, textBeforCursor;
    int newCursorLocation = 0;

    textWithSpaces = toPlainText();
    text = textWithSpaces;
    textBeforCursor = textWithSpaces.left(textCursor().position()); // keep this text to reset the cursor after formatting

    if (filterType == cLineEditHexa || filterType == cLineEditBinary) {
      //text.replace(" ", "");
      text.replace(' ', ""); text.replace('\n', ""); text.replace('\t', ""); text.replace('\r', "");
      text = text.toUpper();
      //textBeforCursor.replace(" ", "");
      textBeforCursor.replace(' ', ""); textBeforCursor.replace('\n', ""); textBeforCursor.replace('\t', ""); textBeforCursor.replace('\r', "");
    }

    if (bInsertSpaces) {
      newCursorLocation = CalculateCursorLocation(textBeforCursor.size());
      //if ((newCursorLocation + 1) % 3 == 0) newCursorLocation++;
    }

    if (bCheckText) {
      int sizeDiff = text.size() - prevText.size();
      int cursor = textBeforCursor.size() - sizeDiff;
      prevCursorPos = CalculateCursorLocation(cursor); // end cursor position

      if (!CheckValue(text)) {
        bCheckText = false;
        setPlainText(prevText);
        bCheckText = true;

        QTextCursor newCur = textCursor();
        newCur.setPosition(prevCursorPos);
        setTextCursor(newCur);
        return;
      }
      else {
        //ByteArray tempHex(text.toStdString().c_str());
        //text = QString(tempHex.GetString()); // add padding if size is odd
        prevText = text;
      }
    }

    if (bInsertSpaces) {
      int i = cPackSize;
      while (i < text.size()) {
        text.insert(i, ' ');
        i += cPackSize + 1;
      }

      bCheckText = bInsertSpaces = false;
      setPlainText(text);
      bCheckText = bInsertSpaces = true;

      QTextCursor newCur = textCursor();
      newCur.setPosition(newCursorLocation);
      setTextCursor(newCur);
    }
  }

  // ------------------- SearchLineEdit --------------------

  void SearchLineEdit::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
      emit EnterPressed();
    QLineEdit::keyPressEvent(event);
  }

  // ------------------- MyTreeView --------------------

  void MyTreeView::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
      if (this->selectedIndexes().size() > 0)
        emit EnterPressed(this->selectedIndexes().at(0));
      else
        QTreeView::keyPressEvent(event);
    else
      QTreeView::keyPressEvent(event);
  }

  // ------------------- MyListView --------------------

  void MyListView::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
      if (this->selectedIndexes().size() > 0)
        emit EnterPressed(this->selectedIndexes().at(0));
      else
        QListView::keyPressEvent(event);
    else
      QListView::keyPressEvent(event);
  }

  // ------------------- ValueDialog --------------------

  void ValueDialog::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
      emit EnterPressed();
    else if (event->key() == Qt::Key_Escape)
      emit EscapePressed();
    else
      QDialog::keyPressEvent(event);
  }

// ----------------------- Clickable Label ------------------

  ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent) {
    m_Clicked = false;
    pressed = false;
  }

  ClickableLabel::~ClickableLabel() {
  }

  bool ClickableLabel::IsPressed() const { return pressed; }
  void ClickableLabel::SetPressed(bool _pressed) { pressed = _pressed; }

  void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    Qt::MouseButton b = event->button();
    if (b == Qt::LeftButton || b == Qt::RightButton) {
      m_Clicked = true;
      setProperty("pressed", true);
      style()->unpolish(this);
      style()->polish(this);
    }
    QLabel::mousePressEvent(event);
  }

  void ClickableLabel::mouseReleaseEvent(QMouseEvent* event) {
    Qt::MouseButton b = event->button();
    if (m_Clicked && rect().contains(event->pos())) {
      if (b == Qt::LeftButton)
        emit clicked(true);
      else if (b == Qt::RightButton)
        emit rightClicked(true);
      setProperty("pressed", false);
      style()->unpolish(this);
      style()->polish(this);
    }
    QLabel::mouseReleaseEvent(event);
  }

  void ClickableLabel::mouseMoveEvent(QMouseEvent* event) {
    if (!rect().contains(event->pos())) {
      setProperty("pressed", false);
    }
    else if (m_Clicked) {
      setProperty("pressed", true);
    }
    style()->unpolish(this);
    style()->polish(this);
    QLabel::mouseMoveEvent(event);
  }

  ClickableLabel* MakeClickableLabel(const QString& name, const QString& tooltip, const QString& icon, QWidget* parent, QSize size) {
    ClickableLabel* lbl = new ClickableLabel(parent);
    lbl->setObjectName(name);
    lbl->setPixmap(QPixmap(icon).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    lbl->setToolTip(tooltip);
    lbl->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    return lbl;
  }

}

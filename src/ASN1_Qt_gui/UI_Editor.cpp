/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "UI_Editor.h"
#include "UI_Main.h"
#include "UI_TreePanel.h"
#include "UI_Editor_Menus.h"

#include "ASN1_includes.h"
#include "Converters/UI_Converter.h"

using namespace Utils;

namespace UI {

  UI_Editor::UI_Editor(UI_Main* main) : QWidget(main), m_Main(main), m_Grammar(nullptr) {
    MakeEditorPane();
    SetGrammar(nullptr);
  }

  void UI_Editor::MakeEditorPane() {
    QVBoxLayout* mainLay = new QVBoxLayout(this);

    mainLay->setContentsMargins(1, 1, 1, 2); // l, t, r, b
    mainLay->setSpacing(2);
    mainLay->addWidget(CreateButtonBar());
    mainLay->addWidget(MakeSplitter(this));
  }

  QWidget* UI_Editor::CreateButtonBar() {
    UI_Editor_ButtonBar* bb = new UI_Editor_ButtonBar(m_Main, this);
    bb->setObjectName("actionBox");
    return bb;
  }

  QWidget* UI_Editor::MakeLeftPanel(QWidget* parent) {
    QGroupBox* box = new QGroupBox("Tree view", parent);
    box->setObjectName("panelBox");
    m_Tree = new UI_TreePanel(this, m_Grammar);
    QLayout* lay = m_Tree->GetTreeLayout();
    box->setLayout(lay);
    return box;
  }

  QWidget* UI_Editor::MakeRightPanel(QWidget* parent) {
    QGroupBox* box = new QGroupBox("Hexadecimal output/input", parent);
    box->setObjectName("panelBox");
    QVBoxLayout* verticalLayout = new QVBoxLayout(box);
    verticalLayout->setContentsMargins(8, 8, 8, 8);
    m_HexaTextEdit = new myQTextEdit(parent, myQTextEdit::cLineEditHexa);
    verticalLayout->addWidget(m_HexaTextEdit);
    return box;
  }

  QWidget* UI_Editor::MakeSplitter(QWidget* parent) {
    QSplitter* splitter = new QSplitter(parent);
    splitter->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setChildrenCollapsible(false);
    splitter->addWidget(MakeLeftPanel(parent));
    splitter->addWidget(MakeRightPanel(parent));
    return splitter;
  }

  UI_Editor::~UI_Editor() {
    if (m_Tree) delete m_Tree;
  }

  void UI_Editor::RefreshTree() {
    m_Tree->RefreshTree();
  }

  void UI_Editor::SetGrammar(std::shared_ptr<ASN1_Object> obj) {
    m_Grammar = obj;
    m_Tree->LoadGrammar(obj);
  }

  void UI_Editor::SetMainStatus(const QString& s) {
    m_Main->SetStatus(s);
  }

  void UI_Editor::Write(ASN1_Object* obj) {
    m_Main->SetStatus("Writing...");

    QApplication::setOverrideCursor(Qt::WaitCursor);
    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);

    m_HexaTextEdit->setPlainText(buffer.GetString());
    QApplication::restoreOverrideCursor();
    m_Main->SetStatus("Writing done.");
  }

  void UI_Editor::Read(ASN1_Object* obj) {
    m_Main->SetStatus("Reading...");
    char c[2001]{};

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (obj->ReadFromBuffer(m_HexaTextEdit->toTextWithoutSpace().toStdString().c_str(), c, 2000)) {
      m_Main->SetStatus("Reading done.");
      QApplication::restoreOverrideCursor();
    }
    else {
      m_Main->SetStatus("Reading failed.");
      QApplication::restoreOverrideCursor();
      QMessageBox box(QMessageBox::Critical, "Parsing error", c);
      box.exec();
    }
    if (m_Grammar.get() == obj)
      m_Tree->RefreshTree();
    else
      m_Tree->RefreshSelectedNode();
  }


// ---------------------- ACTIONS -------------------

  void UI_Editor::action_WriteAll() {
    if (!m_Grammar)
    {
      m_Main->SetStatus("Grammar not set, nothing to write.");
      return;
    }
    Write(m_Grammar.get());
  }

  void UI_Editor::action_ReadAll() {
    if (!m_Grammar)
    {
      m_Main->SetStatus("Grammar not set, cannot read.");
      return;
    }
    if (m_HexaTextEdit->CorrectOddHexa())
      Read(m_Grammar.get());
  }

  void UI_Editor::action_Write() {
    Write(m_Tree->SelectedGrammarNode());
  }

  void UI_Editor::action_Read() {
    if (m_HexaTextEdit->CorrectOddHexa())
      Read(m_Tree->SelectedGrammarNode());
  }

  void UI_Editor::action_Compare() {
    if (!m_Grammar)
    {
      m_Main->SetStatus("Grammar not set, nothing to compare with.");
      return;
    }

    m_Main->SetStatus("Compare...");

    QJSEngine* newEng = InitEngine();
    std::shared_ptr<ASN1_Object> secondTree = nullptr;

    if (!m_Main->GetLastCompGramm().isEmpty())
      secondTree = m_Main->CompToObj(m_Main->GetLastCompGramm(), true); // silent
    else if (!m_Main->GetLastScript().isEmpty())
      secondTree = m_Main->JSToObj(&newEng, m_Main->GetLastScript(), false, true); // no debug + silent

    if (secondTree != nullptr) {
      char c[2001]{};
      if (m_HexaTextEdit->CorrectOddHexa()) {
        if (!secondTree->ReadFromBuffer(m_HexaTextEdit->toTextWithoutSpace().toStdString().c_str(), c, 2000)) {
          m_Main->SetStatus("Compare failed at reading hexadecimal data.");
          QMessageBox box(QMessageBox::Critical, "Parsing error", c);
          box.exec();
        }
        else {
          unsigned int nbDiffs = 0;
          if (m_Grammar->Compare(*secondTree, nbDiffs, c, 2000)) {
            if (nbDiffs > 0) {
              QString str(c);
              QMessageBox box(QMessageBox::Information, "Comparison differences", str);
              box.exec();
              m_Main->SetStatus("Compare showed differences.");
            }
            else {
              m_Main->SetStatus("Compare done with no difference.");
            }
          }
          else {
            m_Main->SetStatus("Comparison failed, grammars are probably incompatible.");
          }
        }
      }
    }
    else {
      m_Main->SetStatus("Compare failed.");
    }

    ClearScriptEngine(newEng);
  }

  void UI_Editor::action_OpenHex() {
    QString fileName =
      QFileDialog::getOpenFileName(this, "Open Hexadecimal File",
                                   "", "Hexadecimal file (*.der *)");
    QFile f(fileName);
    if (f.open(QIODevice::ReadOnly)) {
      QString s(f.read(f.size()));
      m_HexaTextEdit->setPlainText(s);
    }
    f.close();
  }

  void UI_Editor::action_OpenASN() {
    QString fileName =
      QFileDialog::getOpenFileName(this, "Open ASN File",
                                   "", "Grammar file (*.asn *)");
    if (!fileName.isEmpty()) {
      QFile f(fileName);
      if (f.open(QFile::ReadOnly)) {
        QString asn = QTextStream(&f).readAll();
        QString js = m_Main->ASNToJS(asn);
        if (!js.isEmpty()) {
          m_Tree->LoadGrammar(m_Main->JSToObj(m_Main->GetScriptEngine(), js, false));
          m_Main->SetLastScript(js);
        }
      }
      else m_Main->SetStatus("Failed to open the file.");
    }
  }

  void UI_Editor::action_OpenScript() {
    QString fName = QFileDialog::getOpenFileName(this, "Open Script File", "", "JavaScript file (*.js *)");
    if (!fName.isEmpty()) {
      QFile f(fName);
      if (f.open(QFile::ReadOnly)) {
        m_Main->SetStatus("Reading grammar from script.");
        QString js = QTextStream(&f).readAll();
        m_Grammar = m_Main->JSToObj(m_Main->GetScriptEngine(), js, false);
        m_Tree->LoadGrammar(m_Grammar);
        m_Main->SetLastScript(js);
      }
      else m_Main->SetStatus("Failed to open the file.");
    }
  }

  void UI_Editor::action_RunScript() {
    QString fName = QFileDialog::getOpenFileName(this, "Open Script File", "", "JavaScript file (*.js *)");
    if (!fName.isEmpty()) {
      QFile f(fName);
      if (f.open(QFile::ReadOnly)) {
        m_Main->SetStatus("Processing additional script.");
        QString js = QTextStream(&f).readAll();
        m_Main->ProcessAdditionalJS(m_Main->GetScriptEngine(), js, false);
        RefreshTree();
      }
      else m_Main->SetStatus("Failed to open the file.");
    }
  }

  void UI_Editor::action_Save() {
    QString fileName =
      QFileDialog::getSaveFileName(this, "Save Hexadecimal File",
                                   "", "Hexadecimal files (*.der)");
    QFile f(fileName);
    if (f.open(QIODevice::WriteOnly))
      f.write(m_HexaTextEdit->toTextWithoutSpace().toStdString().c_str());
    f.close();
  }


  template <typename convType>
  void ShowConv(QWidget* parent) {
    convType* conv = new convType(parent);
    conv->exec();
  }

  void UI_Editor::action_ConvertBitString() { ShowConv<UI_ASN1_Converter_BitString>(this); }
  void UI_Editor::action_ConvertBoolean() { ShowConv<UI_ASN1_Converter_Boolean>(this); }
  void UI_Editor::action_ConvertEnumerated() { ShowConv<UI_ASN1_Converter_Enumerated>(this); }
  void UI_Editor::action_ConvertIA5String() { ShowConv<UI_ASN1_Converter_IA5String>(this); }
  void UI_Editor::action_ConvertInteger() { ShowConv<UI_ASN1_Converter_Integer>(this); }
  void UI_Editor::action_ConvertObjectID() { ShowConv<UI_ASN1_Converter_ObjectID>(this); }
  void UI_Editor::action_ConvertOctetString() { ShowConv<UI_ASN1_Converter_OctetString>(this); }
  void UI_Editor::action_ConvertReal() { ShowConv<UI_ASN1_Converter_Real>(this); }
  void UI_Editor::action_ConvertUTCTime() { ShowConv<UI_ASN1_Converter_UTCTime>(this); }
  void UI_Editor::action_ConvertUTF8String() { ShowConv<UI_ASN1_Converter_UTF8String>(this); }

}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "UI_GrammarASN.h"
#include "UI_Main.h"
#include "ASNHighlighter.h"

namespace UI {

  UI_GrammarASN::UI_GrammarASN(UI_Main* main) : QWidget(main), m_Main(main) {
    MakeASNGrammarPane();
  }

  QWidget* UI_GrammarASN::MakeMenuBar() {
    QWidget* buttonBarWidget = new QWidget(this);
    buttonBarWidget->setObjectName("actionBox");
    buttonBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QString p = ":/img/img/icon_set_2/";
    ClickableLabel* buttonToEditor = MakeClickableLabel("actionButton", "Process to editor", p + "run.png", this);
    ClickableLabel* buttonToJS = MakeClickableLabel("actionButton", "Process ASN grammar to JavaScript", p + "js.png", this);
    ClickableLabel* buttonToCPP = MakeClickableLabel("actionButton", "Process ASN grammar to C++", p + "cpp.png", this);
    ClickableLabel* buttonLoadScript = MakeClickableLabel("actionButton", "Open", p + "open.png", this);
    ClickableLabel* buttonSaveScript = MakeClickableLabel("actionButton", "Save", p + "save.png", this);

    QHBoxLayout* buttonLay = new QHBoxLayout();

    buttonLay->addWidget(buttonLoadScript);
    buttonLay->addWidget(buttonSaveScript);
    buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    buttonLay->addWidget(buttonToEditor);
    buttonLay->addWidget(buttonToJS);
    buttonLay->addWidget(buttonToCPP);
    buttonLay->addItem(new QSpacerItem(50, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
    buttonBarWidget->setLayout(buttonLay);
    buttonLay->setMargin(1);

    connect(buttonToEditor, SIGNAL(clicked(bool)), this, SLOT(ToEditor()));
    connect(buttonToJS, SIGNAL(clicked(bool)), this, SLOT(ToJS()));
    connect(buttonToCPP, SIGNAL(clicked(bool)), this, SLOT(ToCPP()));
    connect(buttonLoadScript, SIGNAL(clicked(bool)), this, SLOT(LoadASN()));
    connect(buttonSaveScript, SIGNAL(clicked(bool)), this, SLOT(SaveASN()));
    return buttonBarWidget;
  }

  void UI_GrammarASN::MakeASNGrammarPane() {
    QVBoxLayout* vLay = new QVBoxLayout(this);
    vLay->setContentsMargins(1, 1, 1, 2); // l, t, r, b
    vLay->setSpacing(2);

    QSplitter* editSplit = new QSplitter(this);
    editSplit->setChildrenCollapsible(false);
    editSplit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    editSplit->addWidget(MakeHintPanel(this));
    editSplit->addWidget(MakeASNEditor(this));
    editSplit->setStretchFactor(0, 1);
    editSplit->setStretchFactor(1, 3);

    vLay->addWidget(MakeMenuBar());
    vLay->addWidget(editSplit);
  }

  void UI_GrammarASN::SetASNGrammar(const QString& path) {
    QFile asnFile = path;
    if (asnFile.exists()) {
      asnFile.open(QFile::ReadOnly);
      QString asnContent = QTextStream(&asnFile).readAll();
      ASNedit->setPlainText(asnContent);
    }
  }

  QGroupBox* UI_GrammarASN::MakeASNEditor(QWidget* parent) {
    ASNedit = new DropablePlainTextEdit(parent);
    ASNedit->setTabStopWidth(40);
    ASNedit->setWordWrapMode(QTextOption::NoWrap);

    QGroupBox* boxASNEdit = new QGroupBox("ASN1 editor", parent);
    boxASNEdit->setObjectName("panelBox");
    QVBoxLayout* lay = new QVBoxLayout(boxASNEdit);
    lay->addWidget(ASNedit);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    ASNedit->setFont(font);
    new ASNHighlighter(ASNedit->document());


    return boxASNEdit;
  }

  void MakeASNHintList(QStandardItemModel* model) {
    QList<QStandardItem*> itemList;
    QList<QStandardItem*> subList;
    DraggableStandardItem* current;

    // Root
    subList = {
      new DraggableStandardItem("DEFINITIONS", "Keyword to put at the beginning of the module definitions.", ""),
      new DraggableStandardItem("AUTOMATIC TAGS", "Sets the tagging mode to automatic.", ""),
      new DraggableStandardItem("IMPLICIT TAGS", "Sets the tagging mode to implicit.", ""),
      new DraggableStandardItem("EXPLICIT TAGS", "Sets the tagging mode to explicit.", ""),
      new DraggableStandardItem("EXTENSIBILITY IMPLIED", "All Sequences and Set will be extensible.", ""),
      new DraggableStandardItem("BEGIN", "Keyword to start grammar definitions.", ""),
      new DraggableStandardItem("END", "Keyword to end grammar definition.", "")
    };
    current = new DraggableStandardItem("Main Options", "Generic keywords", "Not draggable", "", false);
    current->appendColumn(subList);
    itemList.push_back(current);
    subList.clear();

    QString t1 = "Name ::= SEQUENCE {\n\tvar TYPE,\n\tvar2 TYPE\n}";
    QString t2 = "Name ::= SEQUENCE OF TYPE";
    QString t3 = "Name ::= SET {\n\tvar TYPE,\n\tvar2 TYPE\n}";
    QString t4 = "Name ::= CHOICE {\n\tvar TYPE,\n\tvar2 TYPE\n}";
    subList = {
      new DraggableStandardItem("Sequence Template", "Template for Sequence module creation.", t1, t1),
      new DraggableStandardItem("Sequence Of Template", "Template for Sequence Of module creation.", t2, t2),
      new DraggableStandardItem("Set Template", "Template for Set module creation.", t3, t3),
      new DraggableStandardItem("Choice Template", "Template for Choice module creation.", t4, t4)
    };
    current = new DraggableStandardItem("Templates", "Templates to create modules", "Not draggable", "", false);
    current->appendColumn(subList);
    itemList.push_back(current);
    subList.clear();

    subList = {
      new DraggableStandardItem("OPTIONAL", "Makes the node optional"),
      new DraggableStandardItem("EXPLICIT", "Set explicit tagging mode for the node."),
      new DraggableStandardItem("IMPLICIT", "Set implicit tagging mode for the node."),
      new DraggableStandardItem("[UNIVERSAL x]", "Private tag."),
      new DraggableStandardItem("[CONTEXT SPECIFIC x]", "Context specific tag."),
      new DraggableStandardItem("[APPLICATION x]", "Application tag."),
      new DraggableStandardItem("[PRIVATE x]", "Private tag."),
      new DraggableStandardItem("...", "Extensibility marker."),
    };
    current = new DraggableStandardItem("Node Options", "Option keywords applicable to the nodes.", "Not draggable", "", false);
    current->appendColumn(subList);
    itemList.push_back(current);
    subList.clear();

    current = new DraggableStandardItem("BIT STRING", "Bit String node");
    itemList.push_back(current);
    current = new DraggableStandardItem("BOOLEAN", "Boolean node");
    itemList.push_back(current);
    current = new DraggableStandardItem("CHOICE", "Choice node");
    itemList.push_back(current);
    current = new DraggableStandardItem("ENUMERATED", "Enumerated node");
    itemList.push_back(current);
    current = new DraggableStandardItem("IA5String", "IA5 String node");
    itemList.push_back(current);
    current = new DraggableStandardItem("INTEGER", "Integer node");
    itemList.push_back(current);
    current = new DraggableStandardItem("NULL", "Null node");
    itemList.push_back(current);
    current = new DraggableStandardItem("OBJECT IDENTIFIER", "Object Identifier node");
    itemList.push_back(current);
    current = new DraggableStandardItem("OCTET STRING", "Octet String node");
    itemList.push_back(current);
    current = new DraggableStandardItem("REAL", "Real node");
    itemList.push_back(current);
    current = new DraggableStandardItem("SEQUENCE", "Sequence node");
    itemList.push_back(current);
    current = new DraggableStandardItem("SEQUENCE OF", "Sequence Of node");
    itemList.push_back(current);
    current = new DraggableStandardItem("SET", "Set node");
    itemList.push_back(current);
    current = new DraggableStandardItem("UTCTime", "UTC Time node");
    itemList.push_back(current);
    current = new DraggableStandardItem("UTF8String", "UTF8 String node");
    itemList.push_back(current);

    model->appendColumn(itemList);
  }

  QGroupBox* UI_GrammarASN::MakeHintPanel(QWidget* parent) {
    HintPanel = new DraggableTreeWidget(parent);
    HintPanel->setObjectName("hintTree");
    HintPanel->setHeaderHidden(true);

    MakeASNHintList(static_cast<QStandardItemModel*>(HintPanel->model()));

    QLabel* info = new QLabel("Drag and drop the keywords onto the editor.");
    info->setWordWrap(true);
    QFont f1(info->font());
    f1.setItalic(true);
    info->setFont(f1);

    QGroupBox* descBox = new QGroupBox("Description", parent);
    descBox->setObjectName("treeOptBox");
    descBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    QVBoxLayout* verticalLayout = new QVBoxLayout(descBox);

    HintText = new QLabel("select a function to get the description.");
    HintText->setWordWrap(true);
    verticalLayout->addWidget(HintText);

    QObject::connect(HintPanel->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(RefreshHint(QModelIndex)));

    QGroupBox* boxHints = new QGroupBox("Available functions", this);
    boxHints->setObjectName("panelBox");
    QVBoxLayout* lay2 = new QVBoxLayout(boxHints);
    lay2->addWidget(info);
    lay2->addWidget(HintPanel);
    lay2->addWidget(descBox);

    return boxHints;
  }

  void UI_GrammarASN::RefreshHint(const QModelIndex& i) {
    QStandardItem* item = static_cast<QStandardItemModel*>(HintPanel->model())->itemFromIndex(i);
    DraggableStandardItem* dItem = static_cast<DraggableStandardItem*>(item);
    HintText->setText(dItem->GetDesc());
  }

  void UI_GrammarASN::ToJS() {
    QString r = m_Main->ASNToJS(ASNedit->toPlainText());
    if (!r.isEmpty()) {
      m_Main->SetJSScript(r);
      m_Main->SelectTab(2);
    }
  }

  void UI_GrammarASN::ToCPP() {
    QString defaultFile;
    if (m_CppFile != "")
      defaultFile = m_CppFile;
    QString fileName = QFileDialog::getSaveFileName(this, "Save C++ File", defaultFile, "C++ file (*.cpp *)");
    if (fileName != "") {
      QFile f(fileName);
      if (f.open(QIODevice::WriteOnly)) {
        QString cpp = m_Main->ASNToCPP(ASNedit->toPlainText());
        f.write(cpp.toStdString().c_str());
        m_CppFile = defaultFile;
      }
    }
  }

  void UI_GrammarASN::ToEditor() {
    QString js = m_Main->ASNToJS(ASNedit->toPlainText());
    if (!js.isEmpty()) {
      ASN1_Object* o = m_Main->JSToObj(m_Main->GetScriptEngine(), js, false);
      m_Main->SetLastScript(js);
      m_Main->SetEditorObj(o);
      if (o != nullptr)
        m_Main->SelectTab(3);
    }
  }

  void UI_GrammarASN::LoadASN() {
    QString fileName =
      QFileDialog::getOpenFileName(this, "Open ASN File",
                                   "", "ASN file (*.asn *)");
    if (fileName != "") {
      QFile f(fileName);
      if (f.exists()) {
        m_LoadedASNFile = fileName;
        f.open(QFile::ReadOnly);
        QString asnContent = QTextStream(&f).readAll();
        ASNedit->setPlainText(asnContent);
        f.close();
      }
      else {
        QMessageBox box(QMessageBox::Critical, "Cannot open ASN file", "File does not exist");
        box.exec();
      }
    }
  }

  void UI_GrammarASN::SaveASN() {
    QString defaultFile;
    if (m_LoadedASNFile != "")
      defaultFile = m_LoadedASNFile;
    QString fileName =
      QFileDialog::getSaveFileName(this, "Save ASN File",
                                   defaultFile, "ASN file (*.asn *)");
    QFile f(fileName);
    if (f.open(QIODevice::WriteOnly))
      f.write(ASNedit->toPlainText().toStdString().c_str());
    f.close();
  }
}

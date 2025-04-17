/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "UI_GrammarJS.h"
#include "UI_Main.h"
#include "JSHighlighter.h"


namespace UI {

  UI_GrammarJS::UI_GrammarJS(UI_Main* main) : QWidget(main), m_Main(main), m_JSDebug(false) {
    MakeJSGrammarPane();
  }

  QWidget* UI_GrammarJS::MakeMenuBar() {
    QWidget* buttonBarWidget = new QWidget(this);
    buttonBarWidget->setObjectName("actionBox");
    buttonBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QString p = ":/img/img/icon_set_2/";
    ClickableLabel* buttonLoadScript = MakeClickableLabel("actionButton", "Load JS file", p + "open.png", this);
    ClickableLabel* buttonSaveScript = MakeClickableLabel("actionButton", "Save to file", p + "save.png", this);
    ClickableLabel* buttonNewScript = MakeClickableLabel("actionButton", "Process as new script", p + "run.png", this);
    ClickableLabel* buttonRunScript = MakeClickableLabel("actionButton", "Run additional script", p + "plus.png", this);
    ClickableLabel* buttonDebug = MakeClickableLabel("actionButton", "Process to editor", p + "settings.png", this);

    QHBoxLayout* buttonLay = new QHBoxLayout();
    buttonLay->addWidget(buttonLoadScript);
    buttonLay->addWidget(buttonSaveScript);
    buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    buttonLay->addWidget(buttonNewScript);
    buttonLay->addWidget(buttonRunScript);
    buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    buttonLay->addWidget(buttonDebug);
    buttonLay->addItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLay->setContentsMargins(1, 1, 1, 1); // l, t, r, b

    buttonBarWidget->setLayout(buttonLay);

    connect(buttonLoadScript, SIGNAL(clicked(bool)), this, SLOT(LoadJSScript()));
    connect(buttonSaveScript, SIGNAL(clicked(bool)), this, SLOT(SaveJSScript()));
    connect(buttonNewScript, SIGNAL(clicked(bool)), this, SLOT(RunJSScript()));
    connect(buttonRunScript, SIGNAL(clicked(bool)), this, SLOT(RunAdditionalJSScript()));
    connect(buttonDebug, SIGNAL(clicked(bool)), this, SLOT(debugMenu()));
    return buttonBarWidget;
  }

  void UI_GrammarJS::debugMenu() {
    QMenu* menuConvert = new QMenu("Convert", m_Main);
    QAction* debug = new QAction("debug", m_Main);
    debug->setCheckable(true);
    debug->setChecked(m_JSDebug);
    QObject::connect(debug, SIGNAL(toggled(bool)), this, SLOT(ToggleJSDebugMode()));
    menuConvert->addAction(debug);

    QWidget* button = static_cast<QWidget*>(sender());
    menuConvert->exec(button->mapToGlobal(button->rect().bottomLeft()));
  }

  void UI_GrammarJS::MakeJSGrammarPane() {
    QVBoxLayout* vLay = new QVBoxLayout(this);
    vLay->setContentsMargins(1, 1, 1, 2); // l, t, r, b
    vLay->setSpacing(2);

    QSplitter* editSplit = new QSplitter(this);
    editSplit->setChildrenCollapsible(false);
    editSplit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    editSplit->addWidget(MakeHintPanel(this));
    editSplit->addWidget(MakeJSEditor(this));
    editSplit->setStretchFactor(0, 1);
    editSplit->setStretchFactor(1, 3);

    vLay->addWidget(MakeMenuBar());
    vLay->addWidget(editSplit);
  }

  QGroupBox* UI_GrammarJS::MakeJSEditor(QWidget* parent) {
    JSedit = new DropablePlainTextEdit(parent);
    JSedit->setTabStopDistance(40);
    JSedit->setWordWrapMode(QTextOption::NoWrap);

    QGroupBox* boxJSEdit = new QGroupBox("Script editor", parent);
    boxJSEdit->setObjectName("panelBox");
    QVBoxLayout* lay = new QVBoxLayout(boxJSEdit);
    lay->addWidget(JSedit);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    JSedit->setFont(font);
    new JSHighlighter(JSedit->document());

    return boxJSEdit;
  }

  void MakeJSHintList(QStandardItemModel* model) {
    QList<QStandardItem*> itemList;
    QList<QStandardItem*> subList;
    DraggableStandardItem* current;

    // Root
    subList = {
      new DraggableStandardItem("ClearDynamicData()", "Clears instances in sequence_of and reset choice nodes", "void ClearDynamicData()"),
      new DraggableStandardItem("registerGrammar()", "Makes the node the root node", "void registerGrammar()"),
      new DraggableStandardItem("setDescription()", "Only a description, not part of ASN1 standard", "void setDescription(string description)"),
      new DraggableStandardItem("setIgnoredByUser()", "If the node is optional, the node is ignored", "void setIgnoredByUser(bool ignore [<i>=true</i>])")
    };
    current = new DraggableStandardItem("Common Node ASN1", "Absrtact - Generic functions applicable to any node", "Not draggable", "", false);
    current->appendColumn(subList);
    itemList.push_back(current);

    // Bit String
    subList.clear();
    subList = {
      new DraggableStandardItem("getBitStringValue()", "Get the bitstring value.", "string getBitStringValue()"),
      new DraggableStandardItem("setBitStringValue()", "Set the bitstring value.", "void setBitStringValue(string value)")
    };
    current = new DraggableStandardItem("BitStringASN1()", "ASN1 BitString node constructor. To be used with 'new'.",
                                        "BitStringASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], BitStringASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Bool
    subList.clear();
    subList = {
      new DraggableStandardItem("getBooleanValue()", "Get the boolean value.", "bool getBooleanValue()"),
      new DraggableStandardItem("setBooleanValue()", "Set the boolean value.", "void setBooleanValue(bool value)")
    };
    current = new DraggableStandardItem("BooleanASN1()", "ASN1 Boolean node constructor. To be used with 'new'.",
                                        "BooleanASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], BooleanASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Enum
    subList.clear();
    subList = {
      new DraggableStandardItem("getEnumeratedValue()", "Get the enumerated value.", "int getEnumeratedValue()"),
      new DraggableStandardItem("setEnumeratedValue()", "Set the enumerated value.", "void setEnumeratedValue(int value)")
    };
    current = new DraggableStandardItem("EnumeratedASN1()", "ASN1 Enumerated node constructor. To be used with 'new'.",
                                        "EnumeratedASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], EnumeratedASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // IA5 String
    subList.clear();
    subList = {
      new DraggableStandardItem("getIA5StringValue()", "Get the ia5 string value.", "string getIA5StringValue()"),
      new DraggableStandardItem("setIA5StringValue()", "Set the ia5 string value.", "void setIA5StringValue(string value)")
    };
    current = new DraggableStandardItem("IA5StringASN1()", "ASN1 IA5String node constructor. To be used with 'new'.",
                                        "IA5StringASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], IA5StringASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Integer
    subList.clear();
    subList = {
      new DraggableStandardItem("getIntegerValue()", "Get the integer value.", "int getIntegerValue()"),
      new DraggableStandardItem("setIntegerValue()", "Set the integer value.", "void setIntegerValue(int value)")
    };
    current = new DraggableStandardItem("IntegerASN1()", "ASN1 Integer node constructor. To be used with 'new'.",
                                        "IntegerASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], IntegerASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Null
    current = new DraggableStandardItem("NullASN1()", "ASN1 Integer node constructor. To be used with 'new'.",
                                        "NullASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], IntegerASN1 defaultValue [<i>=null</i>])");
    itemList.push_back(current);

    // Object ID
    subList.clear();
    subList = {
      new DraggableStandardItem("getObjectIDValue()", "Get the object ID value.", "string getObjectIDValue()"),
      new DraggableStandardItem("setObjectIDValue()", "Set the object ID value.", "void setObjectIDValue(string value)")
    };
    current = new DraggableStandardItem("ObjectIDASN1()", "ASN1 ObjectID node constructor. To be used with 'new'.",
                                        "ObjectIDASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], ObjectIDASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Octet string
    subList.clear();
    subList = {
      new DraggableStandardItem("getOctetStringValue()", "Get the octet string value.", "string getOctetStringValue()"),
      new DraggableStandardItem("setOctetStringValue()", "Set the octet string value.", "void setOctetStringValue(string value)")
    };
    current = new DraggableStandardItem("OctetStringASN1()", "ASN1 OctetString node constructor. To be used with 'new'.",
                                        "OctetStringASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], OctetStringASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Real
    subList.clear();
    subList = {
      new DraggableStandardItem("getRealValue()", "Get the real value.", "double getRealValue()"),
      new DraggableStandardItem("setRealValue()", "Set the real value.", "void setRealValue(double value)")
    };
    current = new DraggableStandardItem("RealASN1()", "ASN1 Real node constructor. To be used with 'new'.",
                                        "RealASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], RealASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // UTC Time
    subList.clear();
    subList = {
      new DraggableStandardItem("getUTCTimeValue()", "Get the utc time value.", "string getUTCTimeValue()"),
      new DraggableStandardItem("setUTCTimeValue()", "Set the utc time value. The time zone sign can have the values: UTCTimeASN1.[Plus/Minus/GMT]",
      "void setUTCTimeValue(int year, int month, int day, int hours, int minutes, int seconds, TimeZoneSign TZSign, int TZHours, int TZMinutes)")
    };
    current = new DraggableStandardItem("UTCTimeASN1()", "ASN1 UTCTime node constructor. To be used with 'new'.",
                                        "UTCTimeASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], UTCTimeASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // UTF8 String
    subList.clear();
    subList = {
      new DraggableStandardItem("getUTF8StringValue()", "Get the utf8 string value.",
      "string getUTF8StringValue()"),
      new DraggableStandardItem("setUTF8StringValue()", "Set the utf8 string value.",
      "void setUTF8StringValue(string value)")
    };
    current = new DraggableStandardItem("UTF8StringASN1()", "ASN1 UTF8String node constructor. To be used with 'new'.",
                                        "UTF8StringASN1(string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], UTF8StringASN1 defaultValue [<i>=null</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Choice
    subList.clear();
    QString choiceTemplate = "var chCallBack = function(i) {\n\tif (i === 0) return new _NODE_;\n\tif (i === 1) return new _NODE_;\n}";
    subList = {
      new DraggableStandardItem("Choice callback function template", "Template of a function to easily create the callback to pass as argument to the choice constructor.", "", choiceTemplate),
      new DraggableStandardItem("getSelectedChoice()", "Get the selected object.", "ASN1Object getSelectedChoice()"),
      new DraggableStandardItem("getSelectedChoiceIndex()", "Get the index of the selected object.", "unsigned int getSelectedChoiceIndex()"),
      new DraggableStandardItem("setSelectedChoice()", "Set the choice from index, and returns the created object.", "ASN1Object setSelectedChoice(unsigned int index)"),
      new DraggableStandardItem("makeDummyChoiceList()", "Instanciate all the possible choices. This does not set a choice, it only allows the access them as preview.", "void makeDummyChoiceList()"),
      new DraggableStandardItem("deleteDummyChoiceList()", "Deletes the dummy list to clean memory.", "void deleteDummyChoiceList()"),
      new DraggableStandardItem("getAvailableChoices()", "Get the number of available choices.", "unsigned int getAvailableChoices()"),
      new DraggableStandardItem("dummyChoiceFromIndex()", "Get the object at index in the dummy list.", "ASN1Object dummyChoiceFromIndex(unsigned int index)")
    };
    current = new DraggableStandardItem("ChoiceASN1()", "ASN1 Choice node constructor. To be used with 'new'.",
                                        "ChoiceASN1(function callback [<i>=no function</i>], unsigned int nbPossibilities [<i>=0</i>], string name [<i>=''</i>], string tag [<i>=''</i>], bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], ChoiceASN1 defaultValue [<i>=null</i>]");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Sequence
    subList.clear();
    QString seqTemplate = "function MakeSeq() {\n\tvar v1 = new _NODE_;\n\tvar v2 = new _NODE_;\n\treturn [v1, v2];\n}";
    subList = {
      new DraggableStandardItem("Sequence Array function template", "Template of a function to easily create the array to pass as argument to the sequence constructor.", "", seqTemplate),
      new DraggableStandardItem("getObjectAt()", "Get the object at index.", "ASN1Object getObjectAt(unsigned int index)"),
      new DraggableStandardItem("getSize()", "Get the number of objects in the sequence.", "unsigned int getSize()"),
      new DraggableStandardItem("isExtensible()", "Tester if sequence is extensible or not.", "bool isExtensible()"),
      new DraggableStandardItem("getExtensibilityObjectAt()", "Get the object at indexin the extensible part of the sequence.", "ASN1Object getExtensibilityObjectAt(unsigned int index)"),
      new DraggableStandardItem("getExtensibilityeSize()", "Get the number of objects in the extensible part of the sequence.", "unsigned int getExtensibilityeSize()")
    };
    current = new DraggableStandardItem("SequenceASN1()", "ASN1 Sequence node constructor. To be used with 'new'.",
                                        "SequenceASN1(Array of ASN1Object [<i>=empty Array</i>],string name [<i>=''</i>], string tag [<i>=''</i>],"
                                        "bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], SequenceASN1 defaultValue [<i>=null</i>],	bool extensibility [<i>=false</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Sequence of
    subList.clear();
    QString seqOfTemplate = "var seqofCallback = function() {\n\treturn new _NODE_;\n}";
    subList = {
      new DraggableStandardItem("Sequence Of callback function template", "Template of a function to easily create the callback to pass as argument to the sequence of constructor.", "", seqOfTemplate),
      new DraggableStandardItem("getObjectAt()", "Get the object at index.", "ASN1Object getObjectAt(unsigned int index)"),
      new DraggableStandardItem("getSequenceOfSize()", "Get the number of objects in the sequence of.", "unsigned int getSequenceOfSize()"),
      new DraggableStandardItem("appendNewObject()", "Appends a new object and returns it.", "ASN1Object appendNewObject()"),
      new DraggableStandardItem("deleteObjectAt()", "Deletes the object at index.", "void deleteObjectAt(unsigned int index)"),
      new DraggableStandardItem("moveUpObject()", "Move up the object at index.", "void moveUpObject(unsigned int index)"),
      new DraggableStandardItem("moveDownObject()", "Move down the object at index.", "void moveDownObject(unsigned int index)"),
      new DraggableStandardItem("getNewDummyObject()", "Returns an object as it would be made in the sequence of, but it is not added. It is a preview.", "ASN1Object getNewDummyObject()"),
    };
    current = new DraggableStandardItem("SequenceOfASN1()", "ASN1 Sequence node constructor. To be used with 'new'.",
                                        "SequenceOfASN1(Array of ASN1Object [<i>=empty Array</i>],string name [<i>=''</i>], string tag [<i>=''</i>],"
                                        "bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], SequenceOfASN1 defaultValue [<i>=null</i>],	bool extensibility [<i>=false</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    // Set
    subList.clear();
    QString setTemplate = "function MakeSet() {\n\tvar v1 = new _NODE_;\n\tvar v2 = new _NODE_;\n\treturn [v1, v2];\n}";
    subList = {
      new DraggableStandardItem("Set Array function template", "Template of a function to easily create the array to pass as argument to the set constructor.", "", setTemplate),
      new DraggableStandardItem("getObjectAt()", "Get the object at index.", "ASN1Object getObjectAt(unsigned int index)"),
      new DraggableStandardItem("getSize()", "Get the number of objects in the set.", "unsigned int getSize()"),
      new DraggableStandardItem("isExtensible()", "Tester if set is extensible or not.", "bool isExtensible()"),
      new DraggableStandardItem("getExtensibilityObjectAt()", "Get the object at indexin the extensible part of the set.", "ASN1Object getExtensibilityObjectAt(unsigned int index)"),
      new DraggableStandardItem("getExtensibilityeSize()", "Get the number of objects in the extensible part of the set.", "unsigned int getExtensibilityeSize()")
    };
    current = new DraggableStandardItem("SetASN1()", "ASN1 Set node constructor. To be used with 'new'.",
                                        "SetASN1(Array of ASN1Object [<i>=empty Array</i>],string name [<i>=''</i>], string tag [<i>=''</i>],"
                                        "bool optional [<i>=false</i>], bool explicitTag [<i>=false</i>], SetASN1 defaultValue [<i>=null</i>],	bool extensibility [<i>=false</i>])");
    current->appendColumn(subList);
    itemList.push_back(current);

    model->appendColumn(itemList);
  }

  QGroupBox* UI_GrammarJS::MakeHintPanel(QWidget* parent) {
    HintPanel = new DraggableTreeWidget(parent);
    HintPanel->setObjectName("hintTree");
    HintPanel->setHeaderHidden(true);

    MakeJSHintList(static_cast<QStandardItemModel*>(HintPanel->model()));

    QLabel* info = new QLabel("Drag and drop the functions onto the editor.");
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

  void UI_GrammarJS::RefreshHint(const QModelIndex& i) {
    QStandardItem* item = static_cast<QStandardItemModel*>(HintPanel->model())->itemFromIndex(i);
    DraggableStandardItem* dItem = static_cast<DraggableStandardItem*>(item);
    HintText->setText(dItem->GetDesc());
  }

  void UI_GrammarJS::ToggleJSDebugMode() {
    m_JSDebug = !m_JSDebug;
  }

  void UI_GrammarJS::RunJSScript() {
    std::shared_ptr<ASN1_Object> grammar = m_Main->JSToObj(m_Main->GetScriptEngine(), JSedit->toPlainText(), m_JSDebug);
    m_Main->SetLastScript(JSedit->toPlainText());
    m_Main->SetEditorObj(grammar);
    if (grammar)
      m_Main->SelectTab(3);
  }

  void UI_GrammarJS::RunAdditionalJSScript() {
    if (m_Main->ProcessAdditionalJS(m_Main->GetScriptEngine(), JSedit->toPlainText(), m_JSDebug))
      m_Main->SelectTab(3);
    m_Main->RefreshEditorTree();
  }

  void UI_GrammarJS::LoadJSScript() {
    QString fileName =
      QFileDialog::getOpenFileName(this, "Open Script File",
                                   "", "JavaScript file (*.js *)");
    if (fileName != "") {
      QFile f(fileName);
      if (f.exists()) {
        m_LoadedScriptFile = fileName;
        f.open(QFile::ReadOnly);
        QString jsContent = QTextStream(&f).readAll();
        JSedit->setPlainText(jsContent);
        f.close();
      }
      else {
        QMessageBox box(QMessageBox::Critical, "Cannot open script file", "File does not exist");
        box.exec();
      }
    }
  }

  void UI_GrammarJS::SetScript(const QString& script) {
    m_LoadedScriptFile = "";
    JSedit->setPlainText(script);
  }

  void UI_GrammarJS::SaveJSScript() {
    QString defaultFile;
    if (m_LoadedScriptFile != "")
      defaultFile = m_LoadedScriptFile;
    QString fileName =
      QFileDialog::getSaveFileName(this, "Save Script File",
                                   defaultFile, "JavaScript file (*.js *)");
    QFile f(fileName);
    if (f.open(QIODevice::WriteOnly))
      f.write(JSedit->toPlainText().toStdString().c_str());
    f.close();
  }

}

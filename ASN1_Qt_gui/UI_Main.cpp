/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "UI_Main.h"
#include "UI_GrammarJS.h"
#include "UI_GrammarASN.h"
#include "UI_GrammarComp.h"
#include "UI_Editor.h"
#include <QScriptEngineDebugger>

#include "Script.h"
#include "ASN1_includes.h"

#include "../Grammar/Grammar_test.h"
#include "../Grammar/SAIP.h"

using namespace Utils;

const QString defaultASN = "config/PEDefinitions V1.0_edit.asn";
const QString defaultJS = "config/test.js";

namespace UI {

  UI_Main::UI_Main(QWidget* parent) : QMainWindow(parent), m_Grammar(nullptr), m_ScriptEngine(nullptr) {
    resize(1024, 600);
    setWindowTitle("Q-ASN1");
    setWindowIcon(QIcon(":/img/img/icon.png"));
    setStatusBar(new QStatusBar(this));

    m_GrammarComp = new UI_GrammarComp(this);
    m_GrammarASN = new UI_GrammarASN(this);
    m_GrammarJS = new UI_GrammarJS(this);
    m_Editor = new UI_Editor(this);

    m_Tabs = new QTabWidget(this);
    m_Tabs->addTab(m_GrammarComp, "Compiled Grammars");
    m_Tabs->addTab(m_GrammarASN, "ASN1 Grammar");
    m_Tabs->addTab(m_GrammarJS, "Script");
    m_Tabs->addTab(m_Editor, "Tree Editor");
    m_Tabs->setCurrentIndex(3);
    this->setCentralWidget(m_Tabs);

    m_GrammarASN->SetASNGrammar(defaultASN);
    m_GrammarASN->ToJS();
    m_GrammarJS->RunJSScript();
  }

  void UI_Main::SelectTab(int idx) {
    m_Tabs->setCurrentIndex(idx);
  }

  void UI_Main::SetJSScript(const QString& js) {
    m_GrammarJS->SetScript(js);
  }

  void UI_Main::SetEditorObj(ASN1_Object* obj) {
    m_Editor->SetGrammar(obj);
  }

  QString UI_Main::ASNToX(const QString& asn, eFormat f) {
    const int buffSize = asn.size() * 10 + 1;
    char* buff = new char[buffSize];
    char* errorBuff = new char[500];

    SetStatus("Reading grammar from file.");
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (f == cCPP)
      ASNBufferToCPPBuffer(asn.toStdString().c_str(), buff, buffSize, errorBuff, 500);
    else if (f == cJS)
      ASNBufferToJSBuffer(asn.toStdString().c_str(), buff, buffSize, errorBuff, 500);
    QApplication::restoreOverrideCursor();

    QString err(errorBuff);
    if (err.isEmpty()) {
      statusBar()->showMessage("Grammar processed without error.");
    }
    else {
      statusBar()->showMessage("Grammar processing failed.");
      QMessageBox box(QMessageBox::Critical, "Cannot parse grammar", err);
      box.exec();
    }

    QString r;
    if (err.isEmpty() && buffSize > 0)
      r = buff;
    else r = "";

    delete[] buff;
    delete[] errorBuff;

    return r;
  }

  QString UI_Main::ASNToJS(const QString& asn) {
    return ASNToX(asn, cJS);
  }

  QString UI_Main::ASNToCPP(const QString& asn) {
    return ASNToX(asn, cCPP);
  }

  ASN1_Object* UI_Main::JSToObj(QScriptEngine** eng, const QString& js, bool debug, bool silent) {
    QString err;
    ClearScriptEngine(*eng);
    *eng = InitEngine();

    if (!silent)
      statusBar()->showMessage("Reading grammar from script.");

    QScriptEngineDebugger* debugger = nullptr;
    if (debug) {
      debugger = new QScriptEngineDebugger();
      debugger->attachTo(*eng);
      debugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
    }
    if (!debug)
      QApplication::setOverrideCursor(Qt::WaitCursor);
    ASN1_Object* obj = GrammarFromScript(*eng, js, err);
    QApplication::restoreOverrideCursor();

    if (debugger != nullptr)
      delete debugger;

    if (err.isEmpty()) {
      if (!silent)
        statusBar()->showMessage("Script processed without error.");
    }
    else {
      ClearScriptEngine(*eng);
      if (!silent)
        statusBar()->showMessage("Script processing failed.");
      QMessageBox box(QMessageBox::Critical, "Cannot run script", err);
      box.exec();
    }
    return obj;
  }

  bool UI_Main::ProcessAdditionalJS(QScriptEngine** eng, const QString& js, bool debug) {
    QString error;
    if (*eng == nullptr) {
      statusBar()->showMessage("Please run an initial script first.");
	  return false;
    }
    else {
      statusBar()->showMessage("Processing additional script.");

      QScriptEngineDebugger* debugger = nullptr;
      if (debug) {
        debugger = new QScriptEngineDebugger();
        debugger->attachTo(*eng);
        debugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
      }
      if (!debug)
        QApplication::setOverrideCursor(Qt::WaitCursor);
      ProcessAdditionalScript(*eng, js, error);
      QApplication::restoreOverrideCursor();

      if (debugger != nullptr)
        delete debugger;

      if (!error.isEmpty()) {
        statusBar()->showMessage("Script processing failed.");
        QMessageBox box(QMessageBox::Critical, "The script returned an error", error);
        box.exec();
        return false;
      }
      else {
        statusBar()->showMessage("Script processed without error.");
        return true;
      }
    }
  }

  ASN1_Object* UI_Main::CompToObj(const QString& name, bool silent) {
    ASN1_Object* obj = nullptr;
    if (name == "Test_1") {
      Grammar::SequenceTestVars s;
      obj = Grammar::MakeSequenceTest("Test_Grammar", "", s);
    }
    else if (name == "SIM Alliance") {
      obj = GetGrammar();
    }
    if (!silent) {
      if (obj != nullptr)
        statusBar()->showMessage("Grammar Loaded.");
      else
        statusBar()->showMessage("No Grammar Loaded.");
    }
    return obj;
  }

  void UI_Main::SetLastCompGramm(const QString& name) {
    m_LastGramm = name;
    m_LastScript.clear();
  }

  void UI_Main::SetLastScript(const QString& script) {
    m_LastGramm.clear();
    m_LastScript = script;
  }

  const QString& UI_Main::GetLastCompGramm() {
    return m_LastGramm;
  }
  const QString& UI_Main::GetLastScript() {
    return m_LastScript;
  }

  void UI_Main::RefreshEditorTree() {
    m_Editor->RefreshTree();
  }

  void UI_Main::SetStatus(const QString& status) {
    statusBar()->showMessage(status);
  }

  UI_Main::~UI_Main() {
    ClearScriptEngine(m_ScriptEngine);
  }

}

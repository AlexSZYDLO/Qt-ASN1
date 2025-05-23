/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once
#include "ASN1_includes.h"
#include "ASN1_parser.h"
#include "Script.h"

#include "Widgets/CustomWidgets.h"

class QJSEngine;

namespace UI
{
class UI_GrammarJS;
class UI_GrammarASN;
class UI_GrammarComp;
class UI_Editor;

class UI_Main : public QMainWindow
{
  Q_OBJECT

public:
  explicit UI_Main(QWidget *parent = 0);
  ~UI_Main();

  void SetJSScript(const QString &js);
  void SetEditorObj(std::shared_ptr<ASN1_Object> obj);

  QString ASNToJS(const QString &asn);
  QString ASNToCPP(const QString &asn);
  std::shared_ptr<ASN1_Object> JSToObj(QJSEngine **eng, const QString &js, bool debug, bool silent = false);
  bool ProcessAdditionalJS(QJSEngine **eng, const QString &js, bool debug);
  std::shared_ptr<ASN1_Object> CompToObj(const QString &name, bool silent = false);

  void RefreshEditorTree();

  void SelectTab(int idx);
  void SetStatus(const QString &status);

  void SetLastCompGramm(const QString &name);
  void SetLastScript(const QString &script);
  const QString &GetLastCompGramm();
  const QString &GetLastScript();

  QJSEngine **GetScriptEngine()
  {
    return &m_ScriptEngine;
  }

private:
  QTabWidget *m_Tabs;

  UI_GrammarJS *m_GrammarJS;
  UI_GrammarASN *m_GrammarASN;
  UI_GrammarComp *m_GrammarComp;
  UI_Editor *m_Editor;

  std::shared_ptr<ASN1_Object> m_Grammar;
  QJSEngine *m_ScriptEngine;

  QString m_LastScript;
  QString m_LastGramm;

  enum eFormat
  {
    cCPP,
    cJS
  };

  QString ASNToX(const QString &asn, eFormat f);
};
} // namespace UI

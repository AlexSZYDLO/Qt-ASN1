/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "Script.h"
#include <QTextStream>
#include "Nodes/ASN1_Script_Basic_Nodes.h"
#include "Nodes/ASN1_Script_Choice.h"
#include "Nodes/ASN1_Script_Sequence.h"
#include "Nodes/ASN1_Script_SequenceOf.h"
#include "Nodes/ASN1_Script_Set.h"

template <class nodeType>
void installNode(QJSEngine *eng, QString CtorName)
{
  QJSValue injectedObject = eng->newQMetaObject(&nodeType::staticMetaObject);
  eng->globalObject().setProperty(CtorName, injectedObject);
}

QJSEngine *InitEngine()
{
  QJSEngine *scriptEngine = new QJSEngine();

  installNode<ASN1_Script_BitString>(scriptEngine, "BitStringASN1");
  installNode<ASN1_Script_Boolean>(scriptEngine, "BooleanASN1");
  installNode<ASN1_Script_Enumerated>(scriptEngine, "EnumeratedASN1");
  installNode<ASN1_Script_IA5String>(scriptEngine, "IA5StringASN1");
  installNode<ASN1_Script_Integer>(scriptEngine, "IntegerASN1");
  installNode<ASN1_Script_Null>(scriptEngine, "NullASN1");
  installNode<ASN1_Script_ObjectID>(scriptEngine, "ObjectIDASN1");
  installNode<ASN1_Script_OctetString>(scriptEngine, "OctetStringASN1");
  installNode<ASN1_Script_Real>(scriptEngine, "RealASN1");
  installNode<ASN1_Script_UTCTime>(scriptEngine, "UTCTimeASN1");
  installNode<ASN1_Script_UTF8String>(scriptEngine, "UTF8StringASN1");

  installNode<ASN1_Script_Choice>(scriptEngine, "ChoiceASN1");
  installNode<ASN1_Script_Sequence>(scriptEngine, "SequenceASN1");
  installNode<ASN1_Script_SequenceOf>(scriptEngine, "SequenceOfASN1");
  installNode<ASN1_Script_Set>(scriptEngine, "SetASN1");
  return scriptEngine;
}

void ClearScriptEngine(QJSEngine *e)
{
  delete e;
}

std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, const QString &script, QString &error)
{
  TheGrammar = nullptr;
  QJSValue result = e->evaluate(script);

  if (result.isError())
    error = result.toString();

  if (TheGrammar == nullptr && error.isEmpty())
    error = "Script does not set the grammar. You need to call registerGrammar()";

  return error.isEmpty() ? TheGrammar : nullptr;
}

std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, QFile &file, QString &error)
{
  if (file.exists())
    file.open(QFile::ReadOnly);
  else
  {
    error += "Cannot open script file";
    return nullptr;
  }

  QString jsContent = QTextStream(&file).readAll();
  file.close();

  return GrammarFromScript(e, jsContent, error);
}

std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, QFile &file)
{
  QString err;
  return GrammarFromScript(e, file, err);
}

std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, const QString &script)
{
  QString err;
  return GrammarFromScript(e, script, err);
}

void ProcessAdditionalScript(QJSEngine *e, const QString &script, QString &error)
{
  QJSValue result = e->evaluate(script);
  if (result.isError())
    error = result.toString();
}

void ProcessAdditionalScript(QJSEngine *e, QFile &file, QString &error)
{
  if (file.exists())
    file.open(QFile::ReadOnly);
  else
  {
    error += "Cannot open script file";
    return;
  }

  QString jsContent = QTextStream(&file).readAll();
  file.close();
  ProcessAdditionalScript(e, jsContent, error);
}

void ProcessAdditionalScript(QJSEngine *e, QFile &file)
{
  QString err;
  return ProcessAdditionalScript(e, file, err);
}

void ProcessAdditionalScript(QJSEngine *e, const QString &script)
{
  QString err;
  return ProcessAdditionalScript(e, script, err);
}

void ClearGrammar()
{
  TheGrammar.reset();
}

// --------------- memory check ---------------
bool ScriptMemoryCheck()
{
  return ASN1_Script_Node_Base::memoryCheck() && ASN1_Object::memoryCheck();
}

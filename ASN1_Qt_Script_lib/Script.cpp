/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "Script.h"
#include <QScriptEngine>
#include <QTextStream>

QScriptEngine* InitEngine() {
  QScriptEngine* scriptEngine = new QScriptEngine();
  objMap.insert(scriptEngine, QList<ASN1_Script_Node*>());

  installNode<ASN1_Script_BitString>(scriptEngine, "BitStringASN1");
  installNode<ASN1_Script_Boolean>(scriptEngine, "BooleanASN1");
  installNode<ASN1_Script_Choice>(scriptEngine, "ChoiceASN1");
  installNode<ASN1_Script_Enumerated>(scriptEngine, "EnumeratedASN1");
  installNode<ASN1_Script_IA5String>(scriptEngine, "IA5StringASN1");
  installNode<ASN1_Script_Integer>(scriptEngine, "IntegerASN1");
  installNode<ASN1_Script_Null>(scriptEngine, "NullASN1");
  installNode<ASN1_Script_ObjectID>(scriptEngine, "ObjectIDASN1");
  installNode<ASN1_Script_OctetString>(scriptEngine, "OctetStringASN1");
  installNode<ASN1_Script_Real>(scriptEngine, "RealASN1");
  installNode<ASN1_Script_Sequence>(scriptEngine, "SequenceASN1");
  installNode<ASN1_Script_SequenceOf>(scriptEngine, "SequenceOfASN1");
  installNode<ASN1_Script_Set>(scriptEngine, "SetASN1");
  installNode<ASN1_Script_UTCTime>(scriptEngine, "UTCTimeASN1");
  installNode<ASN1_Script_UTF8String>(scriptEngine, "UTF8StringASN1");

  return scriptEngine;
}

void ClearScriptEngine(QScriptEngine* e) {
  QMap<const QScriptEngine*, QList<ASN1_Script_Node*>>::iterator i =  objMap.find(e);
  if (i != objMap.end()) {
    QList<ASN1_Script_Node*> l = i.value();
    for (int j = 0; j < l.size(); j++)
      delete l.at(j);
    l.clear();
    delete e;
  }

}

QString EngineError(QScriptEngine* e) {
  if (e->hasUncaughtException()) {
    QScriptValue exception = e->uncaughtException();
    return exception.toString();
  }
  else return "";
}

ASN1_Object* GrammarFromScript(QScriptEngine* e, const QString& script, QString& error) {
  if (!e) InitEngine();

  if (!e->canEvaluate(script))
    return nullptr;

  e->evaluate(script);

  error = EngineError(e);
  if (TheGrammar == nullptr && error.isEmpty())
    error += "Script does not set the grammar. You need to call registerGrammar()";

  return error.isEmpty() ? TheGrammar : nullptr;
}

ASN1_Object* GrammarFromScript(QScriptEngine* e, QFile& file, QString& error) {
  if (file.exists())
    file.open(QFile::ReadOnly);
  else {
    error += "Cannot open script file" ;
    return nullptr;
  }

  QString jsContent = QTextStream(&file).readAll();
  file.close();

  return GrammarFromScript(e, jsContent, error);
}

ASN1_Object* GrammarFromScript(QScriptEngine* e, QFile& file) {
  QString err;
  return GrammarFromScript(e, file, err);
}

ASN1_Object* GrammarFromScript(QScriptEngine* e, const QString& script) {
  QString err;
  return GrammarFromScript(e, script, err);
}

void ProcessAdditionalScript(QScriptEngine* e, const QString& script, QString& error) {
  if (!e) InitEngine();

  if (!e->canEvaluate(script))
    return;
  e->evaluate(script);
  error = EngineError(e);
}

void ProcessAdditionalScript(QScriptEngine* e, QFile& file, QString& error) {
  if (file.exists())
    file.open(QFile::ReadOnly);
  else {
    error += "Cannot open script file" ;
    return;
  }

  QString jsContent = QTextStream(&file).readAll();
  file.close();
  ProcessAdditionalScript(e, jsContent, error);
}

void ProcessAdditionalScript(QScriptEngine* e, QFile& file) {
  QString err;
  return ProcessAdditionalScript(e, file, err);
}

void ProcessAdditionalScript(QScriptEngine* e, const QString& script) {
  QString err;
  return ProcessAdditionalScript(e, script, err);
}


// --------------- memory check ---------------
bool ScriptMemoryCheck() {
  return ASN1_Script_Node::memoryCheck();
}

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "EngineInit.h"

#if defined DLLCOMPIL
#define DLLSPEC __declspec(dllexport)
#else
#define DLLSPEC __declspec(dllimport)
#endif

DLLSPEC ASN1_Object* GrammarFromScript(QScriptEngine* e, const QString& script, QString& error);
DLLSPEC ASN1_Object* GrammarFromScript(QScriptEngine* e, const QString& script);
DLLSPEC ASN1_Object* GrammarFromScript(QScriptEngine* e, QFile& file, QString& error);
DLLSPEC ASN1_Object* GrammarFromScript(QScriptEngine* e, QFile& file);

DLLSPEC void ProcessAdditionalScript(QScriptEngine* e, const QString& script, QString& error);
DLLSPEC void ProcessAdditionalScript(QScriptEngine* e, const QString& script);
DLLSPEC void ProcessAdditionalScript(QScriptEngine* e, QFile& file, QString& error);
DLLSPEC void ProcessAdditionalScript(QScriptEngine* e, QFile& file);

DLLSPEC QScriptEngine* InitEngine();
DLLSPEC void ClearScriptEngine(QScriptEngine* e);


DLLSPEC bool ScriptMemoryCheck();



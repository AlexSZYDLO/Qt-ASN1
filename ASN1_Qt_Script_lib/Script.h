/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "EngineInit.h"

#ifdef _MSC_VER
#ifdef MODULE_API_EXPORTS
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif

MODULE_API ASN1_Object* GrammarFromScript(QScriptEngine* e, const QString& script, QString& error);
MODULE_API ASN1_Object* GrammarFromScript(QScriptEngine* e, const QString& script);
MODULE_API ASN1_Object* GrammarFromScript(QScriptEngine* e, QFile& file, QString& error);
MODULE_API ASN1_Object* GrammarFromScript(QScriptEngine* e, QFile& file);

MODULE_API void ProcessAdditionalScript(QScriptEngine* e, const QString& script, QString& error);
MODULE_API void ProcessAdditionalScript(QScriptEngine* e, const QString& script);
MODULE_API void ProcessAdditionalScript(QScriptEngine* e, QFile& file, QString& error);
MODULE_API void ProcessAdditionalScript(QScriptEngine* e, QFile& file);

MODULE_API QScriptEngine* InitEngine();
MODULE_API void ClearScriptEngine(QScriptEngine* e);


MODULE_API bool ScriptMemoryCheck();



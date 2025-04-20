/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QFile>
#include <QJSEngine>
#include <QString>
#include "ASN1_includes.h"

#ifdef _MSC_VER
#ifdef MODULE_API_EXPORTS
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif

MODULE_API std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, const QString &script, QString &error);
MODULE_API std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, const QString &script);
MODULE_API std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, QFile &file, QString &error);
MODULE_API std::shared_ptr<ASN1_Object> GrammarFromScript(QJSEngine *e, QFile &file);

MODULE_API void ProcessAdditionalScript(QJSEngine *e, const QString &script, QString &error);
MODULE_API void ProcessAdditionalScript(QJSEngine *e, const QString &script);
MODULE_API void ProcessAdditionalScript(QJSEngine *e, QFile &file, QString &error);
MODULE_API void ProcessAdditionalScript(QJSEngine *e, QFile &file);

MODULE_API QJSEngine *InitEngine();
MODULE_API void ClearScriptEngine(QJSEngine *e);
MODULE_API void ClearGrammar();

MODULE_API bool ScriptMemoryCheck();

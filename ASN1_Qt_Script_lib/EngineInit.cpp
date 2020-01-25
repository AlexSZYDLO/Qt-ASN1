/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "EngineInit.h"

using namespace Utils;

QMap<const QScriptEngine*, QList<ASN1_Script_Node*> > objMap;

ASN1_Script_Node* Add(const QScriptEngine* e, ASN1_Script_Node* node) {
  objMap.find(e).value().push_back(node);
  return node;
}

template <>
QScriptValue NodeCtor<ASN1_Script_Sequence>(QScriptContext* context, QScriptEngine* engine) {
  QString error = "", name = "", tag = "";
  QObjectList ObjectArray;
  bool IsOptional = false, IsExplicitTagging = false, extensibility = false;
  ASN1_Script_Sequence* defaultValue = nullptr;

  int nbArg = context->argumentCount();
  if (nbArg > 7)
    error = "wrong number of arguments, should be between 0 and 7";

  if (error == "" && nbArg > 0)
    ObjectArray = ParseSequenceObjectListArgument(context->argument(0), "1", error);
  if (error == "" && nbArg > 1)
    name = ParseNameArgument(context->argument(1), "2", error);
  if (error == "" && nbArg > 2)
    tag = ParseTagArgument(context->argument(2), "3", error);
  if (error == "" && nbArg > 3)
    IsOptional = ParseIsOptionalArgument(context->argument(3), "4", error);
  if (error == "" && nbArg > 4)
    IsExplicitTagging = ParseIsExplicitTaggingArgument(context->argument(4), "5", error);
  if (error == "" && nbArg > 5)
    defaultValue = ParseDefaultValueArgument<ASN1_Script_Sequence>(context->argument(5), "6", error);
  if (error == "" && nbArg > 6)
    extensibility = ParseIsExtensibilityArgument(context->argument(6), "7", error);

  if (error != "") {
    context->throwError(error);
    return engine->undefinedValue();
  }
  return engine->toScriptValue(Add(engine, new ASN1_Script_Sequence(ObjectArray, name, tag, IsOptional, IsExplicitTagging, defaultValue, extensibility)));
}

template <>
QScriptValue NodeCtor<ASN1_Script_Set>(QScriptContext* context, QScriptEngine* engine) {
  QString error = "", name = "", tag = "";
  QObjectList ObjectArray;
  bool IsOptional = false, IsExplicitTagging = false, extensibility = false;
  ASN1_Script_Set* defaultValue = nullptr;

  int nbArg = context->argumentCount();
  if (nbArg > 7)
    error = "wrong number of arguments, should be between 0 and 7";

  if (error == "" && nbArg > 0)
    ObjectArray = ParseSequenceObjectListArgument(context->argument(0), "1", error);
  if (error == "" && nbArg > 1)
    name = ParseNameArgument(context->argument(1), "2", error);
  if (error == "" && nbArg > 2)
    tag = ParseTagArgument(context->argument(2), "3", error);
  if (error == "" && nbArg > 3)
    IsOptional = ParseIsOptionalArgument(context->argument(3), "4", error);
  if (error == "" && nbArg > 4)
    IsExplicitTagging = ParseIsExplicitTaggingArgument(context->argument(4), "5", error);
  if (error == "" && nbArg > 5)
    defaultValue = ParseDefaultValueArgument<ASN1_Script_Set>(context->argument(5), "6", error);
  if (error == "" && nbArg > 6)
    extensibility = ParseIsExtensibilityArgument(context->argument(6), "7", error);

  if (error != "") {
    context->throwError(error);
    return engine->undefinedValue();
  }
  return engine->toScriptValue(Add(engine, new ASN1_Script_Set(ObjectArray, name, tag, IsOptional, IsExplicitTagging, defaultValue, extensibility)));
}

template <>
QScriptValue NodeCtor<ASN1_Script_SequenceOf>(QScriptContext* context, QScriptEngine* engine) {
  QString error = "", name = "", tag = "";
  QScriptValue callback;
  bool IsOptional = false, IsExplicitTagging = false;
  ASN1_Script_SequenceOf* defaultValue = nullptr;

  int nbArg = context->argumentCount();
  if (nbArg > 6)
    error = "wrong number of arguments, should be between 0 and 6";

  if (error == "" && nbArg > 0)
    callback = ParseCallbackArgument(context->argument(0), "1", cSequenceOf, error);
  if (error == "" && nbArg > 1)
    name = ParseNameArgument(context->argument(1), "2", error);
  if (error == "" && nbArg > 2)
    tag = ParseTagArgument(context->argument(2), "3", error);
  if (error == "" && nbArg > 3)
    IsOptional = ParseIsOptionalArgument(context->argument(3), "4", error);
  if (error == "" && nbArg > 4)
    IsExplicitTagging = ParseIsExplicitTaggingArgument(context->argument(4), "5", error);
  if (error == "" && nbArg > 5)
    defaultValue = ParseDefaultValueArgument<ASN1_Script_SequenceOf>(context->argument(5), "6", error);

  if (error != "") {
    context->throwError(error);
    return engine->undefinedValue();
  }
  return engine->toScriptValue(Add(engine, new ASN1_Script_SequenceOf(callback, name, tag, IsOptional, IsExplicitTagging, defaultValue)));
}

template <>
QScriptValue NodeCtor<ASN1_Script_Choice>(QScriptContext* context, QScriptEngine* engine) {
  QString error = "", name = "", tag = "";
  QScriptValue callback;
  int maxNbOfChoices = 0;
  bool IsOptional = false, IsExplicitTagging = false;
  ASN1_Script_Choice* defaultValue = nullptr;

  int nbArg = context->argumentCount();
  if (nbArg > 7)
    error = "wrong number of arguments, should be between 2 and 7";

  if (error == "" && nbArg > 0)
    callback = ParseCallbackArgument(context->argument(0), "1", cChoice, error);
  if (error == "" && nbArg > 1)
    maxNbOfChoices = ParseChoiceMaxIndexArgument(context->argument(1), "2", error);
  if (error == "" && nbArg > 2)
    name = ParseNameArgument(context->argument(2), "3", error);
  if (error == "" && nbArg > 3)
    tag = ParseTagArgument(context->argument(3), "4", error);
  if (error == "" && nbArg > 4)
    IsOptional = ParseIsOptionalArgument(context->argument(4), "5", error);
  if (error == "" && nbArg > 5)
    IsExplicitTagging = ParseIsExplicitTaggingArgument(context->argument(5), "6", error);
  if (error == "" && nbArg > 6)
    defaultValue = ParseDefaultValueArgument<ASN1_Script_Choice>(context->argument(6), "7", error);

  if (error != "") {
    context->throwError(error);
    return engine->undefinedValue();
  }
  return engine->toScriptValue(Add(engine, new ASN1_Script_Choice(callback, maxNbOfChoices, name, tag, IsOptional, IsExplicitTagging, defaultValue)));
}

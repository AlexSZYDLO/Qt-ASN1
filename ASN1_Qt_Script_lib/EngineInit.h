/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QScriptEngine>
#include <QFile>
#include <QMap>

#include "ASN1_Script_Node.h"
#include "Nodes/ASN1_Script_Basic_Nodes.h"
#include "Nodes/ASN1_Script_Choice.h"
#include "Nodes/ASN1_Script_Sequence.h"
#include "Nodes/ASN1_Script_SequenceOf.h"
#include "Nodes/ASN1_Script_Set.h"


extern QMap<const QScriptEngine*, QList<ASN1_Script_Node*> > objMap;

ASN1_Script_Node* Add(const QScriptEngine* e, ASN1_Script_Node* node);


template <class pointerT>
QScriptValue ptr_toScriptValue(QScriptEngine* eng, const pointerT& ptr) {
  pointerT p = dynamic_cast<pointerT>(ptr);
  return eng->toScriptValue((QObject*)p);
}

template <class pointerT>
void ptr_fromScriptValue(const QScriptValue& value,  pointerT& ptr) {
  QObject* obj = value.toQObject();
  ptr = dynamic_cast<pointerT>(obj);
}


inline QString ParseNameArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (!arg.isString())
    error = "argument " + argIndex + ": must be a string (Name)";
  else return arg.toString();
  return "";
}

inline QString ParseTagArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (!arg.isString())
    error = "argument " + argIndex + ": must be a string (Tag)";
  else return arg.toString();
  return "";
}

inline bool ParseIsOptionalArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (!arg.isBoolean())
    error = "argument " + argIndex + ": must be a boolean (Is optional)";
  else return arg.toBoolean();
  return false;
}

inline bool ParseIsExplicitTaggingArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (!arg.isBoolean())
    error = "argument " + argIndex + ": must be a boolean (Is explicit tagging)";
  else return arg.toBoolean();
  return false;
}

inline bool ParseIsExtensibilityArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (!arg.isBoolean())
    error = "argument " + argIndex + ": must be a boolean (Is extensible)";
  else return arg.toBoolean();
  return false;
}

template<class nodeType>
inline nodeType* ParseDefaultValueArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (arg.isNull())
    return nullptr;
  if (!arg.isQObject())
    error = "argument " + argIndex + ": must be an object (Default value)";
  else if (dynamic_cast<nodeType*>(arg.toQObject()) == nullptr)
    error = QString("argument " + argIndex + ": must be an object of the same type as the object being constructed (Default value)");
  else return static_cast<nodeType*>(arg.toQObject());
  return nullptr;
}

inline QObjectList ParseSequenceObjectListArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  QObjectList objList;
  if (!arg.isArray())
    error = "argument " + argIndex + ": must be an array (Sequence object list)";
  else
    for (int i = 0; i < arg.toVariant().toList().size(); i++)
      objList.append(arg.toVariant().toList()[i].value<QObject*>());
  return objList;
}

inline QScriptValue ParseCallbackArgument(const QScriptValue& arg, QString argIndex, Utils::eNodeType t, QString& error) {
  if (!arg.isFunction())
    error = "argument " + argIndex + ": must be a function (" + (t == Utils::cChoice ? "Choice" : "Sequence Of") + " callback)";
  else return arg;
  return QScriptValue();
}

inline int ParseChoiceMaxIndexArgument(const QScriptValue& arg, QString argIndex, QString& error) {
  if (!arg.isNumber())
    error = "argument " + argIndex + ": must be a integer (Number of choices)";
  else return arg.toInteger();
  return 0;
}

template <class nodeType>
QScriptValue NodeCtor(QScriptContext* context, QScriptEngine* engine) {
  QString error = "", name = "", tag = "";
  bool IsOptional = false, IsExplicitTagging = false;
  nodeType* defaultValue = nullptr;

  int nbArg = context->argumentCount();
  if (nbArg > 5)
    error = "wrong number of arguments, should be between 0 and 5";

  if (error == "" && nbArg > 0)
    name = ParseNameArgument(context->argument(0), "1", error);
  if (error == "" && nbArg > 1)
    tag = ParseTagArgument(context->argument(1), "2", error);
  if (error == "" && nbArg > 2)
    IsOptional = ParseIsOptionalArgument(context->argument(2), "3", error);
  if (error == "" && nbArg > 3)
    IsExplicitTagging = ParseIsExplicitTaggingArgument(context->argument(3), "4", error);
  if (error == "" && nbArg > 4)
    defaultValue = ParseDefaultValueArgument<nodeType>(context->argument(4), "5", error);

  if (error != "") {
    context->throwError(error);
    return engine->undefinedValue();
  }
  return engine->toScriptValue(Add(engine, new nodeType(name, tag, IsOptional, IsExplicitTagging, defaultValue)));
}

template <>
QScriptValue NodeCtor<ASN1_Script_Sequence>(QScriptContext* context, QScriptEngine* engine);

template <>
QScriptValue NodeCtor<ASN1_Script_Set>(QScriptContext* context, QScriptEngine* engine);

template <>
QScriptValue NodeCtor<ASN1_Script_SequenceOf>(QScriptContext* context, QScriptEngine* engine);

template <>
QScriptValue NodeCtor<ASN1_Script_Choice>(QScriptContext* context, QScriptEngine* engine);

template <class nodeType>
void installNode(QScriptEngine* eng, QString CtorName) {
  qScriptRegisterMetaType<nodeType*>(eng, ptr_toScriptValue, ptr_fromScriptValue);

  nodeType* test = static_cast<nodeType*>(Add(eng, new nodeType()));
  QScriptValue proto = eng->newQObject(test);
  eng->setDefaultPrototype(qMetaTypeId<nodeType*>(), proto);

  QScriptValue ctor = eng->newFunction(NodeCtor<nodeType>, proto);
  eng->globalObject().setProperty(CtorName, ctor);
}

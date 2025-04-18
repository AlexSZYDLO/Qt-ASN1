/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <string>
#include <vector>
#include "global.h"


class Generator {
 public:
  Generator();
  virtual ~Generator() = 0;

  virtual std::string Generate() = 0;

  void SetGrammarName(const std::string& name);

  void SetAutoTags();
  void SetImplicitTags();
  void SetExplicitTags();
  void SetExtensibilityImplied();

  void SetSequenceExtensibility();
  void SetLastVariableTag(Tag tag);
  void SetLastVariableName(const std::string& newName);
  void SetLastVarOptional(bool _optional);

  void AddTempVariable(const std::string& module, eNodeType type, bool unknownType);

  void NewModule();
  void EndModule();
  void AddModule(const std::string& name, eNodeType type);
  std::string* AddUniqueModule(eNodeType type);

  void GrammarEnd();

  virtual void AppyAutoTag();

  void ReviewNames();
  void SortModules();


 protected:
  bool CheckUniqueNames();
  bool CheckExistingTypes();
  Module ModuleFromName(std::string modName);

  bool m_TagAuto;
  bool m_TagExplicit;
  bool m_ExtensibilityImplied;

  std::string m_GrammarName;
  std::vector<Module> m_ModuleList;

 private:
  int UniqueModuleCount;

  bool tempExtensibility;

  std::vector<std::vector<Variable>*> tempVariableLists;
  std::vector<Variable>* currentVariableList;
};

extern Generator* gGen;

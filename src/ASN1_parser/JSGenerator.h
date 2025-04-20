/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "Generator.h"

class JSGenerator : public Generator
{
public:
  JSGenerator();
  virtual ~JSGenerator();

  virtual std::string Generate() override;

  void GenerateVar(Variable &v, bool tab = true);
  void GenerateSequenceOrSet(Module &m);
  void GenerateSequenceOf(Module &m);
  void GenerateChoice(Module &m);
  void GenerateSingleVarModule(Module &m);

protected:
  int count;
  std::string script;

  std::string typeToJSClass(eNodeType t);
};
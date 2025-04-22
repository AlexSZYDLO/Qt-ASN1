#pragma once
#include "Generator.h"
class CPPGenerator : public Generator
{
public:
  CPPGenerator();
  virtual ~CPPGenerator();

  virtual std::string Generate() override;

  void GenerateVar(Variable &v, int tab = 1);
  void GenerateSequenceOrSet(Module &m);
  void GenerateSequenceOf(Module &m);
  void GenerateChoice(Module &m);
  void GenerateSingleVarModule(Module &m);

protected:
  int count;
  std::string cppCode;

  std::string typeToCPPClass(eNodeType t);
};

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "Generator.h"

using namespace std;
using namespace Utils;

void SetTagConstructed(string& tag) {
  string binary = HexAsBinary8Padded(tag.c_str());
  if (binary.size() > 2) {
    binary[2] = '1';
    tag = BinaryAsHex(binary).GetString();
  }
}

Generator* gGen = nullptr;

Generator::Generator() : m_TagAuto(false),
  m_TagExplicit(false),
  m_ExtensibilityImplied(false),
  tempExtensibility(false),
  UniqueModuleCount(0) {}

Generator::~Generator() {}

void Generator::SetGrammarName(const std::string& name) {
  m_GrammarName = name;
}

void Generator::SetAutoTags() {
  log("Set tag auto");
  m_TagAuto = true;
}

void Generator::SetImplicitTags() {
  log("Set tag implicit");
  m_TagExplicit = false;
}

void Generator::SetExplicitTags() {
  log("Set tag explicit");
  m_TagExplicit = true;
}

void Generator::SetExtensibilityImplied() {
  log("Set extensibility implied");
  m_ExtensibilityImplied = true;
}

void Generator::SetSequenceExtensibility() {
  log("extensible sequence");
  tempExtensibility = true;
}

void Generator::AddTempVariable(const std::string&  module, eNodeType type, bool unknownType) {
  Variable v = { "", "", m_TagExplicit, false, false, type, unknownType, module };
  currentVariableList->push_back(v);
}

void Generator::SetLastVariableName(const std::string& newName) {
  if (!currentVariableList->at(currentVariableList->size() - 1).unknownType)
    log(string("variable: " + Utils::NodeTypeToString(currentVariableList->at(currentVariableList->size() - 1).type) + " - name: " + newName));
  else
    log(string("variable: Unknown type - name: " + newName));

  currentVariableList->at(currentVariableList->size() - 1).name = newName;
}

void Generator::SetLastVariableTag(Tag tag) {
  Variable& curVar = currentVariableList->at(currentVariableList->size() - 1);

  if (!tag.noTag)
    log("tag: " + std::to_string(tag.label));

  eTagForm f = (IsComplexType(curVar.type)) ? cTagFormConstructed : cTagFormPrimitive;
  ByteArray t = !tag.noTag ? MakeTag(tag.tagClass, f, IntAsHex(tag.label)) : "";

  curVar.tag = t.GetString();

  if (curVar.explicitTag || tag.explicitTag == cExplicit)
    SetTagConstructed(curVar.tag);

  if (tag.explicitTag == cExplicit) {
    log("explicit tag variable");
    currentVariableList->at(currentVariableList->size() - 1).explicitTag = true;
  }
  if (tag.explicitTag == cImplicit)
    currentVariableList->at(currentVariableList->size() - 1).explicitTag = false;
}

void Generator::SetLastVarOptional(bool _optional) {
  if (_optional) log("optional variable");
  currentVariableList->at(currentVariableList->size() - 1).optional = _optional;
}

void Generator::AppyAutoTag() {
  for (size_t i = 0; i < currentVariableList->size(); i++)
    if (currentVariableList->at(i).tag != "") return; // one tag at least is set manually: dont apply auto tags (unset tags will get the default tag)

  int lblAsInt = 0;
  for (size_t i = 0; i < currentVariableList->size(); i++) {
    Variable& v = currentVariableList->at(i);

    //  /!\ even choice have a tag in  automatic tags context
    eTagForm f = (IsComplexType(v.type)) ? cTagFormConstructed : cTagFormPrimitive;
    ByteArray t = MakeTag(cTagClassContextSpecific, f, IntAsHex(lblAsInt++));

    v.tag = t.GetString();
    v.isAutoTag = true;
  }
}

void Generator::NewModule() {
  tempVariableLists.push_back(new std::vector<Variable>());
  currentVariableList = tempVariableLists.at(tempVariableLists.size() - 1);
}

void Generator::EndModule() {
  delete currentVariableList;
  tempVariableLists.pop_back();
  if (tempVariableLists.size() > 0)
    currentVariableList = tempVariableLists.at(tempVariableLists.size() - 1);
  tempExtensibility = false;
}

void Generator::AddModule(const std::string& name, eNodeType type) {
  log(string("module: " + NodeTypeToString(type) + " - name: " + name));

  if (IsComplexType(type)) {
    if (m_TagAuto == true)
      AppyAutoTag();
    m_ModuleList.push_back({ name, type, *currentVariableList, m_ExtensibilityImplied || tempExtensibility });
  }
  else {
    m_ModuleList.push_back({ name, type, *currentVariableList, m_ExtensibilityImplied || tempExtensibility });
  }
  EndModule();
}

string* Generator::AddUniqueModule(eNodeType type) {
  log(string("unique module: " + NodeTypeToString(type) + "_" + to_string(UniqueModuleCount++)));

  if (m_TagAuto == true)
    AppyAutoTag();
  m_ModuleList.push_back({ NodeTypeToString(type) + to_string(UniqueModuleCount), type, *currentVariableList, m_ExtensibilityImplied || tempExtensibility });

  EndModule();

  return new string(NodeTypeToString(type) + to_string(UniqueModuleCount)); // return unique name
}

Module Generator::ModuleFromName(std::string modName) {
  for (int i = 0; i < m_ModuleList.size(); i++) {
    if (m_ModuleList.at(i).name == modName)
      return m_ModuleList.at(i);
  }
  return{}; // should not happen
}

bool Generator::CheckUniqueNames() {
  for (int i = 0; i < m_ModuleList.size(); i++) {
    string name = m_ModuleList.at(i).name;
    for (int j = 0; j < m_ModuleList.size(); j++)
      if (i != j) {
        if (m_ModuleList.at(j).name == name) {
          string e = "Double module name: " + name + "\n";
          ParsingError += e;
          return false;
        }
      }
  }
  return true;
}

bool Generator::CheckExistingTypes() {
  vector <string> ModuleNames;

  for (int i = 0; i < m_ModuleList.size(); i++)
    ModuleNames.push_back(m_ModuleList.at(i).name);

  for (int i = 0; i < m_ModuleList.size(); i++) {
    for (int j = 0; j < m_ModuleList.at(i).tempVariableList.size(); j++) {

      if (m_ModuleList.at(i).tempVariableList.at(j).customTypeName != "") {
        bool found = false;
        for (int k = 0; k < ModuleNames.size(); k++) {
          if (ModuleNames.at(k) == m_ModuleList.at(i).tempVariableList.at(j).customTypeName) {
            found = true;
            break;
          }
        }
        if (found == false) {
          string e = "Custom type not declared: " + m_ModuleList.at(i).tempVariableList.at(j).customTypeName + "\n";
          ParsingError += e;
          return false;
        }
      }

    }
  }
  return true;
}

void Generator::GrammarEnd() {
  bool b = CheckUniqueNames();
  b &= CheckExistingTypes();

  if (b) {
    // set tag primitive/constructed for modules that were unknown
    for (int i = 0; i < m_ModuleList.size(); i++) {
      for (int j = 0; j < m_ModuleList.at(i).tempVariableList.size(); j++) {
        Variable& v = m_ModuleList.at(i).tempVariableList.at(j);

        if (v.unknownType) {
          // get the type from the name: the name should now exist and we can get the type
          eNodeType t = ModuleFromName(v.customTypeName).type;
          v.type = t;

          // swith to constructed if we find out that the type is complex. no effect on untagged choices that must remain without tag
          if (IsComplexType(t))
            SetTagConstructed(v.tag);
        }

        // case choice with a tag (auto tag or specified tag) -> explicit
        if (v.type == cChoice && v.tag != "")
          v.explicitTag = true;

      }
    }
  }
}

void ReplaceMinus(string& s) {
  size_t idx;
  do {
    idx = s.find('-');
    if (idx != string::npos)
      s[idx] = '_';
  }
  while (idx != string::npos);
}

void Generator::ReviewNames() {
  for (size_t i = 0; i < m_ModuleList.size(); i++) {
    Module* curMod = &m_ModuleList.at(i);
    ReplaceMinus(curMod->name);
    for (size_t j = 0; j < curMod->tempVariableList.size(); j++) {
      Variable* curVar;
      curVar = &curMod->tempVariableList.at(j);
      ReplaceMinus(curVar->name);
      ReplaceMinus(curVar->customTypeName); // module name will be changed, so need to change var type as well
    }
  }
}

void Generator::SortModules() {
  vector<string> knownModules;
  const int cLimit = 100000;
  int limitCount = 0;

  for (size_t i = 0; i < m_ModuleList.size(); i++) {
    bool registerModule = true;
    Module curMod = m_ModuleList.at(i);

    for (size_t j = 0; j < curMod.tempVariableList.size(); j++) {
      bool moduleToBePushedAtEnd = false;

      if (curMod.tempVariableList.at(j).customTypeName != "") {
        moduleToBePushedAtEnd = true;
        for (size_t k = 0; k < knownModules.size(); k++) {
          string s = knownModules.at(k);
          if (s == curMod.tempVariableList.at(j).customTypeName) {
            moduleToBePushedAtEnd = false;
            break;
          }
        }
      }

      if (moduleToBePushedAtEnd) {
        m_ModuleList.erase(m_ModuleList.begin() + i);
        m_ModuleList.push_back(curMod);
        i--;
        registerModule = false;
        break;
      }

      // safety in case of infinite loop
      limitCount++;
      if (limitCount > cLimit)
        break;
    }

    if (registerModule)
      knownModules.push_back(curMod.name);

    // safety in case of infinite loop
    limitCount++;
    if (limitCount > cLimit)
      break;
  }
}

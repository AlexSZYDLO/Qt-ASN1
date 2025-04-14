#include "CPPGenerator.h"

using namespace std;

CPPGenerator::CPPGenerator() : Generator() {}
CPPGenerator::~CPPGenerator() {}

string CPPGenerator::typeToCPPClass(eNodeType t) {
  switch(t) {
    case cBoolean:
      return "ASN1_Boolean";
    case cBitString:
      return "ASN1_BitString";
    case cChoice:
      return "ASN1_Choice";
    case cEnumerated:
      return "ASN1_Enumerated";
    case cIA5String:
      return "ASN1_IA5String";
    case cInteger:
      return "ASN1_Integer";
    case cNull:
      return "ASN1_Null";
    case cObjectID:
      return "ASN1_ObjectID";
    case cOctetString:
      return "ASN1_OctetString";
    case cReal:
      return "ASN1_Real";
    case cSequence:
      return "ASN1_Sequence";
    case cSequenceOf:
      return "ASN1_SequenceOf";
    case cSet:
      return "ASN1_Set";
    case cUTCTime:
      return "ASN1_UTCTime";
    case cUTF8String:
      return "ASN1_UTF8String";
  }
  return "";
}

inline string C(bool b) { return (b ? ", " : ""); }
inline string PAR(string param, bool c = true) { return param + C(c); } // parameter
inline string PARS(string param, bool c = true) { return "\"" + param + "\"" + C(c); } // string parameter
inline string PARB(bool param, bool c = true) { return string(param ? "true" : "false") + C(c); }
inline string TAB(int i) {
  string s;
  for(int j = 0; j < i; j++) s += "\t";
  return s;
}


void CPPGenerator::GenerateVar(Variable& v, int tab) {
  string v_name = v.name + "_" + to_string(++count);

  cppCode += TAB(tab);

  if(v.type == cSequence || v.type == cSet) {
    string nbVar = to_string(ModuleFromName(v.customTypeName).tempVariableList.size());
    string arrName = "arr_" + v_name;

    if(nbVar != "0") {
      cppCode += "ASN1_Object* arr_" + v_name + "[" + nbVar + "];\n";
    } else {
      cppCode += "ASN1_Object** arr_" + v_name + " = nullptr;\n";
    }
    cppCode += TAB(tab);
    cppCode += "Make_" + v.customTypeName + "(" + arrName + ");\n";
    cppCode += TAB(tab);
    cppCode += "ASN1_Object* " + v_name + " = new " + typeToCPPClass(v.type) + "(" +
               PAR(arrName) + PAR(nbVar) + PARS(v.name) + PARS(v.tag) + PARB(v.optional) + PARB(v.explicitTag) +
               PAR("nullptr") + PARB(ModuleFromName(v.customTypeName).extensible, false) + ");";
  } else if(v.type == cSequenceOf) {
    string callbackName = v.customTypeName + "_SeqOfCallback";
    cppCode += "ASN1_Object* " + v_name + " = new " + typeToCPPClass(v.type) + "({&" + PAR(callbackName) + PAR("nullptr}") + PARS(v.name) + PARS(v.tag) + PARB(v.optional) + PARB(v.explicitTag) + PAR("nullptr", false) + ");";
  } else if(v.type == cChoice) {
    string callbackName = v.customTypeName + "_ChoiceCallback";
    string choiceSize = to_string(ModuleFromName(v.customTypeName).tempVariableList.size());
    cppCode += "ASN1_Object* " + v_name + " = new " + typeToCPPClass(v.type) + "({&" + PAR(callbackName) + PAR("nullptr}") + PAR(choiceSize) + PARS(v.name) + PARS(v.tag) + PARB(v.optional) + PARB(v.explicitTag) + PAR("nullptr", false) + ");";
  } else {
    if(v.customTypeName == "") {
      cppCode += "ASN1_Object* " + v_name + " = new " + typeToCPPClass(v.type) + "(" + PARS(v.name) + PARS(v.tag) + PARB(v.optional) + PARB(v.explicitTag) + PAR("nullptr", false) + ");";
    } else {
      cppCode += "ASN1_Object* " + v_name + " = Make_" + v.customTypeName + "(" + PARS(v.name) + PARS(v.tag) + PARB(v.optional) + PARB(v.explicitTag) + PAR("nullptr", false) + ");";
    }
  }
  cppCode += "\n";
}

void CPPGenerator::GenerateSequenceOrSet(Module& m) {
  string nbVar = to_string(m.tempVariableList.size());
  string varArray;

  string m_FunctionName = "Make_" + m.name;
  if(nbVar != "0")
    cppCode += "void " + m_FunctionName + "(ASN1_Object** arr) { \n"; /*[" + nbVar + "]*/
  else
    cppCode += "void " + m_FunctionName + "(ASN1_Object**) { \n";

  for(size_t j = 0; j < m.tempVariableList.size(); j++) {
    Variable v = m.tempVariableList.at(j);
    GenerateVar(v);

    string v_name = v.name + "_" + to_string(count); // keep same count to get same name
    varArray += "arr[" + to_string(j) + "] = " + v_name + "; ";
  }

  cppCode += "\t" + varArray + "\n} \n\n";
}

void CPPGenerator::GenerateSequenceOf(Module& m) {
  string callbackName = m.name + "_SeqOfCallback";

  cppCode += "ASN1_Object* " + callbackName + "(void*) {\n";
  Variable v = m.tempVariableList.at(0);
  v.name = "SeqOfVar";
  GenerateVar(v);
  cppCode += "\treturn " + v.name + "_" + to_string(count) + "; \n} \n\n";
}

void CPPGenerator::GenerateChoice(Module& m) {
  string callbackName = m.name + "_ChoiceCallback";

  cppCode += "ASN1_Object* " + callbackName + "(unsigned int index, void*) {\n";
  for(unsigned int i = 0; i < m.tempVariableList.size(); i++) {
    Variable v = m.tempVariableList.at(i);
    cppCode += "\tif (index == " + to_string(i) + ") {\n";
    GenerateVar(v, 2);
    cppCode += "\t\treturn " + v.name + "_" + to_string(count) + "; \n\t}\n";
  }
  cppCode += "\treturn nullptr;\n}\n\n";
}

void CPPGenerator::GenerateSingleVarModule(Module& m) {
  Variable v = m.tempVariableList.at(0);
  string v_name = "var_" + to_string(++count);

  cppCode += "ASN1_Object* Make_" + m.name + "(const char* name, const char* tag, bool optional, bool explTag, " + typeToCPPClass(v.type) + "* defaultVal) { \n";
  cppCode += "\tASN1_Object* " + v_name + " = new " + typeToCPPClass(v.type) + "(name, tag, optional, explTag, defaultVal);\n";
  cppCode += "\treturn var_" + to_string(count) + "; \n} \n\n";
}

string CPPGenerator::Generate() {
  SortModules();
  ReviewNames();

  log("generating");
  count = 0;
  cppCode = "/*  File auto-generated by Q-ASN1. */\n";
  cppCode += "#include \"ASN1_includes.h\"\n\n";

  for(size_t i = 0; i < m_ModuleList.size(); i++) {
    Module m = m_ModuleList.at(i);

    if(m.type == cSequence || m.type == cSet) {
      GenerateSequenceOrSet(m);
    } else if(m.type == cSequenceOf) {
      GenerateSequenceOf(m);
    } else if(m.type == cChoice) {
      GenerateChoice(m);
    } else {
      GenerateSingleVarModule(m);
    }
  }

  if(m_ModuleList.size() > 0) {
    Variable v = {"main", "", false, false, false, m_ModuleList.at(m_ModuleList.size() - 1).type, false, m_ModuleList.at(m_ModuleList.size() - 1).name};

    if(m_TagExplicit) {
      v.explicitTag = true;
    }

    cppCode += "ASN1_Object* GetGrammar() {\n";
    GenerateVar(v);
    cppCode += "\treturn main_" + to_string(count) + ";\n}\n";

    return cppCode;
  } else {
    return "";
  }
}

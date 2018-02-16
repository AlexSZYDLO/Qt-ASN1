/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <string>
#include <iostream>
#include "Utils.h"

using namespace Utils;

extern std::string ParsingError;

inline void errorLog(const std::string& s) {
  std::cout << "ERROR: " << s << std::endl;
  ParsingError += s + '\n';
}

inline void log(const std::string& s) {
  std::cout << s << std::endl;
}

inline std::string* stringAssign(char* str) {
  return new std::string(str);
}

inline int ConvertToInt(const char* str) {
  int i = atol(str);
  return i;
}

inline double ConvertToDouble(const char* str) {
  double d = atof(str);
  return d;
}

enum Explicity { cIgnored, cImplicit, cExplicit };

struct Tag {
  bool noTag;
  eTagClass tagClass;
  int label;
  Explicity explicitTag;
};

struct Variable {
  std::string name;
  std::string tag;
  bool explicitTag;
  bool isAutoTag;
  bool optional;
  eNodeType type;
  bool unknownType;
  std::string customTypeName;
};

struct Module {
  std::string name;
  eNodeType type;
  std::vector<Variable> tempVariableList;
  bool extensible;
};

struct VarModule {
  std::string* name;
  eNodeType type;
};


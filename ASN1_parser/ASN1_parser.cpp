/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include <string>
#include <iostream>
#include <fstream>
#include "global.h"

//#pragma warning (push)
//#pragma warning (disable: 4005)
//#pragma warning (disable: 4065)
#include "grammar/Parser.h"
#include "grammar/Lexer.h"
//#pragma warning (pop)

#pragma warning( disable : 4996 )

#include "ASN1_parser.h"
#include "Generator.h"
#include "JSGenerator.h"
#include "CPPGenerator.h"

using namespace std;
string error = "";

int parse(const string& s) {
  error = "";
  YY_BUFFER_STATE ybuf;
  ybuf = yy_scan_bytes(s.c_str(), (int)s.size());
  yyparse();
  yy_delete_buffer(ybuf);

  return 0;
}

void FillBufferWithString(string& s, char* buff, int buffSize) {
  if (s.size() == 0) {
    buff[0] = '\0';
  }
  else if (s.size() < buffSize) {
    s.copy(buff, s.size() - 1);
    buff[s.size() - 1] = '\0';
  }
  else {
    s.copy(buff, buffSize - 1);
    buff[buffSize - 1] = '\0';
  }
}

template <class gen>
bool ParseToFormat(const string& in, string& out) {
  gGen = new gen();
  parse(in);

  if (error.empty())
    out = gGen->Generate();

  delete gGen;

  if (!error.empty())
    return false;

  if (!out.empty()) {
    string err = "Generation failed after correct parsing.";
    return false;
  }
  return true;
}

bool ASNBufferToJSBuffer(const char* inBuffer, char* outBuffer, int bufferSize, char* errorBuff, int errorBuffSize) {
  string JS;
  bool b = ParseToFormat<JSGenerator>(inBuffer, JS);

  FillBufferWithString(JS, outBuffer, bufferSize);
  FillBufferWithString(error, errorBuff, errorBuffSize);

  return b;
}

bool ASNFileToJSFile(const char* inPath, const char* outPath, char* errorBuff, int errorBuffSize) {
  ifstream myfile(inPath);
  string s((istreambuf_iterator<char>(myfile)), (istreambuf_iterator<char>()));
  string JS;

  ParseToFormat<JSGenerator>(s, JS);
  FillBufferWithString(error, errorBuff, errorBuffSize);

  if (!JS.empty()) {
    ofstream myfile(outPath);
    myfile.write(JS.c_str(), JS.size());
    return true;
  }
  return false;
}

bool ASNBufferToCPPBuffer(const char* inBuffer, char* outBuffer, int bufferSize, char* errorBuff, int errorBuffSize) {
  string CPP;
  bool b = ParseToFormat<CPPGenerator>(inBuffer, CPP);

  FillBufferWithString(CPP, outBuffer, bufferSize);
  FillBufferWithString(error, errorBuff, errorBuffSize);

  return b;
}

bool ASNFileToCPPFile(const char* inPath, const char* outPath, char* errorBuff, int errorBuffSize) {
  ifstream myfile(inPath);
  string s((istreambuf_iterator<char>(myfile)), (istreambuf_iterator<char>()));
  string CPP;

  ParseToFormat<CPPGenerator>(s, CPP);
  FillBufferWithString(error, errorBuff, errorBuffSize);

  if (!CPP.empty()) {
    ofstream myfile(outPath);
    myfile.write(CPP.c_str(), CPP.size());
    return true;
  }
  return false;
}
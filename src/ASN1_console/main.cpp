﻿/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include <cmath>
#include <codecvt>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "../Grammar/Grammar_test.h"
// #include "../Grammar/Grammar_DLL.h"
#include "../Grammar/Test_comp.h"
#include "ASN1_parser.h"

using namespace Grammar;

bool test_ByteArray()
{
  bool b = true;
  ByteArray hex("010203040506070809AABBCCDDEEFF");
  ByteArray hex2 = hex;
  b &= hex == hex2;
  b &= hex.Equals(hex2);
  b &= hex.Size() == 15;
  b &= hex[5] == "06";

  ByteArray hex3;
  b &= hex.GetByteAtRank(3, hex3);
  b &= !hex.GetByteAtRank(50, hex3); // error
  b &= hex3 == "04";

  ByteArray hex4;
  b &= hex.GetBytesAtRank(3, 5, hex4);
  b &= !hex.GetBytesAtRank(25, 25, hex4);
  b &= hex4 == "0405060708";

  b &= hex.InsertAt("AABB", 4);
  b &= !hex.InsertAt("AABB", 50); // error
  b &= hex == "01020304AABB0506070809AABBCCDDEEFF";
  hex.Clear();
  b &= hex.Size() == 0;
  b &= hex.Equals("");

  return b;
}

bool test_ChoiceList()
{
  ASN1_Choice *choice = MakeChoiceTest("testChoice", "AA");

  choice->MakeDummyChoiceList();
  std::vector<const ASN1_Object *> choiceList;
  for (unsigned int i = 0; i < choice->AvailableChoices(); i++)
    choiceList.push_back(choice->GetChoiceFromIndex(i));
  choice->SetSelectedChoice(1);
  choice->DeleteDummyChoiceList();
  unsigned int a = choice->GetSelectedChoiceIndex();
  delete choice;
  return a == 1;
}

bool test_Tags()
{
  bool res = true;
  ByteArray tA = Utils::MakeTag(Utils::cTagClassContextSpecific, Utils::cTagFormConstructed, ByteArray("1C80"));
  ByteArray tB = Utils::MakeTag(Utils::cTagClassContextSpecific, Utils::cTagFormConstructed, ByteArray("1C80"));

  Utils::eTagClass cl;
  Utils::eTagForm fo;
  ByteArray reconstructedLbl;
  Utils::DecomposeTag(tA, cl, fo, reconstructedLbl);

  res &= cl == Utils::cTagClassContextSpecific;
  res &= fo == Utils::cTagFormConstructed;
  res &= reconstructedLbl == "1C80";

  ASN1_Integer a("a", tA, false, false, nullptr), b("b", tB);
  a.SetValue(5);

  std::string buf;
  ByteArray output;
  a.WriteIntoBuffer(output);
  b.ReadFromBuffer(output, buf);
  res &= 5 == b.GetValue();

  if (!Utils::DecomposeTag("CA45", cl, fo, reconstructedLbl))
  {
  }
  else
  {
    res = false;
  }
  return res;
}

bool test_Sequence()
{
  std::string err, UTCTime;
  SequenceTestVars varTest1, varTest2;
  ASN1_Sequence *test = MakeSequenceTest("testSeq", "", varTest1);
  ASN1_Sequence *test2 = MakeSequenceTest("testSeq", "", varTest2);

  static_cast<ASN1_Integer *>(varTest1.a->SetSelectedChoice(2))->SetValue(500);
  varTest1.b->SetValue("11110000111100001111");
  varTest1.c->SetValue(true);
  varTest1.d->SetValue(4);
  varTest1.e->SetValue("alexandre");
  varTest1.f->SetValue(-6500);
  varTest1.g->Ignore();
  varTest1.h->SetValue("2.12.15632.875.1.625");
  varTest1.i->SetValue("00112233445566778899aabbccddeeff");
  varTest1.j->SetValue(2500.3652);

  Utils::ValuesToUTCTime(90, 01, 03, 17, 02, 00, Utils::cPlus, 01, 00, UTCTime, err);
  varTest1.k->SetValue(UTCTime);

  varTest1.l->SetValue("szydlowski");

  ByteArray buffer("");
  std::string err2;
  test->WriteIntoBuffer(buffer);
  test2->ReadFromBuffer(buffer, err2);

  int a = 0;
  if (varTest2.a->GetSelectedChoiceIndex() == 2)
  {
    a = static_cast<ASN1_Integer *>(varTest2.a->GetSelectedChoice())->GetValue();
  }
  std::string b = varTest2.b->GetValue();
  bool c = varTest2.c->GetValue();
  int d = varTest2.d->GetValue();

  std::string e = varTest2.e->GetValue();
  int f = varTest2.f->GetValue();
  bool g = varTest2.g->IsIgnored();
  std::string h = varTest2.h->GetValue();
  std::string i = varTest2.i->GetValue().GetString();
  double j = varTest2.j->GetValue();
  std::string k = varTest2.k->GetValue();
  std::string l = varTest2.l->GetValue();

  bool result = true;
  result &= a == 500;
  result &= b == "11110000111100001111";
  result &= c == true;
  result &= d == 4;
  result &= e == "alexandre";
  result &= f == -6500;
  result &= g == true;
  result &= h == "2.12.15632.875.1.625";
  result &= i == "00112233445566778899AABBCCDDEEFF";
  result &= j == 2500.3652;
  result &= (k == "9001031702+0100") && (UTCTime == "9001031702+0100");
  result &= l == "szydlowski";

  delete test;
  delete test2;
  return result;
}

bool test_SequenceOf()
{
  ASN1_SequenceOf *seqof = MakeSequenceOfTest("SequenceOf", "AA");
  ASN1_SequenceOf *seqof2 = MakeSequenceOfTest("SequenceOf2", "AA");

  static_cast<ASN1_Integer *>(seqof->AppendNewObject())->SetValue(1);
  static_cast<ASN1_Integer *>(seqof->AppendNewObject())->SetValue(2);
  static_cast<ASN1_Integer *>(seqof->AppendNewObject())->SetValue(3);
  static_cast<ASN1_Integer *>(seqof->AppendNewObject())->SetValue(4);
  static_cast<ASN1_Integer *>(seqof->AppendNewObject())->SetValue(5);
  static_cast<ASN1_Integer *>(seqof->AppendNewObject())->SetValue(6);
  seqof->MoveUpObject(1);
  seqof->MoveDownObject(4);
  seqof->DeleteObjectAt(2);

  ByteArray buffer;
  std::string err;
  seqof->WriteIntoBuffer(buffer);
  seqof2->ReadFromBuffer(buffer, err);

  std::stringstream s;
  //s << seqof2.StringExtractForResearch();
  for (unsigned int i = 0; i < seqof2->GetSequenceOfSize(); i++)
  {
    s << static_cast<ASN1_Integer *>(seqof2->GetObjectAt(i))->GetValue();
  }
  bool result = s.str() == "21465";

  delete seqof;
  delete seqof2;
  return result;
}

bool test_BitString()
{
  ASN1_BitString *bitstr = new ASN1_BitString();
  bitstr->SetValue("");
  ByteArray hex;
  bitstr->WriteIntoBuffer(hex);
  std::string test(hex.GetString());

  std::string err;
  ASN1_BitString *bitstr2 = new ASN1_BitString();
  bitstr2->ReadFromBuffer(hex, err);
  std::string test2(bitstr2->GetValue());

  delete bitstr;
  delete bitstr2;
  return test2 == "";
}

bool test_OID_helper(const ByteArray &_hex, const std::string &str)
{
  ByteArray hex;
  bool b = true;

  ASN1_ObjectID *oid = new ASN1_ObjectID();
  oid->SetValue(str);
  oid->WriteIntoBuffer(hex);
  std::string test(hex.GetString());
  b &= test == _hex.GetString();

  std::string err;
  oid->ReadFromBuffer(hex, err);
  std::string test2(oid->GetValue());
  b &= test2 == str;

  delete oid;
  return b;
}

bool test_ObjectID()
{
  bool b = true;
  b &= !Utils::IsValidObjectID("1.52.3.5"); // error
  b &= !Utils::IsValidObjectID("1");        // error
  b &= Utils::IsValidObjectID("1.1");
  b &= Utils::IsValidObjectID("1.23.5126.3547.652.946321.2");

  b &= test_OID_helper("060B3FA8069B5B850CB9E11102", "1.23.5126.3547.652.946321.2");
  b &= test_OID_helper("0603420305", "1.26.3.5");
  b &= !test_OID_helper("0600", "1.52.3.5"); // error, write is ok empty, but read wont work
  b &= !test_OID_helper("0600", "1");        // error, write is ok empty , but read wont work
  b &= test_OID_helper("060481040305", "2.52.3.5");
  b &= test_OID_helper("060103", "0.3");
  b &= test_OID_helper("060489AE220C", "2.153298.12");
  b &= test_OID_helper("060100", "0.0");
  b &= test_OID_helper("060428000001", "1.0.0.0.1");
  return b;
}

bool test_Real()
{
  SequenceRealVars vars, vars2;

  ASN1_Sequence *real = MakeRealSequenceTest("real seq", "", vars);
  vars.a->SetValue(2.5);
  vars.b->SetValue(-2.5);
  vars.c->SetValue(255003.5635);
  vars.d->SetValue(-3521.5123);
  vars.e->SetValue(NAN);
  vars.f->SetValue(0.326536985632648795123);

  ByteArray hex;
  real->WriteIntoBuffer(hex);
  std::string test(hex.GetString());

  std::string err;
  ASN1_Sequence *real2 = MakeRealSequenceTest("real seq2", "", vars2);
  real2->ReadFromBuffer(hex, err);

  double res1 = vars2.a->GetValue();
  double res2 = vars2.b->GetValue();
  double res3 = vars2.c->GetValue();
  double res4 = vars2.d->GetValue();
  double res5 = vars2.e->GetValue();
  double res6 = vars2.f->GetValue();

  bool b = true;
  b &= res1 == 2.5;
  b &= res2 == -2.5;
  b &= res3 == 255003.5635;
  b &= res4 == -3521.5123;
  b &= std::isnan(res5);
  b &= res6 == 0.326536985632648795123;

  delete real;
  delete real2;
  return b;
}

bool test_Set()
{
  SetTestVars vars, vars2;
  ASN1_Set *t = MakeSetTest("settest", "", vars);
  vars.a->SetValue(542.312);
  vars.b->SetValue(563);
  vars.c->SetValue(true);
  vars.d->SetValue("AABBCCDDEEFF00");

  ByteArray hex1;
  t->WriteIntoBuffer(hex1);

  //HexString hexCst = "311B090980D510F27EF9DB22D1020202330101FF0407AABBCCDDEEFF00"; // good order
  ByteArray hexCst = "311B0407AABBCCDDEEFF000101FF02020233090980D510F27EF9DB22D1"; // remixed

  std::string err;
  ASN1_Set *t2 = MakeSetTest("settest", "", vars2);
  t2->ReadFromBuffer(hexCst, err);

  ByteArray hex2;
  t2->WriteIntoBuffer(hex2);

  delete t;
  delete t2;
  return hex1 == hex2;
}

bool test_IA5String_UTF8String()
{
  using namespace std;
  wstring_convert<codecvt_utf8<wchar_t>, wchar_t> conv;

  wstring s = L"àë";
  wstring s2 = L"al";
  std::string str = reinterpret_cast<const char *>(s.c_str());

  bool res = true;

  std::string utf8str = conv.to_bytes(s);
  std::string utf8str2 = conv.to_bytes(s2);
  res &= Utils::IsValidUTF8String(utf8str) == true;
  res &= Utils::IsValidIA5String(utf8str) == false;

  res &= Utils::IsValidUTF8String(utf8str2) == true;
  res &= Utils::IsValidIA5String(utf8str2) == true;

  utf8str = "\x9A\xC6\x00";
  res &= Utils::IsValidUTF8String(utf8str) == false;

  utf8str = "\xD0\xB0\xD0\xBB\x00";
  res &= Utils::IsValidUTF8String(utf8str) == true;

  wstring recovered = L"";
  try
  {
    recovered = conv.from_bytes(utf8str);
  }
  catch (const range_error &e)
  {
    cout << e.what() << endl;
  }

  res &= recovered == L"ал";
  return res;
}

bool test_Compare()
{
  ASN1_Integer *a = new ASN1_Integer("test");
  ASN1_Integer *b = new ASN1_Integer("test2");
  a->SetValue(5);
  b->SetValue(15);

  std::string comp;
  unsigned int nbDiffs = 0;
  a->Compare(*b, nbDiffs, comp);

  return true;
}

bool test_ParserJS()
{
  char *errorBuff = new char[500];
  errorBuff[0] = '\0';

  char *jsbuff = new char[1];

  ASNFileToJSFile("PEDefinitions V1.0_edit.asn", "out.js", errorBuff, 500);
  ASNFileToJSFile("gramm_test.asn", "out2.js", errorBuff, 500);
  ASNBufferToJSBuffer("", jsbuff, 1, errorBuff, 500); // empty input

  std::string err(errorBuff);
  if (err != "")
  {
    std::cout << err << std::endl;
    return false;
  }
  else
  std::cout << "Parsing grammar to JS OK." << std::endl;

  delete[] jsbuff;
  delete[] errorBuff;
  return true;
}

bool test_ParserCPP()
{
  char *errorBuff = new char[500];
  errorBuff[0] = '\0';

  ASNFileToCPPFile("PEDefinitions V1.0_edit.asn", "out.h", errorBuff, 500);
  ASNFileToCPPFile("gramm_test.asn", "out2.h", errorBuff, 500);

  std::string err(errorBuff);
  if (err != "")
  {
    std::cout << err << std::endl;
    return false;
  }
  else
  std::cout << "Parsing grammar to CPP OK." << std::endl;

  delete[] errorBuff;
  return true;
}

bool test_ParsedGrammar()
{
  ASN1_Object *obj = GetGrammar();
  ByteArray ba;
  obj->WriteIntoBuffer(ba);
  return true;
}

int main()
{
  std::cout << "start test" << std::endl;
  bool result = true;

  result &= test_ByteArray();
  result &= test_ChoiceList();
  result &= test_Tags();
  result &= test_Sequence();
  result &= test_SequenceOf();
  result &= test_BitString();
  result &= test_ObjectID();
  result &= test_Real();
  result &= test_Set();
  // result &= test_DLL();
  result &= test_IA5String_UTF8String();
  result &= test_Compare();
  // result &= test_ParserJS();
  // result &= test_ParserCPP();
  result &= test_ParsedGrammar();

  std::cout << "test result: " << (result ? "OK" : "NOK") << std::endl;
  std::cout << "memory: " << (ASN1_Object::memoryCheck() ? "OK" : "NOK") << std::endl;

  std::cout << "test done" << std::endl;
  return result ? 0 : -1;
}

/*
bool test_DLL() {
  using namespace ASN1_DLL;

  bool res = true;
  wstring dllPath;

#if defined (_WIN64)
#if defined (_DEBUG)
  dllPath = L"ASN1_lib_64d.dll";
#elif defined (NDEBUG)
  dllPath = L"ASN1_lib_64.dll";
#endif
#elif defined (_MSC_VER)
#if defined (_DEBUG)
  dllPath = L"ASN1_lib_32d.dll";
#elif defined (NDEBUG)
  dllPath = L"ASN1_lib_32.dll";
#endif
#endif

  if (!LoadASN1DLL(dllPath))
    return false;

  {
    Hex a("010203040506070809AABBCCDDEEFF");
    Hex b("a");
    ByteArray_Append(a.p(), b.p());
    ByteArray_InsertAt(a.p(), a.p(), 0);

    string s(ByteArray_GetString(a.p()));
    res = s == "010203040506070809AABBCCDDEEFF0A010203040506070809AABBCCDDEEFF0A";
  }

  {
    Hex a("");
    Hex tagLbl("1234");
    Utils_MakeTag(0, 0, tagLbl.p(), a.p());

    string s(ByteArray_GetString(a.p()));
    res &= s == "1FA434";
  }

  {
    bool boolVar;
    Hex tag("");
    DLL_ASN1_Boolean* b = NewObj(ASN1_Boolean_New("Boolean", tag.p(), false, false, nullptr));
    ASN1_Boolean_SetValue(b, true);

    ASN1_Boolean_GetValue(b, &boolVar);
    res &= boolVar == true;

    ASN1_Boolean_SetValue(b, false);
    ASN1_Boolean_GetValue(b, &boolVar);
    res &= boolVar == false;

    DLL_ASN1_Sequence* seq = DLL_MakeGrammar();
    DLL_ASN1_Choice* choice = reinterpret_cast<DLL_ASN1_Choice*>(ASN1_Sequence_GetObjectAt(seq, 1));
    ASN1_Integer_SetValue(reinterpret_cast<DLL_ASN1_Integer*>(ASN1_Choice_SetSelectedChoice(choice, 1)), 150);
    DLL_ASN1_Integer* integerChoice = reinterpret_cast<DLL_ASN1_Integer*>(ASN1_Choice_GetSelectedChoice(choice));

    int integerResult;
    ASN1_Integer_GetValue(integerChoice, &integerResult);
    res &= integerResult == 150;
    res &= ASN1_Choice_GetSelectedChoiceIndex(choice) == 1;

    DLL_ASN1_ObjectID* oid = reinterpret_cast<DLL_ASN1_ObjectID*>(ASN1_Sequence_GetObjectAt(seq, 6));
    ASN1_ObjectID_SetValue(oid, "1.23.5126.3547.652.946321.2");

    Hex buffer("");
    ASN1_Object_WriteIntoBuffer(reinterpret_cast<DLL_ASN1_Object*>(seq), buffer.p());
    string output(ByteArray_GetString(buffer.p()));

    char charbuff[512];

    DLL_ASN1_Sequence* seq2 = DLL_MakeGrammar();
    ASN1_Object_ReadFromBuffer(reinterpret_cast<DLL_ASN1_Object*>(seq2), buffer.p(), charbuff, 512);
    DLL_ASN1_ObjectID* oid2 = reinterpret_cast<DLL_ASN1_ObjectID*>(ASN1_Sequence_GetObjectAt(seq2, 6));
    ASN1_ObjectID_GetValue(oid2, charbuff, 512);
    string oidStr(charbuff);
    res &= oidStr == "1.23.5126.3547.652.946321.2";
  }

  for (unsigned int i = 0; i < toDelete.size(); i++)
    ASN1_Object_Delete(toDelete.at(i));

  {
    char errorBuff[512];
    char charBuff[512];
    Hex buffer("");
    string str;

    ASN1_ObjectID_ObjectIDToHex("1.12.5236.5", buffer.p(), errorBuff, 512);

    if (string(errorBuff) != "") str = errorBuff;
    else str = ByteArray_GetString(buffer.p());

    Hex buffer2(str.c_str());
    ASN1_ObjectID_HexToObjectID(buffer2.p(), charBuff, 512, errorBuff, 512);

    if (string(errorBuff) != "") str = errorBuff;
    else str = charBuff;

    res = str == "1.12.5236.5";
  }

  {
    char errorBuff[512];
    char charBuff[512];
    Hex buffer("");
    string str;

    ASN1_IA5String_IA5StringToHex("alexandre", buffer.p(), errorBuff, 512);

    if (string(errorBuff) != "") str = errorBuff;
    else str = ByteArray_GetString(buffer.p());

    Hex buffer2(str.c_str());
    ASN1_IA5String_HexToIA5String(buffer2.p(), charBuff, 512, errorBuff, 512);

    if (string(errorBuff) != "") str = errorBuff;
    else str = charBuff;

    res = str == "alexandre";
  }
  return res;
}
*/

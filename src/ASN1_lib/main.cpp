/*
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
#include <chrono>
#include "Grammar_test.h"
#include "Test_comp.h"


using namespace Grammar;
using namespace std;

bool test_ChoiceList() {
  ASN1_Choice* choice = MakeChoiceTest("testChoice", "AA");

  choice->MakeDummyChoiceList();
  vector<const ASN1_Object*> choiceList;
  for(unsigned int i = 0; i < choice->AvailableChoices(); i++)
    choiceList.push_back(choice->GetChoiceFromIndex(i));
  choice->SetSelectedChoice(1);
  choice->DeleteDummyChoiceList();
  unsigned int a = choice->GetSelectedChoiceIndex();
  delete choice;
  return a == 1;
}

bool test_Tags() {
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
  a.SetIntegerValue(5);


  char c[2000];
  ByteArray output;
  a.WriteIntoBuffer(output);
  b.ReadFromBuffer(output, c, 2000);
  res &= 5 == b.GetIntegerValue();

  if(!Utils::DecomposeTag("CA45", cl, fo, reconstructedLbl)) {
  } else {
    res = false;
  }
  return res;
}

bool test_Sequence() {
  string err, UTCTime;
  SequenceTestVars varTest1, varTest2;
  ASN1_Sequence* test = MakeSequenceTest("testSeq", "", varTest1);
  ASN1_Sequence* test2 = MakeSequenceTest("testSeq", "", varTest2);

  static_cast<ASN1_Integer*>(varTest1.a->SetSelectedChoice(2))->SetIntegerValue(500);
  varTest1.b->SetBitStringValue("11110000111100001111");
  varTest1.c->SetBooleanValue(true);
  varTest1.d->SetEnumeratedValue(4);
  varTest1.e->SetIA5StringValue("alexandre");
  varTest1.f->SetIntegerValue(-6500);
  varTest1.g->Ignore();
  varTest1.h->SetObjectIDValue("2.12.15632.875.1.625");
  varTest1.i->SetOctetStringValue("00112233445566778899aabbccddeeff");
  varTest1.j->SetRealValue(2500.3652);

  Utils::ValuesToUTCTime(90, 01, 03, 17, 02, 00, Utils::cPlus, 01, 00, UTCTime, err);
  varTest1.k->SetUTCTimeValue(UTCTime);

  varTest1.l->SetUTF8StringValue("szydlowski");

  char cBuff[2000];
  ByteArray buffer("");
  test->WriteIntoBuffer(buffer);
  test2->ReadFromBuffer(buffer, cBuff, 2000);

  int a = 0;
  if(varTest2.a->GetSelectedChoiceIndex() == 2) {
    a = static_cast<ASN1_Integer*>(varTest2.a->GetSelectedChoice())->GetIntegerValue();
  }
  string b = varTest2.b->GetBitStringValue();
  bool c = varTest2.c->GetBooleanValue();
  int d = varTest2.d->GetEnumeratedValue();

  string e = varTest2.e->GetIA5StringValue();
  int f = varTest2.f->GetIntegerValue();
  bool g = varTest2.g->IsIgnored();
  string h = varTest2.h->GetObjectIDValue();
  string i = varTest2.i->GetOctetStringValue().GetString();
  double j = varTest2.j->GetRealValue();
  string k = varTest2.k->GetUTCTimeValue();
  string l = varTest2.l->GetUTF8StringValue();

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

bool test_SequenceOf() {
  ASN1_SequenceOf* seqof = MakeSequenceOfTest("SequenceOf", "AA");
  ASN1_SequenceOf* seqof2 = MakeSequenceOfTest("SequenceOf2", "AA");

  static_cast<ASN1_Integer*>(seqof->AppendNewObject())->SetIntegerValue(1);
  static_cast<ASN1_Integer*>(seqof->AppendNewObject())->SetIntegerValue(2);
  static_cast<ASN1_Integer*>(seqof->AppendNewObject())->SetIntegerValue(3);
  static_cast<ASN1_Integer*>(seqof->AppendNewObject())->SetIntegerValue(4);
  static_cast<ASN1_Integer*>(seqof->AppendNewObject())->SetIntegerValue(5);
  static_cast<ASN1_Integer*>(seqof->AppendNewObject())->SetIntegerValue(6);
  seqof->MoveUpObject(1);
  seqof->MoveDownObject(4);
  seqof->DeleteObjectAt(2);

  char cBuff[2000];
  ByteArray buffer;
  seqof->WriteIntoBuffer(buffer);
  seqof2->ReadFromBuffer(buffer, cBuff, 2000);

  stringstream s;
  //s << seqof2.StringExtractForResearch();
  for(unsigned int i = 0; i < seqof2->GetSequenceOfSize(); i++) {
    s << static_cast<ASN1_Integer*>(seqof2->GetObjectAt(i))->GetIntegerValue();
  }
  bool result = s.str() == "21465";

  delete seqof;
  delete seqof2;
  return result;
}

bool test_BitString() {
  char cBuff[2000];

  ASN1_BitString* bitstr = new ASN1_BitString();
  bitstr->SetBitStringValue("");
  ByteArray hex;
  bitstr->WriteIntoBuffer(hex);
  string test = hex.GetString();

  ASN1_BitString* bitstr2 = new ASN1_BitString();
  bitstr2->ReadFromBuffer(hex, cBuff, 2000);
  string test2(bitstr2->GetBitStringValue());

  delete bitstr;
  delete bitstr2;
  return test2 == "";
}

bool test_OID_helper(const ByteArray& _hex, const string& str) {
  ByteArray hex;
  char cBuff[2000];
  bool b = true;

  ASN1_ObjectID* oid = new ASN1_ObjectID();
  oid->SetObjectIDValue(str);
  oid->WriteIntoBuffer(hex);
  string test = hex.GetString();
  b &= test == _hex.GetString();

  oid->ReadFromBuffer(hex, cBuff, 2000);
  string test2(oid->GetObjectIDValue());
  b &= test2 == str;

  delete oid;
  return b;
}

bool test_ObjectID() {
  bool b = true;
  b &= !Utils::IsValidObjectID("1.52.3.5"); // error
  b &= !Utils::IsValidObjectID("1"); // error
  b &= Utils::IsValidObjectID("1.1");
  b &= Utils::IsValidObjectID("1.23.5126.3547.652.946321.2");

  b &= test_OID_helper("060B3FA8069B5B850CB9E11102", "1.23.5126.3547.652.946321.2");
  b &= test_OID_helper("0603420305", "1.26.3.5");
  b &= !test_OID_helper("0600", "1.52.3.5"); // error, write is ok empty, but read wont work
  b &= !test_OID_helper("0600", "1"); // error, write is ok empty , but read wont work
  b &= test_OID_helper("060481040305", "2.52.3.5");
  b &= test_OID_helper("060103", "0.3");
  b &= test_OID_helper("060489AE220C", "2.153298.12");
  b &= test_OID_helper("060100", "0.0");
  b &= test_OID_helper("060428000001", "1.0.0.0.1");
  return b;
}

bool test_Real() {
  char cBuff[2000];
  SequenceRealVars vars, vars2;

  ASN1_Sequence* real = MakeRealSequenceTest("real seq", "", vars);
  vars.a->SetRealValue(2.5);
  vars.b->SetRealValue(-2.5);
  vars.c->SetRealValue(255003.5635);
  vars.d->SetRealValue(-3521.5123);
  vars.e->SetRealValue(NAN);
  vars.f->SetRealValue(0.326536985632648795123);

  ByteArray hex;
  real->WriteIntoBuffer(hex);
  string test = hex.GetString();

  ASN1_Sequence* real2 = MakeRealSequenceTest("real seq2", "", vars2);
  real2->ReadFromBuffer(hex, cBuff, 2000);

  double res1 = vars2.a->GetRealValue();
  double res2 = vars2.b->GetRealValue();
  double res3 = vars2.c->GetRealValue();
  double res4 = vars2.d->GetRealValue();
  double res5 = vars2.e->GetRealValue();
  double res6 = vars2.f->GetRealValue();

  bool b = true;
  b &= res1 == 2.5;
  b &= res2 == -2.5;
  b &= res3 == 255003.5635;
  b &= res4 == -3521.5123;
  b &= isnan(res5);
  b &= res6 == 0.326536985632648795123;

  delete real;
  delete real2;
  return b;
}

bool test_Set() {
  char cBuff[2000];
  SetTestVars vars, vars2;
  ASN1_Set* t = MakeSetTest("settest", "", vars);
  vars.a->SetRealValue(542.312);
  vars.b->SetIntegerValue(563);
  vars.c->SetBooleanValue(true);
  vars.d->SetOctetStringValue("AABBCCDDEEFF00");

  ByteArray hex1;
  t->WriteIntoBuffer(hex1);

  //HexString hexCst = "311B090980D510F27EF9DB22D1020202330101FF0407AABBCCDDEEFF00"; // good order
  ByteArray hexCst = "311B0407AABBCCDDEEFF000101FF02020233090980D510F27EF9DB22D1"; // remixed

  ASN1_Set* t2 = MakeSetTest("settest", "", vars2);
  t2->ReadFromBuffer(hexCst, cBuff, 2000);

  ByteArray hex2;
  t2->WriteIntoBuffer(hex2);

  delete t;
  delete t2;
  return hex1 == hex2;
}

bool test_IA5String_UTF8String() {
  using namespace std;
  wstring_convert<codecvt_utf8<wchar_t>, wchar_t> conv;

  wstring s = L"àë";
  wstring s2 = L"al";
  string str = reinterpret_cast<const char*>(s.c_str());

  bool res = true;

  string utf8str = conv.to_bytes(s);
  string utf8str2 = conv.to_bytes(s2);
  res &= Utils::IsValidUTF8String(utf8str) == true;
  res &= Utils::IsValidIA5String(utf8str) == false;

  res &= Utils::IsValidUTF8String(utf8str2) == true;
  res &= Utils::IsValidIA5String(utf8str2) == true;

  utf8str = "\x9A""\xC6""\x00";
  res &= Utils::IsValidUTF8String(utf8str) == false;

  utf8str = "\xD0""\xB0""\xD0""\xBB""\x00";
  res &= Utils::IsValidUTF8String(utf8str) == true;

  wstring recovered = L"";
  try {
    recovered = conv.from_bytes(utf8str);
  } catch(const range_error& e) {
    cout << e.what() << endl;
  }

  res &= recovered == L"ал";
  return res;
}

bool test_Compare() {
  ASN1_Integer* a = new ASN1_Integer("test");
  ASN1_Integer* b = new ASN1_Integer("test2");
  a->SetIntegerValue(5);
  b->SetIntegerValue(15);

  char comp[5];
  unsigned int nbDiffs = 0;
  a->Compare(*b, nbDiffs, comp, 5);

  return true;
}

bool test_ParsedGrammar() {
  ASN1_Object* obj = GetGrammar();
  ByteArray ba;
  obj->WriteIntoBuffer(ba);
  std::cout << ba.GetString() << ". Expects: 3009A000A105A303020100" << std::endl;
  return true;
}

void test()
{
  auto start = std::chrono::steady_clock::now();

  // 700'000ms with std string

  for(int i = 0; i < 1; i++) {
    ByteArray b("ae12faae12faae12faae12faae12faae12faae12faae12fa");
    std::cout << b.GetString() << std::endl;
    ByteArray t1;
    b.GetByteAtRank(4, t1);
    std::cout << t1.GetString() << std::endl;
    ByteArray t2;
    b.GetBytesAtRank(4, 3, t2);
    std::cout << t2.GetString() << std::endl;
  }

  auto stop = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
}


int main() {
  bool result = true;

  test();

  // result &= test_ChoiceList();
  // result &= test_Tags();
  // result &= test_Sequence();
  // result &= test_SequenceOf();
  // result &= test_BitString();
  // result &= test_ObjectID();
  // result &= test_Real();
  // result &= test_Set();
  // result &= test_IA5String_UTF8String();
  // result &= test_Compare();
  // result &= test_ParsedGrammar();

  cout << "test result: " << (result ? "OK" : "NOK") << endl;
  cout << "memory: " << (ASN1_Object::memoryCheck() ? "OK" : "NOK") << endl;

  return result ? 0 : -1;
}

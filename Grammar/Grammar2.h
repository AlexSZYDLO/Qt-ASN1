/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "ASN1_includes.h"
/*
class Personnage : public ASN1_Sequence {
 public:
  Personnage(const std::string& name = "", const HexString& tag = "")
    : ASN1_Sequence(name, tag, false, false, false, nullptr) {
    AppendObject(a);
    AppendObject(b);
    AppendObject(c);
  }

  ASN1_IA5String* a        = new ASN1_IA5String("prenom");
  ASN1_IA5String* b        = new ASN1_IA5String("nom");
  ASN1_Integer* c          = new ASN1_Integer("age");
};

class ChoiceTest : public ASN1_Choice {
 public:
  ChoiceTest(const std::string& name = "", const HexString& tag = "",
             bool optional = false, bool explicitTag = false, bool extensibility = false, const ASN1_Choice* defaultValue = nullptr)
    : ASN1_Choice(name, tag, optional, explicitTag, extensibility, defaultValue) {}
  mutable ASN1_Integer* a, *b, *c;
  mutable Personnage* d;
  ASN1_Object* CreateChoiceFromIndex(int idx) const {
    switch (idx) {
    case 0: a = new ASN1_Integer("integer a", "0A"); return a;
    case 1: b = new ASN1_Integer("integer b", "0B"); return b;
    case 2: c = new ASN1_Integer("integer c", "0C"); return c;
    case 3: d = new Personnage("perso", "0D"); return d;
    default: return nullptr;
    }
  }

  void CreateDummyChoiceList() const {
    for (int i = 0; i < 4; i++)
      AppendChoice(CreateChoiceFromIndex(i));
  }
};

class SequenceTest_sub : public ASN1_Sequence {
 public:
  SequenceTest_sub(const std::string& name = "", const HexString& tag = "",
                   bool optional = false, bool explicitTag = false, bool extensibility = false, const ASN1_Sequence* defaultValue = nullptr)
    : ASN1_Sequence(name, tag, optional, explicitTag, extensibility, defaultValue) {
    AppendObject(a);
    AppendObject(b);
    AppendObject(c);
    AppendObject(d);
    AppendObject(e);
    AppendObject(f);
    AppendObject(g);
    AppendObject(h);
    AppendObject(i);
    AppendObject(j);
    AppendObject(k);
    AppendObject(l);

    defB->SetBitStringValue("010101");
  }

  ChoiceTest* a = new ChoiceTest("choice c");
  ASN1_BitString* defB     = new ASN1_BitString("default bitstring");
  ASN1_BitString* b        = new ASN1_BitString("bitstring", "", false, false, false, defB);
  ASN1_Boolean* c          = new ASN1_Boolean("boolean");
  ASN1_Enumerated* d       = new ASN1_Enumerated("enum");
  ASN1_rIA5String* e        = new ASN1_rIA5String("ia5 string");
  ASN1_Integer* f          = new ASN1_Integer("integer a");
  ASN1_Null* g             = new ASN1_Null("null", "", true);
  ASN1_ObjectID* h         = new ASN1_ObjectID("OID");
  ASN1_OctetString* i      = new ASN1_OctetString("octet string");
  ASN1_Real* j             = new ASN1_Real("real");
  ASN1_UTCTime* k          = new ASN1_UTCTime("utc time");
  ASN1_UTF8String* l       = new ASN1_UTF8String("utf8 string");
};

class SequenceTest : public ASN1_Sequence {
 public:
  SequenceTest(const std::string& name = "", const HexString& tag = "",
               bool optional = false, bool explicitTag = false, bool extensibility = false, const ASN1_Sequence* defaultValue = nullptr)
    : ASN1_Sequence(name, tag, optional, explicitTag, extensibility, defaultValue) {
    AppendObject(a);
    AppendObject(b);
    AppendObject(c);
    AppendObject(d);
    AppendObject(e);
    AppendObject(f);
    AppendObject(g);
    AppendObject(seq2);
    AppendObject(h);
    AppendObject(i);
    AppendObject(j);
    AppendObject(k);
    AppendObject(l);

    defB->SetBitStringValue("010101");
  }

  ChoiceTest* a = new ChoiceTest("choice c");
  ASN1_BitString* defB     = new ASN1_BitString("default bitstring");
  ASN1_BitString* b        = new ASN1_BitString("bitstring", "", false, false, false, defB);
  ASN1_Boolean* c          = new ASN1_Boolean("boolean");
  ASN1_Enumerated* d       = new ASN1_Enumerated("enum");
  ASN1_rIA5String* e        = new ASN1_rIA5String("ia5 string");
  ASN1_Integer* f          = new ASN1_Integer("integer a");
  ASN1_Null* g             = new ASN1_Null("null", "", true);
  ASN1_ObjectID* h         = new ASN1_ObjectID("OID");
  ASN1_OctetString* i      = new ASN1_OctetString("octet string");
  ASN1_Real* j             = new ASN1_Real("real");
  ASN1_UTCTime* k          = new ASN1_UTCTime("utc time");
  ASN1_UTF8String* l       = new ASN1_UTF8String("utf8 string");
  SequenceTest_sub* seq2            = new SequenceTest_sub("Seq2");
};

class SequenceOfTest : public ASN1_SequenceOf {
 public:
  SequenceOfTest(const std::string& name = "", const HexString& tag = "",
                 bool optional = false, bool explicitTag = false, bool extensibility = false, const ASN1_SequenceOf* defaultValue = nullptr)
    : ASN1_SequenceOf(name, tag, optional, explicitTag, extensibility, defaultValue) {}

  ASN1_Object* GetNewSequenceOfObject() {
    return new ASN1_Integer("int in seq of");
  }

  ASN1_Integer* AppendInt() { return static_cast<ASN1_Integer*>(AppendNewObject()); }
  ASN1_Integer* GetIntAt(int i) { return static_cast<ASN1_Integer*>(GetObjectAt(i)); }
};

void FillGrammarValues(SequenceTest* test) {
  test->a->SetSelectedChoice(3);
  //test->a->c->SetIntegerValue(500);

  test->b->SetBitStringValue("11110000111100001111");
  test->c->SetBooleanValue(true);
  test->d->SetEnumeratedValue(4);
  test->e->SetIA5StringValue("alexandre");
  test->f->SetIntegerValue(-6500);
  test->g->Ignore();
  test->h->SetObjectIDValue("2.12.15632.875.1.625");
  test->i->SetOctetStringValue("00112233445566778899aabbccddeeff");
  test->j->SetRealAsHexValue("5555");
  //test->k->SetUTCTimeValue(90, 01, 03, 17, 02, 00, C_ASN1_GrammarUTCTime::cPlus, 01, 00);
  test->k->SetUTCTimeValue("9001031702+0100");
  test->l->SetUTF8StringValue("szydlowski");
  test->seq2->a->SetSelectedChoice(2);
  test->seq2->f->SetIntegerValue(3000);
}
*/

/*
	* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
	* Redistribution and modifications are permitted subject to GPL-V3 license.
	*/
#pragma once
#include "ASN1_includes.h"

namespace Grammar
{

struct SequenceTestVars
{
  ASN1_Choice *a;
  ASN1_BitString *b;
  ASN1_Boolean *c;
  ASN1_Enumerated *d;
  ASN1_IA5String *e;
  ASN1_Integer *f;
  ASN1_Null *g;
  ASN1_ObjectID *h;
  ASN1_OctetString *i;
  ASN1_Real *j;
  ASN1_UTCTime *k;
  ASN1_UTF8String *l;
};

struct SequenceRealVars
{
  ASN1_Real *a, *b, *c, *d, *e, *f;
};

struct SetTestVars
{
  ASN1_Real *a;
  ASN1_Integer *b;
  ASN1_Boolean *c;
  ASN1_OctetString *d;
};

ASN1_Choice *MakeChoiceTest(const char *name, ByteArray tag)
{
  ASN1_Choice::callbackChoice callback{[](unsigned int idx, void *) -> ASN1_Object * {
                                         switch (idx)
                                         {
                                           case 0:
                                             return new ASN1_Integer("choice integer a", "0A");
                                           case 1:
                                             return new ASN1_Integer("choice integer b", "0B");
                                           case 2:
                                             return new ASN1_Integer("choice integer c", "0C");
                                           default:
                                             return nullptr;
                                         }
                                       },
                                       nullptr};

  return new ASN1_Choice(callback, 3, name, tag);
}

ASN1_Sequence *MakeSequenceTest(const char *name, ByteArray tag, SequenceTestVars &vars)
{
  vars.a = MakeChoiceTest("choice", "");
  vars.b = new ASN1_BitString("bitstring", "", false, true);
  vars.c = new ASN1_Boolean("boolean", "", false, true);
  vars.d = new ASN1_Enumerated("enum", "", false, true);
  vars.e = new ASN1_IA5String("ia5 string", "84", false, true);
  vars.f = new ASN1_Integer("integer a", "85", false, true);
  vars.g = new ASN1_Null("null", "", true);
  vars.h = new ASN1_ObjectID("OID", "86", false, true);
  vars.i = new ASN1_OctetString("octet string");
  vars.j = new ASN1_Real("real");
  vars.k = new ASN1_UTCTime("utc time");
  vars.l = new ASN1_UTF8String("utf8 string");

  ASN1_Object *arr[12] = {
      vars.a, vars.b, vars.c, vars.d, vars.e, vars.f, vars.g, vars.h, vars.i, vars.j, vars.k, vars.l};
  return new ASN1_Sequence(arr, 12, name, tag);
}

ASN1_SequenceOf *MakeSequenceOfTest(const char *name, ByteArray tag)
{
  ASN1_SequenceOf::callbackSequenceOf callback{
      [](void *) -> ASN1_Object * { return new ASN1_Integer("int in seq of"); }, nullptr};

  return new ASN1_SequenceOf(callback, name, tag);
}

ASN1_Sequence *MakeRealSequenceTest(const char *name, ByteArray tag, SequenceRealVars &vars)
{
  vars.a = new ASN1_Real("real1");
  vars.b = new ASN1_Real("real2");
  vars.c = new ASN1_Real("real3");
  vars.d = new ASN1_Real("real4");
  vars.e = new ASN1_Real("real5");
  vars.f = new ASN1_Real("real6");

  ASN1_Object *arr[6] = {vars.a, vars.b, vars.c, vars.d, vars.e, vars.f};
  return new ASN1_Sequence(arr, 6, name, tag);
}

ASN1_Set *MakeSetTest(const char *name, ByteArray tag, SetTestVars &vars)
{
  vars.a = new ASN1_Real("real1");
  vars.b = new ASN1_Integer("int2");
  vars.c = new ASN1_Boolean("bool3");
  vars.d = new ASN1_OctetString("os4");

  ASN1_Object *arr[4] = {vars.a, vars.b, vars.c, vars.d};
  return new ASN1_Set(arr, 4, name, tag);
}

} // namespace Grammar

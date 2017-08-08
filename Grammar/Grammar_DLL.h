/*
	* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
	* Redistribution and modifications are permitted subject to GPL-V3 license.
	*/
#pragma once
#include "ASN1_includes.h"
#include "DLL_Interface.h"

namespace Grammar {

  ASN1_DLL::DLL_ASN1_Sequence* DLL_MakeGrammar() {
    using namespace ASN1_DLL;
    Hex tag("");

    DLL_callbackChoice choiceStruct{
      [](int idx, void*) -> DLL_ASN1_Object* {
        if (idx == 0) return (DLL_ASN1_Object*)ASN1_BitString_New("BitString", Hex("").p(), false, false, nullptr);
        if (idx == 1) return (DLL_ASN1_Object*)ASN1_Integer_New("Integer", Hex("").p(), false, false, nullptr);
        else return nullptr;
      }, nullptr };

    DLL_ASN1_BitString* c = ASN1_BitString_New("BitString", tag.p(), false, false, nullptr);
    DLL_ASN1_Choice* d = ASN1_Choice_New(choiceStruct, 2, "choice", tag.p(), false, false, nullptr);
    DLL_ASN1_Enumerated* e = ASN1_Enumerated_New("Enumerated", tag.p(), false, false, nullptr);
    DLL_ASN1_IA5String* f = ASN1_IA5String_New("IA5String", tag.p(), false, false, nullptr);
    DLL_ASN1_Integer* g = ASN1_Integer_New("Integer", tag.p(), false, false, nullptr);
    DLL_ASN1_Null* h = ASN1_Null_New("Null", tag.p(), false, false, nullptr);
    DLL_ASN1_ObjectID* i = ASN1_ObjectID_New("ObjectID", tag.p(), false, false, nullptr);
    DLL_ASN1_OctetString* j = ASN1_OctetString_New("OctetString", tag.p(), false, false, nullptr);
    DLL_ASN1_Real* k = ASN1_Real_New("Real", tag.p(), false, false, nullptr);
    //DLL_ASN1_SequenceOf* l = ASN1_SequenceOf_New("SequenceOf", tag.p(), false, false, nullptr);
    DLL_ASN1_UTCTime* m = ASN1_UTCTime_New("UTCTime", tag.p(), false, false, nullptr);
    DLL_ASN1_UTF8String* n = ASN1_UTF8String_New("UTF8String", tag.p(), false, false, nullptr);

    DLL_ASN1_Object* seqObjects[] = { (DLL_ASN1_Object*)c, (DLL_ASN1_Object*)d, (DLL_ASN1_Object*)e, (DLL_ASN1_Object*)f, (DLL_ASN1_Object*)g, (DLL_ASN1_Object*)h, (DLL_ASN1_Object*)i,
                                      (DLL_ASN1_Object*)j, (DLL_ASN1_Object*)k, (DLL_ASN1_Object*)m, (DLL_ASN1_Object*)n
                                    };
    DLL_ASN1_Sequence* o = NewObj(ASN1_Sequence_New(seqObjects, 11, "Sequence", tag.p(), false, false, nullptr, false));
    //DLL_ASN1_Set* p = NewObj(ASN1_Set_New("Set", tag.p(), false, false, nullptr));
    return o;
  }
}

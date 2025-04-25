/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#pragma once
#include "../ASN1_Object.h"
#include "../Values/ASN1_Value_Nodes_Interface.h"

/*
Definition for basic ASN1 nodes. These classes are exported in the DLL and will be the bricks to build a grammar.
You instantiate these objects with their ASN1 properties coming from the grammar (such like tag, optionality...),
and they can't be changed afterwards. To modify the grammar, you need to recreate it.

The complex types are defined in separated classes since they need different functions to access their properties or functionalities.

MEMORY:
An instantiated object must be deleted after use if it is not part of a structure, like any object instantiated with "new"
A sequence/sequence of/set/choice will clean its objects at deletion time.
It means that if you have structure of several sequences, only the root node needs to be deleted.
An object also deletes its defaultValue if it has one.
*/

namespace Value
{
template <Utils::eNodeType T> class ASN1_ValueDer;
}

template <Utils::eNodeType T>
class ASN1_ObjectDer : public ASN1_Object
{
protected:
  using U = Value::UnderlyingType<T>::T;
  using V = Value::ASN1_ValueDer<T>;

public:
  ASN1_ObjectDer(const char *objectName = "",
                 const ByteArray &tag = "",
                 bool optional = false,
                 bool explicitTag = false,
                 const ASN1_ObjectDer<T> *defaultValue = nullptr);

  U GetValue() const;
  void SetValue(const U &val);
  void SetValue(const U &val, std::string &error);

  static void ToHex(const U &input, ByteArray &output, std::string &error);
  static void FromHex(const ByteArray &input, U &output, std::string &error);
};

using ASN1_BitString = ASN1_ObjectDer<Utils::cBitString>;
using ASN1_Boolean = ASN1_ObjectDer<Utils::cBoolean>;
using ASN1_Enumerated = ASN1_ObjectDer<Utils::cEnumerated>;
using ASN1_IA5String = ASN1_ObjectDer<Utils::cIA5String>;
using ASN1_Integer = ASN1_ObjectDer<Utils::cInteger>;
using ASN1_Null = ASN1_ObjectDer<Utils::cNull>;
using ASN1_ObjectID = ASN1_ObjectDer<Utils::cObjectID>;
using ASN1_OctetString = ASN1_ObjectDer<Utils::cOctetString>;
using ASN1_Real = ASN1_ObjectDer<Utils::cReal>;
using ASN1_UTCTime = ASN1_ObjectDer<Utils::cUTCTime>;
using ASN1_UTF8String = ASN1_ObjectDer<Utils::cUTF8String>;
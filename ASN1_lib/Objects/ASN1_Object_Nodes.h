/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#pragma once
#include "../ASN1_Object.h"

/*
Definition for basic ASN1 nodes. These classes are exported in the DLL and will be the bricks to build a grammar.
You instanciate these objects with their ASN1 propertiescoming from the grammar (such like tag, optionality...),
and they can't be changed afterwards. To modify the grammar, you need to recreate it.

The macros in this file avoid having duplicated code for each node type.
The complex types are defined in separated classes since they need different functions to acces their properties or functionalities.

At the end of this file, the macro OBJECT_CLASS_DECL generates the object class based on its name and the type of data it contains.

--------------------------- EXAMPLE ----------------------------
A class is generated with a constructor, a getter, a setter with no check, a setter with check, and two conversion functions.
For example, Boolean node, with type bool will look like:

 class ASN1_Boolean : public ASN1_Object  {
   public:
   ASN1_Boolean(const char* objectName = "", const ByteArray& tag = "", bool optional = false, bool explicitTag = false, const ASN1_Boolean *defaultBoolean = nullptr);
   virtual ~ASN1_Boolean();

   SetBooleanValue(const bool& val);
   SetBooleanValue(const bool& val, std::string& error);

   bool GetBooleanValue() const;

   static void BoooleanToHex(const bool &input, ByteArray &output, std::string &error);
   static void HexToBoolean(const ByteArray &input, bool &output, std::string &error);
 }

 MEMORY:
 An instanciated object must be deleted after use if it is not part of a structure, like any object instaciated with "new"
 A sequence/sequence of/set/choice will clean its objects at deletion time.
 It means that if you have structure of several sequences, only the root node needs to be deleted.
 An object also deletes its defaultValue if it has one.

*/

#ifndef OBJECT_CONSTRUCTOR_DECL
#define OBJECT_CONSTRUCTOR_DECL(name)      \
  ASN1_##name(const char *objectName = "", \
              const ByteArray &tag = "",   \
              bool optional = false,       \
              bool explicitTag = false,    \
              const ASN1_##name *default##name = nullptr);
#endif

#ifndef OBJECT_DESTRUCTOR_DECL
#define OBJECT_DESTRUCTOR_DECL(name) virtual ~ASN1_##name();
#endif

#ifndef OBJECT_SET_VALUE_FUNCTION_DECL
#define OBJECT_SET_VALUE_FUNCTION_DECL(name, type) void Set##name##Value(const type &val);
#endif

#ifndef OBJECT_SET_VALUE_CHECK_FUNCTION_DECL
#define OBJECT_SET_VALUE_CHECK_FUNCTION_DECL(name, type) void Set##name##Value(const type &val, std::string &error);
#endif

#ifndef OBJECT_GET_VALUE_FUNCTION_DECL
#define OBJECT_GET_VALUE_FUNCTION_DECL(name, type) type Get##name##Value() const;
#endif

#ifndef STATIC_CONVERT_TYPE_TO_HEX_FUNCTION_DECL
#define STATIC_CONVERT_TYPE_TO_HEX_FUNCTION_DECL(name, type) \
  static void name##ToHex(const type &input, ByteArray &output, std::string &error);
#endif

#ifndef STATIC_CONVERT_HEX_TO_TYPE_FUNCTION_DECL
#define STATIC_CONVERT_HEX_TO_TYPE_FUNCTION_DECL(name, type) \
  static void HexTo##name(const ByteArray &input, type &output, std::string &error);
#endif

#ifndef OBJECT_CLASS_DECL
#define OBJECT_CLASS_DECL(name, type)                    \
  class MODULE_API ASN1_##name : public ASN1_Object {    \
   public:                                               \
    OBJECT_CONSTRUCTOR_DECL(name)                        \
    OBJECT_DESTRUCTOR_DECL(name)                         \
                                                         \
    OBJECT_SET_VALUE_FUNCTION_DECL(name, type)           \
    OBJECT_SET_VALUE_CHECK_FUNCTION_DECL(name, type)     \
    OBJECT_GET_VALUE_FUNCTION_DECL(name, type)           \
                                                         \
    STATIC_CONVERT_TYPE_TO_HEX_FUNCTION_DECL(name, type) \
    STATIC_CONVERT_HEX_TO_TYPE_FUNCTION_DECL(name, type) \
  };
#endif

OBJECT_CLASS_DECL(BitString, std::string)
OBJECT_CLASS_DECL(IA5String, std::string)
OBJECT_CLASS_DECL(ObjectID, std::string)
OBJECT_CLASS_DECL(UTCTime, std::string)
OBJECT_CLASS_DECL(UTF8String, std::string)
OBJECT_CLASS_DECL(Boolean, bool)
OBJECT_CLASS_DECL(Null, bool)
OBJECT_CLASS_DECL(Enumerated, int)
OBJECT_CLASS_DECL(Integer, int)
OBJECT_CLASS_DECL(OctetString, ByteArray)
OBJECT_CLASS_DECL(Real, double)

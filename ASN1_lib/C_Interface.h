/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "ASN1_includes.h"

/*
The C interface published C like functions on the DLL.
It allows you to link it dynamically in your program.

The interface is adapted since the object concept does not exist in C but remains almost the same.

Example with Boolean type:
To construct an object, call ASN1_Boolean_New(). It returns a pointer of type ASN1_Boolean.
This pointer needs to be passed as first argument to each function call related to this object,
like the get method, generated as follow: void ASN1_Boolean_GetBooleanValue(const ASN1_Boolean * pObj, bool * out);

*/

#if defined DLLCOMPIL
#define DLLSPEC __declspec(dllexport)
#else
#define DLLSPEC __declspec(dllimport)
#endif

#ifndef NODE_CONSTRUCTOR_FUNCTION
#define NODE_CONSTRUCTOR_FUNCTION(name) DLLSPEC ASN1_##name * ASN1_##name##_New \
(const char * objectName, const ByteArray * tag, bool optional, bool explicitTag, const ASN1_##name * defaultValue);
#endif

#ifndef NODE_SET_FUNCTION
#define NODE_SET_FUNCTION(name, type) DLLSPEC void ASN1_##name##_Set##name##Value \
(ASN1_##name * obj, const type val);
#endif

#ifndef NODE_SET_CHECK_FUNCTION
#define NODE_SET_CHECK_FUNCTION(name, type) DLLSPEC void ASN1_##name##_Set##name##ValueCheck \
(ASN1_##name * obj, const type val, char * errorBuffer, unsigned int errorBufferSize);
#endif

#ifndef NODE_GET_FUNCTION
#define NODE_GET_FUNCTION(name, type) DLLSPEC void ASN1_##name##_Get##name##Value \
(const ASN1_##name * obj, type * out);
#endif

#ifndef NODE_GET_WITH_BUFFER_FUNCTION
#define NODE_GET_WITH_BUFFER_FUNCTION(name) DLLSPEC void ASN1_##name##_Get##name##Value \
(const ASN1_##name * obj, char * out, unsigned int bufferSize);
#endif

#ifndef NODE_CONVERT_HEX_TO_TYPE
#define NODE_CONVERT_HEX_TO_TYPE(name, type) DLLSPEC void ASN1_##name##_HexTo##name \
(const ByteArray * input, type * output, char * errorBuffer, unsigned int errorBufferSize);
#endif

#ifndef NODE_CONVERT_HEX_TO_TYPE_WITH_BUFFER
#define NODE_CONVERT_HEX_TO_TYPE_WITH_BUFFER(name) DLLSPEC void ASN1_##name##_HexTo##name \
(const ByteArray * input, char * output, unsigned int outputBufferSize, char * errorBuffer, unsigned int errorBufferSize);
#endif

#ifndef NODE_CONVERT_TYPE_TO_HEX
#define NODE_CONVERT_TYPE_TO_HEX(name, type) DLLSPEC void ASN1_##name##_##name##ToHex \
(const type input, ByteArray * output, char * errorBuffer, unsigned int errorBufferSize);
#endif

#ifndef OBJECT_INTERFACE_TYPE
#define OBJECT_INTERFACE_TYPE(name, type) \
  NODE_CONSTRUCTOR_FUNCTION(name) \
  NODE_GET_FUNCTION(name, type) \
  NODE_SET_FUNCTION(name, type) \
  NODE_SET_CHECK_FUNCTION(name, type) \
  NODE_CONVERT_HEX_TO_TYPE(name, type) \
  NODE_CONVERT_TYPE_TO_HEX(name, type)
#endif

#ifndef OBJECT_INTERFACE_BUFFER
#define OBJECT_INTERFACE_BUFFER(name) \
  NODE_CONSTRUCTOR_FUNCTION(name) \
  NODE_GET_WITH_BUFFER_FUNCTION(name) \
  NODE_SET_FUNCTION(name, char*) \
  NODE_SET_CHECK_FUNCTION(name, char*) \
  NODE_CONVERT_HEX_TO_TYPE_WITH_BUFFER(name) \
  NODE_CONVERT_TYPE_TO_HEX(name, char*)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------ ByteArray ------------
DLLSPEC ByteArray* ByteArray_New(const char* str);
DLLSPEC ByteArray* ByteArray_NewFromByteArray(const ByteArray* hex);
DLLSPEC void ByteArray_Delete(ByteArray* hex);

DLLSPEC unsigned int ByteArray_Size(const ByteArray* hex);
DLLSPEC bool ByteArray_Equals(const ByteArray* hex, const ByteArray* second);

DLLSPEC const char* ByteArray_GetString(const ByteArray* hex);
DLLSPEC bool ByteArray_GetByteAtRank(const ByteArray* hex, unsigned int byteRank, ByteArray* out);
DLLSPEC bool ByteArray_GetBytesAtRank(const ByteArray* hex, unsigned int firstByteRank, unsigned int nbOfBytes, ByteArray* out);

DLLSPEC void ByteArray_Clear(ByteArray* hex);
DLLSPEC void ByteArray_Append(ByteArray* hex, const ByteArray* bufferToAppend);
DLLSPEC bool ByteArray_InsertAt(ByteArray* hex, const ByteArray* bufferToAppend, unsigned int pos);

// ------------ UTILS ------------
DLLSPEC void Utils_IntAsHex(int i, ByteArray* out);
DLLSPEC unsigned int Utils_HexAsInt(const ByteArray* hexStr);

DLLSPEC void Utils_BinaryAsHex(const char* binary, ByteArray* out);
DLLSPEC void Utils_HexAsBinary(const ByteArray* byteArray, char* out, unsigned int bufferSize);
DLLSPEC void Utils_HexAsBinary8Padded(const ByteArray* byteArray, char* out, unsigned int bufferSize);

DLLSPEC void Utils_IntAsBinary(unsigned int i, char* out, unsigned int bufferSize);
DLLSPEC void Utils_IntAsBinary8Padded(unsigned int i, char* out, unsigned int bufferSize);
DLLSPEC unsigned int Utils_BinaryAsInt(const char* binaryStr);

DLLSPEC bool Utils_IsHex(const char* str);
DLLSPEC bool Utils_IsBinary(const char* str);

DLLSPEC bool Utils_IsComplexType(int type);

DLLSPEC bool Utils_GetTagFromBuffer(const ByteArray* fromBuffer, unsigned int pos, ByteArray* tag);
DLLSPEC bool Utils_GetLengthFromBuffer(const ByteArray* fromBuffer, unsigned int pos, unsigned int* L);

DLLSPEC void Utils_MakeLength(unsigned int sizeAsInt, ByteArray* out);
//enum TagClass { cTagClassUniversal, cTagClassApplication, cTagClassContextSpecific, cTagClassPrivate };
//enum TagForm { cTagFormPrimitive, cTagFormConstructed };
DLLSPEC void Utils_MakeTag(unsigned int tagClass, unsigned int tagForm, const ByteArray* label, ByteArray* out);
DLLSPEC bool Utils_DecomposeTag(const ByteArray* tag, unsigned int* tagClass, unsigned int* tagForm, ByteArray* label);


DLLSPEC void Utils_StringToHex(const char* str, ByteArray* out);
DLLSPEC void Utils_HexToString(const ByteArray* hex, char* out, unsigned int bufferSize);

//enum Zone { cGMT, cPlus, cMinus };
DLLSPEC void Utils_UTCTimeToValues(const char* input, int* year_YY, int* month_MM, int* day_DD, int* hours_HH, int* minutes_MM, int* seconds_SS,
                                   unsigned int* zone, int* zoneHours_HH, int* zoneMinutes_MM, char* error, unsigned int errorBufferSize);
DLLSPEC void Utils_ValuesToUTCTime(int year_YY, int month_MM, int day_DD, int hours_HH, int minutes_MM, int seconds_SS,
                                   unsigned int zone, int zoneHours_HH, int zoneMinutes_MM,
                                   char* out, unsigned int bufferSize, char* error, unsigned int errorBufferSize);

DLLSPEC bool Utils_IsValidUTCTime(const char* input);
DLLSPEC bool Utils_IsValidObjectID(const char* input);
DLLSPEC bool Utils_IsValidIA5String(const char* input);
DLLSPEC bool Utils_IsValidUTF8String(const char* input);

// ------------ ASN1_OBJECT ------------
DLLSPEC const ASN1_Object* ASN1_Object_GetMyOwner(const ASN1_Object* obj);
DLLSPEC const ASN1_Object* ASN1_Object_GetDefaultValue(const ASN1_Object* obj);
DLLSPEC void ASN1_Object_GetDefaultTag(const ASN1_Object* obj, ByteArray* out);
DLLSPEC void ASN1_Object_GetTag(const ASN1_Object* obj, ByteArray* out);
DLLSPEC void ASN1_Object_GetName(const ASN1_Object* obj, char* out, unsigned int bufferSize);
DLLSPEC void ASN1_Object_GetDescription(const ASN1_Object* obj, char* out, unsigned int bufferSize);
DLLSPEC void ASN1_Object_StringExtract(const ASN1_Object* obj, char* out, unsigned int bufferSize);
DLLSPEC void ASN1_Object_StringExtractForResearch(const ASN1_Object* obj, char* out, unsigned int bufferSize);

//enum eNodeType { cBitString, cBoolean, cChoice, cEnumerated, cIA5String, cInteger, cNull, cObjectID,
//  cOctetString, cReal, cSequence, cSequenceOf, cSet, cUTCTime, cUTF8String };

DLLSPEC unsigned int ASN1_Object_GetType(const ASN1_Object* obj);
DLLSPEC bool ASN1_Object_IsMandatory(const ASN1_Object* obj);
DLLSPEC bool ASN1_Object_IsIgnored(const ASN1_Object* obj);
DLLSPEC bool ASN1_Object_IsExplicit(const ASN1_Object* obj);
DLLSPEC void ASN1_Object_GetHexBuffer(const ASN1_Object* obj, ByteArray* out);
DLLSPEC unsigned int ASN1_Object_GetLastSize(const ASN1_Object* obj);

DLLSPEC void ASN1_Object_ClearDynamicData(ASN1_Object* obj);
DLLSPEC void ASN1_Object_SetDescription(ASN1_Object* obj, const char* desc);
DLLSPEC void ASN1_Object_Ignore(ASN1_Object* obj, bool ignore);

DLLSPEC void ASN1_Object_WriteIntoBuffer(const ASN1_Object* obj, ByteArray* buffer);
DLLSPEC bool ASN1_Object_ReadFromBuffer(ASN1_Object* obj, const ByteArray* buffer,
                                        char* errorBuffer, unsigned int errorBufferSize);
DLLSPEC bool ASN1_Object_Compare(const ASN1_Object* obj, const ASN1_Object* secondTree,
                                 unsigned int* nbDiffs, char* errorBuffer, unsigned int errorBufferSize);

DLLSPEC void ASN1_Object_Delete(ASN1_Object* obj);

// ------------ ASN1_NODES ------------
OBJECT_INTERFACE_BUFFER(BitString)
OBJECT_INTERFACE_BUFFER(IA5String)
OBJECT_INTERFACE_BUFFER(UTCTime)
OBJECT_INTERFACE_BUFFER(UTF8String)
OBJECT_INTERFACE_TYPE(Boolean, bool)
OBJECT_INTERFACE_TYPE(Null, bool)
OBJECT_INTERFACE_TYPE(Enumerated, int)
OBJECT_INTERFACE_TYPE(Integer, int)
OBJECT_INTERFACE_TYPE(OctetString, ByteArray)
OBJECT_INTERFACE_TYPE(Real, double)
OBJECT_INTERFACE_BUFFER(ObjectID)

// ------------ ASN1_CHOICE ------------
//struct callbackChoice {
//  typedef ASN1_Object* (*callbackFunctionType)(unsigned int i, void* context);
//  callbackFunctionType f;
//  void* context;
//};
DLLSPEC ASN1_Choice* ASN1_Choice_New(ASN1_Choice::callbackChoice choiceFromIdx, unsigned int maxChoiceIdx, const char* name, const ByteArray* tag,
                                     bool optional, bool explicitTag, const ASN1_Choice* defaultValue);
DLLSPEC unsigned int ASN1_Choice_AvailableChoices(const ASN1_Choice* obj);
DLLSPEC const ASN1_Object* ASN1_Choice_GetChoiceFromIndex(const ASN1_Choice* obj, int pos);
DLLSPEC void ASN1_Choice_MakeDummyChoiceList(const ASN1_Choice* obj);
DLLSPEC void ASN1_Choice_DeleteDummyChoiceList(const ASN1_Choice* obj);
DLLSPEC ASN1_Object* ASN1_Choice_SetSelectedChoice(ASN1_Choice* obj, int idx);
DLLSPEC ASN1_Object* ASN1_Choice_GetSelectedChoice(const ASN1_Choice* obj);
DLLSPEC unsigned int ASN1_Choice_GetSelectedChoiceIndex(const ASN1_Choice* obj);

// ------------ ASN1_SEQUENCE ------------
DLLSPEC ASN1_Sequence* ASN1_Sequence_New(ASN1_Object* valuesArray[], unsigned int numberOfValues, const char* name, const ByteArray* tag,
    bool optional, bool explicitTag, const ASN1_Sequence* defaultValue, bool extensibility);
DLLSPEC ASN1_Object* ASN1_Sequence_GetObjectAt(const ASN1_Sequence* obj, unsigned int pos);
DLLSPEC unsigned int ASN1_Sequence_GetSize(const ASN1_Sequence* obj);
DLLSPEC ASN1_Object* ASN1_Sequence_GetExtensibilityObjectAt(const ASN1_Sequence* obj, unsigned int pos);
DLLSPEC unsigned int ASN1_Sequence_GetExtensibilitySize(const ASN1_Sequence* obj);
DLLSPEC bool ASN1_Sequence_IsExtensible(const ASN1_Sequence* obj);

// ------------ ASN1_SEQUENCEOF ------------
//struct callbackSequenceOf {
//  typedef ASN1_Object* (*callbackFunctionType)(void* context);
//  callbackFunctionType f;
//  void* context;
//};
DLLSPEC ASN1_SequenceOf* ASN1_SequenceOf_New(ASN1_SequenceOf::callbackSequenceOf newSeqOfObject, const char* name, const ByteArray* tag,
    bool optional, bool explicitTag, const ASN1_SequenceOf* defaultValue);
DLLSPEC ASN1_Object* ASN1_SequenceOf_GetObjectAt(const ASN1_SequenceOf* obj, int pos);
DLLSPEC unsigned int ASN1_SequenceOf_GetSize(const ASN1_SequenceOf* obj);
DLLSPEC ASN1_Object* ASN1_SequenceOf_AppendNewObject(ASN1_SequenceOf* obj);
DLLSPEC void ASN1_SequenceOf_DeleteObjectAt(ASN1_SequenceOf* obj, int pos);
DLLSPEC void ASN1_SequenceOf_MoveUpObject(ASN1_SequenceOf* obj, int pos);
DLLSPEC void ASN1_SequenceOf_MoveDownObject(ASN1_SequenceOf* obj, int pos);
DLLSPEC ASN1_Object* ASN1_SequenceOf_GetDummyNewObject(const ASN1_SequenceOf* obj);

// ------------ ASN1_SET ------------
DLLSPEC ASN1_Set* ASN1_Set_New(ASN1_Object* valuesArray[], unsigned int numberOfValues, const char* name, const ByteArray* tag,
                               bool optional, bool explicitTag, const ASN1_Set* defaultValue, bool extensibility);
DLLSPEC ASN1_Object* ASN1_Set_GetObjectAt(const ASN1_Set* obj, unsigned int pos);
DLLSPEC unsigned int ASN1_Set_GetSize(const ASN1_Set* obj);
DLLSPEC ASN1_Object* ASN1_Set_GetExtensibilityObjectAt(const ASN1_Set* obj, unsigned int pos);
DLLSPEC unsigned int ASN1_Set_GetExtensibilitySize(const ASN1_Set* obj);
DLLSPEC bool ASN1_Set_IsExtensible(const ASN1_Set* obj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

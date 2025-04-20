/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

namespace ASN1_DLL
{

struct DLL_ByteArray;
struct DLL_ASN1_Object;
struct DLL_ASN1_Choice;
struct DLL_ASN1_Sequence;
struct DLL_ASN1_SequenceOf;
struct DLL_ASN1_Set;

// ------ HEX STRING -----------------------------------------------------------
typedef DLL_ByteArray *(*tByteArray_New)(const char *str);
typedef DLL_ByteArray *(*tByteArray_NewFromByteArray)(const DLL_ByteArray *hex);
typedef void (*tByteArray_Delete)(DLL_ByteArray *hex);
typedef unsigned int (*tByteArray_Size)(const DLL_ByteArray *hex);
typedef bool (*tByteArray_Equals)(const DLL_ByteArray *hex, const DLL_ByteArray *second);
typedef const char *(*tByteArray_GetString)(const DLL_ByteArray *hex);
typedef bool (*tByteArray_GetByteAtRank)(const DLL_ByteArray *hex, unsigned int byteRank, DLL_ByteArray *out);
typedef bool (*tByteArray_GetBytesAtRank)(const DLL_ByteArray *hex,
                                          unsigned int firstByteRank,
                                          unsigned int nbOfBytes,
                                          DLL_ByteArray *out);
typedef void (*tByteArray_Clear)(DLL_ByteArray *hex);
typedef bool (*tByteArray_Append)(DLL_ByteArray *hex, const DLL_ByteArray *bufferToAppend);
typedef bool (*tByteArray_InsertAt)(DLL_ByteArray *hex, const DLL_ByteArray *bufferToAppend, unsigned int pos);

tByteArray_New ByteArray_New;
tByteArray_NewFromByteArray ByteArray_NewFromByteArray;
tByteArray_Delete ByteArray_Delete;
tByteArray_Size ByteArray_Size;
tByteArray_Equals ByteArray_Equals;
tByteArray_GetString ByteArray_GetString;
tByteArray_GetByteAtRank ByteArray_GetByteAtRank;
tByteArray_GetBytesAtRank ByteArray_GetBytesAtRank;
tByteArray_Clear ByteArray_Clear;
tByteArray_Append ByteArray_Append;
tByteArray_InsertAt ByteArray_InsertAt;
// -----------------------------------------------------------------------------

// ------ UTILS -----------------------------------------------------------
typedef void (*tUtils_IntAsHex)(int i, DLL_ByteArray *out);
typedef unsigned int (*tUtils_HexAsInt)(const DLL_ByteArray *hexStr);
typedef void (*tUtils_BinaryAsHex)(const char *binary, DLL_ByteArray *out);
typedef void (*tUtils_HexAsBinary)(const DLL_ByteArray *byteArray, char *out, unsigned int bufferSize);
typedef void (*tUtils_HexAsBinary8Padded)(const DLL_ByteArray *byteArray, char *out, unsigned int bufferSize);
typedef void (*tUtils_IntAsBinary)(unsigned int i, char *out, unsigned int bufferSize);
typedef void (*tUtils_IntAsBinary8Padded)(unsigned int i, char *out, unsigned int bufferSize);
typedef unsigned int (*tUtils_BinaryAsInt)(const char *binaryStr);
typedef bool (*tUtils_IsHex)(const char *str);
typedef bool (*tUtils_IsBinary)(const char *str);
typedef bool (*tUtils_IsComplexType)(int type);
typedef bool (*tUtils_GetTagFromBuffer)(const DLL_ByteArray *fromBuffer, unsigned int pos, DLL_ByteArray *tag);
typedef bool (*tUtils_GetLengthFromBuffer)(const DLL_ByteArray *fromBuffer, unsigned int pos, unsigned int *L);
typedef void (*tUtils_MakeLength)(unsigned int sizeAsInt, DLL_ByteArray *out);
typedef void (*tUtils_MakeTag)(unsigned int tagClass,
                               unsigned int tagForm,
                               const DLL_ByteArray *label,
                               DLL_ByteArray *out);
typedef bool (*tUtils_DecomposeTag)(const DLL_ByteArray *tag,
                                    unsigned int *tagClass,
                                    unsigned int *tagForm,
                                    DLL_ByteArray *label);
typedef void (*tUtils_StringToHex)(const char *str, DLL_ByteArray *out);
typedef void (*tUtils_HexToString)(const DLL_ByteArray *asciiHex, char *out, unsigned int bufferSize);
typedef void (*tUtils_UTCTimeToValues)(const char *input,
                                       int *aYear_YY,
                                       int *aMonth_MM,
                                       int *aDay_DD,
                                       int *aHours_HH,
                                       int *aMinutes_MM,
                                       int *aSeconds_SS,
                                       unsigned int *aZone,
                                       int *aZoneHours_HH,
                                       int *aZoneMinutes_MM,
                                       char *errorBuffer,
                                       unsigned int errorBufferSize);
typedef void (*tUtils_ValuesToUTCTime)(int aYear_YY,
                                       int aMonth_MM,
                                       int aDay_DD,
                                       int aHours_HH,
                                       int aMinutes_MM,
                                       int aSeconds_SS,
                                       unsigned int aZone,
                                       int aZoneHours_HH,
                                       int aZoneMinutes_MM,
                                       char *output,
                                       unsigned int outputBufferSize,
                                       char *errorBuffer,
                                       unsigned int errorBufferSize);
typedef bool (*tUtils_IsValidUTCTime)(const char *input);
typedef bool (*tUtils_IsValidObjectID)(const char *input);
typedef bool (*tUtils_IsValidIA5String)(const char *input);
typedef bool (*tUtils_IsValidUTF8String)(const char *input);

tUtils_IntAsHex Utils_IntAsHex;
tUtils_HexAsInt Utils_HexAsInt;
tUtils_BinaryAsHex Utils_BinaryAsHex;
tUtils_HexAsBinary Utils_HexAsBinary;
tUtils_HexAsBinary8Padded Utils_HexAsBinary8Padded;
tUtils_IntAsBinary Utils_IntAsBinary;
tUtils_IntAsBinary8Padded Utils_IntAsBinary8Padded;
tUtils_BinaryAsInt Utils_BinaryAsInt;
tUtils_IsHex Utils_IsHex;
tUtils_IsBinary Utils_IsBinary;
tUtils_IsComplexType Utils_IsComplexType;
tUtils_StringToHex Utils_StringToHex;
tUtils_HexToString Utils_HexToString;
tUtils_GetTagFromBuffer Utils_GetTagFromBuffer;
tUtils_GetLengthFromBuffer Utils_GetLengthFromBuffer;
tUtils_MakeLength Utils_MakeLength;
tUtils_MakeTag Utils_MakeTag;
tUtils_DecomposeTag Utils_DecomposeTag;
tUtils_UTCTimeToValues Utils_UTCTimeToValues;
tUtils_ValuesToUTCTime Utils_ValuesToUTCTime;
tUtils_IsValidUTCTime Utils_IsValidUTCTime;
tUtils_IsValidObjectID Utils_IsValidObjectID;
tUtils_IsValidIA5String Utils_IsValidIA5String;
tUtils_IsValidUTF8String Utils_IsValidUTF8String;
// -----------------------------------------------------------------------------

// ------ ASN1_OBJECT -----------------------------------------------------------
typedef const DLL_ASN1_Object *(*tASN1_Object_GetMyOwner)(const DLL_ASN1_Object *obj);
typedef const DLL_ASN1_Object *(*tASN1_Object_GetDefaultValue)(const DLL_ASN1_Object *obj);
typedef void (*tASN1_Object_GetDefaultTag)(const DLL_ASN1_Object *obj, DLL_ByteArray *out);
typedef void (*tASN1_Object_GetTag)(const DLL_ASN1_Object *obj, DLL_ByteArray *out);
typedef void (*tASN1_Object_GetName)(const DLL_ASN1_Object *obj, char *out, unsigned int bufferSize);
typedef void (*tASN1_Object_GetDescription)(const DLL_ASN1_Object *obj, char *out, unsigned int bufferSize);
typedef void (*tASN1_Object_StringExtract)(const DLL_ASN1_Object *obj, char *out, unsigned int bufferSize);
typedef void (*tASN1_Object_StringExtractForResearch)(const DLL_ASN1_Object *obj, char *out, unsigned int bufferSize);
typedef unsigned int (*tASN1_Object_GetType)(const DLL_ASN1_Object *obj);
typedef bool (*tASN1_Object_IsMandatory)(const DLL_ASN1_Object *obj);
typedef bool (*tASN1_Object_IsIgnored)(const DLL_ASN1_Object *obj);
typedef bool (*tASN1_Object_IsExplicit)(const DLL_ASN1_Object *obj);
typedef void (*tASN1_Object_GetHexBuffer)(const DLL_ASN1_Object *obj, DLL_ByteArray *out);
typedef unsigned int (*tASN1_Object_GetLastSize)(const DLL_ASN1_Object *obj);
typedef void (*tASN1_Object_ClearDynamicData)(const DLL_ASN1_Object *obj);
typedef void (*tASN1_Object_SetDescription)(const DLL_ASN1_Object *obj, const char *desc);
typedef void (*tASN1_Object_Ignore)(const DLL_ASN1_Object *obj, bool ignore);
typedef void (*tASN1_Object_WriteIntoBuffer)(const DLL_ASN1_Object *obj, DLL_ByteArray *buffer);
typedef bool (*tASN1_Object_ReadFromBuffer)(const DLL_ASN1_Object *obj,
                                            const DLL_ByteArray *buffer,
                                            char *error,
                                            unsigned int errorBufferSize);
typedef bool (*tASN1_Object_Compare)(const DLL_ASN1_Object *obj,
                                     const DLL_ASN1_Object *secondTree,
                                     unsigned int *nbDiffs,
                                     char *errorReport,
                                     unsigned int errorBufferSize);
typedef void (*tASN1_Object_Delete)(DLL_ASN1_Object *obj);

tASN1_Object_GetMyOwner ASN1_Object_GetMyOwner;
tASN1_Object_GetDefaultValue ASN1_Object_GetDefaultValue;
tASN1_Object_GetDefaultTag ASN1_Object_GetDefaultTag;
tASN1_Object_GetTag ASN1_Object_GetTag;
tASN1_Object_GetDescription ASN1_Object_GetDescription;
tASN1_Object_StringExtract ASN1_Object_StringExtract;
tASN1_Object_StringExtractForResearch ASN1_Object_StringExtractForResearch;
tASN1_Object_GetType ASN1_Object_GetType;
tASN1_Object_IsMandatory ASN1_Object_IsMandatory;
tASN1_Object_IsIgnored ASN1_Object_IsIgnored;
tASN1_Object_IsExplicit ASN1_Object_IsExplicit;
tASN1_Object_GetHexBuffer ASN1_Object_GetHexBuffer;
tASN1_Object_GetLastSize ASN1_Object_GetLastSize;
tASN1_Object_ClearDynamicData ASN1_Object_ClearDynamicData;
tASN1_Object_SetDescription ASN1_Object_SetDescription;
tASN1_Object_Ignore ASN1_Object_Ignore;
tASN1_Object_WriteIntoBuffer ASN1_Object_WriteIntoBuffer;
tASN1_Object_ReadFromBuffer ASN1_Object_ReadFromBuffer;
tASN1_Object_Compare ASN1_Object_Compare;
tASN1_Object_Delete ASN1_Object_Delete;
// -----------------------------------------------------------------------------

// needs HINSTANCE hDLL to be defined where this MACRO is called
#ifndef GET_FUNC_POINTER
#define GET_FUNC_POINTER(name) name = (t##name)GetProcAddress(hDLL, #name);
#endif

#ifndef TYPEDEF_WITH_BUFFER
#define TYPEDEF_WITH_BUFFER(name)                                                                                      \
  typedef void (*tASN1_##name##_Get##name##Value)(                                                                     \
      const DLL_ASN1_##name *obj, char *output, unsigned int outputBufferSize);                                        \
  typedef void (*tASN1_##name##_HexTo##name)(const DLL_ByteArray *input,                                               \
                                             char *output,                                                             \
                                             unsigned int outputBufferSize,                                            \
                                             char *errorBuffer,                                                        \
                                             unsigned int errorBufferSize);
#endif

#ifndef TYPEDEF_WITH_TYPE
#define TYPEDEF_WITH_TYPE(name, type)                                                                                  \
  typedef void (*tASN1_##name##_Get##name##Value)(const DLL_ASN1_##name *obj, type *output);                           \
  typedef void (*tASN1_##name##_HexTo##name)(                                                                          \
      const DLL_ByteArray *input, type *output, char *errorBuffer, unsigned int errorBufferSize);
#endif

// Declare the types of each function to get from the DLL. The struct declaration is the type declaration of the node
#ifndef TYPEDEF_COMMON_FUNCTIONS
#define TYPEDEF_COMMON_FUNCTIONS(name, type)                                                                             \
  struct DLL_ASN1_##name;                                                                                                \
  typedef DLL_ASN1_##name *(*tASN1_##name##_New)(                                                                        \
      const char *name, const DLL_ByteArray *tag, bool optional, bool explicitTag, const DLL_ASN1_##name *defaultValue); \
  typedef void (*tASN1_##name##_Set##name##Value)(DLL_ASN1_##name * obj, const type val);                                \
  typedef void (*tASN1_##name##_Set##name##ValueCheck)(                                                                  \
      DLL_ASN1_##name * obj, const type val, char *errorBuffer, unsigned int errorBufferSize);                           \
  typedef void (*tASN1_##name##_##name##ToHex)(                                                                          \
      const type input, DLL_ByteArray *output, char *errorBuffer, unsigned int errorBufferSize);
#endif

// Declare variables that will hold the function pointers, and provide a function that will extract the function pointers from the DLL, and a check function
#ifndef DLL_FUNCTION_POINTER
#define DLL_FUNCTION_POINTER(name)                                                                                     \
  tASN1_##name##_New ASN1_##name##_New;                                                                                \
  tASN1_##name##_Get##name##Value ASN1_##name##_Get##name##Value;                                                      \
  tASN1_##name##_Set##name##Value ASN1_##name##_Set##name##Value;                                                      \
  tASN1_##name##_Set##name##ValueCheck ASN1_##name##_Set##name##ValueCheck;                                            \
  tASN1_##name##_##name##ToHex ASN1_##name##_##name##ToHex;                                                            \
  tASN1_##name##_HexTo##name ASN1_##name##_HexTo##name;                                                                \
                                                                                                                       \
  void InitFunctions_##name(HINSTANCE hDLL)                                                                            \
  {                                                                                                                    \
    GET_FUNC_POINTER(ASN1_##name##_New)                                                                                \
    GET_FUNC_POINTER(ASN1_##name##_Get##name##Value)                                                                   \
    GET_FUNC_POINTER(ASN1_##name##_Set##name##Value)                                                                   \
    GET_FUNC_POINTER(ASN1_##name##_Set##name##ValueCheck)                                                              \
    GET_FUNC_POINTER(ASN1_##name##_##name##ToHex)                                                                      \
    GET_FUNC_POINTER(ASN1_##name##_HexTo##name)                                                                        \
  }                                                                                                                    \
  bool Check_##name()                                                                                                  \
  {                                                                                                                    \
    return (ASN1_##name##_New && ASN1_##name##_Get##name##Value && ASN1_##name##_Set##name##Value                      \
            && ASN1_##name##_Set##name##ValueCheck && ASN1_##name##_##name##ToHex && ASN1_##name##_HexTo##name);       \
  }
#endif

#ifndef DLL_NODE_CHAR_BUFFER
#define DLL_NODE_CHAR_BUFFER(name)                                                                                     \
  TYPEDEF_COMMON_FUNCTIONS(name, char *)                                                                               \
  TYPEDEF_WITH_BUFFER(name)                                                                                            \
  DLL_FUNCTION_POINTER(name)
#endif

#ifndef DLL_NODE_TYPE
#define DLL_NODE_TYPE(name, type)                                                                                      \
  TYPEDEF_COMMON_FUNCTIONS(name, type)                                                                                 \
  TYPEDEF_WITH_TYPE(name, type)                                                                                        \
  DLL_FUNCTION_POINTER(name)
#endif

DLL_NODE_CHAR_BUFFER(BitString)
DLL_NODE_CHAR_BUFFER(IA5String)
DLL_NODE_CHAR_BUFFER(UTF8String)
DLL_NODE_CHAR_BUFFER(UTCTime)
DLL_NODE_CHAR_BUFFER(ObjectID)

DLL_NODE_TYPE(Integer, int)
DLL_NODE_TYPE(Enumerated, int)
DLL_NODE_TYPE(Real, double)
DLL_NODE_TYPE(OctetString, DLL_ByteArray)
DLL_NODE_TYPE(Boolean, bool)
DLL_NODE_TYPE(Null, bool)

// ------------ ASN1_CHOICE ------------
struct DLL_callbackChoice
{
  typedef DLL_ASN1_Object *(*callbackFunctionType)(int i, void *context);
  callbackFunctionType f;
  void *context;
};
typedef DLL_ASN1_Choice *(*tASN1_Choice_New)(DLL_callbackChoice choiceFromIdx,
                                             unsigned int maxChoiceIdx,
                                             const char *name,
                                             const DLL_ByteArray *tag,
                                             bool optional,
                                             bool explicitTag,
                                             const DLL_ASN1_Choice *defaultValue);
typedef unsigned int (*tASN1_Choice_AvailableChoices)(const DLL_ASN1_Choice *obj);
typedef const DLL_ASN1_Object *(*tASN1_Choice_GetChoiceFromIndex)(const DLL_ASN1_Choice *obj, int pos);
typedef void (*tASN1_Choice_MakeDummyChoiceList)(const DLL_ASN1_Choice *obj);
typedef void (*tASN1_Choice_DeleteDummyChoiceList)(const DLL_ASN1_Choice *obj);
typedef DLL_ASN1_Object *(*tASN1_Choice_SetSelectedChoice)(DLL_ASN1_Choice *obj, int idx);
typedef DLL_ASN1_Object *(*tASN1_Choice_GetSelectedChoice)(const DLL_ASN1_Choice *obj);
typedef unsigned int (*tASN1_Choice_GetSelectedChoiceIndex)(const DLL_ASN1_Choice *obj);

tASN1_Choice_New ASN1_Choice_New;
tASN1_Choice_AvailableChoices ASN1_Choice_AvailableChoices;
tASN1_Choice_GetChoiceFromIndex ASN1_Choice_GetChoiceFromIndex;
tASN1_Choice_MakeDummyChoiceList ASN1_Choice_MakeDummyChoiceList;
tASN1_Choice_DeleteDummyChoiceList ASN1_Choice_DeleteDummyChoiceList;
tASN1_Choice_SetSelectedChoice ASN1_Choice_SetSelectedChoice;
tASN1_Choice_GetSelectedChoice ASN1_Choice_GetSelectedChoice;
tASN1_Choice_GetSelectedChoiceIndex ASN1_Choice_GetSelectedChoiceIndex;
// -----------------------------------------------------------------------------

// ------------ ASN1_SEQUENCE ------------
typedef DLL_ASN1_Sequence *(*tASN1_Sequence_New)(DLL_ASN1_Object *valuesArray[],
                                                 unsigned int numberOfValues,
                                                 const char *name,
                                                 const DLL_ByteArray *tag,
                                                 bool optional,
                                                 bool explicitTag,
                                                 const DLL_ASN1_Sequence *defaultValue,
                                                 bool extensibility);
typedef DLL_ASN1_Object *(*tASN1_Sequence_GetObjectAt)(const DLL_ASN1_Sequence *obj, unsigned int pos);
typedef unsigned int (*tASN1_Sequence_GetSize)(const DLL_ASN1_Sequence *obj);
typedef DLL_ASN1_Object *(*tASN1_Sequence_GetExtensibilityObjectAt)(const DLL_ASN1_Sequence *obj, unsigned int pos);
typedef unsigned int (*tASN1_Sequence_GetExtensibilitySize)(const DLL_ASN1_Sequence *obj);
typedef bool (*tASN1_Sequence_IsExtensible)(const DLL_ASN1_Sequence *obj);

tASN1_Sequence_New ASN1_Sequence_New;
tASN1_Sequence_GetObjectAt ASN1_Sequence_GetObjectAt;
tASN1_Sequence_GetSize ASN1_Sequence_GetSize;
tASN1_Sequence_GetExtensibilityObjectAt ASN1_Sequence_GetExtensibilityObjectAt;
tASN1_Sequence_GetExtensibilitySize ASN1_Sequence_GetExtensibilitySize;
tASN1_Sequence_IsExtensible ASN1_Sequence_IsExtensible;
// -----------------------------------------------------------------------------

// ------------ ASN1_SEQUENCEOF ------------
struct DLL_callbackSequenceOf
{
  typedef DLL_ASN1_Object *(*callbackFunctionType)(void *context);
  callbackFunctionType f;
  void *context;
};
typedef DLL_ASN1_SequenceOf *(*tASN1_SequenceOf_New)(DLL_callbackSequenceOf newSeqOfObject,
                                                     const char *name,
                                                     const DLL_ByteArray *tag,
                                                     bool optional,
                                                     bool explicitTag,
                                                     const DLL_ASN1_SequenceOf *defaultValue);
typedef DLL_ASN1_Object *(*tASN1_SequenceOf_GetObjectAt)(const DLL_ASN1_SequenceOf *obj, int pos);
typedef unsigned int (*tASN1_SequenceOf_GetSize)(const DLL_ASN1_SequenceOf *obj);
typedef DLL_ASN1_Object *(*tASN1_SequenceOf_AppendNewObject)(DLL_ASN1_SequenceOf *obj);
typedef void (*tASN1_SequenceOf_DeleteObjectAt)(DLL_ASN1_SequenceOf *obj, int pos);
typedef void (*tASN1_SequenceOf_MoveUpObject)(DLL_ASN1_SequenceOf *obj, int pos);
typedef void (*tASN1_SequenceOf_MoveDownObject)(DLL_ASN1_SequenceOf *obj, int pos);
typedef DLL_ASN1_Object *(*tASN1_SequenceOf_GetDummyNewObject)(const DLL_ASN1_SequenceOf *obj);

tASN1_SequenceOf_New ASN1_SequenceOf_New;
tASN1_SequenceOf_GetObjectAt ASN1_SequenceOf_GetObjectAt;
tASN1_SequenceOf_GetSize ASN1_SequenceOf_GetSize;
tASN1_SequenceOf_AppendNewObject ASN1_SequenceOf_AppendNewObject;
tASN1_SequenceOf_DeleteObjectAt ASN1_SequenceOf_DeleteObjectAt;
tASN1_SequenceOf_MoveUpObject ASN1_SequenceOf_MoveUpObject;
tASN1_SequenceOf_MoveDownObject ASN1_SequenceOf_MoveDownObject;
tASN1_SequenceOf_GetDummyNewObject ASN1_SequenceOf_GetDummyNewObject;
// -----------------------------------------------------------------------------

// ------------ ASN1_SET ------------
typedef DLL_ASN1_Set *(*tASN1_Set_New)(DLL_ASN1_Object *valuesArray[],
                                       unsigned int numberOfValues,
                                       const char *name,
                                       const DLL_ByteArray *tag,
                                       bool optional,
                                       bool explicitTag,
                                       const DLL_ASN1_Set *defaultValue,
                                       bool extensibility);
typedef DLL_ASN1_Object *(*tASN1_Set_GetObjectAt)(const DLL_ASN1_Set *obj, unsigned int pos);
typedef unsigned int (*tASN1_Set_GetSize)(const DLL_ASN1_Set *obj);
typedef DLL_ASN1_Object *(*tASN1_Set_GetExtensibilityObjectAt)(const DLL_ASN1_Set *obj, unsigned int pos);
typedef unsigned int (*tASN1_Set_GetExtensibilitySize)(const DLL_ASN1_Set *obj);
typedef bool (*tASN1_Set_IsExtensible)(const DLL_ASN1_Set *obj);

tASN1_Set_New ASN1_Set_New;
tASN1_Set_GetObjectAt ASN1_Set_GetObjectAt;
tASN1_Set_GetSize ASN1_Set_GetSize;
tASN1_Set_GetExtensibilityObjectAt ASN1_Set_GetExtensibilityObjectAt;
tASN1_Set_GetExtensibilitySize ASN1_Set_GetExtensibilitySize;
tASN1_Set_IsExtensible ASN1_Set_IsExtensible;
// -----------------------------------------------------------------------------

bool LoadASN1DLL(const std::wstring &dllPath)
{
  HINSTANCE hDLL = LoadLibrary(dllPath.c_str());
  if (!hDLL)
    return false;

  // BYTE ARRAY
  GET_FUNC_POINTER(ByteArray_New)
  GET_FUNC_POINTER(ByteArray_NewFromByteArray)
  GET_FUNC_POINTER(ByteArray_Delete)
  GET_FUNC_POINTER(ByteArray_Size)
  GET_FUNC_POINTER(ByteArray_Equals)
  GET_FUNC_POINTER(ByteArray_GetString)
  GET_FUNC_POINTER(ByteArray_GetByteAtRank)
  GET_FUNC_POINTER(ByteArray_GetBytesAtRank)
  GET_FUNC_POINTER(ByteArray_Clear)
  GET_FUNC_POINTER(ByteArray_Append)
  GET_FUNC_POINTER(ByteArray_InsertAt)

  // UTILS
  GET_FUNC_POINTER(Utils_IntAsHex)
  GET_FUNC_POINTER(Utils_HexAsInt)
  GET_FUNC_POINTER(Utils_BinaryAsHex)
  GET_FUNC_POINTER(Utils_HexAsBinary)
  GET_FUNC_POINTER(Utils_HexAsBinary8Padded)
  GET_FUNC_POINTER(Utils_IntAsBinary)
  GET_FUNC_POINTER(Utils_IntAsBinary8Padded)
  GET_FUNC_POINTER(Utils_BinaryAsInt)
  GET_FUNC_POINTER(Utils_IsHex)
  GET_FUNC_POINTER(Utils_IsBinary)
  GET_FUNC_POINTER(Utils_StringToHex)
  GET_FUNC_POINTER(Utils_HexToString)
  GET_FUNC_POINTER(Utils_IsComplexType)
  GET_FUNC_POINTER(Utils_GetTagFromBuffer)
  GET_FUNC_POINTER(Utils_GetLengthFromBuffer)
  GET_FUNC_POINTER(Utils_MakeLength)
  GET_FUNC_POINTER(Utils_MakeTag)
  GET_FUNC_POINTER(Utils_DecomposeTag)
  GET_FUNC_POINTER(Utils_UTCTimeToValues)
  GET_FUNC_POINTER(Utils_ValuesToUTCTime)
  GET_FUNC_POINTER(Utils_IsValidUTCTime)
  GET_FUNC_POINTER(Utils_IsValidObjectID)
  GET_FUNC_POINTER(Utils_IsValidIA5String)
  GET_FUNC_POINTER(Utils_IsValidUTF8String)

  // ASN1_OBJECT
  GET_FUNC_POINTER(ASN1_Object_GetMyOwner)
  GET_FUNC_POINTER(ASN1_Object_GetDefaultValue)
  GET_FUNC_POINTER(ASN1_Object_GetDefaultTag)
  GET_FUNC_POINTER(ASN1_Object_GetTag)
  GET_FUNC_POINTER(ASN1_Object_GetDescription)
  GET_FUNC_POINTER(ASN1_Object_StringExtract)
  GET_FUNC_POINTER(ASN1_Object_StringExtractForResearch)
  GET_FUNC_POINTER(ASN1_Object_GetType)
  GET_FUNC_POINTER(ASN1_Object_IsMandatory)
  GET_FUNC_POINTER(ASN1_Object_IsIgnored)
  GET_FUNC_POINTER(ASN1_Object_IsExplicit)
  GET_FUNC_POINTER(ASN1_Object_GetHexBuffer)
  GET_FUNC_POINTER(ASN1_Object_GetLastSize)
  GET_FUNC_POINTER(ASN1_Object_ClearDynamicData)
  GET_FUNC_POINTER(ASN1_Object_SetDescription)
  GET_FUNC_POINTER(ASN1_Object_Ignore)
  GET_FUNC_POINTER(ASN1_Object_WriteIntoBuffer)
  GET_FUNC_POINTER(ASN1_Object_ReadFromBuffer)
  GET_FUNC_POINTER(ASN1_Object_Compare)
  GET_FUNC_POINTER(ASN1_Object_Delete)

  InitFunctions_BitString(hDLL);
  InitFunctions_Boolean(hDLL);
  InitFunctions_Enumerated(hDLL);
  InitFunctions_IA5String(hDLL);
  InitFunctions_Integer(hDLL);
  InitFunctions_OctetString(hDLL);
  InitFunctions_ObjectID(hDLL);
  InitFunctions_Real(hDLL);
  InitFunctions_Null(hDLL);
  InitFunctions_UTCTime(hDLL);
  InitFunctions_UTF8String(hDLL);

  // ASN1_CHOICE
  GET_FUNC_POINTER(ASN1_Choice_New)
  GET_FUNC_POINTER(ASN1_Choice_AvailableChoices)
  GET_FUNC_POINTER(ASN1_Choice_GetChoiceFromIndex)
  GET_FUNC_POINTER(ASN1_Choice_MakeDummyChoiceList)
  GET_FUNC_POINTER(ASN1_Choice_DeleteDummyChoiceList)
  GET_FUNC_POINTER(ASN1_Choice_SetSelectedChoice)
  GET_FUNC_POINTER(ASN1_Choice_GetSelectedChoice)
  GET_FUNC_POINTER(ASN1_Choice_GetSelectedChoiceIndex)

  // ASN1_SEQUENCE
  GET_FUNC_POINTER(ASN1_Sequence_New)
  GET_FUNC_POINTER(ASN1_Sequence_GetObjectAt)
  GET_FUNC_POINTER(ASN1_Sequence_GetSize)
  GET_FUNC_POINTER(ASN1_Sequence_GetExtensibilityObjectAt)
  GET_FUNC_POINTER(ASN1_Sequence_GetExtensibilitySize)
  GET_FUNC_POINTER(ASN1_Sequence_IsExtensible)

  // ASN1_SEQUENCEOF
  GET_FUNC_POINTER(ASN1_SequenceOf_New)
  GET_FUNC_POINTER(ASN1_SequenceOf_GetObjectAt)
  GET_FUNC_POINTER(ASN1_SequenceOf_GetSize)
  GET_FUNC_POINTER(ASN1_SequenceOf_AppendNewObject)
  GET_FUNC_POINTER(ASN1_SequenceOf_DeleteObjectAt)
  GET_FUNC_POINTER(ASN1_SequenceOf_MoveUpObject)
  GET_FUNC_POINTER(ASN1_SequenceOf_MoveDownObject)
  GET_FUNC_POINTER(ASN1_SequenceOf_GetDummyNewObject)

  // ASN1_SET
  GET_FUNC_POINTER(ASN1_Set_New)
  GET_FUNC_POINTER(ASN1_Set_GetObjectAt)
  GET_FUNC_POINTER(ASN1_Set_GetSize)
  GET_FUNC_POINTER(ASN1_Set_GetExtensibilityObjectAt)
  GET_FUNC_POINTER(ASN1_Set_GetExtensibilitySize)
  GET_FUNC_POINTER(ASN1_Set_IsExtensible)

  // Check all function pointers and return false if one of them is null
  if (!ByteArray_New || !ByteArray_NewFromByteArray || !ByteArray_Delete || !ByteArray_Size || !ByteArray_Equals
      || !ByteArray_GetString || !ByteArray_GetByteAtRank || !ByteArray_GetBytesAtRank || !ByteArray_Clear
      || !ByteArray_Append || !ByteArray_InsertAt)
    return false;
  if (!Utils_IntAsHex || !Utils_HexAsInt || !Utils_BinaryAsHex || !Utils_HexAsBinary || !Utils_HexAsBinary8Padded
      || !Utils_IntAsBinary || !Utils_IntAsBinary8Padded || !Utils_BinaryAsInt || !Utils_IsHex || !Utils_IsBinary
      || !Utils_IsComplexType || !Utils_GetTagFromBuffer || !Utils_GetLengthFromBuffer || !Utils_MakeLength
      || !Utils_MakeTag || !Utils_DecomposeTag || !Utils_StringToHex || !Utils_HexToString || !Utils_UTCTimeToValues
      || !Utils_ValuesToUTCTime || !Utils_IsValidObjectID || !Utils_IsValidUTCTime || !Utils_IsValidIA5String
      || !Utils_IsValidUTF8String)
    return false;
  if (!ASN1_Object_GetMyOwner || !ASN1_Object_GetDefaultValue || !ASN1_Object_GetDefaultTag || !ASN1_Object_GetTag
      || !ASN1_Object_GetDescription || !ASN1_Object_StringExtract || !ASN1_Object_StringExtractForResearch
      || !ASN1_Object_GetType || !ASN1_Object_IsMandatory || !ASN1_Object_IsIgnored || !ASN1_Object_IsExplicit
      || !ASN1_Object_GetHexBuffer || !ASN1_Object_GetLastSize || !ASN1_Object_ClearDynamicData
      || !ASN1_Object_SetDescription || !ASN1_Object_Ignore || !ASN1_Object_WriteIntoBuffer
      || !ASN1_Object_ReadFromBuffer || !ASN1_Object_Compare || !ASN1_Object_Delete)
    return false;
  if (!ASN1_Choice_New || !ASN1_Choice_AvailableChoices || !ASN1_Choice_GetChoiceFromIndex
      || !ASN1_Choice_MakeDummyChoiceList || !ASN1_Choice_DeleteDummyChoiceList || !ASN1_Choice_SetSelectedChoice
      || !ASN1_Choice_GetSelectedChoice || !ASN1_Choice_GetSelectedChoiceIndex)
    return false;
  if (!ASN1_Sequence_New || !ASN1_Sequence_GetObjectAt || !ASN1_Sequence_GetSize
      || !ASN1_Sequence_GetExtensibilityObjectAt || !ASN1_Sequence_GetExtensibilitySize || !ASN1_Sequence_IsExtensible)
    return false;
  if (!ASN1_SequenceOf_New || !ASN1_SequenceOf_GetObjectAt || !ASN1_SequenceOf_GetSize
      || !ASN1_SequenceOf_AppendNewObject || !ASN1_SequenceOf_DeleteObjectAt || !ASN1_SequenceOf_MoveUpObject
      || !ASN1_SequenceOf_MoveDownObject || !ASN1_SequenceOf_GetDummyNewObject)
    return false;
  if (!ASN1_Set_New || !ASN1_Set_GetObjectAt || !ASN1_Set_GetSize || !ASN1_Set_GetExtensibilityObjectAt
      || !ASN1_Set_GetExtensibilitySize || !ASN1_Set_IsExtensible)
    return false;
  if (!Check_BitString() || !Check_Boolean() || !Check_Enumerated() || !Check_IA5String() || !Check_Integer()
      || !Check_Null() || !Check_OctetString() || !Check_ObjectID() || !Check_Real() || !Check_UTCTime()
      || !Check_UTF8String())
    return false;

  return true;
}

// Utility class to manage memory of ByteArray. The ByteArray will be automatically deleted with the object, and prevents the user to call ByteArray_Delete()
class Hex
{
  DLL_ByteArray *ptr;

public:
  Hex(const char *str)
  {
    ptr = ByteArray_New(str);
  }
  Hex(DLL_ByteArray *ptr2)
  {
    ptr = ByteArray_NewFromByteArray(ptr2);
  }
  ~Hex()
  {
    ByteArray_Delete(ptr);
  }
  DLL_ByteArray *p()
  {
    return ptr;
  }
};

// Utility function to manage memory. Add the new object to a list, then you can call the delete function on each object
std::vector<DLL_ASN1_Object *> toDelete;
template <class T>
T *NewObj(T *obj)
{
  toDelete.push_back((DLL_ASN1_Object *)obj);
  return obj;
}

} // namespace ASN1_DLL

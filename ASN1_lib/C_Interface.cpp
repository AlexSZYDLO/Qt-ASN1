/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "C_Interface.h"
#include <string.h>

void StringToBuffer(std::string& s, char* buffer, unsigned int bufferSize) {
  if(s.size() < bufferSize)
    strncpy(buffer, s.c_str(), s.size());
  else
    strncpy(buffer, s.c_str(), bufferSize - 1);
}

#ifndef NODE_CONSTRUCTOR_FUNCTION_IMPL
#define NODE_CONSTRUCTOR_FUNCTION_IMPL(name) \
  MODULE_API ASN1_##name* ASN1_##name##_New(const char* objectName, const ByteArray* tag, bool optional, bool explicitTag, const ASN1_##name* defaultValue) { return new ASN1_##name(objectName, *tag, optional, explicitTag, defaultValue); }
#endif

#ifndef NODE_SET_FUNCTION_IMPL
#define NODE_SET_FUNCTION_IMPL(name, type) \
  MODULE_API void ASN1_##name##_Set##name##Value(ASN1_##name* obj, const type val) { obj->Set##name##Value(val); }
#endif

#ifndef NODE_SET_CHECK_FUNCTION_IMPL
#define NODE_SET_CHECK_FUNCTION_IMPL(name, type)                                                                                           \
  MODULE_API void ASN1_##name##_Set##name##ValueCheck(ASN1_##name* obj, const type val, char* errorBuffer, unsigned int errorBufferSize) { \
    std::string error;                                                                                                                     \
    obj->Set##name##Value(val, error);                                                                                                     \
    StringToBuffer(error, errorBuffer, errorBufferSize);                                                                                   \
  }
#endif

#ifndef NODE_GET_FUNCTION_IMPL
#define NODE_GET_FUNCTION_IMPL(name, type) \
  MODULE_API void ASN1_##name##_Get##name##Value(const ASN1_##name* obj, type* out) { *out = obj->Get##name##Value(); }
#endif

#ifndef NODE_GET_WITH_BUFFER_FUNCTION_IMPL
#define NODE_GET_WITH_BUFFER_FUNCTION_IMPL(name)                                                               \
  MODULE_API void ASN1_##name##_Get##name##Value(const ASN1_##name* obj, char* out, unsigned int bufferSize) { \
    std::string s = obj->Get##name##Value();                                                                   \
    StringToBuffer(s, out, bufferSize);                                                                        \
  }
#endif

#ifndef NODE_CONVERT_HEX_TO_TYPE_IMPL
#define NODE_CONVERT_HEX_TO_TYPE_IMPL(name, type)                                                                                    \
  MODULE_API void ASN1_##name##_HexTo##name(const ByteArray* input, type* output, char* errorBuffer, unsigned int errorBufferSize) { \
    std::string error;                                                                                                               \
    ASN1_##name::HexTo##name(*input, *output, error);                                                                                \
    StringToBuffer(error, errorBuffer, errorBufferSize);                                                                             \
  }
#endif

#ifndef NODE_CONVERT_HEX_TO_TYPE_WITH_BUFFER_IMPL
#define NODE_CONVERT_HEX_TO_TYPE_WITH_BUFFER_IMPL(name)                                                                                                             \
  MODULE_API void ASN1_##name##_HexTo##name(const ByteArray* input, char* output, unsigned int outputBufferSize, char* errorBuffer, unsigned int errorBufferSize) { \
    std::string error, outputStr;                                                                                                                                   \
    ASN1_##name::HexTo##name(*input, outputStr, error);                                                                                                             \
    StringToBuffer(error, errorBuffer, errorBufferSize);                                                                                                            \
    StringToBuffer(outputStr, output, outputBufferSize);                                                                                                            \
  }
#endif

#ifndef NODE_CONVERT_TYPE_TO_HEX_IMPL
#define NODE_CONVERT_TYPE_TO_HEX_IMPL(name, type)                                                                                     \
  MODULE_API void ASN1_##name##_##name##ToHex(const type input, ByteArray* output, char* errorBuffer, unsigned int errorBufferSize) { \
    std::string error;                                                                                                                \
    ASN1_##name::name##ToHex(input, *output, error);                                                                                  \
    StringToBuffer(error, errorBuffer, errorBufferSize);                                                                              \
  }
#endif

#ifndef OBJECT_INTERFACE_TYPE_IMPL
#define OBJECT_INTERFACE_TYPE_IMPL(name, type) \
  NODE_CONSTRUCTOR_FUNCTION_IMPL(name)         \
  NODE_GET_FUNCTION_IMPL(name, type)           \
  NODE_SET_FUNCTION_IMPL(name, type)           \
  NODE_SET_CHECK_FUNCTION_IMPL(name, type)     \
  NODE_CONVERT_HEX_TO_TYPE_IMPL(name, type)    \
  NODE_CONVERT_TYPE_TO_HEX_IMPL(name, type)
#endif

#ifndef OBJECT_INTERFACE_BUFFER_IMPL
#define OBJECT_INTERFACE_BUFFER_IMPL(name)        \
  NODE_CONSTRUCTOR_FUNCTION_IMPL(name)            \
  NODE_GET_WITH_BUFFER_FUNCTION_IMPL(name)        \
  NODE_SET_FUNCTION_IMPL(name, char*)             \
  NODE_SET_CHECK_FUNCTION_IMPL(name, char*)       \
  NODE_CONVERT_HEX_TO_TYPE_WITH_BUFFER_IMPL(name) \
  NODE_CONVERT_TYPE_TO_HEX_IMPL(name, char*)
#endif

// ------------ HEX STRING ----------------
ByteArray* ByteArray_New(const char* str) {
  return new ByteArray(str);
}

ByteArray* ByteArray_NewFromByteArray(const ByteArray* hex) {
  return new ByteArray(*hex);
}

void ByteArray_Delete(ByteArray* hex) {
  delete hex;
}

void ByteArray_Clear(ByteArray* hex) {
  hex->Clear();
}

unsigned int ByteArray_Size(const ByteArray* hex) {
  return hex->Size();
}

bool ByteArray_Equals(const ByteArray* hex, const ByteArray* second) {
  return *hex == *second;
}

const char* ByteArray_GetString(const ByteArray* hex) {
  return hex->GetString();
}

bool ByteArray_GetByteAtRank(const ByteArray* hex, unsigned int byteRank, ByteArray* out) {
  return hex->GetByteAtRank(byteRank, *out);
}

bool ByteArray_GetBytesAtRank(const ByteArray* hex, unsigned int firstByteRank, unsigned int nbOfBytes, ByteArray* out) {
  return hex->GetBytesAtRank(firstByteRank, nbOfBytes, *out);
}

void ByteArray_Append(ByteArray* hex, const ByteArray* bufferToAppend) {
  hex->Append(*bufferToAppend);
}

bool ByteArray_InsertAt(ByteArray* hex, const ByteArray* bufferToAppend, unsigned int pos) {
  return hex->InsertAt(*bufferToAppend, pos);
}

// ------------ UTILS ----------------
void Utils_IntAsHex(int i, ByteArray* out) {
  *out = Utils::IntAsHex(i);
}

unsigned int Utils_HexAsInt(const ByteArray* hexStr) {
  return Utils::HexAsInt(*hexStr);
}

void Utils_BinaryAsHex(const char* binary, ByteArray* out) {
  *out = Utils::BinaryAsHex(binary);
}

void Utils_HexAsBinary(const ByteArray* byteArray, char* out, unsigned int bufferSize) {
  std::string s = Utils::HexAsBinary(*byteArray);
  StringToBuffer(s, out, bufferSize);
}

void Utils_HexAsBinary8Padded(const ByteArray* byteArray, char* out, unsigned int bufferSize) {
  std::string s = Utils::HexAsBinary8Padded(*byteArray);
  StringToBuffer(s, out, bufferSize);
}

void Utils_IntAsBinary(unsigned int i, char* out, unsigned int bufferSize) {
  std::string s = Utils::IntAsBinary(i);
  StringToBuffer(s, out, bufferSize);
}

void Utils_IntAsBinary8Padded(unsigned int i, char* out, unsigned int bufferSize) {
  std::string s = Utils::IntAsBinary8Padded(i);
  StringToBuffer(s, out, bufferSize);
}

unsigned int Utils_BinaryAsInt(const char* binaryStr) {
  return Utils::BinaryAsInt(binaryStr);
}

bool Utils_IsHex(const char* str) {
  return Utils::IsHex(str);
}

bool Utils_IsBinary(const char* str) {
  return Utils::IsBinary(str);
}

bool Utils_GetTagFromBuffer(const ByteArray* fromBuffer, unsigned int pos, ByteArray* tag) {
  return Utils::GetTagFromBuffer(*fromBuffer, pos, *tag);
}

bool Utils_IsComplexType(int type) {
  return Utils::IsComplexType(static_cast<Utils::eNodeType>(type));
}

bool Utils_GetLengthFromBuffer(const ByteArray* fromBuffer, unsigned int pos, unsigned int* L) {
  return Utils::GetLengthFromBuffer(*fromBuffer, pos, *L);
}

void Utils_MakeLength(unsigned int sizeAsInt, ByteArray* out) {
  *out = Utils::MakeLength(sizeAsInt);
}

void Utils_MakeTag(unsigned int tagClass, unsigned int tagForm, const ByteArray* label, ByteArray* out) {
  *out = Utils::MakeTag(static_cast<Utils::eTagClass>(tagClass), static_cast<Utils::eTagForm>(tagForm), *label);
}

bool Utils_DecomposeTag(const ByteArray* tag, unsigned int* tagClass, unsigned int* tagForm, ByteArray* label) {
  Utils::eTagClass c;
  Utils::eTagForm f;
  bool b = Utils::DecomposeTag(*tag, c, f, *label);
  *tagClass = static_cast<unsigned int>(c);
  *tagForm = static_cast<unsigned int>(f);
  return b;
}


void Utils_StringToHex(const char* str, ByteArray* out) {
  *out = Utils::StringToHex(str);
}

void Utils_HexToString(const ByteArray* asciiHex, char* out, unsigned int bufferSize) {
  std::string s = Utils::HexToString(*asciiHex);
  StringToBuffer(s, out, bufferSize);
}

void Utils_UTCTimeToValues(const char* input, int* year_YY, int* month_MM, int* day_DD, int* hours_HH, int* minutes_MM, int* seconds_SS,
                           unsigned int* zone, int* zoneHours_HH, int* zoneMinutes_MM, char* error, unsigned int errorBufferSize) {
  std::string errorStr;
  Utils::eUTCTimeZone z = Utils::cGMT;
  Utils::UTCTimeToValues(input, *year_YY, *month_MM, *day_DD, *hours_HH, *minutes_MM, *seconds_SS, z, *zoneHours_HH, *zoneMinutes_MM, errorStr);
  *zone = static_cast<unsigned int>(z);
  StringToBuffer(errorStr, error, errorBufferSize);
}

void Utils_ValuesToUTCTime(int year_YY, int month_MM, int day_DD, int hours_HH, int minutes_MM, int seconds_SS,
                           unsigned int zone, int zoneHours_HH, int zoneMinutes_MM,
                           char* out, unsigned int bufferSize, char* error, unsigned int errorBufferSize) {
  std::string outStr, errorStr;
  Utils::ValuesToUTCTime(year_YY, month_MM, day_DD, hours_HH, minutes_MM, seconds_SS, static_cast<Utils::eUTCTimeZone>(zone), zoneHours_HH, zoneMinutes_MM, outStr, errorStr);
  StringToBuffer(outStr, out, bufferSize);
  StringToBuffer(errorStr, error, errorBufferSize);
}

bool Utils_IsValidUTCTime(const char* input) {
  return Utils::IsValidUTCTime(input);
}

bool Utils_IsValidObjectID(const char* input) {
  return Utils::IsValidObjectID(input);
}

bool Utils_IsValidIA5String(const char* input) {
  return Utils::IsValidIA5String(input);
}

bool Utils_IsValidUTF8String(const char* input) {
  return Utils::IsValidUTF8String(input);
}

// ------------ ASN1_OBJECT ------------
void ASN1_Object_Delete(ASN1_Object* obj) {
  delete obj;
}

const ASN1_Object* ASN1_Object_GetMyOwner(const ASN1_Object* obj) {
  return obj->GetMyOwner();
}

const ASN1_Object* ASN1_Object_GetDefaultValue(const ASN1_Object* obj) {
  return obj->GetDefaultValue();
}

void ASN1_Object_GetDefaultTag(const ASN1_Object* obj, ByteArray* out) {
  *out = obj->GetDefaultTag();
}

void ASN1_Object_GetTag(const ASN1_Object* obj, ByteArray* out) {
  *out = obj->GetTag();
}

void ASN1_Object_GetName(const ASN1_Object* obj, char* out, unsigned int bufferSize) {
  std::string s = obj->GetName();
  StringToBuffer(s, out, bufferSize);
}

void ASN1_Object_GetDescription(const ASN1_Object* obj, char* out, unsigned int bufferSize) {
  std::string s = obj->GetDescription();
  StringToBuffer(s, out, bufferSize);
}

void ASN1_Object_StringExtract(const ASN1_Object* obj, char* out, unsigned int bufferSize) {
  std::string s = obj->StringExtract();
  StringToBuffer(s, out, bufferSize);
}

void ASN1_Object_StringExtractForResearch(const ASN1_Object* obj, char* out, unsigned int bufferSize) {
  std::string s = obj->StringExtractForResearch();
  StringToBuffer(s, out, bufferSize);
}

unsigned int ASN1_Object_GetType(const ASN1_Object* obj) {
  return static_cast<unsigned int>(obj->GetType());
}

bool ASN1_Object_IsMandatory(const ASN1_Object* obj) {
  return obj->IsMandatory();
}

bool ASN1_Object_IsIgnored(const ASN1_Object* obj) {
  return obj->IsIgnored();
}

bool ASN1_Object_IsExplicit(const ASN1_Object* obj) {
  return obj->IsExplicit();
}

void ASN1_Object_GetHexBuffer(const ASN1_Object* obj, ByteArray* out) {
  *out = obj->GetHexBuffer();
}

unsigned int ASN1_Object_GetLastSize(const ASN1_Object* obj) {
  return obj->GetLastLength();
}

void ASN1_Object_ClearDynamicData(ASN1_Object* obj) {
  obj->ClearDynamicData();
}

void ASN1_Object_SetDescription(ASN1_Object* obj, const char* desc) {
  obj->SetDescription(desc);
}

void ASN1_Object_Ignore(ASN1_Object* obj, bool ignore) {
  obj->Ignore(ignore);
}

void ASN1_Object_WriteIntoBuffer(const ASN1_Object* obj, ByteArray* buffer) {
  obj->WriteIntoBuffer(*buffer);
}

bool ASN1_Object_ReadFromBuffer(ASN1_Object* obj, const ByteArray* buffer,
                                char* error, unsigned int errorBufferSize) {
  return obj->ReadFromBuffer(*buffer, error, errorBufferSize);
}

bool ASN1_Object_Compare(const ASN1_Object* obj, const ASN1_Object* secondTree,
                         unsigned int* nbDiffs, char* errorReport, unsigned int errorBufferSize) {
  return obj->Compare(*secondTree, *nbDiffs, errorReport, errorBufferSize);
}

// ------------ NODES ------------
OBJECT_INTERFACE_BUFFER_IMPL(BitString)
OBJECT_INTERFACE_BUFFER_IMPL(IA5String)
OBJECT_INTERFACE_BUFFER_IMPL(ObjectID)
OBJECT_INTERFACE_BUFFER_IMPL(UTCTime)
OBJECT_INTERFACE_BUFFER_IMPL(UTF8String)

OBJECT_INTERFACE_TYPE_IMPL(Boolean, bool)
OBJECT_INTERFACE_TYPE_IMPL(Null, bool)
OBJECT_INTERFACE_TYPE_IMPL(Enumerated, int)
OBJECT_INTERFACE_TYPE_IMPL(Integer, int)
OBJECT_INTERFACE_TYPE_IMPL(OctetString, ByteArray)
OBJECT_INTERFACE_TYPE_IMPL(Real, double)

// ------------ ASN1_CHOICE ------------
ASN1_Choice* ASN1_Choice_New(ASN1_Choice::callbackChoice choiceFromIdx, unsigned int maxChoiceIdx, const char* name, const ByteArray* tag,
                             bool optional, bool explicitTag, const ASN1_Choice* defaultValue) {
  return new ASN1_Choice(choiceFromIdx, maxChoiceIdx, name, *tag, optional, explicitTag, defaultValue);
}

unsigned int ASN1_Choice_AvailableChoices(const ASN1_Choice* obj) {
  return obj->AvailableChoices();
}

const ASN1_Object* ASN1_Choice_GetChoiceFromIndex(const ASN1_Choice* obj, int pos) {
  return obj->GetChoiceFromIndex(pos);
}

void ASN1_Choice_MakeDummyChoiceList(const ASN1_Choice* obj) {
  obj->MakeDummyChoiceList();
}

void ASN1_Choice_DeleteDummyChoiceList(const ASN1_Choice* obj) {
  obj->DeleteDummyChoiceList();
}

ASN1_Object* ASN1_Choice_SetSelectedChoice(ASN1_Choice* obj, int idx) {
  return obj->SetSelectedChoice(idx);
}

ASN1_Object* ASN1_Choice_GetSelectedChoice(const ASN1_Choice* obj) {
  return obj->GetSelectedChoice();
}

unsigned int ASN1_Choice_GetSelectedChoiceIndex(const ASN1_Choice* obj) {
  return obj->GetSelectedChoiceIndex();
}

// ------------ ASN1_SEQUENCE ------------
ASN1_Sequence* ASN1_Sequence_New(ASN1_Object* valuesArray[], unsigned int numberOfValues, const char* name, const ByteArray* tag,
                                 bool optional, bool explicitTag, const ASN1_Sequence* defaultValue, bool extensibility) {
  return new ASN1_Sequence(valuesArray, numberOfValues, name, *tag, optional, explicitTag, defaultValue, extensibility);
}

ASN1_Object* ASN1_Sequence_GetObjectAt(const ASN1_Sequence* obj, unsigned int pos) {
  return obj->GetObjectAt(pos);
}

unsigned int ASN1_Sequence_GetSize(const ASN1_Sequence* obj) {
  return obj->GetSize();
}

ASN1_Object* ASN1_Sequence_GetExtensibilityObjectAt(const ASN1_Sequence* obj, unsigned int pos) {
  return obj->GetExtensibilityObjectAt(pos);
}
unsigned int ASN1_Sequence_GetExtensibilitySize(const ASN1_Sequence* obj) {
  return obj->GetExtensibilitySize();
}

bool ASN1_Sequence_IsExtensible(const ASN1_Sequence* obj) {
  return obj->IsExtensible();
}


// ------------ ASN1_SEQUENCEOF ------------
ASN1_SequenceOf* ASN1_SequenceOf_New(ASN1_SequenceOf::callbackSequenceOf newSeqOfObject, const char* name, const ByteArray* tag,
                                     bool optional, bool explicitTag, const ASN1_SequenceOf* defaultValue) {
  return new ASN1_SequenceOf(newSeqOfObject, name, *tag, optional, explicitTag, defaultValue);
}

ASN1_Object* ASN1_SequenceOf_GetObjectAt(const ASN1_SequenceOf* obj, int pos) {
  return obj->GetObjectAt(pos);
}

unsigned int ASN1_SequenceOf_GetSize(const ASN1_SequenceOf* obj) {
  return obj->GetSequenceOfSize();
}

ASN1_Object* ASN1_SequenceOf_AppendNewObject(ASN1_SequenceOf* obj) {
  return obj->AppendNewObject();
}

void ASN1_SequenceOf_DeleteObjectAt(ASN1_SequenceOf* obj, int pos) {
  obj->DeleteObjectAt(pos);
}

void ASN1_SequenceOf_MoveUpObject(ASN1_SequenceOf* obj, int pos) {
  obj->MoveUpObject(pos);
}

void ASN1_SequenceOf_MoveDownObject(ASN1_SequenceOf* obj, int pos) {
  obj->MoveDownObject(pos);
}

ASN1_Object* ASN1_SequenceOf_GetDummyNewObject(const ASN1_SequenceOf* obj) {
  return obj->GetDummyNewObject();
}

// ------------ ASN1_SET ------------
ASN1_Set* ASN1_Set_New(ASN1_Object* valuesArray[], unsigned int numberOfValues, const char* name, const ByteArray* tag,
                       bool optional, bool explicitTag, const ASN1_Set* defaultValue, bool extensibility) {
  return new ASN1_Set(valuesArray, numberOfValues, name, *tag, optional, explicitTag, defaultValue, extensibility);
}

ASN1_Object* ASN1_Set_GetObjectAt(const ASN1_Set* obj, unsigned int pos) {
  return obj->GetObjectAt(pos);
}

unsigned int ASN1_Set_GetSize(const ASN1_Set* obj) {
  return obj->GetSize();
}

ASN1_Object* ASN1_Set_GetExtensibilityObjectAt(const ASN1_Set* obj, unsigned int pos) {
  return obj->GetExtensibilityObjectAt(pos);
}

unsigned int ASN1_Set_GetExtensibilitySize(const ASN1_Set* obj) {
  return obj->GetExtensibilitySize();
}

bool ASN1_Set_IsExtensible(const ASN1_Set* obj) {
  return obj->IsExtensible();
}

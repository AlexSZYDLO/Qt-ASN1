/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <string>
#include <vector>
#include "Utils.h"

/*
Base class for grammar node. This class is abstract.
It provides accessor the the node properties that are generic.

It is also the interface for encoding and decoding.
- WriteIntoBuffer(ByteArray& buffer) to get the result buffer of the grammar with its current values
- ReadFromBuffer(const ByteArray& buffer, char* error, size_t errorBufferSize) to read the data from a buffer

- Compare(const ASN1_Object& secondTree, unsigned int& nbDiffs, char* errorReport, size_t errorBufferSize) allow to compare two objects (and their structure)
  The grammar of both tree must correspond. It does not compare the grammars, but the values inside.
*/

#ifdef _MSC_VER
#ifdef MODULE_API_EXPORTS
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif

// This class is just declared here, but the user must not access it.
// It contains the technical behavior of the nodes. We only need to keep a pointer to it
namespace Value {
  class ASN1_Value;
}

class MODULE_API ASN1_Object {
  static unsigned int static_ObjectCount;

 public:
  static bool memoryCheck();

 protected:
  Value::ASN1_Value* Value;

 public:
  ASN1_Object();
  virtual ~ASN1_Object() = 0;

  // Should not be called by client. The client does not have the definition of this class
  Value::ASN1_Value* GetValue() const;

  // Access grammar information
  const ASN1_Object* GetMyOwner() const;
  const ASN1_Object* GetDefaultValue() const;
  ByteArray GetDefaultTag() const;
  ByteArray GetTag() const;
  Utils::eNodeType GetType() const;
  bool IsMandatory() const;
  bool IsIgnored() const;
  bool IsExplicit() const;

  // Access data that are properties of the node, but not contained in the ASN1 grammar
  std::string GetName() const;
  std::string GetDescription() const;
  std::string StringExtract() const;
  std::string StringExtractForResearch() const;

  // Access dynamic data of the node
  ByteArray GetHexBuffer() const;
  unsigned int GetLastLength() const;

  // Clears the dynamic data. It does not clear the values, but reinitializes the structure of the tree (clears the objects of sequence of / reinitilize choices)
  void ClearDynamicData();

  // Setters for changeable values
  void SetDescription(const char* desc);
  void Ignore(bool ignore = true);

  //The output is set in the buffer passed as argument. The buffer is cleared before starting. This function should never fail.
  void WriteIntoBuffer(ByteArray& buffer) const;

  //The data to read must correspond with the grammar encoded in this objet. If a problem at reading happens, the function returns false,
  // and the error will be written in the error buffer passed as argument (512 bytes should be enough to get full message)
  bool ReadFromBuffer(const ByteArray& buffer, char* error, size_t errorBufferSize);

  // Compares two trees, that should be of the same grammar. The report will contain the differences in the values, optionality, selected choices, number of objects in sequences of...
  // The buffer needs to be large enough to print all the differences (5000 bytes should be fine)
  bool Compare(const ASN1_Object& secondTree, unsigned int& nbDiffs, char* errorReport, size_t errorBufferSize) const;
};

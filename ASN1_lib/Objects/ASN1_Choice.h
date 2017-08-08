/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include "../ASN1_Object.h"

/*
ASN1 nodes definition for choice. See comment in ASN1_Object_Nodes.h for further explanations.
Choice works with a call back that must be defined on client side. This call back is called to instanciate the object associated with the choice, based on an index.

if a choice proposes 3 possibilities:
- INTGER
- IA5String
- BOOLEAN

The callback whould look like:

ASN1_Choice::callbackChoice callback{
  [](unsigned int idx, void*) -> ASN1_Object* {
    switch (idx) {
    case 0: return new ASN1_Integer();
    case 1: return new ASN1_IA5String();
    case 2: return new ASN1_Boolean();
    default: return nullptr; // should never be accessed
  }
}, nullptr }; // the pointer can be used by the client side to store context information,
                 if for instance, the same call back function is used for several choices

 The second parameter MUST be the number of possible return values. If not, you may end up with null values in your choice.


 The choice object does not keep instanciated all the possible choices. It only keeps the selected one, and instanciates only the required one when calling SetSelectedChoice(int)
 However, for choice selection, it may be usefull to see all the possible choices at the same time (eg. in GUIs). To do so,
 - call MakeDummyChoiceList() to instanciate one of each possible choice
 - you can call GetChoiceFromIndex(int) to access the available choices. This does NOT set the value, they are just dummies
 - Select the choice you want with SetSelectedChoice(int) (can be done as many times as you want)
 - Clean the list of possibilities with DeleteDummyChoiceList(). Facultative, but if you keep the list, you increase the memory used
 The dummy choices must ONLY be deleted with the DeleteDummyChoiceList() function.

*/

class DLLSPEC ASN1_Choice : public ASN1_Object {
 public:
  struct callbackChoice {
    typedef ASN1_Object* (*callbackFunctionType)(unsigned int i, void* context);

    callbackFunctionType f;
    void* context;
  };

  ASN1_Choice(callbackChoice choiceFromIdx,
              unsigned int maxChoiceIdx,
              const char* name = "",
              const ByteArray& tag = "",
              bool optional = false,
              bool explicitTag = false,
              const ASN1_Choice* defaultChoice = nullptr);
  ~ASN1_Choice();

  unsigned int AvailableChoices() const;
  const ASN1_Object* GetChoiceFromIndex(int pos) const;
  void MakeDummyChoiceList() const;
  void DeleteDummyChoiceList() const;

  ASN1_Object* SetSelectedChoice(int idx);
  ASN1_Object* GetSelectedChoice() const;
  unsigned int GetSelectedChoiceIndex() const;
};

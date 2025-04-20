/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_TreeModel.h"

namespace UI
{
ASN1_ItemModel::ASN1_ItemModel(ASN1_Object *grammar, bool ShowChoiceNodes)
    : myGrammar(grammar)
{
  ASN1_Item *item = BuildModelRecurent(grammar, ShowChoiceNodes);
  this->appendRow(item);
}

ASN1_ItemModelReadOnly::ASN1_ItemModelReadOnly(const ASN1_Object *grammar, bool ShowChoiceNodes)
    : myGrammar(grammar)
{
  ASN1_ItemReadOnly *item = BuildModelRecurent(grammar, ShowChoiceNodes);
  this->appendRow(item);
}

ASN1_Item *ASN1_ItemModel::BuildModelRecurent(ASN1_Object *grammar, bool ShowChoiceNodesInTree)
{
  ASN1_Sequence *seq = dynamic_cast<ASN1_Sequence *>(grammar);
  ASN1_Set *set = dynamic_cast<ASN1_Set *>(grammar);
  ASN1_SequenceOf *seqOf = dynamic_cast<ASN1_SequenceOf *>(grammar);
  ASN1_Choice *choice = dynamic_cast<ASN1_Choice *>(grammar);
  ASN1_Item *item = nullptr;

  if (ShowChoiceNodesInTree || (!ShowChoiceNodesInTree && choice == nullptr))
    if (grammar != nullptr)
      item = new ASN1_Item(grammar->StringExtract().c_str(), grammar);
    else
      return new ASN1_Item("NO GRAMMAR", nullptr);

  if (seq != nullptr)
  {
    for (unsigned int i = 0; i < seq->GetSize(); i++)
      item->appendRow(BuildModelRecurent(seq->GetObjectAt(i), ShowChoiceNodesInTree));
    for (unsigned int i = 0; i < seq->GetExtensibilitySize(); i++)
      item->appendRow(BuildModelRecurent(seq->GetExtensibilityObjectAt(i), ShowChoiceNodesInTree));
  }
  if (set != nullptr)
    for (unsigned int i = 0; i < set->GetSize(); i++)
      item->appendRow(BuildModelRecurent(set->GetObjectAt(i), ShowChoiceNodesInTree));

  if (seqOf != nullptr)
    for (unsigned int i = 0; i < seqOf->GetSequenceOfSize(); i++)
      item->appendRow(BuildModelRecurent(seqOf->GetObjectAt(i), ShowChoiceNodesInTree));

  if (choice != nullptr)
    if (ShowChoiceNodesInTree)
      item->appendRow(BuildModelRecurent(choice->GetSelectedChoice(), ShowChoiceNodesInTree));
    else
      item = BuildModelRecurent(choice->GetSelectedChoice(), ShowChoiceNodesInTree);

  if (item != nullptr)
    item->setEditable(false);
  return item;
}

ASN1_ItemReadOnly *ASN1_ItemModelReadOnly::BuildModelRecurent(const ASN1_Object *grammar, bool ShowChoiceNodesInTree)
{
  const ASN1_Sequence *seq = dynamic_cast<const ASN1_Sequence *>(grammar);
  const ASN1_Set *set = dynamic_cast<const ASN1_Set *>(grammar);
  const ASN1_SequenceOf *seqOf = dynamic_cast<const ASN1_SequenceOf *>(grammar);
  const ASN1_Choice *choice = dynamic_cast<const ASN1_Choice *>(grammar);
  ASN1_ItemReadOnly *item = nullptr;

  if (ShowChoiceNodesInTree || (!ShowChoiceNodesInTree && choice == nullptr))
    if (grammar != nullptr)
      item = new ASN1_ItemReadOnly(grammar->StringExtract().c_str(), grammar);

  if (seq != nullptr)
    for (unsigned int i = 0; i < seq->GetSize(); i++)
      item->appendRow(BuildModelRecurent(seq->GetObjectAt(i), ShowChoiceNodesInTree));

  if (set != nullptr)
    for (unsigned int i = 0; i < set->GetSize(); i++)
      item->appendRow(BuildModelRecurent(set->GetObjectAt(i), ShowChoiceNodesInTree));

  if (seqOf != nullptr)
    for (unsigned int i = 0; i < seqOf->GetSequenceOfSize(); i++)
      item->appendRow(BuildModelRecurent(seqOf->GetObjectAt(i), ShowChoiceNodesInTree));

  if (choice != nullptr)
    if (ShowChoiceNodesInTree)
      item->appendRow(BuildModelRecurent(choice->GetSelectedChoice(), ShowChoiceNodesInTree));
    else
      item = BuildModelRecurent(choice->GetSelectedChoice(), ShowChoiceNodesInTree);

  if (item != nullptr)
    item->setEditable(false);
  return item;
}
} // namespace UI

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once
#include <QStandardItem>
#include "ASN1_includes.h"

namespace UI {
  class ASN1_Item : public QStandardItem {
   public:
    ASN1_Item(QString str, ASN1_Object* grammarObject)
      : QStandardItem(str), myGrammarObject(grammarObject) {}

    ASN1_Object* getGrammarObject() const { return myGrammarObject; }

   private:
    ASN1_Object* myGrammarObject;
  };

  class ASN1_ItemReadOnly : public QStandardItem {
   public:
    ASN1_ItemReadOnly(QString str, const ASN1_Object* grammarObject)
      : QStandardItem(str), myGrammarObject(grammarObject) {}

    const ASN1_Object* getGrammarObject() const {return myGrammarObject; }

   private:
    const ASN1_Object* myGrammarObject;
  };


  class ASN1_ItemModel : public QStandardItemModel {
   public:
    static ASN1_Item* BuildModelRecurent(ASN1_Object* grammar, bool ShowChoiceNodes);
    ASN1_ItemModel(ASN1_Object* grammar, bool ShowChoiceNodes);

   protected:
    ASN1_Object* myGrammar;
  };

  class ASN1_ItemModelReadOnly : public QStandardItemModel {
   public:
    static ASN1_ItemReadOnly* BuildModelRecurent(const ASN1_Object* grammar, bool ShowChoiceNodesInTree);
    ASN1_ItemModelReadOnly(const ASN1_Object* grammar, bool ShowChoiceNodes);

   protected:
    const ASN1_Object* myGrammar;
  };
}

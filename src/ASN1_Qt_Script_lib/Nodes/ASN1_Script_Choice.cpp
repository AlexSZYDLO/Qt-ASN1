/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "ASN1_Script_Choice.h"

ASN1_Script_Choice::ASN1_Script_Choice(QJSValue callback,
                                       int numberOfChoices,
                                       const QString &name,
                                       const QString &tag,
                                       bool optional,
                                       bool explicitTag,
                                       ASN1_Script_Choice *defaultValue)
    : ASN1_Script_Node_Base(name)
    , m_Callback(callback)
{
  ASN1_Choice *def = (defaultValue && !defaultValue->used) ? static_cast<ASN1_Choice *>(defaultValue->getGrammar())
                                                           : nullptr;
  if (def)
    defaultValue->setUsed();

  auto _callback = [](unsigned int idx, void *ptr) -> ASN1_Object * {
    ASN1_Script_Choice *thisPtr = static_cast<ASN1_Script_Choice *>(ptr);
    if (!thisPtr->m_Callback.isCallable())
      return nullptr;

    QJSValueList args;
    args << idx;

    QJSValue ret = thisPtr->m_Callback.call(args);
    if (ret.isError())
      std::cout << ret.toString().toStdString() << std::endl;

    // the underlying ASN1_object automatically deletes the previous chosen value
    // so make sure not to flag it as "unused", otherwise it would get deleted twice
    thisPtr->m_ChosenValue = static_cast<ASN1_Script_Node_Base *>(ret.toQObject());
    thisPtr->m_ChosenValue->setUsed();

    return thisPtr->m_ChosenValue != nullptr ? thisPtr->m_ChosenValue->getGrammar() : nullptr;
  };

  m_GrammarSpe = new ASN1_Choice({_callback, this},
                                 numberOfChoices,
                                 name.toStdString().c_str(),
                                 ByteArray(tag.toStdString().c_str()),
                                 optional,
                                 explicitTag,
                                 def);
  m_GrammarSpeBase = m_GrammarSpe;
}

ASN1_Choice *ASN1_Script_Choice::getGrammar() const
{
  return m_GrammarSpe;
}

QObject *ASN1_Script_Choice::setSelectedChoice(int idx)
{
  m_GrammarSpe->SetSelectedChoice(idx);
  return m_ChosenValue;
}

QObject *ASN1_Script_Choice::getSelectedChoice() const
{
  return m_ChosenValue;
}

unsigned int ASN1_Script_Choice::getSelectedChoiceIndex() const
{
  return m_GrammarSpe->GetSelectedChoiceIndex();
}

void ASN1_Script_Choice::clearDynamicData()
{
  setSelectedChoice(0);
}

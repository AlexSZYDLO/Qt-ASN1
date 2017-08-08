/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#include "ASNHighlighter.h"

ASNHighlighter::ASNHighlighter(QTextDocument* parent)
  : QSyntaxHighlighter(parent) {
  HighlightingRule rule;

  QTextCharFormat keywordFormat;
  QTextCharFormat quotationDoubleFormat;
  QTextCharFormat quotationSingleFormat;
  QTextCharFormat singleLineCommentFormat;

  keywordFormat.setForeground(Qt::darkBlue);
  keywordFormat.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "\\bDEFINITIONS\\b" << "\\bAUTOMATIC TAGS\\b" << "\\bIMPLICIT TAGS\\b" << "\\bEXPLICIT TAGS\\b"
                  << "\\bEXTENSIBILITY IMPLIED\\b" << "\\bBEGIN\\b" << "\\bEND\\b" << "\\bOPTIONAL\\b"
                  << "\\bEXPLICIT\\b" <<  "\\bIMPLICIT\\b" << "\\bUNIVERSAL\\b"
                  << "\\bCONTEXT SPECIFIC\\b" << "\\bPRIVATE\\b" << "\\bAPPLICATION\\b"
                  << "\\bBIT STRING\\b" <<  "\\bBOOLEAN\\b" << "\\bENUMERATED\\b"
                  << "\\bIA5String\\b" << "\\bINTEGER\\b" << "\\bNULL\\b"
                  << "\\bOBJECT IDENTIFIER\\b" <<  "\\bOCTET STRING\\b" << "\\bREAL\\b"
                  << "\\bUTCTime\\b" << "\\bUTF8String\\b" << "\\bSEQUENCE\\b" <<  "\\bSEQUENCE OF\\b" << "\\bCHOICE\\b"
                  << "\\bSET\\b";

  foreach (const QString& pattern, keywordPatterns) {
    rule.pattern = QRegExp(pattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);
  }

  quotationDoubleFormat.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("\".*\"");
  rule.format = quotationDoubleFormat;
  highlightingRules.append(rule);

  quotationSingleFormat.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("\'.*\'");
  rule.format = quotationSingleFormat;
  highlightingRules.append(rule);

  singleLineCommentFormat.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("--[^\n]*");
  rule.format = singleLineCommentFormat;
  highlightingRules.append(rule);

  multiLineCommentFormat.setForeground(Qt::darkGreen);

  commentStartExpression = QRegExp("/\\*");
  commentEndExpression = QRegExp("\\*/");
}

void ASNHighlighter::highlightBlock(const QString& text) {
  foreach (const HighlightingRule& rule, highlightingRules) {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0) {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = expression.indexIn(text, index + length);
    }
  }
  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
    startIndex = commentStartExpression.indexIn(text);

  while (startIndex >= 0) {
    int endIndex = commentEndExpression.indexIn(text, startIndex);
    int commentLength;
    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    }
    else {
      commentLength = endIndex - startIndex
                      + commentEndExpression.matchedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
  }
}

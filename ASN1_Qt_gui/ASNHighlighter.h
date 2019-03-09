/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class ASNHighlighter : public QSyntaxHighlighter {
  Q_OBJECT

 public:
  ASNHighlighter(QTextDocument* parent = 0);

 protected:
  void highlightBlock(const QString& text) override;

 private:
  struct HighlightingRule {
    QRegExp pattern;
    QTextCharFormat format;
  };
  QVector<HighlightingRule> highlightingRules;

  QRegExp commentStartExpression;
  QRegExp commentEndExpression;

  QTextCharFormat multiLineCommentFormat;

};

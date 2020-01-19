/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_GRAMMAR_PARSER_H_INCLUDED
# define YY_YY_GRAMMAR_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _Number = 258,
    _Int = 259,
    _ModuleID = 260,
    _VarID = 261,
    _BEGIN = 262,
    _END = 263,
    _EXPLICIT = 264,
    _IMPLICIT = 265,
    _AUTOMATIC = 266,
    _TAG = 267,
    _EXTENSIBILITY = 268,
    _IMPLIED = 269,
    _DEFINITIONS = 270,
    _UNIVERSAL = 271,
    _APPLICATION = 272,
    _CONTEXTSPECIFIC = 273,
    _PRIVATE = 274,
    _OPTIONAL = 275,
    _SEQUENCE = 276,
    _SET = 277,
    _SEQUENCEOF = 278,
    _CHOICE = 279,
    _BITSTRING = 280,
    _BOOLEAN = 281,
    _ENUM = 282,
    _IA5STRING = 283,
    _INTEGER = 284,
    _NULL = 285,
    _OBJECTID = 286,
    _OCTETSTRING = 287,
    _REAL = 288,
    _UTCTIME = 289,
    _UTF8STRING = 290,
    _OPENBRACKET = 291,
    _CLOSEBRACKET = 292,
    _COMMA_ = 293,
    _ASSIGN = 294,
    _OPENSQBRACKET = 295,
    _CLOSESQBRACKET = 296,
    _EXTENSIBILESEQ = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 31 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1921  */

  double d;
  int i;
  std::string* name;
  bool opt;

  eNodeType nodeType;
  eTagClass tagClass;
  eTagForm tagForm;
  VarModule vMod;
  Tag tag;
  Explicity explImpl;

#line 115 "grammar/Parser.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_PARSER_H_INCLUDED  */

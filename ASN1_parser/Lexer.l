%{
/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include "../global.h"
#include <iostream>
#include <string>
#include "Parser.h"
%}


%option outfile="grammar/Lexer.cpp"
%option header-file="grammar/Lexer.h"

%option never-interactive
%option nounistd
%option noyywrap
%option yylineno

/*
%option warn nodefault
%option never-interactive nounistd
%option bison-bridge
*/

%x COMMENT

white           [ \t\n]+

digit           [0-9]
integ           {digit}+
exp             [eE][+-]?{integ}
real            {integ}("."{integ})?{exp}?

MOD_ID			    [A-Z][a-zA-Z0-9_-]*
VAR_ID			    [a-z][a-zA-Z0-9_-]*

sl_comm         \-\-.*\n
sl_comm2        \/\/.*\n

%%

"/*"                      BEGIN(COMMENT);
<COMMENT>"*/"             BEGIN(INITIAL);
<COMMENT>.|"\n"


{white}           { /* ignore */ }
{sl_comm}         { /*single line comment*/ }
{sl_comm2}        { /*single line comment, second method*/ }

{integ}           { yylval.i = ConvertToInt(yytext);    return _Int;    }
{real}            { yylval.d = ConvertToDouble(yytext); return _Number; }


"EXPLICIT"        return _EXPLICIT;
"IMPLICIT"        return _IMPLICIT;
"AUTOMATIC"       return _AUTOMATIC;
"TAGS"            return _TAG;
"EXTENSIBILITY"   return _EXTENSIBILITY;
"IMPLIED"         return _IMPLIED;
"DEFINITIONS"     return _DEFINITIONS;
"BEGIN"           return(_BEGIN);
"END"             return(_END);

"UNIVERSAL"         return(_UNIVERSAL);
"APPLICATION"       return(_APPLICATION);
"CONTEXT SPECIFIC"  return(_CONTEXTSPECIFIC);
"PRIVATE"           return(_PRIVATE);

"OPTIONAL"          return(_OPTIONAL);

"SEQUENCE OF"     return(_SEQUENCEOF);
"SEQUENCE"        return(_SEQUENCE);
"SET"             return(_SET);
"CHOICE"          return(_CHOICE);

"BIT STRING"      return(_BITSTRING);
"BOOLEAN"         return(_BOOLEAN);
"ENUM"            return(_ENUM);
"IA5String"      return(_IA5STRING);
"INTEGER"         return(_INTEGER);
"NULL"            return(_NULL);
"OBJECT IDENTIFIER"  return(_OBJECTID);
"OCTET STRING"    return(_OCTETSTRING);
"REAL"            return(_REAL);
"UTC TIME"        return(_UTCTIME);
"UTF8String"     return(_UTF8STRING);

{MOD_ID}		      { yylval.name = stringAssign(yytext); return _ModuleID; }
{VAR_ID}		      { yylval.name = stringAssign(yytext); return _VarID; }

"::="		          return(_ASSIGN);
"{"               return(_OPENBRACKET);
"}"               return(_CLOSEBRACKET);
"["               return(_OPENSQBRACKET);
"]"               return(_CLOSESQBRACKET);
","               return(_COMMA_);
"..."             return(_EXTENSIBILESEQ);

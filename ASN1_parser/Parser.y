%{
/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include <iostream>
#include <string>
#include "../global.h"
#include "../generator.h"

using namespace std;

#define YYERROR_VERBOSE
#define YY_INPUT(buf,result,max_size)  {\
  result = GetNextChar(buf, max_size); \
  if (  result <= 0  ) \
    result = YY_NULL; \
}

extern int yylineno;

int yylex(void);
void yyerror(const char *s);

%}

%output  "grammar/Parser.cpp"
%defines "grammar/Parser.h"


%union {
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
}

%token <d> _Number
%token <i> _Int
%token <name> _ModuleID
%token <name> _VarID

%token _BEGIN _END
%token _EXPLICIT _IMPLICIT _AUTOMATIC _TAG _EXTENSIBILITY _IMPLIED _DEFINITIONS
%token _UNIVERSAL _APPLICATION _CONTEXTSPECIFIC _PRIVATE _OPTIONAL

%token <nodeType> _SEQUENCE _SET _SEQUENCEOF _CHOICE
%token <nodeType> _BITSTRING _BOOLEAN _ENUM _IA5STRING _INTEGER _NULL _OBJECTID _OCTETSTRING _REAL _UTCTIME _UTF8STRING

%token _OPENBRACKET _CLOSEBRACKET _COMMA_ _ASSIGN _OPENSQBRACKET _CLOSESQBRACKET _EXTENSIBILESEQ

%type <nodeType> ModuleDef
%type <nodeType> ModuleTypeSeqSet

%type <nodeType> ASN1_Type
%type <opt>      Optional
%type <tagClass> TagClass
%type <vMod>     UniqueModule
%type <tag>      TagField
%type <explImpl> Explicit

%start Grammar
%%


Grammar:
  /* */
  | _ModuleID _DEFINITIONS GlobalOptions _ASSIGN _BEGIN ModuleList _END { gGen->SetGrammarName(*$1); delete $1; gGen->GrammarEnd(); }
  | ModuleList { gGen->GrammarEnd(); }
    ;


/* ---------------------------------Grammar gGeneric options-----------------------------------*/
GlobalOptions:
   /* nothing */
   | GlobalOptionList
   ;
GlobalOptionList:
   Opt
   | GlobalOptionList Opt
   ;
Opt:
  GlobalOptSeq
  | GlobalOptTags
  ;
GlobalOptSeq:
  _EXTENSIBILITY _IMPLIED     { gGen->SetExtensibilityImplied(); }
  ;
GlobalOptTags:
  _EXPLICIT _TAG       { gGen->SetExplicitTags(); }
  | _IMPLICIT _TAG     { gGen->SetImplicitTags(); }
  | _AUTOMATIC _TAG    { gGen->SetAutoTags();     }
  ;
/* -------------------------------------------------------------------------------------------*/


ModuleList:
  Module
  | ModuleList Module
  ;

Module:
    _ModuleID _ASSIGN ModuleDef   { gGen->AddModule(*$1, $3); delete $1; }
    ;

UniqueModule:
  ModuleTypeSeqSet   { gGen->NewModule(); } _OPENBRACKET VariableListSeqSet _CLOSEBRACKET   { $$ = {gGen->AddUniqueModule($1), $1}; }
  | _CHOICE          { gGen->NewModule(); } _OPENBRACKET VariableList _CLOSEBRACKET         { $$ = {gGen->AddUniqueModule(cChoice), cChoice}; }
  | _SEQUENCEOF      { gGen->NewModule(); } SeqOfConstraint VariableType                    { $$ = {gGen->AddUniqueModule(cSequenceOf), cSequenceOf}; }
  ;

ModuleDef:
  ModuleTypeSeqSet        { gGen->NewModule(); } _OPENBRACKET VariableListSeqSet _CLOSEBRACKET   { $$ = $1; }
  | _CHOICE               { gGen->NewModule(); } _OPENBRACKET VariableList _CLOSEBRACKET         { $$ = cChoice; }
  | _SEQUENCEOF           { gGen->NewModule(); } SeqOfConstraint VariableType                    { $$ = cSequenceOf; }
  | ASN1_Type Constraint  { gGen->NewModule(); gGen->AddTempVariable("", $1, false); $$ = $1; }
  ;

SeqOfConstraint:
  /* (SIZE (x..y) )
  |  (SIZE (x) )
  */
  ;

ModuleTypeSeqSet:
  _SEQUENCE       { $$ = cSequence;   }
  | _SET          { $$ = cSet;        }
  ;

VariableListSeqSet:
  /* */
  | Variable
  | VariableListSeqSet _COMMA_ Variable
  | VariableListSeqSet _COMMA_ _EXTENSIBILESEQ { gGen->SetSequenceExtensibility(); }
  ;

VariableList:
  Variable
  | VariableList _COMMA_ Variable
  ;

Variable:
  _VarID TagField VariableType Optional
  {
    gGen->SetLastVariableName(*$1);
    gGen->SetLastVariableTag($2);
    gGen->SetLastVarOptional($4);
    delete $1;
  }
  ;

Optional:
  /**/        { $$ = false; }
  | _OPTIONAL { $$ = true;  }
  ;

VariableType:
  ASN1_Type Constraint    { gGen->AddTempVariable("", $1, false);                            }
  | UniqueModule          { gGen->AddTempVariable(*$1.name, $1.type, false); delete $1.name; }
  | _ModuleID             { gGen->AddTempVariable(*$1, cNull, true); delete $1;              }
  ;

TagField:
  /* */  { $$ = {true, cTagClassUniversal, 0, cIgnored}; }
  | _OPENSQBRACKET TagClass _Int _CLOSESQBRACKET Explicit   { $$ = {false, $2, $3, $5}; }
  ;

Explicit:
  /* */         { $$ = cIgnored;  }
  | _EXPLICIT   { $$ = cExplicit; }
  | _IMPLICIT   { $$ = cImplicit; }
  ;

TagClass:
  /**/                { $$ = cTagClassContextSpecific; }
  | _UNIVERSAL        { $$ = cTagClassUniversal;       }
  | _APPLICATION      { $$ = cTagClassApplication;     }
  | _CONTEXTSPECIFIC  { $$ = cTagClassContextSpecific; }
  | _PRIVATE          { $$ = cTagClassPrivate;         }
  ;

Constraint: /**/;

ASN1_Type:
  _BOOLEAN        { $$ = cBoolean;     }
  | _BITSTRING    { $$ = cBitString;   }
  | _ENUM         { $$ = cEnumerated;  }
  | _IA5STRING    { $$ = cIA5String;   }
  | _INTEGER      { $$ = cInteger;     }
  | _NULL         { $$ = cNull;        }
  | _OBJECTID     { $$ = cObjectID;    }
  | _OCTETSTRING  { $$ = cOctetString; }
  | _REAL         { $$ = cReal;        }
  | _UTF8STRING   { $$ = cUTF8String;  }
  | _UTCTIME      { $$ = cUTCTime;     }
  ;

%%

void yyerror(const char *s) {
    errorLog(string (s) + ". Line:" + to_string(yylineno) + '\n');
    //cout << string(s) << ". Line:" << yylineno << endl;
}




/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:337  */

/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#include <iostream>
#include <string>
#include "../global.h"
#include "../Generator.h"

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


#line 96 "grammar/Parser.cpp" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Parser.h".  */
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
#line 31 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:352  */

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

#line 196 "grammar/Parser.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   89

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

#define YYUNDEFTOK  2
#define YYMAXUTOK   297

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    73,    73,    75,    76,    81,    83,    86,    87,    90,
      91,    94,    97,    98,    99,   105,   106,   110,   114,   114,
     115,   115,   116,   116,   120,   120,   121,   121,   122,   122,
     123,   126,   133,   134,   137,   139,   140,   141,   145,   146,
     150,   160,   161,   165,   166,   167,   171,   172,   176,   177,
     178,   182,   183,   184,   185,   186,   189,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_Number", "_Int", "_ModuleID", "_VarID",
  "_BEGIN", "_END", "_EXPLICIT", "_IMPLICIT", "_AUTOMATIC", "_TAG",
  "_EXTENSIBILITY", "_IMPLIED", "_DEFINITIONS", "_UNIVERSAL",
  "_APPLICATION", "_CONTEXTSPECIFIC", "_PRIVATE", "_OPTIONAL", "_SEQUENCE",
  "_SET", "_SEQUENCEOF", "_CHOICE", "_BITSTRING", "_BOOLEAN", "_ENUM",
  "_IA5STRING", "_INTEGER", "_NULL", "_OBJECTID", "_OCTETSTRING", "_REAL",
  "_UTCTIME", "_UTF8STRING", "_OPENBRACKET", "_CLOSEBRACKET", "_COMMA_",
  "_ASSIGN", "_OPENSQBRACKET", "_CLOSESQBRACKET", "_EXTENSIBILESEQ",
  "$accept", "Grammar", "GlobalOptions", "GlobalOptionList", "Opt",
  "GlobalOptSeq", "GlobalOptTags", "ModuleList", "Module", "UniqueModule",
  "$@1", "$@2", "$@3", "ModuleDef", "$@4", "$@5", "$@6", "SeqOfConstraint",
  "ModuleTypeSeqSet", "VariableListSeqSet", "VariableList", "Variable",
  "Optional", "VariableType", "TagField", "Explicit", "TagClass",
  "Constraint", "ASN1_Type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF -69

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-69)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -1,    -4,     6,    11,   -69,     4,    28,   -69,   -21,   -69,
      26,    56,    58,    55,    32,     4,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,    65,   -69,   -69,    37,    38,   -69,    11,    -2,    69,
      69,     0,   -69,   -69,   -69,   -69,   -69,   -69,   -69,    36,
     -28,   -69,     7,   -69,   -69,   -69,    41,    42,   -69,    24,
      -2,   -69,    69,   -69,    -5,    -2,    69,    69,   -69,   -69,
     -69,   -69,    75,    60,   -69,   -69,   -69,   -69,     9,    27,
      40,   -69,   -69,   -69,   -69,    57,   -69,   -69,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     4,    15,     5,     0,     1,     0,    16,
       0,     0,     0,     0,     0,     6,     7,     9,    10,    32,
      33,    28,    26,    58,    57,    59,    60,    61,    62,    63,
      64,    65,    67,    66,    17,    24,    56,    12,    13,    14,
      11,     0,     8,    31,     0,     0,    30,     0,     0,     0,
      34,     0,    45,    22,    20,    44,    18,    29,    56,    46,
       0,    38,     0,    35,     3,    31,     0,     0,    43,    51,
       0,    27,     0,    25,     0,     0,     0,    34,    52,    53,
      54,    55,     0,    41,    39,    37,    36,    23,     0,     0,
       0,    42,    40,    21,    19,    48,    49,    50,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,   -69,    67,   -69,   -69,    39,    -3,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,    18,    78,     8,
      12,   -38,   -69,   -68,   -69,   -69,   -69,    29,    83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    14,    15,    16,    17,    18,     3,     4,    55,
      67,    66,    65,    34,    45,    44,    43,    48,    56,    62,
      60,    61,    92,    57,    70,    98,    82,    46,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    59,    83,    52,     1,     8,     7,    87,    64,    71,
      72,     5,    63,    10,    11,    12,     8,    13,     6,    19,
      20,    53,    54,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    84,     6,    86,    85,    37,    63,
      78,    79,    80,    81,    73,    74,    93,    72,     9,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    94,    74,    96,    97,    38,    40,
      39,    41,    47,    49,    50,    59,    69,    76,    77,    90,
      91,    95,    42,    75,    35,    89,    51,    68,    88,    36
};

static const yytype_uint8 yycheck[] =
{
       3,     6,    70,     5,     5,     5,     0,    75,     8,    37,
      38,    15,    50,     9,    10,    11,     5,    13,    39,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    72,    39,    74,    42,    12,    77,
      16,    17,    18,    19,    37,    38,    37,    38,    51,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    37,    38,     9,    10,    12,    14,
      12,    39,     7,    36,    36,     6,    40,    36,    36,     4,
      20,    41,    15,    65,     6,    77,    47,    58,    76,     6
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    44,    50,    51,    15,    39,     0,     5,    51,
       9,    10,    11,    13,    45,    46,    47,    48,    49,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    56,    61,    71,    12,    12,    12,
      14,    39,    47,    59,    58,    57,    70,     7,    60,    36,
      36,    50,     5,    23,    24,    52,    61,    66,    71,     6,
      63,    64,    62,    64,     8,    55,    54,    53,    70,    40,
      67,    37,    38,    37,    38,    60,    36,    36,    16,    17,
      18,    19,    69,    66,    64,    42,    64,    66,    63,    62,
       4,    20,    65,    37,    37,    41,     9,    10,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    44,    45,    45,    46,    46,    47,
      47,    48,    49,    49,    49,    50,    50,    51,    53,    52,
      54,    52,    55,    52,    57,    56,    58,    56,    59,    56,
      56,    60,    61,    61,    62,    62,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    69,    69,    69,    70,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     7,     1,     0,     1,     1,     2,     1,
       1,     2,     2,     2,     2,     1,     2,     3,     0,     5,
       0,     5,     0,     4,     0,     5,     0,     5,     0,     4,
       2,     0,     1,     1,     0,     1,     3,     3,     1,     3,
       4,     0,     1,     2,     1,     1,     0,     5,     0,     1,
       1,     0,     1,     1,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 75 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->SetGrammarName(*(yyvsp[-6].name)); delete (yyvsp[-6].name); gGen->GrammarEnd(); }
#line 1361 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 76 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->GrammarEnd(); }
#line 1367 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 94 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->SetExtensibilityImplied(); }
#line 1373 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 97 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->SetExplicitTags(); }
#line 1379 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 98 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->SetImplicitTags(); }
#line 1385 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 99 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->SetAutoTags();     }
#line 1391 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 110 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->AddModule(*(yyvsp[-2].name), (yyvsp[0].nodeType)); delete (yyvsp[-2].name); }
#line 1397 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 114 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); }
#line 1403 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 114 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.vMod) = {gGen->AddUniqueModule((yyvsp[-4].nodeType)), (yyvsp[-4].nodeType)}; }
#line 1409 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 115 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); }
#line 1415 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 115 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.vMod) = {gGen->AddUniqueModule(cChoice), cChoice}; }
#line 1421 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 116 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); }
#line 1427 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 116 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.vMod) = {gGen->AddUniqueModule(cSequenceOf), cSequenceOf}; }
#line 1433 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 120 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); }
#line 1439 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 120 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = (yyvsp[-4].nodeType); }
#line 1445 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 121 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); }
#line 1451 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 121 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cChoice; }
#line 1457 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 122 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); }
#line 1463 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 122 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cSequenceOf; }
#line 1469 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 123 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->NewModule(); gGen->AddTempVariable("", (yyvsp[-1].nodeType), false); (yyval.nodeType) = (yyvsp[-1].nodeType); }
#line 1475 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 133 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cSequence;   }
#line 1481 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 134 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cSet;        }
#line 1487 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 141 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->SetSequenceExtensibility(); }
#line 1493 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 151 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    {
    gGen->SetLastVariableName(*(yyvsp[-3].name));
    gGen->SetLastVariableTag((yyvsp[-2].tag));
    gGen->SetLastVarOptional((yyvsp[0].opt));
    delete (yyvsp[-3].name);
  }
#line 1504 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 160 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.opt) = false; }
#line 1510 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 161 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.opt) = true;  }
#line 1516 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 165 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->AddTempVariable("", (yyvsp[-1].nodeType), false);                            }
#line 1522 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 166 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->AddTempVariable(*(yyvsp[0].vMod).name, (yyvsp[0].vMod).type, false); delete (yyvsp[0].vMod).name; }
#line 1528 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 167 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { gGen->AddTempVariable(*(yyvsp[0].name), cNull, true); delete (yyvsp[0].name);              }
#line 1534 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 171 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tag) = {true, cTagClassUniversal, 0, cIgnored}; }
#line 1540 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 172 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tag) = {false, (yyvsp[-3].tagClass), (yyvsp[-2].i), (yyvsp[0].explImpl)}; }
#line 1546 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 176 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.explImpl) = cIgnored;  }
#line 1552 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 177 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.explImpl) = cExplicit; }
#line 1558 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 178 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.explImpl) = cImplicit; }
#line 1564 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 182 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tagClass) = cTagClassContextSpecific; }
#line 1570 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 183 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tagClass) = cTagClassUniversal;       }
#line 1576 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 184 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tagClass) = cTagClassApplication;     }
#line 1582 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 185 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tagClass) = cTagClassContextSpecific; }
#line 1588 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 186 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.tagClass) = cTagClassPrivate;         }
#line 1594 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 192 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cBoolean;     }
#line 1600 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 193 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cBitString;   }
#line 1606 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 194 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cEnumerated;  }
#line 1612 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 195 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cIA5String;   }
#line 1618 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 196 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cInteger;     }
#line 1624 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 197 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cNull;        }
#line 1630 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 198 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cObjectID;    }
#line 1636 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 199 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cOctetString; }
#line 1642 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 200 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cReal;        }
#line 1648 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 201 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cUTF8String;  }
#line 1654 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 202 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1652  */
    { (yyval.nodeType) = cUTCTime;     }
#line 1660 "grammar/Parser.cpp" /* yacc.c:1652  */
    break;


#line 1664 "grammar/Parser.cpp" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 205 "/home/alexandre/Dev/q-asn1/ASN1_parser/Parser.y" /* yacc.c:1918  */


void yyerror(const char *s) {
    errorLog(string (s) + ". Line:" + to_string(yylineno) + '\n');
    //cout << string(s) << ". Line:" << yylineno << endl;
}




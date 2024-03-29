
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "projet_compilation.y"

#include <stdio.h> //FILE
#include <stdlib.h> //atoi
#include <string.h>
  extern int yylex(void);
  extern int yyleng;
  void yyerror(char *s);
  extern FILE* yyin;
  extern FILE* yyout;
  extern FILE* yyerr;
  int nbcol = 0;
  int nbseparateur = 0;
  int  numberInLine = 1;
  float  sumLine = 0;
  int  colonneCourant = 0;
  int* numberInColonne;
  float* sumColonne;
  char * positionnement = "center";
  
  void ajouteColonne(char* chaine,char* position, float num);
  void redigeOption( int border, char* pos);
  char* redigeColonne(char* texte, char* pos, int multicolumn, int colspan);
  char* redigeColonneReel(double val, char* pos, int multicolumn, int colspan);
  char* redigeColonneEntier(int val, char* pos, int multicolumn, int colspan);
  void initialiseTabBool(int* tab, int size);
  void initialiseTabReel(float* tab, int size);
  void changeTab(int* tab, int deb, int end);
  void sommeColonne(char* chaine, char* position, int* appliqueSomme, float* toutesSommes, int nbFois);
 

/* Line 189 of yacc.c  */
#line 104 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEB = 258,
     DOC = 259,
     DC = 260,
     GFX = 261,
     TABLE = 262,
     TABULAR = 263,
     CAPTION = 264,
     OPTION_T = 265,
     FUSION = 266,
     TRAIT_HOR = 267,
     SEPAR_COL = 268,
     FIN_LIGNE = 269,
     SEPAR = 270,
     FIN = 271,
     ACCOL_G = 272,
     ACCOL_D = 273,
     ANTISLASH = 274,
     CROCH_G = 275,
     CROCH_D = 276,
     ENTIER = 277,
     REEL = 278,
     MOT = 279,
     SPACE = 280
   };
#endif
/* Tokens.  */
#define DEB 258
#define DOC 259
#define DC 260
#define GFX 261
#define TABLE 262
#define TABULAR 263
#define CAPTION 264
#define OPTION_T 265
#define FUSION 266
#define TRAIT_HOR 267
#define SEPAR_COL 268
#define FIN_LIGNE 269
#define SEPAR 270
#define FIN 271
#define ACCOL_G 272
#define ACCOL_D 273
#define ANTISLASH 274
#define CROCH_G 275
#define CROCH_D 276
#define ENTIER 277
#define REEL 278
#define MOT 279
#define SPACE 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 34 "projet_compilation.y"
 char* str; double reel; int entier;


/* Line 214 of yacc.c  */
#line 194 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 206 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   131

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    12,    22,    27,    34,    40,    45,    55,
      64,    69,    70,    76,    81,    87,    88,    92,    96,    99,
     102,   104,   106,   111,   115,   119,   122,   124,   130,   134,
     136,   138,   140,   151,   162,   173,   176,   178,   181,   189,
     196,   200,   203
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      27,     0,    -1,    28,    46,    30,    37,    31,    46,    29,
      46,    -1,     5,    46,     6,    46,     3,    17,     4,    18,
      46,    -1,    16,    17,     4,    18,    -1,    32,    34,     3,
      17,     8,    18,    -1,    32,     3,    17,     8,    18,    -1,
       3,    17,     8,    18,    -1,    16,    17,     8,    18,    46,
      35,    46,    36,    33,    -1,     3,    17,     7,    18,    20,
      24,    21,    46,    -1,    16,    17,     7,    18,    -1,    -1,
       3,    17,    24,    18,    46,    -1,    16,    17,    24,    18,
      -1,     9,    17,    44,    18,    46,    -1,    -1,    38,    46,
      40,    -1,    17,    39,    18,    -1,    15,    39,    -1,    24,
      39,    -1,    15,    -1,    24,    -1,    41,    14,    46,    40,
      -1,    41,    14,    46,    -1,    12,    46,    40,    -1,    12,
      46,    -1,    42,    -1,    46,    43,    46,    13,    42,    -1,
      46,    43,    46,    -1,    44,    -1,    22,    -1,    23,    -1,
      11,    17,    22,    18,    17,    39,    18,    17,    44,    18,
      -1,    11,    17,    22,    18,    17,    39,    18,    17,    22,
      18,    -1,    11,    17,    22,    18,    17,    39,    18,    17,
      23,    18,    -1,    45,    44,    -1,    45,    -1,    24,    46,
      -1,    17,    19,    24,    25,    44,    18,    46,    -1,    19,
      24,    17,    44,    18,    46,    -1,    19,    24,    46,    -1,
      46,    25,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    69,    69,    72,    75,    78,    79,    80,    83,    86,
      89,    90,    93,    96,    99,   100,   107,   119,   127,   128,
     129,   130,   134,   135,   136,   137,   144,   157,   158,   163,
     167,   171,   175,   179,   184,   191,   192,   198,   199,   200,
     201,   204,   205
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEB", "DOC", "DC", "GFX", "TABLE",
  "TABULAR", "CAPTION", "OPTION_T", "FUSION", "TRAIT_HOR", "SEPAR_COL",
  "FIN_LIGNE", "SEPAR", "FIN", "ACCOL_G", "ACCOL_D", "ANTISLASH",
  "CROCH_G", "CROCH_D", "ENTIER", "REEL", "MOT", "SPACE", "$accept",
  "fichier", "debLatex", "endLatex", "init", "end", "tabledeb", "tableend",
  "posdeb", "posend", "caption", "tableau", "options", "option", "lignes",
  "ligne", "colonnes", "colonne", "phrase", "mots", "blancs", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    27,    28,    29,    30,    30,    30,    31,    32,
      33,    33,    34,    35,    36,    36,    37,    38,    39,    39,
      39,    39,    40,    40,    40,    40,    41,    42,    42,    43,
      43,    43,    43,    43,    43,    44,    44,    45,    45,    45,
      45,    46,    46
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     9,     4,     6,     5,     4,     9,     8,
       4,     0,     5,     4,     5,     0,     3,     3,     2,     2,
       1,     1,     4,     3,     3,     2,     1,     5,     3,     1,
       1,     1,    10,    10,    10,     2,     1,     2,     7,     6,
       3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    42,     0,    42,     0,     1,     0,    42,    41,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,    20,    21,     0,     0,    42,    42,     0,     0,
       0,     0,     7,    18,    19,    17,     0,     0,    42,    16,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    42,    42,     0,     0,     0,    30,    31,    42,    42,
      29,    36,     6,    42,     0,    42,     0,    42,     0,     2,
      24,    42,     0,     0,    42,    37,    28,    35,    12,     5,
       3,    42,     0,     0,    22,     0,     0,     0,    40,    42,
       9,     0,    42,     4,     0,     0,     0,    27,     0,    15,
       0,     0,    42,     0,     0,    11,     0,    42,    39,    13,
       0,     0,     8,     0,    38,     0,     0,     0,    42,     0,
       0,     0,     0,    14,    10,    33,    34,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    50,    10,    26,    11,   112,    18,    92,
     105,    15,    16,    24,    39,    40,    41,    59,    60,    61,
      42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -57
static const yytype_int8 yypact[] =
{
       9,   -57,    17,   -57,     5,   -57,    -2,   -57,   -57,    24,
      35,    16,     4,    64,     3,    20,   -57,    42,    71,    50,
      57,    58,     3,     3,    59,    61,   -57,    31,     2,    62,
      78,    63,   -57,   -57,   -57,   -57,    76,    -4,   -57,   -57,
      72,   -57,    23,    67,    69,    80,    74,    65,    75,    73,
     -57,    -3,   -57,    77,    79,    81,   -57,   -57,   -57,   -57,
     -57,    36,   -57,   -57,    82,   -57,    83,   -57,    91,    84,
     -57,     8,    85,    86,    94,    84,    25,   -57,    84,   -57,
      84,   -57,    19,    90,   -57,    95,    87,    36,    84,   -57,
      84,    97,   -57,   -57,    98,    36,   100,   -57,    92,     7,
       3,   101,   -57,   102,   104,   106,   105,   -57,    84,   -57,
      36,   107,   -57,   108,    84,   109,    89,    46,   -57,   110,
     111,   112,   113,    84,   -57,   -57,   -57,   -57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -19,   -43,   -57,    10,   -57,   -56,   -57,
      -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -26
static const yytype_int8 yytable[] =
{
       4,     9,     6,    33,    34,    77,    12,    19,    70,    38,
      43,     7,    49,   -25,     1,    27,   104,     5,    22,    17,
      38,     8,     8,     8,   -23,    37,    44,    23,    84,     8,
       8,    96,     8,     8,    53,    91,    25,    51,    89,   101,
      54,    13,    55,    38,     8,    56,    57,    58,     8,    69,
       8,    71,    14,    54,   115,    55,     8,    75,    76,    28,
      58,   122,    78,    54,    80,    55,    82,    30,   120,   121,
      58,    20,    21,    88,    29,    31,    32,    35,    36,    45,
      90,   106,    46,    47,    48,    62,    52,    63,    64,    66,
      68,    99,    65,    67,    72,    83,   119,     0,    73,    97,
      79,   108,     0,     0,    81,    74,   114,    85,    93,     8,
      86,    87,    95,    94,    98,   100,   103,   123,   102,   107,
     109,   110,   111,   113,   116,   117,     0,   118,   124,   125,
     126,   127
};

static const yytype_int8 yycheck[] =
{
       1,     3,     3,    22,    23,    61,     7,     3,    51,    12,
       8,     6,    16,    16,     5,    16,     9,     0,    15,     3,
      12,    25,    25,    25,    16,    26,    24,    24,    71,    25,
      25,    87,    25,    25,    11,    16,    16,    38,    13,    95,
      17,    17,    19,    12,    25,    22,    23,    24,    25,    50,
      25,    52,    17,    17,   110,    19,    25,    58,    59,    17,
      24,   117,    63,    17,    65,    19,    67,    17,    22,    23,
      24,     7,     8,    74,     3,    18,    18,    18,    17,    17,
      81,   100,     4,    20,     8,    18,    14,    18,     8,    24,
      17,    92,    18,    18,    17,     4,     7,    -1,    19,    89,
      18,   102,    -1,    -1,    21,    24,   107,    22,    18,    25,
      24,    17,    25,    18,    17,    17,    24,   118,    18,    18,
      18,    17,    16,    18,    17,    17,    -1,    18,    18,    18,
      18,    18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    27,    28,    46,     0,    46,     6,    25,     3,
      30,    32,    46,    17,    17,    37,    38,     3,    34,     3,
       7,     8,    15,    24,    39,    16,    31,    46,    17,     3,
      17,    18,    18,    39,    39,    18,    17,    46,    12,    40,
      41,    42,    46,     8,    24,    17,     4,    20,     8,    16,
      29,    46,    14,    11,    17,    19,    22,    23,    24,    43,
      44,    45,    18,    18,     8,    18,    24,    18,    17,    46,
      40,    46,    17,    19,    24,    46,    46,    44,    46,    18,
      46,    21,    46,     4,    40,    22,    24,    17,    46,    13,
      46,    16,    35,    18,    18,    25,    44,    42,    17,    46,
      17,    44,    18,    24,     9,    36,    39,    18,    46,    18,
      17,    16,    33,    18,    46,    44,    17,    17,    18,     7,
      22,    23,    44,    46,    18,    18,    18,    18
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
	    /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 69 "projet_compilation.y"
    {fprintf(yyout,"</html>");}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 78 "projet_compilation.y"
    { fprintf(yyout, "<table ");}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 79 "projet_compilation.y"
    { fprintf(yyout, "<table ");}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 80 "projet_compilation.y"
    { fprintf(yyout, "<table ");}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 93 "projet_compilation.y"
    {positionnement = (yyvsp[(3) - (5)].str);}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 99 "projet_compilation.y"
    {fprintf(yyout,"%s",(yyvsp[(3) - (5)].str));}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 107 "projet_compilation.y"
    {char* ligneDesTotaux = malloc(sizeof(char)*1000);
sommeColonne(ligneDesTotaux,positionnement, numberInColonne, sumColonne, nbcol);
 fprintf(yyout,"%s</tbody>\n</table>\n",ligneDesTotaux);
 free(ligneDesTotaux);}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 119 "projet_compilation.y"
    {numberInColonne = malloc(nbcol * sizeof(int));
   sumColonne = malloc(nbcol*sizeof(float));
   initialiseTabBool(numberInColonne, nbcol);
   initialiseTabReel(sumColonne, nbcol);
   redigeOption(nbseparateur>=nbcol/2, positionnement);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 127 "projet_compilation.y"
    {nbseparateur++;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 128 "projet_compilation.y"
    {nbcol =+ strlen((yyvsp[(1) - (2)].str));}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 129 "projet_compilation.y"
    {nbseparateur++;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 130 "projet_compilation.y"
    {nbcol =+ strlen((yyvsp[(1) - (1)].str));}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 134 "projet_compilation.y"
    {}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 135 "projet_compilation.y"
    {}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 144 "projet_compilation.y"
    {
  if (numberInLine)
    {
      ajouteColonne((yyvsp[(1) - (1)].str),positionnement, sumLine);
    }
  fprintf(yyout,"<tr>%s</tr>\n",(yyvsp[(1) - (1)].str));
  free((yyvsp[(1) - (1)].str));
  numberInLine = 1; 
  colonneCourant = 0;
  sumLine = 0;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 157 "projet_compilation.y"
    {(yyval.str)= strcat((yyvsp[(2) - (5)].str), (yyvsp[(5) - (5)].str));}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 158 "projet_compilation.y"
    {(yyval.str) = (yyvsp[(2) - (3)].str);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 163 "projet_compilation.y"
    {(yyval.str) = redigeColonne((yyvsp[(1) - (1)].str), positionnement, 0,0 );
   numberInColonne[colonneCourant] = 0;
   numberInLine = 0;
   colonneCourant++;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 167 "projet_compilation.y"
    {(yyval.str) = redigeColonneEntier((yyvsp[(1) - (1)].entier), positionnement, 0, 0);
   sumLine += (yyvsp[(1) - (1)].entier);
   sumColonne[colonneCourant] += (yyvsp[(1) - (1)].entier);
   colonneCourant++;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 171 "projet_compilation.y"
    {(yyval.str) = redigeColonneReel((yyvsp[(1) - (1)].reel), positionnement, 0, 0);
   sumLine += (yyvsp[(1) - (1)].reel);
   sumColonne[colonneCourant] += (yyvsp[(1) - (1)].reel);   
   colonneCourant++;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 175 "projet_compilation.y"
    {(yyval.str) = redigeColonne((yyvsp[(9) - (10)].str), positionnement, 1, (yyvsp[(3) - (10)].entier));
   changeTab(numberInColonne, colonneCourant, (yyvsp[(3) - (10)].entier));
   colonneCourant += (yyvsp[(3) - (10)].entier);
   numberInLine = 0;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 179 "projet_compilation.y"
    {(yyval.str) = redigeColonneEntier((yyvsp[(9) - (10)].entier), positionnement, 1, (yyvsp[(3) - (10)].entier));
   changeTab(numberInColonne, colonneCourant, (yyvsp[(3) - (10)].entier));
   colonneCourant += (yyvsp[(3) - (10)].entier);
   sumLine += (yyvsp[(9) - (10)].entier);
 }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 184 "projet_compilation.y"
    {(yyval.str) = redigeColonneReel((yyvsp[(9) - (10)].reel), positionnement, 1, (yyvsp[(3) - (10)].entier));
   changeTab(numberInColonne, colonneCourant, (yyvsp[(3) - (10)].entier));
   colonneCourant += (yyvsp[(3) - (10)].entier);
   sumLine += (yyvsp[(9) - (10)].reel);
 }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 191 "projet_compilation.y"
    {(yyval.str)= strcat((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str));}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 192 "projet_compilation.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 198 "projet_compilation.y"
    {(yyval.str) =strcat( (yyvsp[(1) - (2)].str),(yyvsp[(2) - (2)].str));}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 199 "projet_compilation.y"
    {(yyval.str)= strcat((yyvsp[(5) - (7)].str),(yyvsp[(7) - (7)].str));}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 200 "projet_compilation.y"
    {(yyval.str) = strcat((yyvsp[(4) - (6)].str),(yyvsp[(6) - (6)].str));}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 201 "projet_compilation.y"
    {(yyval.str)=strcat((yyvsp[(2) - (3)].str),(yyvsp[(3) - (3)].str));}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 204 "projet_compilation.y"
    {(yyval.str) = strcat((yyvsp[(2) - (2)].str), (yyvsp[(1) - (2)].str));}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 205 "projet_compilation.y"
    {(yyval.str) ="";}
    break;



/* Line 1455 of yacc.c  */
#line 1748 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 208 "projet_compilation.y"

void yyerror(char *s)
{
  fprintf(stderr,"yyerror : %s\n",s);
  return;
}

char tab[]= "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"   \"http://www.w3.org/TR/html4/strict.dtd\">\n<html>\n<head><head/>\n<body>";

/*redige le champ d'option du tableau html*/
void redigeOption( int border, char * pos)
{
  fprintf(yyout, "style=text-align: %s; width: 90%%; border=\"", pos);
  if (border)
    fprintf(yyout,"1");
  else
    fprintf(yyout,"0");
  fprintf(yyout,"\"cellpadding=\"2\" cellspacing=\"2\">\n<tbody>\n<tr>");
}

/*renvoie une chaine de caractère contenant le code d'une colonne en html*/
/*texte est une string correspondant à la valeur à mettre dans la colonne*/
/*pos l'alignement dans la colonne*/
/*si multicolumn est à 1 alors colspan indique la taille de colspan*/
char* redigeColonne(char* texte, char* pos, int multicolumn, int colspan)
{
  char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: %s;\" colspan=\"%d\" rowspan = \"1\">%s</td>", pos, colspan, texte);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: %s ;\">%s</td>", pos, texte);
    }
  return retour;
}

/*idem que redigecolumn mais pour les reels*/
char* redigeColonneReel(double val, char* pos, int multicolumn, int colspan)
{
  char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: %s;\" colspan=\"%d\" rowspan = \"1\">%.2f</td>", pos, colspan, val);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: %s;\">%.2f</td>", pos, val);
    }
  return retour;
}
/*idem que redigecolumn mais pour les entiers*/
char* redigeColonneEntier(int val, char* pos, int multicolumn, int colspan)
{
  char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: %s;\" colspan=\"%d\" rowspan = \"1\">%d</td>", pos, colspan, val);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: %s;\">%d</td>", pos, val);
    }
  return retour;
}

/*Permet d'initialiser numberInColonne*/
void initialiseTabBool(int* tab, int size)
{
  int i;
  for(i = 0; i<size; i++)
    {
      tab[i] = 1;
    }
}

/*Permet d'initialiser sumColonne*/
void initialiseTabReel(float* tab, int size)
{
  int i;
  for(i = 0; i<size; i++)
    {
      tab[i] = 0;
    }
}

/*permet de changer les valeurs de numberInColonne dans le cas d'une multicolumn*/
void changeTab(int* tab, int deb, int quantity)
{
  int i;
  for(i = deb; i<deb+quantity; i++)
    {
      tab[i] = 0;
    }
}

/* Fonction ajoutant la colonne de somme d'une ligne*/
void ajouteColonne(char* chaine, char* position, float num)
 {
   char* aCopier=malloc(100* sizeof(char));
   sprintf(aCopier,  "<td style=\"text-align: %s;\">%.2f</td>",position, num);
   strcat(chaine, aCopier);
   free(aCopier);
 }

/* Fonction d'ajouter la somme des colonnes en fin de tableau*/
void sommeColonne(char* chaine, char* position, int* appliqueSomme, float* toutesSommes, int nbFois)
  {
    int i, bool;
    bool=1;
    sprintf(chaine , "");
    char* aCopier;
    for(i=0;i<nbFois;i++)
      {
	bool *= appliqueSomme[i];	
      }
    if (bool)
      {
	strcat(chaine, "<tr>");
	for (i=0;i<nbFois;i++)
	  {
	    if (appliqueSomme[i])
	      {	
		aCopier=malloc(50* sizeof(char));
		sprintf(aCopier,"");
		ajouteColonne(aCopier, position, toutesSommes[i]);
		strcat(chaine, aCopier);
		free(aCopier);
	      }
	    else
	      strcat(chaine, "<td></td>");
	  }
	strcat(chaine, "</tr>\n");
      }
  }

int main(int argc, char* argv[])
{
  if (argc >1)
    {
      yyin=fopen(argv[1],"r");
      if (!yyin) 
	{
	  printf("error when open input file\n");
	  exit(1);
	}
      if (argc >2)
	{
	  yyout=fopen(argv[2], "w");
	}
      if(!yyout)
	{
	  printf("error when open output file\n");
	  exit(1);
	}
      fprintf(yyout, "%s", tab);
      if (!yyparse() ) 
	{
	  fclose(yyin);
	  fclose(yyout);
	}
      else
	{
	  printf("parse error\n" );
	  exit(1);
	}
    }
  else 
    {
      printf("call : ./exo3 texxte.txt...");
      exit(1);
    }
}


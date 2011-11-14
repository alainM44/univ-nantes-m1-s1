
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEB = 258,
     TABLE = 259,
     TABULAR = 260,
     CAPTION = 261,
     OPTION_T = 262,
     FUSION = 263,
     TRAIT_HOR = 264,
     SEPAR_COL = 265,
     FIN_LIGNE = 266,
     SEPAR = 267,
     FIN = 268,
     ACCOL_G = 269,
     ACCOL_D = 270,
     DML = 271,
     CROCH_G = 272,
     CROCH_D = 273,
     ENTIER = 274,
     REEL = 275,
     MOT = 276,
     SPACE = 277
   };
#endif
/* Tokens.  */
#define DEB 258
#define TABLE 259
#define TABULAR 260
#define CAPTION 261
#define OPTION_T 262
#define FUSION 263
#define TRAIT_HOR 264
#define SEPAR_COL 265
#define FIN_LIGNE 266
#define SEPAR 267
#define FIN 268
#define ACCOL_G 269
#define ACCOL_D 270
#define DML 271
#define CROCH_G 272
#define CROCH_D 273
#define ENTIER 274
#define REEL 275
#define MOT 276
#define SPACE 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 23 "projet_compilation.y"
 char* str; double reel; int entier;


/* Line 1676 of yacc.c  */
#line 100 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



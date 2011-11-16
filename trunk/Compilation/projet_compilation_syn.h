
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
     DML = 274,
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
#define DML 274
#define CROCH_G 275
#define CROCH_D 276
#define ENTIER 277
#define REEL 278
#define MOT 279
#define SPACE 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 23 "projet_compilation.y"
 char* str; double reel; int entier;


/* Line 1676 of yacc.c  */
#line 106 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



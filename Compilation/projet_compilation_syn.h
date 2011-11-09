
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
     TABLEAU = 259,
     OPTION_T = 260,
     FUSION = 261,
     TRAIT_HOR = 262,
     SEPAR_COL = 263,
     FIN_LIGNE = 264,
     SEPAR = 265,
     FIN = 266,
     ACCOL_G = 267,
     ACCOL_D = 268,
     GARBAGE = 269,
     NOMBRE = 270,
     MOT = 271,
     SPACE = 272
   };
#endif
/* Tokens.  */
#define DEB 258
#define TABLEAU 259
#define OPTION_T 260
#define FUSION 261
#define TRAIT_HOR 262
#define SEPAR_COL 263
#define FIN_LIGNE 264
#define SEPAR 265
#define FIN 266
#define ACCOL_G 267
#define ACCOL_D 268
#define GARBAGE 269
#define NOMBRE 270
#define MOT 271
#define SPACE 272




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 21 "projet_compilation.y"
 char* str; double nb;


/* Line 1676 of yacc.c  */
#line 90 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



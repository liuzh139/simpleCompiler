/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     ELSE = 258,
     IF = 259,
     FOR = 260,
     NONE = 261,
     PRINT = 262,
     RETURN = 263,
     NEW = 264,
     BOOL = 265,
     INT = 266,
     TRUE = 267,
     FALSE = 268,
     MNAME = 269,
     OR = 270,
     AND = 271,
     LT = 272,
     LTE = 273,
     EQLTO = 274,
     PLUS = 275,
     MINUS = 276,
     TIMES = 277,
     DIVIDE = 278,
     NOT = 279,
     SEMICOLON = 280,
     COLON = 281,
     COMMA = 282,
     LEFTBRACE = 283,
     RIGHTBRACE = 284,
     LEFTPAREN = 285,
     RIGHTPAREN = 286,
     ASSIGNMENT = 287,
     DOT = 288
   };
#endif
/* Tokens.  */
#define ELSE 258
#define IF 259
#define FOR 260
#define NONE 261
#define PRINT 262
#define RETURN 263
#define NEW 264
#define BOOL 265
#define INT 266
#define TRUE 267
#define FALSE 268
#define MNAME 269
#define OR 270
#define AND 271
#define LT 272
#define LTE 273
#define EQLTO 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define DIVIDE 278
#define NOT 279
#define SEMICOLON 280
#define COLON 281
#define COMMA 282
#define LEFTBRACE 283
#define RIGHTBRACE 284
#define LEFTPAREN 285
#define RIGHTPAREN 286
#define ASSIGNMENT 287
#define DOT 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


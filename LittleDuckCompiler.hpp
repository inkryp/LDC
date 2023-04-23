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
     TOK_PROG = 258,
     TOK_END = 259,
     TOK_VAR = 260,
     TOK_IF = 261,
     TOK_ELSE = 262,
     TOK_WHILE = 263,
     TOK_PRINT = 264,
     TOK_ASSIGNMENT = 265,
     TOK_SEMICOLON = 266,
     TOK_COLON = 267,
     TOK_COMMA = 268,
     TOK_INT = 269,
     TOK_FLOAT = 270,
     TOK_OPEN_PARENTHESIS = 271,
     TOK_CLOSED_PARENTHESIS = 272,
     TOK_OPEN_BRACKET = 273,
     TOK_CLOSED_BRACKET = 274,
     TOK_OPEN_BRACE = 275,
     TOK_CLOSED_BRACE = 276,
     TOK_PLUS = 277,
     TOK_MINUS = 278,
     TOK_MULTIPLICATION = 279,
     TOK_DIVISION = 280,
     TOK_OTHER_OPERATOR = 281,
     TOK_LESS_THAN = 282,
     TOK_GREATER_THAN = 283,
     TOK_IDENTIFIER = 284,
     TOK_CONST_STRING = 285,
     TOK_CONST_INT = 286,
     TOK_CONST_FLOAT = 287
   };
#endif
/* Tokens.  */
#define TOK_PROG 258
#define TOK_END 259
#define TOK_VAR 260
#define TOK_IF 261
#define TOK_ELSE 262
#define TOK_WHILE 263
#define TOK_PRINT 264
#define TOK_ASSIGNMENT 265
#define TOK_SEMICOLON 266
#define TOK_COLON 267
#define TOK_COMMA 268
#define TOK_INT 269
#define TOK_FLOAT 270
#define TOK_OPEN_PARENTHESIS 271
#define TOK_CLOSED_PARENTHESIS 272
#define TOK_OPEN_BRACKET 273
#define TOK_CLOSED_BRACKET 274
#define TOK_OPEN_BRACE 275
#define TOK_CLOSED_BRACE 276
#define TOK_PLUS 277
#define TOK_MINUS 278
#define TOK_MULTIPLICATION 279
#define TOK_DIVISION 280
#define TOK_OTHER_OPERATOR 281
#define TOK_LESS_THAN 282
#define TOK_GREATER_THAN 283
#define TOK_IDENTIFIER 284
#define TOK_CONST_STRING 285
#define TOK_CONST_INT 286
#define TOK_CONST_FLOAT 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 9 "Parser.y"
{
  int i;
  float f;
  char *str;
}
/* Line 1529 of yacc.c.  */
#line 119 "LittleDuckCompiler.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


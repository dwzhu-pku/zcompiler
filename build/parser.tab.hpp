/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

#ifndef YY_YY_MNT_E_PKU_SYSY_CMAKE_TEMPLATE_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_MNT_E_PKU_SYSY_CMAKE_TEMPLATE_BUILD_PARSER_TAB_HPP_INCLUDED
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
    INT = 258,
    VOID = 259,
    CONST = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    BREAK = 264,
    CONTINUE = 265,
    RETURN = 266,
    ADD = 267,
    SUB = 268,
    MUL = 269,
    DIV = 270,
    MOD = 271,
    NOT = 272,
    LT = 273,
    GT = 274,
    LE = 275,
    GE = 276,
    EQ = 277,
    NE = 278,
    LAND = 279,
    LOR = 280,
    IDENT = 281,
    ASSIGN = 282,
    VAL_CONST = 283,
    SEMI = 284,
    COMMA = 285,
    LKHX = 286,
    RKHX = 287,
    LKHZ = 288,
    RKHZ = 289,
    LKHD = 290,
    RKHD = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"

    Token* kToken;
    BaseAst* kPtrAst;

#line 99 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (BaseAst* *root);

#endif /* !YY_YY_MNT_E_PKU_SYSY_CMAKE_TEMPLATE_BUILD_PARSER_TAB_HPP_INCLUDED  */

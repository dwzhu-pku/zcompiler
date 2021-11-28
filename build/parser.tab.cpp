/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"

    #include<stdio.h>
    #include"ast.hpp"
    extern int yylex();
    extern int yylineno;
    extern FILE * yyin;
    extern FILE * yyout;
    void yyerror(BaseAst**, const char *);

#line 80 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 174 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (BaseAst* *root);

#endif /* !YY_YY_MNT_E_PKU_SYSY_CMAKE_TEMPLATE_BUILD_PARSER_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   174

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

#define YYUNDEFTOK  2
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    32,    32,    38,    44,    52,    62,    66,    71,    77,
      83,    88,    95,   100,   108,   113,   118,   125,   131,   136,
     141,   145,   150,   156,   160,   165,   170,   177,   181,   186,
     191,   196,   201,   209,   213,   217,   224,   229,   237,   242,
     249,   254,   259,   265,   273,   278,   286,   294,   299,   306,
     311,   317,   323,   331,   337,   341,   345,   349,   354,   359,
     364,   369,   374,   379,   386,   392,   396,   402,   406,   413,
     417,   422,   429,   433,   438,   443,   448
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "VOID", "CONST", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "ADD", "SUB", "MUL", "DIV",
  "MOD", "NOT", "LT", "GT", "LE", "GE", "EQ", "NE", "LAND", "LOR", "IDENT",
  "ASSIGN", "VAL_CONST", "SEMI", "COMMA", "LKHX", "RKHX", "LKHZ", "RKHZ",
  "LKHD", "RKHD", "$accept", "CompUnit", "Decl", "ConstDecl", "VarDecl",
  "VarDefArr", "VarDef", "InitVal", "ConstDefArr", "ConstDef",
  "ConstInitVal", "ConstExp", "AddExp", "MulExp", "UnaryExp", "PrimaryExp",
  "FuncRParams", "Exp", "LVal", "FuncDef", "FuncFParams", "FuncFParam",
  "Block", "BlockItems", "BlockItem", "Stmt", "Cond", "LOrExp", "LAndExp",
  "EqExp", "RelExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      71,    -8,    17,    46,    26,   -84,   -84,   -84,   -84,   -23,
     -18,   -84,    25,    53,   -84,   -84,   -84,   125,     6,   -84,
      66,    12,    68,   103,   -84,   125,   125,   125,    41,   -84,
     125,   -84,    -7,    94,   -84,   -84,   -84,   -84,    77,    80,
      -5,   -84,    85,   -84,    80,    74,   125,   -84,    53,   -84,
     -84,   -84,   108,    86,   125,   125,   125,   125,   125,   -84,
      11,   -84,   119,    80,   -84,    80,   -84,   -84,    -7,   -84,
     -84,    81,   -84,   -84,    94,    94,   -84,   -84,   -84,    66,
      96,    98,   112,   114,   118,   -84,   -84,   -84,   116,   121,
     -84,    88,   -84,   -84,   -84,   -84,   -84,   125,   -84,   125,
     125,   -84,   -84,   -84,   123,   -84,   125,   -84,   -84,   -84,
      -7,   130,   138,   126,   132,    45,   133,   -84,   128,    42,
     125,   125,   125,   125,   125,   125,   125,   125,    42,   -84,
     157,   126,   132,    45,    45,    -7,    -7,    -7,    -7,   -84,
      42,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     4,     6,     7,     5,    12,
       0,    11,     0,     0,     1,     2,     3,     0,     0,     9,
       0,     0,     0,     0,    16,     0,     0,     0,    39,    35,
       0,    13,    38,    20,    23,    27,    14,    34,     0,     0,
       0,    45,    12,    10,     0,     0,     0,     8,     0,    30,
      31,    32,     0,     0,     0,     0,     0,     0,     0,    46,
       0,    41,     0,     0,    40,     0,    17,    18,    19,    15,
      28,     0,    37,    33,    21,    22,    24,    25,    26,     0,
       0,     0,     0,     0,     0,    54,    47,    51,     0,    34,
      56,     0,    50,    52,    44,    43,    42,     0,    29,     0,
       0,    60,    61,    62,     0,    55,     0,    48,    49,    36,
      72,     0,    64,    65,    67,    69,     0,    63,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      57,    66,    68,    70,    71,    73,    74,    75,    76,    59,
       0,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,    58,   -84,   -84,   -84,   146,   -84,   -84,   120,
     -84,   -84,   -39,   104,   -24,   -84,   -84,   -17,   -50,   163,
     148,   109,    63,   -84,    79,   -83,    72,   -84,    54,    52,
      38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,    87,     6,     7,    10,    11,    31,    23,    24,
      66,    67,    32,    33,    34,    35,    71,    88,    37,     8,
      40,    41,    90,    91,    92,    93,   111,   112,   113,   114,
     115
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,    49,    50,    51,    17,    54,    55,    68,    18,    38,
      89,    19,    20,    53,    79,    38,     3,    80,     9,    81,
      82,    83,    84,    25,    26,    62,    14,    63,    27,     1,
       2,     3,    76,    77,    78,    72,   130,    28,    39,    29,
      85,    89,    30,    12,    44,   139,    60,    86,    80,    13,
      81,    82,    83,    84,    25,    26,    21,   141,     5,    27,
     110,   110,    15,   124,   125,   126,   127,   104,    28,    89,
      29,    85,    52,    30,     1,     2,     3,    60,    89,    22,
     109,   110,   110,   110,   110,   135,   136,   137,   138,   118,
      89,    79,    42,     3,    80,    46,    81,    82,    83,    84,
      25,    26,    61,    59,    62,    27,    65,    64,    56,    57,
      58,    97,    17,    98,    28,    60,    29,    85,    73,    30,
      25,    26,    38,    60,   107,    27,    95,    99,    96,   100,
      25,    26,    47,    48,    28,    27,    29,    25,    26,    30,
      70,   101,    27,   102,    28,   105,    29,   103,   106,    30,
     121,    28,   117,    29,   122,   123,    30,   129,    74,    75,
     133,   134,   119,   120,   140,   128,    43,    16,    69,    45,
     108,    94,   116,   132,   131
};

static const yytype_uint8 yycheck[] =
{
      17,    25,    26,    27,    27,    12,    13,    46,    31,     3,
      60,    29,    30,    30,     3,     3,     5,     6,    26,     8,
       9,    10,    11,    12,    13,    30,     0,    32,    17,     3,
       4,     5,    56,    57,    58,    52,   119,    26,    32,    28,
      29,    91,    31,    26,    32,   128,    35,    36,     6,     3,
       8,     9,    10,    11,    12,    13,    31,   140,     0,    17,
      99,   100,     4,    18,    19,    20,    21,    84,    26,   119,
      28,    29,    31,    31,     3,     4,     5,    35,   128,    26,
      97,   120,   121,   122,   123,   124,   125,   126,   127,   106,
     140,     3,    26,     5,     6,    27,     8,     9,    10,    11,
      12,    13,    39,    26,    30,    17,    32,    44,    14,    15,
      16,    30,    27,    32,    26,    35,    28,    29,    32,    31,
      12,    13,     3,    35,    36,    17,    63,    31,    65,    31,
      12,    13,    29,    30,    26,    17,    28,    12,    13,    31,
      32,    29,    17,    29,    26,    29,    28,    29,    27,    31,
      24,    26,    29,    28,    22,    23,    31,    29,    54,    55,
     122,   123,    32,    25,     7,    32,    20,     4,    48,    21,
      91,    62,   100,   121,   120
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    38,    39,    40,    41,    56,    26,
      42,    43,    26,     3,     0,    39,    56,    27,    31,    29,
      30,    31,    26,    45,    46,    12,    13,    17,    26,    28,
      31,    44,    49,    50,    51,    52,    54,    55,     3,    32,
      57,    58,    26,    43,    32,    57,    27,    29,    30,    51,
      51,    51,    31,    54,    12,    13,    14,    15,    16,    26,
      35,    59,    30,    32,    59,    32,    47,    48,    49,    46,
      32,    53,    54,    32,    50,    50,    51,    51,    51,     3,
       6,     8,     9,    10,    11,    29,    36,    39,    54,    55,
      59,    60,    61,    62,    58,    59,    59,    30,    32,    31,
      31,    29,    29,    29,    54,    29,    27,    36,    61,    54,
      49,    63,    64,    65,    66,    67,    63,    29,    54,    32,
      25,    24,    22,    23,    18,    19,    20,    21,    32,    29,
      62,    65,    66,    67,    67,    49,    49,    49,    49,    62,
       7,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      42,    42,    43,    43,    44,    45,    45,    46,    47,    48,
      49,    49,    49,    50,    50,    50,    50,    51,    51,    51,
      51,    51,    51,    52,    52,    52,    53,    53,    54,    55,
      56,    56,    56,    56,    57,    57,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    63,    64,    64,    65,    65,    66,
      66,    66,    67,    67,    67,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     4,     3,
       3,     1,     1,     3,     1,     3,     1,     3,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     1,     3,     4,
       2,     2,     2,     3,     1,     1,     3,     1,     1,     1,
       5,     5,     6,     6,     3,     1,     2,     2,     3,     2,
       1,     1,     1,     4,     1,     2,     1,     5,     7,     5,
       2,     2,     2,     3,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3
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
        yyerror (root, YY_("syntax error: cannot back up")); \
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
                  Type, Value, root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, BaseAst* *root)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (root);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, BaseAst* *root)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, root);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, BaseAst* *root)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, root); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, BaseAst* *root)
{
  YYUSE (yyvaluep);
  YYUSE (root);
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
yyparse (BaseAst* *root)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
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
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
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

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
  case 2:
#line 33 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        dynamic_cast<BlockAst*>((yyvsp[-1].kPtrAst))->append_stmt((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=(yyvsp[-1].kPtrAst);
                    }
#line 1460 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 3:
#line 39 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        dynamic_cast<BlockAst*>((yyvsp[-1].kPtrAst))->append_stmt((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=(yyvsp[-1].kPtrAst);
                    }
#line 1470 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 4:
#line 45 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        BlockAst* ptr = new BlockAst();
                        ptr->append_stmt((yyvsp[0].kPtrAst));
                        *root = ptr;
		                (yyval.kPtrAst) = ptr;
                    }
#line 1482 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 5:
#line 53 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        BlockAst* ptr = new BlockAst();
                        ptr->append_stmt((yyvsp[0].kPtrAst));
                        *root = ptr;
		                (yyval.kPtrAst) = ptr;
                    }
#line 1494 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 6:
#line 63 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1502 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 7:
#line 67 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1510 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 8:
#line 72 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[-1].kPtrAst);
                    }
#line 1518 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 9:
#line 78 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst) = (yyvsp[-1].kPtrAst);
                    }
#line 1526 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 10:
#line 84 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        dynamic_cast<ArrayAst*>((yyvsp[-2].kPtrAst))->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=(yyvsp[-2].kPtrAst);
                    }
#line 1535 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 11:
#line 89 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=ptr;
                    }
#line 1545 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 12:
#line 96 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        DeclAst* ptr = new DeclAst(INT, (yyvsp[0].kToken)->ident_name);
                        (yyval.kPtrAst)=ptr;
                    }
#line 1554 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 13:
#line 101 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: VarDef\n");
                        DeclAst* ptr = new DeclAst(INT, (yyvsp[-2].kToken)->ident_name, (yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=ptr;
                    }
#line 1564 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 14:
#line 109 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1572 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 15:
#line 114 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        dynamic_cast<ArrayAst*>((yyvsp[-2].kPtrAst))->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=(yyvsp[-2].kPtrAst);
                    }
#line 1581 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 16:
#line 119 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=ptr;
                    }
#line 1591 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 17:
#line 126 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        DeclAst* ptr = new DeclAst(INT, (yyvsp[-2].kToken)->ident_name, (yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=ptr;
                    }
#line 1600 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 18:
#line 132 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1608 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 19:
#line 137 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1616 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 20:
#line 142 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1624 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 21:
#line 146 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "+", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1633 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 22:
#line 151 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "-", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1642 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 23:
#line 157 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1650 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 24:
#line 161 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "*", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1659 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 25:
#line 166 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "/", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1668 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 26:
#line 171 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "%", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1677 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 27:
#line 178 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1685 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 28:
#line 182 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        FunCallAst* ptr = new FunCallAst(((yyvsp[-2].kToken))->ident_name);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1694 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 29:
#line 187 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        FunCallAst* ptr = new FunCallAst(((yyvsp[-3].kToken))->ident_name, dynamic_cast<ArrayAst*>((yyvsp[-1].kPtrAst))->array_list);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1703 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 30:
#line 192 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        UnaryOpAst* ptr = new UnaryOpAst((yyvsp[0].kPtrAst), "+");
                        (yyval.kPtrAst) = ptr;
                    }
#line 1712 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 31:
#line 197 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        UnaryOpAst* ptr = new UnaryOpAst((yyvsp[0].kPtrAst), "-");
                        (yyval.kPtrAst) = ptr;
                    }
#line 1721 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 32:
#line 202 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        UnaryOpAst* ptr = new UnaryOpAst((yyvsp[0].kPtrAst), "!");
                        (yyval.kPtrAst) = ptr;
                    }
#line 1730 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 33:
#line 210 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[-1].kPtrAst);
                    }
#line 1738 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 34:
#line 214 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1746 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 35:
#line 218 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: PrimaryExp\n");
                        BinaryOpAst* ptr = new BinaryOpAst(nullptr, nullptr, "", ((yyvsp[0].kToken))->val, 1);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1756 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 36:
#line 225 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        dynamic_cast<ArrayAst*>((yyvsp[-2].kPtrAst))->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=(yyvsp[-2].kPtrAst);
                    }
#line 1765 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 37:
#line 230 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=ptr;
                    }
#line 1775 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 38:
#line 238 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1783 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 39:
#line 243 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        LvalAst* ptr = new LvalAst(((yyvsp[0].kToken))->ident_name);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1792 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 40:
#line 250 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        FunDefAst* ptr = new FunDefAst(VOID, ((yyvsp[-3].kToken))->ident_name, (yyvsp[0].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 1801 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 41:
#line 255 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        FunDefAst* ptr = new FunDefAst(INT, ((yyvsp[-3].kToken))->ident_name, (yyvsp[0].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 1810 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 42:
#line 260 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: FuncDef\n");
                        FunDefAst* ptr = new FunDefAst(VOID, ((yyvsp[-4].kToken))->ident_name, (yyvsp[0].kPtrAst), dynamic_cast<ArrayAst*>((yyvsp[-2].kPtrAst))->array_list);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1820 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 43:
#line 266 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: FuncDef\n");
                        FunDefAst* ptr = new FunDefAst(INT, ((yyvsp[-4].kToken))->ident_name, (yyvsp[0].kPtrAst), dynamic_cast<ArrayAst*>((yyvsp[-2].kPtrAst))->array_list);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1830 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 44:
#line 274 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        dynamic_cast<ArrayAst*>((yyvsp[-2].kPtrAst))->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst) = (yyvsp[-2].kPtrAst);
                    }
#line 1839 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 45:
#line 279 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 1849 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 46:
#line 287 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        DeclAst* ptr = new DeclAst(INT, ((yyvsp[0].kToken))->ident_name);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1858 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 47:
#line 295 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BlockAst* ptr = new BlockAst();
                        (yyval.kPtrAst)=ptr;
                    }
#line 1867 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 48:
#line 300 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BlockAst* ptr = new BlockAst(dynamic_cast<BlockAst*>((yyvsp[-1].kPtrAst))->list_stmts);
                        (yyval.kPtrAst)=ptr;
                    }
#line 1876 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 49:
#line 307 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        dynamic_cast<BlockAst*>((yyvsp[-1].kPtrAst))->append_stmt((yyvsp[0].kPtrAst));
                        (yyval.kPtrAst)=(yyvsp[-1].kPtrAst);
                    }
#line 1885 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 50:
#line 312 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1893 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 51:
#line 318 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BlockAst* ptr = new BlockAst;
                        ptr->append_stmt((yyvsp[0].kPtrAst));
		                (yyval.kPtrAst) = ptr;
                    }
#line 1903 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 52:
#line 324 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BlockAst* ptr = new BlockAst;
                        ptr->append_stmt((yyvsp[0].kPtrAst));
		                (yyval.kPtrAst) = ptr;
                    }
#line 1913 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 53:
#line 332 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        if(Debug_Parser)    printf("Trace: Stmt\n");
                        AssignAst* ptr = new AssignAst(dynamic_cast<LvalAst*>((yyvsp[-3].kPtrAst))->name, (yyvsp[-1].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 1923 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 54:
#line 338 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ;
                    }
#line 1931 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 55:
#line 342 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[-1].kPtrAst);
                    }
#line 1939 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 56:
#line 346 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 1947 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 57:
#line 350 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        IfAst* ptr = new IfAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), nullptr);
                        (yyval.kPtrAst) = ptr;
                    }
#line 1956 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 58:
#line 355 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        IfAst* ptr = new IfAst((yyvsp[-4].kPtrAst), (yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 1965 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 59:
#line 360 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        WhileAst* ptr = new WhileAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 1974 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 60:
#line 365 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BreakAst* ptr = new BreakAst();
                        (yyval.kPtrAst) = ptr;
                    }
#line 1983 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 61:
#line 370 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ContinueAst* ptr = new ContinueAst();
                        (yyval.kPtrAst) = ptr;
                    }
#line 1992 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 62:
#line 375 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ReturnAst* ptr = new ReturnAst(nullptr, nullptr);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2001 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 63:
#line 380 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        ReturnAst* ptr = new ReturnAst(nullptr, (yyvsp[-1].kPtrAst));
                        (yyval.kPtrAst) = ptr;
                    }
#line 2010 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 64:
#line 387 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 2018 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 65:
#line 393 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst)=(yyvsp[0].kPtrAst);
                    }
#line 2026 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 66:
#line 397 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "||", 0, 0);
                        (yyval.kPtrAst) = ptr; 
                    }
#line 2035 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 67:
#line 403 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst) = (yyvsp[0].kPtrAst);
                    }
#line 2043 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 68:
#line 407 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "&&", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2052 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 69:
#line 414 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst) = (yyvsp[0].kPtrAst);
                    }
#line 2060 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 70:
#line 418 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "==", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2069 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 71:
#line 423 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "!=", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2078 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 72:
#line 430 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        (yyval.kPtrAst) = (yyvsp[0].kPtrAst);
                    }
#line 2086 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 73:
#line 434 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "<", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2095 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 74:
#line 439 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), ">", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2104 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 75:
#line 444 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), "<=", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2113 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;

  case 76:
#line 449 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"
                    {
                        BinaryOpAst* ptr = new BinaryOpAst((yyvsp[-2].kPtrAst), (yyvsp[0].kPtrAst), ">=", 0, 0);
                        (yyval.kPtrAst) = ptr;
                    }
#line 2122 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"
    break;


#line 2126 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp"

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
      yyerror (root, YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (root, yymsgp);
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
                      yytoken, &yylval, root);
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
                  yystos[yystate], yyvsp, root);
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
  yyerror (root, YY_("memory exhausted"));
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
                  yytoken, &yylval, root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, root);
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
#line 455 "/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y"


void yyerror(BaseAst**, const char *){
    printf("Syntax error at line %d. \n", yylineno);
};

int yywrap(void){
    return 1;
}

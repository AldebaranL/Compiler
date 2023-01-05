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

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <assert.h>
    #include <map>
    #include <vector>
    #include "parser.h"
    using namespace std;
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    map<std::string, ExprNode*> idlist;
    map<std::string, vector<ExprNode*>> arraylist;
    vector<string> curr_array;
    std::vector<Type*> paramtypes;
    vector<SymbolEntry*> sesymlist;
    std::vector<std::string> paramsymbols;
    std::vector<ExprNode*> globle_tmp_paramcalls;
    bool isret=false;
    
    bool alarm=false;
    extern int yylineno;
    string curr_func="";

    vector<BreakStmt*> breakList;
    vector<ContinueStmt*> continueList;

    int l_br=-1;
    vector<int>dims;
    vector<int>dc_record;
    map<string, vector<ExprNode*>> init_;
    string init_array;

#line 101 "src/parser.cpp"




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
#ifndef YY_YY_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 35 "src/parser.y"

    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"

#line 153 "src/parser.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTEGER = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    INT = 263,
    BOOL = 264,
    VOID = 265,
    LPAREN = 266,
    RPAREN = 267,
    LBRACKET = 268,
    RBRACKET = 269,
    LBRACE = 270,
    RBRACE = 271,
    SEMICOLON = 272,
    COMMA = 273,
    NOT = 274,
    AADD = 275,
    SSUB = 276,
    MUL = 277,
    DIV = 278,
    MOD = 279,
    ADD = 280,
    SUB = 281,
    OR = 282,
    AND = 283,
    LESS = 284,
    MORE = 285,
    EQUAL = 286,
    MORE_E = 287,
    LESS_E = 288,
    NOT_EQUAL = 289,
    ASSIGN = 290,
    RETURN = 291,
    CONST = 292,
    BREAK = 293,
    CONTINUE = 294,
    THEN = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 41 "src/parser.y"

    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;

#line 213 "src/parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */



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
#define YYFINAL  88
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

#define YYUNDEFTOK  2
#define YYMAXUTOK   295


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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    77,    78,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,   100,   109,   119,   126,
     134,   150,   180,   198,   205,   211,   211,   229,   228,   238,
     244,   247,   253,   253,   270,   275,   283,   289,   303,   308,
     315,   319,   334,   352,   372,   395,   400,   420,   440,   450,
     458,   473,   492,   515,   540,   567,   585,   609,   635,   653,
     673,   693,   713,   735,   753,   772,   793,   810,   837,   854,
     881,   885,   888,   891,   899,   954,   954,  1006,  1006,  1080,
    1084,  1112,  1116,  1120,  1124,  1128,  1132,  1136,  1140,  1144,
    1149,  1154,  1158,  1164,  1185,  1220,  1249,  1287,  1336,  1343,
    1357,  1362,  1383,  1381,  1464,  1462,  1528,  1534,  1543,  1567
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "IF", "ELSE", "WHILE",
  "INT", "BOOL", "VOID", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "SEMICOLON", "COMMA", "NOT", "AADD", "SSUB", "MUL",
  "DIV", "MOD", "ADD", "SUB", "OR", "AND", "LESS", "MORE", "EQUAL",
  "MORE_E", "LESS_E", "NOT_EQUAL", "ASSIGN", "RETURN", "CONST", "BREAK",
  "CONTINUE", "THEN", "$accept", "Stmts", "Stmt", "AssignStmt",
  "BlockStmt", "IfStmt", "WhileStmt", "AssignExpr", "ReturnStmt",
  "DeclStmt", "ExprStmt", "BreakStmt", "ContinueStmt", "FuncDef", "Cond",
  "Exp", "MulExp", "AddExp", "LOrExp", "PrimaryExp", "LVal", "EqlExp",
  "RelExp", "LAndExp", "preSinExp", "sufSinExp", "FuncCall", "Type",
  "IDList", "Program", "ARRAY", "$@1", "$@2", "$@3", "BRACEUnit", "$@4",
  "$@5", "BRACEList", "ParamDefs", "$@6", "$@7", "Params", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF (-144)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     187,    17,  -144,    -4,  -144,  -144,  -144,  -144,   117,     1,
    -144,   117,   117,   117,   117,   117,    28,    15,    29,    45,
     187,  -144,  -144,  -144,  -144,  -144,    57,  -144,  -144,  -144,
    -144,  -144,  -144,    71,    36,    82,    73,  -144,    44,     4,
      61,    70,  -144,   114,  -144,   102,   109,   101,    52,    92,
     117,   111,   134,  -144,  -144,   187,  -144,  -144,  -144,  -144,
    -144,  -144,   112,  -144,  -144,  -144,  -144,  -144,  -144,   117,
     117,   117,   117,   117,   117,  -144,   117,   117,   117,   117,
     117,   117,   117,  -144,  -144,    16,    33,    48,  -144,   117,
    -144,  -144,     8,  -144,   142,   136,  -144,   117,  -144,   150,
    -144,  -144,  -144,  -144,    36,    36,    70,   117,    61,    61,
      82,    82,    82,    82,     4,     6,  -144,  -144,   117,    62,
    -144,    69,  -144,  -144,   216,   148,  -144,   117,  -144,   187,
     152,  -144,  -144,  -144,   171,    58,   123,  -144,   117,  -144,
     216,   161,  -144,   127,  -144,  -144,   172,   187,   164,   167,
     101,  -144,    15,  -144,  -144,   163,   165,   166,   216,  -144,
    -144,   187,  -144,  -144,   164,   181,  -144,  -144,  -144,  -144,
      68,  -144,  -144,   167,   101,  -144,   216,  -144
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    39,     0,    32,    70,    71,    72,     0,    27,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     5,     6,     7,     8,     0,     9,    10,    12,
      14,    15,    11,     0,    55,    58,    36,    42,    38,    66,
      63,    68,    51,    45,    41,     0,     0,    22,     0,     0,
       0,     0,     0,    38,    29,     0,    48,    46,    47,    49,
      50,    34,     0,    73,    16,    17,     4,    24,    23,     0,
       0,     0,     0,     0,     0,    25,     0,     0,     0,     0,
       0,     0,     0,    43,    44,     0,     0,     0,     1,     0,
     109,   106,     0,    18,     0,     0,    37,     0,    40,     0,
      35,    52,    53,    54,    56,    57,    69,     0,    64,    65,
      59,    60,    62,    61,    67,     0,    93,    81,     0,    89,
      97,    91,    95,    83,     0,     0,   108,     0,    19,     0,
       0,    28,    26,   104,     0,     0,     0,    85,     0,    87,
       0,    77,    74,     0,    20,   107,    30,     0,     0,    98,
      99,   102,     0,    94,    82,    90,    92,     0,     0,    96,
      84,     0,    33,   105,     0,     0,    86,    88,    76,    79,
       0,    31,   103,   100,   101,    78,     0,    80
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,   130,   -14,  -144,  -143,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,   103,    -8,    79,    46,  -144,  -144,
       2,   119,    96,   125,    -2,  -144,  -144,   -13,  -144,  -144,
     -42,  -144,  -144,  -144,  -139,  -144,  -144,  -144,  -144,  -144,
    -144,  -144
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    95,    33,    34,    35,    36,    37,
      53,    39,    40,    41,    42,    43,    44,    45,    86,    46,
      47,   107,    55,    51,   143,   157,   158,   170,   135,   164,
     148,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,   156,    38,    87,    63,   163,    66,    50,    62,    56,
      57,    58,    59,    60,     5,     6,     7,    54,   133,   169,
     126,   172,    38,     5,     6,     7,   127,   115,    48,    49,
      49,     1,     2,   116,   117,    76,   119,   177,    77,     8,
      91,    94,    96,    17,   121,    61,    64,    11,    12,    13,
     120,   118,    17,    14,    15,     1,     2,    38,    69,    70,
      71,    89,    65,     8,    90,   122,   123,   101,   102,   103,
     151,    11,    12,    13,    67,    49,   152,    14,    15,    75,
     137,   125,    89,   124,   175,    66,   176,   139,    68,    96,
      78,    79,   150,    80,    81,     1,     2,   138,    82,   132,
      74,    38,   134,     8,   140,    85,    93,    72,    73,    88,
     136,    11,    12,    13,    89,   146,   142,    14,    15,   145,
       1,     2,    97,   174,   110,   111,   112,   113,     8,   100,
     155,    38,   142,   162,    83,    84,    11,    12,    13,   165,
     153,   154,    14,    15,   159,   160,    98,   171,   129,    38,
     142,   104,   105,     1,     2,     3,   128,     4,     5,     6,
       7,     8,   144,    38,   147,     9,   131,    10,   142,    11,
      12,    13,   108,   109,   149,    14,    15,   -75,   161,     9,
      49,   166,   168,   167,   173,    99,    16,    17,    18,    19,
       1,     2,     3,     0,     4,     5,     6,     7,     8,   106,
     130,   114,     9,     0,    10,     0,    11,    12,    13,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     1,
       2,     0,     0,    16,    17,    18,    19,     8,     0,     0,
       0,   141,     0,     0,     0,    11,    12,    13,     0,     0,
       0,    14,    15
};

static const yytype_int16 yycheck[] =
{
       8,   140,     0,    45,    17,   148,    20,    11,    16,    11,
      12,    13,    14,    15,     8,     9,    10,    16,    12,   158,
      12,   164,    20,     8,     9,    10,    18,    11,    11,    13,
      13,     3,     4,    17,    18,    31,     3,   176,    34,    11,
      48,    49,    50,    37,    86,    17,    17,    19,    20,    21,
      17,    35,    37,    25,    26,     3,     4,    55,    22,    23,
      24,    13,    17,    11,    12,    17,    18,    69,    70,    71,
      12,    19,    20,    21,    17,    13,    18,    25,    26,    35,
      18,    89,    13,    35,    16,    99,    18,    18,    17,    97,
      29,    30,   134,    32,    33,     3,     4,    35,    28,   107,
      27,    99,   115,    11,    35,     3,    14,    25,    26,     0,
     118,    19,    20,    21,    13,   129,   124,    25,    26,   127,
       3,     4,    11,   165,    78,    79,    80,    81,    11,    17,
     138,   129,   140,   147,    20,    21,    19,    20,    21,   152,
      17,    18,    25,    26,    17,    18,    12,   161,    12,   147,
     158,    72,    73,     3,     4,     5,    14,     7,     8,     9,
      10,    11,    14,   161,    12,    15,    16,    17,   176,    19,
      20,    21,    76,    77,     3,    25,    26,    16,     6,    15,
      13,    18,    16,    18,     3,    55,    36,    37,    38,    39,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    74,
      97,    82,    15,    -1,    17,    -1,    19,    20,    21,    -1,
      -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,    36,    37,    38,    39,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    19,    20,    21,    -1,    -1,
      -1,    25,    26
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    15,
      17,    19,    20,    21,    25,    26,    36,    37,    38,    39,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    70,    71,    11,    13,
      11,    74,    56,    61,    16,    73,    65,    65,    65,    65,
      65,    17,    56,    68,    17,    17,    43,    17,    17,    22,
      23,    24,    25,    26,    27,    35,    31,    34,    29,    30,
      32,    33,    28,    20,    21,     3,    69,    71,     0,    13,
      12,    56,    82,    14,    56,    55,    56,    11,    12,    42,
      17,    65,    65,    65,    57,    57,    64,    72,    63,    63,
      58,    58,    58,    58,    62,    11,    17,    18,    35,     3,
      17,    71,    17,    18,    35,    56,    12,    18,    14,    12,
      55,    16,    56,    12,    68,    79,    56,    18,    35,    18,
      35,    15,    56,    75,    14,    56,    43,    12,    81,     3,
      71,    12,    18,    17,    18,    56,    75,    76,    77,    17,
      18,     6,    43,    45,    80,    68,    18,    18,    16,    75,
      78,    43,    45,     3,    71,    16,    18,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    70,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    52,    53,    71,    71,
      71,    61,    61,    51,    44,    72,    48,    73,    45,    45,
      46,    46,    74,    47,    49,    49,    56,    55,    60,    60,
      60,    60,    66,    66,    66,    65,    65,    65,    65,    65,
      65,    57,    57,    57,    57,    58,    58,    58,    63,    63,
      63,    63,    63,    62,    62,    62,    64,    64,    59,    59,
      68,    68,    68,    68,    75,    76,    75,    77,    75,    78,
      78,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    50,    50,    50,    50,    50,    79,    79,
      79,    79,    80,    54,    81,    54,    82,    82,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     4,
       4,     1,     1,     2,     2,     0,     4,     0,     4,     2,
       5,     7,     0,     6,     2,     3,     1,     1,     1,     1,
       3,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     1,     1,     2,     1,     0,     3,     0,     4,     1,
       3,     2,     4,     2,     4,     3,     5,     3,     5,     2,
       4,     2,     4,     3,     5,     3,     5,     3,     2,     2,
       4,     4,     0,     7,     0,     6,     1,     3,     4,     3
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
#line 70 "src/parser.y"
            {
        //cout<<"Stmts"<<endl;
        ast.setRoot((yyvsp[0].stmttype));
        //ast.output();
    }
#line 1534 "src/parser.cpp"
    break;

  case 3:
#line 77 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1540 "src/parser.cpp"
    break;

  case 4:
#line 78 "src/parser.y"
                {
        //cout<<"Stmts1"<<endl;
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
        
    }
#line 1550 "src/parser.cpp"
    break;

  case 5:
#line 85 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1556 "src/parser.cpp"
    break;

  case 6:
#line 86 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1562 "src/parser.cpp"
    break;

  case 7:
#line 87 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1568 "src/parser.cpp"
    break;

  case 8:
#line 88 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1574 "src/parser.cpp"
    break;

  case 9:
#line 89 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1580 "src/parser.cpp"
    break;

  case 10:
#line 90 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1586 "src/parser.cpp"
    break;

  case 11:
#line 91 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1592 "src/parser.cpp"
    break;

  case 12:
#line 92 "src/parser.y"
              {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1598 "src/parser.cpp"
    break;

  case 13:
#line 93 "src/parser.y"
                {(yyval.stmttype) = new EmptyStmt();}
#line 1604 "src/parser.cpp"
    break;

  case 14:
#line 94 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1610 "src/parser.cpp"
    break;

  case 15:
#line 95 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1616 "src/parser.cpp"
    break;

  case 16:
#line 100 "src/parser.y"
                   {
        BreakStmt* bs = new BreakStmt();
        breakList.push_back(bs);
        (yyval.stmttype) = bs;
    }
#line 1626 "src/parser.cpp"
    break;

  case 17:
#line 109 "src/parser.y"
                      {
        ContinueStmt* cs = new ContinueStmt();
        continueList.push_back(cs);
        (yyval.stmttype) = cs;
    }
#line 1636 "src/parser.cpp"
    break;

  case 18:
#line 119 "src/parser.y"
                        {
        curr_array.push_back((yyvsp[-2].strtype));
        //vector<ExprNode*> emp;
        //arraylist[curr_array.back()]=emp;
        arraylist[curr_array.back()].push_back(nullptr);
    }
#line 1647 "src/parser.cpp"
    break;

  case 19:
#line 127 "src/parser.y"
    {
        //arraylist.erase($1);
        cout<<"hi array----"<<(yyvsp[-3].strtype)<<endl;
        curr_array.push_back((yyvsp[-3].strtype));
        arraylist[curr_array.back()].push_back((yyvsp[-1].exprtype));
    }
#line 1658 "src/parser.cpp"
    break;

  case 20:
#line 135 "src/parser.y"
    {
        // cout<<"hi array----"<<curr_array.size()<<endl;
        //Exp可能调用另外的ARRAY，导致错误。
        if((yyvsp[-1].exprtype)->getSymPtr()->getType()->isArray()||(yyvsp[-1].exprtype)->get_arrflag()){
            cout<<"hi array----"<<curr_array.back()<<endl;
            curr_array.erase(curr_array.end()-1);
            cout<<"!!!!!!!!!!!!!!!!!!!!"<<endl;
            cout<<"hi array----"<<curr_array.back()<<endl;
        }
        arraylist[curr_array.back()].push_back((yyvsp[-1].exprtype));
    }
#line 1674 "src/parser.cpp"
    break;

  case 21:
#line 150 "src/parser.y"
       {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));

        //类型检查：使用前未声明
        if(se == nullptr)
        {
            cout<<"line: "<<yylineno<<endl;
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            cout<<se->toStr()<<endl;
            assert(se != nullptr);
        }

        if(se->getType()->isArray()){
              cout<<"ID isArray!!  "<<(yyvsp[0].strtype)<<endl;
            //$$ = (ExprNode*)(((IdentifierSymbolEntry*)se)->getParent());
            vector<ExprNode*> emp;
            (yyval.exprtype)=new ArrayItem(se, emp, true);
            //((ArrayItem*)$$)->setf(true);
            // SymbolEntry *offset_se = new ConstantSymbolEntry(TypeSystem::intType, 0);//offset为常数
            // Constant *offset = new Constant(offset_se);
            // $$ = new ArrayItem(se, offset, true);
       }
        else{
            (yyval.exprtype) = new Id(se);
        }
        delete [](yyvsp[0].strtype);
    }
#line 1708 "src/parser.cpp"
    break;

  case 22:
#line 180 "src/parser.y"
          {
        cout<<"curr_array.back():"<<curr_array.back()<<endl;
        SymbolEntry *array_se;
        array_se = identifiers->lookup(curr_array.back());
        
        vector<ExprNode*> offsets=arraylist[curr_array.back()];
        (yyval.exprtype) = new ArrayItem(array_se, offsets);
        (yyval.exprtype)->set_arrflag(true);
        ((IdentifierSymbolEntry*)array_se)->setParent((yyval.exprtype));
        cout<<"hi"<<endl;
        //一定要！因为可能有重复！
        arraylist.erase(curr_array.back());
    }
#line 1726 "src/parser.cpp"
    break;

  case 23:
#line 198 "src/parser.y"
                 {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
        //std::cout<<"ExprStmt"<<endl;
    }
#line 1735 "src/parser.cpp"
    break;

  case 24:
#line 205 "src/parser.y"
                         {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1743 "src/parser.cpp"
    break;

  case 25:
#line 211 "src/parser.y"
               {alarm=false;}
#line 1749 "src/parser.cpp"
    break;

  case 26:
#line 211 "src/parser.y"
                                  {
        //类型检查：函数返回值为void（空）
        if(alarm){
            // cout<<"error"<<endl;
            cout<<"lineno: "<<yylineno+1<<endl;
            alarm=false;                          
            fprintf(stderr, "assign error: operation's type should not be <void>.\n");
            //assert(alarm);
        }
        SymbolEntry *se = (yyvsp[-3].exprtype)->getSymPtr();
        if((yyvsp[-3].exprtype)->getSymPtr()->getType()->isConst()){
            (yyvsp[-3].exprtype)->getSymPtr()->set_value((yyvsp[0].exprtype)->getSymPtr()->get_value());
        }
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[0].exprtype));
    }
#line 1769 "src/parser.cpp"
    break;

  case 27:
#line 229 "src/parser.y"
        {identifiers = new SymbolTable(identifiers);}
#line 1775 "src/parser.cpp"
    break;

  case 28:
#line 231 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1786 "src/parser.cpp"
    break;

  case 29:
#line 239 "src/parser.y"
    {
        (yyval.stmttype) = new EmptyStmt();
    }
#line 1794 "src/parser.cpp"
    break;

  case 30:
#line 244 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1802 "src/parser.cpp"
    break;

  case 31:
#line 247 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1810 "src/parser.cpp"
    break;

  case 32:
#line 253 "src/parser.y"
          {
        breakList.clear();
        continueList.clear();
    }
#line 1819 "src/parser.cpp"
    break;

  case 33:
#line 257 "src/parser.y"
                           {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
        for(int i=0;i<(int)(breakList.size());i++){
            breakList[i]->setParent((yyval.stmttype));
        }
        for(int i=0;i<(int)(continueList.size());i++){
            continueList[i]->setParent((yyval.stmttype));
        }
    }
#line 1833 "src/parser.cpp"
    break;

  case 34:
#line 270 "src/parser.y"
                    {

        (yyval.stmttype) = new ReturnStmt();
    }
#line 1842 "src/parser.cpp"
    break;

  case 35:
#line 275 "src/parser.y"
                        {
        isret=true;

        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1852 "src/parser.cpp"
    break;

  case 36:
#line 283 "src/parser.y"
           {
        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"LOrExp"<<endl;
    }
#line 1860 "src/parser.cpp"
    break;

  case 37:
#line 290 "src/parser.y"
    {
        //类型检查：int->bool
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+1<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1874 "src/parser.cpp"
    break;

  case 38:
#line 303 "src/parser.y"
         {

        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1883 "src/parser.cpp"
    break;

  case 39:
#line 308 "src/parser.y"
            {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].itype));
        se->set_value((yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
       // std::cout<<"INTEGER"<<$1<<endl;
    }
#line 1894 "src/parser.cpp"
    break;

  case 40:
#line 315 "src/parser.y"
                      {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1902 "src/parser.cpp"
    break;

  case 41:
#line 319 "src/parser.y"
             {
        //类型检查：返回值是否为void
        SymbolEntry* se = ((FunctionCall*)(yyvsp[0].exprtype))->getSymPtr();
        if(((FunctionType*)(se->getType()))->getRetType()->isVoid()){
            // cout<<"line:"<<yylineno+1<<endl;
            // cout<<"Exp should not be void!"<<endl;
            alarm=true;
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1918 "src/parser.cpp"
    break;

  case 42:
#line 334 "src/parser.y"
              {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {               
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);
        //std::cout<<"PrimaryExp"<<endl;
    }
#line 1940 "src/parser.cpp"
    break;

  case 43:
#line 352 "src/parser.y"
                   {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[-1].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new sufSingleExpr(se, (yyvsp[-1].exprtype), sufSingleExpr::AADD);
        (yyval.exprtype)->set_arrflag((yyvsp[-1].exprtype)->get_arrflag());
    }
#line 1964 "src/parser.cpp"
    break;

  case 44:
#line 372 "src/parser.y"
                   {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[-1].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new sufSingleExpr(se, (yyvsp[-1].exprtype), sufSingleExpr::SSUB);
        (yyval.exprtype)->set_arrflag((yyvsp[-1].exprtype)->get_arrflag());
    }
#line 1988 "src/parser.cpp"
    break;

  case 45:
#line 395 "src/parser.y"
              {
        (yyval.exprtype) = (yyvsp[0].exprtype);
        //std::cout<<"sufSinExp"<<endl;
    }
#line 1997 "src/parser.cpp"
    break;

  case 46:
#line 400 "src/parser.y"
                   {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::AADD, (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
    }
#line 2021 "src/parser.cpp"
    break;

  case 47:
#line 420 "src/parser.y"
                  {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::SSUB, (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
    }
#line 2045 "src/parser.cpp"
    break;

  case 48:
#line 440 "src/parser.y"
                 {
        //是不是应该存布尔？
        //类型检查：int->bool
        if(!(yyvsp[0].exprtype)->getSymPtr()->isTemporary())
            cout<<"wrong int in line:"<<yylineno+1<<endl;

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::NOT, (yyvsp[0].exprtype));
    }
#line 2059 "src/parser.cpp"
    break;

  case 49:
#line 450 "src/parser.y"
                  {
        //+出现不对表达式的值产生影响 直接忽略
        // SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        // $$ = new preSingleExpr(se, preSingleExpr::ADD, $2);
        (yyval.exprtype)=(yyvsp[0].exprtype);
        (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
    }
#line 2071 "src/parser.cpp"
    break;

  case 50:
#line 458 "src/parser.y"
                 {
        if((yyvsp[0].exprtype)->getSymPtr()->isConstant()){
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, -1*((ConstantSymbolEntry*)((yyvsp[0].exprtype)->getSymPtr()))->getValue());
            se->set_value(-1*((yyvsp[0].exprtype)->getSymPtr()->get_value()));
            (yyval.exprtype) = new Constant(se);(yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
        }
        else{
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::SUB, (yyvsp[0].exprtype));
            (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
        }
    }
#line 2088 "src/parser.cpp"
    break;

  case 51:
#line 473 "src/parser.y"
              {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);
        //std::cout<<"MulExp"<<endl;
        }
#line 2111 "src/parser.cpp"
    break;

  case 52:
#line 493 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {               
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        int res=((yyvsp[-2].exprtype)->getSymPtr()->get_value())*((yyvsp[0].exprtype)->getSymPtr()->get_value());
        se->set_value(res);
        
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2137 "src/parser.cpp"
    break;

  case 53:
#line 516 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        if((yyvsp[0].exprtype)->getSymPtr()->get_value()!=0){
            int res=((yyvsp[-2].exprtype)->getSymPtr()->get_value())/((yyvsp[0].exprtype)->getSymPtr()->get_value());
            se->set_value(res);
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2165 "src/parser.cpp"
    break;

  case 54:
#line 541 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        if((yyvsp[0].exprtype)->getSymPtr()->get_value()!=0){
            int res=((yyvsp[-2].exprtype)->getSymPtr()->get_value())%((yyvsp[0].exprtype)->getSymPtr()->get_value());
            se->set_value(res);
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2193 "src/parser.cpp"
    break;

  case 55:
#line 567 "src/parser.y"
           {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"add2"<<endl;
    }
#line 2215 "src/parser.cpp"
    break;

  case 56:
#line 586 "src/parser.y"
    {
       // std::cout<<"add1"<<endl;
       SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        int res=((yyvsp[-2].exprtype)->getSymPtr()->get_value())+((yyvsp[0].exprtype)->getSymPtr()->get_value());
        se->set_value(res);

        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2242 "src/parser.cpp"
    break;

  case 57:
#line 610 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        int res=((yyvsp[-2].exprtype)->getSymPtr()->get_value())-((yyvsp[0].exprtype)->getSymPtr()->get_value());
        se->set_value(res);
        
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2269 "src/parser.cpp"
    break;

  case 58:
#line 635 "src/parser.y"
           {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"AddExp"<<endl;
    }
#line 2291 "src/parser.cpp"
    break;

  case 59:
#line 654 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2314 "src/parser.cpp"
    break;

  case 60:
#line 674 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MORE, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2337 "src/parser.cpp"
    break;

  case 61:
#line 694 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS_E, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2360 "src/parser.cpp"
    break;

  case 62:
#line 714 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MORE_E, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2383 "src/parser.cpp"
    break;

  case 63:
#line 735 "src/parser.y"
          {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"RelExp"<<endl;
    }
#line 2405 "src/parser.cpp"
    break;

  case 64:
#line 753 "src/parser.y"
                       {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2428 "src/parser.cpp"
    break;

  case 65:
#line 772 "src/parser.y"
                           {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NOT_EQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2451 "src/parser.cpp"
    break;

  case 66:
#line 793 "src/parser.y"
           {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        
        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"RelExp"<<endl;
    }
#line 2472 "src/parser.cpp"
    break;

  case 67:
#line 811 "src/parser.y"
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        
        //类型检查：int->bool
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+2<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2500 "src/parser.cpp"
    break;

  case 68:
#line 837 "src/parser.y"
            {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        
        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"LAndExp"<<endl;
    }
#line 2521 "src/parser.cpp"
    break;

  case 69:
#line 855 "src/parser.y"
    {
        cout<<"OR!"<<endl;
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=(yyvsp[0].exprtype)->getSymPtr();
        
        //类型检查：int->bool
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+2<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2550 "src/parser.cpp"
    break;

  case 70:
#line 881 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
    }
#line 2558 "src/parser.cpp"
    break;

  case 71:
#line 885 "src/parser.y"
        {
        (yyval.type) = TypeSystem::boolType;
    }
#line 2566 "src/parser.cpp"
    break;

  case 72:
#line 888 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
    }
#line 2574 "src/parser.cpp"
    break;

  case 73:
#line 891 "src/parser.y"
                 {
        // cout<<"ha"<<endl;
        // $$ = new IntType(4, 1);
        (yyval.type) = TypeSystem::constType;
    }
#line 2584 "src/parser.cpp"
    break;

  case 74:
#line 899 "src/parser.y"
       {
        //计算位置
        int pos=0;
        cout<<init_array<<": ";
        int size=dc_record.size();
        int total=1;
        for(auto & dim:dims){
            total*=dim;
        }
        for(int i=0;i<size-1;i++){
            total/=dims[i];
            pos+=dc_record[i]*total;
        }
        for(int i=0;i<size;i++){
            cout<<"["<<dc_record[i]<<"]";
        }
        pos+=dc_record[size-1];
        cout<<endl;
        //赋值！
        cout<<"pos:"<<pos<<endl;
        init_[init_array][pos]=(yyvsp[0].exprtype);
        cout<<"haha"<<endl;
        //--------------------------------------------------
        cout<<"dc_record.back(): "<<dc_record.back()<<endl;
        cout<<"dims.back(): "<<dims.back()<<endl;
        if(dc_record.back()+1==dims.back()){
            int i=dc_record.size()-1;
            //进位
            while(i>=0){
                dc_record[i]=0;
                if(i>0){
                    if(dc_record[i-1]+1==dims[i-1]){
                        i--;
                        continue;
                    }
                    else{
                        dc_record[i-1]++;
                        break;
                    }
                }
                else{
                    break;
                }
            }
            // if(i==l_br){
            //     if(i>0){
            //         dc_record[i-1]--;
            //     }
            // }
                
        }
        else
            dc_record.back()++;
    }
#line 2643 "src/parser.cpp"
    break;

  case 75:
#line 954 "src/parser.y"
          {
        //空
        if(l_br==-1){
            std::map <std::string, vector<ExprNode*>>::iterator it1=arraylist.begin();
            //初始化dims和dc_record
            //一定要while循环 因为里面有可能有很多个数组id（但是未初始化的目标数组只有一个）
            int total=1;//计算一共有多少元素
            while(it1!=arraylist.end()){
                if(!identifiers->lookup(it1->first)){
                    init_array=it1->first;
                    Type* arrayType;
                    //vector<int>dims;
                    dims.clear();
                    dc_record.clear();
                    for(auto & iter:it1->second){
                        total*=((ConstantSymbolEntry*)(iter->getSymPtr()))->getValue();
                        dims.push_back(((ConstantSymbolEntry*)(iter->getSymPtr()))->getValue());
                        dc_record.push_back(0);
                    }
                }
                it1++;
            }
            // cout<<"dims:";
            // for(int i=0;i<dims.size();i++){
            //     cout<<dims[i]<<' ';
            // }
            // cout<<endl;
            //初始化init_
            init_[init_array].clear();
            while(total>0){
                init_[init_array].push_back(nullptr);
                total--;
            }
        }
        // else{
        //     //l_br--;
        // }
        l_br++;
    }
#line 2687 "src/parser.cpp"
    break;

  case 76:
#line 992 "src/parser.y"
            {
        l_br--;
        if(l_br>=0){
            dc_record[l_br]++;
        }
        //cout<<"rbr"<<l_br<<" "<<endl;
        for(int i=l_br+1;i<dc_record.size();i++){
            dc_record[i]=0;
        }
        if(l_br==-1){
            dc_record.clear();
        }
    }
#line 2705 "src/parser.cpp"
    break;

  case 77:
#line 1006 "src/parser.y"
           {
        //最开始
        if(l_br==-1){
            std::map <std::string, vector<ExprNode*>>::iterator it1=arraylist.begin();
            //初始化dims和dc_record
            //一定要while循环 因为里面有可能有很多个数组id（但是未初始化的目标数组只有一个）
            int total=1;//计算一共有多少元素
            while(it1!=arraylist.end()){
                if(!identifiers->lookup(it1->first)||((IdentifierSymbolEntry*)(identifiers->lookup(it1->first)))->getScope()!=identifiers->getLevel()){
                    init_array=it1->first;
                    Type* arrayType;
                    //vector<int>dims;
                    dims.clear();
                    dc_record.clear();
                    for(auto & iter:it1->second){
                        total*=iter->getSymPtr()->get_value();
                        dims.push_back(iter->getSymPtr()->get_value());
                        dc_record.push_back(0);
                    }
                    cout<<"total:"<<total<<endl;
                }
                else{
                    cout<<"scope:"<<((IdentifierSymbolEntry*)(identifiers->lookup(it1->first)))->getScope()<<endl;
                    cout<<"now scope:"<<identifiers->getLevel()<<endl;
                }
                it1++;
            }
            cout<<"------------init_array:"<<init_array<<endl;
            // cout<<"dims:";
            // for(int i=0;i<dims.size();i++){
            //     cout<<dims[i]<<' ';
            // }
            // cout<<endl;
            //初始化init_
            init_[init_array].clear();
            while(total>0){
                init_[init_array].push_back(nullptr);
                total--;
            }
            cout<<"init_ size:"<<init_[init_array].size()<<endl;
        }
        l_br++;
    }
#line 2753 "src/parser.cpp"
    break;

  case 78:
#line 1050 "src/parser.y"
    {
        l_br--;
        cout<<"dc_record:";
        for(auto& r:dc_record){
            cout<<r<<", ";
        }
        cout<<endl;
        if(l_br>=0){
            bool f=false;
            for(int x=l_br+1;x<dc_record.size();x++){
                if(dc_record[x]!=0){
                    f=true;
                    break;
                }
            }
            if(f){
                dc_record[l_br]++;
            }
        }
        //cout<<"rbr"<<l_br<<" "<<endl;
        for(int i=l_br+1;i<dc_record.size();i++){
            dc_record[i]=0;
        }
        if(l_br==-1){
            dc_record.clear();
        }
    }
#line 2785 "src/parser.cpp"
    break;

  case 79:
#line 1080 "src/parser.y"
             {
        //dc_record.back()++;
    }
#line 2793 "src/parser.cpp"
    break;

  case 80:
#line 1084 "src/parser.y"
                             {
        // cout<<"comma lbr:"<<l_br<<endl;
        // if(dc_record.back()+1==dims.back()){
        //     // dc_record[l_br-1]++;
        //     // dc_record.back()=0;
        //     int i=dc_record.size()-1;
        //     //进位
        //     while(i>=0){
        //         dc_record[i]=0;
        //         if(dc_record[i-1]+1==dims[i-1]){
        //             i--;
        //             continue;
        //         }
        //         else{
        //             dc_record[i-1]++;
        //             break;
        //         }
        //         i--;
        //     }
        //     if(i==l_br)
        //         dc_record[i-1]--;
        // }
        // else
        //     dc_record.back()++;
    }
#line 2823 "src/parser.cpp"
    break;

  case 81:
#line 1112 "src/parser.y"
            {
        idlist[(yyvsp[-1].strtype)]=nullptr;
    }
#line 2831 "src/parser.cpp"
    break;

  case 82:
#line 1116 "src/parser.y"
                       {
        idlist[(yyvsp[-3].strtype)]=(yyvsp[-1].exprtype);
    }
#line 2839 "src/parser.cpp"
    break;

  case 83:
#line 1120 "src/parser.y"
               {

    }
#line 2847 "src/parser.cpp"
    break;

  case 84:
#line 1124 "src/parser.y"
                                {

    }
#line 2855 "src/parser.cpp"
    break;

  case 85:
#line 1128 "src/parser.y"
                   {
        idlist[(yyvsp[-1].strtype)]=nullptr;
    }
#line 2863 "src/parser.cpp"
    break;

  case 86:
#line 1132 "src/parser.y"
                              {
        idlist[(yyvsp[-3].strtype)]=(yyvsp[-1].exprtype);
    }
#line 2871 "src/parser.cpp"
    break;

  case 87:
#line 1136 "src/parser.y"
                      {
        
    }
#line 2879 "src/parser.cpp"
    break;

  case 88:
#line 1140 "src/parser.y"
                                       {
        
    }
#line 2887 "src/parser.cpp"
    break;

  case 89:
#line 1144 "src/parser.y"
             {
        //结束
        idlist[(yyvsp[0].strtype)]=nullptr;
    }
#line 2896 "src/parser.cpp"
    break;

  case 90:
#line 1149 "src/parser.y"
                        {
        //结束
        idlist[(yyvsp[-2].strtype)]=(yyvsp[0].exprtype);
    }
#line 2905 "src/parser.cpp"
    break;

  case 91:
#line 1154 "src/parser.y"
                 {
        
    }
#line 2913 "src/parser.cpp"
    break;

  case 92:
#line 1158 "src/parser.y"
                                  {
        
    }
#line 2921 "src/parser.cpp"
    break;

  case 93:
#line 1164 "src/parser.y"
                      {
        // cout<<"hhh"<<endl;
        SymbolEntry *se;
        //类型检查：是否重复声明
        se = identifiers->lookup((yyvsp[-1].strtype));
        if(se != nullptr)
        {
            cout<<"line:"<<yylineno+1<<endl;
            fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)(yyvsp[-1].strtype));
            //assert(se == nullptr);
        }

        se = new IdentifierSymbolEntry((yyvsp[-2].type), (yyvsp[-1].strtype), identifiers->getLevel());
        
        identifiers->install((yyvsp[-1].strtype), se);
        DeclStmt* tmp = new DeclStmt();
        tmp->insert(new Id(se));
        (yyval.stmttype) = tmp; 
        delete [](yyvsp[-1].strtype);
    }
#line 2946 "src/parser.cpp"
    break;

  case 94:
#line 1185 "src/parser.y"
                                {

        //类型检查：函数返回值为void（空）
        if(alarm){
            // cout<<"error"<<endl;
            cout<<"lineno: "<<yylineno+1<<endl;
            alarm=false;                          
            fprintf(stderr, "assign error: operation's type should not be <void>.\n");
            //assert(alarm);
        }

        //应该加一个value值 在entry里也要加
        SymbolEntry *se;

        //类型检查：是否重复声明
        se = identifiers->lookup((yyvsp[-3].strtype));
        if(se != nullptr)
        {
            cout<<"line:"<<yylineno+1<<endl;
            fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)(yyvsp[-3].strtype));
            //assert(se == nullptr);
        }

        se = new IdentifierSymbolEntry((yyvsp[-4].type), (yyvsp[-3].strtype), identifiers->getLevel());
        //if($1->isConst()){
        se->set_value((yyvsp[-1].exprtype)->getSymPtr()->get_value());
        //}

        identifiers->install((yyvsp[-3].strtype), se);
        DeclStmt* tmp = new DeclStmt();
        tmp->insert(new Id(se),(yyvsp[-1].exprtype));
        (yyval.stmttype) = tmp;       
        delete [](yyvsp[-3].strtype);
    }
#line 2985 "src/parser.cpp"
    break;

  case 95:
#line 1220 "src/parser.y"
                        {
        //处理数组声明
                std::map <std::string, vector<ExprNode*>>::iterator it1=arraylist.begin();
        SymbolEntry *se1;
        DeclStmt* tmp = new DeclStmt();
        while(it1!=arraylist.end()){
            // cout<<it->first<<endl;
            Type* arrayType;
            //vector<int>dims;
            dims.clear();
            for(auto & iter:it1->second){
                //dims.push_back(((ConstantSymbolEntry*)(iter->getSymPtr()))->getValue());
                dims.push_back(iter->getSymPtr()->get_value());
            }
            arrayType=new ArrayType((yyvsp[-2].type), dims);
            se1 = new IdentifierSymbolEntry(arrayType, it1->first, identifiers->getLevel());
            if(!identifiers->lookup(it1->first)||((IdentifierSymbolEntry*)(identifiers->lookup(it1->first)))->getScope()!=identifiers->getLevel()){
                identifiers->install(it1->first, se1);
                
                vector<ExprNode*> newv;
                tmp->insert_array(new Id(se1), newv);
            }
            it1++;
        }
        (yyval.stmttype) = tmp;
        arraylist.clear();
        init_.clear();
    }
#line 3018 "src/parser.cpp"
    break;

  case 96:
#line 1249 "src/parser.y"
                                         {
        cout<<endl;
        cout<<"array assign??"<<endl;
        //处理数组声明
        std::map <std::string, vector<ExprNode*>>::iterator it1=arraylist.begin();
        SymbolEntry *se1;
        DeclStmt* tmp = new DeclStmt();
        
        while(it1!=arraylist.end()){
            // cout<<it->first<<endl;
            //cout<<it1->first<<" installed??"<<endl;
            if(!identifiers->lookup(it1->first)||((IdentifierSymbolEntry*)(identifiers->lookup(it1->first)))->getScope()!=identifiers->getLevel()){
                Type* arrayType;
                //vector<int>dims;
                dims.clear();
                //dc_record.clear();
                for(auto & iter:it1->second){
                    //dims.push_back(((ConstantSymbolEntry*)(iter->getSymPtr()))->getValue());
                    //dc_record.push_back(0);
                    dims.push_back(iter->getSymPtr()->get_value());
                }
                arrayType=new ArrayType((yyvsp[-4].type), dims);
                se1 = new IdentifierSymbolEntry(arrayType, it1->first, identifiers->getLevel());           

                identifiers->install(it1->first, se1);
                tmp->insert_array(new Id(se1), init_[it1->first]);
                //cout<<it1->first<<" installed!!"<<endl;
            }
            //cout<<(identifiers->lookup(it1->first)==nullptr)<<endl;
            it1++;
        }
        (yyval.stmttype) = tmp;
        arraylist.clear();
        dc_record.clear();
        init_.clear();
        l_br=-1;
    }
#line 3060 "src/parser.cpp"
    break;

  case 97:
#line 1287 "src/parser.y"
                          {
        cout<<"hhh"<<endl;
        DeclStmt* tmp = new DeclStmt();

        //处理普通变量声明
        std::map <std::string, ExprNode*>::iterator it=idlist.begin();
        SymbolEntry *se;
        while(it!=idlist.end()){
            // cout<<it->first<<endl;
            se = new IdentifierSymbolEntry((yyvsp[-2].type), it->first, identifiers->getLevel());
            if(it->second){
                se->set_value(it->second->getSymPtr()->get_value());
            }
            identifiers->install(it->first, se);
            tmp->insert(new Id(se), it->second);
            it++;
        }

        //处理数组声明
        std::map <std::string, vector<ExprNode*>>::iterator it1=arraylist.begin();
        SymbolEntry *se1;
        while(it1!=arraylist.end()){
            cout<<"---------------------"<<it1->first<<endl;
            cout<<it1->second.size()<<endl;
            Type* arrayType;
            // vector<int>dims;
            dims.clear();
            for(auto & iter:it1->second){
                //dims.push_back(((ConstantSymbolEntry*)(iter->getSymPtr()))->getValue());
                cout<<"value:"<<iter->getSymPtr()->get_value()<<endl;
                dims.push_back(iter->getSymPtr()->get_value());
            }
            arrayType=new ArrayType((yyvsp[-2].type), dims);
            se1 = new IdentifierSymbolEntry(arrayType, it1->first, identifiers->getLevel());
            if(!identifiers->lookup(it1->first)){
                identifiers->install(it1->first, se1);
                tmp->insert_array(new Id(se1), init_[it1->first]);
            }
            it1++;
        }

        (yyval.stmttype) = tmp;
        idlist.clear();//存完以后清空
        arraylist.clear();
        init_.clear();
        //delete []$2;
    }
#line 3112 "src/parser.cpp"
    break;

  case 98:
#line 1336 "src/parser.y"
           {
        // paramtypes.clear();
        // paramsymbols.clear();
        paramtypes.push_back((yyvsp[-1].type));
        paramsymbols.push_back((yyvsp[0].strtype));
    }
#line 3123 "src/parser.cpp"
    break;

  case 99:
#line 1343 "src/parser.y"
              {       
        vector<int> emp;
        for(auto & exp:arraylist[curr_array.back()]){
            int val=0;
            if(exp){
                val=exp->getSymPtr()->get_value();
            }
            emp.push_back(val);
        }
        paramtypes.push_back(new ArrayType((yyvsp[-1].type), emp));
        paramsymbols.push_back(curr_array.back());
        arraylist.erase(curr_array.back());
    }
#line 3141 "src/parser.cpp"
    break;

  case 100:
#line 1357 "src/parser.y"
                           {
        paramtypes.push_back((yyvsp[-1].type));
        paramsymbols.push_back((yyvsp[0].strtype));
    }
#line 3150 "src/parser.cpp"
    break;

  case 101:
#line 1362 "src/parser.y"
                              {
        vector<int> emp;
        for(auto & exp:arraylist[curr_array.back()]){
            int val=0;
            if(exp){
                val=exp->getSymPtr()->get_value();
            }
            emp.push_back(val);
        }
        paramtypes.push_back(new ArrayType((yyvsp[-1].type), emp));
        paramsymbols.push_back(curr_array.back());
        arraylist.erase(curr_array.back());

        // paramtypes.push_back($3);
        // paramsymbols.push_back($4);
    }
#line 3171 "src/parser.cpp"
    break;

  case 102:
#line 1383 "src/parser.y"
    {
        isret=false;

        //类型检查：是否重复定义（可能有问题，声明没有处理）
        SymbolEntry *se1=identifiers->lookup((yyvsp[-3].strtype));
        //cout<<((FunctionType*)(se1->getType()))->num_params()<<endl;
        //cout<<(int)(paramtypes.size())<<endl;
        if(se1){
            if(((FunctionType*)(se1->getType()))->num_params()==(int)(paramtypes.size())){
                cout<<"line: "<<yylineno<<endl;
                fprintf(stderr, "function define error: the function is redefined.\n");
                //assert(se1);
            }
        }

        //类型检查：检查return
        curr_func=(yyvsp[-3].strtype);


        Type *funcType;
        //std::vector<Type*> params;
        //params.swap(paramtypes);
        funcType = new FunctionType((yyvsp[-4].type),paramtypes);
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[-3].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-3].strtype), se);
        identifiers = new SymbolTable(identifiers);

        
        for(int i=0;i<int(paramsymbols.size());i++){
            // cout<<paramsymbols[i]<<endl;
            SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            sesymlist.push_back(sesym);
            identifiers->install(paramsymbols[i], sesym);
        }
    }
#line 3211 "src/parser.cpp"
    break;

  case 103:
#line 1419 "src/parser.y"
    {

        //类型检查：检查返回值类型
        if((yyvsp[-6].type)->isVoid()&&isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<(yyvsp[-5].strtype)<<"\""<<"should return void!"<<endl;
        }
        else if (!(yyvsp[-6].type)->isVoid()&&!isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<(yyvsp[-5].strtype)<<"\""<<"should return an int value!"<<endl;
        }

        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-5].strtype));
        assert(se != nullptr);

        //改动
        vector<Id*> paramlist;
        for(int i=0;i<int(paramsymbols.size());i++){
            //SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            Id *id = new Id(sesymlist[i]);//不能new！！一定要保持符号表表项
            paramlist.push_back(id);
        }
        (yyval.stmttype) = new FunctionDef(se, (yyvsp[0].stmttype), paramlist, paramsymbols);

        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();

        std::vector<Type*> params;
        params.swap(paramtypes);
        std::vector<std::string> params1;
        params1.swap(paramsymbols);
        std::vector<SymbolEntry*> sesyms;
        sesymlist.swap(sesyms);

        paramtypes.clear();
        paramsymbols.clear();
        delete top;
        delete [](yyvsp[-5].strtype);
        
        cout<<"def end??"<<endl;
    }
#line 3258 "src/parser.cpp"
    break;

  case 104:
#line 1464 "src/parser.y"
    {
        isret=false;

        //类型检查：是否重复定义（可能有问题，声明没有处理）
        SymbolEntry *se1=identifiers->lookup((yyvsp[-2].strtype));
        //cout<<((FunctionType*)(se1->getType()))->num_params()<<endl;
        //cout<<(int)(paramtypes.size())<<endl;
        if(se1){
            if(((FunctionType*)(se1->getType()))->num_params()==(int)(paramtypes.size())){
                cout<<"line: "<<yylineno<<endl;
                fprintf(stderr, "function define error: the function is redefined.\n");
                //assert(se1);
            }
        }
        //类型检查：检查return
        curr_func=(yyvsp[-2].strtype);

        Type *funcType;
        std::vector<Type*> params;
        funcType = new FunctionType((yyvsp[-3].type),params);
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[-2].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[-2].strtype), se);
        identifiers = new SymbolTable(identifiers);

        for(int i=0;i<int(paramsymbols.size());i++){
            // cout<<paramsymbols[i]<<endl;
            SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            identifiers->install(paramsymbols[i], sesym);
        }
    }
#line 3293 "src/parser.cpp"
    break;

  case 105:
#line 1495 "src/parser.y"
    {

        //类型检查：检查返回值类型
        if((yyvsp[-5].type)->isVoid()&&isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<(yyvsp[-4].strtype)<<"\""<<"should return void!"<<endl;
        }
        else if (!(yyvsp[-5].type)->isVoid()&&!isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<(yyvsp[-4].strtype)<<"\""<<"should return an int value!"<<endl;
        }

        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-4].strtype));
        assert(se != nullptr);
        //改动
        vector<Id*> paramlist;
        for(int i=0;i<int(paramsymbols.size());i++){
            SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            Id *id = new Id(sesym);
            paramlist.push_back(id);
        }
        (yyval.stmttype) = new FunctionDef(se, (yyvsp[0].stmttype), paramlist, paramsymbols);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();

        paramtypes.clear();
        paramsymbols.clear();
        delete top;
        delete [](yyvsp[-4].strtype);
    }
#line 3329 "src/parser.cpp"
    break;

  case 106:
#line 1528 "src/parser.y"
       {
        //全部变成ID了。。。
        //globle_tmp_paramcalls.clear();
        globle_tmp_paramcalls.push_back((yyvsp[0].exprtype));
    }
#line 3339 "src/parser.cpp"
    break;

  case 107:
#line 1534 "src/parser.y"
                    {
        //SymbolEntry *se;
        //se = identifiers->lookup($3);
        //assert(se != nullptr);
        globle_tmp_paramcalls.push_back((yyvsp[0].exprtype));
    }
#line 3350 "src/parser.cpp"
    break;

  case 108:
#line 1544 "src/parser.y"
    {
        std::vector<ExprNode*> params;
        params.swap(globle_tmp_paramcalls);
        
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        
        cout<<(yyvsp[-3].strtype)<<endl;
        //类型检查：函数是否声明
        if(!se){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<(yyvsp[-3].strtype)<<"\" is called without declaration!"<<endl;
        }
        assert(se != nullptr);
        //类型检查：检查参数个数是否正确
        if(int(params.size())!=((FunctionType*)(se->getType()))->num_params()){
            cout<<"line: "<<yylineno<<endl;
            fprintf(stderr, "function call error: please check params.\n");
            //assert();
        }
        (yyval.exprtype) = new FunctionCall(se, params);
    }
#line 3377 "src/parser.cpp"
    break;

  case 109:
#line 1568 "src/parser.y"
    {
        std::vector<ExprNode*> params;
        params.swap(globle_tmp_paramcalls);
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-2].strtype));
        //assert(se != nullptr);
        (yyval.exprtype) = new FunctionCall(se, params);
    }
#line 3390 "src/parser.cpp"
    break;


#line 3394 "src/parser.cpp"

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
                  yystos[+*yyssp], yyvsp);
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
#line 1578 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}

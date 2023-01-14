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
    map<int, vector<ExprNode*>> globle_tmp_paramcalls;
    int call_level=0;
    bool isret=false;
    
    bool alarm=false;
    extern int yylineno;
    string curr_func="";

    map<int,vector<BreakStmt*>> breakList;
    map<int,vector<ContinueStmt*>> continueList;
    int while_level=0;

    int l_br=-1;
    vector<int>dims;
    vector<int>dc_record;
    map<string, vector<ExprNode*>> init_;
    string init_array;

#line 103 "src/parser.cpp"




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
#line 37 "src/parser.y"

    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"

#line 155 "src/parser.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTEGER = 259,
    FLOATING_POINT = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    INT = 264,
    FLOAT = 265,
    BOOL = 266,
    VOID = 267,
    LPAREN = 268,
    RPAREN = 269,
    LBRACKET = 270,
    RBRACKET = 271,
    LBRACE = 272,
    RBRACE = 273,
    SEMICOLON = 274,
    COMMA = 275,
    NOT = 276,
    AADD = 277,
    SSUB = 278,
    MUL = 279,
    DIV = 280,
    MOD = 281,
    ADD = 282,
    SUB = 283,
    OR = 284,
    AND = 285,
    LESS = 286,
    MORE = 287,
    EQUAL = 288,
    MORE_E = 289,
    LESS_E = 290,
    NOT_EQUAL = 291,
    ASSIGN = 292,
    RETURN = 293,
    CONST = 294,
    BREAK = 295,
    CONTINUE = 296,
    THEN = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 43 "src/parser.y"

    double itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;

#line 217 "src/parser.cpp"

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
#define YYFINAL  90
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    72,    72,    79,    80,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,   102,   111,   121,   128,
     136,   152,   182,   200,   207,   213,   213,   233,   232,   242,
     248,   251,   257,   257,   284,   289,   297,   303,   317,   322,
     329,   338,   342,   357,   375,   400,   426,   431,   455,   479,
     489,   497,   516,   535,   571,   609,   647,   665,   703,   742,
     760,   780,   800,   820,   842,   860,   879,   900,   917,   944,
     961,   988,   992,   996,   999,  1002,  1011,  1066,  1066,  1118,
    1118,  1192,  1196,  1224,  1228,  1232,  1236,  1240,  1244,  1248,
    1252,  1256,  1261,  1266,  1270,  1276,  1297,  1342,  1371,  1409,
    1478,  1485,  1499,  1504,  1525,  1523,  1610,  1608,  1674,  1682,
    1693,  1693,  1719,  1719
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "FLOATING_POINT", "IF",
  "ELSE", "WHILE", "INT", "FLOAT", "BOOL", "VOID", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "SEMICOLON", "COMMA", "NOT",
  "AADD", "SSUB", "MUL", "DIV", "MOD", "ADD", "SUB", "OR", "AND", "LESS",
  "MORE", "EQUAL", "MORE_E", "LESS_E", "NOT_EQUAL", "ASSIGN", "RETURN",
  "CONST", "BREAK", "CONTINUE", "THEN", "$accept", "Stmts", "Stmt",
  "AssignStmt", "BlockStmt", "IfStmt", "WhileStmt", "AssignExpr",
  "ReturnStmt", "DeclStmt", "ExprStmt", "BreakStmt", "ContinueStmt",
  "FuncDef", "Cond", "Exp", "MulExp", "AddExp", "LOrExp", "PrimaryExp",
  "LVal", "EqlExp", "RelExp", "LAndExp", "preSinExp", "sufSinExp",
  "FuncCall", "Type", "IDList", "Program", "ARRAY", "$@1", "$@2", "$@3",
  "BRACEUnit", "$@4", "$@5", "BRACEList", "ParamDefs", "$@6", "$@7",
  "Params", "$@8", "$@9", YY_NULLPTR
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
     295,   296,   297
};
# endif

#define YYPACT_NINF (-147)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-113)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     176,    49,  -147,  -147,     1,  -147,  -147,  -147,  -147,  -147,
     208,    13,  -147,   208,   208,   208,   208,   208,    30,    17,
      28,    52,   176,  -147,  -147,  -147,  -147,  -147,    59,  -147,
    -147,  -147,  -147,  -147,  -147,    61,    60,    12,    70,  -147,
      64,    27,    42,    67,  -147,    68,  -147,   100,   108,    96,
     113,    91,   208,   115,   117,  -147,  -147,   176,  -147,  -147,
    -147,  -147,  -147,  -147,   118,  -147,  -147,  -147,  -147,  -147,
    -147,   208,   208,   208,   208,   208,   208,  -147,   208,   208,
     208,   208,   208,   208,   208,  -147,  -147,    35,     4,    46,
    -147,   208,   208,   122,  -147,   141,   139,  -147,   208,  -147,
     137,  -147,  -147,  -147,  -147,    60,    60,    67,   208,    42,
      42,    12,    12,    12,    12,    27,     7,  -147,  -147,   208,
       0,  -147,    55,  -147,  -147,   205,   145,  -147,    16,  -147,
    -147,   176,   148,  -147,  -147,  -147,   160,    18,    86,  -147,
     208,  -147,   205,   150,  -147,    97,  -147,  -147,   208,   159,
     176,   152,   156,    96,  -147,    17,  -147,  -147,   153,   154,
     165,   205,  -147,  -147,  -147,   176,  -147,  -147,   152,   169,
    -147,  -147,  -147,  -147,    69,  -147,  -147,   156,    96,  -147,
     205,  -147
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    39,    40,     0,    32,    71,    72,    73,    74,
       0,    27,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     5,     6,     7,     8,     0,     9,
      10,    12,    14,    15,    11,     0,    56,    59,    36,    43,
      38,    67,    64,    69,    52,    46,    42,     0,     0,    22,
     110,     0,     0,     0,     0,    38,    29,     0,    49,    47,
      48,    50,    51,    34,     0,    75,    16,    17,     4,    24,
      23,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,    44,    45,     0,     0,     0,
       1,     0,     0,     0,    18,     0,     0,    37,     0,    41,
       0,    35,    53,    54,    55,    57,    58,    70,     0,    65,
      66,    60,    61,    63,    62,    68,     0,    95,    83,     0,
      91,    99,    93,    97,    85,     0,     0,   108,     0,   113,
      19,     0,     0,    28,    26,   106,     0,     0,     0,    87,
       0,    89,     0,    79,    76,     0,    20,   111,     0,    30,
       0,     0,   100,   101,   104,     0,    96,    84,    92,    94,
       0,     0,    98,    86,   109,     0,    33,   107,     0,     0,
      88,    90,    78,    81,     0,    31,   105,   102,   103,    80,
       0,    82
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,   133,   -21,  -147,  -146,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,    93,   -10,    50,    40,  -147,  -147,
       2,   110,    56,   116,    -4,  -147,  -147,   -16,  -147,  -147,
     -43,  -147,  -147,  -147,  -136,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    96,    35,    36,    37,    38,    39,
      55,    41,    42,    43,    44,    45,    46,    47,    88,    48,
      49,   108,    57,    53,   145,   160,   161,   174,   137,   168,
     151,   128,    92,    93
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    68,    40,    65,    89,   167,   159,   120,    64,    58,
      59,    60,    61,    62,    52,    51,     6,     7,     8,     9,
     139,   135,   176,   121,    40,   173,     6,     7,     8,     9,
     147,    56,   154,     1,     2,     3,   148,   140,   155,    74,
      75,    95,    97,    10,   181,   122,    19,    66,   116,    63,
      51,    13,    14,    15,   117,   118,    19,    16,    17,    40,
      78,    91,    50,    79,    51,   123,   124,   102,   103,   104,
      91,    67,   119,    80,    81,   141,    82,    83,    69,    68,
      70,   126,   127,   125,    71,    72,    73,   179,    97,   180,
      85,    86,   142,   153,     1,     2,     3,    84,   134,    76,
     136,    77,    40,    87,    10,   156,   157,    94,    90,   138,
     149,    91,    13,    14,    15,   144,   162,   163,    16,    17,
     111,   112,   113,   114,   105,   106,   178,  -112,    98,   166,
     158,    99,   144,    40,   109,   110,   129,   101,   164,   169,
       1,     2,     3,     4,   175,     5,     6,     7,     8,     9,
      10,   144,    40,   131,    11,   133,    12,   130,    13,    14,
      15,   146,   150,   152,    16,    17,   165,    40,   -77,    11,
     144,    51,   177,   170,   171,    18,    19,    20,    21,     1,
       2,     3,     4,   172,     5,     6,     7,     8,     9,    10,
     100,   132,   107,    11,   115,    12,     0,    13,    14,    15,
       0,     0,     0,    16,    17,     0,     0,     0,     1,     2,
       3,     1,     2,     3,    18,    19,    20,    21,    10,     0,
       0,    10,   143,     0,     0,     0,    13,    14,    15,    13,
      14,    15,    16,    17,     0,    16,    17
};

static const yytype_int16 yycheck[] =
{
      10,    22,     0,    19,    47,   151,   142,     3,    18,    13,
      14,    15,    16,    17,    13,    15,     9,    10,    11,    12,
      20,    14,   168,    19,    22,   161,     9,    10,    11,    12,
      14,    18,    14,     3,     4,     5,    20,    37,    20,    27,
      28,    51,    52,    13,   180,    88,    39,    19,    13,    19,
      15,    21,    22,    23,    19,    20,    39,    27,    28,    57,
      33,    15,    13,    36,    15,    19,    20,    71,    72,    73,
      15,    19,    37,    31,    32,    20,    34,    35,    19,   100,
      19,    91,    92,    37,    24,    25,    26,    18,    98,    20,
      22,    23,    37,   136,     3,     4,     5,    30,   108,    29,
     116,    37,   100,     3,    13,    19,    20,    16,     0,   119,
     131,    15,    21,    22,    23,   125,    19,    20,    27,    28,
      80,    81,    82,    83,    74,    75,   169,    14,    13,   150,
     140,    14,   142,   131,    78,    79,    14,    19,   148,   155,
       3,     4,     5,     6,   165,     8,     9,    10,    11,    12,
      13,   161,   150,    14,    17,    18,    19,    16,    21,    22,
      23,    16,    14,     3,    27,    28,     7,   165,    18,    17,
     180,    15,     3,    20,    20,    38,    39,    40,    41,     3,
       4,     5,     6,    18,     8,     9,    10,    11,    12,    13,
      57,    98,    76,    17,    84,    19,    -1,    21,    22,    23,
      -1,    -1,    -1,    27,    28,    -1,    -1,    -1,     3,     4,
       5,     3,     4,     5,    38,    39,    40,    41,    13,    -1,
      -1,    13,    17,    -1,    -1,    -1,    21,    22,    23,    21,
      22,    23,    27,    28,    -1,    27,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    17,    19,    21,    22,    23,    27,    28,    38,    39,
      40,    41,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    72,    73,
      13,    15,    13,    76,    58,    63,    18,    75,    67,    67,
      67,    67,    67,    19,    58,    70,    19,    19,    45,    19,
      19,    24,    25,    26,    27,    28,    29,    37,    33,    36,
      31,    32,    34,    35,    30,    22,    23,     3,    71,    73,
       0,    15,    85,    86,    16,    58,    57,    58,    13,    14,
      44,    19,    67,    67,    67,    59,    59,    66,    74,    65,
      65,    60,    60,    60,    60,    64,    13,    19,    20,    37,
       3,    19,    73,    19,    20,    37,    58,    58,    84,    14,
      16,    14,    57,    18,    58,    14,    70,    81,    58,    20,
      37,    20,    37,    17,    58,    77,    16,    14,    20,    45,
      14,    83,     3,    73,    14,    20,    19,    20,    58,    77,
      78,    79,    19,    20,    58,     7,    45,    47,    82,    70,
      20,    20,    18,    77,    80,    45,    47,     3,    73,    18,
      20,    77
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    72,    44,    44,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    54,    55,    73,    73,
      73,    63,    63,    53,    46,    74,    50,    75,    47,    47,
      48,    48,    76,    49,    51,    51,    58,    57,    62,    62,
      62,    62,    62,    68,    68,    68,    67,    67,    67,    67,
      67,    67,    59,    59,    59,    59,    60,    60,    60,    65,
      65,    65,    65,    65,    64,    64,    64,    66,    66,    61,
      61,    70,    70,    70,    70,    70,    77,    78,    77,    79,
      77,    80,    80,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    52,    52,    52,    52,    52,
      81,    81,    81,    81,    82,    56,    83,    56,    84,    84,
      85,    69,    86,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     4,
       4,     1,     1,     2,     2,     0,     4,     0,     4,     2,
       5,     7,     0,     6,     2,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     2,     2,     2,
       2,     2,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     2,     1,     0,     3,     0,
       4,     1,     3,     2,     4,     2,     4,     3,     5,     3,
       5,     2,     4,     2,     4,     3,     5,     3,     5,     3,
       2,     2,     4,     4,     0,     7,     0,     6,     1,     3,
       0,     5,     0,     4
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
#line 72 "src/parser.y"
            {
        //cout<<"Stmts"<<endl;
        ast.setRoot((yyvsp[0].stmttype));
        //ast.output();
    }
#line 1543 "src/parser.cpp"
    break;

  case 3:
#line 79 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1549 "src/parser.cpp"
    break;

  case 4:
#line 80 "src/parser.y"
                {
        //cout<<"Stmts1"<<endl;
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
        
    }
#line 1559 "src/parser.cpp"
    break;

  case 5:
#line 87 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1565 "src/parser.cpp"
    break;

  case 6:
#line 88 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1571 "src/parser.cpp"
    break;

  case 7:
#line 89 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1577 "src/parser.cpp"
    break;

  case 8:
#line 90 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1583 "src/parser.cpp"
    break;

  case 9:
#line 91 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1589 "src/parser.cpp"
    break;

  case 10:
#line 92 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1595 "src/parser.cpp"
    break;

  case 11:
#line 93 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1601 "src/parser.cpp"
    break;

  case 12:
#line 94 "src/parser.y"
              {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1607 "src/parser.cpp"
    break;

  case 13:
#line 95 "src/parser.y"
                {(yyval.stmttype) = new EmptyStmt();}
#line 1613 "src/parser.cpp"
    break;

  case 14:
#line 96 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1619 "src/parser.cpp"
    break;

  case 15:
#line 97 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1625 "src/parser.cpp"
    break;

  case 16:
#line 102 "src/parser.y"
                   {
        BreakStmt* bs = new BreakStmt();
        breakList[while_level].push_back(bs);
        (yyval.stmttype) = bs;
    }
#line 1635 "src/parser.cpp"
    break;

  case 17:
#line 111 "src/parser.y"
                      {
        ContinueStmt* cs = new ContinueStmt();
        continueList[while_level].push_back(cs);
        (yyval.stmttype) = cs;
    }
#line 1645 "src/parser.cpp"
    break;

  case 18:
#line 121 "src/parser.y"
                        {
        curr_array.push_back((yyvsp[-2].strtype));
        //vector<ExprNode*> emp;
        //arraylist[curr_array.back()]=emp;
        arraylist[curr_array.back()].push_back(nullptr);
    }
#line 1656 "src/parser.cpp"
    break;

  case 19:
#line 129 "src/parser.y"
    {
        //arraylist.erase($1);
        cout<<"hi array----"<<(yyvsp[-3].strtype)<<endl;
        curr_array.push_back((yyvsp[-3].strtype));
        arraylist[curr_array.back()].push_back((yyvsp[-1].exprtype));
    }
#line 1667 "src/parser.cpp"
    break;

  case 20:
#line 137 "src/parser.y"
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
#line 1683 "src/parser.cpp"
    break;

  case 21:
#line 152 "src/parser.y"
       {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));

        //类型检查：使用前未声明
        if(se == nullptr)
        {
            cout<<"line: "<<yylineno<<endl;
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            // delete [](char*)$1;
            // cout<<se->toStr()<<endl;
            // assert(se != nullptr);
                        
            se = new IdentifierSymbolEntry(TypeSystem::intType, (yyvsp[0].strtype), identifiers->getLevel());
            se->set_value(idlist[(yyvsp[0].strtype)]->getSymPtr()->get_value());        
            identifiers->install((yyvsp[0].strtype), se);
        }

        if(se->getType()->isArray()){
              cout<<"ID isArray!!  "<<(yyvsp[0].strtype)<<endl;
            //$$ = (ExprNode*)(((IdentifierSymbolEntry*)se)->getParent());
            vector<ExprNode*> emp;
            (yyval.exprtype)=new ArrayItem(se, emp, true);
       }
        else{
            (yyval.exprtype) = new Id(se);
        }
        delete [](yyvsp[0].strtype);
    }
#line 1717 "src/parser.cpp"
    break;

  case 22:
#line 182 "src/parser.y"
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
#line 1735 "src/parser.cpp"
    break;

  case 23:
#line 200 "src/parser.y"
                 {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
        //std::cout<<"ExprStmt"<<endl;
    }
#line 1744 "src/parser.cpp"
    break;

  case 24:
#line 207 "src/parser.y"
                         {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1752 "src/parser.cpp"
    break;

  case 25:
#line 213 "src/parser.y"
               {alarm=false;}
#line 1758 "src/parser.cpp"
    break;

  case 26:
#line 213 "src/parser.y"
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
        double val=(yyvsp[0].exprtype)->getSymPtr()->get_value();
        if(se->getType()->isInt())
            val=(int)val;
        (yyvsp[-3].exprtype)->getSymPtr()->set_value(val);
        
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[0].exprtype));
    }
#line 1780 "src/parser.cpp"
    break;

  case 27:
#line 233 "src/parser.y"
        {identifiers = new SymbolTable(identifiers);}
#line 1786 "src/parser.cpp"
    break;

  case 28:
#line 235 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1797 "src/parser.cpp"
    break;

  case 29:
#line 243 "src/parser.y"
    {
        (yyval.stmttype) = new EmptyStmt();
    }
#line 1805 "src/parser.cpp"
    break;

  case 30:
#line 248 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1813 "src/parser.cpp"
    break;

  case 31:
#line 251 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1821 "src/parser.cpp"
    break;

  case 32:
#line 257 "src/parser.y"
          {

        while_level++;
        breakList[while_level].clear();
        continueList[while_level].clear();
        
    }
#line 1833 "src/parser.cpp"
    break;

  case 33:
#line 264 "src/parser.y"
                           {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<(yyval.stmttype)<<endl;
        for(int i=0;i<(int)(breakList[while_level].size());i++){
            cout<<"break??"<<endl;
            breakList[while_level][i]->setParent((yyval.stmttype));
        }
        for(int i=0;i<(int)(continueList[while_level].size());i++){
            continueList[while_level][i]->setParent((yyval.stmttype));
        }

        // breakList.clear();
        // continueList.clear();

        while_level--;
    }
#line 1854 "src/parser.cpp"
    break;

  case 34:
#line 284 "src/parser.y"
                    {

        (yyval.stmttype) = new ReturnStmt();
    }
#line 1863 "src/parser.cpp"
    break;

  case 35:
#line 289 "src/parser.y"
                        {
        isret=true;

        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1873 "src/parser.cpp"
    break;

  case 36:
#line 297 "src/parser.y"
           {
        (yyval.exprtype) = (yyvsp[0].exprtype);//std::cout<<"LOrExp"<<endl;
    }
#line 1881 "src/parser.cpp"
    break;

  case 37:
#line 304 "src/parser.y"
    {
        //类型检查：int->bool
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+1<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1895 "src/parser.cpp"
    break;

  case 38:
#line 317 "src/parser.y"
         {

        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1904 "src/parser.cpp"
    break;

  case 39:
#line 322 "src/parser.y"
            {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].itype));
        se->set_value((yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
       // std::cout<<"INTEGER"<<$1<<endl;
    }
#line 1915 "src/parser.cpp"
    break;

  case 40:
#line 329 "src/parser.y"
                    {
        cout<<(yyvsp[0].itype)<<endl;
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, (yyvsp[0].itype));
        se->set_value((yyvsp[0].itype));
        cout<<se->get_value()<<endl;
        (yyval.exprtype) = new Constant(se);
        cout<<"FLOATING_POINT"<<endl;
    }
#line 1928 "src/parser.cpp"
    break;

  case 41:
#line 338 "src/parser.y"
                      {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1936 "src/parser.cpp"
    break;

  case 42:
#line 342 "src/parser.y"
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
#line 1952 "src/parser.cpp"
    break;

  case 43:
#line 357 "src/parser.y"
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
#line 1974 "src/parser.cpp"
    break;

  case 44:
#line 375 "src/parser.y"
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

        SymbolEntry *se;
        if((yyvsp[-1].exprtype)->getSymPtr()->getType()->isInt())
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        else if((yyvsp[-1].exprtype)->getSymPtr()->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        
        (yyval.exprtype) = new sufSingleExpr(se, (yyvsp[-1].exprtype), sufSingleExpr::AADD);
        (yyval.exprtype)->set_arrflag((yyvsp[-1].exprtype)->get_arrflag());
    }
#line 2003 "src/parser.cpp"
    break;

  case 45:
#line 400 "src/parser.y"
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

        SymbolEntry *se;
        if((yyvsp[-1].exprtype)->getSymPtr()->getType()->isInt())
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        else if((yyvsp[-1].exprtype)->getSymPtr()->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());     
        (yyval.exprtype)->set_arrflag((yyvsp[-1].exprtype)->get_arrflag());
    }
#line 2030 "src/parser.cpp"
    break;

  case 46:
#line 426 "src/parser.y"
              {
        (yyval.exprtype) = (yyvsp[0].exprtype);
        //std::cout<<"sufSinExp"<<endl;
    }
#line 2039 "src/parser.cpp"
    break;

  case 47:
#line 431 "src/parser.y"
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

        SymbolEntry *se;
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt())
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        else if((yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());       
        (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::AADD, (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
    }
#line 2067 "src/parser.cpp"
    break;

  case 48:
#line 455 "src/parser.y"
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

        SymbolEntry *se;
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt())
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        else if((yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());      
        (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::SSUB, (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
    }
#line 2095 "src/parser.cpp"
    break;

  case 49:
#line 479 "src/parser.y"
                 {
        //是不是应该存布尔？
        //类型检查：int->bool
        if(!(yyvsp[0].exprtype)->getSymPtr()->isTemporary())
            cout<<"wrong int in line:"<<yylineno+1<<endl;

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::NOT, (yyvsp[0].exprtype));
    }
#line 2109 "src/parser.cpp"
    break;

  case 50:
#line 489 "src/parser.y"
                  {
        //+出现不对表达式的值产生影响 直接忽略
        // SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        // $$ = new preSingleExpr(se, preSingleExpr::ADD, $2);
        (yyval.exprtype)=(yyvsp[0].exprtype);
        (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
    }
#line 2121 "src/parser.cpp"
    break;

  case 51:
#line 497 "src/parser.y"
                 {
        if((yyvsp[0].exprtype)->getSymPtr()->isConstant()){
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, -1*((ConstantSymbolEntry*)((yyvsp[0].exprtype)->getSymPtr()))->getValue());
            se->set_value(-1*((yyvsp[0].exprtype)->getSymPtr()->get_value()));
            (yyval.exprtype) = new Constant(se);(yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
        }
        else{
            SymbolEntry *se;
            if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt())
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            else if((yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat())
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());       
            (yyval.exprtype) = new preSingleExpr(se, preSingleExpr::SUB, (yyvsp[0].exprtype));
            (yyval.exprtype)->set_arrflag((yyvsp[0].exprtype)->get_arrflag());
        }
    }
#line 2142 "src/parser.cpp"
    break;

  case 52:
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

        (yyval.exprtype) = (yyvsp[0].exprtype);
        //std::cout<<"MulExp"<<endl;
        }
#line 2165 "src/parser.cpp"
    break;

  case 53:
#line 536 "src/parser.y"
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

        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFloat()||(yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat()
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->gettype()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->gettype()->isFloat()))
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());       

        double val1=(yyvsp[-2].exprtype)->getSymPtr()->get_value(), val2=(yyvsp[0].exprtype)->getSymPtr()->get_value();
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isInt()) val1=(int)val1;
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt()) val2=(int)val2;

        double res=(val1)*(val2);
        se->set_value((float)res);
        
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2204 "src/parser.cpp"
    break;

  case 54:
#line 572 "src/parser.y"
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

        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFloat()||(yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat()
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->gettype()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->gettype()->isFloat()))
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());       

        if((yyvsp[0].exprtype)->getSymPtr()->get_value()!=0){
            double val1=(yyvsp[-2].exprtype)->getSymPtr()->get_value(), val2=(yyvsp[0].exprtype)->getSymPtr()->get_value();
            if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isInt()) val1=(int)val1;
            if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt()) val2=(int)val2;

            double res=(val1)/(val2);
            se->set_value((float)res);
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2245 "src/parser.cpp"
    break;

  case 55:
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

        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFloat()||(yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat()
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->gettype()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->gettype()->isFloat()))
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());       

        if((yyvsp[0].exprtype)->getSymPtr()->get_value()!=0){
            int t1=((yyvsp[-2].exprtype)->getSymPtr()->get_value());
            int t2=((yyvsp[0].exprtype)->getSymPtr()->get_value());
            int res=t1%t2;
            se->set_value(res);
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2284 "src/parser.cpp"
    break;

  case 56:
#line 647 "src/parser.y"
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
#line 2306 "src/parser.cpp"
    break;

  case 57:
#line 666 "src/parser.y"
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
        
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFloat()||(yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat()
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->gettype()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->gettype()->isFloat()))
            
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());       

        double val1=(yyvsp[-2].exprtype)->getSymPtr()->get_value(), val2=(yyvsp[0].exprtype)->getSymPtr()->get_value();
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isInt()) val1=(int)val1;
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt()) val2=(int)val2;

        double res=(val1)+(val2);
        se->set_value(res);

        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2347 "src/parser.cpp"
    break;

  case 58:
#line 704 "src/parser.y"
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
        
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFloat()||(yyvsp[0].exprtype)->getSymPtr()->getType()->isFloat()
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isFunc()&&((FunctionType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->getRetType()->isFloat())
            ||((yyvsp[-2].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[-2].exprtype)->getSymPtr()->getType()))->gettype()->isFloat())
            ||((yyvsp[0].exprtype)->getSymPtr()->getType()->isArray()&&((ArrayType*)((yyvsp[0].exprtype)->getSymPtr()->getType()))->gettype()->isFloat()))
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());      

        double val1=(yyvsp[-2].exprtype)->getSymPtr()->get_value(), val2=(yyvsp[0].exprtype)->getSymPtr()->get_value();
        if((yyvsp[-2].exprtype)->getSymPtr()->getType()->isInt()) val1=(int)val1;
        if((yyvsp[0].exprtype)->getSymPtr()->getType()->isInt()) val2=(int)val2;

        double res=(val1)-(val2);
        se->set_value(res);
        
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        (yyval.exprtype)->set_arrflag((yyvsp[-2].exprtype)->get_arrflag()||(yyvsp[0].exprtype)->get_arrflag());
    }
#line 2387 "src/parser.cpp"
    break;

  case 59:
#line 742 "src/parser.y"
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
#line 2409 "src/parser.cpp"
    break;

  case 60:
#line 761 "src/parser.y"
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
#line 2432 "src/parser.cpp"
    break;

  case 61:
#line 781 "src/parser.y"
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
#line 2455 "src/parser.cpp"
    break;

  case 62:
#line 801 "src/parser.y"
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
#line 2478 "src/parser.cpp"
    break;

  case 63:
#line 821 "src/parser.y"
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
#line 2501 "src/parser.cpp"
    break;

  case 64:
#line 842 "src/parser.y"
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
#line 2523 "src/parser.cpp"
    break;

  case 65:
#line 860 "src/parser.y"
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
#line 2546 "src/parser.cpp"
    break;

  case 66:
#line 879 "src/parser.y"
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
#line 2569 "src/parser.cpp"
    break;

  case 67:
#line 900 "src/parser.y"
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
#line 2590 "src/parser.cpp"
    break;

  case 68:
#line 918 "src/parser.y"
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
#line 2618 "src/parser.cpp"
    break;

  case 69:
#line 944 "src/parser.y"
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
#line 2639 "src/parser.cpp"
    break;

  case 70:
#line 962 "src/parser.y"
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
#line 2668 "src/parser.cpp"
    break;

  case 71:
#line 988 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
    }
#line 2676 "src/parser.cpp"
    break;

  case 72:
#line 992 "src/parser.y"
          {
        (yyval.type) = TypeSystem::floatType;
    }
#line 2684 "src/parser.cpp"
    break;

  case 73:
#line 996 "src/parser.y"
        {
        (yyval.type) = TypeSystem::boolType;
    }
#line 2692 "src/parser.cpp"
    break;

  case 74:
#line 999 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
    }
#line 2700 "src/parser.cpp"
    break;

  case 75:
#line 1002 "src/parser.y"
                 {
        if((yyvsp[0].type)->isInt())
            (yyval.type) = TypeSystem::intType_const;
        else if((yyvsp[0].type)->isFloat())
            (yyval.type) = TypeSystem::floatType_const;
    }
#line 2711 "src/parser.cpp"
    break;

  case 76:
#line 1011 "src/parser.y"
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
#line 2770 "src/parser.cpp"
    break;

  case 77:
#line 1066 "src/parser.y"
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
#line 2814 "src/parser.cpp"
    break;

  case 78:
#line 1104 "src/parser.y"
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
#line 2832 "src/parser.cpp"
    break;

  case 79:
#line 1118 "src/parser.y"
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
#line 2880 "src/parser.cpp"
    break;

  case 80:
#line 1162 "src/parser.y"
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
#line 2912 "src/parser.cpp"
    break;

  case 81:
#line 1192 "src/parser.y"
             {
        //dc_record.back()++;
    }
#line 2920 "src/parser.cpp"
    break;

  case 82:
#line 1196 "src/parser.y"
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
#line 2950 "src/parser.cpp"
    break;

  case 83:
#line 1224 "src/parser.y"
            {
        idlist[(yyvsp[-1].strtype)]=nullptr;
    }
#line 2958 "src/parser.cpp"
    break;

  case 84:
#line 1228 "src/parser.y"
                       {
        idlist[(yyvsp[-3].strtype)]=(yyvsp[-1].exprtype);
    }
#line 2966 "src/parser.cpp"
    break;

  case 85:
#line 1232 "src/parser.y"
               {

    }
#line 2974 "src/parser.cpp"
    break;

  case 86:
#line 1236 "src/parser.y"
                                {

    }
#line 2982 "src/parser.cpp"
    break;

  case 87:
#line 1240 "src/parser.y"
                   {
        idlist[(yyvsp[-1].strtype)]=nullptr;
    }
#line 2990 "src/parser.cpp"
    break;

  case 88:
#line 1244 "src/parser.y"
                              {
        idlist[(yyvsp[-3].strtype)]=(yyvsp[-1].exprtype);
    }
#line 2998 "src/parser.cpp"
    break;

  case 89:
#line 1248 "src/parser.y"
                      {
        
    }
#line 3006 "src/parser.cpp"
    break;

  case 90:
#line 1252 "src/parser.y"
                                       {
        
    }
#line 3014 "src/parser.cpp"
    break;

  case 91:
#line 1256 "src/parser.y"
             {
        //结束
        idlist[(yyvsp[0].strtype)]=nullptr;
    }
#line 3023 "src/parser.cpp"
    break;

  case 92:
#line 1261 "src/parser.y"
                        {
        //结束
        idlist[(yyvsp[-2].strtype)]=(yyvsp[0].exprtype);
    }
#line 3032 "src/parser.cpp"
    break;

  case 93:
#line 1266 "src/parser.y"
                 {
        
    }
#line 3040 "src/parser.cpp"
    break;

  case 94:
#line 1270 "src/parser.y"
                                  {
        
    }
#line 3048 "src/parser.cpp"
    break;

  case 95:
#line 1276 "src/parser.y"
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
#line 3073 "src/parser.cpp"
    break;

  case 96:
#line 1297 "src/parser.y"
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
        double val=(yyvsp[-1].exprtype)->getSymPtr()->get_value();
        if(se->getType()->isInt())
            val=(int)val;
        se->set_value(val);
        //}

        identifiers->install((yyvsp[-3].strtype), se);
        DeclStmt* tmp = new DeclStmt();

        ExprNode* exp=(yyvsp[-1].exprtype);
        if(identifiers->getLevel()==0){
            SymbolEntry* const_se=new ConstantSymbolEntry((yyvsp[-4].type), (yyvsp[-1].exprtype)->getSymPtr()->get_value());
            exp=new Constant(const_se);
        }

        tmp->insert(new Id(se),exp);
        (yyval.stmttype) = tmp;       
        delete [](yyvsp[-3].strtype);
    }
#line 3122 "src/parser.cpp"
    break;

  case 97:
#line 1342 "src/parser.y"
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
#line 3155 "src/parser.cpp"
    break;

  case 98:
#line 1371 "src/parser.y"
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
#line 3197 "src/parser.cpp"
    break;

  case 99:
#line 1409 "src/parser.y"
                          {
        cout<<"hhh"<<endl;
        DeclStmt* tmp = new DeclStmt();

        //处理普通变量声明
        std::map <std::string, ExprNode*>::iterator it=idlist.begin();
        SymbolEntry *se;
        while(it!=idlist.end()){
            cout<<"!!!!!!!!!!!!!"<<endl;
            cout<<it->first<<endl;
            se=identifiers->lookup(it->first);
            if(!se){
                se = new IdentifierSymbolEntry((yyvsp[-2].type), it->first, identifiers->getLevel());
            }
            else{ 
                se->setType((yyvsp[-2].type));
            }
            if(it->second){
                se->set_value(it->second->getSymPtr()->get_value());
                // cout<<"******************"<<it->second->getSymPtr()->get_value()<<endl;
                //救命。。
                if(identifiers->getLevel()==0){
                    SymbolEntry* const_se=new ConstantSymbolEntry((yyvsp[-2].type), it->second->getSymPtr()->get_value());
                    // cout<<((ConstantSymbolEntry*)const_se)->getValue()<<endl;
                    const_se->set_value(it->second->getSymPtr()->get_value());
                    it->second=new Constant(const_se);
                }
                // cout<<"******************"<<it->second->getSymPtr()->get_value()<<endl;
            }
            cout<<it->first<<endl;
            identifiers->install(it->first, se);
            // SymbolEntry* const_se=new ConstantSymbolEntry(TypeSystem::floatType, it->second->getSymPtr()->get_value());
            // ExprNode* c=new Constant(const_se);
            
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
#line 3269 "src/parser.cpp"
    break;

  case 100:
#line 1478 "src/parser.y"
           {
        // paramtypes.clear();
        // paramsymbols.clear();
        paramtypes.push_back((yyvsp[-1].type));
        paramsymbols.push_back((yyvsp[0].strtype));
    }
#line 3280 "src/parser.cpp"
    break;

  case 101:
#line 1485 "src/parser.y"
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
#line 3298 "src/parser.cpp"
    break;

  case 102:
#line 1499 "src/parser.y"
                           {
        paramtypes.push_back((yyvsp[-1].type));
        paramsymbols.push_back((yyvsp[0].strtype));
    }
#line 3307 "src/parser.cpp"
    break;

  case 103:
#line 1504 "src/parser.y"
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
#line 3328 "src/parser.cpp"
    break;

  case 104:
#line 1525 "src/parser.y"
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
        // for(auto& t:paramtypes){
        //     cout<<t->toStr();
        // }
        // cout<<endl;
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
#line 3372 "src/parser.cpp"
    break;

  case 105:
#line 1565 "src/parser.y"
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
#line 3419 "src/parser.cpp"
    break;

  case 106:
#line 1610 "src/parser.y"
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
#line 3454 "src/parser.cpp"
    break;

  case 107:
#line 1641 "src/parser.y"
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
#line 3490 "src/parser.cpp"
    break;

  case 108:
#line 1674 "src/parser.y"
       {
        //全部变成ID了。。。
        //globle_tmp_paramcalls.clear();
        globle_tmp_paramcalls[call_level].push_back((yyvsp[0].exprtype));

        // if($1->getSymPtr()->getType()->isFunc()) call_level++;
    }
#line 3502 "src/parser.cpp"
    break;

  case 109:
#line 1682 "src/parser.y"
                    {
        //SymbolEntry *se;
        //se = identifiers->lookup($3);
        //assert(se != nullptr);
        globle_tmp_paramcalls[call_level].push_back((yyvsp[0].exprtype));

        // if($3->getSymPtr()->getType()->isFunc()) call_level++;
    }
#line 3515 "src/parser.cpp"
    break;

  case 110:
#line 1693 "src/parser.y"
             {call_level++;}
#line 3521 "src/parser.cpp"
    break;

  case 111:
#line 1694 "src/parser.y"
    {
        std::vector<ExprNode*> params;
        params.swap(globle_tmp_paramcalls[call_level]);
        
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-4].strtype));
        
        cout<<(yyvsp[-4].strtype)<<endl;
        //类型检查：函数是否声明
        if(!se){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<(yyvsp[-4].strtype)<<"\" is called without declaration!"<<endl;
        }
        assert(se != nullptr);
        //类型检查：检查参数个数是否正确
        if(int(params.size())!=((FunctionType*)(se->getType()))->num_params()){
            cout<<"line: "<<yylineno<<endl;
            fprintf(stderr, "function call error: please check params.\n");
            //assert();
        }
        (yyval.exprtype) = new FunctionCall(se, params);

        call_level--;
    }
#line 3550 "src/parser.cpp"
    break;

  case 112:
#line 1719 "src/parser.y"
             {call_level++;}
#line 3556 "src/parser.cpp"
    break;

  case 113:
#line 1720 "src/parser.y"
    {
        std::vector<ExprNode*> params;
        params.swap(globle_tmp_paramcalls[call_level]);
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        //assert(se != nullptr);
        (yyval.exprtype) = new FunctionCall(se, params);
    }
#line 3569 "src/parser.cpp"
    break;


#line 3573 "src/parser.cpp"

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
#line 1730 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}

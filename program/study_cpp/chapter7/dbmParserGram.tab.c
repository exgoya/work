/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "dbmParserGram.y" /* yacc.c:339  */

#include <dbmParser.h>
#include <dbmParserObject.h>
int yylex();
int yyerror( void           * aLocation,
             void           * aParam,
             void           * aScanner,
             const char     * aMsg );

#line 76 "dbmParserGram.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "dbmParserGram.tab.h".  */
#ifndef YY_YY_DBMPARSERGRAM_TAB_H_INCLUDED
# define YY_YY_DBMPARSERGRAM_TAB_H_INCLUDED
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
    TOK_PLUS = 258,
    TOK_MINUS = 259,
    TOK_ASTERISK = 260,
    TOK_SOLIDUS = 261,
    TOK_AND = 262,
    TOK_OR = 263,
    TOK_LEFT_PAREN = 264,
    TOK_RIGHT_PAREN = 265,
    TOK_CONCAT_OPER = 266,
    TOK_COLON = 267,
    TOK_COMMA = 268,
    TOK_SEMICOLON = 269,
    TOK_PERIOD = 270,
    TOK_QUESTION = 271,
    TOK_QUOTE = 272,
    TOK_DOUBLE_QUOTE = 273,
    TOK_UNDERSCORE = 274,
    TOK_PERCENT = 275,
    TOK_COMMENT_TERM = 276,
    TOK_DOLLAR_SIGN = 277,
    TOK_SHARP = 278,
    TOK_AT_SIGN = 279,
    TOK_PROC_ASSIGN = 280,
    TOK_PROC_ITER = 281,
    TOK_PROC_LEFT_LABEL = 282,
    TOK_PROC_RIGHT_LABEL = 283,
    TOK_ABS = 284,
    TOK_ACTIVE = 285,
    TOK_ADD = 286,
    TOK_AGING = 287,
    TOK_ALL = 288,
    TOK_ALTER = 289,
    TOK_AS = 290,
    TOK_ASCENDING = 291,
    TOK_AVG = 292,
    TOK_BEGIN = 293,
    TOK_BY = 294,
    TOK_CALL = 295,
    TOK_CAPTURE = 296,
    TOK_CASE = 297,
    TOK_CEIL = 298,
    TOK_CHECKPOINT = 299,
    TOK_CLOSE = 300,
    TOK_COLUMN = 301,
    TOK_COMMIT = 302,
    TOK_COMPACT = 303,
    TOK_CONCAT = 304,
    TOK_CONTINUE = 305,
    TOK_CREATE = 306,
    TOK_CURRVAL = 307,
    TOK_CURSOR = 308,
    TOK_CYCLE = 309,
    TOK_DBMSOUTPUT = 310,
    TOK_DECLARE = 311,
    TOK_DECODE = 312,
    TOK_DEFAULT = 313,
    TOK_DELETE = 314,
    TOK_DEQUEUE = 315,
    TOK_DESCENDING = 316,
    TOK_DIGEST = 317,
    TOK_DIRECT = 318,
    TOK_DROP = 319,
    TOK_DUMP = 320,
    TOK_DURATION = 321,
    TOK_ELSE = 322,
    TOK_ELSIF = 323,
    TOK_EMPTY_BLOB = 324,
    TOK_EMPTY_CLOB = 325,
    TOK_END = 326,
    TOK_ENQUEUE = 327,
    TOK_EXEC = 328,
    TOK_EXCEPTION = 329,
    TOK_EXCEPTION_INIT = 330,
    TOK_EXIT = 331,
    TOK_EXP = 332,
    TOK_EXPIRED = 333,
    TOK_EXTEND = 334,
    TOK_EXTERNAL = 335,
    TOK_EXTRACT = 336,
    TOK_FETCH = 337,
    TOK_FIELDS = 338,
    TOK_FINI = 339,
    TOK_FLOOR = 340,
    TOK_FOR = 341,
    TOK_FOUND = 342,
    TOK_FROM = 343,
    TOK_FUNCTION = 344,
    TOK_GOTO = 345,
    TOK_GROUP = 346,
    TOK_GSB = 347,
    TOK_HEX = 348,
    TOK_HEXTORAW = 349,
    TOK_HOST_VARIABLE = 350,
    TOK_IF = 351,
    TOK_IN = 352,
    TOK_INSTR = 353,
    TOK_IS = 354,
    TOK_ISOPEN = 355,
    TOK_INOUT = 356,
    TOK_INACTIVE = 357,
    TOK_INCREMENT = 358,
    TOK_IDENTIFIER = 359,
    TOK_INDEX = 360,
    TOK_INIT = 361,
    TOK_INSERT = 362,
    TOK_INSTANCE = 363,
    TOK_INTERVAL = 364,
    TOK_INTO = 365,
    TOK_JSON_ADD = 366,
    TOK_JSON_DELETE = 367,
    TOK_JSON_KEY = 368,
    TOK_JSON_QUERY = 369,
    TOK_JSON_STRING = 370,
    TOK_JSON_VALUE = 371,
    TOK_LENGTH = 372,
    TOK_LIBRARY = 373,
    TOK_LIKE = 374,
    TOK_LIMIT = 375,
    TOK_LN = 376,
    TOK_LOAD = 377,
    TOK_LOCAL = 378,
    TOK_LOG = 379,
    TOK_LOOP = 380,
    TOK_LOWER = 381,
    TOK_LPAD = 382,
    TOK_LTRIM = 383,
    TOK_MAX = 384,
    TOK_MAXVALUE = 385,
    TOK_MIN = 386,
    TOK_MINVALUE = 387,
    TOK_MOD = 388,
    TOK_MONITOR = 389,
    TOK_NEXTVAL = 390,
    TOK_NOCYCLE = 391,
    TOK_NODE = 392,
    TOK_NOTFOUND = 393,
    TOK_NULL = 394,
    TOK_NVL = 395,
    TOK_ON = 396,
    TOK_OPEN = 397,
    TOK_ORDER = 398,
    TOK_OTHERS = 399,
    TOK_OUT = 400,
    TOK_PARAMETER = 401,
    TOK_PARAM_PTR = 402,
    TOK_PARAM_32 = 403,
    TOK_PARAM_64 = 404,
    TOK_PERF = 405,
    TOK_POWER = 406,
    TOK_PRAGMA = 407,
    TOK_PROCEDURE = 408,
    TOK_PROCESS = 409,
    TOK_PUT_LINE = 410,
    TOK_QUOTE_STRING = 411,
    TOK_DOUBLE_QUOTE_STRING = 412,
    TOK_QUEUE = 413,
    TOK_RAISE = 414,
    TOK_RAISE_APPLICATION_ERROR = 415,
    TOK_RANDOM = 416,
    TOK_REBUILD = 417,
    TOK_RENAME = 418,
    TOK_RESET = 419,
    TOK_REPL = 420,
    TOK_REPLACE = 421,
    TOK_RETURN = 422,
    TOK_REVERSE = 423,
    TOK_RPAD = 424,
    TOK_ROLLBACK = 425,
    TOK_ROUND = 426,
    TOK_ROWCOUNT = 427,
    TOK_ROWTYPE = 428,
    TOK_RTRIM = 429,
    TOK_SELECT = 430,
    TOK_SEQUENCE = 431,
    TOK_SERVER = 432,
    TOK_SERVICE = 433,
    TOK_SESSION = 434,
    TOK_SESSION_ID = 435,
    TOK_SET = 436,
    TOK_SLOT = 437,
    TOK_SIZE = 438,
    TOK_SQL = 439,
    TOK_SQRT = 440,
    TOK_START = 441,
    TOK_SUBSTR = 442,
    TOK_SUM = 443,
    TOK_SUMMARY = 444,
    TOK_SYNC = 445,
    TOK_SYSDATE = 446,
    TOK_SYSTEM = 447,
    TOK_TABLE = 448,
    TOK_TARGET = 449,
    TOK_TERMINATE = 450,
    TOK_THEN = 451,
    TOK_TIMEOUT = 452,
    TOK_TO = 453,
    TOK_TO_DATE = 454,
    TOK_TO_TIMESTAMP = 455,
    TOK_TRIM = 456,
    TOK_TRUNC = 457,
    TOK_TRUNCATE = 458,
    TOK_TYPE = 459,
    TOK_UNIQUE = 460,
    TOK_UPDATE = 461,
    TOK_UPPER = 462,
    TOK_USERENV = 463,
    TOK_USING = 464,
    TOK_UINT = 465,
    TOK_UNUM = 466,
    TOK_VALUES = 467,
    TOK_WHEN = 468,
    TOK_WHERE = 469,
    TOK_WHILE = 470,
    TOK_WITH = 471,
    TOK_CHAR = 472,
    TOK_DATE = 473,
    TOK_DATEDIFF = 474,
    TOK_DATETIME_STR = 475,
    TOK_DOUBLE = 476,
    TOK_FLOAT = 477,
    TOK_LONG = 478,
    TOK_INT = 479,
    TOK_INTEGER = 480,
    TOK_SHORT = 481,
    TOK_COUNT = 482,
    TOK_EQ = 483,
    TOK_GT = 484,
    TOK_GE = 485,
    TOK_LE = 486,
    TOK_LT = 487,
    TOK_NE = 488
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (dbmParserContext   * param, void               * scanner);

#endif /* !YY_YY_DBMPARSERGRAM_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 374 "dbmParserGram.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  244
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3045

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  234
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  184
/* YYNRULES -- Number of rules.  */
#define YYNRULES  464
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1169

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   488

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   278,   278,   282,   286,   293,   297,   301,   305,   309,
     313,   317,   321,   325,   329,   333,   337,   341,   345,   349,
     353,   357,   361,   365,   369,   373,   377,   381,   385,   392,
     396,   400,   404,   408,   412,   416,   420,   424,   428,   432,
     436,   440,   447,   452,   460,   473,   506,   521,   537,   547,
     559,   576,   594,   597,   617,   620,   640,   642,   670,   781,
     789,   798,   804,   812,   820,   828,   834,   842,   846,   850,
     854,   858,   862,   866,   873,   881,   886,   895,   902,   909,
     915,   924,   927,   934,   944,   961,   968,   979,   985,   992,
     998,  1005,  1011,  1018,  1024,  1031,  1036,  1042,  1050,  1056,
    1062,  1068,  1074,  1082,  1088,  1096,  1103,  1108,  1116,  1125,
    1132,  1139,  1149,  1157,  1169,  1185,  1201,  1215,  1218,  1225,
    1239,  1252,  1261,  1270,  1279,  1288,  1300,  1311,  1321,  1339,
    1359,  1362,  1366,  1374,  1385,  1394,  1406,  1422,  1436,  1442,
    1448,  1454,  1463,  1479,  1492,  1501,  1510,  1523,  1526,  1534,
    1537,  1541,  1549,  1552,  1560,  1563,  1580,  1597,  1610,  1616,
    1626,  1642,  1655,  1662,  1666,  1678,  1681,  1689,  1692,  1699,
    1715,  1727,  1736,  1742,  1748,  1754,  1760,  1766,  1772,  1783,
    1793,  1796,  1804,  1807,  1815,  1818,  1827,  1840,  1856,  1859,
    1863,  1870,  1878,  1885,  1896,  1899,  1905,  1921,  1935,  1945,
    1961,  1977,  1980,  1987,  1994,  2001,  2013,  2023,  2045,  2067,
    2074,  2081,  2088,  2095,  2107,  2114,  2121,  2134,  2146,  2165,
    2184,  2197,  2209,  2222,  2235,  2247,  2262,  2276,  2289,  2296,
    2307,  2310,  2318,  2327,  2335,  2351,  2366,  2375,  2379,  2388,
    2393,  2401,  2406,  2414,  2427,  2442,  2446,  2454,  2462,  2478,
    2493,  2509,  2525,  2531,  2537,  2546,  2559,  2572,  2586,  2599,
    2616,  2619,  2627,  2643,  2658,  2669,  2673,  2678,  2683,  2691,
    2697,  2704,  2713,  2719,  2727,  2732,  2740,  2762,  2786,  2790,
    2794,  2798,  2805,  2813,  2821,  2829,  2839,  2855,  2870,  2886,
    2901,  2917,  2930,  2934,  2943,  2959,  2971,  2975,  2990,  3008,
    3012,  3016,  3033,  3037,  3046,  3052,  3058,  3064,  3070,  3076,
    3082,  3088,  3094,  3100,  3106,  3115,  3124,  3128,  3132,  3141,
    3145,  3149,  3153,  3157,  3161,  3165,  3169,  3173,  3177,  3181,
    3190,  3194,  3198,  3202,  3206,  3210,  3214,  3218,  3222,  3226,
    3230,  3234,  3238,  3242,  3246,  3255,  3264,  3273,  3277,  3281,
    3290,  3294,  3308,  3317,  3326,  3335,  3344,  3353,  3362,  3371,
    3380,  3392,  3401,  3410,  3419,  3431,  3440,  3452,  3464,  3477,
    3489,  3501,  3513,  3516,  3522,  3538,  3549,  3558,  3569,  3580,
    3589,  3600,  3609,  3621,  3632,  3643,  3655,  3666,  3679,  3696,
    3705,  3717,  3727,  3739,  3748,  3759,  3770,  3781,  3792,  3801,
    3812,  3821,  3833,  3842,  3851,  3860,  3869,  3878,  3887,  3896,
    3905,  3917,  3926,  3935,  3944,  3953,  3962,  3974,  3983,  3992,
    4001,  4010,  4019,  4028,  4037,  4049,  4062,  4077,  4081,  4085,
    4089,  4093,  4097,  4101,  4105,  4109,  4113,  4117,  4123,  4129,
    4135,  4142,  4149,  4156,  4162,  4168,  4175,  4181,  4187,  4194,
    4201,  4207,  4213,  4219,  4226,  4237,  4244,  4256,  4263,  4273,
    4279,  4293,  4301,  4313,  4320
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_PLUS", "TOK_MINUS", "TOK_ASTERISK",
  "TOK_SOLIDUS", "TOK_AND", "TOK_OR", "TOK_LEFT_PAREN", "TOK_RIGHT_PAREN",
  "TOK_CONCAT_OPER", "TOK_COLON", "TOK_COMMA", "TOK_SEMICOLON",
  "TOK_PERIOD", "TOK_QUESTION", "TOK_QUOTE", "TOK_DOUBLE_QUOTE",
  "TOK_UNDERSCORE", "TOK_PERCENT", "TOK_COMMENT_TERM", "TOK_DOLLAR_SIGN",
  "TOK_SHARP", "TOK_AT_SIGN", "TOK_PROC_ASSIGN", "TOK_PROC_ITER",
  "TOK_PROC_LEFT_LABEL", "TOK_PROC_RIGHT_LABEL", "TOK_ABS", "TOK_ACTIVE",
  "TOK_ADD", "TOK_AGING", "TOK_ALL", "TOK_ALTER", "TOK_AS",
  "TOK_ASCENDING", "TOK_AVG", "TOK_BEGIN", "TOK_BY", "TOK_CALL",
  "TOK_CAPTURE", "TOK_CASE", "TOK_CEIL", "TOK_CHECKPOINT", "TOK_CLOSE",
  "TOK_COLUMN", "TOK_COMMIT", "TOK_COMPACT", "TOK_CONCAT", "TOK_CONTINUE",
  "TOK_CREATE", "TOK_CURRVAL", "TOK_CURSOR", "TOK_CYCLE", "TOK_DBMSOUTPUT",
  "TOK_DECLARE", "TOK_DECODE", "TOK_DEFAULT", "TOK_DELETE", "TOK_DEQUEUE",
  "TOK_DESCENDING", "TOK_DIGEST", "TOK_DIRECT", "TOK_DROP", "TOK_DUMP",
  "TOK_DURATION", "TOK_ELSE", "TOK_ELSIF", "TOK_EMPTY_BLOB",
  "TOK_EMPTY_CLOB", "TOK_END", "TOK_ENQUEUE", "TOK_EXEC", "TOK_EXCEPTION",
  "TOK_EXCEPTION_INIT", "TOK_EXIT", "TOK_EXP", "TOK_EXPIRED", "TOK_EXTEND",
  "TOK_EXTERNAL", "TOK_EXTRACT", "TOK_FETCH", "TOK_FIELDS", "TOK_FINI",
  "TOK_FLOOR", "TOK_FOR", "TOK_FOUND", "TOK_FROM", "TOK_FUNCTION",
  "TOK_GOTO", "TOK_GROUP", "TOK_GSB", "TOK_HEX", "TOK_HEXTORAW",
  "TOK_HOST_VARIABLE", "TOK_IF", "TOK_IN", "TOK_INSTR", "TOK_IS",
  "TOK_ISOPEN", "TOK_INOUT", "TOK_INACTIVE", "TOK_INCREMENT",
  "TOK_IDENTIFIER", "TOK_INDEX", "TOK_INIT", "TOK_INSERT", "TOK_INSTANCE",
  "TOK_INTERVAL", "TOK_INTO", "TOK_JSON_ADD", "TOK_JSON_DELETE",
  "TOK_JSON_KEY", "TOK_JSON_QUERY", "TOK_JSON_STRING", "TOK_JSON_VALUE",
  "TOK_LENGTH", "TOK_LIBRARY", "TOK_LIKE", "TOK_LIMIT", "TOK_LN",
  "TOK_LOAD", "TOK_LOCAL", "TOK_LOG", "TOK_LOOP", "TOK_LOWER", "TOK_LPAD",
  "TOK_LTRIM", "TOK_MAX", "TOK_MAXVALUE", "TOK_MIN", "TOK_MINVALUE",
  "TOK_MOD", "TOK_MONITOR", "TOK_NEXTVAL", "TOK_NOCYCLE", "TOK_NODE",
  "TOK_NOTFOUND", "TOK_NULL", "TOK_NVL", "TOK_ON", "TOK_OPEN", "TOK_ORDER",
  "TOK_OTHERS", "TOK_OUT", "TOK_PARAMETER", "TOK_PARAM_PTR",
  "TOK_PARAM_32", "TOK_PARAM_64", "TOK_PERF", "TOK_POWER", "TOK_PRAGMA",
  "TOK_PROCEDURE", "TOK_PROCESS", "TOK_PUT_LINE", "TOK_QUOTE_STRING",
  "TOK_DOUBLE_QUOTE_STRING", "TOK_QUEUE", "TOK_RAISE",
  "TOK_RAISE_APPLICATION_ERROR", "TOK_RANDOM", "TOK_REBUILD", "TOK_RENAME",
  "TOK_RESET", "TOK_REPL", "TOK_REPLACE", "TOK_RETURN", "TOK_REVERSE",
  "TOK_RPAD", "TOK_ROLLBACK", "TOK_ROUND", "TOK_ROWCOUNT", "TOK_ROWTYPE",
  "TOK_RTRIM", "TOK_SELECT", "TOK_SEQUENCE", "TOK_SERVER", "TOK_SERVICE",
  "TOK_SESSION", "TOK_SESSION_ID", "TOK_SET", "TOK_SLOT", "TOK_SIZE",
  "TOK_SQL", "TOK_SQRT", "TOK_START", "TOK_SUBSTR", "TOK_SUM",
  "TOK_SUMMARY", "TOK_SYNC", "TOK_SYSDATE", "TOK_SYSTEM", "TOK_TABLE",
  "TOK_TARGET", "TOK_TERMINATE", "TOK_THEN", "TOK_TIMEOUT", "TOK_TO",
  "TOK_TO_DATE", "TOK_TO_TIMESTAMP", "TOK_TRIM", "TOK_TRUNC",
  "TOK_TRUNCATE", "TOK_TYPE", "TOK_UNIQUE", "TOK_UPDATE", "TOK_UPPER",
  "TOK_USERENV", "TOK_USING", "TOK_UINT", "TOK_UNUM", "TOK_VALUES",
  "TOK_WHEN", "TOK_WHERE", "TOK_WHILE", "TOK_WITH", "TOK_CHAR", "TOK_DATE",
  "TOK_DATEDIFF", "TOK_DATETIME_STR", "TOK_DOUBLE", "TOK_FLOAT",
  "TOK_LONG", "TOK_INT", "TOK_INTEGER", "TOK_SHORT", "TOK_COUNT", "TOK_EQ",
  "TOK_GT", "TOK_GE", "TOK_LE", "TOK_LT", "TOK_NE", "$accept",
  "start_syntax", "ddl_stmt", "dml_stmt", "dcl_stmt",
  "create_instance_stmt", "create_queue_stmt", "create_table_stmt",
  "create_index_stmt", "create_external_library_stmt",
  "create_sync_library_stmt", "user_lib_init_func", "user_lib_fini_func",
  "user_lib_func_list", "drop_instance_stmt", "drop_procedure_stmt",
  "drop_table_stmt", "drop_index_stmt", "drop_library_stmt",
  "truncate_stmt", "alter_system_stmt", "session_kill_stmt",
  "execute_aging_stmt", "alter_table_stmt", "default_val",
  "rebuild_index_stmt", "create_sequence_stmt", "drop_sequence_stmt",
  "alter_sequence_stmt", "seq_start_with", "seq_increment", "seq_max",
  "seq_min", "seq_cycle", "repl_send_stmt", "repl_mod_stmt",
  "reset_perf_stmt", "change_instance_active_stmt",
  "reset_ckpt_fileno_stmt", "create_repl_stmt", "drop_repl_stmt",
  "create_capture_stmt", "drop_capture_stmt", "ora_insert_stmt",
  "ora_insert_columns", "insert_stmt", "expired_time", "ora_update_stmt",
  "update_stmt", "json_function_item", "ora_delete_stmt", "delete_stmt",
  "select_stmt", "limit_phrase", "enqueue_stmt", "dequeue_stmt",
  "load_stmt", "sync_stmt", "exec_proc_stmt", "index_key_list",
  "index_key_column", "order_by_stmt", "ordering", "group_by_list",
  "for_update", "table_source_list", "table_source", "update_target_list",
  "update_item", "where_cond_expr", "insert_columns", "column_def_list",
  "column_def", "declare_data_type", "obj_init_option",
  "obj_extend_option", "obj_max_option", "create_procedure_stmt",
  "proc_param_phrase", "proc_block_section", "proc_block_exception",
  "proc_exception_list", "proc_exception_item", "proc_stmt_list",
  "proc_label", "proc_stmt", "proc_raise_item", "proc_param_using",
  "proc_case_when_list", "proc_case_when_item", "proc_case_end",
  "proc_exit_stmt", "proc_continue_stmt", "proc_if_stmt", "proc_else_stmt",
  "proc_elseif_list", "proc_declare_section", "proc_declare_data_type",
  "declare_proc_item", "proc_cursor_param", "proc_param_section",
  "param_item", "proc_param_in_out", "int_val", "minus_val", "num_val",
  "identifier", "proc_attrib_var", "proc_attribute", "host_variable",
  "dynamic_param", "quote_val", "double_quote_val", "identifier_chain",
  "double_quote_chain", "identifier_list", "value_expr", "value_expr_list",
  "value_OR", "value_AND", "value_single", "const_value",
  "user_lib_function", "built_function", "instr_function",
  "to_date_function", "to_timestamp_function", "nvl_function",
  "upper_function", "lower_function", "decode_function",
  "decode_extra_item", "decode_item_list", "decode_item",
  "random_function", "datetime_str_function", "ltrim_function",
  "rtrim_function", "lpad_function", "rpad_function", "length_function",
  "digest_function", "hex_function", "in_function", "string_function",
  "substr_function", "dump_function", "mod_function", "ceil_function",
  "floor_function", "round_function", "trunc_function", "number_function",
  "aggr_function", "comp_function", "sequence_function", "alter_gsb_stmt",
  "gsb_name", "gsb_node_name", "gsb_server_grp_name", "gsb_server_name",
  "gsb_library", "gsb_function", "gsb_port", "gsb_client_min",
  "gsb_client_cnt", "gsb_client_max", "gsb_process_max",
  "gsb_process_count", "gsb_q_size", "gsb_influx_ip", "gsb_influx_port",
  "gsb_influx_database", "create_gsb_node", "drop_gsb_node",
  "create_gsb_monitor", "drop_gsb_monitor", "create_gsb_server_group",
  "drop_gsb_server_group", "create_gsb_server", "drop_gsb_server",
  "create_gsb_service", "drop_gsb_service", "alter_gsb_process_count", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488
};
# endif

#define YYPACT_NINF -946

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-946)))

#define YYTABLE_NINF -248

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     952,    78,    55,   230,  -946,   805,   230,   104,   130,   138,
      97,   -18,   230,  -946,   135,   139,  -946,   210,  -946,  1236,
     204,   157,   192,   267,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
      62,  -946,   -46,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,   230,    76,   230,   102,    33,
     230,   230,   252,   893,  -946,   324,   172,   230,   149,   265,
     226,   230,   230,   230,   230,   238,   230,   320,   230,   351,
     435,   154,   192,   230,   230,   232,   230,   230,   230,   230,
     230,  -946,   230,   230,   230,   451,   192,   230,   455,   151,
     400,  2486,  -946,   481,   485,   491,   492,   500,   505,   507,
     511,   512,   520,   521,   529,   530,   539,  -946,   550,   563,
     568,   572,   578,   579,   583,   584,   609,   610,   627,   630,
     631,   632,   633,  -946,   634,   635,  -946,  -946,   636,   638,
     640,   641,   642,  -946,   490,   644,   646,   647,  -946,   648,
     649,   650,   651,   652,   653,  -946,  -946,   654,   655,   656,
    -946,  -946,  -946,  -946,   580,  -946,  -946,  -946,  -946,  -946,
      51,   525,  -946,    44,    75,   659,  -946,   125,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,   230,
     230,   230,   487,    15,  -946,    55,  -946,   657,   660,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,   211,  -946,    64,
     516,   489,   494,   504,    12,   230,    41,    10,    69,    11,
     664,   459,   617,  -946,  1424,   230,   680,    17,   681,   586,
      18,   230,   230,   230,  2486,   585,    55,   684,   230,   230,
     690,   686,  1612,   230,  2486,   687,   691,   693,   695,  -946,
    -946,   696,   373,    61,  2486,   551,   524,   230,   230,   230,
     230,   -35,   230,   573,   612,   710,   537,  2486,   536,   230,
     714,   230,   230,   629,    55,   510,    21,   510,  -946,   230,
     230,    90,   230,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
     721,  1778,   721,   286,   721,   230,  -946,  -946,   230,   382,
     147,  2652,  2486,  2486,  2652,  2486,  2486,  2486,   722,   724,
    2486,  2486,  2486,  2486,  2486,  2486,  2486,  2486,  2486,  1966,
    2486,  2486,  2486,  2486,  2486,  2486,  2486,  2486,  2486,  2486,
    2486,  2486,  2486,  2486,  2486,  2486,  2486,   187,  2486,  2486,
    2486,  2486,  2486,  2486,  2486,  2486,   582,  2486,  2486,  2154,
     187,  2486,   159,   726,   587,  2486,   230,  2818,   230,  2818,
    2652,  2652,  2652,  2652,  2652,   600,  2652,  2652,  2652,  2652,
    2652,  2652,  2652,   721,  -946,  -946,   277,   277,   252,  -946,
      12,  -946,  2486,   230,  -109,   509,   230,   230,   688,   532,
    -946,   728,   732,  -946,  -946,   230,  -946,  -946,    40,   701,
    -946,   702,   230,   703,  -946,   230,   459,  -946,  -946,  2486,
     -30,  -946,   528,   736,  -946,  -946,  2486,   598,   230,  -946,
    2486,   658,   661,   743,   590,   230,    50,  -946,   790,   786,
    -946,   797,  -946,   692,    35,   678,  -946,  -946,  -946,  -946,
    -946,  2486,   791,  2486,   207,   230,  2486,   801,   689,  -946,
     803,   806,   230,   807,   809,   230,    12,   727,    42,   715,
      12,   808,   604,   716,   700,   230,   682,   334,  -946,   171,
     665,   252,  2486,  -946,  -946,   628,  -946,  -946,   230,  -946,
    -946,   230,   618,  -946,   419,   621,   587,   738,   816,     7,
    -946,   230,  2818,  -946,  2652,  2652,  2652,  2652,  2652,   408,
     822,   824,   394,   823,   828,   436,  -946,  -946,   825,   754,
     834,   835,   838,   837,   839,   844,   846,   841,   440,   441,
     850,   851,   853,   854,   859,   448,   857,   863,   861,   862,
     864,   865,   866,   867,   452,   466,  -946,  -946,  -946,  -946,
    -946,   871,   869,   873,   472,   876,   877,   479,   878,   879,
     881,   880,   885,   888,  -946,   556,  -946,  -946,  -946,  2486,
    -946,  -946,     7,  2486,   659,  -946,  -946,   390,   359,   193,
     852,  -946,  -946,   467,   467,   467,   467,   467,   467,   467,
     788,  -946,    14,  -946,   663,     4,    14,   829,   892,   889,
    -946,  -946,   676,   732,   732,   677,   230,    12,  -946,  -946,
     732,   897,   230,  -946,   230,   712,  -946,   713,    55,   870,
    -946,   900,   -30,  -946,   901,   907,   905,   230,  2320,  -946,
      55,   795,   911,  -946,   913,   230,   230,    55,   557,  -946,
     916,  -946,   710,   808,   230,   582,   230,    12,   918,   230,
     230,   928,  -946,    12,   810,  -946,   558,    43,   612,    12,
     902,   812,   582,   576,  -946,   301,   230,  -946,   230,  -946,
    -946,  -946,   339,   930,   874,  -946,    12,  -946,   591,   938,
    -946,   941,   592,  -946,   582,   797,   230,   811,  -946,   599,
     574,   501,   307,   341,   531,  -946,  -946,  -946,  2652,  2486,
    2486,  -946,  2486,  -946,  2486,  -946,  -946,  -946,  2486,  2486,
    2486,  2486,  -946,  -946,  -946,  2486,  -946,  -946,  2486,  -946,
    2486,  -946,  2486,  -946,  -946,  2486,  2486,  2486,  2486,  2486,
    2486,  -946,  2486,  -946,  2486,  -946,  2486,  -946,  -946,  2486,
    -946,  -946,  -946,  2486,  -946,  -946,  2486,  -946,  -946,  -946,
    -946,   597,   860,   412,   582,   277,  -946,  2486,  2486,  -946,
    -946,  -946,  -946,    12,    12,   728,  -946,   230,  -946,   755,
      55,    55,   141,  -946,  -946,   942,  -946,  2486,  -946,   402,
    2486,   929,   300,   943,  -946,   582,    81,   122,   166,  -946,
    -946,   868,   603,   855,  -946,   946,  -946,   949,   230,  -946,
     951,  -946,   953,   148,  -946,    12,  -946,  -946,   954,   727,
    -946,    12,    12,   840,   855,   612,   230,  -946,   962,  -946,
    -946,  -946,  -946,  -946,  -946,  2486,  2486,   761,   587,   765,
     966,  -946,   939,   891,  -946,  -946,  -946,  -946,  -946,   493,
     967,   969,  -946,   974,   975,   977,   607,   978,   981,   983,
     984,   986,   989,   994,   996,   997,   999,  1003,  1001,  1006,
    1010,  1011,   613,  1012,  1013,  1016,  -946,   988,   811,   819,
    -946,  -946,  -946,  -946,  -946,  -946,   971,   230,    34,    -4,
     992,  -946,  1020,  -946,  1014,  2486,    55,  2486,   940,  1025,
     357,  -946,  1031,   230,   230,   917,    43,   810,   582,   959,
     582,    12,  1034,    12,   582,  1037,   614,  -946,   152,   152,
    -946,  1041,   810,  -946,  -946,    12,    20,   959,   727,  -946,
     148,   615,   619,  1039,  -946,   230,  1035,  2486,   845,   934,
    -946,  2486,  2486,  1040,  -946,  -946,  -946,  -946,  2486,  -946,
    -946,  -946,  -946,  -946,  2486,  -946,  -946,  -946,  -946,  -946,
    2486,  2486,  -946,  -946,  -946,  2486,  -946,  -946,  -946,  2486,
     891,   230,  2486,  1045,  -946,  -946,  1043,  2486,   933,   233,
     875,  -946,  1046,  1047,     7,     7,  1048,  1050,  -946,  -946,
     582,   976,  -946,  1053,  -946,  1056,  -946,  -946,  1057,  -946,
    1059,   230,  -946,   148,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,   976,   810,   620,  -946,   995,  2486,
    1066,  -946,   808,  -946,    12,  -946,  -946,   967,  -946,  -946,
     624,  1067,  1068,  1069,  1070,   808,   934,  1073,  -946,  -946,
    -946,   958,    55,   980,    55,  -946,   860,   860,  -946,  1078,
    -946,   230,  1072,    12,    12,    12,   230,  1074,  -946,  1072,
    -946,  -946,    12,  -946,   625,   582,  1075,  -946,  2486,  -946,
    -946,  -946,  -946,  -946,   582,    55,   257,  -946,   272,   891,
     891,  -946,   582,   230,  -946,  1076,  -946,  1080,  -946,  1079,
    -946,  1081,   582,  -946,  -946,  1082,    12,  1083,  1084,   264,
     973,  1086,  1087,  -946,   582,   582,  -946,    12,  -946,  1089,
     582,  -946,  -946,   582,   982,  1091,  -946,  -946,  -946,  -946,
    1093,  1096,    12,  1100,  1101,  1092,  -946,  -946,    12,  1102,
     995,  -946,  -946,  -946,  1104,   152,  -946,  -946,  -946
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,   201,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,   274,     0,     0,   275,     0,    43,     0,
       0,     0,     0,     0,     2,     3,     4,     5,     7,     6,
       8,     9,    10,    11,    28,    12,    13,    14,    15,    16,
      73,    72,    21,    22,    18,    19,    20,    67,    68,    71,
      69,    70,    23,    24,    25,    26,    39,    29,    40,    30,
      41,    31,    32,    33,    34,    35,    36,    37,    27,    38,
       0,   250,     0,    17,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,     0,     0,     0,     0,     0,
       0,     0,   201,     0,   199,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     260,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,     0,     0,   140,     0,     0,     0,     0,
       0,     0,   283,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   282,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   314,     0,     0,   284,   285,     0,     0,
       0,     0,     0,   344,     0,     0,     0,     0,   318,     0,
       0,     0,     0,     0,     0,   269,   272,     0,     0,     0,
     350,   307,   270,   308,   286,   312,   309,   310,   306,   288,
     304,   305,   294,     0,   292,   296,   299,   302,   313,   311,
     343,   347,   348,   342,   340,   341,   339,   338,   337,   327,
     328,   330,   331,   326,   336,   335,   334,   325,   332,   319,
     320,   321,   322,   323,   324,   317,   316,   303,   333,     0,
       0,     0,     0,     0,     1,   201,   251,     0,     0,   179,
     176,   175,   177,   174,   173,   172,   252,     0,   286,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,     0,     0,   230,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   214,
     215,     0,   286,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   188,     0,     0,    87,     0,
       0,     0,     0,     0,   201,   165,   165,   165,   112,     0,
       0,     0,     0,    63,    59,    64,    60,    62,    85,    61,
     167,     0,   167,     0,   167,     0,   271,   273,     0,     0,
     302,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   167,    66,    65,     0,     0,   201,   258,
       0,   255,     0,     0,     0,     0,     0,     0,     0,     0,
      74,   290,    76,   106,   107,     0,   105,   102,    98,     0,
      80,     0,     0,     0,   202,     0,   195,   196,   192,     0,
       0,   234,     0,     0,   228,   241,     0,     0,     0,   239,
       0,     0,     0,     0,     0,     0,   201,   204,   232,     0,
     231,     0,   229,     0,     0,     0,   209,   210,   211,   203,
     212,     0,     0,     0,     0,     0,     0,     0,     0,   438,
       0,     0,     0,     0,     0,     0,     0,   182,     0,     0,
       0,   109,     0,    89,     0,     0,     0,     0,   262,   265,
       0,   201,     0,   127,   126,   134,   457,   455,     0,   461,
     463,     0,     0,   141,     0,     0,     0,     0,     0,   165,
     156,   158,     0,   300,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   352,   353,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   279,   278,   280,   281,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,     0,   426,   425,   287,     0,
     289,   295,   165,     0,   297,   293,   301,   402,   404,   406,
     408,   390,   424,   423,   417,   419,   418,   420,   421,   422,
       0,   163,   165,   160,     0,     0,   165,     0,     0,     0,
     254,   253,     0,   103,   104,     0,     0,     0,   100,    99,
     101,     0,     0,    83,     0,     0,   197,     0,   201,     0,
     235,     0,     0,   224,     0,     0,     0,     0,     0,   221,
     201,     0,     0,   225,     0,     0,     0,   201,     0,   227,
       0,   138,   188,   111,     0,     0,     0,     0,     0,     0,
       0,     0,   181,     0,   184,   190,     0,     0,   180,     0,
       0,    91,     0,     0,   169,     0,     0,   261,     0,   266,
     268,   267,     0,     0,     0,   166,     0,   459,     0,     0,
     139,     0,     0,   114,     0,     0,     0,   147,   159,   297,
     402,   404,   406,   408,     0,   410,   414,   396,     0,     0,
       0,   393,     0,   357,     0,   397,   387,   354,     0,     0,
       0,     0,   346,   345,   125,     0,   385,   358,     0,   370,
       0,   379,     0,   415,   416,     0,     0,     0,     0,     0,
       0,   398,     0,   381,     0,   356,     0,   413,   365,     0,
     367,   329,   400,     0,   369,   351,     0,   378,   412,   411,
     315,     0,   152,     0,     0,     0,   120,     0,     0,   119,
     191,   178,   256,     0,     0,   291,   108,     0,    79,     0,
     201,   201,   201,   237,   217,     0,   242,     0,   240,     0,
       0,     0,   201,     0,   222,     0,     0,     0,   201,   233,
     205,     0,     0,    52,   439,     0,   444,     0,     0,   440,
       0,   441,     0,     0,   183,     0,    44,   189,     0,   182,
      88,     0,     0,    93,    52,   180,     0,   171,     0,   263,
     264,   257,   193,   135,   168,     0,     0,     0,     0,     0,
       0,   157,     0,   154,   298,   403,   405,   407,   409,     0,
       0,   372,   374,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   388,     0,   147,     0,
     161,   162,   164,   449,   464,    86,    81,     0,   201,   201,
       0,   216,     0,   223,     0,     0,   201,     0,     0,   248,
       0,   213,     0,     0,     0,     0,     0,   184,     0,    54,
       0,     0,     0,     0,     0,     0,     0,   142,   149,   149,
     185,     0,   184,    90,    92,     0,    95,    54,   182,   170,
       0,     0,     0,     0,   115,     0,     0,     0,     0,   130,
     389,     0,     0,     0,   386,   394,   364,   361,     0,   121,
     122,   123,   124,   359,     0,   380,   395,   368,   355,   377,
       0,     0,   399,   382,   391,     0,   366,   401,   349,     0,
     154,     0,     0,     0,    77,   238,     0,     0,     0,   201,
       0,   245,   249,     0,   165,   165,     0,     0,    47,    53,
       0,    56,   451,     0,   447,     0,   458,   445,     0,   442,
       0,     0,    49,     0,   150,   151,   144,   145,   186,    45,
      94,    96,    97,    84,    56,   184,     0,   133,   117,     0,
       0,   259,   148,   155,     0,   129,   376,   373,   375,   371,
       0,     0,     0,     0,     0,   153,   130,     0,    82,    78,
     206,     0,   201,     0,   201,   226,   152,   152,   220,     0,
      55,     0,    50,     0,     0,     0,     0,     0,   143,    51,
      46,    48,     0,   116,     0,     0,   131,   362,     0,   383,
     360,   384,   392,   128,     0,   201,   201,   246,   201,   154,
     154,   187,     0,     0,   452,     0,   448,     0,   446,     0,
     443,     0,     0,   118,   113,     0,     0,     0,     0,   201,
       0,     0,     0,    57,     0,     0,   454,     0,   462,     0,
       0,   132,   363,     0,     0,     0,   208,   207,    58,   453,
       0,     0,     0,     0,     0,     0,   218,   456,     0,     0,
     117,   137,   219,   450,     0,   149,   136,   460,   146
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,   240,   158,    72,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  1024,   -42,  -946,  1026,  -409,
    -946,  1027,   601,    57,  -946,  -946,  -946,  -946,  -946,   164,
      93,   217,  -936,  -596,  -945,  -401,   403,   704,   333,  -312,
    -264,   446,  -719,   427,  -665,  -809,  -884,  -946,   453,   -89,
    -366,  -946,   697,  -235,  -946,   -91,  -946,   662,   671,  -439,
     474,  -946,  -946,  -946,   214,  -946,  1127,   425,    92,  -946,
     637,   438,  -946,  -230,  -472,  -946,     0,  -946,   751,  -946,
    -946,  -211,  -402,   -64,    13,  -398,   399,  -150,  -120,  -360,
    -946,   133,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,   180,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -286,   318,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,    23,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,   939,  1021,  1082,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,  1003,    43,    44,    45,    46,   513,
     701,   853,   956,  1043,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,   722,    57,  1093,    58,    59,   190,
      60,    61,    62,  1055,    63,    64,    65,    66,    67,   946,
     947,   873,  1036,   908,   969,   539,   540,   632,   633,   523,
     532,   703,   704,   256,   507,   694,   846,    68,   509,    69,
     272,   456,   457,    92,    93,    94,   479,   492,   460,   461,
     661,   299,   300,   301,   929,   930,    70,   257,    71,   323,
     517,   518,   712,   191,   192,   193,   194,   195,   590,   196,
     197,   198,   199,   200,   201,   442,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   973,   881,   882,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,    73,   500,   835,   840,
     842,  1030,  1121,   837,  1028,  1119,  1025,  1117,   914,  1164,
    1023,  1115,  1150,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,   273,   610,    95,   298,   612,   110,    72,   259,   674,
     428,   349,   125,  1037,   524,   525,   439,   631,   631,   404,
     726,   660,   242,    91,   501,   503,   504,   795,   247,   303,
     404,   465,   469,   849,   440,   243,   404,   658,   643,   644,
     952,   659,   449,   526,   527,   529,   530,   614,   405,   616,
     650,   476,   695,  1018,   445,  1066,   502,   405,    13,   450,
     401,    91,   637,  -236,   640,   265,   402,  -236,  1039,    13,
      72,   443,   258,   648,  1041,   451,   433,    91,   535,   433,
     537,     2,    91,   407,   434,   260,   493,   263,   916,   521,
     269,   270,   124,   302,   646,   641,     6,   306,    16,     7,
     245,   313,   314,   315,   316,  -198,   318,   261,   320,    16,
     408,    72,   325,   327,   328,     6,   333,   334,   335,   336,
     337,   671,   338,   339,   340,   326,   342,   344,   410,   411,
     412,   413,   406,   718,   723,   646,   414,   959,   114,   343,
     262,   266,   484,   444,    13,   676,    13,    13,   403,  1045,
     544,   545,   546,   547,   494,   714,  1042,     6,   414,   630,
     446,  1090,   246,   649,  1131,  1132,    13,   511,    91,   933,
      85,   248,   249,   452,   453,   250,   251,   252,   253,   254,
     255,   528,   729,   459,    16,   599,    16,    16,  1034,   115,
     958,   534,   324,    91,    13,    17,   427,   267,   268,   413,
     638,   441,   116,   246,   414,   117,    16,     6,    13,  -236,
     934,   606,   920,  1035,    17,   118,   688,   681,   112,   568,
     405,   522,   185,   660,   415,   431,   113,   727,   522,  1168,
     466,   470,   798,   447,    16,   522,   432,   935,   259,   423,
     424,   425,   717,    86,   416,   126,   415,  -198,    16,   127,
     119,   605,    13,   870,    87,   120,    17,    88,    13,   448,
      91,   945,   121,    13,   350,   258,   416,   244,   709,   819,
      89,    90,   710,   122,   586,   463,   692,   826,   827,    91,
     698,   471,   472,   473,    91,   128,  -247,   587,   478,   480,
     123,    91,    16,   242,   607,   536,    13,   264,    16,    91,
     792,   404,   258,    16,  1073,   167,    17,   497,   498,   499,
     499,   499,   499,   413,   239,   240,   711,   877,   414,   514,
     796,   516,   519,  -194,   799,   588,   271,    91,  1130,   499,
     499,   499,   499,   304,    13,  1144,    16,   273,   305,  -247,
    -247,   678,   307,  -247,   707,   538,   683,   708,   541,   167,
     241,   878,   414,   417,   418,   419,   420,   421,   422,   589,
     309,   346,   347,   310,   412,   413,   329,   926,   927,   330,
     414,   928,   441,   441,    16,   417,   418,   419,   420,   421,
     422,    13,   491,   308,   441,   273,   631,  -232,   149,   150,
     542,   151,   543,   153,   411,   412,   413,   410,   411,   412,
     413,   414,   608,   311,   312,   414,   541,   738,   615,   331,
     332,   410,   411,   412,   413,   646,   923,   806,   735,   414,
     407,    16,   543,   812,   926,   927,   634,   634,   928,   720,
     273,   317,   405,   608,   167,   822,   258,   258,   319,   635,
     635,   949,   828,    13,   322,   647,   741,   247,   258,   742,
     753,   754,   653,   405,   755,   655,   321,   836,   761,   791,
     341,   762,   771,   844,   345,   772,   964,   441,   325,   850,
     410,   411,   412,   413,   833,   342,   773,    13,   414,   774,
    1109,  1110,   778,    16,   549,   779,   863,   552,   348,   782,
     351,   854,   783,   793,   352,   682,   410,   411,   412,   413,
     353,   354,   499,   970,   414,   691,   412,   413,   519,   355,
     387,   876,   414,   869,   356,   705,   357,    16,   248,   249,
     358,   359,   250,   251,   252,   253,   254,   255,   499,   360,
     361,   258,  1014,  1015,   544,   545,   546,   547,   362,   363,
     404,   728,   414,   617,   618,   619,   620,   621,   364,   623,
     624,   625,   626,   627,   628,   629,   248,   249,   949,   365,
     250,   251,   252,   253,   254,   255,   790,   829,   847,   405,
     405,   708,   366,   913,   915,   918,   919,   367,   411,   412,
     413,   368,   805,   909,   875,   414,   855,   369,   370,   856,
     248,   249,   371,   372,   250,   251,   252,   253,   254,   255,
     400,   864,   867,   441,   646,   868,   409,   906,   848,   874,
     405,   441,   441,   937,   932,   950,   856,   977,   373,   374,
     978,   953,   954,   994,  1032,  1047,   995,  1033,   405,  1048,
    1091,   949,   405,  1033,  1097,  1124,   375,  1098,   405,   376,
     377,   378,   379,   380,   381,   382,   258,   383,   259,   384,
     385,   386,   808,   388,   809,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   409,   258,   426,   430,
     435,   429,   455,   462,   468,   258,   258,   730,   731,   732,
     733,   734,   436,   474,   705,   438,   834,   437,   458,   839,
     841,  1009,   454,   485,   464,   475,   467,    72,   477,   481,
     482,   486,  1076,  1077,   495,   487,   858,   488,   519,   489,
     490,  1024,   258,  1027,   505,   961,   962,   496,   506,   508,
     510,   273,   512,   515,   522,  1040,   541,  1019,   520,  1022,
     531,   273,   556,  1029,   557,   609,   642,   273,   166,   622,
     645,   459,   346,   433,   167,   646,   350,   651,   652,   654,
     663,   550,   551,   665,   553,   554,   555,   669,   668,   558,
     559,   560,   561,   562,   563,   564,   565,   566,   667,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   670,   591,   592,   593,
     594,   595,   596,   597,   598,   634,   600,   601,   603,   491,
     673,   439,   675,   677,   611,   679,   693,   705,   635,  1080,
     684,   685,   686,    96,   697,   687,   689,  1052,   690,   700,
     699,   405,   702,   706,  1096,   716,   724,   273,   273,   725,
     719,   639,   736,   721,   737,   743,   739,  1106,   834,  1108,
      19,   740,   744,   948,   745,   746,    97,  1017,   747,  1065,
     748,   752,   749,  1114,  1116,  1118,   705,   750,   657,   751,
     756,   757,  1123,   414,   759,   664,   758,   763,    98,   666,
    1129,   879,   760,   764,   765,   766,   794,   767,   768,   769,
     770,   775,   776,   777,  1125,    99,   780,   781,   784,   785,
     787,   797,   680,  1128,   786,   788,  1141,   100,   789,  1094,
     800,  1133,   801,   802,   803,   804,   807,  1024,   810,   811,
     101,  1139,   813,   102,   814,   816,   817,  1004,   273,   818,
     823,   715,  1159,  1148,  1149,   824,   825,   838,  1163,  1153,
     830,     2,  1154,   541,   541,   274,    72,   843,   275,   845,
     276,   851,   852,   277,   861,   862,     6,   865,   278,     7,
     866,   907,   279,   917,   872,   925,   921,   931,   103,   940,
     948,   938,   941,   104,   943,  1050,   944,   936,   951,   280,
     105,   960,   955,   963,   965,   281,   966,   968,   967,   282,
     971,   106,   972,   283,   974,   975,     1,   976,   979,   284,
       2,   980,     3,   981,   982,   107,   983,    13,   108,     4,
     285,  1067,   984,     5,   985,     6,   986,   987,     7,   988,
     109,     8,     9,   989,   990,   273,    10,   273,   286,   991,
     992,   993,   996,   997,    11,    12,   998,   999,  1001,  1002,
    1006,  1087,   287,   948,  1005,   288,  1011,    16,   273,  -243,
    1007,  1013,  1016,  1020,  1026,    17,  1031,  1038,  1049,  1051,
    1059,  1053,   289,   290,  1054,  1069,    13,  1070,  1072,    14,
    -244,  1075,  1078,   291,  1079,  1081,  1083,   821,   292,  1084,
    1085,  1074,  1086,  1092,    15,  1095,  1107,  1099,  1100,  1101,
    1102,  1112,  1104,  1105,  1111,  1113,  1120,  1122,  1126,  1135,
    1136,  1138,  1137,  1142,   957,  1140,    16,  1143,  1145,   293,
    1146,  1147,  1152,  1157,    17,  1156,  1162,  1155,   294,  1158,
    1160,  1161,  1165,  1134,  1167,  1044,  1089,   295,  1166,   296,
     297,   713,    18,  1103,  1046,  1000,  1088,    19,   910,   871,
     832,   636,   857,   662,   111,   831,   815,   860,   880,   883,
     672,   884,    20,   885,  1012,   696,   859,   886,   887,   888,
     889,   604,  1058,   656,   890,    21,   942,   891,    22,   892,
    1151,   893,     0,     0,   894,   895,   896,   897,   898,   899,
       0,   900,     0,   901,     0,   902,     0,     0,   903,     0,
       0,     0,   904,     0,     0,   905,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   911,   912,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   922,     0,     0,   924,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,     0,     0,     0,   131,     0,     0,     0,     0,
       0,     0,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,     0,     0,     0,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,   135,
       0,     0,     0,     0,     0,   136,     0,     0,     0,     0,
       0,     0,     0,   137,     0,     0,     0,     0,   138,     0,
       0,   139,     0,     0,     0,   140,   141,     0,     0,     0,
       0,     0,     0,   142,     0,     0,     0,   143,     0,     0,
       0,   144,     0,     0,  1008,     0,  1010,     0,     0,   145,
     146,   147,     0,     0,   148,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,   149,   150,     0,
     151,   152,   153,   154,     0,     0,     0,   155,     0,     0,
     156,     0,   157,   158,   159,   160,     0,   161,     0,   162,
    1056,  1057,     0,     0,     0,   163,   164,  1060,     0,     0,
      16,     0,     0,  1061,     0,     0,     0,   165,     0,  1062,
    1063,     0,   166,   167,  1064,     0,     0,   168,     0,     0,
       0,  1068,   169,     0,     0,   170,  1071,   171,     0,     0,
     172,     0,     0,     0,     0,     0,   173,     0,     0,     0,
     174,   175,     0,   176,   177,     0,     0,   178,   129,     0,
       0,     0,     0,   131,     0,   179,   180,   181,   182,     0,
     132,     0,     0,   183,   184,     0,   185,   186,     0,     0,
       0,     0,     0,   133,     0,   187,   188,     0,     0,     0,
       0,   134,     0,   189,     0,     0,     0,   135,     0,     0,
       0,     0,     0,   136,     0,     0,     0,     0,     0,     0,
       0,   137,     0,     0,     0,     0,   138,     0,     0,   139,
       0,     0,     0,   140,   141,     0,     0,  1127,     0,     0,
       0,   142,     0,     0,     0,   143,     0,     0,     0,   144,
       0,     0,     0,     0,     0,     0,     0,   145,   146,   147,
       0,     0,   148,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,     0,   149,   150,     0,   151,   152,
     153,   154,     0,     0,     0,   155,     0,     0,   156,     0,
     157,   158,   159,   160,     0,   161,     0,   162,     0,     0,
       0,     0,     0,   163,   164,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     0,   165,     0,     0,     0,     0,
     166,   167,     0,     0,     0,   168,     0,     0,     0,     0,
     169,     0,     0,   170,     0,   171,     0,     0,   172,     0,
       0,     0,     0,     0,   173,     0,     0,     0,   174,   175,
       0,   176,   177,     0,     0,   178,   129,   483,     0,     0,
       0,   131,     0,   179,   180,   181,   182,     0,   132,     0,
       0,   183,   184,     0,   185,   186,     0,   459,     0,     0,
       0,   133,     0,   187,   188,     0,     0,     0,     0,   134,
       0,   189,     0,     0,     0,   135,     0,     0,     0,     0,
       0,   136,     0,     0,     0,     0,     0,     0,     0,   137,
       0,     0,     0,     0,   138,     0,     0,   139,     0,     0,
       0,   140,   141,     0,     0,     0,     0,     0,     0,   142,
       0,     0,     0,   143,     0,     0,     0,   144,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,     0,     0,
     148,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,     0,   149,   150,     0,   151,   152,   153,   154,
       0,     0,     0,   155,     0,     0,   156,     0,   157,   158,
     159,   160,     0,   161,     0,   162,     0,     0,     0,     0,
       0,   163,   164,     0,     0,     0,    16,     0,     0,     0,
       0,     0,     0,   165,     0,     0,     0,     0,   166,   167,
       0,     0,     0,   168,     0,     0,     0,     0,   169,     0,
       0,   170,   129,   171,     0,     0,   172,   131,   533,     0,
       0,     0,   173,     0,   132,     0,   174,   175,     0,   176,
     177,     0,     0,   178,     0,     0,     0,   133,     0,     0,
       0,   179,   180,   181,   182,   134,     0,     0,     0,   183,
     184,   135,   185,   186,     0,     0,     0,   136,     0,     0,
       0,   187,   188,     0,     0,   137,     0,     0,     0,   189,
     138,     0,     0,   139,     0,     0,     0,   140,   141,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,   143,
       0,     0,     0,   144,     0,     0,     0,     0,     0,     0,
       0,   145,   146,   147,     0,     0,   148,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,     0,   149,
     150,     0,   151,   152,   153,   154,     0,     0,     0,   155,
       0,     0,   156,     0,   157,   158,   159,   160,     0,   161,
       0,   162,     0,     0,     0,     0,     0,   163,   164,     0,
       0,     0,    16,     0,     0,     0,     0,     0,     0,   165,
       0,     0,     0,     0,   166,   167,     0,     0,     0,   168,
       0,     0,     0,     0,   169,     0,     0,   170,     0,   171,
       0,     0,   172,     0,     0,     0,     0,     0,   173,     0,
       0,     0,   174,   175,     0,   176,   177,     0,     0,   178,
     129,   567,     0,     0,     0,   131,     0,   179,   180,   181,
     182,     0,   132,     0,     0,   183,   184,     0,   185,   186,
       0,     0,     0,     0,     0,   133,     0,   187,   188,     0,
       0,     0,     0,   134,     0,   189,     0,     0,     0,   135,
       0,     0,     0,     0,     0,   136,     0,     0,     0,     0,
       0,     0,     0,   137,     0,     0,     0,     0,   138,     0,
       0,   139,     0,     0,     0,   140,   141,     0,     0,     0,
       0,     0,     0,   142,     0,     0,     0,   143,     0,     0,
       0,   144,     0,     0,     0,     0,     0,     0,     0,   145,
     146,   147,     0,     0,   148,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,   149,   150,     0,
     151,   152,   153,   154,     0,     0,     0,   155,     0,     0,
     156,     0,   157,   158,   159,   160,     0,   161,     0,   162,
       0,     0,     0,     0,     0,   163,   164,     0,     0,     0,
      16,     0,     0,     0,     0,     0,     0,   165,     0,     0,
       0,     0,   166,   167,     0,     0,     0,   168,     0,     0,
       0,     0,   169,     0,     0,   170,     0,   171,     0,     0,
     172,     0,     0,     0,     0,     0,   173,     0,     0,     0,
     174,   175,     0,   176,   177,     0,     0,   178,   129,   602,
       0,     0,     0,   131,     0,   179,   180,   181,   182,     0,
     132,     0,     0,   183,   184,     0,   185,   186,     0,     0,
       0,     0,     0,   133,     0,   187,   188,     0,     0,     0,
       0,   134,     0,   189,     0,     0,     0,   135,     0,     0,
       0,     0,     0,   136,     0,     0,     0,     0,     0,     0,
       0,   137,     0,     0,     0,     0,   138,     0,     0,   139,
       0,     0,     0,   140,   141,     0,     0,     0,     0,     0,
       0,   142,     0,     0,     0,   143,     0,     0,     0,   144,
       0,     0,     0,     0,     0,     0,     0,   145,   146,   147,
       0,     0,   148,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,     0,   149,   150,     0,   151,   152,
     153,   154,     0,     0,     0,   155,     0,     0,   156,     0,
     157,   158,   159,   160,     0,   161,     0,   162,     0,     0,
       0,     0,     0,   163,   164,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     0,   165,     0,     0,     0,     0,
     166,   167,     0,     0,     0,   168,     0,     0,     0,     0,
     169,     0,     0,   170,   129,   171,     0,     0,   172,   131,
       0,     0,     0,     0,   173,     0,   132,     0,   174,   175,
       0,   176,   177,     0,     0,   178,     0,     0,     0,   133,
       0,     0,     0,   179,   180,   181,   182,   134,     0,     0,
       0,   183,   184,   135,   185,   186,     0,     0,     0,   136,
       0,     0,     0,   187,   188,     0,     0,   137,     0,     0,
       0,   189,   138,     0,     0,   139,     0,     0,     0,   140,
     141,     0,     0,     0,     0,     0,     0,   142,     0,     0,
       0,   143,     0,     0,     0,   144,     0,     0,     0,     0,
       0,     0,     0,   145,   146,   147,     0,     0,   148,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,   149,   150,     0,   151,   152,   153,   154,     0,     0,
       0,   155,     0,     0,   156,     0,   157,   158,   159,   160,
       0,   161,     0,   162,     0,     0,     0,     0,     0,   163,
     164,     0,     0,     0,    16,     0,     0,     0,     0,     0,
       0,   165,     0,     0,     0,     0,   166,   167,     0,     0,
       0,   168,     0,     0,     0,     0,   169,     0,   820,   170,
     129,   171,     0,     0,   172,   131,     0,     0,     0,     0,
     173,     0,   132,     0,   174,   175,     0,   176,   177,     0,
       0,   178,     0,     0,     0,   133,     0,     0,     0,   179,
     180,   181,   182,   134,     0,     0,     0,   183,   184,   135,
     185,   186,     0,     0,     0,   136,     0,     0,     0,   187,
     188,     0,     0,   137,     0,     0,     0,   189,   138,     0,
       0,   139,     0,     0,     0,   140,   141,     0,     0,     0,
       0,     0,     0,   142,     0,     0,     0,   143,     0,     0,
       0,   144,     0,     0,     0,     0,     0,     0,     0,   145,
     146,   147,     0,     0,   148,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,   149,   150,     0,
     151,   152,   153,   154,     0,     0,     0,   155,     0,     0,
     156,     0,   157,   158,   159,   160,     0,   161,     0,   162,
       0,     0,     0,     0,     0,   163,   164,     0,     0,     0,
      16,     0,     0,     0,     0,     0,     0,   165,     0,     0,
       0,     0,   166,   167,     0,     0,     0,   168,     0,     0,
       0,     0,   169,     0,     0,   170,   129,   171,     0,     0,
     172,   548,     0,     0,     0,     0,   173,     0,   132,     0,
     174,   175,     0,   176,   177,     0,     0,   178,     0,     0,
       0,   133,     0,     0,     0,   179,   180,   181,   182,   134,
       0,     0,     0,   183,   184,   135,   185,   186,     0,     0,
       0,   136,     0,     0,     0,   187,   188,     0,     0,   137,
       0,     0,     0,   189,   138,     0,     0,   139,     0,     0,
       0,   140,   141,     0,     0,     0,     0,     0,     0,   142,
       0,     0,     0,   143,     0,     0,     0,   144,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,     0,     0,
     148,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,     0,   149,   150,     0,   151,   152,   153,   154,
       0,     0,     0,   155,     0,     0,   156,     0,   157,   158,
     159,   160,     0,   161,     0,   162,     0,     0,     0,     0,
       0,   163,   164,     0,     0,     0,    16,     0,     0,     0,
       0,     0,     0,   165,     0,     0,     0,     0,   166,   167,
       0,     0,     0,   168,     0,     0,     0,     0,   169,     0,
       0,   170,   129,   171,     0,     0,   172,   613,     0,     0,
       0,     0,   173,     0,   132,     0,   174,   175,     0,   176,
     177,     0,     0,   178,     0,     0,     0,   133,     0,     0,
       0,   179,   180,   181,   182,   134,     0,     0,     0,   183,
     184,   135,   185,   186,     0,     0,     0,   136,     0,     0,
       0,   187,   188,     0,     0,   137,     0,     0,     0,   189,
     138,     0,     0,   139,     0,     0,     0,   140,   141,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,   143,
       0,     0,     0,   144,     0,     0,     0,     0,     0,     0,
       0,   145,   146,   147,     0,     0,   148,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,     0,   149,
     150,     0,   151,   152,   153,   154,     0,     0,     0,   155,
       0,     0,   156,     0,   157,   158,   159,   160,     0,   161,
       0,   162,     0,     0,     0,     0,     0,   163,   164,     0,
       0,     0,    16,     0,     0,     0,     0,     0,     0,   165,
       0,     0,     0,     0,   166,   167,     0,     0,     0,   168,
       0,     0,     0,     0,   169,     0,     0,   170,     0,   171,
       0,     0,   172,     0,     0,     0,     0,     0,   173,     0,
       0,     0,   174,   175,     0,   176,   177,     0,     0,   178,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,     0,     0,     0,     0,   183,   184,     0,   185,   186,
       0,     0,     0,     0,     0,     0,     0,   187,   188,     0,
       0,     0,     0,     0,     0,   189
};

static const yytype_int16 yycheck[] =
{
       0,    92,   404,     3,    93,   406,     6,     7,    72,   481,
     245,   131,    12,   949,   326,   327,     4,   426,   427,    15,
      13,   460,    22,    27,   310,   311,   312,    13,    74,    93,
      15,    14,    14,   698,   264,    22,    15,    67,   436,   437,
     849,    71,    31,   329,   330,   331,   332,   407,    13,   409,
     448,   286,    10,   937,    44,  1000,    91,    13,   104,    48,
       9,    27,   428,    67,   173,    32,    15,    71,   952,   104,
      70,    30,    72,    33,    54,    64,    15,    27,   342,    15,
     344,    38,    27,     8,    20,    85,    25,    87,   807,   324,
      90,    91,   110,    93,    13,   204,    53,    97,   144,    56,
      38,   101,   102,   103,   104,    71,   106,    31,   108,   144,
      35,   111,   112,   113,   114,    53,   116,   117,   118,   119,
     120,    71,   122,   123,   124,   112,   126,   127,     3,     4,
       5,     6,    88,   531,   536,    13,    11,   856,    41,   126,
      64,   108,   292,   102,   104,   110,   104,   104,    97,   958,
       3,     4,     5,     6,   304,   521,   136,    53,    11,   423,
     150,  1045,    70,   123,  1109,  1110,   104,   317,    27,    88,
      92,   217,   218,   162,   163,   221,   222,   223,   224,   225,
     226,    91,   542,   213,   144,   396,   144,   144,    36,    92,
     855,   341,    38,    27,   104,   152,   181,   164,   165,     6,
     430,   265,   105,   111,    11,   108,   144,    53,   104,   213,
      88,    52,    71,    61,   152,   118,   502,    10,    88,   369,
      13,   214,   210,   662,    99,    14,    88,   539,   214,  1165,
     213,   213,   228,   164,   144,   214,    25,    71,   302,   239,
     240,   241,   528,   165,   119,   110,    99,   213,   144,   110,
     153,   401,   104,   725,   176,   158,   152,   179,   104,   190,
      27,   113,   165,   104,   131,   265,   119,     0,    97,   667,
     192,   193,   101,   176,    87,   275,   506,   675,   676,    27,
     510,   281,   282,   283,    27,    75,    14,   100,   288,   289,
     193,    27,   144,   293,   135,     9,   104,   195,   144,    27,
     612,    15,   302,   144,    71,   157,   152,   307,   308,   309,
     310,   311,   312,     6,   110,   158,   145,    10,    11,   319,
     632,   321,   322,    71,   636,   138,    74,    27,    71,   329,
     330,   331,   332,     9,   104,    71,   144,   428,   166,    67,
      68,   491,   193,    71,    10,   345,   496,    13,   348,   157,
     193,    10,    11,   228,   229,   230,   231,   232,   233,   172,
     134,   210,   211,   137,     5,     6,   134,    67,    68,   137,
      11,    71,   436,   437,   144,   228,   229,   230,   231,   232,
     233,   104,     9,   118,   448,   476,   795,    14,   111,   112,
       8,   114,    10,   116,     4,     5,     6,     3,     4,     5,
       6,    11,   402,   177,   178,    11,   406,    13,   408,   177,
     178,     3,     4,     5,     6,    13,    14,   647,    10,    11,
       8,   144,    10,   658,    67,    68,   426,   427,    71,    10,
     521,   193,    13,   433,   157,   670,   436,   437,   118,   426,
     427,   843,   677,   104,     9,   445,    10,    74,   448,    13,
      10,    10,   452,    13,    13,   455,   105,   687,    10,   609,
       9,    13,    10,   693,     9,    13,   868,   531,   468,   699,
       3,     4,     5,     6,   685,   475,    10,   104,    11,    13,
    1076,  1077,    10,   144,   351,    13,   716,   354,    88,    10,
       9,   702,    13,   613,     9,   495,     3,     4,     5,     6,
       9,     9,   502,    10,    11,   505,     5,     6,   508,     9,
      20,    10,    11,   724,     9,   515,     9,   144,   217,   218,
       9,     9,   221,   222,   223,   224,   225,   226,   528,     9,
       9,   531,   933,   934,     3,     4,     5,     6,     9,     9,
      15,   541,    11,   410,   411,   412,   413,   414,     9,   416,
     417,   418,   419,   420,   421,   422,   217,   218,   960,     9,
     221,   222,   223,   224,   225,   226,    10,    10,    10,    13,
      13,    13,     9,   803,   804,   810,   811,     9,     4,     5,
       6,     9,   646,   794,    10,    11,    10,     9,     9,    13,
     217,   218,     9,     9,   221,   222,   223,   224,   225,   226,
      20,    10,    10,   667,    13,    13,     7,    10,   697,    10,
      13,   675,   676,    10,   825,   845,    13,    10,     9,     9,
      13,   851,   852,    10,    10,    10,    13,    13,    13,    10,
      10,  1033,    13,    13,    10,    10,     9,    13,    13,     9,
       9,     9,     9,     9,     9,     9,   646,     9,   712,     9,
       9,     9,   652,     9,   654,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     7,   667,   181,     9,
     154,    14,   213,   274,    88,   675,   676,   544,   545,   546,
     547,   548,   193,   284,   684,   181,   686,   193,    71,   689,
     690,   926,    28,   294,    14,   110,    15,   697,    14,     9,
      14,    14,  1014,  1015,   153,    14,   706,    14,   708,    14,
      14,   941,   712,   943,   141,   865,   866,   193,   106,     9,
     183,   812,   186,     9,   214,   955,   726,   938,    99,   940,
       9,   822,    10,   944,    10,     9,   227,   828,   156,   139,
      52,   213,   210,    15,   157,    13,   613,    46,    46,    46,
      14,   352,   353,   155,   355,   356,   357,    14,    97,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   110,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   196,   388,   389,   390,
     391,   392,   393,   394,   395,   795,   397,   398,   399,     9,
      14,     4,   110,   125,   405,    14,    79,   807,   795,  1020,
       9,   122,     9,     8,    99,     9,     9,   967,     9,   103,
     216,    13,   122,   141,  1054,   197,    88,   918,   919,    13,
     212,   432,    10,   212,    10,    10,    13,  1072,   838,  1074,
     175,    13,    88,   843,    10,    10,    41,   936,    10,   999,
      13,    10,    13,  1083,  1084,  1085,   856,    13,   459,    13,
      10,    10,  1092,    11,    10,   466,    13,    10,    63,   470,
    1105,   738,    13,    10,    13,    13,    88,    13,    13,    13,
      13,    10,    13,    10,  1095,    80,    10,    10,    10,    10,
      10,   228,   493,  1104,    13,    10,  1126,    92,    10,  1049,
      71,  1112,    10,    14,   228,   228,     9,  1137,   196,   196,
     105,  1122,    42,   108,    14,    14,     9,   917,  1009,    14,
     125,   522,  1152,  1134,  1135,    14,    13,     9,  1158,  1140,
      14,    38,  1143,   933,   934,    42,   936,     9,    45,   129,
      47,    39,   130,    50,    14,    71,    53,     9,    55,    56,
       9,    91,    59,   198,   143,    26,    14,    14,   153,    13,
     960,   106,    13,   158,    13,   965,    13,    99,    14,    76,
     165,     9,   132,   212,   209,    82,    10,    86,    39,    86,
      13,   176,    13,    90,    10,    10,    34,    10,    10,    96,
      38,    10,    40,    10,    10,   190,    10,   104,   193,    47,
     107,  1001,    13,    51,    10,    53,    10,    10,    56,    10,
     205,    59,    60,    10,    13,  1106,    64,  1108,   125,    13,
      10,    10,    10,    10,    72,    73,    10,    39,   209,    58,
      10,  1031,   139,  1033,    42,   142,    96,   144,  1129,    14,
      26,    10,   125,    84,    10,   152,     9,     6,     9,    14,
      10,   206,   159,   160,   120,    10,   104,    14,   125,   107,
      14,    14,    14,   170,    14,    89,    13,   668,   175,    13,
      13,   196,    13,    78,   122,     9,    96,    10,    10,    10,
      10,  1081,     9,   125,     6,    13,  1086,    13,    13,    13,
      10,    10,    13,    10,   854,    13,   144,    13,   125,   206,
      14,    14,    13,    10,   152,    14,    14,   125,   215,    13,
      10,    10,    10,  1113,    10,   957,  1044,    93,  1160,    93,
      93,   520,   170,  1066,   960,   908,  1033,   175,   795,   726,
     684,   427,   705,   462,     7,   682,   662,   712,   739,   740,
     478,   742,   190,   744,   930,   508,   708,   748,   749,   750,
     751,   400,   972,   456,   755,   203,   838,   758,   206,   760,
    1137,   762,    -1,    -1,   765,   766,   767,   768,   769,   770,
      -1,   772,    -1,   774,    -1,   776,    -1,    -1,   779,    -1,
      -1,    -1,   783,    -1,    -1,   786,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   797,   798,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   817,    -1,    -1,   820,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       4,     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,   925,    -1,   927,    -1,    -1,    93,
      94,    95,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
     114,   115,   116,   117,    -1,    -1,    -1,   121,    -1,    -1,
     124,    -1,   126,   127,   128,   129,    -1,   131,    -1,   133,
     971,   972,    -1,    -1,    -1,   139,   140,   978,    -1,    -1,
     144,    -1,    -1,   984,    -1,    -1,    -1,   151,    -1,   990,
     991,    -1,   156,   157,   995,    -1,    -1,   161,    -1,    -1,
      -1,  1002,   166,    -1,    -1,   169,  1007,   171,    -1,    -1,
     174,    -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,
     184,   185,    -1,   187,   188,    -1,    -1,   191,     4,    -1,
      -1,    -1,    -1,     9,    -1,   199,   200,   201,   202,    -1,
      16,    -1,    -1,   207,   208,    -1,   210,   211,    -1,    -1,
      -1,    -1,    -1,    29,    -1,   219,   220,    -1,    -1,    -1,
      -1,    37,    -1,   227,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      -1,    -1,    -1,    69,    70,    -1,    -1,  1098,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,
      -1,    -1,    -1,    -1,    -1,   111,   112,    -1,   114,   115,
     116,   117,    -1,    -1,    -1,   121,    -1,    -1,   124,    -1,
     126,   127,   128,   129,    -1,   131,    -1,   133,    -1,    -1,
      -1,    -1,    -1,   139,   140,    -1,    -1,    -1,   144,    -1,
      -1,    -1,    -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,    -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,
     166,    -1,    -1,   169,    -1,   171,    -1,    -1,   174,    -1,
      -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,   184,   185,
      -1,   187,   188,    -1,    -1,   191,     4,     5,    -1,    -1,
      -1,     9,    -1,   199,   200,   201,   202,    -1,    16,    -1,
      -1,   207,   208,    -1,   210,   211,    -1,   213,    -1,    -1,
      -1,    29,    -1,   219,   220,    -1,    -1,    -1,    -1,    37,
      -1,   227,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    65,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,    -1,   114,   115,   116,   117,
      -1,    -1,    -1,   121,    -1,    -1,   124,    -1,   126,   127,
     128,   129,    -1,   131,    -1,   133,    -1,    -1,    -1,    -1,
      -1,   139,   140,    -1,    -1,    -1,   144,    -1,    -1,    -1,
      -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,   156,   157,
      -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,   166,    -1,
      -1,   169,     4,   171,    -1,    -1,   174,     9,    10,    -1,
      -1,    -1,   180,    -1,    16,    -1,   184,   185,    -1,   187,
     188,    -1,    -1,   191,    -1,    -1,    -1,    29,    -1,    -1,
      -1,   199,   200,   201,   202,    37,    -1,    -1,    -1,   207,
     208,    43,   210,   211,    -1,    -1,    -1,    49,    -1,    -1,
      -1,   219,   220,    -1,    -1,    57,    -1,    -1,    -1,   227,
      62,    -1,    -1,    65,    -1,    -1,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    94,    95,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,    -1,   114,   115,   116,   117,    -1,    -1,    -1,   121,
      -1,    -1,   124,    -1,   126,   127,   128,   129,    -1,   131,
      -1,   133,    -1,    -1,    -1,    -1,    -1,   139,   140,    -1,
      -1,    -1,   144,    -1,    -1,    -1,    -1,    -1,    -1,   151,
      -1,    -1,    -1,    -1,   156,   157,    -1,    -1,    -1,   161,
      -1,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,
      -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,   180,    -1,
      -1,    -1,   184,   185,    -1,   187,   188,    -1,    -1,   191,
       4,     5,    -1,    -1,    -1,     9,    -1,   199,   200,   201,
     202,    -1,    16,    -1,    -1,   207,   208,    -1,   210,   211,
      -1,    -1,    -1,    -1,    -1,    29,    -1,   219,   220,    -1,
      -1,    -1,    -1,    37,    -1,   227,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    65,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      94,    95,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
     114,   115,   116,   117,    -1,    -1,    -1,   121,    -1,    -1,
     124,    -1,   126,   127,   128,   129,    -1,   131,    -1,   133,
      -1,    -1,    -1,    -1,    -1,   139,   140,    -1,    -1,    -1,
     144,    -1,    -1,    -1,    -1,    -1,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,    -1,    -1,    -1,   161,    -1,    -1,
      -1,    -1,   166,    -1,    -1,   169,    -1,   171,    -1,    -1,
     174,    -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,
     184,   185,    -1,   187,   188,    -1,    -1,   191,     4,     5,
      -1,    -1,    -1,     9,    -1,   199,   200,   201,   202,    -1,
      16,    -1,    -1,   207,   208,    -1,   210,   211,    -1,    -1,
      -1,    -1,    -1,    29,    -1,   219,   220,    -1,    -1,    -1,
      -1,    37,    -1,   227,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      -1,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,
      -1,    -1,    -1,    -1,    -1,   111,   112,    -1,   114,   115,
     116,   117,    -1,    -1,    -1,   121,    -1,    -1,   124,    -1,
     126,   127,   128,   129,    -1,   131,    -1,   133,    -1,    -1,
      -1,    -1,    -1,   139,   140,    -1,    -1,    -1,   144,    -1,
      -1,    -1,    -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,    -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,
     166,    -1,    -1,   169,     4,   171,    -1,    -1,   174,     9,
      -1,    -1,    -1,    -1,   180,    -1,    16,    -1,   184,   185,
      -1,   187,   188,    -1,    -1,   191,    -1,    -1,    -1,    29,
      -1,    -1,    -1,   199,   200,   201,   202,    37,    -1,    -1,
      -1,   207,   208,    43,   210,   211,    -1,    -1,    -1,    49,
      -1,    -1,    -1,   219,   220,    -1,    -1,    57,    -1,    -1,
      -1,   227,    62,    -1,    -1,    65,    -1,    -1,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    94,    95,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   112,    -1,   114,   115,   116,   117,    -1,    -1,
      -1,   121,    -1,    -1,   124,    -1,   126,   127,   128,   129,
      -1,   131,    -1,   133,    -1,    -1,    -1,    -1,    -1,   139,
     140,    -1,    -1,    -1,   144,    -1,    -1,    -1,    -1,    -1,
      -1,   151,    -1,    -1,    -1,    -1,   156,   157,    -1,    -1,
      -1,   161,    -1,    -1,    -1,    -1,   166,    -1,   168,   169,
       4,   171,    -1,    -1,   174,     9,    -1,    -1,    -1,    -1,
     180,    -1,    16,    -1,   184,   185,    -1,   187,   188,    -1,
      -1,   191,    -1,    -1,    -1,    29,    -1,    -1,    -1,   199,
     200,   201,   202,    37,    -1,    -1,    -1,   207,   208,    43,
     210,   211,    -1,    -1,    -1,    49,    -1,    -1,    -1,   219,
     220,    -1,    -1,    57,    -1,    -1,    -1,   227,    62,    -1,
      -1,    65,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      94,    95,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
     114,   115,   116,   117,    -1,    -1,    -1,   121,    -1,    -1,
     124,    -1,   126,   127,   128,   129,    -1,   131,    -1,   133,
      -1,    -1,    -1,    -1,    -1,   139,   140,    -1,    -1,    -1,
     144,    -1,    -1,    -1,    -1,    -1,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,    -1,    -1,    -1,   161,    -1,    -1,
      -1,    -1,   166,    -1,    -1,   169,     4,   171,    -1,    -1,
     174,     9,    -1,    -1,    -1,    -1,   180,    -1,    16,    -1,
     184,   185,    -1,   187,   188,    -1,    -1,   191,    -1,    -1,
      -1,    29,    -1,    -1,    -1,   199,   200,   201,   202,    37,
      -1,    -1,    -1,   207,   208,    43,   210,   211,    -1,    -1,
      -1,    49,    -1,    -1,    -1,   219,   220,    -1,    -1,    57,
      -1,    -1,    -1,   227,    62,    -1,    -1,    65,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,    -1,   114,   115,   116,   117,
      -1,    -1,    -1,   121,    -1,    -1,   124,    -1,   126,   127,
     128,   129,    -1,   131,    -1,   133,    -1,    -1,    -1,    -1,
      -1,   139,   140,    -1,    -1,    -1,   144,    -1,    -1,    -1,
      -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,   156,   157,
      -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,   166,    -1,
      -1,   169,     4,   171,    -1,    -1,   174,     9,    -1,    -1,
      -1,    -1,   180,    -1,    16,    -1,   184,   185,    -1,   187,
     188,    -1,    -1,   191,    -1,    -1,    -1,    29,    -1,    -1,
      -1,   199,   200,   201,   202,    37,    -1,    -1,    -1,   207,
     208,    43,   210,   211,    -1,    -1,    -1,    49,    -1,    -1,
      -1,   219,   220,    -1,    -1,    57,    -1,    -1,    -1,   227,
      62,    -1,    -1,    65,    -1,    -1,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    94,    95,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,    -1,   114,   115,   116,   117,    -1,    -1,    -1,   121,
      -1,    -1,   124,    -1,   126,   127,   128,   129,    -1,   131,
      -1,   133,    -1,    -1,    -1,    -1,    -1,   139,   140,    -1,
      -1,    -1,   144,    -1,    -1,    -1,    -1,    -1,    -1,   151,
      -1,    -1,    -1,    -1,   156,   157,    -1,    -1,    -1,   161,
      -1,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,   171,
      -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,   180,    -1,
      -1,    -1,   184,   185,    -1,   187,   188,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,   201,
     202,    -1,    -1,    -1,    -1,   207,   208,    -1,   210,   211,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,   220,    -1,
      -1,    -1,    -1,    -1,    -1,   227
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    34,    38,    40,    47,    51,    53,    56,    59,    60,
      64,    72,    73,   104,   107,   122,   144,   152,   170,   175,
     190,   203,   206,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   259,   260,   261,   262,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   279,   281,   282,
     284,   285,   286,   288,   289,   290,   291,   292,   311,   313,
     330,   332,   340,   390,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,    92,   165,   176,   179,   192,
     193,    27,   317,   318,   319,   340,     8,    41,    63,    80,
      92,   105,   108,   153,   158,   165,   176,   190,   193,   205,
     340,   330,    88,    88,    41,    92,   105,   108,   118,   153,
     158,   165,   176,   193,   110,   340,   110,   110,    75,     4,
       5,     9,    16,    29,    37,    43,    49,    57,    62,    65,
      69,    70,    77,    81,    85,    93,    94,    95,    98,   111,
     112,   114,   115,   116,   117,   121,   124,   126,   127,   128,
     129,   131,   133,   139,   140,   151,   156,   157,   161,   166,
     169,   171,   174,   180,   184,   185,   187,   188,   191,   199,
     200,   201,   202,   207,   208,   210,   211,   219,   220,   227,
     283,   337,   338,   339,   340,   341,   343,   344,   345,   346,
     347,   348,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   110,
     158,   193,   340,   348,     0,    38,   332,    74,   217,   218,
     221,   222,   223,   224,   225,   226,   307,   331,   340,   347,
     340,    31,    64,   340,   195,    32,   108,   164,   165,   340,
     340,    74,   314,   319,    42,    45,    47,    50,    55,    59,
      76,    82,    86,    90,    96,   107,   125,   139,   142,   159,
     160,   170,   175,   206,   215,   279,   282,   285,   313,   325,
     326,   327,   340,   347,     9,   166,   340,   193,   118,   134,
     137,   177,   178,   340,   340,   340,   340,   193,   340,   118,
     340,   105,     9,   333,    38,   340,   348,   340,   340,   134,
     137,   177,   178,   340,   340,   340,   340,   340,   340,   340,
     340,     9,   340,   348,   340,     9,   210,   211,    88,   352,
     355,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,    20,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
      20,     9,    15,    97,    15,    13,    88,     8,    35,     7,
       3,     4,     5,     6,    11,    99,   119,   228,   229,   230,
     231,   232,   233,   340,   340,   340,   181,   181,   317,    14,
       9,    14,    25,    15,    20,   154,   193,   193,   181,     4,
     337,   347,   349,    30,   102,    44,   150,   164,   190,    31,
      48,    64,   162,   163,    28,   213,   315,   316,    71,   213,
     322,   323,   350,   340,    14,    14,   213,    15,    88,    14,
     213,   340,   340,   340,   350,   110,   317,    14,   340,   320,
     340,     9,    14,     5,   351,   350,    14,    14,    14,    14,
      14,     9,   321,    25,   351,   153,   193,   340,   340,   340,
     391,   391,    91,   391,   391,   141,   106,   308,     9,   312,
     183,   351,   186,   263,   340,     9,   340,   334,   335,   340,
      99,   317,   214,   303,   303,   303,   391,   391,    91,   391,
     391,     9,   304,    10,   351,   304,     9,   304,   340,   299,
     300,   340,     8,    10,     3,     4,     5,     6,     9,   355,
     350,   350,   355,   350,   350,   350,    10,    10,   350,   350,
     350,   350,   350,   350,   350,   350,   350,     5,   351,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,    87,   100,   138,   172,
     342,   350,   350,   350,   350,   350,   350,   350,   350,   345,
     350,   350,     5,   350,   342,   351,    52,   135,   340,     9,
     346,   350,   299,     9,   353,   340,   353,   355,   355,   355,
     355,   355,   139,   355,   355,   355,   355,   355,   355,   355,
     304,   283,   301,   302,   340,   348,   301,   314,   337,   350,
     173,   204,   227,   349,   349,    52,    13,   340,    33,   123,
     349,    46,    46,   340,    46,   340,   316,   350,    67,    71,
     323,   324,   322,    14,   350,   155,   350,   110,    97,    14,
     196,    71,   321,    14,   338,   110,   110,   125,   351,    14,
     350,    10,   340,   351,     9,   122,     9,     9,   391,     9,
       9,   340,   337,    79,   309,    10,   334,    99,   337,   216,
     103,   264,   122,   305,   306,   340,   141,    10,    13,    97,
     101,   145,   336,   286,   314,   350,   197,   391,   349,   212,
      10,   212,   278,   346,    88,    13,    13,   303,   340,   353,
     355,   355,   355,   355,   355,    10,    10,    10,    13,    13,
      13,    10,    13,    10,    88,    10,    10,    10,    13,    13,
      13,    13,    10,    10,    10,    13,    10,    10,    13,    10,
      13,    10,    13,    10,    10,    13,    13,    13,    13,    13,
      13,    10,    13,    10,    13,    10,    13,    10,    10,    13,
      10,    10,    10,    13,    10,    10,    13,    10,    10,    10,
      10,   351,   303,   352,    88,    13,   303,   228,   228,   303,
      71,    10,    14,   228,   228,   347,   337,     9,   340,   340,
     196,   196,   317,    42,    14,   324,    14,     9,    14,   349,
     168,   350,   317,   125,    14,    13,   349,   349,   317,    10,
      14,   312,   305,   345,   340,   392,   337,   397,     9,   340,
     393,   340,   394,     9,   337,   129,   310,    10,   313,   308,
     337,    39,   130,   265,   345,    10,    13,   307,   340,   335,
     331,    14,    71,   337,    10,     9,     9,    10,    13,   345,
     338,   300,   143,   295,    10,    10,    10,    10,    10,   355,
     350,   366,   367,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,    10,    91,   297,   345,
     302,   350,   350,   337,   402,   337,   306,   198,   317,   317,
      71,    14,   350,    14,   350,    26,    67,    68,    71,   328,
     329,    14,   345,    88,    88,    71,    99,    10,   106,   245,
      13,    13,   392,    13,    13,   113,   293,   294,   340,   346,
     337,    14,   309,   337,   337,   132,   266,   245,   308,   306,
       9,   351,   351,   212,   346,   209,    10,    39,    86,   298,
      10,    13,    13,   365,    10,    10,    10,    10,    13,    10,
      10,    10,    10,    10,    13,    10,    10,    10,    10,    10,
      13,    13,    10,    10,    10,    13,    10,    10,    10,    39,
     295,   209,    58,   258,   340,    42,    10,    26,   350,   317,
     350,    96,   328,    10,   299,   299,   125,   313,   310,   345,
      84,   246,   345,   404,   337,   400,    10,   337,   398,   345,
     395,     9,    10,    13,    36,    61,   296,   296,     6,   310,
     337,    54,   136,   267,   246,   309,   293,    10,    10,     9,
     340,    14,   351,   206,   120,   287,   350,   350,   367,    10,
     350,   350,   350,   350,   350,   351,   298,   340,   350,    10,
      14,   350,   125,    71,   196,    14,   303,   303,    14,    14,
     345,    89,   247,    13,    13,    13,    13,   340,   294,   247,
     310,    10,    78,   280,   351,     9,   337,    10,    13,    10,
      10,    10,    10,   287,     9,   125,   317,    96,   317,   297,
     297,     6,   340,    13,   337,   405,   337,   401,   337,   399,
     340,   396,    13,   337,    10,   345,    13,   350,   345,   317,
      71,   298,   298,   345,   340,    13,    10,    13,    10,   345,
      13,   337,    10,    13,    71,   125,    14,    14,   345,   345,
     406,   400,    13,   345,   345,   125,    14,    10,    13,   337,
      10,    10,    14,   337,   403,    10,   280,    10,   296
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   234,   235,   235,   235,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   238,   238,   239,   240,   241,   241,   242,   242,
     243,   244,   245,   245,   246,   246,   247,   247,   247,   248,
     249,   250,   250,   251,   252,   253,   253,   254,   254,   254,
     254,   254,   254,   254,   255,   256,   256,   257,   257,   257,
     257,   258,   258,   259,   260,   261,   262,   263,   263,   264,
     264,   265,   265,   266,   266,   267,   267,   267,   268,   268,
     268,   268,   268,   269,   269,   270,   271,   271,   272,   273,
     274,   275,   276,   277,   278,   278,   279,   280,   280,   281,
     282,   283,   283,   283,   283,   283,   284,   285,   286,   286,
     287,   287,   287,   288,   289,   289,   290,   291,   292,   292,
     292,   292,   293,   293,   294,   294,   294,   295,   295,   296,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   302,   303,   303,   304,   304,   305,
     305,   306,   307,   307,   307,   307,   307,   307,   307,   307,
     308,   308,   309,   309,   310,   310,   311,   311,   312,   312,
     312,   313,   313,   313,   314,   314,   315,   315,   316,   317,
     317,   318,   318,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     320,   320,   321,   321,   322,   322,   323,   324,   324,   325,
     325,   326,   326,   327,   327,   328,   328,   328,   329,   329,
     330,   330,   331,   331,   331,   332,   332,   332,   332,   332,
     333,   333,   334,   334,   335,   336,   336,   336,   336,   337,
     337,   338,   339,   339,   340,   340,   341,   341,   342,   342,
     342,   342,   343,   344,   345,   346,   347,   347,   348,   348,
     349,   349,   350,   350,   351,   351,   352,   352,   352,   353,
     353,   353,   354,   354,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   356,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   358,   358,   358,   358,   359,   359,   360,   361,   362,
     363,   364,   365,   365,   366,   366,   367,   368,   369,   370,
     370,   371,   371,   372,   373,   374,   375,   376,   377,   378,
     378,   379,   379,   380,   380,   381,   382,   383,   384,   384,
     385,   385,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   387,   387,   387,   387,   387,   387,   388,   388,   388,
     388,   388,   388,   388,   388,   389,   389,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     8,     9,     8,     9,     8,
       9,     9,     0,     2,     0,     2,     0,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     8,     9,     6,
       4,     0,     2,     5,     8,     3,     7,     0,     3,     0,
       3,     0,     2,     0,     2,     0,     1,     1,     4,     5,
       5,     5,     4,     5,     5,     4,     4,     4,     6,     4,
       2,     5,     3,    10,     1,     3,     9,     0,     2,     5,
       5,     6,     6,     6,     6,     4,     4,     4,     9,     8,
       0,     2,     4,     8,     4,     6,    14,    13,     5,     5,
       2,     4,     1,     3,     2,     2,     9,     0,     3,     0,
       1,     1,     0,     3,     0,     2,     1,     3,     1,     2,
       1,     3,     3,     1,     3,     0,     2,     0,     3,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     4,     1,
       0,     2,     0,     2,     0,     2,     8,    10,     0,     3,
       2,     5,     4,     6,     0,     2,     1,     2,     4,     1,
       2,     0,     3,     3,     3,     5,     8,    11,    11,     3,
       3,     3,     3,     6,     2,     2,     6,     5,    12,    13,
       8,     4,     5,     6,     4,     4,     8,     4,     3,     3,
       0,     1,     0,     3,     1,     2,     4,     2,     4,     2,
       4,     2,     4,     5,     6,     2,     4,     4,     1,     2,
       1,     2,     1,     3,     3,     3,     5,     6,     3,     8,
       0,     3,     1,     3,     3,     0,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     5,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     1,     1,     6,
       1,     4,     3,     3,     4,     6,     4,     4,     4,     6,
       8,     6,     8,    10,     6,     4,     6,     4,     6,     4,
       4,     7,     0,     2,     1,     3,     3,     6,     4,     4,
       6,     4,     6,     8,     8,     4,     6,     4,     5,     6,
       3,     6,     8,     4,     6,     6,     4,     4,     4,     6,
       4,     6,     3,     5,     3,     5,     3,     5,     3,     5,
       4,     4,     4,     4,     4,     4,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,    11,     4,    13,     4,     8,     5,
      15,     4,    11,     4,     7
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, param, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, param, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, dbmParserContext   * param, void               * scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (param);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, dbmParserContext   * param, void               * scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, param, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, dbmParserContext   * param, void               * scanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , param, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, param, scanner); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, dbmParserContext   * param, void               * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (param);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (dbmParserContext   * param, void               * scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 279 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  param->mParseObj = v1;
              }
#line 2822 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 283 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  param->mParseObj = v1;
              }
#line 2830 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 287 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  param->mParseObj = v1;
              }
#line 2838 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 294 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2846 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 298 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2854 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 302 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2862 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 306 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2870 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 310 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2878 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 314 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2886 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 318 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2894 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 322 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2902 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 326 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2910 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 330 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2918 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 334 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2926 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 338 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2934 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 342 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2942 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 346 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2950 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 350 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2958 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 354 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2966 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 358 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2974 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 362 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2982 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 366 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2990 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 370 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 2998 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 374 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3006 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 378 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3014 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 382 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3022 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 386 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3030 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 393 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3038 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 397 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3046 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 401 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3054 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 405 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3062 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 409 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3070 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 413 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3078 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 417 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3086 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 421 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3094 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 425 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3102 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 429 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3110 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 433 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3118 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 437 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3126 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 441 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 3134 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 448 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = dbmMakeCreateDCLStmt( param,
                                         DBM_TRUE );
          }
#line 3143 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 453 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = dbmMakeCreateDCLStmt( param,
                                         DBM_FALSE );
          }
#line 3152 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 464 "dbmParserGram.y" /* yacc.c:1646  */
    {
                          v0 = dbmMakeCreateInstanceStmt( param,
                                                          v3,    // instName,
                                                          v4,    // InitOption
                                                          v5,    // extendOption
                                                          v6 );  // MaxOption
                      }
#line 3164 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 478 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateQueueStmt( param,
                                                    v3,      // NameList
                                                    v5,      // MsgSizeOption
                                                    v6,      // InitOption
                                                    v7,      // ExtendOption
                                                    v8,      // MaxOption
                                                    DBM_FALSE );   
                   }
#line 3178 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 511 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateTableStmt( param,
                                                    DBM_TABLE_TYPE_TABLE,
                                                    v3,      // NameList
                                                    v5,      // ColumnList
                                                    v7,      // InitOption
                                                    v8,      // ExtendOption
                                                    v9 );    // MaxOption
                   }
#line 3192 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 524 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateTableStmt( param,
                                                    DBM_TABLE_TYPE_DIRECT_TABLE,
                                                    v4,      // NameList
                                                    v6,      // ColumnList
                                                    NULL,    // InitOption
                                                    NULL,    // ExtendOption
                                                    v8 );    // MaxOption
                   }
#line 3206 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 539 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateIndexStmt( param,
                                                    DBM_TRUE,  // IsUnique
                                                    v4,        // IndexName
                                                    v6,        // TableName
                                                    v8 );      // KeyList
                   }
#line 3218 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 549 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateIndexStmt( param,
                                                    DBM_FALSE, // IsUnique
                                                    v3,        // IndexName
                                                    v5,        // TableName
                                                    v7 );      // KeyList
                   }
#line 3230 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 564 "dbmParserGram.y" /* yacc.c:1646  */
    {
                                  v0 = dbmMakeCreateLibraryStmt( param,
                                                                 DBM_FALSE,
                                                                 v4,
                                                                 v6,
                                                                 v7,
                                                                 v8,
                                                                 v9 );
                              }
#line 3244 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 581 "dbmParserGram.y" /* yacc.c:1646  */
    {
                              v0 = dbmMakeCreateLibraryStmt( param,
                                                             DBM_TRUE,
                                                             v4,
                                                             v6,
                                                             v7,
                                                             v8,
                                                             v9 );
                          }
#line 3258 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 594 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = NULL;
                    }
#line 3266 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 598 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmParseLibraryItem     * sItem = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mFuncName = v2;
                        //sItem->mParamList = v3;

                        v0 = sItem;
                    }
#line 3286 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 617 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = NULL;
                    }
#line 3294 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 621 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmParseLibraryItem     * sItem = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mFuncName = v2;
                        //sItem->mParamList = v3;

                        v0 = sItem;
                    }
#line 3314 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 640 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    }
#line 3321 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 643 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmParseLibraryItem    * sItem = NULL;
                        dbmList                * sList = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mAliasName = v2;
                        sItem->mFuncName = v3;
                        //sItem->mParamList = v4;

                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    sItem,
                                    param->mErrorStack );
 
                        v0 = sList;
                    }
#line 3353 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 671 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmParseLibraryItem    * sItem = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mAliasName = v3;
                        sItem->mFuncName = v4;
                        //sItem->mParamList = v5;


                        dbmAddList( param->mAllocator,
                                    v1,
                                    DBM_LIST_ELEM_POINTER,
                                    sItem,
                                    param->mErrorStack );

                        v0 = v1;
                    }
#line 3381 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 782 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeDropInstanceStmt( param,
                                                      v3 );
                    }
#line 3390 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 790 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         v0 = dbmMakeDropProcedureStmt( param,
                                                        v3 );
                     }
#line 3399 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 799 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeDropTableStmt( param,
                                                DBM_PARSE_TYPE_DROP_TABLE_STMT,
                                                v3 );
                 }
#line 3409 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 805 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeDropTableStmt( param,
                                                DBM_PARSE_TYPE_DROP_QUEUE_STMT,
                                                v3 );
                 }
#line 3419 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 813 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeDropIndexStmt( param,
                                                v3 );
                 }
#line 3428 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 821 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeDropLibraryStmt( param,
                                                     v3 );
                   }
#line 3437 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 829 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeTruncateStmt( param,
                                               DBM_PARSE_TYPE_TRUNCATE_TABLE_STMT,
                                               v3 );
               }
#line 3447 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 835 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeTruncateStmt( param,
                                               DBM_PARSE_TYPE_TRUNCATE_QUEUE_STMT,
                                               v3 );
               }
#line 3457 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 843 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3465 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 847 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3473 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 851 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3481 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 855 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3489 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 859 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3497 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 863 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3505 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 867 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v1;
                   }
#line 3513 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 874 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeAlterTermSessionStmt( param,
                                                         v4 );
                   }
#line 3522 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 882 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeAlterAgingStmt( param,
                                                    NULL );
                    }
#line 3531 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 887 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeAlterAgingStmt( param,
                                                    v4 );
                    }
#line 3540 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 896 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeAlterTableRenameColumnStmt( param,
                                                              v3,
                                                              v6,
                                                              v8 );       
                  }
#line 3551 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 903 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeAlterTableAddColumnStmt( param,
                                                           v3,
                                                           v7,
                                                           v8 );
                  }
#line 3562 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 910 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeAlterTableDropColumnStmt( param,
                                                            v3,
                                                            v6 );
                  }
#line 3572 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 916 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeAlterTableCompactStmt( param,
                                                         v3 );
                  }
#line 3581 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 924 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = NULL;
             }
#line 3589 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 928 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = v2;
             }
#line 3597 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 935 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeAlterRebuildIndexStmt( param,
                                                           v3,
                                                           v5 );
                    }
#line 3607 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 950 "dbmParserGram.y" /* yacc.c:1646  */
    {
                          v0 = dbmMakeCreateSequenceStmt( param,
                                                          v3,
                                                          v4,
                                                          v5,
                                                          v6, // max
                                                          v7, // min
                                                          v8 );
                      }
#line 3621 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 962 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeDropSequenceStmt( param,
                                                      v3 );
                    }
#line 3630 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 970 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         v0 = dbmMakeAlterSequenceStmt( param,
                                                        v3,
                                                        v7 );
                     }
#line 3640 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 979 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeIntValue( param,
                                         DBM_FALSE,
                                         "1" );
                }
#line 3650 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 986 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v3;
                }
#line 3658 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 992 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeIntValue( param,
                                         DBM_FALSE,
                                         "1" );
               }
#line 3668 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 999 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = v3;
               }
#line 3676 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1005 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = dbmMakeIntValue( param,
                                   DBM_FALSE,
                                   "MAX" );
         }
#line 3686 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1012 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = v2;
         }
#line 3694 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1018 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = dbmMakeIntValue( param,
                                   DBM_FALSE,
                                   "MIN" );
         }
#line 3704 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1025 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = v2;
         }
#line 3712 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1031 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeIntValue( param,
                                     DBM_FALSE,
                                     "N" );
           }
#line 3722 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1037 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeIntValue( param,
                                     DBM_FALSE,
                                     "Y" );
           }
#line 3732 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1043 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeIntValue( param,
                                     DBM_FALSE,
                                     "N" );
           }
#line 3742 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1051 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_SYNC,
                                                   NULL );
                }
#line 3752 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1057 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_LOCAL_SYNC,
                                                   NULL );
                }
#line 3762 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1063 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_FULL_SYNC,
                                                   NULL );
                }
#line 3772 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1069 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_FULL_SYNC,
                                                   v5 );
                }
#line 3782 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1075 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_RESET,
                                                   NULL );
                }
#line 3792 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1083 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeAlterReplModStmt( param,
                                                 DBM_FALSE,
                                                 v5 );
               }
#line 3802 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1089 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeAlterReplModStmt( param,
                                                 DBM_TRUE,
                                                 v5 );
               }
#line 3812 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1097 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeAlterResetPerfStmt( param );
                 }
#line 3820 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1104 "dbmParserGram.y" /* yacc.c:1646  */
    {
                                 v0 = dbmMakeAlterSystemInstanceStmt( param,
                                                                      DBM_TRUE );
                             }
#line 3829 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1109 "dbmParserGram.y" /* yacc.c:1646  */
    {
                                 v0 = dbmMakeAlterSystemInstanceStmt( param,
                                                                      DBM_FALSE );
                             }
#line 3838 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1117 "dbmParserGram.y" /* yacc.c:1646  */
    {
                            v0 = dbmMakeAlterSystemResetCkptFileStmt( param,
                                                                      v5,
                                                                      v6 );
                        }
#line 3848 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1126 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeCreateReplStmt( param,
                                                  v4 );
                  }
#line 3857 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1133 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeDropReplStmt( param );
                }
#line 3865 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1141 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         v0 = dbmMakeCreateCaptureStmt( param,
                                                        v3,
                                                        v5 );
                     }
#line 3875 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1150 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeDropCaptureStmt( param,
                                                 v3 );
                }
#line 3884 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1160 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeOraInsertStmt( param,
                                                v3,      // TableName
                                                v5,      // Columns
                                                v9 );    // ValueList
                 }
#line 3895 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1170 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList       * sList = NULL;
   
                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v1,
                                    param->mErrorStack );
   
                        v0 = sList;
                    }
#line 3915 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1186 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList          * sList = v1;
  
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v3,
                                    param->mErrorStack );
                        v0 = sList;
                    }
#line 3930 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1205 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeInsertStmt( param,
                                         v3,      // TableName
                                         v4,      // Columns
                                         v7,      // values
                                         v9 );    
             }
#line 3942 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1215 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = NULL;
              }
#line 3950 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1219 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = v2;
              }
#line 3958 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1228 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeOraUpdateStmt( param,
                                                DBM_PARSE_TYPE_UPDATE_STMT,
                                                v2,      // TableName
                                                v4,      // Set List
                                                v5 );    // where 
                 }
#line 3970 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1242 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeUpdateStmt( param,
                                         DBM_PARSE_TYPE_UPDATE_STMT,
                                         v2,      // TableName
                                         v4,      // Set List
                                         v5 );    // where 
             }
#line 3982 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1253 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_ADD,
                                                   v3,
                                                   v5,
                                                   NULL, 
                                                   NULL );
                    }
#line 3995 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1262 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_DELETE,
                                                   v3,
                                                   v5,
                                                   NULL,
                                                   NULL );
                    }
#line 4008 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1271 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_QUERY,
                                                   v3,
                                                   v5,
                                                   NULL,
                                                   NULL );
                    }
#line 4021 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1280 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_VALUE,
                                                   v3,
                                                   v5,
                                                   NULL,
                                                   NULL );
                    }
#line 4034 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1289 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_VALUE,
                                                   v3,
                                                   NULL,
                                                   NULL,
                                                   NULL );
                    }
#line 4047 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1302 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeOraDeleteStmt( param,
                                                v3,      // TableName
                                                v4 );    // where 
                 }
#line 4057 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1313 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeDeleteStmt( param,
                                         v3,      // TableName
                                         v4 );    // where 
             }
#line 4067 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1328 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeSelectStmt( param,
                                         v2,       // Target List
                                         v4,       // Table
                                         v5,       // Where
                                         v6,       // Group By
                                         v7,       // Order By
                                         v8,       // for update
                                         v9 );     // limit
             }
#line 4082 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1345 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeSelectStmt( param,
                                         NULL,     // Target List (ALL COLUMN)
                                         v4,       // Table
                                         v5,       // Where
                                         NULL,     // Group by
                                         v6,       // Order by
                                         v7,       // for update
                                         v8 );     // limit
             }
#line 4097 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1359 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = NULL;
              }
#line 4105 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1363 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeParseLimit( param, NULL, v2 );
              }
#line 4113 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1367 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeParseLimit( param, v2, v4 );
              }
#line 4121 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1377 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeEnqueueStmt( param,
                                           v3,      // TableName
                                           v4,      // Columns
                                           v7 );    // Values
              }
#line 4132 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1387 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeDequeueStmt( param,
                                           v3,       // Table
                                           v4,       // where
                                           NULL );   // Timeout
              }
#line 4143 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1397 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeDequeueStmt( param,
                                           v3,       // Table
                                           v4,       // where
                                           v6 );     // Timeout
              }
#line 4154 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1410 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeLoadStmt( param,
                                     v3,       // targetTable
                                     v4,       // TargetTable columnTargetList
                                     v6,       // SourceQuery
                                     v8,       // SourceDSN
                                     v10,      // SourceUid
                                     v12,      // SourcePwd
                                     v14 );    // expiredTime
           }
#line 4169 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1424 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeSyncStmt( param,
                                     v3,       // targetTable
                                     v4,       // targetColumnList
                                     v6,       // sourceQuery
                                     v8,       // targetDSN
                                     v10,      // targetUid
                                     v12 );    // targetPwd
           }
#line 4183 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1437 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              v4 );
                }
#line 4193 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1443 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              v4 );
                }
#line 4203 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1449 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              NULL );
                }
#line 4213 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1455 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              NULL );
                }
#line 4223 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1464 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    dbmList    * sList = NULL;

                    dbmCreateList( param->mAllocator,
                                   &sList,
                                   param->mErrorStack );
   
                    dbmAddList( param->mAllocator,
                                sList,
                                DBM_LIST_ELEM_POINTER,
                                v1,
                                param->mErrorStack );
 
                    v0 = sList;
                }
#line 4243 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1480 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    dbmAddList( param->mAllocator,
                                v1,
                                DBM_LIST_ELEM_POINTER,
                                v3,
                                param->mErrorStack );
  
                    v0 = v1;
                }
#line 4257 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1493 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeKeyColumnDef( param,
                                                DBM_PARSE_FUNCTION_INVALID,
                                                v1,
                                                NULL,
                                                NULL,
                                                v2 );
                  }
#line 4270 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1502 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeKeyColumnDef( param,
                                                DBM_PARSE_FUNCTION_INVALID,
                                                v1,
                                                NULL,
                                                NULL,
                                                v2 );
                  }
#line 4283 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1511 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeKeyColumnDef( param,
                                                DBM_PARSE_FUNCTION_JSON_KEY,
                                                v3,
                                                v5,
                                                v7,
                                                v9 );
                  }
#line 4296 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1523 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = NULL;
               }
#line 4304 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1527 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = v3;
               }
#line 4312 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1534 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = NULL;
          }
#line 4320 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1538 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = NULL;
          }
#line 4328 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1542 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 4336 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1549 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = NULL;
               }
#line 4344 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1553 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = v3;
               }
#line 4352 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1560 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = NULL;
            }
#line 4360 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1564 "dbmParserGram.y" /* yacc.c:1646  */
    {
                dbmParseValue *sVal;

                dbmAllocMemory( param->mAllocator,
                                sizeof(dbmParseValue),
                                (void **)&sVal,
                                param->mErrorStack );

                sVal->mType = DBM_PARSE_TYPE_IDENTIFIER;
                sVal->mValue = NULL;

                v0 = sVal;
            }
#line 4378 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1581 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmList       * sList = NULL;

                       dbmCreateList( param->mAllocator,
                                      &sList,
                                      param->mErrorStack );
   
                       dbmAddList( param->mAllocator,
                                   sList,
                                   DBM_LIST_ELEM_POINTER,
                                   v1,
                                   param->mErrorStack );
  
                       v0 = sList;
 
                   }
#line 4399 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1598 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmAddList( param->mAllocator,
                                   v1,
                                   DBM_LIST_ELEM_POINTER,
                                   v3,
                                   param->mErrorStack );
  
                       v0 = v1;
                   }
#line 4413 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1611 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeTableSource( param,
                                           v1,
                                           NULL );
              }
#line 4423 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1617 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeTableSource( param,
                                           v1,
                                           v2 );
              }
#line 4433 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1627 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList       * sList = NULL;

                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    v1,
                                    param->mErrorStack );
   
                        v0 = sList;
                    }
#line 4453 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1643 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmAddList( param->mAllocator,
                                    v1,
                                    DBM_LIST_ELEM_POINTER,
                                    v3,
                                    param->mErrorStack );
 
                        v0 = v1;
                    }
#line 4467 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1656 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeUpdateSetItem( param,
                                            DBM_FALSE,
                                            v1,     // Column
                                            v3 );   // Value
             }
#line 4478 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1663 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = v1;
             }
#line 4486 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1667 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeUpdateSetItem( param,
                                            DBM_TRUE,
                                            v1,     // Column
                                            v3 );   // Value
             }
#line 4497 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1678 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = NULL;
                 }
#line 4505 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1682 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v2;
                 }
#line 4513 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1689 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = NULL;
                }
#line 4521 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1693 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v2;
                }
#line 4529 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1700 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmList       * sList = NULL;

                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
#line 4549 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1716 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmAddList( param->mAllocator,
                                 v1,
                                 DBM_LIST_ELEM_POINTER,
                                 v3,
                                 param->mErrorStack );
                     v0 = v1;
                 }
#line 4562 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1728 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = dbmMakeColumnDef( param,
                                       v1,
                                       v2 );    
            }
#line 4572 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1737 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_SHORT,
                                                sizeof(dbmUInt16) );
                   }
#line 4582 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1743 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_INT,
                                                sizeof(int) );
                   }
#line 4592 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1749 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_INT,
                                                sizeof(int) );
                   }
#line 4602 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1755 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_FLOAT,
                                                sizeof(float) );
                   }
#line 4612 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1761 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_DOUBLE,
                                                sizeof(double) );
                   }
#line 4622 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1767 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_LONG,
                                                sizeof(long) );
                   }
#line 4632 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1773 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseValue *sVal = (dbmParseValue *)v3;
                      
                       if( (sVal != NULL) && (sVal->mType == DBM_PARSE_TYPE_UINT) )
                       {
                           v0 = dbmMakeDataTypeDef( param,
                                                    DBM_PARSE_DATA_TYPE_CHAR,
                                                    atoi(sVal->mValue) );
                       }
                   }
#line 4647 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1784 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_DATE,
                                                sizeof(dbmTime) );
                   }
#line 4657 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1793 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = NULL;
                 }
#line 4665 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1797 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v2;
                 }
#line 4673 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1804 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = NULL;
                   }
#line 4681 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1808 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v2;
                   }
#line 4689 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1815 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = NULL;
                }
#line 4697 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1819 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v2;
                }
#line 4705 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1833 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           v0 = dbmMakeCreateProcStmt( param,
                                                       v3,    // ProcName
                                                       v4,    // ParamList
                                                       v6,    // Proc Block
                                                       DBM_FALSE );
                       }
#line 4717 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1846 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           v0 = dbmMakeCreateProcStmt( param,
                                                       v5,    // ProcName
                                                       v6,    // ParamList
                                                       v8,    // Proc Block
                                                       DBM_TRUE );
                       }
#line 4729 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1856 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = NULL;
                   }
#line 4737 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1860 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v2;
                   }
#line 4745 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1864 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = NULL;
                   }
#line 4753 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1872 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeProcBlockStmt( param,
                                                   v1,
                                                   v3,
                                                   v4 );
                    }
#line 4764 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1879 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeProcBlockStmt( param,
                                                   NULL,
                                                   v2,
                                                   v3 );
                    }
#line 4775 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1887 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeProcBlockStmt( param,
                                                   v2,
                                                   v4,
                                                   v5 );
                    }
#line 4786 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1896 "dbmParserGram.y" /* yacc.c:1646  */
    {
                          v0 = NULL;
                      }
#line 4794 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1900 "dbmParserGram.y" /* yacc.c:1646  */
    {
                          v0 = v2;
                      }
#line 4802 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1906 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         dbmList       * sList = NULL;
  
                         dbmCreateList( param->mAllocator,
                                        &sList,
                                        param->mErrorStack );

                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v1,
                                     param->mErrorStack );

                         v0 = sList;
                     }
#line 4822 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1922 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         dbmList        * sList = (dbmList *)v1;
 
                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v2,
                                     param->mErrorStack );
     
                         v0 = sList;
                     }
#line 4838 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1936 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         v0 = dbmMakeProcExceptionItem( param,
                                                        v2,
                                                        v4 );
                     }
#line 4848 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1946 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmList       * sList = NULL;
  
                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
#line 4868 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1962 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmList        * sList = (dbmList *)v1;
 
                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v2,
                                 param->mErrorStack );
 
                     v0 = sList;
                 }
#line 4884 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1977 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = NULL;
            }
#line 4892 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1981 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = v2;
            }
#line 4900 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1988 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_BLOCK,
                                     v1,
                                     v2 );
           }
#line 4911 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1995 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_NULL,
                                     v1,
                                     NULL );
           }
#line 4922 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 2002 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcAssignStmt     * sStmt = NULL;
               sStmt = dbmMakeProcAssignStmt( param,
                                              v2,
                                              v4 );
 
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_ASSIGN,
                                     v1,
                                     sStmt );
           }
#line 4938 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 2014 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcPutLineStmt     * sStmt = NULL;
               sStmt = dbmMakeProcPutLineStmt( param,
                                               v6 );
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_PUTLINE,
                                     v1,
                                     sStmt );
           }
#line 4952 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 2030 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseSelectIntoStmt *sStmt = NULL;

               sStmt = dbmMakeSelectIntoStmt( param,
                                              v3,       // Target List
                                              v5,       // IntoList
                                              v7,       // Table
                                              v8,       // Where
                                              v9,     // Group By
                                              v10 );     // for update
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SELECT_INTO,
                                     v1,
                                     sStmt );
           }
#line 4972 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 2052 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseSelectIntoStmt *sStmt = NULL;

               sStmt = dbmMakeSelectIntoStmt( param,
                                              NULL,       // Target List
                                              v5,       // IntoList
                                              v7,       // Table
                                              v8,       // Where
                                              v9,     // Group By
                                              v10 );     // for update
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SELECT_INTO,
                                     v1,
                                     sStmt );
           }
#line 4992 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 2068 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_INSERT,
                                     v1,
                                     v2 );
           }
#line 5003 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 2075 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_UPDATE,
                                     v1,
                                     v2 );
           }
#line 5014 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 2082 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_DELETE,
                                     v1,
                                     v2 );
           }
#line 5025 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 2089 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_IF,
                                     v1,
                                     v2 );
           }
#line 5036 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 2096 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcLoopStmt    * sStmt = NULL;

               sStmt = dbmMakeProcLoopStmt( param,
                                            v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_LOOP,
                                     v1,
                                     sStmt );
           }
#line 5052 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 2108 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_EXIT,
                                     v1,
                                     v2 );
           }
#line 5063 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 2115 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_CONTINUE,
                                     v1,
                                     v2 );
           }
#line 5074 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 2122 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcSimpleCaseStmt    * sStmt = NULL;

               sStmt = dbmMakeProcSimpleCaseStmt( param,
                                                  v3,
                                                  v4,
                                                  v5 );
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SIMPLE_CASE,
                                     v1,
                                     sStmt );
           }
#line 5091 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 2135 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcSearchedCaseStmt    * sStmt = NULL;

               sStmt = dbmMakeProcSearchedCaseStmt( param,
                                                    v3,
                                                    v4 );
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SEARCH_CASE,
                                     v1,
                                     sStmt );
           }
#line 5107 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 2150 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcForLoopStmt     * sStmt = NULL;

               sStmt = dbmMakeProcForLoopStmt( param,
                                               v3,
                                               DBM_FALSE,
                                               v5,
                                               v7,
                                               v9 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_FOR_LOOP,
                                     v1,
                                     sStmt );
           }
#line 5127 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 2169 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcForLoopStmt     * sStmt = NULL;

               sStmt = dbmMakeProcForLoopStmt( param,
                                               v3,
                                               DBM_TRUE,
                                               v6,
                                               v8,
                                               v10 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_FOR_LOOP,
                                     v1,
                                     sStmt );
           }
#line 5147 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 2185 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcWhileLoopStmt      * sStmt = NULL;

               sStmt = dbmMakeProcWhileLoopStmt( param,
                                                 v3,
                                                 v5 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_WHILE_LOOP,
                                     v1,
                                     sStmt );
           }
#line 5164 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 2198 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcGotoStmt      * sStmt = NULL;

               sStmt = dbmMakeProcGotoStmt( param,
                                            v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_GOTO,
                                     v1,
                                     sStmt );
           }
#line 5180 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 2210 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcOpenCursorStmt     * sStmt = NULL;

               sStmt = dbmMakeProcOpenCursorStmt( param,
                                                  v3,
                                                  v4 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_OPEN_CURSOR,
                                     v1,
                                     sStmt );
           }
#line 5197 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 2223 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcFetchCursorStmt     * sStmt = NULL;

               sStmt = dbmMakeProcFetchCursorStmt( param,
                                                   v3,
                                                   v5 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_FETCH_CURSOR,
                                     v1,
                                     sStmt );
           }
#line 5214 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 2236 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcCloseCursorStmt     * sStmt = NULL;

               sStmt = dbmMakeProcCloseCursorStmt( param,
                                                   v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_CLOSE_CURSOR,
                                     v1,
                                     sStmt );
           }
#line 5230 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 2248 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcRaiseStmt     * sStmt = NULL;

               sStmt = dbmMakeProcRaiseStmt( param,
                                             v3,
                                             NULL,
                                             NULL );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_RAISE,
                                     v1,
                                     sStmt );
 
           }
#line 5249 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 2263 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcRaiseStmt     * sStmt = NULL;

               sStmt = dbmMakeProcRaiseStmt( param,
                                             NULL,
                                             v4,
                                             v6 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_RAISE,
                                     v1,
                                     sStmt );
           }
#line 5267 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 2277 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseProcCallProcStmt     * sStmt = NULL;

               sStmt = dbmMakeProcCallProcStmt( param,
                                                v2,
                                                v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_CALL_PROC,
                                     v1,
                                     sStmt );
           }
#line 5284 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 2290 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_COMMIT,
                                     v1,
                                     NULL );
           }
#line 5295 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 2297 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_ROLLBACK,
                                     v1,
                                     NULL );
           }
#line 5306 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 2307 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = NULL;
                 }
#line 5314 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 2311 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v1;
                 }
#line 5322 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 2318 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmList       * sList = NULL;
  
                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );
 
                     v0 = sList;
                 }
#line 5336 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 2328 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v2;
                 }
#line 5344 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 2336 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         dbmList       * sList = NULL;
  
                         dbmCreateList( param->mAllocator,
                                        &sList,
                                        param->mErrorStack );
  
                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v1,
                                     param->mErrorStack );
    
                         v0 = sList;
                     }
#line 5364 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 2352 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         dbmList        * sList = (dbmList *)v1;

                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v2,
                                     param->mErrorStack );
 
                          v0 = sList;
                     }
#line 5380 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 2367 "dbmParserGram.y" /* yacc.c:1646  */
    {
                         v0 = dbmMakeProcIfItem( param,
                                                 v2,
                                                 v4 );
                     }
#line 5390 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 2376 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = NULL;
               }
#line 5398 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 2380 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeProcIfItem( param,
                                           NULL,
                                           v2 );
               }
#line 5408 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 2389 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeProcExitStmt( param,
                                              NULL );
                }
#line 5417 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 2394 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeProcExitStmt( param,
                                              v3 );
                }
#line 5426 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 2402 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeProcContinueStmt( param,
                                                      NULL );
                    }
#line 5435 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 2407 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeProcContinueStmt( param,
                                                      v3 );
                    }
#line 5444 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 2415 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  dbmParseProcIfItem    * sItem = NULL;

                  sItem = dbmMakeProcIfItem( param,
                                             v2,
                                             v4 );
                  
                  v0 = dbmMakeProcIfStmt( param,
                                          sItem,
                                          NULL,
                                          v5 );
              }
#line 5461 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 2428 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  dbmParseProcIfItem    * sItem = NULL;

                  sItem = dbmMakeProcIfItem( param,
                                             v2,
                                             v4 );
                  
                  v0 = dbmMakeProcIfStmt( param,
                                          sItem,     // if
                                          v5,        // else if
                                          v6 );      // else
              }
#line 5478 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 2443 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = NULL;
                }
#line 5486 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 2447 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeProcIfItem( param,
                                            NULL,
                                            v2 );
                }
#line 5496 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 2455 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeProcIfItem( param,
                                            v2,
                                            v4 );
                }
#line 5506 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 2463 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      dbmList       * sList = NULL;
  
                      dbmCreateList( param->mAllocator,
                                     &sList,
                                     param->mErrorStack );
  
                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_POINTER,
                                  v1,
                                  param->mErrorStack );
 
                      v0 = sList;
                  }
#line 5526 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 2479 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      dbmList        * sList = (dbmList *)v1;

                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_POINTER,
                                  v2,
                                  param->mErrorStack );
 
                       v0 = sList;
                  }
#line 5542 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 2494 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           dbmList       * sList = NULL;
  
                           dbmCreateList( param->mAllocator,
                                          &sList,
                                          param->mErrorStack );
  
                           dbmAddList( param->mAllocator,
                                       sList,
                                       DBM_LIST_ELEM_POINTER,
                                       v1,
                                       param->mErrorStack );
 
                           v0 = sList;
                      }
#line 5562 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 2510 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           dbmList        * sList = (dbmList *)v1;
 
                           dbmAddList( param->mAllocator,
                                       sList,
                                       DBM_LIST_ELEM_POINTER,
                                       v2,
                                       param->mErrorStack );
 
                           v0 = sList;
                      }
#line 5578 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 2526 "dbmParserGram.y" /* yacc.c:1646  */
    {
                            v0 = dbmMakeProcDataTypeDef( param,
                                                         DBM_PROC_VAR_TYPE_SCALAR,
                                                         v1 );
                        }
#line 5588 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 2532 "dbmParserGram.y" /* yacc.c:1646  */
    {
                            v0 = dbmMakeProcDataTypeDef( param,
                                                         DBM_PROC_VAR_TYPE_TYPE,
                                                         v1 );
                        }
#line 5598 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 2538 "dbmParserGram.y" /* yacc.c:1646  */
    {
                            v0 = dbmMakeProcDataTypeDef( param,
                                                         DBM_PROC_VAR_TYPE_ROWTYPE,
                                                         v1 );
                        }
#line 5608 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 2547 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseDeclareVar  * sVar = NULL;

                       sVar = dbmMakeProcDeclareVar( param,
                                                     v1,
                                                     v2,
                                                     NULL );
 
                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_VAR,
                                                    sVar );
                   }
#line 5625 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 2560 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseDeclareVar  * sVar = NULL;

                       sVar = dbmMakeProcDeclareVar( param,
                                                     v1,
                                                     v2,
                                                     v4 );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_VAR,
                                                    sVar );
                   }
#line 5642 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 2573 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseDeclareCursor  * sCursor = NULL;

                       sCursor = dbmMakeProcDeclareCursor( param,
                                                           DBM_PROC_VAR_TYPE_CURSOR,
                                                           v2,
                                                           v3, 
                                                           v5 );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_CURSOR,
                                                    sCursor );
                   }
#line 5660 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 2587 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseDeclareException  * sException = NULL;

                       sException = dbmMakeProcDeclareException( param,
                                                                 DBM_PROC_VAR_TYPE_EXCEPTION,
                                                                 v1,
                                                                 NULL );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_EXCEPTION,
                                                    sException );
                   }
#line 5677 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 2600 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseDeclareException  * sException = NULL;

                       sException = dbmMakeProcDeclareException( param,
                                                                 DBM_PROC_VAR_TYPE_EXCEPTION_INIT,
                                                                 v4,
                                                                 v6 );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_EXCEPTION_INIT,
                                                    sException );
                   }
#line 5694 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 2616 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = NULL;
                   }
#line 5702 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 2620 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v2;
                   }
#line 5710 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 2628 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList       * sList = NULL;
  
                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
  
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    v1,
                                    param->mErrorStack );
 
                        v0 = sList;
                    }
#line 5730 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 2644 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList        * sList = (dbmList *)v1;
 
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    v3,
                                    param->mErrorStack );
 
                        v0 = sList;
                    }
#line 5746 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 2659 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = dbmMakeParamDef( param,
                                      v1,
                                      v2,
                                      v3 );    
            }
#line 5757 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 2669 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_IN );
                   }
#line 5766 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 2674 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_IN );
                   }
#line 5775 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 2679 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_OUT );
                   }
#line 5784 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 2684 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_INOUT );
                   }
#line 5793 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 2692 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = dbmMakeIntValue( param,
                                   DBM_FALSE,
                                   v1 );
         }
#line 5803 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 2698 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = v1;
         }
#line 5811 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 2705 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = dbmMakeIntValue( param,
                                     DBM_TRUE,
                                     v2 );
           }
#line 5821 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 2714 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = dbmMakeNumberValue( param,
                                      DBM_FALSE,
                                      v1 );
         }
#line 5831 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 2720 "dbmParserGram.y" /* yacc.c:1646  */
    {
             v0 = dbmMakeNumberValue( param,
                                      DBM_TRUE,
                                      v2 );
         }
#line 5841 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 2728 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = dbmMakeIdentifier( param,
                                        v1 );
            }
#line 5850 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 2733 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = dbmMakeIdentifier( param,
                                        v1 );
            }
#line 5859 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 2741 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmChar          * sVal = (dbmChar *)v1;
                     dbmChar          * sAttr = (dbmChar *)v3;
                     dbmChar          * sStr = NULL;
                     dbmInt32           sLen1 = 0;
                     dbmInt32           sLen2 = 0;
                     
                     sLen1 = dbmStrlen( sVal );
                     sLen2 = dbmStrlen( sAttr );

                     dbmAllocMemory( param->mAllocator,
                                     (sLen1 + sLen2 + 2),
                                     (void **)&sStr,
                                     param->mErrorStack );

                     dbmMemset( sStr, 0x00, (sLen1 + sLen2 + 2) );
                     dbmSnprintf( sStr, (sLen1 + sLen2 + 2), "%s%%%s", sVal, sAttr );

                     v0 = dbmMakeIdentifier( param,
                                             sStr );
                 }
#line 5885 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 2763 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmChar          * sVal = (dbmChar *)((dbmParseValue *)v1)->mValue;
                     dbmChar          * sAttr = (dbmChar *)v3;
                     dbmChar          * sStr = NULL;
                     dbmInt32           sLen1 = 0;
                     dbmInt32           sLen2 = 0;
                     
                     sLen1 = dbmStrlen( sVal );
                     sLen2 = dbmStrlen( sAttr );

                     dbmAllocMemory( param->mAllocator,
                                     (sLen1 + sLen2 + 2),
                                     (void **)&sStr,
                                     param->mErrorStack );

                     dbmMemset( sStr, 0x00, (sLen1 + sLen2 + 2) );
                     dbmSnprintf( sStr, (sLen1 + sLen2 + 2), "%s%%%s", sVal, sAttr );

                     v0 = dbmMakeIdentifier( param,
                                             sStr );
                 }
#line 5911 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 2787 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 5919 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 2791 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 5927 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 2795 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 5935 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 2799 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 5943 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 2806 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   dbmParseBindParam *sVar = dbmMakeBindParam( param,
                                                               v1 );
                   v0 = sVar;
               }
#line 5953 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 2814 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    dbmParseBindParam *sVar = dbmMakeBindParam( param,
                                                                NULL );
                    v0 = sVar;
               }
#line 5963 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 2822 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = dbmMakeStrValue( param,
                                      v1 );
            }
#line 5972 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 2830 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeIdentifierDoubleQuote( param,
                                                         v1 );
                  }
#line 5981 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 2840 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      dbmList       * sList = NULL;
 
                      dbmCreateList( param->mAllocator,
                                     &sList,
                                     param->mErrorStack );
 
                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_STRING,
                                  v1,
                                  param->mErrorStack );
 
                      v0 = sList;
                  }
#line 6001 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 2856 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      dbmList          * sList = v1;

                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_STRING,
                                  v3,
                                  param->mErrorStack );
                      v0 = sList;
                  }
#line 6016 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 2871 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList       * sList = NULL;
   
                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v1,
                                    param->mErrorStack );
   
                        v0 = sList;
                    }
#line 6036 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 2887 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        dbmList          * sList = v1;
  
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v3,
                                    param->mErrorStack );
                        v0 = sList;
                    }
#line 6051 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 2902 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmList       * sList = NULL;

                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_STRING,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
#line 6071 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 2918 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmAddList( param->mAllocator,
                                 v1,
                                 DBM_LIST_ELEM_STRING,
                                 v3,
                                 param->mErrorStack );
                     v0 = v1;
                 }
#line 6084 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 2931 "dbmParserGram.y" /* yacc.c:1646  */
    {
                v0 = v1;
            }
#line 6092 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 2935 "dbmParserGram.y" /* yacc.c:1646  */
    {
                dbmParseExpr    * sExpr = v1;
                sExpr->mAlias = v3;
                v0 = sExpr;
            }
#line 6102 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 2944 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmList       * sList = NULL;

                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
#line 6122 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2960 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     dbmAddList( param->mAllocator,
                                 v1,
                                 DBM_LIST_ELEM_POINTER,
                                 v3,
                                 param->mErrorStack );
                     v0 = v1;
                 }
#line 6135 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2972 "dbmParserGram.y" /* yacc.c:1646  */
    {
              v0 = v1;
          }
#line 6143 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2976 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseFunction * sFunc = NULL;

               sFunc = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_OR,
                                             v1,
                                             v3,
                                             NULL,
                                             NULL );

               v0 = dbmMakeParseExpr( param,
                                      DBM_PARSE_EXPR_FUNCTION,
                                      sFunc );
          }
#line 6162 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2991 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseFunction * sFunc = NULL;

               sFunc = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_OR,
                                             v2,
                                             v4,
                                             NULL,
                                             NULL );

               v0 = dbmMakeParseExpr( param,
                                      DBM_PARSE_EXPR_FUNCTION,
                                      sFunc );
          }
#line 6181 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 3009 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = v1;              
           }
#line 6189 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 3013 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = v2;              
           }
#line 6197 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 3017 "dbmParserGram.y" /* yacc.c:1646  */
    {
               dbmParseFunction * sFunc = NULL;
               sFunc = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_AND,
                                             v1,
                                             v3,
                                             NULL,
                                             NULL );

               v0 = dbmMakeParseExpr( param,
                                      DBM_PARSE_EXPR_FUNCTION,
                                      sFunc );
           }
#line 6215 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 3034 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = v1;
              }
#line 6223 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 3038 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeParseExpr( param,
                                         DBM_PARSE_EXPR_FUNCTION,
                                         v1 );
              }
#line 6233 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 3047 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_IDENTIFIER,
                                        v1 );
             }
#line 6243 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 3053 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_IDENTIFIER,
                                        v1 );
             }
#line 6253 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 3059 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
#line 6263 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 3065 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
#line 6273 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 3071 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
#line 6283 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 3077 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_BIND_PARAM,
                                        v1 );
             }
#line 6293 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 3083 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_BIND_PARAM,
                                        v1 );
             }
#line 6303 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 3089 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_FUNCTION,
                                        v1 );
             }
#line 6313 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 3095 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
#line 6323 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 3101 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_USER_LIB_FUNCTION,
                                        v1 );
             }
#line 6333 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 3107 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_NULL,
                                        NULL );
             }
#line 6343 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 3116 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeParseUserLibFunction( param,
                                                         v1,
                                                         v3 );
                   }
#line 6353 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 3125 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6361 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 3129 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6369 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 3133 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_SYSDATE,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6382 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 3142 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6390 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 3146 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6398 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 3150 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6406 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 3154 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6414 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 3158 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6422 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 3162 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6430 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 3166 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6438 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 3170 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6446 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 3174 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6454 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 3178 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6462 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 3182 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_TRIM,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6475 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 3191 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6483 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 3195 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6491 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 3199 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6499 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 3203 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6507 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 3207 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6515 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 3211 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6523 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 3215 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6531 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 3219 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6539 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 3223 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6547 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 3227 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6555 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 3231 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6563 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 3235 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6571 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 3239 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = v1;
                }
#line 6579 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 3243 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = v1;
                }
#line 6587 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 3247 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_SESSION_ID,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6600 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 3256 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_JSON_STRING,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6613 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 3265 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_JSON_STRING,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6626 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 3274 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6634 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 3278 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6642 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 3282 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_DATEDIFF,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 6655 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 3291 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 6663 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 3295 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    dbmParseExpr   * s1 = NULL;
                    s1 = dbmMakeParseExpr( param,
                                           DBM_PARSE_EXPR_CONST,
                                           v3 );
 
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_USERENV,
                                               s1,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6681 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 3309 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EMPTY_BLOB,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6694 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 3318 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EMPTY_CLOB,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6707 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 3327 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_HEXTORAW,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6720 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 3336 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_POWER,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 6733 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 3345 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_SQRT,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6746 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 3354 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EXP,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6759 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 3363 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LN,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6772 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 3372 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LOG,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 6785 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 3381 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_REPLACE,
                                               v3,
                                               v5,
                                               v7,
                                               NULL );
                }
#line 6798 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 3393 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_INSTR,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 6811 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 3402 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_INSTR,
                                               v3,
                                               v5,
                                               v7,
                                               NULL );
                }
#line 6824 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 3411 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_INSTR,
                                               v3,
                                               v5,
                                               v7,
                                               v9 );
                }
#line 6837 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 3420 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EXTRACT,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 6850 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 3432 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeParseFunction( param,
                                                 DBM_PARSE_FUNCTION_TO_DATE,
                                                 v3,
                                                 NULL,
                                                 NULL,
                                                 NULL );
                  }
#line 6863 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 3441 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeParseFunction( param,
                                                 DBM_PARSE_FUNCTION_TO_DATE,
                                                 v3,
                                                 v5,
                                                 NULL,
                                                 NULL );
                  }
#line 6876 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 3453 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           v0 = dbmMakeParseFunction( param,
                                                      DBM_PARSE_FUNCTION_TO_TIMESTAMP,
                                                      v3,
                                                      NULL,
                                                      NULL,
                                                      NULL );
                       }
#line 6889 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 3465 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_NVL,
                                             v3,
                                             v5,
                                             NULL,
                                             NULL );
              }
#line 6902 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 3478 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_UPPER,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6915 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 3490 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LOWER,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 6928 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 3502 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DECODE,
                                                v3,
                                                v5, 
                                                v6,
                                                NULL );
                 }
#line 6941 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 3513 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = NULL;
                   }
#line 6949 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 3517 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = v2;
                   }
#line 6957 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 3523 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      dbmList       * sList = NULL;

                      dbmCreateList( param->mAllocator,
                                     &sList,
                                     param->mErrorStack );

                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_POINTER,
                                  v1,
                                  param->mErrorStack );

                      v0 = sList;
                  }
#line 6977 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 3539 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      dbmAddList( param->mAllocator,
                                  v1,
                                  DBM_LIST_ELEM_POINTER,
                                  v3,
                                  param->mErrorStack );
                      v0 = v1;
                  }
#line 6990 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 3550 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = dbmMakeParseDecodeItem( param,
                                              v1, 
                                              v3 );
             }
#line 7000 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 3559 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_RANDOM,
                                                v3,
                                                v5, 
                                                NULL,
                                                NULL );
                 }
#line 7013 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 3570 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           v0 = dbmMakeParseFunction( param,
                                                      DBM_PARSE_FUNCTION_DATETIME_STR,
                                                      v3,
                                                      NULL, 
                                                      NULL, 
                                                      NULL );
                       }
#line 7026 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 3581 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LTRIM,
                                               v3,
                                               NULL, 
                                               NULL, 
                                               NULL );
                }
#line 7039 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 3590 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LTRIM,
                                               v3,
                                               v5, 
                                               NULL,
                                               NULL );
                }
#line 7052 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 3601 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_RTRIM,
                                               v3,
                                               NULL, 
                                               NULL, 
                                               NULL );
                }
#line 7065 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 3610 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_RTRIM,
                                               v3,
                                               v5, 
                                               NULL,
                                               NULL );
                }
#line 7078 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 3622 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LPAD,
                                              v3,
                                              v5, 
                                              v7,
                                              NULL );
               }
#line 7091 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 3633 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_RPAD,
                                              v3,
                                              v5, 
                                              v7,
                                              NULL );
               }
#line 7104 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 3644 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_LENGTH,
                                                v3,
                                                NULL,
                                                NULL,
                                                NULL );
                 }
#line 7117 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 3656 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DIGEST,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
                 }
#line 7130 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 3667 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_HEX,
                                             v3,
                                             NULL,
                                             NULL,
                                             NULL );
              }
#line 7143 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 3680 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 dbmParseExpr * sArg;
                 sArg = dbmMakeParseExpr( param,
                                          DBM_PARSE_EXPR_IDENTIFIER,
                                          v1 );

                 v0 = dbmMakeParseFunction( param,
                                            DBM_PARSE_FUNCTION_IN,
                                            sArg,
                                            v4,
                                            NULL,
                                            NULL );
             }
#line 7161 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 3697 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_CONCAT,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
                 }
#line 7174 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 3706 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_CONCAT,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
#line 7187 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 3718 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_SUBSTR,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
                 }
#line 7200 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 3728 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_SUBSTR,
                                                v3,
                                                v5,
                                                v7,
                                                NULL );
                 }
#line 7213 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 3740 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DUMP,
                                                v3,
                                                NULL,
                                                NULL,
                                                NULL );
               }
#line 7226 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 3749 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DUMP,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
               }
#line 7239 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 3760 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_MOD,
                                             v3,
                                             v5,
                                             NULL,
                                             NULL );
              }
#line 7252 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 3771 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_CEIL,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7265 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 3782 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_FLOOR,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 7278 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 3793 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_ROUND,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 7291 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 3802 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_ROUND,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 7304 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 3813 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_TRUNC,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
#line 7317 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 3822 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_TRUNC,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
#line 7330 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 3834 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_PLUS,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
#line 7343 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 3843 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_PLUS,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
#line 7356 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 3852 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MINUS,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
#line 7369 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 3861 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MINUS,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
#line 7382 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 3870 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MULTIPLE,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
#line 7395 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 3879 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MULTIPLE,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
#line 7408 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 3888 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DIVIDE,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
#line 7421 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 3897 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DIVIDE,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
#line 7434 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 3906 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_ABS,
                                                v3,
                                                NULL,
                                                NULL,
                                                NULL );
                 }
#line 7447 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 411:
#line 3918 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_COUNT,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7460 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 412:
#line 3927 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_COUNT,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7473 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 413:
#line 3936 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_SUM,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7486 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 414:
#line 3945 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_AVG,
                                              v3,
                                              v3,
                                              v3,
                                              NULL );
               }
#line 7499 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 3954 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_MAXVAL,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7512 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 3963 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_MINVAL,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7525 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 3975 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_EQ,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7538 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 3984 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_GE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7551 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 3993 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_GT,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7564 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 4002 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7577 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 4011 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LT,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7590 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 4020 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_NE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7603 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 4029 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LIKE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
#line 7616 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 4038 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_ISNULL,
                                              v1,
                                              NULL,
                                              NULL,
                                              NULL );
               }
#line 7629 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 4050 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseExpr *sExpr = NULL;
                       sExpr = dbmMakeParseExpr( param,
                                                 DBM_PARSE_EXPR_IDENTIFIER,
                                                 v1 );
                       v0 = dbmMakeParseFunction( param,
                                                  DBM_PARSE_FUNCTION_NEXTVAL,
                                                  sExpr,
                                                  NULL,
                                                  NULL,
                                                  NULL );
                   }
#line 7646 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 4063 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       dbmParseExpr *sExpr = NULL;
                       sExpr = dbmMakeParseExpr( param,
                                                 DBM_PARSE_EXPR_IDENTIFIER,
                                                 v1 );
                       v0 = dbmMakeParseFunction( param,
                                                  DBM_PARSE_FUNCTION_CURRVAL,
                                                  sExpr,
                                                  NULL,
                                                  NULL,
                                                  NULL );
                   }
#line 7663 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 4078 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7671 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 4082 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7679 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 4086 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7687 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 4090 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7695 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 4094 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7703 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 4098 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7711 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 4102 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7719 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 4106 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7727 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 4110 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7735 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 4114 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7743 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 4118 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7751 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 4124 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = v1;
           }
#line 7759 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 4130 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7767 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 4136 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7775 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 4143 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7783 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 4150 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = v1;
              }
#line 7791 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 4157 "dbmParserGram.y" /* yacc.c:1646  */
    {
                   v0 = v1;
               }
#line 7799 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 4163 "dbmParserGram.y" /* yacc.c:1646  */
    {
               v0 = v1;
           }
#line 7807 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 4169 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v1;
                 }
#line 7815 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 4176 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v1;
                 }
#line 7823 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 4182 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = v1;
                 }
#line 7831 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 4188 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = v1;
                  }
#line 7839 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 4195 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = v1;
                    }
#line 7847 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 4202 "dbmParserGram.y" /* yacc.c:1646  */
    {
                 v0 = v1;
             }
#line 7855 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 4208 "dbmParserGram.y" /* yacc.c:1646  */
    {
                  v0 = v1;
              }
#line 7863 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 4214 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = v1;
                }
#line 7871 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 4220 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = v1;
                    }
#line 7879 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 4232 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeCreateGsbNodeStmt( param, v4, v6, v8, v10 );
                 }
#line 7887 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 4238 "dbmParserGram.y" /* yacc.c:1646  */
    {
                    v0 = dbmMakeDropGsbNodeStmt( param, v4 );
               }
#line 7895 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 4251 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateGsbMonitorStmt( param, v4, v6, v8, v10, v12 );
                    }
#line 7903 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 4257 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeDropGsbMonitorStmt( param, v4 );
                  }
#line 7911 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 4267 "dbmParserGram.y" /* yacc.c:1646  */
    {
                             v0 = dbmMakeCreateGsbSvrGrpStmt( param, v5, v7 );
                         }
#line 7919 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 4274 "dbmParserGram.y" /* yacc.c:1646  */
    {
                           v0 = dbmMakeDropGsbSvrGrpStmt( param, v5 );
                       }
#line 7927 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 4287 "dbmParserGram.y" /* yacc.c:1646  */
    {
                       v0 = dbmMakeCreateGsbSvrStmt( param, v4, v6, v8, v10, v12, v14 );
                   }
#line 7935 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 461:
#line 4294 "dbmParserGram.y" /* yacc.c:1646  */
    {
                     v0 = dbmMakeDropGsbSvrStmt( param, v4 );
                 }
#line 7943 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 462:
#line 4307 "dbmParserGram.y" /* yacc.c:1646  */
    {
                        v0 = dbmMakeCreateGsbSvcStmt( param, v4, v6, v8, v10 );
                    }
#line 7951 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 463:
#line 4314 "dbmParserGram.y" /* yacc.c:1646  */
    {
                      v0 = dbmMakeDropGsbSvcStmt( param, v4 );
                  }
#line 7959 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 4322 "dbmParserGram.y" /* yacc.c:1646  */
    {
                             v0 = dbmMakeAlterGsbProcCntStmt( param, v3, v7 );
                         }
#line 7967 "dbmParserGram.tab.c" /* yacc.c:1646  */
    break;


#line 7971 "dbmParserGram.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
      yyerror (&yylloc, param, scanner, YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (&yylloc, param, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, param, scanner);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, param, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, param, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, param, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, param, scanner);
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
#line 4331 "dbmParserGram.y" /* yacc.c:1906  */



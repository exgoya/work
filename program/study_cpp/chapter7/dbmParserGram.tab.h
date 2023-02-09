/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

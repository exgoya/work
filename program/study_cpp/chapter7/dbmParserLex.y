%{
#include <dbmStruct.h>
#include <dbmParser.h>
#include <dbmParserGram.tab.h>
%}

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge bison-locations
%option case-sensitive
%option nounput
%option noinput
%option yylineno


comment_introducer               "/*"
comment_terminator               "*/"
simple_comment                   "--"[^\n]*
c_simple_comment                 "//"[^\n]*
blanks                           [ \t\n\v\f\r]+
plus_sign                        "+"
minus_sign                       "-"
asterisk                         "*"
solidus                          "/"
comma                            ","
period                           "."
colon                            ":"
semicolon                        ";"
underscore                       "_"
question_mark                    "?"
equal_operator                   "="
less_than_operator               "<"
greater_than_operator            ">"
not_equal_operator_expand        "!="
left_paren                       "("
right_paren                      ")"
left_bracket                     "["
right_bracket                    "]"
left_brace                       "{"
right_brace                      "}"
proc_assign                      ":="
percent                          "%"
proc_iter                        ".."
proc_left_label                  "<<"
proc_right_label                 ">>"

not_equal_operator               {less_than_operator}{greater_than_operator}
less_than_equal_operator         {less_than_operator}{equal_operator}
greater_than_equal_operator      {greater_than_operator}{equal_operator}
quote                            "\'"
quote_symbol                     "\'\'"
quote_string                     {quote_symbol}|{quote}([^\']|{quote_symbol})+{quote}
double_quote                     "\""
double_quote_string              {double_quote}[^\"]*{double_quote}

digit                            [0-9]
digits                           {digit}+
hex_digit                        [a-fA-F0-9]
hex_digits                       {white_space}*{hex_digit}{white_space}*{hex_digit}{white_space}*
hex_string                       [xX]{quote}{hex_digits}*{quote}

identifier_start                 [a-zA-Z\200-\377_]
identifier_continue              [a-zA-Z\200-\377_0-9\$]
identifier                       {identifier_start}{identifier_continue}*
host_variable                    {colon}{identifier}

unsigned_integer_literal         {digits}[dDfF]?
positive_integer_literal         [+][ ]*{digits}
negative_integer_literal         [-][ ]*{digits}

concat_operator                  "||"
dollar_sign                      "$"
sharp                            "#"
at_sign                          "@"



unsigned_range_numeric_literal   {digits}{period}{period}
unsigned_exact_numeric_literal   {digits}{period}[dDfF]?|{digits}{period}{digits}[dDfF]?|{period}{digits}[dDfF]?
unsigned_approximate_numeric_literal  {digits}[eE][+-]?{digits}[dDfF]?|{unsigned_exact_numeric_literal}[eE][+-]?{digits}[dDfF]?

bracketed_comment_1        {comment_introducer}{comment_terminator}|{comment_introducer}([^+])([^*]|(\*+[^*/]))*\**{comment_terminator}
bracketed_comment          {bracketed_comment_1}


%%

{blanks}                          { /* ignore */ }
{plus_sign}                       { DBM_IGNORE_STR(PARAM); return TOK_PLUS; }
{minus_sign}                      { DBM_IGNORE_STR(PARAM); return TOK_MINUS; }
{asterisk}                        { DBM_IGNORE_STR(PARAM); return TOK_ASTERISK; }
{solidus}                         { DBM_IGNORE_STR(PARAM); return TOK_SOLIDUS; }
{comma}                           { DBM_IGNORE_STR(PARAM); return TOK_COMMA; }
{semicolon}                       { DBM_IGNORE_STR(PARAM); return TOK_SEMICOLON; }
{colon}                           { DBM_IGNORE_STR(PARAM); return TOK_COLON; }
{period}                          { DBM_IGNORE_STR(PARAM); return TOK_PERIOD; }
{question_mark}                   { DBM_IGNORE_STR(PARAM); return TOK_QUESTION; }
{left_paren}                      { DBM_IGNORE_STR(PARAM); return TOK_LEFT_PAREN; }
{right_paren}                     { DBM_IGNORE_STR(PARAM); return TOK_RIGHT_PAREN; }
{quote}                           { DBM_IGNORE_STR(PARAM); return TOK_QUOTE; }
{double_quote}                    { DBM_IGNORE_STR(PARAM); return TOK_DOUBLE_QUOTE; }
{underscore}                      { DBM_IGNORE_STR(PARAM); return TOK_UNDERSCORE; }
{concat_operator}                 { DBM_IGNORE_STR(PARAM); return TOK_CONCAT_OPER; }
{proc_assign}                     { DBM_IGNORE_STR(PARAM); return TOK_PROC_ASSIGN; }
{percent}                         { DBM_IGNORE_STR(PARAM); return TOK_PERCENT; }
{proc_iter}                       { DBM_IGNORE_STR(PARAM); return TOK_PROC_ITER; }
{proc_left_label}                 { DBM_IGNORE_STR(PARAM); return TOK_PROC_LEFT_LABEL; }
{proc_right_label}                { DBM_IGNORE_STR(PARAM); return TOK_PROC_RIGHT_LABEL; }



{comment_terminator}              { DBM_IGNORE_STR(PARAM); return TOK_COMMENT_TERM; }
{simple_comment}                  { DBM_IGNORE_STR(PARAM); }
{c_simple_comment}                { DBM_IGNORE_STR(PARAM); }
{bracketed_comment}               { DBM_IGNORE_STR(PARAM); }



{equal_operator}                  { DBM_IGNORE_STR(PARAM); return TOK_EQ; }
{less_than_operator}              { DBM_IGNORE_STR(PARAM); return TOK_LT; }
{greater_than_operator}           { DBM_IGNORE_STR(PARAM); return TOK_GT; }
{less_than_equal_operator}        { DBM_IGNORE_STR(PARAM); return TOK_LE; }
{greater_than_equal_operator}     { DBM_IGNORE_STR(PARAM); return TOK_GE; }
{not_equal_operator}              { DBM_IGNORE_STR(PARAM); return TOK_NE; }
{not_equal_operator_expand}       { DBM_IGNORE_STR(PARAM); return TOK_NE; }

{unsigned_integer_literal}        { DBM_RETURN_IDENTIFIER( PARAM, yytext ); return( TOK_UINT ); }
{unsigned_exact_numeric_literal}  { DBM_RETURN_IDENTIFIER( PARAM, yytext ); return( TOK_UNUM ); }

{dollar_sign}    { DBM_IGNORE_STR( PARAM ); return TOK_DOLLAR_SIGN; }
{sharp}          { DBM_IGNORE_STR( PARAM ); return TOK_SHARP; }
{at_sign}        { DBM_IGNORE_STR( PARAM ); return TOK_AT_SIGN; }



{identifier} {
    dbmKeyWord      * sKeyWord = NULL;
    int               sLen;
    int               i;


    sLen = dbmStrlen( yytext );

    for( i = 0; i < sLen; i++)
    {
        yytext[i] = toupper(yytext[i]);
    }


    sKeyWord = dbmLookUpKeyWord( yytext );

    if( sKeyWord == NULL )
    {
        DBM_RETURN_IDENTIFIER( PARAM, yytext );
        return( TOK_IDENTIFIER );
    }
    else
    {
        DBM_RETURN_IDENTIFIER( PARAM, yytext );
        return( sKeyWord->mCode );
        //DBM_RETURN_STR( PARAM, sKeyWord->mName );
        //return( sKeyWord->mCode );
    }
}



{host_variable} {
    dbmKeyWord      * sKeyWord = NULL;
    int               sLen;
    int               i;


    sLen = dbmStrlen( yytext );

    for( i = 1; i < sLen; i++)
    {
        yytext[i-1] = toupper(yytext[i]);
    }


    sKeyWord = dbmLookUpKeyWord( yytext );

    if( sKeyWord == NULL )
    {
        DBM_RETURN_HOST_VARIABLE( PARAM, yytext, (sLen-1) );
        return( TOK_HOST_VARIABLE );
    }
    else
    {
        DBM_RETURN_HOST_VARIABLE( PARAM, yytext, (sLen-1) );
        return( sKeyWord->mCode );
    }
}



{quote_string} {
    yyleng = yyleng - 2;

    DBM_RETURN_QUOTE_STRING( PARAM, yytext + 1 );
    return( TOK_QUOTE_STRING );
}

{double_quote_string} {
    yyleng = yyleng - 2;
    DBM_RETURN_DOUBLE_QUOTE_STRING( PARAM, yytext + 1);
    return TOK_DOUBLE_QUOTE_STRING;
}




%%

const dbmKeyWord dbmKeyWordList[] =
{
    {"ABS",            TOK_ABS},
    {"ACTIVE",         TOK_ACTIVE},
    {"ADD",            TOK_ADD},
    {"AGING",          TOK_AGING},
    {"ALL",            TOK_ALL},
    {"ALTER",          TOK_ALTER},
    {"AND",            TOK_AND},
    {"AS",             TOK_AS},
    {"ASC",            TOK_ASCENDING},
    {"AVG",            TOK_AVG},
    {"BEGIN",          TOK_BEGIN},
    {"BY",             TOK_BY},
    {"CALL",           TOK_CALL},
    {"CAPTURE",        TOK_CAPTURE},
    {"CASE",           TOK_CASE},
    {"CEIL",           TOK_CEIL},
    {"CHAR",           TOK_CHAR},
    {"CHECKPOINT",     TOK_CHECKPOINT},
    {"CLOSE",          TOK_CLOSE},
    {"COLUMN",         TOK_COLUMN},
    {"COMMIT",         TOK_COMMIT},
    {"COMPACT",        TOK_COMPACT},
    {"CONCAT",         TOK_CONCAT},
    {"CONTINUE",       TOK_CONTINUE},
    {"COUNT",          TOK_COUNT},
    {"CREATE",         TOK_CREATE},
    {"CURRVAL",        TOK_CURRVAL},
    {"CURSOR",         TOK_CURSOR},
    {"CYCLE",          TOK_CYCLE},
    {"DATE",           TOK_DATE},
    {"DATEDIFF",       TOK_DATEDIFF},
    {"DATETIME_STR",   TOK_DATETIME_STR},
    {"DBMS_OUTPUT",    TOK_DBMSOUTPUT},
    {"DECLARE",        TOK_DECLARE},
    {"DECODE",         TOK_DECODE},
    {"DEFAULT",        TOK_DEFAULT},
    {"DELETE",         TOK_DELETE},
    {"DEQUEUE",        TOK_DEQUEUE},
    {"DESC",           TOK_DESCENDING},
    {"DIGEST",         TOK_DIGEST},
    {"DIRECT",         TOK_DIRECT},
    {"DOUBLE",         TOK_DOUBLE},
    {"DROP",           TOK_DROP},
    {"DUMP",           TOK_DUMP},
    {"DURATION",       TOK_DURATION},
    {"ELSE",           TOK_ELSE},
    {"ELSIF",          TOK_ELSIF},
    {"EMPTY_BLOB",     TOK_EMPTY_BLOB},
    {"EMPTY_CLOB",     TOK_EMPTY_CLOB},
    {"END",            TOK_END},
    {"ENQUEUE",        TOK_ENQUEUE},
    {"EXCEPTION",      TOK_EXCEPTION},
    {"EXCEPTION_INIT", TOK_EXCEPTION_INIT},
    {"EXEC",           TOK_EXEC},
    {"EXIT",           TOK_EXIT},
    {"EXP",            TOK_EXP},
    {"EXPIRED",        TOK_EXPIRED},
    {"EXTEND",         TOK_EXTEND},
    {"EXTERNAL",       TOK_EXTERNAL},
    {"EXTRACT",        TOK_EXTRACT},
    {"FETCH",          TOK_FETCH},
    {"FLOAT",          TOK_FLOAT},
    {"FLOOR",          TOK_FLOOR},
    {"FIELDS",         TOK_FIELDS},
    {"FINI",           TOK_FINI},
    {"FOR",            TOK_FOR},
    {"FOUND",          TOK_FOUND},
    {"FROM",           TOK_FROM},
    {"FUNCTION",       TOK_FUNCTION},
    {"GOTO",           TOK_GOTO},
    {"GROUP",          TOK_GROUP},
    {"GSB",            TOK_GSB},
    {"HEXTORAW",       TOK_HEXTORAW},
    {"LENGTH",         TOK_LENGTH},
    {"LIBRARY",        TOK_LIBRARY},
    {"LIKE",           TOK_LIKE},
    {"LIMIT",          TOK_LIMIT},
    {"LN",             TOK_LN},
    {"LOAD",           TOK_LOAD},
    {"LOCAL",          TOK_LOCAL},
    {"LOG",            TOK_LOG},
    {"LONG",           TOK_LONG},
    {"LOOP",           TOK_LOOP},
    {"LOWER",          TOK_LOWER},
    {"LPAD",           TOK_LPAD},
    {"LTRIM",          TOK_LTRIM},
    {"HEX",            TOK_HEX},
    {"IF",             TOK_IF},
    {"IN",             TOK_IN},
    {"INSTR",          TOK_INSTR},
    {"IS",             TOK_IS},
    {"ISOPEN",         TOK_ISOPEN},
    {"INACTIVE",       TOK_INACTIVE},
    {"INCREMENT",      TOK_INCREMENT},
    {"INDEX",          TOK_INDEX},
    {"INIT",           TOK_INIT},
    {"INOUT",          TOK_INOUT},
    {"INSERT",         TOK_INSERT},
    {"INSTANCE",       TOK_INSTANCE},
    {"INT",            TOK_INT},
    {"INTEGER",        TOK_INTEGER},
    {"INTERVAL",       TOK_INTERVAL},
    {"INTO",           TOK_INTO},
    {"JSON_ADD",       TOK_JSON_ADD},
    {"JSON_DELETE",    TOK_JSON_DELETE},
    {"JSON_KEY",       TOK_JSON_KEY},
    {"JSON_QUERY",     TOK_JSON_QUERY},
    {"JSON_STRING",    TOK_JSON_STRING},
    {"JSON_VALUE",     TOK_JSON_VALUE},
    {"MAX",            TOK_MAX},
    {"MAXVALUE",       TOK_MAXVALUE},
    {"MIN",            TOK_MIN},
    {"MINVALUE",       TOK_MINVALUE},
    {"MOD",            TOK_MOD},
    {"MONITOR",        TOK_MONITOR},
    {"NEXTVAL",        TOK_NEXTVAL},
    {"NOCYCLE",        TOK_NOCYCLE},
    {"NODE",           TOK_NODE},
    {"NOTFOUND",       TOK_NOTFOUND},
    {"NULL",           TOK_NULL},
    {"NVL",            TOK_NVL},
    {"ON",             TOK_ON},
    {"OPEN",           TOK_OPEN},
    {"OR",             TOK_OR},
    {"ORDER",          TOK_ORDER},
    {"OTHERS",         TOK_OTHERS},
    {"OUT",            TOK_OUT},
    {"QUEUE",          TOK_QUEUE},
    {"PARAMETER",      TOK_PARAMETER},
    {"PARAM32",        TOK_PARAM_32},
    {"PARAM64",        TOK_PARAM_64},
    {"PARAM",          TOK_PARAM_PTR},
    {"PERF",           TOK_PERF},
    {"POWER",          TOK_POWER},
    {"PRAGMA",         TOK_PRAGMA},
    {"PROCEDURE",      TOK_PROCEDURE},
    {"PROCESS",        TOK_PROCESS},
    {"PUT_LINE",       TOK_PUT_LINE},
    {"RAISE",          TOK_RAISE},
    {"RAISE_APPLICATION_ERROR", TOK_RAISE_APPLICATION_ERROR},
    {"RANDOM",         TOK_RANDOM},
    {"REBUILD",        TOK_REBUILD},
    {"RENAME",         TOK_RENAME},
    {"REPLICATION",    TOK_REPL},
    {"REPLACE",        TOK_REPLACE},
    {"RESET",          TOK_RESET},
    {"RETURN",         TOK_RETURN},
    {"REVERSE",        TOK_REVERSE},
    {"RPAD",           TOK_RPAD},
    {"ROLLBACK",       TOK_ROLLBACK},
    {"ROUND",          TOK_ROUND},
    {"ROWCOUNT",       TOK_ROWCOUNT},
    {"ROWTYPE",        TOK_ROWTYPE},
    {"RTRIM",          TOK_RTRIM},
    {"START",          TOK_START},
    {"SELECT",         TOK_SELECT},
    {"SEQUENCE",       TOK_SEQUENCE},
    {"SERVER",         TOK_SERVER},
    {"SERVICE",        TOK_SERVICE},
    {"SESSION",        TOK_SESSION},
    {"SESSION_ID",     TOK_SESSION_ID},
    {"SET",            TOK_SET},
    {"SHORT",          TOK_SHORT},
    {"SLOT",           TOK_SLOT},
    {"SIZE",           TOK_SIZE},
    {"SQL",            TOK_SQL},
    {"SQRT",           TOK_SQRT},
    {"SUBSTR",         TOK_SUBSTR},
    {"SUM",            TOK_SUM},
    {"SUMMARY",        TOK_SUMMARY},
    {"SYNC",           TOK_SYNC},
    {"SYSDATE",        TOK_SYSDATE},
    {"SYSTEM",         TOK_SYSTEM},
    {"TABLE",          TOK_TABLE},
    {"TARGET",         TOK_TARGET},
    {"TERMINATE",      TOK_TERMINATE},
    {"THEN",           TOK_THEN},
    {"TIMEOUT",        TOK_TIMEOUT},
    {"TO",             TOK_TO},
    {"TO_DATE",        TOK_TO_DATE},
    {"TO_TIMESTAMP",   TOK_TO_TIMESTAMP},
    {"TRIM",           TOK_TRIM},
    {"TRUNC",          TOK_TRUNC},
    {"TRUNCATE",       TOK_TRUNCATE},
    {"TYPE",           TOK_TYPE},
    {"UNIQUE",         TOK_UNIQUE},
    {"UPDATE",         TOK_UPDATE},
    {"UPPER",          TOK_UPPER},
    {"USER_ENV",       TOK_USERENV},
    {"USING",          TOK_USING},
    {"VALUES",         TOK_VALUES},
    {"WHEN",           TOK_WHEN},
    {"WHERE",          TOK_WHERE},
    {"WHILE",          TOK_WHILE},
    {"WITH",           TOK_WITH}
};


const int dbmKeyWordCount = sizeof( dbmKeyWordList ) / sizeof( dbmKeyWordList[ 0 ] );

dbmKeyWord * dbmLookUpKeyWord( const char   * aWord )
{
    int i;

    for(i = 0; i< dbmKeyWordCount; i++ )
    {
        if( dbmStrcmp( dbmKeyWordList[i].mName, aWord ) == 0 )
        {
            return (dbmKeyWord *)& dbmKeyWordList[ i ];
        }
    }

    return NULL;
}

int yyerror( YYLTYPE                 * aLocation,
             dbmParserContext        * aParam,
             void                    * aScanner,
             const char              * aMsg )
{
    return 0;
}


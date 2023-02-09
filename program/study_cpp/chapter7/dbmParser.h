#ifndef __DBM_PARSER_H
#define __DBM_PARSER_H 1

#include <dbmTypes.h>
#include <dbmStruct.h>
#include <dbmDef.h>
#include <dbmDefEx.h>



#define DBM_MAX_PARSER_SIZE    (1024 * 1024 * 10)
#define YYSTYPE                void *
#define YYLTYPE                dbmInt32
#define YY_EXTRA_TYPE          dbmParserContext *
#define PARAM                  yyget_extra(yyscanner)


#define YYLLOC_DEFAULT(Current, Rhs, N)         \
    do {                                        \
        if (N)                                  \
            (Current) = (Rhs)[1];               \
        else                                    \
            (Current) = (Rhs)[0];               \
    } while (0)


#define DBM_IGNORE_STR( param )                 \
    {                                           \
        *yylloc = PARAM->mCurrLoc;              \
    }


#define DBM_RETURN_QUOTE_STRING( param, text )                      \
    {                                                               \
        dbmUInt32 sCursor = 0;                                            \
        dbmChar * sCurChar = NULL;                                     \
        dbmChar * sResult  = NULL;                                     \
                                                                    \
        dbmAllocMemory( (param)->mAllocator,                        \
                        yyleng + 1,                                 \
                        (void **)yylval,                            \
                        (param)->mErrorStack );                     \
        if( yyleng == 0)                                            \
        {                                                           \
            ((dbmChar*)(*yylval))[0] = '\0';                           \
        }                                                           \
        else                                                        \
        {                                                           \
            sCurChar = (dbmChar*) text;                                \
            sResult  = (dbmChar*) *yylval;                             \
            for( sCursor = 0; sCursor < (dbmUInt32)yyleng ; sCursor++ )        \
            {                                                       \
                if( ( sCurChar[0] == '\'' ) &&                      \
                    ( sCurChar[1] == '\'' ) )                       \
                {                                                   \
                    *sResult = '\'';                                \
                    sCurChar++;                                     \
                    yyleng--;                                       \
                }                                                   \
                else                                                \
                {                                                   \
                    *sResult = *sCurChar;                           \
                }                                                   \
                                                                    \
                sCurChar++;                                         \
                sResult++;                                          \
            }                                                       \
                                                                    \
            ((dbmChar*)(*yylval))[yyleng] = '\0';                      \
        }                                                           \
        *yylloc = PARAM->mCurrLoc;                                  \
    }


#define DBM_RETURN_DOUBLE_QUOTE_STRING( param, text )               \
    {                                                               \
        dbmUInt32 sCursor = 0;                                            \
        dbmChar * sCurChar = NULL;                                     \
        dbmChar * sResult  = NULL;                                     \
                                                                    \
        dbmAllocMemory( (param)->mAllocator,                        \
                        yyleng + 1,                                 \
                        (void **)yylval,                            \
                        (param)->mErrorStack );                     \
        if( yyleng == 0)                                            \
        {                                                           \
            ((dbmChar*)(*yylval))[0] = '\0';                           \
        }                                                           \
        else                                                        \
        {                                                           \
            sCurChar = (dbmChar*) text;                                \
            sResult  = (dbmChar*) *yylval;                             \
            for( sCursor = 0; sCursor < (dbmUInt32)yyleng ; sCursor++ )        \
            {                                                       \
                if( ( sCurChar[0] == '\"' ) &&                      \
                    ( sCurChar[1] == '\"' ) )                       \
                {                                                   \
                    *sResult = '\"';                                \
                    sCurChar++;                                     \
                    yyleng--;                                       \
                }                                                   \
                else                                                \
                {                                                   \
                    *sResult = *sCurChar;                           \
                }                                                   \
                                                                    \
                sCurChar++;                                         \
                sResult++;                                          \
            }                                                       \
                                                                    \
            ((dbmChar*)(*yylval))[yyleng] = '\0';                      \
        }                                                           \
        *yylloc = PARAM->mCurrLoc;                                  \
    }



#define DBM_RETURN_STR( param, text )                                   \
    {                                                                   \
        if( yyleng > 0)                                 \
        {                                               \
            dbmAllocMemory( (param)->mAllocator,        \
                            yyleng + 1,                 \
                            (void **)yylval,            \
                            (param)->mErrorStack );     \
            dbmMemcpy( (void*) *yylval, text, yyleng );    \
            ((dbmChar*)(*yylval))[yyleng] = '\0';          \
            *yylloc = PARAM->mCurrLoc;                  \
        }                                               \
    }


#define DBM_RETURN_IDENTIFIER( param, text )            \
    {                                                   \
        if( yyleng > 0)                                 \
        {                                               \
            dbmAllocMemory( (param)->mAllocator,        \
                            yyleng + 1,                 \
                            (void **)yylval,            \
                            (param)->mErrorStack );     \
            dbmMemcpy( (void*) *yylval, text, yyleng );    \
            ((dbmChar*)(*yylval))[yyleng] = '\0';          \
            *yylloc = PARAM->mCurrLoc;                  \
        }                                               \
    }

#define DBM_RETURN_HOST_VARIABLE( param, text, len )    \
    {                                                   \
        if( yyleng > 0)                                 \
        {                                               \
            dbmAllocMemory( (param)->mAllocator,        \
                            len + 1,                    \
                            (void **)yylval,            \
                            (param)->mErrorStack );     \
            dbmMemcpy( (void*) *yylval, text, len );       \
            ((dbmChar*)(*yylval))[len] = '\0';             \
            *yylloc = PARAM->mCurrLoc;                  \
        }                                               \
    }


#define YY_INPUT( buffer, res, max_size )                               \
    do {                                                                \
        if (PARAM->mPosition >= PARAM->mStmtLength)                     \
        {                                                               \
            res = YY_NULL;                                              \
        }                                                               \
        else                                                            \
        {                                                               \
            res = PARAM->mStmtLength - PARAM->mPosition;                \
            res > max_size ? res = max_size : 0;                   \
            dbmMemcpy(buffer, PARAM->mBuffer + PARAM->mPosition, res);     \
            PARAM->mPosition += res;                                    \
        }                                                               \
    } while (0)

#define YY_USER_ACTION                                  \
    {                                                   \
        dbmChar * sStr;                                    \
        if( yylineno != PARAM->mLineNo )                \
        {                                               \
            PARAM->mColumn = 1;                         \
            PARAM->mLength = 0;                         \
            sStr = PARAM->mBuffer + PARAM->mNextLoc     \
                   + yyleng - 1;                        \
            while( *sStr != '\n' )                      \
            {                                           \
                PARAM->mLength++;                       \
                sStr--;                                 \
            }                                           \
        }                                               \
        else                                            \
        {                                               \
            PARAM->mColumn += PARAM->mLength;           \
            PARAM->mLength  = yyleng;                   \
        }                                               \
        *yylloc = PARAM->mCurrLoc;                      \
        PARAM->mLineNo  = yylineno;                     \
        PARAM->mCurrLoc = PARAM->mNextLoc;              \
        PARAM->mNextLoc += yyleng;                      \
    }



#define YYSTYPE         void *
#define YYCHAR          (yychar)
#define v0              (yyval)
#define v1              (yyvsp[(1) - (yylen)])
#define v2              (yyvsp[(2) - (yylen)])
#define v3              (yyvsp[(3) - (yylen)])
#define v4              (yyvsp[(4) - (yylen)])
#define v5              (yyvsp[(5) - (yylen)])
#define v6              (yyvsp[(6) - (yylen)])
#define v7              (yyvsp[(7) - (yylen)])
#define v8              (yyvsp[(8) - (yylen)])
#define v9              (yyvsp[(9) - (yylen)])
#define v10             (yyvsp[(10) - (yylen)])
#define v11             (yyvsp[(11) - (yylen)])
#define v12             (yyvsp[(12) - (yylen)])
#define v13             (yyvsp[(13) - (yylen)])
#define v14             (yyvsp[(14) - (yylen)])
#define v15             (yyvsp[(15) - (yylen)])
#define v16             (yyvsp[(16) - (yylen)])


#define a0              (yyloc)
#define a1              (yylsp[(1) - (yylen)])
#define a2              (yylsp[(2) - (yylen)])
#define a3              (yylsp[(3) - (yylen)])
#define a4              (yylsp[(4) - (yylen)])
#define a5              (yylsp[(5) - (yylen)])
#define a6              (yylsp[(6) - (yylen)])
#define a7              (yylsp[(7) - (yylen)])
#define a8              (yylsp[(8) - (yylen)])
#define a9              (yylsp[(9) - (yylen)])
#define a10             (yylsp[(10) - (yylen)])
#define a11             (yylsp[(11) - (yylen)])
#define a12             (yylsp[(12) - (yylen)])
#define a13             (yylsp[(13) - (yylen)])
#define a14             (yylsp[(14) - (yylen)])
#define a15             (yylsp[(15) - (yylen)])
#define a16             (yylsp[(16) - (yylen)])


dbmKeyWord * dbmLookUpKeyWord( const dbmChar* aWord );

dbmStatus dbmInitParserContext( dbmParserContext    * aCtx,
                                dbmErrorStack       * aErrorStack );

dbmStatus dbmParseText( dbmParserContext    * aCtx,
                        const dbmChar       * aString,
                        dbmErrorStack       * aErrorStack );

void dbmFinalizeParserContext( dbmParserContext * aCtx );


#endif

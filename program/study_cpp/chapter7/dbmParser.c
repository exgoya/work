/**
 * @file   dbmParser.c
 * @brief  Parser와 연관된 함수 처리 루틴
 */
#include <dbmTypes.h>
#include <dbmDef.h>
#include <dbmDefEx.h>
#include <dbmStruct.h>
#include <dbmParserObject.h>
#include <dbmErrorCode.h>


int yylex_init( void * scanner );
int yyparse( dbmParserContext * param, void * scanner );
int yylex_destroy( void * yyscanner );
void yyset_extra( dbmParserContext * param, void * yyscanner );


/**
 * @brief Parser수행전 context를 초기화 한다.
 */
dbmStatus dbmInitParserContext( dbmParserContext    * aCtx,
                                dbmErrorStack       * aErrorStack )
{
    /**
     * 입력항목 체크
     */

    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );

    dbmMemset( aCtx, 0x00, sizeof( dbmParserContext ) );


    /**
     * Scanner 할당
     */

    yylex_init( & aCtx->mScanner );

    DBM_TRY_THROW( aCtx->mScanner != NULL, RAMP_ERR_ALLOC_FAIL1 );



    /**
     * Validate까지 쓸 메모리할당
     */

    DBM_TRY_THROW( dbmCreateAllocator( & aCtx->mAllocator,
                                       aErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_INIT_ALLOCATOR );


    /**
     * Context 설정
     */

    aCtx->mSize       = 0;
    aCtx->mLineNo     = 1;
    aCtx->mColumn     = 0;
    aCtx->mPosition   = 0;
    aCtx->mLength     = 0;
    aCtx->mCurrLoc    = 0;
    aCtx->mNextLoc    = 0;
    aCtx->mBindCount  = 0;
    aCtx->mErrorStack = aErrorStack;

    yyset_extra( aCtx, aCtx->mScanner );


    /**
     * 정상
     */

    return DBM_SUCCESS;

    /**
     * 오류처리
     */

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL1 )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_MEMORY_NOT_SUFFICIENT,
                      NULL,
                      aErrorStack,
                      errno );
    }

    DBM_CATCH( RAMP_ERR_INIT_ALLOCATOR )
    {
    }

    DBM_FINISH;

    return DBM_FAILURE;
}



/**
 * @brief Parsing을 수행할 함수
 */
dbmStatus dbmParseText( dbmParserContext    * aCtx,
                        const dbmChar       * aString,
                        dbmErrorStack       * aErrorStack )
{
  
    /**
     * 입력항목 체크
     */

    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aString != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( dbmStrlen( aString ) > 0, RAMP_ERR_INVALID_ARGS );


    /**
     * Context에 설정
     */

    aCtx->mBuffer = (dbmChar *)aString; 
    aCtx->mStmtLength = dbmStrlen( aString );


    /**
     * Parse 수행
     */

    DBM_TRY_THROW( yyparse( aCtx, aCtx->mScanner ) == 0,
                   RAMP_ERR_PARSE_FAIL );

    DBM_TRY_THROW( aCtx->mParseObj != NULL, RAMP_ERR_PARSE_FAIL );


    /**
     * 정상
     */

    return DBM_SUCCESS;

    /**
     * 오류처리
     */

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_PARSE_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_PARSE,
                      NULL,
                      aErrorStack,
                      aCtx->mLineNo,
                      aCtx->mColumn );
    }

    DBM_FINISH;

    return DBM_FAILURE;
}



/**
 * @brief  Scanner 삭제
 */
void dbmFinalizeParserContext( dbmParserContext * aCtx )
{
    if( aCtx->mScanner != NULL )
    {
        (void) dbmDropAllocator( &aCtx->mAllocator,
                                 aCtx->mErrorStack );

        yylex_destroy( aCtx->mScanner );
    }

    aCtx->mScanner = NULL;
}





/**
 * @brief number type을 1개 생성
 */
dbmParseValue  * dbmMakeNumberValue( dbmParserContext     * aCtx,
                                     dbmBool                aIsMinus,
                                     dbmChar              * aValue )
{
    dbmParseValue    * sValue = NULL;
    dbmChar          * sTmpVal = NULL;
    dbmInt32           sSize  = 0;


    /**
     * ParseValue 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseValue),
                                   (void **)&sValue,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sValue, 0x00, sizeof(dbmParseValue) );


    /**
     * ParseValue 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    if( aIsMinus == DBM_TRUE )
    {
        sSize = dbmStrlen(aValue) + 1;
        DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                       (sSize + 1),
                                       (void **)&sTmpVal,
                                       aCtx->mErrorStack ) == DBM_SUCCESS,
                       RAMP_ERR_ALLOC_FAIL );

        dbmMemset( sTmpVal, 0x00, (sSize + 1) );
        dbmStrcpy( sTmpVal, "-" );
        dbmStrcat( sTmpVal, aValue );


        sValue->mType = DBM_PARSE_TYPE_UNUM;
        sValue->mValue = sTmpVal;
    }
    else
    {
        sValue->mType = DBM_PARSE_TYPE_UNUM;
        sValue->mValue = aValue;
    }


    return sValue;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}



/**
 * @brief uInt type을 1개 생성
 */
dbmParseValue  * dbmMakeIntValue( dbmParserContext     * aCtx,
                                  dbmBool                aIsMinus,
                                  dbmChar              * aValue )
{
    dbmParseValue    * sValue = NULL;
    dbmChar          * sTmpVal = NULL;
    dbmInt32           sSize  = 0;


    /**
     * ParseValue 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseValue),
                                   (void **)&sValue,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sValue, 0x00, sizeof(dbmParseValue) );


    if( aIsMinus == DBM_TRUE )
    {
        sSize = dbmStrlen(aValue) + 1;
        DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                       (sSize + 1),
                                       (void **)&sTmpVal,
                                       aCtx->mErrorStack ) == DBM_SUCCESS,
                       RAMP_ERR_ALLOC_FAIL );

        dbmMemset( sTmpVal, 0x00, (sSize + 1) );
        dbmStrcpy( sTmpVal, "-" );
        dbmStrcat( sTmpVal, aValue );


        sValue->mType = DBM_PARSE_TYPE_UINT;
        sValue->mValue = sTmpVal;
    }
    else
    {
        sValue->mType = DBM_PARSE_TYPE_UINT;
        sValue->mValue = aValue;
    }


    return sValue;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief Column등으로 추정되는 Expr type을 1개 생성
 */
dbmParseValue  * dbmMakeIdentifier( dbmParserContext     * aCtx,
                                    dbmChar              * aValue )
{
    dbmParseValue    * sValue = NULL;


    /**
     * ParseValue 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseValue),
                                   (void **)&sValue,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sValue, 0x00, sizeof(dbmParseValue) );


    /**
     * ParseValue 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */
    sValue->mType = DBM_PARSE_TYPE_IDENTIFIER;
    sValue->mValue = aValue;
    sValue->mLineNo = aCtx->mLineNo;
    sValue->mColumn = aCtx->mColumn;
    sValue->mIsDoubleQuote = DBM_FALSE;

    return sValue;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Column등으로 추정되는 Expr type을 1개 생성
 */
dbmParseValue  * dbmMakeIdentifierDoubleQuote( dbmParserContext     * aCtx,
                                               dbmChar              * aValue )
{
    dbmParseValue    * sValue = NULL;


    /**
     * ParseValue 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseValue),
                                   (void **)&sValue,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sValue, 0x00, sizeof(dbmParseValue) );


    /**
     * ParseValue 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */
    sValue->mType = DBM_PARSE_TYPE_IDENTIFIER;
    sValue->mValue = aValue;
    sValue->mLineNo = aCtx->mLineNo;
    sValue->mColumn = aCtx->mColumn;
    sValue->mIsDoubleQuote = DBM_TRUE;

    return sValue;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}









/**
 * @brief identifier_list로 추정되는 Expr type을 1개 생성
 */
dbmParseValue  * dbmMakeIdentifierList( dbmParserContext     * aCtx,
                                        dbmList              * aList )
{
    dbmParseValue    * sValue = NULL;


    /**
     * ParseValue 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseValue),
                                   (void **)&sValue,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sValue, 0x00, sizeof(dbmParseValue) );


    /**
     * ParseValue 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sValue->mType = DBM_PARSE_TYPE_IDENTIFIER_LIST;
    sValue->mValue = (dbmChar *)aList;


    return sValue;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief string type을 1개 생성
 */
dbmParseValue  * dbmMakeStrValue( dbmParserContext     * aCtx,
                                  dbmChar              * aValue )
{
    dbmParseValue    * sValue = NULL;


    /**
     * ParseValue 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseValue),
                                   (void **)&sValue,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sValue, 0x00, sizeof(dbmParseValue) );


    /**
     * ParseValue 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sValue->mType = DBM_PARSE_TYPE_STRING;
    sValue->mValue = aValue;
    sValue->mLineNo = aCtx->mLineNo;
    sValue->mColumn = aCtx->mColumn;


    return sValue;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief Declare DataType에 의핸 1개 생성
 */
dbmParseDataTypeDef  * dbmMakeDataTypeDef( dbmParserContext     * aCtx,
                                           dbmParseDataType       aDataType,
                                           dbmInt32               aSize )
{
    dbmParseDataTypeDef    * sTypeDef = NULL;


    /**
     * Parse DataTypeDef 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDataTypeDef),
                                   (void **)&sTypeDef,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sTypeDef, 0x00, sizeof(dbmParseDataTypeDef) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sTypeDef->mType = DBM_PARSE_TYPE_DATA_TYPE_DEF;
    sTypeDef->mDataType = aDataType;
    sTypeDef->mSize = aSize;


    return sTypeDef;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Column Def에 의핸 1개 생성
 */
dbmParseColumnDef  * dbmMakeColumnDef( dbmParserContext     * aCtx,
                                       dbmParseValue        * aName,
                                       dbmParseDataTypeDef  * aDataTypeDef )
{
    dbmParseColumnDef    * sColumnDef = NULL;


    /**
     * Parse ColumnDef 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseColumnDef),
                                   (void **)&sColumnDef,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sColumnDef, 0x00, sizeof(dbmParseColumnDef) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sColumnDef->mType = DBM_PARSE_TYPE_COLUMN_DEF;
    sColumnDef->mName = aName;
    sColumnDef->mDataTypeDef = aDataTypeDef;


    return sColumnDef;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief Key Column Info을 1개 생성
 */
dbmParseKeyColumnDef  * dbmMakeKeyColumnDef( dbmParserContext     * aCtx,
                                             dbmParseFunctionType   aFuncType,
                                             dbmParseValue        * aName,
                                             dbmParseValue        * aValue,
                                             dbmParseValue        * aMaxSize,
                                             void                 * aIsAsc )
{
    dbmParseKeyColumnDef    * sColumnDef = NULL;


    /**
     * ParseKeyColumnDef 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseKeyColumnDef),
                                   (void **)&sColumnDef,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sColumnDef, 0x00, sizeof(dbmParseKeyColumnDef) );


    /**
     * ParseKeyColumn 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sColumnDef->mType = DBM_PARSE_TYPE_KEY_COLUMN_DEF;
    sColumnDef->mFuncType = aFuncType;
    sColumnDef->mName = aName;
    sColumnDef->mValue = aValue;
    sColumnDef->mMaxSize = aMaxSize;

    if( aIsAsc == NULL )
    {
        sColumnDef->mIsAsc = DBM_TRUE;
    }
    else
    {
        sColumnDef->mIsAsc = DBM_FALSE;
    }

    return sColumnDef;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}



/**
 * @brief Parse UDT Function Def에 의핸 1개 생성
 */
dbmParseUserLibraryFunction  * dbmMakeParseUserLibFunction( dbmParserContext     * aCtx,
                                                            dbmList              * aFuncName,
                                                            dbmList              * aArgs )
{
    dbmParseUserLibraryFunction    * sFunc = NULL;


    /**
     * Parse User Library Function 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseUserLibraryFunction),
                                   (void **)&sFunc,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sFunc, 0x00, sizeof(dbmParseUserLibraryFunction) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sFunc->mType = DBM_PARSE_TYPE_USER_LIBRARY_FUNCTION;
    sFunc->mFuncName = aFuncName;
    sFunc->mArgs = aArgs;


    return sFunc;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}









/**
 * @brief Parse Function Def에 의핸 1개 생성
 */
dbmParseFunction  * dbmMakeParseFunction( dbmParserContext     * aCtx,
                                          dbmParseFunctionType   aFuncType,
                                          void                 * aLeftArg,
                                          void                 * aRightArg,
                                          void                 * aAdditionalArg1,
                                          void                 * aAdditionalArg2 )
{
    dbmParseFunction    * sFunc = NULL;


    /**
     * Parse Function 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseFunction),
                                   (void **)&sFunc,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sFunc, 0x00, sizeof(dbmParseFunction) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sFunc->mType = DBM_PARSE_TYPE_FUNCTION;
    sFunc->mFuncType = aFuncType;
    sFunc->mLeftArg = aLeftArg;
    sFunc->mRightArg = aRightArg;
    sFunc->mAdditionalArg1 = aAdditionalArg1;
    sFunc->mAdditionalArg2 = aAdditionalArg2;


    return sFunc;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief Parse Expr에 의핸 1개 생성
 */
dbmParseBindParam  * dbmMakeBindParam( dbmParserContext     * aCtx,
                                       dbmChar              * aVarName )
{
    dbmParseBindParam      * sBindParam = NULL;


    /**
     * ParamList를 구한다.
     */
 
    if( aCtx->mBindParamList == NULL )
    {
        DBM_TRY_THROW( dbmCreateList( aCtx->mAllocator,
                                      & aCtx->mBindParamList,
                                      aCtx->mErrorStack ) == DBM_SUCCESS,
                       RAMP_ERR_ALLOC_FAIL );
    }


    /**
     * Parse Expr 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseBindParam),
                                   (void **)&sBindParam,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sBindParam, 0x00, sizeof(dbmParseBindParam) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sBindParam->mType = DBM_PARSE_TYPE_BIND_PARAM;
    sBindParam->mVarName = aVarName;
    sBindParam->mBindId = (aCtx->mBindCount + 1);


    DBM_TRY_THROW( dbmAddList( aCtx->mAllocator,
                               aCtx->mBindParamList,
                               DBM_LIST_ELEM_POINTER,
                               sBindParam,
                               aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    aCtx->mBindCount ++;

    return sBindParam;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Parse Expr에 의핸 1개 생성
 */
dbmParseExpr  * dbmMakeParseExpr( dbmParserContext     * aCtx,
                                  dbmParseExprType       aExprType,
                                  void                 * aOrgExpr )
{
    dbmParseExpr    * sExpr = NULL;


    /**
     * Parse Expr 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseExpr),
                                   (void **)&sExpr,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sExpr, 0x00, sizeof(dbmParseExpr) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sExpr->mType = DBM_PARSE_TYPE_EXPR;
    sExpr->mExprType = aExprType;
    sExpr->mOrgExpr = aOrgExpr;


    return sExpr;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Update Set 1개 생성
 */
dbmParseUpdateSetItem  * dbmMakeUpdateSetItem( dbmParserContext     * aCtx,
                                               dbmBool                aIsJson,
                                               void                 * aTargetColumn,
                                               dbmParseExpr         * aValueExpr )
{
    dbmParseUpdateSetItem    * sUpdateSet = NULL;


    /**
     * Parse Update Set 1개 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseUpdateSetItem),
                                   (void **)&sUpdateSet,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sUpdateSet, 0x00, sizeof(dbmParseUpdateSetItem) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sUpdateSet->mType = DBM_PARSE_TYPE_UPDATE_SET_ITEM;
    sUpdateSet->mIsTargetJson = aIsJson;
    sUpdateSet->mTargetColumn = aTargetColumn;
    sUpdateSet->mValueExpr = aValueExpr;


    return sUpdateSet;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief Table Source 1개 생성
 */
dbmParseTableSource  * dbmMakeTableSource( dbmParserContext     * aCtx,
                                           dbmParseValue        * aTableName,
                                           dbmParseValue        * aAlias )
{
    dbmParseTableSource    * sTableSource = NULL;


    /**
     * Parse Update Set 1개 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseTableSource),
                                   (void **)&sTableSource,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sTableSource, 0x00, sizeof(dbmParseTableSource) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sTableSource->mType = DBM_PARSE_TYPE_TABLE_SOURCE;
    sTableSource->mTableName = aTableName;
    sTableSource->mAlias = aAlias;


    return sTableSource;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}



                                        



/**
 * @brief create instance stmt 생성
 */
dbmParseCreateInstStmt  * dbmMakeCreateInstanceStmt( dbmParserContext     * aCtx,
                                                     dbmParseValue        * aName,
                                                     dbmParseValue        * aInitOption,
                                                     dbmParseValue        * aExtendOption,
                                                     dbmParseValue        * aMaxOption )
{
    dbmParseCreateInstStmt    * sStmt = NULL;


    /**
     * ParseCreateInstStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateInstStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateInstStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_INSTANCE_STMT;
    sStmt->mName = aName;
    sStmt->mInitOption = aInitOption;
    sStmt->mExtendOption = aExtendOption;
    sStmt->mMaxOption = aMaxOption;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}

 


/**
 * @brief create Queue stmt 생성
 */
dbmParseCreateQueueStmt  * dbmMakeCreateQueueStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aName,
                                                   dbmParseValue        * aMsgSize,
                                                   dbmParseValue        * aInitOption,
                                                   dbmParseValue        * aExtendOption,
                                                   dbmParseValue        * aMaxOption,
                                                   dbmBool                aIsDirect )
{
    dbmParseCreateQueueStmt    * sStmt = NULL;


    /**
     * ParseCreateQueueStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateQueueStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateQueueStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_QUEUE_STMT;
    sStmt->mName = aName;
    sStmt->mMsgSize = aMsgSize;
    sStmt->mInitOption = aInitOption;
    sStmt->mExtendOption = aExtendOption;
    sStmt->mMaxOption = aMaxOption;
    sStmt->mIsDirect = aIsDirect;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief create Table stmt 생성
 */
dbmParseCreateTableStmt  * dbmMakeCreateTableStmt( dbmParserContext     * aCtx,
                                                   dbmTableType           aTableType,
                                                   dbmParseValue        * aName,
                                                   void                 * aColumnListOrSize,
                                                   dbmParseValue        * aInitOption,
                                                   dbmParseValue        * aExtendOption,
                                                   dbmParseValue        * aMaxOption )
{
    dbmParseCreateTableStmt    * sStmt = NULL;


    /**
     * ParseCreateTableStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateTableStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateTableStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_TABLE_STMT;
    sStmt->mTableType = aTableType;
    sStmt->mName = aName;
    sStmt->mColumnListOrSize = aColumnListOrSize;
    sStmt->mInitOption = aInitOption;
    sStmt->mExtendOption = aExtendOption;
    sStmt->mMaxOption = aMaxOption;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief create Index stmt 생성
 */
dbmParseCreateIndexStmt  * dbmMakeCreateIndexStmt( dbmParserContext     * aCtx,
                                                   dbmBool                aIsUnique,
                                                   dbmParseValue        * aIndexName,
                                                   dbmParseValue        * aTableName,
                                                   dbmList              * aKeyList )
{
    dbmParseCreateIndexStmt    * sStmt = NULL;


    /**
     * ParseCreateIndexStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateIndexStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateIndexStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_INDEX_STMT;
    sStmt->mIsUnique = aIsUnique;
    sStmt->mIndexName = aIndexName;
    sStmt->mTableName = aTableName;
    sStmt->mKeyList = aKeyList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief create library object stmt
 */
dbmParseCreateLibraryStmt  * dbmMakeCreateLibraryStmt( dbmParserContext     * aCtx,
                                                       dbmBool                aIsSyncLib,
                                                       dbmParseValue        * aObjectName,
                                                       dbmParseValue        * aDllName,
                                                       dbmParseLibraryItem  * aInitFunc,
                                                       dbmParseLibraryItem  * aFiniFunc,
                                                       dbmList              * aFuncList )
{
    dbmParseCreateLibraryStmt    * sStmt = NULL;


    /**
     * ParseCreateLibrary 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateLibraryStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateLibraryStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_LIBRARY_STMT;
    sStmt->mIsSyncLib = aIsSyncLib;
    sStmt->mObjectName = aObjectName;
    sStmt->mDllName = aDllName;
    sStmt->mInitFunc = aInitFunc;
    sStmt->mFiniFunc = aFiniFunc;
    sStmt->mFuncList = aFuncList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief drop Instance  stmt 생성
 */
dbmParseDropInstStmt  * dbmMakeDropInstanceStmt( dbmParserContext     * aCtx,
                                                 dbmParseValue        * aInstName )
{
    dbmParseDropInstStmt    * sStmt = NULL;


    /**
     * ParseDropInstStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropInstStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropInstStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_INSTANCE_STMT;
    sStmt->mInstName = aInstName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief drop table stmt 생성
 */
dbmParseDropTableStmt  * dbmMakeDropTableStmt( dbmParserContext     * aCtx,
                                               dbmParseType           aParseType,
                                               dbmParseValue        * aTableName )
{
    dbmParseDropTableStmt    * sStmt = NULL;


    /**
     * ParseDropTableStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropTableStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropTableStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = aParseType;
    sStmt->mTableName = aTableName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief drop Sequence stmt 생성
 */
dbmParseDropSequenceStmt  * dbmMakeDropSequenceStmt( dbmParserContext     * aCtx,
                                                     dbmParseValue        * aSeqName )
{
    dbmParseDropSequenceStmt    * sStmt = NULL;


    /**
     * ParseDropSequenceStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropSequenceStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropSequenceStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_SEQUENCE_STMT;
    sStmt->mSeqName = aSeqName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief alter Sequence stmt 생성
 */
dbmParseAlterSequenceStmt  * dbmMakeAlterSequenceStmt( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aSeqName,
                                                       dbmParseValue        * aCurrVal )
{
    dbmParseAlterSequenceStmt    * sStmt = NULL;


    /**
     * ParseAlterSequenceStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterSequenceStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterSequenceStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_SEQUENCE_STMT;
    sStmt->mSeqName = aSeqName;
    sStmt->mCurrVal = aCurrVal;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief alter rename column tmt 생성
 */
dbmParseAlterTableRenameColumnStmt  * dbmMakeAlterTableRenameColumnStmt( dbmParserContext     * aCtx,
                                                                         dbmParseValue        * aTableName,
                                                                         dbmParseValue        * aOrgColumn,
                                                                         dbmParseValue        * aNewColumn )
{
    dbmParseAlterTableRenameColumnStmt    * sStmt = NULL;


    /**
     * dbmParseAlterTableRenameColumnStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterTableRenameColumnStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterTableRenameColumnStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_TABLE_RENAME_COLUMN_STMT;
    sStmt->mTableName = aTableName;
    sStmt->mOrgColumn = aOrgColumn;
    sStmt->mNewColumn = aNewColumn;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief alter compact table 생성
 */
dbmParseAlterTableCompactStmt  * dbmMakeAlterTableCompactStmt( dbmParserContext     * aCtx,
                                                               dbmParseValue        * aTableName )
{
    dbmParseAlterTableCompactStmt    * sStmt = NULL;


    /**
     * dbmParseAlterTableCompactStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterTableCompactStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterTableCompactStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_TABLE_COMPACT_STMT;
    sStmt->mTableName = aTableName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}











/**
 * @brief alter rebuild index stmt 생성
 */
dbmParseRebuildIndexStmt  * dbmMakeAlterRebuildIndexStmt( dbmParserContext     * aCtx,
                                                          dbmParseValue        * aTableName,
                                                          dbmParseValue        * aIndexName )
{
    dbmParseRebuildIndexStmt    * sStmt = NULL;


    /**
     * dbmParseRebuildIndexStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseRebuildIndexStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseRebuildIndexStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_REBUILD_INDEX_STMT;
    sStmt->mTableName = aTableName;
    sStmt->mIndexName = aIndexName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





 
/**
 * @brief drop index stmt 생성
 */
dbmParseDropIndexStmt  * dbmMakeDropIndexStmt( dbmParserContext     * aCtx,
                                               dbmParseValue        * aIndexName )
{
    dbmParseDropIndexStmt    * sStmt = NULL;


    /**
     * ParseDropIndexStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropIndexStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropIndexStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_INDEX_STMT;
    sStmt->mIndexName = aIndexName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief truncate stmt 생성
 */
dbmParseTruncateStmt  * dbmMakeTruncateStmt( dbmParserContext     * aCtx,
                                             dbmParseType           aParseType,
                                             dbmParseValue        * aTableName )
{
    dbmParseTruncateStmt    * sStmt = NULL;


    /**
     * ParseTruncateStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseTruncateStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseTruncateStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = aParseType;
    sStmt->mTableName = aTableName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Create Sequence stmt 생성
 */
dbmParseCreateSequenceStmt  * dbmMakeCreateSequenceStmt( dbmParserContext     * aCtx,
                                                         dbmParseValue        * aSeqName,
                                                         dbmParseValue        * aStartVal,
                                                         dbmParseValue        * aIncrementVal,
                                                         dbmParseValue        * aMaxVal,
                                                         dbmParseValue        * aMinVal,
                                                         dbmParseValue        * aIsCycle )
{
    dbmParseCreateSequenceStmt    * sStmt = NULL;


    /**
     * ParseTruncateStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateSequenceStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateSequenceStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_SEQUENCE_STMT;
    sStmt->mSeqName = aSeqName;
    sStmt->mStartVal = aStartVal;
    sStmt->mIncrementVal = aIncrementVal;
    sStmt->mMaxVal = aMaxVal;
    sStmt->mMinVal = aMinVal;
    sStmt->mIsCycle = aIsCycle;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief ayter replication sync
 */
dbmParseAlterReplSyncStmt  * dbmMakeAlterReplSyncStmt( dbmParserContext     * aCtx,
                                                       dbmReplActDef          aReplAct,
                                                       dbmList              * aTableList )
{
    dbmParseAlterReplSyncStmt    * sStmt = NULL;


    /**
     * dbmParseAlterReplSyncStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterReplSyncStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterReplSyncStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_REPL_SYNC_STMT;
    sStmt->mReplAct = aReplAct;
    sStmt->mTableList = aTableList;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief ayter replication add/drop table
 */
dbmParseAlterReplModStmt  * dbmMakeAlterReplModStmt( dbmParserContext     * aCtx,
                                                     dbmBool                aIsDrop,
                                                     dbmList              * aTableList )
{
    dbmParseAlterReplModStmt    * sStmt = NULL;


    /**
     * dbmParseAlterReplModStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterReplModStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterReplModStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_REPL_MOD_STMT;
    sStmt->mIsDrop = aIsDrop;
    sStmt->mTableList = aTableList;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}








/**
 * @brief ayter system reset perf
 */
dbmParseAlterResetPerfStmt  * dbmMakeAlterResetPerfStmt( dbmParserContext     * aCtx )
{
    dbmParseAlterResetPerfStmt    * sStmt = NULL;


    /**
     * dbmParseAlterResetPerfStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterResetPerfStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterResetPerfStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_RESET_PERF_STMT;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief ayter system instance active
 */
dbmParseAlterSystemInstanceStmt  * dbmMakeAlterSystemInstanceStmt( dbmParserContext     * aCtx,
                                                                   dbmBool                aIsActive )
{
    dbmParseAlterSystemInstanceStmt    * sStmt = NULL;


    /**
     * dbmParseAlterSystemInstance 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterSystemInstanceStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterSystemInstanceStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_SYSTEM_INSTANCE_ACTIVE_STMT;
    sStmt->mIsActive = aIsActive;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief ayter system reset checkpoint <fileno>
 */
dbmParseAlterSystemResetCkptFileStmt  * dbmMakeAlterSystemResetCkptFileStmt( dbmParserContext     * aCtx,
                                                                             dbmParseValue        * aInstName,
                                                                             dbmParseValue        * aFileNo )
{
    dbmParseAlterSystemResetCkptFileStmt   * sStmt = NULL;


    /**
     * dbmParseAlterSystemResetCkptFileStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterSystemResetCkptFileStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterSystemResetCkptFileStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_SYSTEM_RESET_CKPT_FILE_STMT;
    sStmt->mInstName = aInstName;
    sStmt->mFileNo = aFileNo;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





 


/**
 * @brief create replication 
 */
dbmParseCreateReplStmt  * dbmMakeCreateReplStmt( dbmParserContext     * aCtx,
                                                 dbmList              * aTableList )
{
    dbmParseCreateReplStmt    * sStmt = NULL;


    /**
     * dbmParseCreateReplStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateReplStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateReplStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_REPL_STMT;
    sStmt->mTableList = aTableList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief drop replication 
 */
dbmParseDropReplStmt  * dbmMakeDropReplStmt( dbmParserContext     * aCtx )
{
    dbmParseDropReplStmt    * sStmt = NULL;


    /**
     * dbmParseDropReplStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropReplStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropReplStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_REPL_STMT;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief create capture
 */
dbmParseCreateCaptureStmt  * dbmMakeCreateCaptureStmt( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aCaptureName,
                                                       dbmList              * aTableList )
{
    dbmParseCreateCaptureStmt    * sStmt = NULL;


    /**
     * dbmParseCreateCaptureStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateCaptureStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateCaptureStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_CAPTURE_STMT;
    sStmt->mCaptureName = aCaptureName;
    sStmt->mTableList = aTableList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief drop capture
 */
dbmParseDropCaptureStmt  * dbmMakeDropCaptureStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aCaptureName )

{
    dbmParseDropCaptureStmt    * sStmt = NULL;


    /**
     * dbmParseDropCaptureStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropCaptureStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropCaptureStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_CAPTURE_STMT;
    sStmt->mCaptureName = aCaptureName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}








/**
 * @brief insert stmt 생성
 */
dbmParseOraInsertStmt  * dbmMakeOraInsertStmt( dbmParserContext     * aCtx,
                                               dbmList              * aName,
                                               dbmList              * aColumnList,
                                               dbmList              * aValueList )
{
    dbmParseOraInsertStmt    * sStmt = NULL;


    /**
     * Parse InsertStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseOraInsertStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseOraInsertStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ORA_INSERT_STMT;
    sStmt->mNameList = aName;
    sStmt->mColumnList = aColumnList;
    sStmt->mValueList = aValueList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief insert stmt 생성
 */
dbmParseInsertStmt  * dbmMakeInsertStmt( dbmParserContext     * aCtx,
                                         dbmParseValue        * aName,
                                         dbmList              * aColumnList,
                                         dbmList              * aValueList,
                                         dbmParseValue        * aExpiredTime )
{
    dbmParseInsertStmt    * sStmt = NULL;


    /**
     * Parse InsertStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseInsertStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseInsertStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_INSERT_STMT;
    sStmt->mName = aName;
    sStmt->mColumnList = aColumnList;
    sStmt->mValueList = aValueList;
    sStmt->mExpiredTime = aExpiredTime;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}

 


/**
 * @brief update stmt 생성
 */
dbmParseOraUpdateStmt  * dbmMakeOraUpdateStmt( dbmParserContext     * aCtx,
                                               dbmParseType           aParseType,
                                               dbmList              * aName,
                                               dbmList              * aSetList,
                                               dbmParseExpr         * aWhereExpr )
{
    dbmParseOraUpdateStmt    * sStmt = NULL;


    /**
     * Parse UpdateStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseOraUpdateStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseOraUpdateStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ORA_UPDATE_STMT;
    sStmt->mNameList = aName;
    sStmt->mSetList = aSetList;
    sStmt->mWhereExpr = aWhereExpr;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief update stmt 생성
 */
dbmParseUpdateStmt  * dbmMakeUpdateStmt( dbmParserContext     * aCtx,
                                         dbmParseType           aParseType,
                                         dbmParseValue        * aName,
                                         dbmList              * aSetList,
                                         dbmParseExpr         * aWhereExpr )
{
    dbmParseUpdateStmt    * sStmt = NULL;


    /**
     * Parse UpdateStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseUpdateStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseUpdateStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = aParseType;
    sStmt->mName = aName;
    sStmt->mSetList = aSetList;
    sStmt->mWhereExpr = aWhereExpr;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief delete stmt 생성
 */
dbmParseOraDeleteStmt  * dbmMakeOraDeleteStmt( dbmParserContext     * aCtx,
                                               dbmList              * aName,
                                               dbmParseExpr         * aWhereExpr )
{
    dbmParseOraDeleteStmt    * sStmt = NULL;


    /**
     * Parse UpdateStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseOraDeleteStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseOraDeleteStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ORA_DELETE_STMT;
    sStmt->mNameList = aName;
    sStmt->mWhereExpr = aWhereExpr;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief delete stmt 생성
 */
dbmParseDeleteStmt  * dbmMakeDeleteStmt( dbmParserContext     * aCtx,
                                         dbmParseValue        * aName,
                                         dbmParseExpr         * aWhereExpr )
{
    dbmParseDeleteStmt    * sStmt = NULL;


    /**
     * Parse UpdateStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDeleteStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDeleteStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DELETE_STMT;
    sStmt->mName = aName;
    sStmt->mWhereExpr = aWhereExpr;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}


 


/**
 * @brief select stmt 생성
 */
dbmParseSelectStmt  * dbmMakeSelectStmt( dbmParserContext     * aCtx,
                                         dbmList              * aTargetList,
                                         dbmList              * aTableList,
                                         dbmParseExpr         * aWhereExpr,
                                         dbmList              * aGroupByList,
                                         dbmList              * aOrderByList,
                                         dbmParseValue        * aForUpdate,
                                         dbmParseLimit        * aLimit )
{
    dbmParseSelectStmt    * sStmt = NULL;


    /**
     * Parse SelectStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseSelectStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseSelectStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_SELECT_STMT;
    sStmt->mTargetList = aTargetList;
    sStmt->mTableList = aTableList;
    sStmt->mWhereExpr = aWhereExpr;
    sStmt->mGroupByList = aGroupByList;
    sStmt->mOrderByList = (aOrderByList != NULL ? aOrderByList : aGroupByList);
    if( aForUpdate != NULL )
    {
        sStmt->mIsForUpdate = DBM_TRUE;
    }
    sStmt->mLimit = aLimit;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief select into stmt 생성
 */
dbmParseSelectIntoStmt  * dbmMakeSelectIntoStmt( dbmParserContext     * aCtx,
                                                 dbmList              * aTargetList,
                                                 dbmList              * aIntoList,
                                                 dbmList              * aTableList,
                                                 dbmParseExpr         * aWhereExpr,
                                                 dbmList              * aGroupByList,
                                                 dbmParseValue        * aForUpdate )
{
    dbmParseSelectIntoStmt    * sStmt = NULL;


    /**
     * Parse SelectIntoStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseSelectIntoStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseSelectIntoStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_SELECT_INTO_STMT;
    sStmt->mTargetList = aTargetList;
    sStmt->mIntoList = aIntoList;
    sStmt->mTableList = aTableList;
    sStmt->mWhereExpr = aWhereExpr;
    sStmt->mGroupByList = aGroupByList;
    if( aForUpdate != NULL )
    {
        sStmt->mIsForUpdate = DBM_TRUE;
    }


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}


 

/**
 * @brief Enqueue stmt 생성
 */
dbmParseEnqueueStmt  * dbmMakeEnqueueStmt( dbmParserContext     * aCtx,
                                           dbmParseValue        * aName,
                                           dbmList              * aColumnList,
                                           dbmList              * aValueList )
{
    dbmParseEnqueueStmt    * sStmt = NULL;


    /**
     * Parse Enqueue Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseEnqueueStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseEnqueueStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ENQUEUE_STMT;
    sStmt->mName = aName;
    sStmt->mColumnList = aColumnList;
    sStmt->mValueList = aValueList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief Dequeue stmt 생성
 */
dbmParseDequeueStmt  * dbmMakeDequeueStmt( dbmParserContext     * aCtx,
                                           dbmParseValue        * aName,
                                           dbmParseExpr         * aWhereExpr,
                                           dbmParseValue        * aTimeOut )
{
    dbmParseDequeueStmt    * sStmt = NULL;


    /**
     * Parse Enqueue Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDequeueStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDequeueStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DEQUEUE_STMT;
    sStmt->mName = aName;
    sStmt->mWhereExpr = aWhereExpr;
    sStmt->mTimeOut = aTimeOut;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief load stmt 생성
 */
dbmParseLoadStmt  * dbmMakeLoadStmt( dbmParserContext     * aCtx,
                                     dbmParseValue        * aTargetTable,
                                     dbmList              * aTargetColList,
                                     dbmParseValue        * aQuery,
                                     dbmParseValue        * aSourceDSN,
                                     dbmParseValue        * aSourceUID,
                                     dbmParseValue        * aSourcePWD,
                                     dbmParseValue        * aExpiredTime )
{
    dbmParseLoadStmt    * sStmt = NULL;


    /**
     * Parse Load Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseLoadStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseLoadStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_LOAD_STMT;
    sStmt->mQuery = aQuery;
    sStmt->mSourceDSN = aSourceDSN;
    sStmt->mSourceUID = aSourceUID;
    sStmt->mSourcePWD = aSourcePWD;
    sStmt->mTargetTable = aTargetTable;
    sStmt->mTargetColList = aTargetColList;
    sStmt->mExpiredTime = aExpiredTime;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief sync stmt 생성
 */
dbmParseSyncStmt  * dbmMakeSyncStmt( dbmParserContext     * aCtx,
                                     dbmParseValue        * aTable,
                                     dbmList              * aColumnList,
                                     dbmParseValue        * aQuery,
                                     dbmParseValue        * aTargetDSN,
                                     dbmParseValue        * aTargetUID,
                                     dbmParseValue        * aTargetPWD )
{
    dbmParseSyncStmt    * sStmt = NULL;


    /**
     * Parse Sync Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseSyncStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseSyncStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_SYNC_STMT;
    sStmt->mTargetTable = aTable;
    sStmt->mColumnList = aColumnList;
    sStmt->mSourceQuery = aQuery;
    sStmt->mTargetDSN = aTargetDSN;
    sStmt->mTargetUID = aTargetUID;
    sStmt->mTargetPWD = aTargetPWD;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief ProcExec stmt 생성
 */
dbmParseExecProcStmt  * dbmMakeExecProcStmt( dbmParserContext     * aCtx,
                                             dbmParseValue        * aProcName,
                                             dbmList              * aParamList )
{
    dbmParseExecProcStmt    * sStmt = NULL;


    /**
     * Parse ExecProc Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseExecProcStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseExecProcStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_EXEC_PROC_STMT;
    sStmt->mProcName = aProcName;
    sStmt->mParamList = aParamList;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief ProcArgs 에 의핸 1개 생성
 */
dbmParseParamDef  * dbmMakeParamDef( dbmParserContext         * aCtx,
                                     dbmParseValue            * aName,
                                     dbmParseParamInOut       * aInOut,
                                     dbmParseProcDataTypeDef  * aDataTypeDef )
{
    dbmParseParamDef    * sParamDef = NULL;


    DBM_TRY_THROW( aInOut->mType == DBM_PARSE_TYPE_PARAM_INOUT, RAMP_ERR_PARSE_FAIL );


    /**
     * Parse ParamDef 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseParamDef),
                                   (void **)&sParamDef,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sParamDef, 0x00, sizeof(dbmParseParamDef) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sParamDef->mType = DBM_PARSE_TYPE_PARAM_DEF;
    sParamDef->mName = aName;
    sParamDef->mInOutType = aInOut->mInOut;
    sParamDef->mDataTypeDef = aDataTypeDef;


    return sParamDef;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_CATCH( RAMP_ERR_PARSE_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_PARSE,
                      NULL,
                      aCtx->mErrorStack,
                      aCtx->mLineNo,
                      aCtx->mColumn );
    }

 
    DBM_FINISH

    return NULL;
}






/**
 * @brief ProcDeclare 에 의핸 declare item 1개 생성
 */
dbmParseDeclareItem  * dbmMakeProcDeclareItem( dbmParserContext     * aCtx,
                                               dbmProcDeclareType     aDeclareType,
                                               void                 * aItem )
{
    dbmParseDeclareItem    * sDeclareItem = NULL;


    /**
     * Parse DeclareItem 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDeclareItem),
                                   (void **)&sDeclareItem,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sDeclareItem, 0x00, sizeof(dbmParseDeclareItem) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sDeclareItem->mType = DBM_PARSE_TYPE_DECLARE_ITEM;
    sDeclareItem->mLineNo = aCtx->mLineNo;
    sDeclareItem->mColumn = aCtx->mColumn;
    sDeclareItem->mDeclareType = aDeclareType;
    sDeclareItem->mItem = aItem;

    return sDeclareItem;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }


    DBM_FINISH

    return NULL;
}









/**
 * @brief ProcDeclare 에 의핸 1개 생성
 */
dbmParseDeclareVar  * dbmMakeProcDeclareVar( dbmParserContext         * aCtx,
                                             dbmParseValue            * aName,
                                             dbmParseProcDataTypeDef  * aDataTypeDef,
                                             dbmParseExpr             * aInitValue )
{
    dbmParseDeclareVar    * sDeclareVar = NULL;


    /**
     * Parse DeclareItem 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDeclareVar),
                                   (void **)&sDeclareVar,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sDeclareVar, 0x00, sizeof(dbmParseDeclareVar) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sDeclareVar->mType = DBM_PARSE_TYPE_DECLARE_ITEM;
    sDeclareVar->mName = aName;
    sDeclareVar->mDataTypeDef = aDataTypeDef;
    sDeclareVar->mInitValue = aInitValue;

    return sDeclareVar;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }


    DBM_FINISH

    return NULL;
}







/**
 * @brief ProcDeclare 에 의핸 Cursor 1개 생성
 */
dbmParseDeclareCursor  * dbmMakeProcDeclareCursor( dbmParserContext     * aCtx,
                                                   dbmProcDeclareType     aDeclareType,
                                                   dbmParseValue        * aName,
                                                   dbmList              * aParamList,
                                                   dbmParseSelectStmt   * aSelectStmt )
{
    dbmParseDeclareCursor    * sDeclareCursor = NULL;


    /**
     * Parse DeclareItem 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDeclareCursor),
                                   (void **)&sDeclareCursor,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sDeclareCursor, 0x00, sizeof(dbmParseDeclareCursor) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sDeclareCursor->mType = DBM_PARSE_TYPE_DECLARE_ITEM;
    sDeclareCursor->mDeclareType = aDeclareType;
    sDeclareCursor->mName = aName;
    sDeclareCursor->mParamList = aParamList;
    sDeclareCursor->mSelectStmt = aSelectStmt;

    return sDeclareCursor;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }


    DBM_FINISH

    return NULL;
}






/**
 * @brief ProcDeclare 에 의핸 Exception  1개 생성
 */
dbmParseDeclareException  * dbmMakeProcDeclareException( dbmParserContext     * aCtx,
                                                         dbmProcDeclareType     aDeclareType,
                                                         dbmParseValue        * aName,
                                                         dbmParseValue        * aErrorCode )
{
    dbmParseDeclareException   * sDeclareException = NULL;


    /**
     * Parse DeclareItem 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDeclareException),
                                   (void **)&sDeclareException,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sDeclareException, 0x00, sizeof(dbmParseDeclareException) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sDeclareException->mType = DBM_PARSE_TYPE_DECLARE_ITEM;
    sDeclareException->mDeclareType = aDeclareType;
    sDeclareException->mName = aName;
    sDeclareException->mErrorCode = aErrorCode;

    return sDeclareException;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }


    DBM_FINISH

    return NULL;
}







/**
 * @brief create procedure stmt
 */
dbmParseCreateProcStmt  * dbmMakeCreateProcStmt( dbmParserContext       * aCtx,
                                                 dbmParseValue          * aName,
                                                 dbmList                * aParamList,
                                                 dbmParseProcBlockStmt  * aBlockStmt,
                                                 dbmBool                  aIsReplace )
{
    dbmParseCreateProcStmt    * sCreateProcStmt = NULL;


    /**
     * Parse create procedure 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateProcStmt),
                                   (void **)&sCreateProcStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sCreateProcStmt, 0x00, sizeof(dbmParseCreateProcStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sCreateProcStmt->mType = DBM_PARSE_TYPE_CREATE_PROCEDURE_STMT;
    sCreateProcStmt->mName = aName;
    sCreateProcStmt->mParamList = aParamList;
    sCreateProcStmt->mBlockStmt = aBlockStmt;
    sCreateProcStmt->mIsReplace = aIsReplace;

    return sCreateProcStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief procedure block stmt
 */
dbmParseProcBlockStmt  * dbmMakeProcBlockStmt( dbmParserContext     * aCtx,
                                               dbmList              * aDeclareList,
                                               dbmList              * aStmtList,
                                               dbmList              * aExceptionList )
{
    dbmParseProcBlockStmt    * sProcBlockStmt = NULL;


    /**
     * Parse procedure Block 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcBlockStmt),
                                   (void **)&sProcBlockStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sProcBlockStmt, 0x00, sizeof(dbmParseProcBlockStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sProcBlockStmt->mType = DBM_PARSE_TYPE_PROC_BLOCK_STMT;
    sProcBlockStmt->mLineNo = aCtx->mLineNo;
    sProcBlockStmt->mColumn = aCtx->mColumn;
    sProcBlockStmt->mDeclareList = aDeclareList;
    sProcBlockStmt->mStmtList = aStmtList;
    sProcBlockStmt->mExceptionList = aExceptionList;


    return sProcBlockStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief procedure stmt
 */
dbmParseProcStmt  * dbmMakeProcStmt( dbmParserContext     * aCtx,
                                     dbmProcStmtType        aStmtType,
                                     dbmParseValue        * aLabelName,
                                     void                 * aStmt )
{
    dbmParseProcStmt    * sProcStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcStmt),
                                   (void **)&sProcStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sProcStmt, 0x00, sizeof(dbmParseProcStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sProcStmt->mType = DBM_PARSE_TYPE_PROC_STMT;
    sProcStmt->mCommon.mStmtType = aStmtType;
    sProcStmt->mCommon.mLineNo = aCtx->mLineNo;
    sProcStmt->mCommon.mColumn = aCtx->mColumn;
    sProcStmt->mCommon.mLabelName = aLabelName;
    sProcStmt->mStmt = aStmt;


    return sProcStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief procedure assign stmt
 */
dbmParseProcAssignStmt  * dbmMakeProcAssignStmt( dbmParserContext     * aCtx,
                                                 dbmList              * aNameList,
                                                 dbmParseExpr         * aValueExpr )
{
    dbmParseProcAssignStmt    * sAssignStmt = NULL;


    /**
     * Parse procedure Assign Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcAssignStmt),
                                   (void **)&sAssignStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sAssignStmt, 0x00, sizeof(dbmParseProcAssignStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sAssignStmt->mNameList = aNameList;
    sAssignStmt->mValueExpr = aValueExpr;


    return sAssignStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief procedure PutLine stmt
 */
dbmParseProcPutLineStmt  * dbmMakeProcPutLineStmt( dbmParserContext     * aCtx,
                                                   dbmParseExpr         * aValueExpr )
{
    dbmParseProcPutLineStmt    * sPutLineStmt = NULL;


    /**
     * Parse procedure PutLine Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcPutLineStmt),
                                   (void **)&sPutLineStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sPutLineStmt, 0x00, sizeof(dbmParseProcPutLineStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sPutLineStmt->mValueExpr = aValueExpr;


    return sPutLineStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief procedure exception item
 */
dbmParseProcExceptionItem  * dbmMakeProcExceptionItem( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aName,
                                                       dbmList              * aStmtList )
{
    dbmParseProcExceptionItem   * sException = NULL;


    /**
     * Parse procedure Exception Item 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcExceptionItem),
                                   (void **)&sException,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sException, 0x00, sizeof(dbmParseProcExceptionItem) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */


    sException->mName = aName;
    sException->mStmtList = aStmtList;
    sException->mLineNo = aCtx->mLineNo;
    sException->mColumn = aCtx->mColumn;


    return sException;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief procedure if item
 */
dbmParseProcIfItem  * dbmMakeProcIfItem( dbmParserContext     * aCtx,
                                         dbmParseExpr         * aCondExpr,
                                         dbmList              * aStmtList )
{
    dbmParseProcIfItem    * sIfItem = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcIfItem),
                                   (void **)&sIfItem,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sIfItem, 0x00, sizeof(dbmParseProcIfItem) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sIfItem->mCondExpr = aCondExpr;
    sIfItem->mStmtList = aStmtList;


    return sIfItem;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief procedure if stmt
 */
dbmParseProcIfStmt  * dbmMakeProcIfStmt( dbmParserContext     * aCtx,
                                         dbmParseProcIfItem   * aFirstIf,
                                         dbmList              * aElseList,
                                         dbmParseProcIfItem   * aLast )
{
    dbmParseProcIfStmt    * sIfStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcIfStmt),
                                   (void **)&sIfStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sIfStmt, 0x00, sizeof(dbmParseProcIfStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sIfStmt->mFirstIf = aFirstIf;
    sIfStmt->mElseList = aElseList;
    sIfStmt->mLast = aLast;


    return sIfStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}



/**
 * @brief procedure exit stmt
 */
dbmParseProcExitStmt  * dbmMakeProcExitStmt( dbmParserContext     * aCtx,
                                             dbmParseExpr         * aCondExpr )
{
    dbmParseProcExitStmt    * sExitStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcExitStmt),
                                   (void **)&sExitStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sExitStmt, 0x00, sizeof(dbmParseProcExitStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sExitStmt->mCondExpr = aCondExpr;


    return sExitStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief procedure continue stmt
 */
dbmParseProcContinueStmt  * dbmMakeProcContinueStmt( dbmParserContext     * aCtx,
                                                     dbmParseExpr         * aCondExpr )
{
    dbmParseProcContinueStmt    * sContinueStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcContinueStmt),
                                   (void **)&sContinueStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sContinueStmt, 0x00, sizeof(dbmParseProcContinueStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sContinueStmt->mCondExpr = aCondExpr;


    return sContinueStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}







/**
 * @brief procedure loop stmt
 */
dbmParseProcLoopStmt  * dbmMakeProcLoopStmt( dbmParserContext     * aCtx,
                                             dbmList              * aStmtList )
{
    dbmParseProcLoopStmt    * sLoopStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcLoopStmt),
                                   (void **)&sLoopStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sLoopStmt, 0x00, sizeof(dbmParseProcLoopStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sLoopStmt->mStmtList = aStmtList;


    return sLoopStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief procedure simpleCase stmt
 */
dbmParseProcSimpleCaseStmt  * dbmMakeProcSimpleCaseStmt( dbmParserContext     * aCtx,
                                                         dbmParseExpr         * aValueExpr,
                                                         dbmList              * aCondList,
                                                         dbmParseProcIfItem   * aElse )
{
    dbmParseProcSimpleCaseStmt    * sSimpleCaseStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcSimpleCaseStmt),
                                   (void **)&sSimpleCaseStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sSimpleCaseStmt, 0x00, sizeof(dbmParseProcSimpleCaseStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sSimpleCaseStmt->mValueExpr = aValueExpr;
    sSimpleCaseStmt->mCondList = aCondList;
    sSimpleCaseStmt->mElse = aElse;


    return sSimpleCaseStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief procedure searchedCase stmt
 */
dbmParseProcSearchedCaseStmt  * dbmMakeProcSearchedCaseStmt( dbmParserContext     * aCtx,
                                                             dbmList              * aCondList,
                                                             dbmParseProcIfItem   * aElse )
{
    dbmParseProcSearchedCaseStmt    * sSearchCaseStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcSearchedCaseStmt),
                                   (void **)&sSearchCaseStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sSearchCaseStmt, 0x00, sizeof(dbmParseProcSearchedCaseStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sSearchCaseStmt->mCondList = aCondList;
    sSearchCaseStmt->mElse = aElse;


    return sSearchCaseStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief procedure for loop stmt
 */
dbmParseProcForLoopStmt  * dbmMakeProcForLoopStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aName,
                                                   dbmBool                aIsReverse,
                                                   dbmParseExpr         * aFirstExpr,
                                                   dbmParseExpr         * aLastExpr,
                                                   dbmList              * aStmtList )
{
    dbmParseProcForLoopStmt    * sForLoopStmt = NULL;
    dbmParseDeclareVar         * sDeclareVar = NULL;
    dbmParseDataTypeDef        * sDataTypeDef = NULL;
    dbmParseProcDataTypeDef    * sDeclareTypeDef = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcForLoopStmt),
                                   (void **)&sForLoopStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sForLoopStmt, 0x00, sizeof(dbmParseProcForLoopStmt) );



    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcDataTypeDef),
                                   (void **)&sDeclareTypeDef,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sDeclareTypeDef, 0x00, sizeof(dbmParseProcDataTypeDef) );


    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDataTypeDef),
                                   (void **)&sDataTypeDef,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    sDataTypeDef->mDataType = DBM_DATA_TYPE_LONG;
    sDataTypeDef->mSize = sizeof(dbmInt64);
    sDataTypeDef->mType = DBM_PARSE_TYPE_DATA_TYPE_DEF;


    sDeclareTypeDef->mType = DBM_PARSE_TYPE_PROC_DATA_TYPE_DEF;
    sDeclareTypeDef->mDeclareType = DBM_PROC_VAR_TYPE_SCALAR;
    sDeclareTypeDef->mDeclareDef = sDataTypeDef;

    sDeclareVar = dbmMakeProcDeclareVar( aCtx,
                                         aName,
                                         sDeclareTypeDef,
                                         NULL );



    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sForLoopStmt->mParseName = sDeclareVar;
    sForLoopStmt->mIsReverse = aIsReverse;
    sForLoopStmt->mFirstExpr = aFirstExpr;
    sForLoopStmt->mLastExpr = aLastExpr;
    sForLoopStmt->mStmtList = aStmtList;


    return sForLoopStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief While Loop
 */
dbmParseProcWhileLoopStmt  * dbmMakeProcWhileLoopStmt( dbmParserContext     * aCtx,
                                                       dbmParseExpr         * aCondExpr,
                                                       dbmList              * aStmtList )
{
    dbmParseProcWhileLoopStmt    * sWhileLoopStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcWhileLoopStmt),
                                   (void **)&sWhileLoopStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sWhileLoopStmt, 0x00, sizeof(dbmParseProcWhileLoopStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sWhileLoopStmt->mCondExpr = aCondExpr;
    sWhileLoopStmt->mStmtList = aStmtList;


    return sWhileLoopStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief Goto Loop
 */
dbmParseProcGotoStmt  * dbmMakeProcGotoStmt( dbmParserContext     * aCtx,
                                             dbmParseValue        * aName )
{
    dbmParseProcGotoStmt    * sGotoStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcGotoStmt),
                                   (void **)&sGotoStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sGotoStmt, 0x00, sizeof(dbmParseProcGotoStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sGotoStmt->mName = aName;


    return sGotoStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief OpenCursor
 */
dbmParseProcOpenCursorStmt  * dbmMakeProcOpenCursorStmt( dbmParserContext     * aCtx,
                                                         dbmParseValue        * aName,
                                                         dbmList              * aParamList )
{
    dbmParseProcOpenCursorStmt    * sOpenCursorStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcOpenCursorStmt),
                                   (void **)&sOpenCursorStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sOpenCursorStmt, 0x00, sizeof(dbmParseProcOpenCursorStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sOpenCursorStmt->mName = aName;
    sOpenCursorStmt->mParamList = aParamList;


    return sOpenCursorStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief FetchCursor
 */
dbmParseProcFetchCursorStmt  * dbmMakeProcFetchCursorStmt( dbmParserContext     * aCtx,
                                                           dbmParseValue        * aName,
                                                           dbmList              * aIntoList )
{
    dbmParseProcFetchCursorStmt    * sFetchCursorStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcFetchCursorStmt),
                                   (void **)&sFetchCursorStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sFetchCursorStmt, 0x00, sizeof(dbmParseProcFetchCursorStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sFetchCursorStmt->mName = aName;
    sFetchCursorStmt->mIntoList = aIntoList;


    return sFetchCursorStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief CloseCursor
 */
dbmParseProcCloseCursorStmt  * dbmMakeProcCloseCursorStmt( dbmParserContext     * aCtx,
                                                           dbmParseValue        * aName )
{
    dbmParseProcCloseCursorStmt    * sCloseCursorStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcCloseCursorStmt),
                                   (void **)&sCloseCursorStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sCloseCursorStmt, 0x00, sizeof(dbmParseProcCloseCursorStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sCloseCursorStmt->mName = aName;


    return sCloseCursorStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief Raise
 */
dbmParseProcRaiseStmt  * dbmMakeProcRaiseStmt( dbmParserContext     * aCtx,
                                               dbmParseValue        * aName,
                                               dbmParseValue        * aErrorCode,
                                               dbmParseValue        * aErrorMsg )
{
    dbmParseProcRaiseStmt    * sRaiseStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcRaiseStmt),
                                   (void **)&sRaiseStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sRaiseStmt, 0x00, sizeof(dbmParseProcRaiseStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sRaiseStmt->mName = aName;
    sRaiseStmt->mErrorCode = aErrorCode;
    sRaiseStmt->mErrorMsg = aErrorMsg;


    return sRaiseStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Call Proc
 */
dbmParseProcCallProcStmt  * dbmMakeProcCallProcStmt( dbmParserContext     * aCtx,
                                                     dbmParseValue        * aName,
                                                     dbmList              * aArgList )
{
    dbmParseProcCallProcStmt    * sCallProcStmt = NULL;


    /**
     * Parse procedure Stmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcCallProcStmt),
                                   (void **)&sCallProcStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sCallProcStmt, 0x00, sizeof(dbmParseProcCallProcStmt) );


    /**
     * Parse 설정
     * 각 항목들의 메모리는 새로운 공간에 저장하자
     */

    sCallProcStmt->mName = aName;
    sCallProcStmt->mArgList = aArgList;


    return sCallProcStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief drop Procedure  stmt 생성
 */
dbmParseDropProcStmt  * dbmMakeDropProcedureStmt( dbmParserContext     * aCtx,
                                                  dbmParseValue        * aProcName )
{
    dbmParseDropProcStmt    * sStmt = NULL;


    /**
     * ParseDropProcStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropProcStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropProcStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_PROCEDURE_STMT;
    sStmt->mProcName = aProcName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief Param InOut 생성
 */
dbmParseParamInOut  * dbmMakeParamInOut( dbmParserContext     * aCtx,
                                         dbmParamInOutType      aInOut )
{
    dbmParseParamInOut   * sStmt = NULL;


    /**
     * ParseParamInOut 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseParamInOut),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseParamInOut) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_PARAM_INOUT;
    sStmt->mInOut = aInOut;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief Proc DataTypeDef 생성
 */
dbmParseProcDataTypeDef  * dbmMakeProcDataTypeDef( dbmParserContext     * aCtx,
                                                   dbmProcDeclareType     aDeclareType,
                                                   void                 * aDeclareDef )
{
    dbmParseProcDataTypeDef   * sStmt = NULL;


    /**
     * ParseProcDataTypeDef 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseProcDataTypeDef),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseProcDataTypeDef) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_PROC_DATA_TYPE_DEF;
    sStmt->mDeclareType = aDeclareType;
    sStmt->mDeclareDef = aDeclareDef;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief drop library stmt 생성
 */
dbmParseDropLibraryStmt  * dbmMakeDropLibraryStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aSvcName )
{
    dbmParseDropLibraryStmt    * sStmt = NULL;


    /**
     * ParseDropLibraryStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropLibraryStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropLibraryStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_LIBRARY_STMT;
    sStmt->mSvcName = aSvcName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}



/**
 * @brief create gsb server group
 */
dbmParseCreateGsbNodeStmt * dbmMakeCreateGsbNodeStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName,
                                        dbmParseValue        * aHostPort,
                                        dbmParseValue        * aClientMax,
                                        dbmParseValue        * aProcessMax )
{
    dbmParseCreateGsbNodeStmt    * sStmt = NULL;

    /**
     * dbmParseCreateGsbNodeStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateGsbNodeStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateGsbNodeStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_GSB_NODE;
    sStmt->mName = aName;
    sStmt->mHostPort = aHostPort;
    sStmt->mClientMax = aClientMax;
    sStmt->mProcessMax = aProcessMax;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief drop gsb server group
 */
dbmParseDropGsbNodeStmt * dbmMakeDropGsbNodeStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName )
{
    dbmParseDropGsbNodeStmt    * sStmt = NULL;

    /**
     * dbmParseDropGsbNodeStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropGsbNodeStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropGsbNodeStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_GSB_NODE;
    sStmt->mName = aName;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}


dbmParseCreateGsbMonitorStmt * dbmMakeCreateGsbMonitorStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName,
                                dbmParseValue        * aNodeName,
                                dbmParseValue        * aInfluxIp,
                                dbmParseValue        * aInfluxPort,
                                dbmParseValue        * aInfluxDb )
{
    dbmParseCreateGsbMonitorStmt    * sStmt = NULL;

    /**
     * dbmParseCreateGsbMonitorStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateGsbMonitorStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateGsbMonitorStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_GSB_MONITOR;
    sStmt->mName = aName;
    sStmt->mNodeName = aNodeName;
    sStmt->mInfluxIp = aInfluxIp;
    sStmt->mInfluxPort = aInfluxPort;
    sStmt->mInfluxDb = aInfluxDb;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}


dbmParseDropGsbMonitorStmt * dbmMakeDropGsbMonitorStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName )
{
    dbmParseDropGsbMonitorStmt    * sStmt = NULL;

    /**
     * dbmParseDropGsbMonitorStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropGsbMonitorStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropGsbMonitorStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_GSB_MONITOR;
    sStmt->mName = aName;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief create gsb server group
 */
dbmParseCreateGsbSvrGrpStmt * dbmMakeCreateGsbSvrGrpStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName,
                                        dbmParseValue        * aNodeName )
{
    dbmParseCreateGsbSvrGrpStmt    * sStmt = NULL;

    /**
     * dbmParseCreateGsbSvrGrpStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateGsbSvrGrpStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateGsbSvrGrpStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_GSB_SVR_GRP;
    sStmt->mName = aName;
    sStmt->mNodeName = aNodeName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief drop gsb server group
 */
dbmParseDropGsbSvrGrpStmt * dbmMakeDropGsbSvrGrpStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName )
{
    dbmParseDropGsbSvrGrpStmt    * sStmt = NULL;

    /**
     * dbmParseDropGsbSvrGrpStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropGsbSvrGrpStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropGsbSvrGrpStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_GSB_SVR_GRP;
    sStmt->mName = aName;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}


/**
 * @brief create gsb server
 */
dbmParseCreateGsbSvrStmt * dbmMakeCreateGsbSvrStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName,
                                        dbmParseValue        * aSvrGrpName,
                                        dbmParseValue        * aProcessMin,
                                        dbmParseValue        * aProcessCnt,
                                        dbmParseValue        * aProcessMax,
                                        dbmParseValue        * aQSize )
{
    dbmParseCreateGsbSvrStmt    * sStmt = NULL;

    /**
     * dbmParseCreateGsbSvrStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateGsbSvrStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateGsbSvrStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_GSB_SVR;
    sStmt->mName = aName;
    sStmt->mSvrGrpName = aSvrGrpName;
    sStmt->mProcessMin = aProcessMin;
    sStmt->mProcessCnt = aProcessCnt;
    sStmt->mProcessMax = aProcessMax;
    sStmt->mQSize = aQSize;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief drop gsb server
 */
dbmParseDropGsbSvrStmt * dbmMakeDropGsbSvrStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName )
{
    dbmParseDropGsbSvrStmt    * sStmt = NULL;

    /**
     * dbmParseDropGsbSvrStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropGsbSvrStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropGsbSvrStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_GSB_SVR;
    sStmt->mName = aName;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief create gsb service
 */
dbmParseCreateGsbSvcStmt * dbmMakeCreateGsbSvcStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName,
                                        dbmParseValue        * aSvrName,
                                        dbmParseValue        * aLibrary,
                                        dbmParseValue        * aFunction )
{
    dbmParseCreateGsbSvcStmt    * sStmt = NULL;

    /**
     * dbmParseCreateGsbSvcStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseCreateGsbSvcStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseCreateGsbSvcStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_CREATE_GSB_SVC;
    sStmt->mName = aName;
    sStmt->mSvrName = aSvrName;
    sStmt->mLibrary = aLibrary;
    sStmt->mFunction = aFunction;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief drop gsb service
 */
dbmParseDropGsbSvcStmt * dbmMakeDropGsbSvcStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aName )
{
    dbmParseDropGsbSvcStmt    * sStmt = NULL;

    /**
     * dbmParseDropGsbSvcStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDropGsbSvcStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDropGsbSvcStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DROP_GSB_SVC;
    sStmt->mName = aName;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}


/**
 * @brief alter process count
 */
dbmParseAlterGsbProcCntStmt * dbmMakeAlterGsbProcCntStmt( 
                                        dbmParserContext     * aCtx,
                                        dbmParseValue        * aSvrName,
                                        dbmParseValue        * aProcessCnt )
{
    dbmParseAlterGsbProcCntStmt    * sStmt = NULL;

    /**
     * dbmParseAlterGsbProcCntStmt 할당
     */
    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterGsbProcCntStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterGsbProcCntStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_GSB_PROC_CNT;
    sStmt->mSvrName = aSvrName;
    sStmt->mProcessCnt = aProcessCnt;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}






/**
 * @brief Decode Item
 */
dbmParseDecodeItem * dbmMakeParseDecodeItem( dbmParserContext     * aCtx,
                                             dbmParseExpr         * aCondExpr,
                                             dbmParseExpr         * aValueExpr )
{
    dbmParseDecodeItem    * sStmt = NULL;


    /**
     * dbmParseDecodeItem 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDecodeItem),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDecodeItem) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_DECODE_ITEM;
    sStmt->mCondExpr = aCondExpr;
    sStmt->mValueExpr = aValueExpr;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief create dcl stmt 생성
 */
dbmParseDCLStmt  * dbmMakeCreateDCLStmt( dbmParserContext     * aCtx,
                                         dbmBool                aIsCommit )
{
    dbmParseDCLStmt    * sStmt = NULL;


    /**
     * ParseDCLStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseDCLStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseDCLStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = aIsCommit == DBM_TRUE ? DBM_PARSE_TYPE_COMMIT : DBM_PARSE_TYPE_ROLLBACK;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief alter session terminate
 */
dbmParseSessionTermStmt  * dbmMakeAlterTermSessionStmt( dbmParserContext     * aCtx,
                                                        dbmParseValue        * aSessionId )
{
    dbmParseSessionTermStmt    * sStmt = NULL;


    /**
     * dbmParseSessionTermStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseSessionTermStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseSessionTermStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_SESSION_TERM_STMT;
    sStmt->mSessionId = aSessionId;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}

 




 


/**
 * @brief alter system aging
 */
dbmParseAgingStmt  * dbmMakeAlterAgingStmt( dbmParserContext     * aCtx,
                                            dbmList              * aTableList )
{
    dbmParseAgingStmt    * sStmt = NULL;


    /**
     * ParseAgingStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAgingStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAgingStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_AGING_STMT;
    sStmt->mTableList = aTableList;

    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}

 



/**
 * @brief alter table add column 생성
 */
dbmParseAlterTableAddColumnStmt  * dbmMakeAlterTableAddColumnStmt( dbmParserContext     * aCtx,
                                                                   dbmParseValue        * aTableName,
                                                                   dbmParseColumnDef    * aColumnDef,
                                                                   dbmParseExpr         * aDefaultVal )
{
    dbmParseAlterTableAddColumnStmt    * sStmt = NULL;


    /**
     * dbmParseAlterTableAddColumnStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterTableAddColumnStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterTableAddColumnStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_TABLE_ADD_COLUMN_STMT;
    sStmt->mTableName = aTableName;
    sStmt->mColumnDef = aColumnDef;
    sStmt->mDefaultVal = aDefaultVal;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}





/**
 * @brief alter table drop column 생성
 */
dbmParseAlterTableDropColumnStmt  * dbmMakeAlterTableDropColumnStmt( dbmParserContext     * aCtx,
                                                                     dbmParseValue        * aTableName,
                                                                     dbmParseValue        * aColumnName )
{
    dbmParseAlterTableDropColumnStmt    * sStmt = NULL;


    /**
     * dbmParseAlterTableDropColumnStmt 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseAlterTableDropColumnStmt),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseAlterTableDropColumnStmt) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_ALTER_TABLE_DROP_COLUMN_STMT;
    sStmt->mTableName = aTableName;
    sStmt->mColumnName = aColumnName;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief limit info
 */
dbmParseLimit  * dbmMakeParseLimit( dbmParserContext     * aCtx,
                                    dbmParseValue        * aStart,
                                    dbmParseValue        * aCount )
{
    dbmParseLimit    * sStmt = NULL;


    /**
     * dbmParseLimit 할당
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx->mAllocator,
                                   sizeof(dbmParseLimit),
                                   (void **)&sStmt,
                                   aCtx->mErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sStmt, 0x00, sizeof(dbmParseLimit) );


    /**
     * Stmt Value 설정
     */

    sStmt->mType = DBM_PARSE_TYPE_LIMIT_INFO;
    sStmt->mStart = aStart;
    sStmt->mCount = aCount;


    return sStmt;

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aCtx->mErrorStack );
    }

    DBM_FINISH

    return NULL;
}




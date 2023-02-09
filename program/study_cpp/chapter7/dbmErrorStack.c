#include <dbmErrorStack.h>

#if 0

/**
 * 공통 에러 메시지 테이블 (별도의 분리된 코드체계를 가질 경우 여기에 추가)
 */
extern dbmDetailErrorMessage gCommonError[];
extern dbmDetailErrorMessage gParserError[];
extern dbmDetailErrorMessage gAPIError[];



/**
 * 전체 에러 메시지 테이블 (여기에도 추가)
 */
dbmDetailErrorMessage * gErrorTable[] =
{
    gCommonError,
    gParserError,
    gAPIError,
    NULL
};



/**
 * @brief 1개의 ErrorStack을 채운다.
 */
dbmStatus dbmPushError( dbmInt32         aErrorCode,
                        dbmErrorStack  * aErrorStack,
                        ... )
{
    va_list                  sList;
    dbmErrorData           * sErrorData   = NULL;
    dbmDetailErrorMessage  * sErrorTable  = NULL;
    dbmInt32                 sErrorKind;
    dbmInt32                 sErrorPos;


    /**
     * 에러코드가 오류이어야 한다.
     * 에러스택은 NULL일 수 없다.
     */

    DBM_TRY_THROW( aErrorCode != DBM_SUCCESS, RAMP_INVALID_ERROR_CODE );
    DBM_TRY_THROW( aErrorStack != NULL, RAMP_INVALID_ERROR_STACK );


    /**
     * ErrorStack의 Max-Depth를 넘을 수 없다.
     */

    DBM_TRY_THROW( aErrorStack->mCount < DBM_MAX_ERR_DEPTH, RAMP_TOO_MANY_DEPTH );


    /**
     * ErrorStack내에 삽입할 위치의 ErrorData를 초기화 한다.
     */

    sErrorData = (dbmErrorData *)& aErrorStack->mErrorData[ aErrorStack->mCount ];
    dbmMemset( sErrorData, 0x00, sizeof( dbmErrorData ) );

    /**
     * 에러코드를 설정한다.
     */
    sErrorData->mErrorCode = aErrorCode;


    /**
     * 입력된 에러코드로부터 에러모듈을 알아낸다.
     * 최대 각 파트당 DBM_MAX_ERR_COUNT개의 메시지를 갖는다.
     */

    sErrorKind = ( aErrorCode / DBM_MAX_ERR_COUNT ) - DBM_ERROR_BASE;
    sErrorTable = gErrorTable[ sErrorKind ];

    /**
     * 에러정의 모듈이 존재해야 한다.
     */

    DBM_TRY_THROW( sErrorTable != NULL, RAMP_INVALID_ERROR );


    /**
     * 유형별 에러모듈에서 에러포맷 위치를 알아낸다.
     */

    sErrorPos = ( aErrorCode %  DBM_MAX_ERR_COUNT );

    DBM_TRY_THROW( sErrorData != NULL, RAMP_INVALID_ERROR_CODE );


    /**
     * 부가적인 사용자 오류메시지를 포함한 에러메시지를 생성
     */

    va_start( sList, aErrorStack );
    vsnprintf( sErrorData->mErrorMsg,
               DBM_MAX_ERR_MSG_LEN,
               sErrorTable[ sErrorPos ].mDetailMessage,
               sList );
    va_end( sList );

    /**
     * 에러스택을 증가시킴
     */

    aErrorStack->mCount ++;


    /**
     * 정상종료
     */

    return DBM_SUCCESS;


    /**
     * 오류종료
     */

    DBM_CATCH( RAMP_INVALID_ERROR_CODE )
    {
    }

    DBM_CATCH( RAMP_INVALID_ERROR_STACK )
    {
    }

    DBM_CATCH( RAMP_TOO_MANY_DEPTH )
    {
    }

    DBM_CATCH( RAMP_INVALID_ERROR )
    {
    }


    DBM_FINISH

    return DBM_FAILURE;
}




/**
 * @brief 에러스택에 남겨두고 마지막에 발생한 오류를 리턴한다.
 */
dbmErrorData * dbmGetLastErrorData( dbmErrorStack * aErrorStack )
{
    dbmInt32 sPos = 0;


    /**
     * 에러스택이 NULL일 수 없다.
     */

    DBM_TRY_THROW( aErrorStack != NULL, RAMP_INVALID_ERROR_STACK );


    /**
     * 에러가 없는 경우는 NULL로 리턴
     */

    if( aErrorStack->mCount == 0 )
    {
        return NULL;
    }


    /**
     * 에러스택의 마지막 위치의 에러데이터를 리턴한다.
     */

    sPos = aErrorStack->mCount - 1;

    /**
     * 정상 종료
     */

    return (dbmErrorData *)( &aErrorStack->mErrorData[ sPos ] );


    /**
     * 에러 처리
     */

    DBM_CATCH( RAMP_INVALID_ERROR_STACK )
    {
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief 에러스택에서 1개씩 꺼내본다.
 */
dbmErrorData * dbmPopErrorData( dbmErrorStack * aErrorStack )
{
    dbmInt32 sPos = 0;


    /**
     * 에러스택이 NULL일 수 없다.
     */

    DBM_TRY_THROW( aErrorStack != NULL, RAMP_INVALID_ERROR_STACK );


    /**
     * 에러가 없는 경우는 NULL로 리턴
     */

    if( aErrorStack->mCount == 0 )
    {
        return NULL;
    }


    /**
     * 에러스택의 마지막 위치의 에러데이터를 리턴한다.
     */
    sPos = aErrorStack->mCount - 1;
    aErrorStack->mCount --;


    /**
     * 정상 종료
     */

    return (dbmErrorData *)( &aErrorStack->mErrorData[ sPos ] );


    /**
     * 에러 처리
     */

    DBM_CATCH( RAMP_INVALID_ERROR_STACK )
    {
    }

    DBM_FINISH

    return NULL;
}




/**
 * @brief 최초 사용하기전, 혹은 최종 사용완료 후에는 호출해라.
 */
void dbmClearErrorStack( dbmErrorStack * aErrorStack )
{

    /**
     * 에러스택이 NULL일 수 없다.
     */

    DBM_TRY_THROW( aErrorStack != NULL, RAMP_INVALID_ERROR_STACK );

    /**
     * 정상 종료
     */

    aErrorStack->mCount = 0;

    return;


    /**
     * 에러 처리
     */

    DBM_CATCH( RAMP_INVALID_ERROR_STACK )
    {
    }

    DBM_FINISH

    return;
}

#endif

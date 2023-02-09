#include <dbmList.h>
#include <dbmErrorCode.h>





/**
 * @brief List Object를 생성한다.
 */
dbmStatus dbmCreateList( dbmAllocator     * aCtx,
                         dbmList         ** aList,
                         dbmErrorStack    * aErrorStack )
{
    dbmList      * sList = NULL;



    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aList != NULL, RAMP_ERR_INVALID_ARGS );

    
    /**
     * create List
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx,
                                   sizeof( dbmList ),
                                   (void **)& sList,
                                   aErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sList, 0x00, sizeof(dbmList) );


    /**
     * Initialize List
     */

    sList->mCount = 0;
    sList->mHead = NULL;
    sList->mTail = NULL;


    /**
     * return
     */

    *aList = sList;


    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    return DBM_FAILURE;
}





/**
 * @brief List에 element를 매단다. (순서없음, 중복가능)
 */
dbmStatus dbmAddList( dbmAllocator         * aCtx,
                      dbmList              * aList,
                      dbmListElemType        aElemType,
                      void                 * aElem,
                      dbmErrorStack        * aErrorStack )
{
    dbmListElement      * sElem = NULL;


    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aList != NULL, RAMP_ERR_INVALID_ARGS );

    
    /**
     * create List Element
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx,
                                   sizeof( dbmListElement ),
                                   (void **)& sElem,
                                   aErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sElem, 0x00, sizeof(dbmListElement) );

    sElem->mType = aElemType;
    sElem->mElem = aElem;
    sElem->mPrev = NULL;
    sElem->mNext = NULL;


    /**
     * Head, Tail 변경
     */

    if( aList->mCount == 0 )
    {
        aList->mHead = sElem;
        aList->mTail = sElem;
        aList->mCount ++;
    }
    else
    {
        aList->mTail->mNext = sElem;
        sElem->mPrev = aList->mTail;
        aList->mTail = sElem;
        aList->mCount ++;
    }



    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    return DBM_FAILURE;
}





/**
 * @brief List에 element를 매단다. (순서없음, 중복가능)
 */
dbmStatus dbmAddListNoDup( dbmAllocator         * aCtx,
                           dbmList              * aList,
                           dbmListElemType        aElemType,
                           void                 * aElem,
                           dbmErrorStack        * aErrorStack )
{
    dbmListElement      * sElem = NULL;


    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aList != NULL, RAMP_ERR_INVALID_ARGS );


    /**
     * 중복을 허용하지 않는다.
     */

    DBM_LIST_ITERATE( aList, sElem )
    {
        if( aElem == DBM_LIST_GET_POINTER_VALUE( sElem ) )
        {
            DBM_THROW( RAMP_FINISH );
        }
    }

    
    /**
     * create List Element
     */

    DBM_TRY_THROW( dbmAllocMemory( aCtx,
                                   sizeof( dbmListElement ),
                                   (void **)& sElem,
                                   aErrorStack ) == DBM_SUCCESS,
                   RAMP_ERR_ALLOC_FAIL );

    dbmMemset( sElem, 0x00, sizeof(dbmListElement) );

    sElem->mType = aElemType;
    sElem->mElem = aElem;
    sElem->mPrev = NULL;
    sElem->mNext = NULL;


    /**
     * Head, Tail 변경
     */

    if( aList->mCount == 0 )
    {
        aList->mHead = sElem;
        aList->mTail = sElem;
        aList->mCount ++;
    }
    else
    {
        aList->mTail->mNext = sElem;
        sElem->mPrev = aList->mTail;
        aList->mTail = sElem;
        aList->mCount ++;
    }


    DBM_RAMP( RAMP_FINISH )

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_ALLOC_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    return DBM_FAILURE;
}







/**
 * @brief List에서 제거한다.
 */
dbmStatus dbmRemoveListElem( dbmList             * aList,
                             void                * aObject,
                             dbmErrorStack       * aErrorStack )
{
    dbmListElement        * sElem = NULL;
    void                  * sObject = NULL;
    dbmBool                 sFound = DBM_FALSE;


    DBM_TRY_THROW( aList != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aObject != NULL, RAMP_ERR_INVALID_ARGS );


    /**
     * 동일한 Pointer로 탐색
     */

    DBM_LIST_ITERATE( aList, sElem )
    {
        sObject = DBM_LIST_GET_POINTER_VALUE( sElem );
        if( sObject == aObject )
        {
            sFound = DBM_TRUE;
            break;
        }
    }

    DBM_TRY_THROW( sFound == DBM_TRUE, RAMP_FINISH );

    /**
     * 탐색이 됬다면 Link에서 제거한다.
     * 메모리가 좀 늘긴 하겠지만 빈번한 작업이 아닐듯 함.(성능느림)
     */

    if( sElem->mPrev != NULL )
    {
        sElem->mPrev->mNext = sElem->mNext;
    }

    if( sElem->mNext != NULL )
    {
        sElem->mNext->mPrev = sElem->mPrev;
    }

    // Head = tail 임으로 둘다 elem에 어느쪽이든 해당되면 교체한다.
    if( sElem == aList->mHead )
    {
        aList->mHead = sElem->mNext;
    }

    if( sElem == aList->mTail )
    {
        aList->mTail = sElem->mPrev;
    }

    aList->mCount = aList->mCount - 1;
    if( aList->mCount < 0 ) 
    {
        aList->mCount = 0;
    }


    DBM_RAMP( RAMP_FINISH )

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    return DBM_FAILURE;
}

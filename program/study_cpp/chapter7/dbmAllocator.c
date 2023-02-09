/**
 * @brief 단순히 memory chunk를 연결해서 공간을 활용하도록 한다.
 */

#include <dbmAllocatorEx.h>
#include <dbmErrorCode.h>



/**
 * @brief Static 하게 자유롭게 할당할 memMgr을 생성한다.
 * @param  aCtx         새롭게 생성될 메모리 관리자
 * @param  aErrorStack  ErrorStack
 */
dbmStatus dbmCreateAllocator( dbmAllocator    ** aCtx,
                              dbmErrorStack    * aErrorStack )
{
    dbmAllocator      * sCtx = NULL;
    dbmMemChunk       * sChunk = NULL;


    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );
   

    /**
     * Allocator 할당
     */
    
    DBM_TRY( dbmAllocHeap( (void **)&sCtx,
                           sizeof(dbmAllocator),
                           aErrorStack ) == DBM_SUCCESS );

    dbmMemset( sCtx, 0x00, sizeof( dbmAllocator ) );
    

    /**
     * Chunk 할당
     */
 
    DBM_TRY( dbmAllocHeap( (void **)&sChunk,
                           sizeof(dbmMemChunk),
                           aErrorStack ) == DBM_SUCCESS );
    
    dbmMemset( sCtx, 0x00, sizeof( dbmMemChunk ) );


    /**
     * 실제로 쓸 Chunk할당하고 정보 설정
     */

    DBM_TRY( dbmAllocHeap( (void **)&sChunk->mChunk,
                           DBM_MEM_CHUNK_SIZE,
                           aErrorStack ) == DBM_SUCCESS );


    sChunk->mCurr = 0;
    sChunk->mSize = DBM_MEM_CHUNK_SIZE;
    sChunk->mNext = NULL;


    /**
     * Head 로 셋팅
     */

    sCtx->mHead = sChunk;
    sCtx->mTail = sChunk;
    sCtx->mCurrent = sChunk;
    sCtx->mSaveChunk = NULL;
    sCtx->mSaveCurr = DBM_NOT_USED;
    

    /**
     * Return
     */

    *aCtx = sCtx;


    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    if( sCtx != NULL )
    {
        free( sCtx );
    }

    return DBM_FAILURE;
}





/**
 * @brief Allocator를 다 썼거나 할때 이걸 확장한다.
 */
dbmStatus dbmExtendAllocator( dbmAllocator     * aCtx,
                              dbmErrorStack    * aErrorStack )
{
    dbmMemChunk       * sChunk = NULL;


    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );


    /**
     * Chunk 할당
     */
 
    DBM_TRY( dbmAllocHeap( (void **)&sChunk,
                           sizeof(dbmMemChunk),
                           aErrorStack ) == DBM_SUCCESS );
    
    dbmMemset( sChunk, 0x00, sizeof( dbmMemChunk ) );


    /**
     * 실제로 쓸 Chunk할당하고 정보 설정
     */

    DBM_TRY( dbmAllocHeap( (void **)&sChunk->mChunk,
                           DBM_MEM_CHUNK_SIZE,
                           aErrorStack ) == DBM_SUCCESS );

    sChunk->mCurr = 0;
    sChunk->mSize = DBM_MEM_CHUNK_SIZE;
    sChunk->mNext = NULL;


    /**
     * Current, Tail을 새로 만든 Chunk로 바꾼다.
     */

    aCtx->mCurrent->mNext = sChunk;
    aCtx->mTail = sChunk;
    aCtx->mCurrent = sChunk;
    

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    if( sChunk != NULL )
    {
        free( sChunk );
    }

    return DBM_FAILURE;
}





/**
 * @brief Chunk내에서 메모리를 요청한다. (DBM_MEM_CHUNK_SIZE이내만 가능)
 */
dbmStatus dbmAllocMemory( dbmAllocator     * aCtx,
                          dbmInt32           aSize,
                          void            ** aRet,
                          dbmErrorStack    * aErrorStack )
{
    dbmInt32       sSize = DBM_ALIGN_SIZE( aSize );

    DBM_TRY_THROW( aCtx != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aCtx->mHead != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aCtx->mCurrent != NULL, RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( (sSize > 0 && sSize < DBM_MEM_CHUNK_SIZE), RAMP_ERR_INVALID_ARGS );
    DBM_TRY_THROW( aRet != NULL, RAMP_ERR_INVALID_ARGS );
   

    /**
     * Allocator 할당
     */
     
    if( aCtx->mCurrent->mCurr + sSize > aCtx->mCurrent->mSize )
    {
        if( aCtx->mCurrent->mNext == NULL )
        {
            DBM_TRY_THROW( dbmExtendAllocator( aCtx,
                                               aErrorStack ) == DBM_SUCCESS,
                           RAMP_ERR_EXTEND_FAIL );
        }
        else
        {
            aCtx->mCurrent = (dbmMemChunk *)aCtx->mCurrent->mNext;
        }
    }
    

    /**
     * Return
     */

    *aRet = (void *)( aCtx->mCurrent->mChunk + aCtx->mCurrent->mCurr );
    aCtx->mCurrent->mCurr = aCtx->mCurrent->mCurr + sSize;

#ifdef DBM_DEBUG
    dbmMemset( *aRet, 0xfe, sSize );
#endif

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_EXTEND_FAIL )
    {
    }


    DBM_FINISH

    return DBM_FAILURE;
}



/**
 * @brief reset
 */
void dbmResetAllocator( dbmAllocator     * aCtx )
{
    dbmMemChunk       * sChunk = NULL;
    dbmMemChunk       * sNextChunk = NULL;

    sChunk = aCtx->mHead;

    while( sChunk != NULL )
    {
        sNextChunk = sChunk->mNext;

        if( sChunk != aCtx->mHead )
        {
            dbmFreeHeap( sChunk->mChunk );
            sChunk->mChunk = NULL;

            dbmFreeHeap( sChunk );
            sChunk = NULL;
        }

        sChunk = sNextChunk;    
    }
    
    sChunk = aCtx->mHead;
    sChunk->mCurr = 0;
    sChunk->mNext = NULL;

    aCtx->mCurrent = aCtx->mHead;
    aCtx->mTail = aCtx->mHead;
    aCtx->mSaveChunk = NULL;
    aCtx->mSaveCurr = DBM_NOT_USED;
}



/**
 * @brief Allocator 가 Head부터 모든 Chunk를 해제한다.
 */
dbmStatus dbmDropAllocator( dbmAllocator    ** aCtx,
                            dbmErrorStack    * aErrorStack )
{
    dbmMemChunk       * sChunk = NULL;
    dbmMemChunk       * sNextChunk = NULL;


    DBM_TRY_THROW( aCtx != NULL, RAMP_FINISH );
    DBM_TRY_THROW( *aCtx != NULL, RAMP_FINISH );


    /**
     * Head부터 순회하면서 해제한다.
     */

    sChunk = (*aCtx)->mHead;

    while( sChunk != NULL )
    {
        sNextChunk = sChunk->mNext;

        dbmFreeHeap( sChunk->mChunk );
        sChunk->mChunk = NULL;

        dbmFreeHeap( sChunk );
        sChunk = NULL;

        sChunk = sNextChunk;    
    }
    

    /**
     * Context 자체도 해제해버린다.
     */


    dbmFreeHeap( *aCtx );
    *aCtx = NULL;


    DBM_RAMP( RAMP_FINISH )

    return DBM_SUCCESS;
}





/**
 * @berif Allocator현재위치
 */
void dbmSaveAllocator( dbmAllocator     * aCtx )
{
    // 현재 시작하는 메모리 위치를 저장해둔다.
    aCtx->mSaveChunk = aCtx->mCurrent;
    aCtx->mSaveCurr = aCtx->mCurrent->mCurr;
}




/**
 * @brief Rewind Allocator
 */
void dbmRewindAllocator( dbmAllocator     * aCtx )
{
    dbmMemChunk       * sChunk = NULL;
    dbmMemChunk       * sNextChunk = NULL;

    if( (aCtx->mSaveChunk != NULL && aCtx->mSaveCurr != DBM_NOT_USED) && 
        (aCtx->mSaveChunk != aCtx->mCurrent || aCtx->mSaveCurr != aCtx->mCurrent->mCurr) )
    { 
        // SaveChunk 이후로 매달린 것들은 메모리를 해제한다.
        
        sChunk = aCtx->mSaveChunk;

        while( sChunk != NULL )
        {
            sNextChunk = sChunk->mNext;

            if( sChunk != aCtx->mSaveChunk )
            {
                dbmFreeHeap( sChunk->mChunk );
                sChunk->mChunk = NULL;

                dbmFreeHeap( sChunk );
                sChunk = NULL;
            }

            sChunk = sNextChunk;    
        }
        
        // Save했던 위치로 되돌린다.
        aCtx->mCurrent = aCtx->mSaveChunk;
        aCtx->mCurrent->mCurr = aCtx->mSaveCurr;
        aCtx->mTail = aCtx->mCurrent;
    }
}



void dbmClearSaveAllocator( dbmAllocator      * aCtx )
{
    aCtx->mSaveChunk = NULL;
    aCtx->mSaveCurr = DBM_NOT_USED;
}

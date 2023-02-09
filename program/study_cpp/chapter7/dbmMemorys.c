/*******************************************************************************
 * dbmMemorys.c
 *
 * Copyright (c) 2011, SUNJESOFT Inc.
 *
 *
 * IDENTIFICATION & REVISION
 *        $Id: dbmMemorys.c 21968 2017-05-16 03:10:01Z cloudrain21 $
 *
 * NOTES
 *    
 *
 ******************************************************************************/

/**
 * @file dbmMemorys.c
 * @brief Standard Layer Memory Routines
 */

#include <dbc.h>
#include <dbmDef.h>
#include <dbmError.h>
#include <dbe.h>
#include <dbmMemorys.h>
#include <dbmLog.h>

/**
 * @addtogroup dbmMemorys
 * @{
 */

const dbmCopyFunction gDbmCopyFunc[9] =
{
    dbmCopy0Bytes,
    dbmCopy1Bytes,
    dbmCopy2Bytes,
    dbmCopy3Bytes,
    dbmCopy4Bytes,
    dbmCopy5Bytes,
    dbmCopy6Bytes,
    dbmCopy7Bytes,
    dbmCopy8Bytes
};

/**
 * @brief Heap 메모리를 할당한다.
 * @param[out] aAddr 할당할 Heap 메모리 포인터의 주소
 * @param[in] aSize 할당할 Heap 메모리 크기
 * @param[out] aErrorStack 에러 스택
 * @par Error Codes:
 * @code
 * [DBM_ERRCODE_OUT_OF_MEMORY]
 *     커널 메모리를 할당받을수 없는 경우에 발생함.
 * @endcode
 */
dbmStatus dbmAllocHeap( void         ** aAddr,
                        dbmSize         aSize,
                        dbmErrorStack * aErrorStack )
{
    *aAddr = NULL;

    DBM_TRY_THROW( aSize != 0, RAMP_EXIT_FUNCTION );

    *aAddr = malloc( aSize );

    DBM_TRY_THROW( *aAddr != NULL, RAMP_ERR_OUT_OF_MEMORY );

#ifdef DBM_DEBUG
    dbmMemset( *aAddr, 0xfe, aSize );
#endif

    DBM_RAMP(RAMP_EXIT_FUNCTION);

    //printf("alloc %p \n", *aAddr);

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_OUT_OF_MEMORY )
    {
        dblPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_OUT_OF_MEMORY,
                      NULL,
                      aErrorStack );
        STE_SET_SYSTEM_ERROR( errno, aErrorStack );
    }
    
    DBM_FINISH;

    return DBM_FAILURE;
}

/**
 * @brief 할당된 Heap 메모리를 해제한다.
 * @param[in] aAddr 해제할 Heap 메모리 포인터
 */
void dbmFreeHeap( void * aAddr )
{
    //printf("free %p \n", aAddr);
    DBM_ASSERT( aAddr != NULL );
    
    free( aAddr );
}


/**
 * @brief 메모리를 특정 값으로 설정한다.
 * @param[in] aAddr 설정할 메모리 주소
 * @param[in] aConstant 메모리에 설정할 값
 * @param[in] aSize 설정할 크기
 * @return 메모리 영역 @a aAddr 에 대한 포인터를 반환한다.
 */
void * dbmMemset( void   * aAddr,
                  dbmInt32 aConstant,
                  dbmSize  aSize )
{
    DBM_ASSERT( aSize >= 0 );

    return memset( aAddr, aConstant, aSize );
}

void dbmCopy0Bytes( void * aDest, const void * aSrc )
{
}

void dbmCopy1Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT8( aDest, aSrc );
}

void dbmCopy2Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT16( aDest, aSrc );
}
 
void dbmCopy3Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT16( aDest, aSrc );
    ((dbmChar*)aDest)[2] = ((dbmChar*)aSrc)[2];
}
 
void dbmCopy4Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT32( aDest, aSrc );
}
 
void dbmCopy5Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT32( aDest, aSrc );
    ((dbmChar*)aDest)[4] = ((dbmChar*)aSrc)[4];
}
 
void dbmCopy6Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT32( aDest, aSrc );
    ((dbmChar*)aDest)[4] = ((dbmChar*)aSrc)[4];
    ((dbmChar*)aDest)[5] = ((dbmChar*)aSrc)[5];
}
 
void dbmCopy7Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT32( aDest, aSrc );
    ((dbmChar*)aDest)[4] = ((dbmChar*)aSrc)[4];
    ((dbmChar*)aDest)[5] = ((dbmChar*)aSrc)[5];
    ((dbmChar*)aDest)[6] = ((dbmChar*)aSrc)[6];
}
 
void dbmCopy8Bytes( void * aDest, const void * aSrc )
{
    DBM_WRITE_INT64( aDest, aSrc );
}

/**
 * @brief 메모리 영역 @a aSrc 를 메모리 영역 @a aDest 로 @a aSize 바이트 복사한다.
 * @param[in] aDest 복사될 메모리
 * @param[in] aSrc 복사할 메모리
 * @param[in] aSize 복사할 크기
 * @return 메모리 영역 @a aDest 에 대한 포인터를 반환한다.
 * @remark @a aSrc 와 @a aDest 의 메모리 영역은 겹치면 안된다.
 *         만일 메모리 영역을 겹쳐서 사용하길 원한다면 dbmMemmove()를 사용한다.
 */

#if 0
void * dbmMemcpy( void       * aDest,
                  const void * aSrc,
                  dbmSize      aSize )
{
    DBM_ASSERT( aSize >= 0 );

    return memcpy( aDest, aSrc, aSize );
}
#endif

/**
 * @brief 메모리 영역 @a aSrc 를 메모리 영역 @a aDest 로 @a aSize 바이트 복사한다.
 * @param[in] aDest 복사될 메모리
 * @param[in] aSrc 복사할 메모리
 * @param[in] aSize 복사할 크기
 * @return 메모리 영역 @a aDest 에 대한 포인터를 반환한다.
 * @remark @a aSrc의 @a aSize 만큼 임시 영역에 복사한 후 @a aDest에 복사하므로
 *         @a aSrc 와 @a aDest 의 메모리 영역은 겹칠 수 있다.
 */
void * dbmMemmove( void *       aDest,
                   const void * aSrc,
                   dbmSize      aSize )
{
    DBM_ASSERT( aSize >= 0 );

    return memmove( aDest, aSrc, aSize );
}

/**
 * @brief 메모리 영역 @a aSrc 에서부터 @a aSize byte 중에  @a aChar 값의 byte 위치가 있으면 해당 위치를 반환한다
 * @param[in] aSrc 체크할 메모리 시작 포인터
 * @param[in] aChar 체크할 byte 값
 * @param[in] aSize 체크할 byte dbream의 길이
 * @return 최초로 나타나는 aChar값의 위치에 대한 포인터를 반환한다.
 */
void * dbmMemchr( void *       aSrc,
                  dbmInt32     aChar,
                  dbmSize      aSize )
{
    DBM_ASSERT( aSize >= 0 );

    return memchr( aSrc, aChar, aSize );
}

/**
 * @brief @a aValue1이 @a aValue2를 @a aSize 길이 만큼 메모리 비교를 수행한다.
 * @param[in] aValue1 비교할 대상1의 메모리 시작 포인터
 * @param[in] aValue2 비교할 대상2의 메모리 시작 포인터
 * @param[in] aSize 두 값을 비교할 byte dbream의 길이
 * @return @a aValue1이 @a aValue2보다 크면 양의 정수를 반환하고, 작으면 음의 정수를 반환한다.
 *         @a aValue1과 @a aValue2가 같으면 0을 반환한다.
 */
dbmInt32 dbmMemcmp( void *       aValue1,
                    void *       aValue2,
                    dbmSize      aSize )
{
    DBM_ASSERT( aSize >= 0 );

    return memcmp( aValue1, aValue2, aSize );
}

/** @} */

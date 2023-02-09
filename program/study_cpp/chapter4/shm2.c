#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>


#define  DATA_SIZE (1024)              // 데이터 최대 크기 고정
#define  DATA_MAX_COUNT (1024)         // 데이터 최대 개수 고정
#define  SUCCESS   (0)                 // 성공
#define  FAILURE   (-1)                // 실패


/**
 * @brief 메모리저장의 헤더를 정의
 */
typedef struct
{
    volatile int         mLock;           // Lock
    volatile long long   mAllocIdx;       // 공간할당자
    volatile long long   mFreeIdx;        // 해제관리자
    int                  mDataSize;       // 이 Segment에 적재가능한 데이터 최대 크기정보
    int                  mDataMaxCount;   // 이 Segment에 적재가능한 데이터의 최대 개수
} Header;


#define  SLOT_POS( A, B, C)     (A + sizeof(Header) + DATA_SIZE * C)



/**
 * @brief Shared memory를 최초 헤더를 설정한다.
 */
void Init( char * aPtr )
{
    Header   * sHdr;

    /**
     * 헤더정보를 초기화 한다.
     */

    sHdr = (Header *)(aPtr);
    sHdr->mLock = -1;
    sHdr->mAllocIdx = 0;
    sHdr->mFreeIdx = 0;
    sHdr->mDataSize = DATA_SIZE;
    sHdr->mDataMaxCount = DATA_MAX_COUNT;
}



/**
 * @brief Shared Memory내의 ring-buffer형태의 공간관리자를 설정한다.
 */
void InitSpace( char * aPtr )
{
    int     * sPtr;
    int       i;


    // 4byte짜리 공간 위치를 표기하는 설정을 해둔다.
    // [0][1][2][3] ...[max] 
    
    sPtr = (int *)(aPtr + sizeof(Header));
    for( i = 0 ; i < DATA_MAX_COUNT; i ++ )
    {
        *(int *)sPtr = i;
        sPtr ++;
    }

    // 제대로 되었나 테스트 출력해본다.
    sPtr = (int *)(aPtr + sizeof(Header));
    printf( "0th = %d\n", *(int *)sPtr );
    
    sPtr = (int *)(aPtr + sizeof(Header) + sizeof(int) * 56);
    printf( "56th = %d\n", *(int *)sPtr );
}




int Lock( char * aPtr )
{
    Header   * sHdr;
    int        sTry = 0;
    int        sOld = -1;

    sHdr = (Header *)(aPtr);

    while( 1 )
    {
        sOld = __sync_val_compare_and_swap( &sHdr->mLock, -1, 1 );
        if( sOld == -1 ) break;

#if 0
        if( sTry++ >= 1024 )
        {
            usleep(100);
            sTry = 0;
        }
#endif
    }

    return SUCCESS;
}


int Unlock( char * aPtr )
{
    Header   * sHdr;
    int        sOld = -1;

    sHdr = (Header *)(aPtr);

    while( 1 )
    {
        sOld = __sync_val_compare_and_swap( &sHdr->mLock, 1, -1 );
        if( sOld == 1 ) break;
    }

    return SUCCESS;
}




/**
 * @brief 1개의 공간을 할당해준다.
 */
void AllocSpace( char    * aPtr , 
                 int     * aPos )
{
    Header        * sHdr = NULL;
    char          * sPtr = aPtr;
    int           * sNumInfo;
    int             sPos;
    int             sIdx;

    sHdr = (Header *)sPtr;

    // Lock을 걸자
    Lock( sPtr );

    // 현재 Allocator가 보는 위치를 사용하자.
    sIdx = sHdr->mAllocIdx%sHdr->mDataMaxCount;
    printf( "Alloc Index = %d\n", sIdx );
   
    // 그 공간정보가 제대로 된 정보인지 체크한다.
    sNumInfo = (int *)(sPtr + sizeof(Header) + sizeof(int) * sIdx);
    if( *(int *)sNumInfo == -1 )
    {
        printf( "This space already used, space full\n" );
        Unlock( sPtr );
        return;
    }
    
    // 이제 이 공간은 사용중이라고 표기하자.
    sPos = *(int *)sNumInfo;
    *(int *)sNumInfo = -1;

    // 다른놈들이 쓸 수 있게 allocator지시자를 +1 시키자.
    sHdr->mAllocIdx++;

    // 쓸수 있게 Unlock하고
    Unlock( sPtr );

    // 내가 할당받은 공간 정보를 리턴하자.
    *aPos = sPos;
}




/**
 * @brief 1개의 공간을 반납한다.
 */
void FreeSpace( char    * aPtr , 
                int       aPos )
{
    Header        * sHdr = NULL;
    char          * sPtr = aPtr;
    int           * sNumInfo;
    int             sIdx;

    sHdr = (Header *)sPtr;

    Lock( sPtr );

    sIdx = sHdr->mFreeIdx%sHdr->mDataMaxCount;
    printf( "Free Index = %d\n", sIdx );
   
    sNumInfo = (int *)(sPtr + sizeof(Header) + sizeof(int) * sIdx);
    if( *(int *)sNumInfo != -1 )
    {
        printf( "This space can not be free,\n" );
        Unlock( sPtr );
        return;
    }
    
    // 사용자가 알려준 공간정보를 가용공간이 되도록 설정해둔다.
    *(int *)sNumInfo = aPos;

    // 이제 해제 가능한 정보는 다음위치에 할 수 있게 +1 시키자.
    sHdr->mFreeIdx++;

    Unlock( sPtr );
}









void AllocFreeTest( char   * aPtr )
{
    Header        * sHdr;
    long long       i;
    int           * sNum;
    int             sIdx;

    
    // 10개의 공간을 할당/해제를 해본다.
    sHdr = (Header *)(aPtr);
    printf( "Before: sHeader->mAllocIdx = %ld,  mFreeIdx = %ld\n", sHdr->mAllocIdx, sHdr->mFreeIdx );

    for( i = 0 ; i < 10 ; i ++ )
    {
        AllocSpace( aPtr, & sIdx );
        FreeSpace( aPtr, sIdx );
    }


    printf( "After: sHeader->mAllocIdx = %ld,  mFreeIdx = %ld\n", sHdr->mAllocIdx, sHdr->mFreeIdx );

    // 10개의 직전 처리가 해제가 제대로 됬으면
    // 할당된 정보와 동일하게 설정됬어야 할거다.
    for( i = (sHdr->mFreeIdx-10) ; i < sHdr->mFreeIdx; i ++ )
    {
        sIdx = i % sHdr->mDataMaxCount;
        sNum = (int *)(aPtr + sizeof(Header) + sizeof(int) * sIdx);
        printf( "SlotInfo = %d\n", *(int *)sNum );
    }

}


main()
{
    //void     * sPtr;
    char       * sPtr;
    int          sShmId;
    int          sFirst = 0;
    key_t        sKey = 5221113;


    // 전체헤더공간 + Space관리공간 + 실제 데이터 저장공간 할당
    sShmId = shmget( sKey, (sizeof(Header) + (sizeof(int) * DATA_MAX_COUNT) + DATA_SIZE * DATA_MAX_COUNT), 0666 );
    if( sShmId < 0 )
    {
        sShmId = shmget( sKey, (sizeof(Header) + (sizeof(int) * DATA_MAX_COUNT) + DATA_SIZE * DATA_MAX_COUNT), IPC_CREAT|0666 );
        if( sShmId < 0 )
        { 
            printf( "failed to shmget errno=%d\n", errno );
            exit(-1);
        }
        sFirst = 1;
    }

    printf( "shmKey=%d, %x, shmId = %d\n", sKey, sKey, sShmId );

    //sPtr = shmat( sShmId, NULL, 0 );
    sPtr = (char *)shmat( sShmId, NULL, 0 );
    if( sPtr == NULL )
    {
        printf( "failed to shmat errno=%d\n", errno );
        exit(-1);
    }

    if( sFirst == 1 ) 
    {
        Init( sPtr );
        InitSpace( sPtr );
    }


    AllocFreeTest( sPtr );

    shmdt( sPtr );
}

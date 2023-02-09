#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>


#define  SUCCESS   (0)
#define  FAILURE   (-1)



typedef struct
{
    volatile int  mLock;
} Header;


void Init( char * aPtr )
{
    Header   * sHdr;

    sHdr = (Header *)(aPtr);
    sHdr->mLock = -1;
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

#if 1
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


main()
{
    //void     * sPtr;
    char       * sPtr;
    int          sShmId;
    int          sFirst = 0;
    key_t        sKey = 5221112;


    sShmId = shmget( sKey, (1024 * 1024), 0666 );
    if( sShmId < 0 )
    {
        sShmId = shmget( sKey, (1024 * 1024), IPC_CREAT|0666 );
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
    }


    Lock( sPtr );
    printf("Lock Success\n");
    fflush(stdout);

    // 여기서 죽으면 어떻게 될까???
    sleep(10);

    Unlock( sPtr );

    shmdt( sPtr );
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


void *threadFunc( void * );


sem_t   gSema;



void *threadFunc( void *aArgs )
{
    int sVal1, sVal2;

    while( 1 )
    {
        sem_getvalue( &gSema, &sVal1);
        sem_wait( &gSema );
        sem_getvalue( &gSema, &sVal2);
        printf( "i am a thread (%ld) (semaV1=%d, V2=%d)\n", pthread_self(), sVal1, sVal2 );
        sem_post( &gSema );
    }

    return NULL;
}




main()
{
    pthread_t    sTid1, sTid2;


    sem_init( &gSema, 0, 1 );


    if( pthread_create( &sTid1, NULL, threadFunc, NULL )  < 0 )
    {
        printf( "failed to create a thread1 (errno=%d)\n", errno );
        exit(-1);
    }

    if( pthread_create( &sTid2, NULL, threadFunc, NULL )  < 0 )
    {
        printf( "failed to create a thread2 (errno=%d)\n", errno );
        exit(-1);
    }

#if 0
    // 이대로 끝나면 main은 종료되고 그러면 모두 종료.
    pthread_join( sTid1, NULL );
    pthread_join( sTid2, NULL );

#else
    pthread_detach( sTid1 );
    pthread_detach( sTid2 );


    while( 1 )
    {
        sleep(3);
    }
#endif

}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


void *threadFunc( void * );


// 3초마다 출력해보는 sample
void *threadFunc( void *aArgs )
{
    while( 1 )
    {
        printf( "i am a thread, tid=%ld\n", pthread_self() );
        sleep(3);
    }

    return NULL;
}



main()
{
    pthread_t    sTid;

    // 1개의 쓰레드 생성
    if( pthread_create( &sTid, NULL, threadFunc, NULL )  < 0 )
    {
        printf( "failed to create a thread (errno=%d)\n", errno );
        exit(-1);
    }


#if 0
    // 이대로 끝나면 main은 종료되고 그러면 모두 종료.
    pthread_join( sTid, NULL );

#else
    pthread_detach( sTid );


    while( 1 )
    {
        printf( "i am main\n" );
        sleep(3);
    }
#endif

}

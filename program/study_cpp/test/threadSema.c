#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


void *threadFunc( void * );

sem_t   gSema;

int gTotal = 0;

typedef struct
{
    int mExecuteCount;
}ThreadParam;

void *threadFunc( void *aArgs )
{
    int i;
    ThreadParam * sParam;
    sParam = (ThreadParam *)aArgs;
   
    for( i = 0; i < sParam -> mExecuteCount; i++ )
    {
    sem_wait( &gSema );
         gTotal = gTotal + 1;
    sem_post( &gSema );
    }
    sem_post( &gSema );
    printf("total execute %d \n", gTotal);

    return NULL;
}




main(int argc, char * argv[])
{
    pthread_t    sTid[100]; 
    int sThreadCount;
    int sLoopCount;
    int sExecuteCount;
    int i;
    ThreadParam * sParam = malloc(sizeof(ThreadParam));
    
    sem_init( &gSema, 0, 1 );
    sLoopCount = atoi(argv[2]);
    sThreadCount = atoi(argv[1]);
    sExecuteCount = sLoopCount / sThreadCount;
    sParam -> mExecuteCount = sExecuteCount;
    
    for(i = 0; i < sThreadCount; i++)
    {
        if( pthread_create( &sTid[i], NULL, threadFunc, (void*)sParam )  < 0 )
        {
            printf( "failed to create a thread1 (errno=%d)\n", errno );
            exit(-1);
        }
    }
    for(i = 0; i < sThreadCount; i++)
    {
        pthread_join( sTid[i], NULL);
    }
}

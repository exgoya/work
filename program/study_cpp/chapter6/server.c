#include <commLib.h>
#include <pthread.h>
#include <poll.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SESSION   (1024)

typedef struct
{
    int mSock;
} THREAD_PARAM;



typedef struct
{
    char mData[100];
    int  mNo;
} DATA;


void *threadSock( void *aArgs )
{
    THREAD_PARAM   *sParam;
    DATA            sData;
    struct pollfd   sPollFd;
    int  sSize = 100;
    int  sTimeout = 3000;
    int  sNum;
    int  i;

    sParam = (THREAD_PARAM *)aArgs;
    sPollFd.fd = sParam->mSock;
    printf( "threadInvoked sock=%d\n", sPollFd.fd );

    while( 1 )
    {
        sPollFd.revents = 0;
        sPollFd.events = POLLIN | POLLHUP | POLLERR;

        sNum = poll( &sPollFd, 1, sTimeout );
        if( sNum <= 0 || errno == EINTR ) continue;

        printf( "event raised sNum=%d\n", sNum );

        if( sPollFd.revents & POLLIN )
        {
            if( recvData( sPollFd.fd, (char *)&sData, &sSize ) == -1 )
            {
                break;
            }
            else
            {
                printf( "%d) %s-%d\n", sPollFd.fd, sData.mData, sData.mNo );
                if( sSize == 0 ) break;

                sData.mNo++;
 
                if( sendData( sPollFd.fd, (char *)&sData, sizeof(DATA) ) != 0 ) 
                {
                    break;
                }
            }
        }
        else if (sPollFd.revents & POLLHUP )
        {
            printf( "disconnect event\n" );
            break;
        }
        else if (sPollFd.revents & POLLERR )
        {
            printf( "error event\n" );
            break;
        }
        else
        {
            printf( "invalid revents (%d)\n", i );
            break;
        }

    }

    printf( "threadTerminated sock=%d\n", sParam->mSock );

    closeSocket( sParam->mSock );
    free( sParam );
 
    return NULL;
}



main( int argc, char *argv[] )
{
    THREAD_PARAM * sParam;
    pthread_t sTid;
    int sSock;
    int sClientSock;
    int sPort;
    int sVal;
    int i;


    if( argc < 2 )
    {
        printf( "usage] %s portNo\n", argv[0] );
        exit(-1);
    }

    sPort = atoi( argv[1] );


    if( createSocket( &sSock ) != 0 )
    {
        printf( "failed to create a socket\n" );
        exit(-1);
    }

    sVal = 1;
    setsockopt( sSock, IPPROTO_TCP, SO_REUSEADDR, &sVal, sizeof(sVal) );

    if( bindSocket( sSock, sPort ) != 0 )
    {
        printf( "failed to create a socket\n" );
        exit(-1);
    }

    if( listenSocket( sSock, 100 ) != 0 )
    {
        printf( "failed to create a socket\n" );
        exit(-1);
    }



    while( 1 )
    {
        if( acceptSocket( sSock, &sClientSock ) != 0 )
        {
            continue;
        }

        printf( "welcome (%d)\n", sClientSock );

        sParam = (THREAD_PARAM *)malloc( sizeof(THREAD_PARAM) );
        sParam->mSock = sClientSock;

        pthread_create( &sTid, NULL, threadSock, (void*)sParam );
        pthread_detach( sTid );
        
    }
    
}

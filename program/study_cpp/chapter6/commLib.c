#include <commLib.h>


int createSocket( int * aSock )
{
    int     sSock;

    sSock = socket( AF_INET, SOCK_STREAM, 0 );
    if( sSock < 0 )
    {
        printf("failed to create a socket (%d)\n", errno );
        return -1;
    }

    *aSock = sSock;
    return 0;
}



int bindSocket( int aSock,
                int aPort )
{
    struct sockaddr_in   sServer;
    int                  sRet;
   
    memset( &sServer, 0x00, sizeof(struct sockaddr_in) );
    sServer.sin_family = AF_INET;
    sServer.sin_port = htons( aPort );
    sServer.sin_addr.s_addr = htonl(INADDR_ANY );

    sRet = bind( aSock, (struct sockaddr *)&sServer, sizeof(struct sockaddr_in) );

    return sRet;
}



int listenSocket( int aSock,
                  int aBackLogSz )
{
    int              sRet;

    sRet = listen( aSock, aBackLogSz );

    return sRet;
}



int acceptSocket( int aSock,
                  int *aNewSock )
{
    struct sockaddr_in sClient;
    int                sSock;
    int                sLen;


    memset( &sClient, 0x00, sizeof(struct sockaddr_in) );
    sLen = sizeof(struct sockaddr_in);

    sSock = accept( aSock, (struct sockaddr *)&sClient, &sLen );

    if( sSock < 0 )
    {
        printf( "failed to accept a client (%d)\n", errno );
        return -1;
    }

    *aNewSock = sSock;
    return 0;
}



int connectHost( char    * aAddr, 
                 int       aPortNo,
                 int     * aSock )
{
    struct sockaddr_in    sServer;
    int                   sSock = -1;

    
    if( createSocket( &sSock ) != 0 )
    {
        return -1;
    }

    memset( &sServer, 0x00, sizeof(sServer) );

    sServer.sin_family = AF_INET;
    sServer.sin_addr.s_addr = inet_addr( aAddr );
    sServer.sin_port = htons( aPortNo );


    if( connect( sSock, (struct sockaddr *)&sServer, sizeof(sServer) ) < 0 )
    {
        printf( "failed to connect a host (%d)\n", errno );
        return -1;
    }
    

    *aSock = sSock;

    return 0;
}



void closeSocket( int aSock )
{
    close( aSock );
}




int recvData( int      aSock,
              char   * aData,
              int    * aDataSz )
{
    int sBuffSz = (*aDataSz);
    int sReadSz = 0;
    int sSz;
    int sRecvSz = 0;


    sBuffSz = sizeof(int);
    while( sReadSz < sBuffSz )
    {
        sSz = read( aSock, &sRecvSz + sReadSz, (sBuffSz - sReadSz));
        if( sSz == 0 ) break;
        sReadSz = sReadSz + sSz;
    }

    sBuffSz = sRecvSz;
    sReadSz = 0;
    while( sReadSz < sBuffSz )
    {
        sSz = read( aSock, aData + sReadSz, (sBuffSz - sReadSz));
        if( sSz == 0 ) break;
        sReadSz = sReadSz + sSz;
    }

    *aDataSz = sRecvSz;
    return 0;
}



int sendData( int    aSock,
              char * aData,
              int    aSize )
{
    int sWriteSz = 0;
    int sRemain = 0;
    int sSz;

    sRemain = sizeof(int);
    sWriteSz = 0;
    while( sRemain > 0 )
    {
        sSz = send( aSock, (&aSize + sWriteSz), (sRemain - sWriteSz), 0 );
        if( sSz == 0 ) return -1;

        sWriteSz = sWriteSz + sSz;
        sRemain = sRemain - sSz;
    }

    sRemain = aSize;
    sWriteSz = 0;
    while( sRemain > 0 )
    {
        sSz = send( aSock, (aData + sWriteSz), (sRemain - sWriteSz), 0 );
        if( sSz == 0 ) return -1;

        sWriteSz = sWriteSz + sSz;
        sRemain = sRemain - sSz;
    }

    return 0;
}

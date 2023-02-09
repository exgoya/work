#include <commLib.h>
#include <poll.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct
{
    char mData[100];
    int  mNo;
} DATA;

main( int argc, char *argv[] )
{
    DATA sData;
    int sLen;
    int sSock;
    int sPort;
    int i;


    if( argc < 3 )
    {
        printf( "usage] %s ip portNo\n", argv[0] );
        exit(-1);
    }


    sPort = atoi( argv[2] );
    if( connectHost( argv[1], sPort, &sSock ) != 0 )
    {
        exit(-1);
    }

    memset( &sData, 0x00, sizeof(DATA) );
    sData.mNo = 1;

    while( 1 )
    {
        sprintf( sData.mData, "client message: %d", sData.mNo );
        if( sendData( sSock, (char *)&sData, sizeof(sData) ) != 0 )
        {
            break;
        }

        sLen = 0;
        if( recvData( sSock, (char *)&sData, &sLen ) != 0 )
        {
            break;
        }

        printf( "sRecvData=%s\n", sData );
        sleep(3);
    }

    closeSocket( sSock );
    
}

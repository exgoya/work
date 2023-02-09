#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <dataMgr.h>



void SelectData( char  * aPtr)
{
    char   * sPtr = NULL;
    DATA   * sData = NULL;
    int      sFile = -1;
    int      i;
    char sName[32];
    int sResult = 0;

    assert( aPtr != NULL );
    sPtr = aPtr;


    sFile = open( "test.dat", O_RDONLY );
    if( sFile < 0 )
    {
        printf( "sorry, fopen fail\n" );
        exit(-1);
    }

    read( sFile, sPtr, sizeof(DATA)*DATA_MAX_COUNT );
    close(sFile );

    printf( "input Name:");
    scanf( "%s", sName);

    for( i = 0 ; i < DATA_MAX_COUNT; i ++ )
    {
        sData = (DATA *)(sPtr + sizeof(DATA) * i );
        if( strcmp(sData->mName, sName) == 0 )
        {
	    sResult = 1;
            printf( "Name=[%-32.32s], Age=%d\n", sData->mName, sData->mAge );
            break;
        }       
    }
    if( sResult == 0 )
    {
        printf( "no data" );
    }
}



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



void insert( char * aPtr)
{
    char       sName[32];
    int        sAge;
    char     * sPtr = NULL;
    DATA     * sData = NULL;
    int        sFound = 0;
    int        sFile = -1;
    int        i;

    assert( aPtr != NULL );
    sPtr = aPtr;


    // Memory Alloc
    sPtr = (char *)malloc( sizeof(DATA) * DATA_MAX_COUNT );
    if( sPtr == NULL )
    {
        printf( "failed to alloc memory (%d)\n", errno );
        exit(-1);
    }

    memset( sPtr, 0x00, sizeof(DATA) * DATA_MAX_COUNT );

    while( 1 )
    {
        printf("Input Data (Name, Age) : " );
        scanf( "%s %d", sName, &sAge );

        // quit면 종료
        if( strcmp( sName, "quit" ) == 0 )
        {
            break;
        }
        
        // 빈자리를 찾아보고 있으면 저장
        sFound = 0;
        for( i = 0 ; i < DATA_MAX_COUNT; i ++ )
        {
            sData = (DATA *)(sPtr + sizeof(DATA) * i );
            if( sData->mName[0] == 0x00 )
            {
                strcpy( sData->mName, sName );
                sData->mAge = sAge;
                sFound = 1;
                break;
            }
        }   

        if( sFound == 0 )
        {
            printf( "memory full\n" );
            break;
        }
    }    


    sFile = open( "test.dat", O_CREAT|O_RDWR );
    if( sFile < 0 )
    {
        printf( "sorry, fopen fail\n" );
        exit(-1);
    }

    write( sFile, sPtr, sizeof(DATA)*DATA_MAX_COUNT );

    fsync( sFile );

    close(sFile );
}



void printAll( char  * aPtr)
{
    char   * sPtr = NULL;
    DATA   * sData = NULL;
    int      sFile = -1;
    int      i;

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


    for( i = 0 ; i < DATA_MAX_COUNT; i ++ )
    {
        sData = (DATA *)(sPtr + sizeof(DATA) * i );
        if( sData->mName[0] != 0x00 )
        {
            printf( "Name=[%-32.32s], Age=%d\n", sData->mName, sData->mAge );
        }
    }
}


main( int argc, char *argv[] )
{
    DATA   * sData = NULL;
    char   * sPtr = NULL;
    char     sName[32];
    int      sAge;
    int      sFound = 0;
    int      i;


    if( argc < 2 )
    {
        printf( "usage] %s [i|s|p]\n", argv[0] );
        exit(-1);
    }


    // Memory Alloc
    sPtr = (char *)malloc( sizeof(DATA) * DATA_MAX_COUNT );
    if( sPtr == NULL )
    {
        printf( "failed to alloc memory (%d)\n", errno );
        exit(-1);
    }

    memset( sPtr, 0x00, sizeof(DATA) * DATA_MAX_COUNT );

    switch( argv[1][0] )
    {
        case 'i':
        {
            insert( sPtr );
            break;
        }

        case 'p':
        {
            printAll( sPtr );
            break;
        }
        case 's':
        {
            SelectData( sPtr );
            break;
        }
        default:
        {
            printf( "invalid option\n" );
            break;
        }
    }

    free( sPtr );
}

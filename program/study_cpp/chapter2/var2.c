#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


// 0x00에 대한 의미 이해 필요

main()
{
    char sStr[1024];
    char *sStrPtr;    
    size_t sSize = (1024 * 1024 * 1024 * 1);
    int i;

    strcpy( sStr, "i am a boy" );
    printf( "%s\n", sStr );


#if 1
    for( i = 0 ; i < 1000; i ++ )
    {
    sStrPtr = (char *)malloc( sSize );
    memset( sStrPtr, 0x00, sSize );
    printf( "errno = %d\n", errno );
    if( sStrPtr == NULL ) 
    {
        exit(-1);
    }
    }
#endif

    strcpy( sStrPtr, "i am a girl" );
    printf( "%s\n", sStrPtr );
}

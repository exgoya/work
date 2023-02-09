#include <stdio.h>


main()
{
    short sNumShort;
    int  sNumInt;
    long long sNumLong;

    sNumShort = 32760;
    printf( "sNumShort = %d\n", sNumShort );

    sNumShort = 65500;
    printf( "sNumShort = %d\n", sNumShort );


    sNumInt = 2100000000;
    printf( "sNumInt = %d\n", sNumInt );

    sNumInt = 2200000000;
    printf( "sNumInt = %d\n", sNumInt );


    sNumLong = 99999999999999999LL;
    printf( "sNumLong = %ld\n", sNumLong );

    printf( "%d %d %d\n", sizeof(int), sizeof(size_t), sizeof(long) );
}

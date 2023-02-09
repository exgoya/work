#include <stdio.h>
#include <stddef.h>


typedef struct
{
    char mName[30];
    long m1;
    int  mAge;
} Data;



void func1();


main()
{
    func1();
}





void func1()
{
    char     *sPtr;
    Data     *rData ;
    int       i;

    sPtr = (char *)malloc( 1024 );

//    memcpy( sPtr + 8192000, "x", 1 );

    rData = (Data *)(sPtr);
    rData->mAge = 10;

    rData = (Data *)(sPtr + sizeof(Data) * 3 );
    rData->mAge = 20;

    for( i = 0; i < 10; i++ )
    {
       rData = (Data *)(sPtr + sizeof(Data) * i );
       printf( "age=%d\n", rData->mAge );
    }
}

#include <stdio.h>

int func1( int a, int b)
{
    return (a + b);
}

int main( int argc, char *argv[])
{
    int i;
    int c1, c2, c3;

    if( argc > 2 )
    {
        c1 = atoi(argv[1]);
        c2 = atoi(argv[2]);
 
        c3 = func1( c1, c2 );
        printf( "Result= %d\n", c3 );
    }
    else
    {
        printf( "usage] %s c1 c2\n", argv[0] );
    }

    return 0;
}

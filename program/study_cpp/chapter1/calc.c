#include <stdio.h>




int main( int aArgc,  char *aArgv[] )
{
    int sNum1, sNum2, sResult = -1;


    if( aArgc < 3 )
    {
        printf( "usage] %s integer operator integer\n", aArgv[0] );
        printf( "operator] [ +|-|*|/]\n" );
        exit(-1);
    }


    sNum1 = atoi( aArgv[1] );
    sNum2 = atoi( aArgv[3] );
    
    switch( aArgv[2][0] )
    {
        case '+':
        {
            sResult = sNum1 + sNum2;
            break;
        }

        case '-':
        {
            sResult = sNum1 - sNum2;
            break;
        }

        case '*':
        {
            sResult = sNum1 * sNum2;
            break;
        }

        case '/':
        {
            sResult = sNum1 / sNum2;
            break;
        }

        default:
        {
            printf( "invalid operator\n" );
            break;
        }
    }

    printf( "Result = %d\n", sResult );
}

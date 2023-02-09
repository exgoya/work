#include <stdio.h>
#include <calOp.h>



extern CAL_FUNC gFunc[];


int main( int aArgc,  char *aArgv[] )
{
    int sType;
    int sNum1, sNum2, sResult = -1;


    if( aArgc < 3 )
    {
        printf( "usage] %s integer operator integer\n", aArgv[0] );
        printf( "operator] [ +|-|*|/]\n" );
        exit(-1);
    }


    sNum1 = atoi( aArgv[1] );
    sNum2 = atoi( aArgv[3] );
    sType = getOpType( aArgv[2][0] );

    sResult = gFunc[ sType ].mFunc( sNum1, sNum2 );
    printf( "Result = %d\n", sResult );
}

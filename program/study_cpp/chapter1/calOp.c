#include <calOp.h>


CAL_FUNC gFunc[] =
{
    {
        INVALID,
        invalidFunc
    },
    {
        ADD,
        addFunc
    },
    {
        SUB,
        subFunc
    },
    {
        MULTIPLE,
        multipleFunc
    },
    {
        DIVIDE,
        divideFunc
    }
};


int getOpType( char aType )
{
    if( aType == '+' ) return ADD;
    else if( aType == '-' ) return SUB;
    else if( aType == '*' ) return MULTIPLE;
    else if( aType == '/') return DIVIDE;
    else return INVALID;
}


int invalidFunc( int aNum1, int aNum2 )
{
    printf( "invalid operator\n" );
    return INVALID;
}


int addFunc( int aNum1, int aNum2 )
{
    return (aNum1 + aNum2 );
}


int subFunc( int aNum1, int aNum2 )
{
    return (aNum1 - aNum2 );
}


int multipleFunc( int aNum1, int aNum2 )
{
    return (aNum1 * aNum2 );
}


int divideFunc( int aNum1, int aNum2 )
{
    //if( aNum2 == 0 ) return -1;

    return (aNum1 / aNum2 );
}

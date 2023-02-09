#ifndef __CAL_OP
#define __CAL_OP

#include <stdio.h>


typedef int ( *calFunc) (int aNum1, int aNum2 );

typedef enum
{
    INVALID = 0,
    ADD,
    SUB,
    MULTIPLE,
    DIVIDE
} OPERATOR;



typedef struct
{
    OPERATOR     mOp;
    calFunc      mFunc;
} CAL_FUNC;



int invalidFunc( int, int );
int addFunc( int, int );
int subFunc( int, int );
int multipleFunc( int, int );
int divideFunc( int, int );


#endif

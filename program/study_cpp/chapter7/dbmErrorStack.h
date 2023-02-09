#ifndef __DBM_ERRORSTACK_DEF_
#define __DBM_ERRORSTACK_DEF_ 1


#include <dbmCommon.h>
#include <dbmStruct.h>


#define dbmPopErrorData         dbmPopError
#define dbmClearErrorStack      DBM_INIT_ERROR_STACK

#if __GNUC__ >= 8

/**
 * dbmPushError 매크로내의 주석 지우면 안됨.
 * 가끔 한번씩 format검증용으로 build 함.
 */
#define dbmPushError( aLevel, aCode, aStr, aStack, ... )            \
    {                                                               \
        /* printf( aCode##_STR, ##__VA_ARGS__ ); */                 \
        dblPushError( aLevel, aCode, aStr, aStack, ##__VA_ARGS__ ); \
    }
#else

/*
 * gcc 4.x 에서 warning남
 * format 검증은 gcc 8.x 이상에서 해야 함
 */
#define dbmPushError dblPushError

#endif


#endif

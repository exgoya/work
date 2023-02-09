/*******************************************************************************
 * dbmMemorys.h
 *
 * Copyright (c) 2011, SUNJESOFT Inc.
 *
 *
 * IDENTIFICATION & REVISION
 *        $Id: dbmMemorys.h 21968 2017-05-16 03:10:01Z cloudrain21 $
 *
 * NOTES
 *    
 *
 ******************************************************************************/


#ifndef _DBMMEMORYS_H_
#define _DBMMEMORYS_H_ 1

/**
 * @file dbmMemorys.h
 * @brief Standard Layer Memory Routines
 */

#include <dbmDef.h>

DBM_BEGIN_DECLS

/**
 * @defgroup dbmMemorys Memory
 * @ingroup DBM 
 * @{
 */

dbmStatus dbmAllocHeap( void         ** aAddr,
                        dbmSize         aSize,
                        dbmErrorStack * aErrorStack);

void dbmFreeHeap( void * aAddr );

void * dbmMemset( void   * aAddr,
                  dbmInt32 aConstant,
                  dbmSize  aSize );

#if 0
void * dbmMemcpy( void *       aDest,
                  const void * aSrc,
                  dbmSize      aSize );
#endif

void * dbmMemmove( void *       aDest,
                   const void * aSrc,
                   dbmSize      aSize );

void * dbmMemchr( void *       aSrc,
                  dbmInt32     aChar,
                  dbmSize      aSize );

dbmInt32 dbmMemcmp( void *       aValue1,
                    void *       aValue2,
                    dbmSize      aSize );


extern void dbmCopy0Bytes( void * aDest, const void * aSrc );
extern void dbmCopy1Bytes( void * aDest, const void * aSrc );
extern void dbmCopy2Bytes( void * aDest, const void * aSrc );
extern void dbmCopy3Bytes( void * aDest, const void * aSrc );
extern void dbmCopy4Bytes( void * aDest, const void * aSrc );
extern void dbmCopy5Bytes( void * aDest, const void * aSrc );
extern void dbmCopy6Bytes( void * aDest, const void * aSrc );
extern void dbmCopy7Bytes( void * aDest, const void * aSrc );
extern void dbmCopy8Bytes( void * aDest, const void * aSrc );

typedef void (*dbmCopyFunction)( void * aDest, const void * aSrc );
extern const dbmCopyFunction gDbmCopyFunc[9];

#if defined( DBM_DEBUG ) || defined( DOXYGEN )
#define dbmMemcpy( aDest, aSrc, aSize )                                         \
    {                                                                           \
        dbmUInt64 dbmMemcpySize = (dbmUInt64)(aSize);                           \
        /* aSize가 signed인 경우 양수여야 함 */                                    \
        DBM_DASSERT( (aSize) + dbmMemcpySize > 0 || aSize == 0 );               \
        /* aSize를 type casting안하면 hp에서 warning  */                          \
        DBM_DASSERT( dbmMemcpySize < DBM_INT64_C(1073741824) );                 \
        if( (dbmSize)(aSize) > (dbmSize)8 )                                     \
        {                                                                       \
            memcpy( aDest, aSrc, aSize );                                       \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            (void)gDbmCopyFunc[aSize]( aDest, aSrc );                              \
        }                                                                       \
    }
#else
#define dbmMemcpy( aDest, aSrc, aSize )                                         \
    {                                                                           \
        if( (dbmSize)(aSize) > (dbmSize)8 )                                     \
        {                                                                       \
            memcpy( aDest, aSrc, aSize );                                       \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            (void)gDbmCopyFunc[aSize]( aDest, aSrc );                              \
        }                                                                       \
    }
#endif

/** @} */
    
DBM_END_DECLS

#endif /* _DBMATOMIC_H_ */

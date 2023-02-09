#ifndef __DBM_ALLOCATOR_
#define __DBM_ALLOCATOR_ 1

#include <dbmTypes.h>
#include <dbmCommon.h>
#include <dbmDefEx.h>
#include <dbmStruct.h>

#define DBM_MEM_CHUNK_SIZE        ( 1024 * 1024 * 32 )



dbmStatus dbmCreateAllocator( dbmAllocator    ** aCtx,
                              dbmErrorStack    * aErrorStack );

dbmStatus dbmAllocMemory( dbmAllocator       * aCtx,
                          dbmInt32             aSize,
                          void              ** aRet,
                          dbmErrorStack      * aErrorStack );

dbmStatus dbmExtendAllocator( dbmAllocator     * aCtx,
                              dbmErrorStack    * aErrorStack );

void dbmResetAllocator( dbmAllocator     * aCtx );

dbmStatus dbmDropAllocator( dbmAllocator    ** aCtx,
                            dbmErrorStack    * aErrorStack );

void dbmSaveAllocator( dbmAllocator     * aCtx );

void dbmRewindAllocator( dbmAllocator     * aCtx );

void dbmClearSaveAllocator( dbmAllocator      * aCtx );



#endif


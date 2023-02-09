#ifndef __DBM_LIST_H_
#define __DBM_LIST_H_  1

#include <dbmCommon.h>
#include <dbmStruct.h>




#define DBM_LIST_GET_FIRST( aList )    ( (aList)->mHead )

#define DBM_LIST_GET_LAST( aList )    ( (aList)->mTail )

#define DBM_LIST_GET_COUNT( aList )   ( (aList)->mCount )

#define DBM_LIST_GET_POINTER_VALUE( aListElem )   ( (aListElem)->mElem )

#define DBM_LIST_GET_NEXT_ELEM( aListElem )    ( (aListElem)->mNext )

#define DBM_LIST_GET_PREV_ELEM( aListElem )    ( (aListElem)->mPrev )

#define DBM_LIST_ITERATE( aList, aElem )                                              \
    for( (aElem) = (aList->mCount == 0 ? NULL : DBM_LIST_GET_FIRST( aList )) ;        \
         (aElem) != NULL ;                                                            \
         (aElem) = DBM_LIST_GET_NEXT_ELEM( aElem ) )


#define DBM_LIST_ITERATE_REVERSE( aList, aElem )                                      \
    for( (aElem) = (aList->mCount == 0 ? NULL : DBM_LIST_GET_LAST( aList )) ;         \
         (aElem) != NULL ;                                                            \
         (aElem) = DBM_LIST_GET_PREV_ELEM( aElem ) )



dbmStatus dbmCreateList( dbmAllocator     * aCtx,
                         dbmList         ** aList,
                         dbmErrorStack    * aErrorStack );


dbmStatus dbmAddList( dbmAllocator       * aCtx,
                      dbmList            * aList,
                      dbmListElemType      aElemType,
                      void               * aElem,
                      dbmErrorStack      * aErrorStack );

dbmStatus dbmAddListNoDup( dbmAllocator       * aCtx,
                           dbmList            * aList,
                           dbmListElemType      aElemType,
                           void               * aElem,
                           dbmErrorStack      * aErrorStack );

dbmStatus dbmRemoveListElem( dbmList             * aList,
                             void                * aObject,
                             dbmErrorStack       * aErrorStack ) ;


#endif

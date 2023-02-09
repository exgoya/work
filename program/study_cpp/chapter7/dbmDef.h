/*******************************************************************************
 * dbmDef.h
 *
 * Copyright (c) 2011, SUNJESOFT Inc.
 *
 *
 * IDENTIFICATION & REVISION
 *        $Id: dbmDef.h 26745 2019-01-04 05:03:09Z mkkim $
 *
 * NOTES
 *    
 *
 ******************************************************************************/


#ifndef _DBMDEF_H_
#define _DBMDEF_H_ 1

/**
 * @file dbmDef.h
 * @brief Standard Layer Definitions
 */

#include <dbmTypes.h>

/* SQLSTATE code list */
#include <dbmSqlState.h>

/**
 * @addtogroup DBM
 * @{
 */

#ifdef __cplusplus
#define DBM_BEGIN_DECLS     extern "C" {
#define DBM_END_DECLS       }
#else
#define DBM_BEGIN_DECLS
#define DBM_END_DECLS
#endif

#ifndef DBM_DEBUG 
#define DBM_IGNORE_VALIDATION  (1)
#endif

DBM_BEGIN_DECLS

/**
 * @brief 레이어 클래스
 */
typedef enum dbmLayerClass
{
    DBM_LAYER_NONE = 0,              /**< Invalid Layer */
    DBM_LAYER_STANDARD,              /**< Standard Layer */ 
    DBM_LAYER_DATATYPE,              /**< DataType Layer */ 
    DBM_LAYER_COMMUNICATION,         /**< Communication Layer */ 
    DBM_LAYER_KERNEL,                /**< Kernel Layer */
    DBM_LAYER_SERVER_COMMUNICATION,  /**< Server Communication Layer */
    DBM_LAYER_STORAGE_MANAGER,       /**< Storage Manager Layer */
    DBM_LAYER_EXECUTION_LIBRARY,     /**< Execution Library Layer */
    DBM_LAYER_CLUSTER,               /**< Cluster Layer */
    DBM_LAYER_SQL_PROCESSOR,         /**< SQL Processor Layer */
    DBM_LAYER_PSM_PROCESSOR,         /**< PSM Processor Layer */
    DBM_LAYER_SESSION,               /**< Session Layer */
    DBM_LAYER_SERVER_LIBRARY,        /**< Server Library Layer */
    DBM_LAYER_GLIESE_LIBRARY,        /**< Glise Library */
    DBM_LAYER_GLIESE_TOOL,           /**< Gliese Tool */
    DBM_LAYER_GOLDILOCKS_LIBRARY,    /**< Goldilocks Library */
    DBM_LAYER_GOLDILOCKS_TOOL,       /**< Goldilocks Tool */
    DBM_LAYER_MAX
} dbmLayerClass;

/**
 * @brief 에러 모듈 클래스
 */
typedef enum dbmErrorModule
{
    DBM_ERROR_MODULE_NONE = 10,                /* 10 */  /**< Invalid Layer */
    DBM_ERROR_MODULE_STANDARD,                          /**< Standard Layer */ 
    DBM_ERROR_MODULE_DBM,                     /*    */  /**< dbm */
    DBM_ERROR_MODULE_GSB,                     /*    */  /**< gsb */
    DBM_ERROR_MODULE_MOM,                     /*    */  /**< mom */
    DBM_ERROR_MODULE_MAX
} dbmErrorModule;



/**
 * @brief Layer 이름이 가질수 있는 최대 길이
 */
#define DBM_MAX_LAYER_NAME  (30)


/**
 * @brief ASSERT 매크로
 */
#define DBM_ASSERT( aExpression )                       \
    do                                                  \
    {                                                   \
        if( !(aExpression) )                            \
        {                                               \
            dbmAssert( "ASSERT(%s)\n"                   \
                       "failed in file %s line %d\n",   \
                       #aExpression,                    \
                       __FILE__,                        \
                       __LINE__ );                      \
        }                                               \
    } while( 0 )

/**
 * @brief ASSERT 매크로(Hide Backtrace 용)
 */
#define DBM_SILENT_ASSERT( aExpression )                    \
    do                                                      \
    {                                                       \
        if( !(aExpression) )                                \
        {                                                   \
            dbmSilentAssert( "SILENT ASSERT(%s)\n"          \
                             "failed in file %s line %d\n", \
                             #aExpression,                  \
                             __FILE__,                      \
                             __LINE__ );                    \
        }                                                   \
    } while( 0 )

#if defined( DBM_DEBUG ) || defined( DOXYGEN )
#define DBM_DASSERT( aExpression ) DBM_ASSERT( aExpression )
#else
#define DBM_DASSERT( aExpression )
#endif

#define DBM_THROW( aLabel ) goto aLabel;

#define DBM_TRY_THROW( aExpression, aLabel )    \
    do                                          \
    {                                           \
        if( !(aExpression) )                    \
        {                                       \
            goto aLabel;                        \
        }                                       \
    } while( 0 )

#define DBM_TRY( aExpression )                  \
    do                                          \
    {                                           \
        if( !(aExpression) )                    \
        {                                       \
            goto DBM_FINISH_LABEL;              \
        }                                       \
    } while( 0 )

typedef void (*dblTraceLog)( dbmChar * aMsg, 
                             dbmChar * aFileName,
                             dbmChar * aFuncName,
                             dbmInt32  aLine );
dblTraceLog     gDblTraceLog;
#define __FILENAME__    (strrchr( __FILE__,'/')==NULL)?__FILE__:(strrchr( __FILE__,'/')+1)

#define DBM_CATCH( aLabel )                     \
    goto DBM_FINISH_LABEL;                      \
    aLabel:

#if 0
    // DBM_CATCH 에서 log를 남기기 위한거였으나 삭제함.
    // 필요시 DBM_CATCH 에 추가하면 됨
    if( gDblTraceLog != NULL ) gDblTraceLog( "DBM_CATCH \n", __FILENAME__, __LINE__ );
#endif

#define DBM_CATCH_NOLOG( aLabel )                     \
    goto DBM_FINISH_LABEL;                      \
    aLabel:

#define DBM_RAMP( aLabel ) aLabel:

#if defined( DBM_DEBUG ) || defined( DOXYGEN )
#define DBM_DEBUG_STATEMENT( aExpression )    aExpression
#else
#define DBM_DEBUG_STATEMENT( aExpression )
#endif


/**
 * @brief aExpression이 대부분 경우에 TRUE일때 사용되며, if 구문안의 명령어들이 prefetch 된다.
 */
#define DBM_EXPECT_TRUE( aExpression )    __builtin_expect( aExpression, 1 )
/**
 * @brief aExpression이 대부분 경우에 FALSE일때 사용되며, if 구문밖의 명령어들이 prefetch 된다.
 */
#define DBM_EXPECT_FALSE( aExpression )   __builtin_expect( aExpression, 0 )

#if defined( DBM_IGNORE_VALIDATION )
/*
 * DBM_FINISH에서 "goto DBM_FINISH_LABEL"을 추가한 이유는 DBM_IGNORE_VALIDATION이
 * TRUE인 상황에서의 compile warning을 제거하기 위함이다.
 */
#define DBM_FINISH                              \
    goto DBM_FINISH_LABEL;                      \
    DBM_FINISH_LABEL:
#else
#define DBM_FINISH                              \
    DBM_FINISH_LABEL:
#endif

/**
 * @brief 파라미터 유효성 검사 매크로 ( 디버그 모드에서만 프로세스를 종료시킴 )
 */
#if defined( DBM_IGNORE_VALIDATION )
#define DBM_PARAM_VALIDATE( aExpression, aErrorStack )
#else
#define DBM_PARAM_VALIDATE( aExpression, aErrorStack )          \
    do                                                          \
    {                                                           \
        if( !(aExpression) )                                    \
        {                                                       \
            dbmChar sSource[DBM_MAX_ERROR_MESSAGE];             \
            dbmSnprintf( sSource,                               \
                         DBM_MAX_ERROR_MESSAGE,                 \
                         "(%s) failed in file %s line %d",      \
                         #aExpression,                          \
                         __FILE__,                              \
                         __LINE__ );                            \
            dblPushError( DBM_ERROR_LEVEL_ABORT,                \
                          DBM_ERRCODE_INVALID_ARGUMENT,         \
                          sSource,                              \
                          aErrorStack );                        \
            DBM_DASSERT( aExpression );                         \
            goto DBM_FINISH_LABEL;                              \
        }                                                       \
    } while( 0 )
#endif
/**
 * @brief FALSE
 */
#define DBM_FALSE 0

/**
 * @brief TRUE
 */
#define DBM_TRUE  1

/**
 * @brief NO
 */
#define DBM_NO    0

/**
 * @brief YES
 */
#define DBM_YES   1

/**
 * @brief INACTIVE
 */
#define DBM_INACTIVE 0

/**
 * @brief ACTIVE
 */
#define DBM_ACTIVE 1

/**
 * @brief Maximum callstack count
 */
#define DBM_MAX_CALLSTACK_FRAME_SIZE 100

/**
 * @brief SQL 객체의 이름 길이의 최대값
 * @remark SQL표준의 SQL_IDENTIFIER 길이로 식별자 이름은 128보다 작아야 함.
 */ 
#define DBM_MAX_SQL_IDENTIFIER_BUFFER_SIZE (128)

/**
 * @brief 입력받은 크기를 @a aBoundary 크기에 맞춰 조정한다.
 * @param aSize 조절할 크기
 * @param aBoundary 정렬할 크기
 * @remark @a aBoundary 는 2의 거듭제곱이어야 한다.
 */
#define DBM_ALIGN( aSize, aBoundary )                           \
    (((aSize) + ((aBoundary) - 1)) & ~((aBoundary) - 1))

/**
 * @brief A와 B중 작은값을 얻는다.
 */
#define DBM_MIN( aA, aB )                       \
    ( ( (aA) < (aB) ) ? (aA) : (aB) )

/**
 * @brief A와 B중 큰값을 얻는다.
 */
#define DBM_MAX( aA, aB )                       \
    ( ( (aA) > (aB) ) ? (aA) : (aB) )

/**
 * @brief 입력받은 크기를 기본값(8) 크기에 맞춰 조정한다.
 */
#define DBM_ALIGN_DEFAULT( aSize ) DBM_ALIGN( aSize, 8 )

#define DBM_OFFSET(aType, aMember)                                                      \
    ((dbmSize) (((dbmChar *) (&(((aType)NULL)->aMember))) - ((dbmChar *) NULL)))

/**
 * @brief structure 안의 멤버의 offset을 구한다.
 * @param aType structure 타입 이름
 * @param aMember structure 안의 멤버 이름
 * @return offset
 */
#define DBM_OFFSETOF(aType, aMember) DBM_OFFSET(aType*, aMember)

/**
 * @brief 주어진 파라미터의 사이즈를 구한다.
 * @param aType 타입 이름
 * @return size
 */
#define DBM_SIZEOF( aType ) sizeof( aType )

/**
 * @brief 주어진 파라미터의 비트수를 구한다.
 * @param aType 타입 이름
 * @return Bit Count
 */
#define DBM_BIT_COUNT( aType ) ( 8 * DBM_SIZEOF(aType) )

/**
 * @brief PATH의 최대 길이
 */
#if defined(PATH_MAX) || defined( DOXYGEN )
#define DBM_PATH_MAX       PATH_MAX
#elif defined(_POSIX_PATH_MAX)
#define DBM_PATH_MAX       _POSIX_PATH_MAX
#else
#define DBM_PATH_MAX       1024
#endif

/**
 * @brief difference pointers
 */
#define DBM_DIFF_POINTER( aPointer1, aPointer2 )                                \
    ( DBM_INT_FROM_POINTER(aPointer1) - DBM_INT_FROM_POINTER(aPointer2) )
#define DBM_INT_FROM_POINTER( aPointer ) ( (dbmVarInt)(aPointer) )

/**
 * @brief 무한대 시간
 */
#define DBM_INFINITE_TIME ( DBM_UINT64_MAX )

/**
 * @brief Product Version Length
 */
#define DBM_PRODUCT_VERSION_LENGTH (4)

/**
 * @brief Version information
 */
typedef struct dbmVersionInfo
{
    dbmChar  mProduct[DBM_PRODUCT_VERSION_LENGTH];   /**< product version */
    dbmInt32 mMajor;        /**< major version */
    dbmInt32 mMinor;        /**< minor version */
    dbmInt32 mPatch;        /**< patch version */
    dbmInt32 mRevision;     /**< revision */
} dbmVersionInfo;
    
/** @} */

/**
 * @addtogroup dblAtomic
 * @{
 */

/**
 * @brief Memory Barrier를 설정한다.
 */
#define dbmMemBarrier()    __sync_synchronize()

/**
 * @brief aMem의 기존값이 aCmp와 같다면 aWith로 교체한다.
 * @param aMem 설정할 포인터
 * @param aWith 교체하고자 하는 32비트 정수값
 * @param aCmp 비교값
 * @return *aMem의 기존값(old value)
 */
#ifdef WIN32
#define dblAtomicCas32( aMem, aWith, aCmp )  InterlockedCompareExchange((long*)aMem, aWith, aCmp)
#else
#define dblAtomicCas32( aMem, aWith, aCmp )  __sync_val_compare_and_swap( aMem, aCmp, aWith )
#endif
/** @} */

/**
 * @addtogroup dbmAllocator
 * @{
 */

typedef struct dblAllocator
{
    dbmInt64   mInitSize;             /**< Init size */
    dbmInt64   mNextSize;             /**< Next size */
    dbmInt64   mUsedChunkCount;       /**< Used chunk count */
    dbmInt64   mTotalChunkCount;      /**< Total allocated chunk count */
    void     * mCurChunk;             /**< Current chunk */
    void     * mFirstChunk;           /**< First chunk */
    void     * mLastChunk;            /**< Last chunk */
    dbmUInt32  mAtomic;               /**< thread 동시 실행 검증용 */
} dblAllocator;

typedef struct dbmRegionMark
{
    void     * mChunk;                /**< Marked chunk */
    dbmInt64   mUsedChunkCount;       /**< Used chunk count  */
    dbmInt32   mAllocHwm;             /**< Allocated HWM(High Water Mark) */
} dbmRegionMark;

/** @} */


/**
 * @addtogroup dbmError
 * @{
 */

/**
 * @brief 에러 메세지의 최대 크기
 */
#define DBM_MAX_ERROR_MESSAGE          (512)

#define DBM_MAX_DETAIL_ERROR_MESSAGE   (1024)

/**
 * @brief LARGE 에러 메세지의 최대 크기
 */
#define DBM_MAX_LARGE_ERROR_MESSAGE    (32*1024)
/**
 * @brief 에러 스택의 최대 크기
 */
#define DBM_MAX_ERROR_STACK_DEPTH      (4)
/**
 * @brief 에러 스택의 콜스택 최대 크기
 */
#define DBM_MAX_ERROR_CALLSTACK_DEPTH  (50)
/**
 * @brief 에러 레벨
 */
typedef enum
{
    DBM_ERROR_LEVEL_FATAL = 0, /**< FATAL ERROR (서버가 운영될수 없는 수준의 에러) */
    DBM_ERROR_LEVEL_ABORT,     /**< ABORT ERROR (롤백 가능한 수준의 에러) */
    DBM_ERROR_LEVEL_WARNING,   /**< WARNING (경고 수준의 에러) */
    DBM_ERROR_LEVEL_MAX
} dbmErrorLevel;

/**
 * @brief 에러 스택 초기화
 */
#ifdef DBM_VALGRIND
#define DBM_INIT_ERROR_STACK( aErrorDataStack )                                 \
    {                                                                           \
        dbmMemset( (aErrorDataStack), 0x00, DBM_SIZEOF( dbmErrorStack ) );      \
        (aErrorDataStack)->mTop = -1;                                           \
    }
#else
#define DBM_INIT_ERROR_STACK( aErrorDataStack ) \
    {                                           \
        (aErrorDataStack)->mTop = -1;           \
    }
#endif

/*
 * Internal Error Code 구조
 * - 5자리의 10진수
 *  - 앞 두자리 : Layer 정보 (10 부터 시작)
 *  - 뒤 세자리 : Value 정보 
 */

/**
 * @brief 에러 레이어 기저 (10)
 */
#define DBM_ERROR_MODULE_BASE         (10) 

/**
 * @brief 에러 순차값 최대치 
 */
#define DBM_ERROR_MAX_VALUE_COUNT    (1000)

/**
 * @brief 에러 코드로부터 에러 레이어값을 얻는다.
 */
#define DBM_GET_ERROR_LAYER( aErrorCode )                                               \
    ( (dbmInt32) ( aErrorCode / DBM_ERROR_MAX_VALUE_COUNT ) - DBM_ERROR_MODULE_BASE )

/**
 * @brief 에러 코드로부터 에러 순차값 얻는다.
 */
#define DBM_GET_ERROR_VALUE( aErrorCode )       \
    ( aErrorCode % DBM_ERROR_MAX_VALUE_COUNT )

/**
 * @brief 에러 코드를 구성한다.
 * 에러 코드는 32비트 정수를 사용하며,
 * 상위 10비트의 레이어와 하위 22비트의 에러 순차값으로 구성된다.
 */
#define DBM_MAKE_ERRCODE( aErrorLayer, aErrorValue )                                            \
    ( aErrorValue + ( aErrorLayer + DBM_ERROR_MODULE_BASE ) * DBM_ERROR_MAX_VALUE_COUNT )

/**
 * @brief 유효하지 않은 에러 코드.
 * 잘못된 에러 코드 식별을 위해 사용됨.
 */
#define DBM_INVALID_ERROR_CODE   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_NONE, 0 )

/**
 * @brief 에러 데이터 구조
 */
typedef struct dbmErrorData
{
    dbmErrorLevel mErrorLevel;                                       /**< 에러 레벨 */
    dbmUInt32     mExternalErrorCode;                                /**< External Error Code */
    dbmUInt32     mErrorCode;                                        /**< 에러 코드 */
    dbmChar       mErrorMessage[DBM_MAX_ERROR_MESSAGE];              /**< 기본 에러 메세지 */
    dbmChar       mDetailErrorMessage[DBM_MAX_DETAIL_ERROR_MESSAGE]; /**< 자세한 에러 메세지 */
} dbmErrorData;

/**
 * @brief 에러 스택 구조
 */
typedef struct dbmErrorStack
{
    dbmInt32       mTop;                                            /**< 스택 Top을 가리킴 */
    dbmInt32       mCallStackFrameCount;                            /**< mErrorCallstack에 저장된 프레임 개수 */
    dbmErrorData   mErrorData[DBM_MAX_ERROR_STACK_DEPTH];           /**< 에러 데이터의 배열 */
    void         * mErrorCallStack[DBM_MAX_ERROR_CALLSTACK_DEPTH];  /**< 콜스택 프레임 배열 */
} dbmErrorStack;

/**
 * @brief 에러 레코드 구조.
 * dbmErrorTable에 한개의 레코드를 표현한다.
 */
typedef struct dbmErrorRecord
{
    dbmUInt32   mExternalErrorCode;    /**< 내부 에러코드와 매핑되는 외부 에러코드 */
    dbmChar   * mErrorMessage;         /**< 내부 에러코드의 에러 메세지 */
} dbmErrorRecord;

extern dbmErrorRecord * gDbmLayerErrorTables[DBM_ERROR_MODULE_MAX];

typedef enum dbmPrintErrorLevel
{
    DBM_PRINT_ERROR_LEVEL_CODE,               /** error code */
    DBM_PRINT_ERROR_LEVEL_MESSAGE,            /** error code + error message */
    DBM_PRINT_ERROR_LEVEL_DETAIL_MESSAGE      /** error code + error message + detail message */
} dbmPrintErrorLevel;

/**
 * @brief 주어진 aErrorStack에 에러 데이터를 가지고 있는 검사한다.
 */
#define DBM_HAS_ERROR( aErrorStack )   ( (aErrorStack)->mTop > -1 )

/**
 * @defgroup dbmInternalErrorCode Internal Error Codes
 * @ingroup dbmError
 * @{
 */
/**
 * @brief invalid argument error
 */
#define DBM_ERRCODE_INVALID_ARGUMENT       DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 0 )
/**
 * @brief operation incomplete error
 */
#define DBM_ERRCODE_INCOMPLETE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 1 )
/**
 * @brief access denied error
 */
#define DBM_ERRCODE_ACCESS                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 2 )
/**
 * @brief end of file error
 */
#define DBM_ERRCODE_EOF                    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 3 )
/**
 * @brief duplicate file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_DUP               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 4 )
/**
 * @brief lock file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_LOCK              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 5 )
/**
 * @brief unlock file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_UNLOCK            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 6 )
/**
 * @brief open file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_OPEN              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 7 )
/**
 * @brief close file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_CLOSE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 8 )
/**
 * @brief remove file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_REMOVE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 9 )
/**
 * @brief link file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_LINK              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 10 )
/**
 * @brief read file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_READ              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 11 )
/**
 * @brief write file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_WRITE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 12 )
/**
 * @brief sync(flush) file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_SYNC              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 13 )
/**
 * @brief seek file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_SEEK              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 14 )
/**
 * @brief truncate file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_TRUNCATE          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 15 )
/**
 * @brief dbat file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_STAT              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 16 )
/**
 * @brief create pipe error (대표 에러)
 */
#define DBM_ERRCODE_PIPE                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 17 )
/**
 * @brief wait process error (대표 에러)
 */
#define DBM_ERRCODE_PROC_WAIT              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 18 )
/**
 * @brief insufficient resource error
 */
#define DBM_ERRCODE_INSUFFICIENT_RESOURCE  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 19 )
/**
 * @brief kill signal error (대표 에러)
 */
#define DBM_ERRCODE_SIGNAL_KILL            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 20 )
/**
 * @brief set signal handler error (대표 에러)
 */
#define DBM_ERRCODE_SIGNAL_SET_HANDLER     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 21 )
/**
 * @brief block signal error (대표 에러)
 */
#define DBM_ERRCODE_SIGNAL_BLOCK           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 22 )
/**
 * @brief set thread attribute error (대표 에러)
 */
#define DBM_ERRCODE_THREAD_ATTR            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 23 )
/**
 * @brief create thread error (대표 에러)
 */
#define DBM_ERRCODE_THREAD_CREATE          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 24 )
/**
 * @brief join thread error (대표 에러)
 */
#define DBM_ERRCODE_THREAD_JOIN            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 25 )
/**
 * @brief set thread once error (대표 에러)
 */
#define DBM_ERRCODE_THREAD_ONCE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 26 )
/**
 * @brief dbring truncation error
 */
#define DBM_ERRCODE_STRING_TRUNCATION      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 27 )
/**
 * @brief name too long error
 */
#define DBM_ERRCODE_NAMETOOLONG            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 28 )
/**
 * @brief shared memory segment exist error
 */
#define DBM_ERRCODE_SHM_EXIST              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 29 )
/**
 * @brief create shared memory error (대표 에러)
 */
#define DBM_ERRCODE_SHM_CREATE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 30 )
/**
 * @brief attach shared memory error (대표 에러)
 */
#define DBM_ERRCODE_SHM_ATTACH             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 31 )
/**
 * @brief detach shared memory error (대표 에러)
 */
#define DBM_ERRCODE_SHM_DETACH             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 32 )
/**
 * @brief destroy shared memory error (대표 에러)
 */
#define DBM_ERRCODE_SHM_DESTROY            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 33 )
/**
 * @brief create semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_CREATE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 34 )
/**
 * @brief acquire semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_ACQUIRE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 35 )
/**
 * @brief release semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_RELEASE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 36 )
/**
 * @brief destroy semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_DESTROY            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 37 )
/**
 * @brief resource busy error
 */
#define DBM_ERRCODE_BUSY                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 38 )
/**
 * @brief timed-out error
 */
#define DBM_ERRCODE_TIMEDOUT               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 39 )
/**
 * @brief no entry error
 */
#define DBM_ERRCODE_NO_ENTRY               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 40 )
/**
 * @brief mismatch error
 */
#define DBM_ERRCODE_MISMATCH               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 41 )
/**
 * @brief out of memory error
 */
#define DBM_ERRCODE_OUT_OF_MEMORY          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 42 )
/**
 * @brief disk full error
 */
#define DBM_ERRCODE_DISK_FULL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 43 )
/**
 * @brief execute process error (대표 에러)
 */
#define DBM_ERRCODE_PROC_EXECUTE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 44 )
/* By Network I/O */
#define DBM_ERRCODE_NOTSUPPORT             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 45 )
#define DBM_ERRCODE_NOSPACE                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 46 )
#define DBM_ERRCODE_INET_PTON_INVAL        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 47 )
#define DBM_ERRCODE_SENDTO                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 48 )
#define DBM_ERRCODE_RECVFROM               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 49 )
#define DBM_ERRCODE_GETSOCKNAME            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 50 )
#define DBM_ERRCODE_GETPEERNAME            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 51 )
#define DBM_ERRCODE_FCNTL                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 52 )
#define DBM_ERRCODE_SETSOCKOPT             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 53 )
#define DBM_ERRCODE_NOTIMPL                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 54 )
#define DBM_ERRCODE_IOCTL                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 55 )
#define DBM_ERRCODE_GETHOSTNAME            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 56 )
#define DBM_ERRCODE_SOCKET_CLOSE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 57 )
#define DBM_ERRCODE_SOCKET_SHUTDOWN        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 58 )
#define DBM_ERRCODE_SOCKET                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 59 )
#define DBM_ERRCODE_GETFD                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 60 )
#define DBM_ERRCODE_SETFD                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 61 )
#define DBM_ERRCODE_BIND                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 62 )
#define DBM_ERRCODE_LISTEN                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 63 )
#define DBM_ERRCODE_ACCEPT                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 64 )
#define DBM_ERRCODE_INTR                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 65 )
#define DBM_ERRCODE_GETSOCKOPT             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 66 )
#define DBM_ERRCODE_CONNECT                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 67 )
#define DBM_ERRCODE_POLL                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 68 )
#define DBM_ERRCODE_INTERNAL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 69 )
#define DBM_ERRCODE_SENDMSG                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 70 )
#define DBM_ERRCODE_RECVMSG                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 71 )
#define DBM_ERRCODE_SOCKETPAIR             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 72 )
/**
 * @brief range overflow or underflow
 */
#define DBM_ERRCODE_OUT_OF_RANGE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 73 )
/**
 * @brief dbring is not number
 */
#define DBM_ERRCODE_STRING_IS_NOT_NUMBER   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 74 )
/**
 * @brief bad file error
 */
#define DBM_ERRCODE_FILE_BAD               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 75 )
/**
 * @brief again error
 */
#define DBM_ERRCODE_AGAIN                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 76 )
/**
 * @brief The given address is already in use
 */
#define DBM_ERRCODE_ADDR_INUSE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 77 )
/**
 * @brief fail to initialize communication context
 */
#define DBM_ERRCODE_INITIALIZE_CONTEXT     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 78 )
/**
 * @brief fail to finalize communication context
 */
#define DBM_ERRCODE_FINALIZE_CONTEXT       DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 79 )
/**
 * @brief fail to connect communication context
 */
#define DBM_ERRCODE_CONNECT_CONTEXT        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 80 )
/**
 * @brief fail to poll communication context
 */
#define DBM_ERRCODE_POLL_CONTEXT           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 81 )
/**
 * @brief fail to write packet through communication context
 */
#define DBM_ERRCODE_WRITE_PACKET           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 82 )
/**
 * @brief fail to read packet through communication context
 */
#define DBM_ERRCODE_READ_PACKET            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 83 )
/**
 * @brief fail to send descriptor through communication context
 */
#define DBM_ERRCODE_SEND_CONTEXT           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 84 )
/**
 * @brief fail to receive descriptor through communication context
 */
#define DBM_ERRCODE_RECV_CONTEXT           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 85 )
/**
 * @brief fail to get current file path (대표 에러)
 */
#define DBM_ERRCODE_FILE_PATH              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 86 )
/**
 * @brief fail to open library (대표 에러)
 */
#define DBM_ERRCODE_OPEN_LIBRARY           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 87 )
/**
 * @brief fail to close library (대표 에러)
 */
#define DBM_ERRCODE_CLOSE_LIBRARY          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 88 )
/**
 * @brief fail to get symbol (대표 에러)
 */
#define DBM_ERRCODE_GET_SYMBOL             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 89 )
/**
 * @brief query is not supported
 */
#define DBM_ERRCODE_PARSER_NOTSUPPORT      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 90 )
/**
 * @brief open file error (대표 에러)
 */
#define DBM_ERRCODE_FILE_EXIST             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 91 )
/**
 * @brief input is too long
 */
#define DBM_ERRCODE_PARSER_INPUT_TOO_LONG  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 92 )
/**
 * @brief system call error 
 */
#define DBM_ERRCODE_PARSER_SYSTEM_CALL_ERROR DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 93 )
/**
 * @brief divide zero 
 */
#define DBM_ERRCODE_PARSER_DIVIDE_ZERO DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 94 )
/**
 * @brief open semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_OPEN               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 96 )
/**
 * @brief close semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_CLOSE              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 96 )
/**
 * @brief unlink semaphore error (대표 에러)
 */
#define DBM_ERRCODE_SEM_UNLINK             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 97 )
/**
 * @brief permission denied - '%s'
 */
#define DBM_ERRCODE_ACCESS_FILE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 98 )
/**
 * @brief not supported os
 */
#define DBM_ERRCODE_OS_NOTSUPPORT          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 99 )
/**
 * @brief Environment Variable '%s' is not defined
 */
#define DBM_ERRCODE_UNDEFINED_ENV_VARIABLE DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 100 )
/**
 * @brief License file(%s) is not exist
 */
#define DBM_ERRCODE_NOT_EXIST_LICENSE      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 101 )
/**
 * @brief License is out of date. License is valid after %d-%d-%d
 */
#define DBM_ERRCODE_LICENSE_OUT_OF_DATE    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 102 )
/**
 * @brief License date is expired. License is expired in %d-%d-%d
 */
#define DBM_ERRCODE_EXPIRED_LICENSE        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 103 )
/**
 * @brief License core count mismatch.
 */
#define DBM_ERRCODE_MISMATCH_CORECOUNT     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 104 )
/**
 * @brief License key is corrupted.
 */
#define DBM_ERRCODE_INVALID_LICENSE_KEY    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 105 )
/**
 * @brief License host name mismatch.
 */
#define DBM_ERRCODE_MISMATCH_HOSTNAME      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 106 )
/**
 * @brief failed to set thread affinity.
 */
#define DBM_ERRCODE_SET_THREAD_AFFINITY    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 107 )
/**
 * @brief failed to creeate timer
 */
#define DBM_ERRCODE_CREATE_TIMER           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 108 )
/**
 * @brief failed to set timer
 */
#define DBM_ERRCODE_SET_TIMER              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 109 )
/**
 * @brief failed to destroy timer
 */
#define DBM_ERRCODE_DESTROY_TIMER          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 110 )
/**
 * @brief address is not given
 */
#define DBM_ERRCODE_ADDR_NOTGIVEN          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 111 )
/**
 * @brief Unable to access the message queue
 */
#define DBM_ERRCODE_MSGQ_ACCESS            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 112 )
/**
 * @brief A message queue exists
 */
#define DBM_ERRCODE_MSGQ_EXIST             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 113 )
/**
 * @brief Unable to create a message queue
 */
#define DBM_ERRCODE_MSGQ_CREATE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 114 )
/**
 * @brief The message queue was removed
 */
#define DBM_ERRCODE_MSGQ_REMOVED           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 115 )
/**
 * @brief Unable to destroy the message queue
 */
#define DBM_ERRCODE_MSGQ_DESTROY           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 116 )
/**
 * @brief Unable to send message
 */
#define DBM_ERRCODE_MSGQ_SEND              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 117 )
/**
 * @brief Unable to receive message
 */
#define DBM_ERRCODE_MSGQ_RECV              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 118 )
/**
 * @brief No message was available in the message queue
 */
#define DBM_ERRCODE_MSGQ_AGAIN             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 119 )
/**
 * @brief fail to get property of a file dbatus
 */
#define DBM_ERRCODE_GETFL                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 120 )
/**
 * @brief fail to set property of a file dbatus
 */
#define DBM_ERRCODE_SETFL                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 121 )
/**
 * @brief infiniband verbs returned error
 */
#define DBM_ERRCODE_IBV_VERBS_FAILURE      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 122 )
/**
 * @brief no infiniband device was found
 */
#define DBM_ERRCODE_NO_IB_DEVICE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 123 )
/**
 * @brief cannot find specified infiniband device
 */
#define DBM_ERRCODE_CANNOT_FIND_IB_DEVICE  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 124 )
/**
 * @brief cannot find suitable Memory Region for specified ptr and size
 */
#define DBM_ERRCODE_CANNOT_FIND_MEMORY_REGION  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 125 )
/**
 * @brief fail to get semaphore value (대표 에러)
 */
#define DBM_ERRCODE_SEM_GET_VALUE              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 126 )
/**
 * @brief fail to control pollset
 */
#define DBM_ERRCODE_POLLSET_CTRL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 127 )
/**
 * @brief fail to create pollset
 */
#define DBM_ERRCODE_POLLSET_CREATE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 128 )
/**
 * @brief overflow fd
 */
#define DBM_ERRCODE_OVERFLOW_FD                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 129 )
/**
 * @brief invalid INI file format
 */
#define DBM_ERRCODE_INVALID_INI_FILE_FORMAT    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 130 )
/**
 * @brief path '%s' does not exist
 */
#define DBM_ERRCODE_PATH_EXIST                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 131 )

/**
 * @brief Unable to get maximum undo semaphores per array
 */
#define DBM_ERRCODE_UNDO_SEM_GET_MAX_SEMS      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 132 )

/**
 * @brief Unable to create a undo semaphore
 */
#define DBM_ERRCODE_UNDO_SEM_CREATE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 133 )

/**
 * @brief Unable to bind the given undo semaphore
 */
#define DBM_ERRCODE_UNDO_SEM_BIND              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 134 )

/**
 * @brief Unable to unbind the given undo semaphore
 */
#define DBM_ERRCODE_UNDO_SEM_UNBIND            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 135 )

/**
 * @brief Unable to get the given undo semaphore dbate
 */
#define DBM_ERRCODE_UNDO_SEM_GET_STATE         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 136 )

/**
 * @brief Unable to destroy the given undo semaphore
 */
#define DBM_ERRCODE_UNDO_SEM_DESTROY           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 137 )

/**
 * @brief Unable to suspend asyncronous io
 */
#define DBM_ERRCODE_ASYNC_SUSPEND_FILE         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 138 )

/**
 * @brief Unable to control the shared memory segment
 */
#define DBM_ERRCODE_SHM_CONTROL                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 139 )

/**
 * @brief detach thread error (대표 에러)
 */
#define DBM_ERRCODE_THREAD_DETACH              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 140 )

#define DBM_ERRCODE_COMMUNICATION_LINK_FAILURE DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 141 )

/**
 * @brief No such process
 */ 
#define DBM_ERRCODE_NO_PROCESS                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_STANDARD, 142 )

#define DBM_MAX_ERROR     143

/** @} */

/** @} */

/**
 * @addtogroup dbmFile
 * @{
 */

/**
 * @brief Direct IO Block Size
 */
#define DBM_DIRECT_IO_DEFAULT_BLOCKSIZE   (512)
/**
 * @brief 파일 이름의 최대 크기
 */
#define DBM_MAX_FILE_NAME_LENGTH 128
/**
 * @brief 파일 경로(+이름)의 최대 크기
 */
#define DBM_MAX_FILE_PATH_LENGTH 1024
/**
 * @brief BULK I/O의 최대 바이트수
 */
#define DBM_BULK_IO_BYTES        (32*1024*1024)

/**
 * @brief unix domain socket path(name포함)의 최대 크기
 */
#define DBM_MAX_UDS_PATH         (91)

/**
 * @brief unix domain socket directory의 최대 크기
 */
#define DBM_MAX_UDS_DIR          (50)

/**
 * @brief Polling Method for checking Async IO Completion
 */
#define DBM_AIO_COMPLETE_METHOD_POLLING ( 1 )
/**
 * @brief Suspend Method for checking Async IO Completion
 */
#define DBM_AIO_COMPLETE_METHOD_SUSPEND ( 2 )

/**
 * @defgroup dbmFileInfoFlags File Information Flags
 * @ingroup dbmFile
 * @{
 */
#define DBM_FINFO_LINK   0x00000001 /**< Stat the link not the file itself if it is a link */
#define DBM_FINFO_MTIME  0x00000010 /**< Modification Time */
#define DBM_FINFO_CTIME  0x00000020 /**< Creation or inode-changed time */
#define DBM_FINFO_ATIME  0x00000040 /**< Access Time */
#define DBM_FINFO_SIZE   0x00000100 /**< Size of the file */
#define DBM_FINFO_ASIZE  0x00000200 /**< Storage size consumed by the file */
#define DBM_FINFO_DEV    0x00001000 /**< Device */
#define DBM_FINFO_INODE  0x00002000 /**< Inode */
#define DBM_FINFO_NLINK  0x00004000 /**< Number of links */
#define DBM_FINFO_TYPE   0x00008000 /**< Type */
#define DBM_FINFO_USER   0x00010000 /**< User */
#define DBM_FINFO_GROUP  0x00020000 /**< Group */
#define DBM_FINFO_UPROT  0x00100000 /**< User protection bits */
#define DBM_FINFO_GPROT  0x00200000 /**< Group protection bits */
#define DBM_FINFO_WPROT  0x00400000 /**< World protection bits */

#define DBM_FINFO_MIN    0x00008170 /**< type, mtime, ctime, atime, size */
#define DBM_FINFO_IDENT  0x00003000 /**< dev and inode */
#define DBM_FINFO_OWNER  0x00030000 /**< user and group */
#define DBM_FINFO_PROT   0x00700000 /**< all protections */
#define DBM_FINFO_NORM   0x0073b170 /**< platform-independent flags (all flags - INODE - CSIZE) */
/** @} */

typedef enum
{
    DBM_FTYPE_NOFILE = 0,     /**< no file type determined */
    DBM_FTYPE_REG,            /**< a regular file */
    DBM_FTYPE_DIR,            /**< a directory */
    DBM_FTYPE_CHR,            /**< a character device */
    DBM_FTYPE_BLK,            /**< a block device */
    DBM_FTYPE_PIPE,           /**< a FIFO / pipe */
    DBM_FTYPE_LNK,            /**< a symbolic link */
    DBM_FTYPE_SOCK,           /**< a [unix domain] socket */
    DBM_FTYPE_UNKFILE = 127   /**< a file of some other unknown type */
} dbmFileType; 

/**
 * @defgroup dbmFileLockFlags File Lock Flags
 * @ingroup dbmFile
 * @{
 */
#define DBM_FLOCK_SHARED        1       /**< Shared lock. More than one process
                                           or thread can hold a shared lock
                                           at any given time. Essentially,
                                           this is a "read lock", preventing
                                           writers from establishing an
                                           exclusive lock. */
#define DBM_FLOCK_EXCLUSIVE     2       /**< Exclusive lock. Only one process
                                           may hold an exclusive lock at any
                                           given time. This is analogous to
                                           a "write lock". */

#define DBM_FLOCK_TYPEMASK      0x000F  /**< mask to extract lock type */
#define DBM_FLOCK_NONBLOCK      0x0010  /**< do not block while acquiring the
                                           file lock */
/** @} */

/**
 * @defgroup dbmPermFlags Permission Flags
 * @ingroup dbmFile
 * @{
 */
#define DBM_PERM_USETID             0x8000 /**< Set user id */
#define DBM_PERM_UREAD              0x0400 /**< Read by user */
#define DBM_PERM_UWRITE             0x0200 /**< Write by user */
#define DBM_PERM_UEXECUTE           0x0100 /**< Execute by user */

#define DBM_PERM_GSETID             0x4000 /**< Set group id */
#define DBM_PERM_GREAD              0x0040 /**< Read by group */
#define DBM_PERM_GWRITE             0x0020 /**< Write by group */
#define DBM_PERM_GEXECUTE           0x0010 /**< Execute by group */

#define DBM_PERM_WSTICKY            0x2000 /**< Sticky bit */
#define DBM_PERM_WREAD              0x0004 /**< Read by others */
#define DBM_PERM_WWRITE             0x0002 /**< Write by others */
#define DBM_PERM_WEXECUTE           0x0001 /**< Execute by others */

#define DBM_PERM_DEFAULT            0x0FFF /**< use default permissions */

#define DBM_PERM_SHM_DEFAULT        ( 0600 )            /** SharedMemory에서 DBM_FPERM_DEFAULT 시 실제 적용되는 value */
#define DBM_PERM_MSGQ_DEFAULT       ( 0660 )            /** Message Queue에서 DBM_FPERM_DEFAULT 시 실제 적용되는 value */
#define DBM_PERM_SEMAPHORE_DEFAULT  ( 0600 )            /** Semaphore에서 DBM_FPERM_DEFAULT 시 실제 적용되는 value */
#define DBM_PERM_FILE_DEFAULT       ( 0600 )            /** File에서 DBM_FPERM_DEFAULT 시 실제 적용되는 value */

/* additional permission flags for dbmCopyFile  and dbmAppendFile */
#define DBM_FPERM_FILE_SOURCE 0x1000 /**< Copy source file's permissions */
/** @} */

/**
 * @defgroup dbmFileOpenFlags File Open Flags
 * @ingroup dbmFile
 * @{
 */
#define DBM_FOPEN_READ       0x00001  /**< Open the file for reading */
#define DBM_FOPEN_WRITE      0x00002  /**< Open the file for writing */
#define DBM_FOPEN_CREATE     0x00004  /**< Create the file if not there */
#define DBM_FOPEN_APPEND     0x00008  /**< Append to the end of the file */
#define DBM_FOPEN_TRUNCATE   0x00010  /**< Open the file and truncate
                                           to 0 length */
#define DBM_FOPEN_BINARY     0x00020  /**< Open the file in binary mode */
#define DBM_FOPEN_EXCL       0x00040  /**< Open should fail if DBM_FOPEN_CREATE
                                           and file exists. */
#define DBM_FOPEN_DIRECT     0x00080  /**< Open the file in direct mode */
#define DBM_FOPEN_LARGEFILE  0x04000  /**< Platform dependent flag to enable
                                       * large file support, see WARNING below
                                       */
/** @} */

/**
 * @defgroup dbmControlFileDescriptorFlags Control File Descriptor Flags
 * @ingroup dbmFile
 * @{
 */
#define DBM_FDCTL_GETFD      0x01     /**< get file descriptor flags */
#define DBM_FDCTL_SETFD      0x02     /**< set file descriptor flags */

#define DBM_FDCTL_CLOEXEC    0x01     /**< close on exec */

/** @} */


/**
 * @defgroup dbmFileSeekFlags File Seek Flags
 * @ingroup dbmFile
 * @{
 */
#define DBM_FSEEK_SET SEEK_SET          /**< Set the file position */
#define DBM_FSEEK_CUR SEEK_CUR          /**< Current file position */
#define DBM_FSEEK_END SEEK_END          /**< Go to end of file */
/** @} */

/**
 * @defgroup dbmFileAttrFlags File Attribute Flags
 * @ingroup dbmFile
 * @{
 */
/* flags for apr_file_attrs_set */
#define DBM_FATTR_READONLY   0x01       /**< File is read-only */
#define DBM_FATTR_EXECUTABLE 0x02       /**< File is executable */
#define DBM_FATTR_HIDDEN     0x04       /**< File is hidden */
/** @} */

/**
 * @brief The file information structure.
 * This is analogous to the POSIX dbat structure.
 */
typedef struct dbmFileInfo
{
    dbmInt32     mValid;                /**< The bitmask describing
                                             valid fields of this structure */
    dbmInt32     mProtection;           /**< The access permissions of the file */
    dbmFileType  mFileType;             /**< The type of file */
    dbmUserID    mUserID;               /**< The user id that owns the file */
    dbmGroupID   mGroupID;              /**< The group id that owns the file */
    dbmInode     mInodeNumber;          /**< The inode of the file */
    dbmDeviceID  mDeviceID;             /**< The id of the device the file is on */
    dbmInt32     mLinks;                /**< The number of hard links to the file */
    dbmOffset    mSize;                 /**< The size of the file */
    dbmOffset    mAllocatedSize;        /**< The dborage size consumed by the file */
    dbmTime      mLastAccessedTime;     /**< The time the file was last accessed */
    dbmTime      mLastModifiedTime;     /**< The time the file was last modified */
    dbmTime      mCreateTime;           /**< The time the file was created,
                                             or the inode was last changed */
} dbmFileInfo;

/**
 * @brief async io job의 최대 개수
 */
#define DBM_MAX_AIO_JOB_COUNT  ( 8 )

/** @} */

/**
 * @addtogroup dbmGeneral
 * @{
 */

/**
 * @brief Startup시 StartupInfo를 위한 공유메모리 Seed Key
 */
#define DBM_STARTUP_MSG_KEY  (22581)
/**
 * OS default time-slice time(ms)
 */
#define DBM_TIMESLICE_TIME   (10000)

/** @} */

/**
 * @addtogroup dbmXid
 * @{
 */

#define DBM_XID_DATA_SIZE    ( 128 )  /**< Xid.mData field size */
#define DBM_XID_TRANS_SIZE   ( 64 )   /**< Xid.mData의 global tranaction id field size */
#define DBM_XID_BRANCH_SIZE  ( 64 )   /**< Xid.mData의 branch qualifier field size */

/**
 * @brief XID structure
 */
typedef struct dbmXid
{
    dbmInt64   mFormatId;                 /**< format identifier */
    dbmInt64   mTransLength;              /**< byte length of global transaction identifier */
    dbmInt64   mBranchLength;             /**< byte length of branch qualifier identifier */
    dbmChar    mData[DBM_XID_DATA_SIZE];  /**< actual data */
} dbmXid;

/**
 * @brief maximum XID dbring size
 */
#define DBM_XID_STRING_SIZE   ( DBM_XID_DATA_SIZE * 2 + 64 )

/** @} */

/**
 * @addtogroup dbmMemorys
 * @{
 */

/**
 * @brief 8비트 aSrc를 aDest에 저장한다.
 */
#define DBM_WRITE_INT8( aDest, aSrc )                   \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
    }

/**
 * @brief 8비트 aSrc를 0 으로 설정한다.
 */
#define DBM_WRITE_ZERO_INT8( aDest )                    \
    {                                                   \
        ((dbmChar*)(aDest))[0] = (dbmChar)(0);          \
    }

/**
 * @brief (aSrc + aOffset)의 8비트를 aDest에 저장하고, aOffset을 증가한다.
 */
#define DBM_READ_MOVE_INT8( aDest, aSrc, aOffset )      \
    {                                                   \
        DBM_WRITE_INT8( aDest, aSrc + aOffset );        \
        aOffset += 1;                                   \
    }

/**
 * @brief aSrc의 8비트를 (aDest + aOffset)에 저장하고, aOffset을 증가한다.
 */
#define DBM_WRITE_MOVE_INT8( aDest, aSrc, aOffset )     \
    {                                                   \
        DBM_WRITE_INT8( aDest + aOffset, aSrc );        \
        aOffset += 1;                                   \
    }

/**
 * @brief 16비트 aSrc를 aDest에 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_INT16( aDest, aSrc )                  \
    {                                                   \
        *(dbmUInt16*)(aDest) = *(dbmUInt16*)(aSrc);     \
    }
#else
#define DBM_WRITE_INT16( aDest, aSrc )                  \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
        ((dbmChar*)(aDest))[1] = ((dbmChar*)(aSrc))[1]; \
    }
#endif

/**
 * @brief 16비트 aDest에 0 을 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_ZERO_INT16( aDest )                   \
    {                                                   \
        *(dbmUInt16*)(aDest) = (dbmUInt16)(0);          \
    }
#else
#define DBM_WRITE_ZERO_INT16( aDest )                   \
    {                                                   \
        ((dbmChar*)(aDest))[0] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[1] = (dbmChar)(0);          \
    }
#endif

/**
 * @brief (aSrc + aOffset)의 16비트를 aDest에 저장하고, aOffset을 증가한다.
 */
#define DBM_READ_MOVE_INT16( aDest, aSrc, aOffset )     \
    {                                                   \
        DBM_WRITE_INT16( aDest, aSrc + aOffset );       \
        aOffset += 2;                                   \
    }

/**
 * @brief aSrc의 16비트를 (aDest + aOffset)에 저장하고, aOffset을 증가한다.
 */
#define DBM_WRITE_MOVE_INT16( aDest, aSrc, aOffset )    \
    {                                                   \
        DBM_WRITE_INT16( aDest + aOffset, aSrc );       \
        aOffset += 2;                                   \
    }

/**
 * @brief 32비트 aSrc를 aDest에 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_INT32( aDest, aSrc )                  \
    {                                                   \
        *(dbmUInt32*)(aDest) = *(dbmUInt32*)(aSrc);     \
    }
#else
#define DBM_WRITE_INT32( aDest, aSrc )                  \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
        ((dbmChar*)(aDest))[1] = ((dbmChar*)(aSrc))[1]; \
        ((dbmChar*)(aDest))[2] = ((dbmChar*)(aSrc))[2]; \
        ((dbmChar*)(aDest))[3] = ((dbmChar*)(aSrc))[3]; \
    }
#endif

/**
 * @brief 32비트 aDest에 0 을 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_ZERO_INT32( aDest )                   \
    {                                                   \
        *(dbmUInt32*)(aDest) = (dbmUInt32)(0);          \
    }
#else
#define DBM_WRITE_ZERO_INT32( aDest )                   \
    {                                                   \
        ((dbmChar*)(aDest))[0] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[1] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[2] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[3] = (dbmChar)(0);          \
    }
#endif

/**
 * @brief (aSrc + aOffset)의 32비트를 aDest에 저장하고, aOffset을 증가한다.
 */
#define DBM_READ_MOVE_INT32( aDest, aSrc, aOffset )     \
    {                                                   \
        DBM_WRITE_INT32( aDest, aSrc + aOffset );       \
        aOffset += 4;                                   \
    }

/**
 * @brief aSrc의 32비트를 (aDest + aOffset)에 저장하고, aOffset을 증가한다.
 */
#define DBM_WRITE_MOVE_INT32( aDest, aSrc, aOffset )    \
    {                                                   \
        DBM_WRITE_INT32( aDest + aOffset, aSrc );       \
        aOffset += 4;                                   \
    }

/**
 * @brief 64비트 aSrc를 aDest에 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_INT64( aDest, aSrc )                  \
    {                                                   \
        *(dbmUInt64*)(aDest) = *(dbmUInt64*)(aSrc);     \
    }
#else
#define DBM_WRITE_INT64( aDest, aSrc )                  \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
        ((dbmChar*)(aDest))[1] = ((dbmChar*)(aSrc))[1]; \
        ((dbmChar*)(aDest))[2] = ((dbmChar*)(aSrc))[2]; \
        ((dbmChar*)(aDest))[3] = ((dbmChar*)(aSrc))[3]; \
        ((dbmChar*)(aDest))[4] = ((dbmChar*)(aSrc))[4]; \
        ((dbmChar*)(aDest))[5] = ((dbmChar*)(aSrc))[5]; \
        ((dbmChar*)(aDest))[6] = ((dbmChar*)(aSrc))[6]; \
        ((dbmChar*)(aDest))[7] = ((dbmChar*)(aSrc))[7]; \
    }
#endif

/**
 * @brief 64비트 aDest에 0 을 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_ZERO_INT64( aDest )                   \
    {                                                   \
        *(dbmUInt64*)(aDest) = (dbmUInt64)(0);          \
    }
#else
#define DBM_WRITE_ZERO_INT64( aDest )                   \
    {                                                   \
        ((dbmChar*)(aDest))[0] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[1] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[2] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[3] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[4] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[5] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[6] = (dbmChar)(0);          \
        ((dbmChar*)(aDest))[7] = (dbmChar)(0);          \
    }
#endif

/**
 * @brief (aSrc + aOffset)의 32비트를 aDest에 저장하고, aOffset을 증가한다.
 */
#define DBM_READ_MOVE_INT64( aDest, aSrc, aOffset )     \
    {                                                   \
        DBM_WRITE_INT64( aDest, aSrc + aOffset );       \
        aOffset += 8;                                   \
    }

/**
 * @brief aSrc의 64비트를 (aDest + aOffset)에 저장하고, aOffset을 증가한다.
 */
#define DBM_WRITE_MOVE_INT64( aDest, aSrc, aOffset )    \
    {                                                   \
        DBM_WRITE_INT64( aDest + aOffset, aSrc );       \
        aOffset += 8;                                   \
    }

/**
 * @brief 32비트 Float aSrc를 aDest에 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_FLOAT32( aDest, aSrc )                \
    {                                                   \
        *(dbmFloat32*)(aDest) = *(dbmFloat32*)(aSrc);   \
    }
#else
#define DBM_WRITE_FLOAT32( aDest, aSrc )                \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
        ((dbmChar*)(aDest))[1] = ((dbmChar*)(aSrc))[1]; \
        ((dbmChar*)(aDest))[2] = ((dbmChar*)(aSrc))[2]; \
        ((dbmChar*)(aDest))[3] = ((dbmChar*)(aSrc))[3]; \
    }
#endif

/**
 * @brief 64비트 Float aSrc를 aDest에 저장한다.
 */
#ifdef DBM_SUPPORT_MISSALIGNED_ADDRESS
#define DBM_WRITE_FLOAT64( aDest, aSrc )                \
    {                                                   \
        *(dbmFloat64*)(aDest) = *(dbmFloat64*)(aSrc);   \
    }
#else
#define DBM_WRITE_FLOAT64( aDest, aSrc )                \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
        ((dbmChar*)(aDest))[1] = ((dbmChar*)(aSrc))[1]; \
        ((dbmChar*)(aDest))[2] = ((dbmChar*)(aSrc))[2]; \
        ((dbmChar*)(aDest))[3] = ((dbmChar*)(aSrc))[3]; \
        ((dbmChar*)(aDest))[4] = ((dbmChar*)(aSrc))[4]; \
        ((dbmChar*)(aDest))[5] = ((dbmChar*)(aSrc))[5]; \
        ((dbmChar*)(aDest))[6] = ((dbmChar*)(aSrc))[6]; \
        ((dbmChar*)(aDest))[7] = ((dbmChar*)(aSrc))[7]; \
    }
#endif

/**
 * @brief 64비트 Pointer를 aDest에 저장한다.
 */
#define DBM_WRITE_POINTER( aDest, aSrc )                \
    {                                                   \
        ((dbmChar*)(aDest))[0] = ((dbmChar*)(aSrc))[0]; \
        ((dbmChar*)(aDest))[1] = ((dbmChar*)(aSrc))[1]; \
        ((dbmChar*)(aDest))[2] = ((dbmChar*)(aSrc))[2]; \
        ((dbmChar*)(aDest))[3] = ((dbmChar*)(aSrc))[3]; \
        ((dbmChar*)(aDest))[4] = ((dbmChar*)(aSrc))[4]; \
        ((dbmChar*)(aDest))[5] = ((dbmChar*)(aSrc))[5]; \
        ((dbmChar*)(aDest))[6] = ((dbmChar*)(aSrc))[6]; \
        ((dbmChar*)(aDest))[7] = ((dbmChar*)(aSrc))[7]; \
    }

/**
 * @brief (aSrc + aOffset)의 Pointer를 aDest에 저장하고, aOffset을 증가한다.
 */
#define DBM_READ_MOVE_POINTER( aDest, aSrc, aOffset )   \
    {                                                   \
        DBM_WRITE_POINTER( aDest, aSrc + aOffset );     \
        aOffset += 8;                                   \
    }

/**
 * @brief aSrc의 Pointer를 (aDest + aOffset)에 저장하고, aOffset을 증가한다.
 */
#define DBM_WRITE_MOVE_POINTER( aDest, aSrc, aOffset )  \
    {                                                   \
        DBM_WRITE_POINTER( aDest + aOffset, aSrc );     \
        aOffset += 8;                                   \
    }

/**
 * @brief aSrc에서 aBytes만큼의 바이트를 aDest에 저장한다.
 */
#define DBM_WRITE_BYTES( aDest, aSrc, aBytes )                          \
    {                                                                   \
        dbmMemcpy( (dbmChar*)(aDest), (dbmChar*)(aSrc), aBytes );       \
    }

/**
 * @brief (aSrc + aOffset)의 aBytes만큼의 바이트를 aDest에 저장하고, aOffset을 증가한다.
 */
#define DBM_READ_MOVE_BYTES( aDest, aSrc, aBytes, aOffset )     \
    {                                                           \
        DBM_WRITE_BYTES( aDest, aSrc + aOffset, aBytes );       \
        aOffset += aBytes;                                      \
    }

/**
 * @brief aSrc의 aBytes만큼의 바이트를 (aDest + aOffset)에 저장하고, aOffset을 증가한다.
 */
#define DBM_WRITE_MOVE_BYTES( aDest, aSrc, aBytes, aOffset )    \
    {                                                           \
        DBM_WRITE_BYTES( aDest + aOffset, aSrc, aBytes );       \
        aOffset += aBytes;                                      \
    }

/**
 * @brief aSrc의 data 를 aDst 로 복사하고 Position 을 이동한다.
 */
#define DBM_WRITE_POS_INT8( aDst, aPos, aSrc )  \
    {                                           \
        (aDst)[(aPos)] = (aSrc);                \
        (aPos)++;                               \
    }

#define DBM_WRITE_POS_INT16( aDst, aPos, aSrc )     \
    {                                               \
        (aDst)[(aPos)] = ((aSrc) & 0xFF00) >> 8;    \
        (aDst)[(aPos+1)] = ((aSrc) & 0xFF);         \
        (aPos) += 2;                                \
    }

#define DBM_WRITE_POS_INT32( aDst, aPos, aSrc )         \
    {                                                   \
        (aDst)[(aPos)] = ((aSrc) & 0xFF000000) >> 24;   \
        (aDst)[(aPos+1)] = ((aSrc) & 0xFF0000) >> 16;   \
        (aDst)[(aPos+2)] = ((aSrc) & 0xFF00) >> 8;      \
        (aDst)[(aPos+3)] = ((aSrc) & 0xFF);             \
        (aPos) += 4;                                    \
    }

#define DBM_WRITE_POS_INT64( aDst, aPos, aSrc )                 \
    {                                                           \
        (aDst)[(aPos)] = ((aSrc) & 0xFF00000000000000l) >> 56;  \
        (aDst)[(aPos+1)] = ((aSrc) & 0xFF000000000000l) >> 48;  \
        (aDst)[(aPos+2)] = ((aSrc) & 0xFF0000000000l) >> 40;    \
        (aDst)[(aPos+3)] = ((aSrc) & 0xFF00000000l) >> 32;      \
        (aDst)[(aPos+4)] = ((aSrc) & 0xFF000000) >> 24;         \
        (aDst)[(aPos+5)] = ((aSrc) & 0xFF0000) >> 16;           \
        (aDst)[(aPos+6)] = ((aSrc) & 0xFF00) >> 8;              \
        (aDst)[(aPos+7)] = ((aSrc) & 0xFF);                     \
        (aPos) += 8;                                            \
    }

/** @} */

/**
 * @addtogroup dbmGetOpt
 * @{
 */

/**
 * @brief 명령행 인자 정보를 저장하기 위한 구조체
 */ 
typedef struct dbmGetOpt
{
    dbmInt32                mArgc;   /**< 인자의 수  */
    const dbmChar * const * mArgv;   /**< 인자의 배열 포인터  */
    dbmInt32                mIndex;  /**< 인자 배열 포인터에서 위치 */
    dbmInt32                mOptCh;  /**< 옵션 */
    dbmChar const *         mOptArg; /**< 옵션의 인자 */
} dbmGetOpt;

typedef struct dbmGetOptOption
{
    const dbmChar * mName;         /**< Long Option Name  */
    dbmInt32        mOptCh;        /**< Short Option Letter */
    dbmInt32        mHasArg;       /**< Argument를 갖는가 */
    dbmChar const * mDescription;  /**< Decription */
} dbmGetOptOption;

/** @} */

/**
 * @addtogroup dbmStrings
 * @{
 */

#define DBM_NTS              (-3) /**< null-terminated dbring */

/**
 * @defgroup dbmPaintTextAttr Paint Text Attribute
 * @ingroup dbmStrings
 * @{
 */
#define DBM_PTA_OFF          (0)   /**< All attributes off */
#define DBM_PTA_BOLD         (1)   /**< Bold on */
#define DBM_PTA_UNDERSCORE   (4)   /**< Underscore */
#define DBM_PTA_BLINK        (5)   /**< Blink on */
#define DBM_PTA_REVERSE      (7)   /**< Reverse */
/** @} */

/**
 * @defgroup dbmPaintForeColor Paint Foreground Color
 * @ingroup dbmStrings
 * @{
 */
#define DBM_PFC_OFF            (-1)   /**< Ignore */
#define DBM_PFC_BLACK          (0)    /**< Black */
#define DBM_PFC_GRAY           (1)    /**< Gray */
#define DBM_PFC_RED            (2)    /**< Red */
#define DBM_PFC_LIGHT_RED      (3)    /**< Light Red */
#define DBM_PFC_GREEN          (4)    /**< Green */
#define DBM_PFC_LIGHT_GREEN    (5)    /**< Light Green */
#define DBM_PFC_BROWN          (6)    /**< Brown */
#define DBM_PFC_YELLOW         (7)    /**< Yellow */
#define DBM_PFC_BLUE           (8)    /**< Blue */
#define DBM_PFC_LIGHT_BLUE     (9)    /**< Light Blue */
#define DBM_PFC_MAGENTA        (10)   /**< Magenta */
#define DBM_PFC_LIGHT_MAGENTA  (11)   /**< Light Magenta */
#define DBM_PFC_CYAN           (12)   /**< Cyan */
#define DBM_PFC_LIGHT_CYAN     (13)   /**< Light Cyan */
#define DBM_PFC_WHITE          (14)   /**< White */
/** @} */

/**
 * @defgroup dbmPaintBackColor Paint Background Color
 * @ingroup dbmStrings
 * @{
 */
#define DBM_PBC_OFF          (0)    /**< Ignore */
#define DBM_PBC_BLACK        (40)   /**< Black */
#define DBM_PBC_RED          (41)   /**< Red */
#define DBM_PBC_GREEN        (42)   /**< Green */
#define DBM_PBC_YELLOW       (43)   /**< Yellow */
#define DBM_PBC_BLUE         (44)   /**< Blue */
#define DBM_PBC_MAGENTA      (45)   /**< Magenta */
#define DBM_PBC_CYAN         (46)   /**< Cyan */
#define DBM_PBC_WHITE        (47)   /**< White */
/** @} */

/**
 * @brief Paint Attribute
 */
typedef struct dbmPaintAttr
{
    dbmInt32 mTextAttr;       /**< Text Attribute @see dbmPaintTextAttr */
    dbmInt32 mForeColor;      /**< Foreground Color @see dbmPaintForeColor */
    dbmInt32 mBackColor;      /**< Background Color @see dbmPaintBackColor */
} dbmPaintAttr;

/** @} */

/**
 * @addtogroup dbmNetworkIo
 * @{
 */

#ifndef DBM_MAX_SECS_TO_LINGER
/** SO_LINGER에 적용할 최대 대기 초 */
#define DBM_MAX_SECS_TO_LINGER 30
#endif

#ifndef DBM_MAX_HOST_LEN
/** hostname의 최대 길이 */
#define DBM_MAX_HOST_LEN 256
#endif

#ifndef DBM_ANYADDR
/** 디폴트 'any' address */
#define DBM_ANYADDR "0.0.0.0"
#endif

#define DBM_DEFAULT_BACKLOG         (64)

#define DBM_SOCK_BLOCKED_IO_WAIT    (10)

/**
 * @defgroup dbmSocketOption Socket Option Flags
 * @ingroup dbmNetworkIo
 * @{
 */
#define DBM_SOPT_SO_LINGER        1    /**< Linger */
#define DBM_SOPT_SO_KEEPALIVE     2    /**< Keepalive */
#define DBM_SOPT_SO_DEBUG         4    /**< Debug */
#define DBM_SOPT_SO_NONBLOCK      8    /**< Non-blocking IO */
#define DBM_SOPT_SO_REUSEADDR     16   /**< Reuse addresses */
#define DBM_SOPT_SO_SNDBUF        64   /**< Send buffer */
#define DBM_SOPT_SO_RCVBUF        128  /**< Receive buffer */
#define DBM_SOPT_TCP_NODELAY      512  /**< For SCTP socket,
                                        * 내부적으로 SCTP_NODELAY에 매핑된다
                                        */
#define DBM_SOPT_TCP_NOPUSH       1024 /**< No push */
#define DBM_SOPT_RESET_NODELAY    2048 /**< This flag is ONLY set internally
                                        * when we set DBM_TCP_NOPUSH with
                                        * DBM_TCP_NODELAY set to tell us that
                                        * DBM_TCP_NODELAY should be turned on
                                        * again when NOPUSH is turned off
                                        */
#define DBM_SOPT_IPV6_V6ONLY     16384 /**< IPv6로 listen하고 있는 소켓에 대해
                                        * IPv4 연결 요청을 받지 않는다
                                        */
#define DBM_SOPT_TCP_DEFER_ACCEPT 32768 /**< 읽을 data가 올때까지 accept를 완료하지 않는다
                                         */
#define DBM_SOPT_TCP_KEEPIDLE     65536 /**< Dead connection 체크를 시작하는 시간까지의 idle time */
#define DBM_SOPT_TCP_KEEPCNT     131072 /**< 세션 체크 probe 횟수 */
#define DBM_SOPT_TCP_KEEPINTVL   262144 /**< 세션 체크 주기 */
/** @} */

/**
 * @defgroup dbmShutdownHow shutdown시에 닫을 채널
 * @ingroup dbmNetworkIo
 * @{
 */
typedef enum {
    DBM_SHUTDOWN_READ,          /**< read 채널을 닫음 */
    DBM_SHUTDOWN_WRITE,         /**< write 채널을 닫음 */
    DBM_SHUTDOWN_READWRITE      /**< read와 write 둘 다 닫음 */
} dbmShutdownHow;
/** @} */


/** @def DBM_INADDR_NONE
 * 모든 플랫폼이 INADDR_NONE을 갖고있지 않아서 정의함
 */
#if defined(INADDR_NONE) || defined( DOXYGEN )
#define DBM_INADDR_NONE INADDR_NONE
#else
#define DBM_INADDR_NONE ((dbmUInt32) 0xffffffff)
#endif

/** @def DBM_INADDR_ANY_STR
 * INADDR_ANY에 대한 IP를 dbring 형태로 정의
 */
#define DBM_INADDR_ANY_STR      "0.0.0.0"

/** @def DBM_FLAG_IPV6_SUPPORT
 * IPv6를 지원하는 플랫폼인지에 대한 체크 플래그
 */
#if defined(AF_INET6) || defined( DOXYGEN )
#define DBM_FLAG_IPV6_SUPPORT   1
#else
#define DBM_FLAG_IPV6_SUPPORT   0
#endif

/** @def DBM_FLAG_AF_UNSPEC_SUPPORT
 * AF_UNSPEC을 지원하는 플랫폼인지에 대한 체크 플래그
 */
#if defined(AF_UNSPEC) || defined( DOXYGEN )
#define DBM_FLAG_AF_UNSPEC_SUPPORT   1
#else
#define DBM_FLAG_AF_UNSPEC_SUPPORT   0
#endif

/**
 * @defgroup dbmAddressFamily Socket에서 사용하는 Address Family
 * @ingroup dbmNetworkIo
 * @{
 */

/**
 * 모든 플랫폼이 AF_INET을 갖고있지는 않아서 정의함
 * 디폴트 값은 FreeBSD 4.1.1에서 가져옴
 */
#define DBM_AF_INET     AF_INET
/** 
 * system이 알아서 address family를 정하도록 함
 * 모든 플랫폼에 다 정의되어 있지는 않음
 * DBM_FLAG_AF_UNSPEC_SUPPORT로 확인 후 사용해야 함
 */
#if defined(AF_UNSPEC) || defined( DOXYGEN )
#define DBM_AF_UNSPEC   AF_UNSPEC
#else
#define DBM_AF_UNSPEC   0
#endif

#if defined(AF_INET6) || defined( DOXYGEN )
/**
 * IPv6 Address Family. 모든 플랫폼에 다 정의되어 있지는 않음
 * DBM_FLAG_IPV6_SUPPORT로 확인 후 사용해야 함
 */
#define DBM_AF_INET6    AF_INET6
#endif

#if defined(AF_UNIX)  || defined( DOXYGEN )
/** 
 * UNIX DOMIAN SOCKET(== AF_LOCAL). 모든 플랫폼에 다 정의되어 있지는 않음
 */
#define DBM_AF_UNIX  AF_UNIX
#endif

/** @} */

/**
 * @defgroup dbmSocketType Socket Types
 * @ingroup dbmNetworkIo
 * @{
 */

/**
 * 연결 기반의 믿을 수 있는 양방향 바이트 스트림 통신
 */
#define DBM_SOCK_STREAM  SOCK_STREAM

/**
 * 연결이 필요없고 부분 소실이 날 수도 있는 데이터그램 통신
 */
#define DBM_SOCK_DGRAM  SOCK_DGRAM

/**
 * 소켓 옵션에 O_NONBLOCK을 설정
 */
#define DBM_SOCK_NONBLOCK  SOCK_NONBLOCK

/**
 * 소켓 옵션에 FD_CLOEXEC를 설정
 */
#if defined (SOCK_CLOEXEC) || defined (DOXYGEN)
#define DBM_SOCK_CLOEXEC  SOCK_CLOEXEC
#endif

/** @} */


/**
 * @defgroup dbmNetworkProtocol Socket의 Protocol
 * @ingroup dbmNetworkIo
 * @{
 */

/**
 * TCP 프로토콜
 */
#define DBM_PROTO_TCP       6
/**
 * UDP 프로토콜
 */
#define DBM_PROTO_UDP      17
/**
 * SCTP 프로토콜
 */
#define DBM_PROTO_SCTP    132

/**
 * Endian
 */
#define DBM_BIG_ENDIAN      (0)
#define DBM_LITTLE_ENDIAN   (-1)

#ifdef DBM_IS_BIGENDIAN
#define DBM_PLATFORM_ENDIAN             DBM_BIG_ENDIAN
#else
#define DBM_PLATFORM_ENDIAN             DBM_LITTLE_ENDIAN
#endif


/** @} */

/**
 * @defgroup dbmNetworkFlag Socket의 flag
 * @ingroup dbmNetworkIo
 * @{
 */

/**
 * 일반적 데이터 스트림에서 받지 않는 out-of-band 데이터를 요구한다.
 */
#define DBM_MSG_OOB         MSG_OOB

/**
 * 큐에서 데이터를 제거하지 않고 받는 큐의 시작에서부터 데이터를반환하는 받기 작동을 하도록 한다.
 */
#define DBM_MSG_PEEK        MSG_PEEK

/**
 * 요구한 양이 다 찰 때까지 작동을 블럭킹하도록 요구한다.
 */
#define DBM_MSG_WAITALL     MSG_WAITALL

/** @} */


/**
 * @defgroup dbmCommunicationGroupContext Communication Context
 * @ingroup dbmCommMgr
 * @{
 */

#define DBM_SOCKET_IN_CONTEXT(aContext)    ((aContext).mPollFd.mSocketHandle)

/** @} */


/**
 * @addtogroup dbmPoll
 * @{
 */

/**
 * @brief dbmDispatchPollSet()에서 이벤트가 발생한 소켓마다 호출되는 함수의 prototype
 * @param[in] aPollFd 이벤트가 발생한 소켓
 * @param[in] aErrorStack 에러 스택
 * @remark @a aPollFd 의 mRetEnvents에는 해당 소켓에 어떤 이벤트가 발생했는지 설정되어 있다.
 */
typedef dbmStatus (*dbmPollSetCallback)(dbmPollFd     * aPollFd,
                                        dbmErrorStack * aErrorStack);

/**
 * @brief Poll 옵션
 */

#if defined( POLLIN ) || defined( DOXYGEN )
#define DBM_POLLIN    POLLIN      /**< 읽을 데이터가 있다. */
#else
#define DBM_POLLIN    0x00000001
#endif
#if defined( POLLPRI ) || defined( DOXYGEN )
#define DBM_POLLPRI   POLLPRI     /**< 읽을 긴급한 데이터가 있다. */
#else
#define DBM_POLLPRI   0x00000002
#endif
#if defined( POLLOUT ) || defined( DOXYGEN )
#define DBM_POLLOUT   POLLOUT     /**< 쓰기가 block 이 아니다. */
#else
#define DBM_POLLOUT   0x00000004
#endif
#if defined( POLLERR ) || defined( DOXYGEN )
#define DBM_POLLERR   POLLERR     /**< 에러 발생 */
#else
#define DBM_POLLERR   0x00000008
#endif
#if defined( POLLHUP ) || defined( DOXYGEN )
#define DBM_POLLHUP   POLLHUP     /**< 연결이 끊겼음 */
#else
#define DBM_POLLERR   0x00000010
#endif

#define DBM_POLLMASK  0xFFFFFFFF  /**< MASK */

/** @} */

/**
 * @addtogroup dbmShm
 * @{
 */

/**
 * @brief 공유 메모리 세그먼트 이름의 최대 길이
 */
#define DBM_MAX_SHM_NAME      7

/**
 * @brief 공유 메모리 세그먼트 정보를 저장하는 구조체
 */
typedef struct dbmShm
{
    dbmChar       mName[DBM_MAX_SHM_NAME+1]; /**< 공유 메모리 이름(Null Terminated String) */
    void        * mAddr;   /**< 할당된 공유 메모리 세그먼트의 주소 */
    dbmSize       mSize;   /**< 할당된 공유 메모리 세그먼트의 크기 */
    dbmShmHandle  mHandle; /**< 할당된 공유 메모리 세그먼트의 핸들 */
    dbmInt32      mKey;    /**< 공유 메모리 세그먼트의 키 */
} dbmShm;

/**
 * @brief 공유 메모리 attach permission flag - read
 */ 
#define DBM_SHM_PERM_READ       0400 /** SHM_R */
/**
 * @brief 공유 메모리 attach permission flag - write
 */ 
#define DBM_SHM_PERM_WRITE      0200 /** SHM_W */

/** @} */

/**
 * @addtogroup dbmMsgQueue
 * @{
 */

/**
 * @defgroup dbmMsgQueueType Message Queue Type
 * @ingroup dbmMsgQueue
 * @{
 */
#define DBM_MSGQ_TYPE_EXEC_PROCESS      ( 1 )  /**< Execute Process Message */

/** @} */

/**
 * @brief 메세지 큐 구조체
 */
typedef struct dbmMsgQueue
{
    dbmInt32  mKey;     /**< message queue key */
    dbmInt32  mId;      /**< message queue identifier */
} dbmMsgQueue;

/**
 * @brief 메세지 Buffer 구조체
 */
typedef struct dbmMsgBuffer
{
    dbmInt64  mType;       /**< @see dbmMsgQueue */
    dbmChar   mText[1];    /**< message body */
} dbmMsgBuffer;

/**
 * @brief Message Queue Flag - NOWAIT
 */
#define DBM_MSGQ_FLAG_NOWAIT  IPC_NOWAIT

/** @} */

/**
 * @addtogroup dbmSignal
 * @{
 */

/**
 * @brief Signal Handler Function의 프로토타입
 */
typedef void (*dbmSignalFunc)( dbmInt32 );

/**
 * @brief Signal Extended Handler Function의 프로토타입
 */
typedef void (*dbmSignalExFunc)( dbmInt32, void*, void* );

/**
 * @defgroup dbmSignalNumber Signal Number
 * @ingroup dbmSignal
 * @{
 */
/**
 * @brief 플랫폼에서 제공되지 않는 Signal 번호.
 */
#define DBM_SIGNAL_UNKNOWN   0x0FFFFFFF

/**
 * @brief ignore signal handler
 */
#define DBM_SIGNAL_IGNORE   SIG_IGN

/**
 * @brief system default signal handler
 */
#define DBM_SIGNAL_DEFAULT  SIG_DFL

/**
 * @brief Trace trap
 */
#if defined( SIGTRAP ) || defined( DOXYGEN )
#define DBM_SIGNAL_TRAP SIGTRAP
#else
#define DBM_SIGNAL_TRAP DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Abort (abort function)
 */
#if defined( SIGABRT ) || defined( DOXYGEN )
#define DBM_SIGNAL_ABRT SIGABRT

#else
#define DBM_SIGNAL_ABRT DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Illegal instruction
 */
#if defined( SIGILL ) || defined( DOXYGEN )
#define DBM_SIGNAL_ILL SIGILL
#else
#define DBM_SIGNAL_ILL DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Floating-point exception
 */
#if defined( SIGFPE ) || defined( DOXYGEN )
#define DBM_SIGNAL_FPE SIGFPE
#else
#define DBM_SIGNAL_FPE DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Segmentation violation
 */
#if defined( SIGSEGV ) || defined( DOXYGEN )
#define DBM_SIGNAL_SEGV SIGSEGV
#else
#define DBM_SIGNAL_SEGV DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief BUS error
 */
#if defined( SIGBUS ) || defined( DOXYGEN )
#define DBM_SIGNAL_BUS SIGBUS
#else
#define DBM_SIGNAL_BUS DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Bad system call
 */
#if defined( SIGSYS ) || defined( DOXYGEN )
#define DBM_SIGNAL_SYS SIGSYS
#else
#define DBM_SIGNAL_SYS DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Continue
 */
#if defined( SIGCONT ) || defined( DOXYGEN )
#define DBM_SIGNAL_CONT SIGCONT
#else
#define DBM_SIGNAL_CONT DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Quit
 */
#if defined( SIGQUIT ) || defined( DOXYGEN )
#define DBM_SIGNAL_QUIT SIGQUIT
#else
#define DBM_SIGNAL_QUIT DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Termination
 */
#if defined( SIGTERM ) || defined( DOXYGEN )
#define DBM_SIGNAL_TERM SIGTERM
#else
#define DBM_SIGNAL_TERM DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Alarm clock
 */
#if defined( SIGALRM ) || defined( DOXYGEN )
#define DBM_SIGNAL_ALRM SIGALRM
#else
#define DBM_SIGNAL_ALRM DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Hangup
 */
#if defined( SIGHUP ) || defined( DOXYGEN )
#define DBM_SIGNAL_HUP SIGHUP
#else
#define DBM_SIGNAL_HUP DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Interrupt
 */
#if defined( SIGINT ) || defined( DOXYGEN )
#define DBM_SIGNAL_INT SIGINT
#else
#define DBM_SIGNAL_INT DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Kill, unblockable
 */
#if defined( SIGKILL ) || defined( DOXYGEN )
#define DBM_SIGNAL_KILL SIGKILL
#else
#define DBM_SIGNAL_KILL DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Broken pipe
 */
#if defined( SIGPIPE ) || defined( DOXYGEN )
#define DBM_SIGNAL_PIPE SIGPIPE
#else
#define DBM_SIGNAL_PIPE DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief IOT trap
 */
#if defined( SIGIOT ) || defined( DOXYGEN )
#define DBM_SIGNAL_IOT SIGIOT
#else
#define DBM_SIGNAL_IOT DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief User-defined signal 1
 */
#if defined( SIGUSR1 ) || defined( DOXYGEN )
#define DBM_SIGNAL_USR1 SIGUSR1
#else
#define DBM_SIGNAL_USR1 DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief User-defined signal 2
 */
#if defined( SIGUSR2 ) || defined( DOXYGEN )
#define DBM_SIGNAL_USR2 SIGUSR2
#else
#define DBM_SIGNAL_USR2 DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Stop, unblockable
 */
#if defined( SIGSTOP ) || defined( DOXYGEN )
#define DBM_SIGNAL_STOP SIGSTOP
#else
#define DBM_SIGNAL_STOP DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Stack fault
 */
#if defined( SIGSTKFLT ) || defined( DOXYGEN )
#define DBM_SIGNAL_STKFLT SIGSTKFLT
#else
#define DBM_SIGNAL_STKFLT DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Same as SIGCHLD
 */
#if defined( SIGCLD ) || defined( DOXYGEN )
#define DBM_SIGNAL_CLD SIGCLD
#else
#define DBM_SIGNAL_CLD DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Child dbatus has changed
 */
#if defined( SIGCHLD ) || defined( DOXYGEN )
#define DBM_SIGNAL_CHLD SIGCHLD
#else
#define DBM_SIGNAL_CHLD DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Pollable event occurred
 */
#if defined( SIGPOLL ) || defined( DOXYGEN )
#define DBM_SIGNAL_POLL SIGPOLL
#else
#define DBM_SIGNAL_POLL DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Real-time event occurred
 */
#if defined( SIGRTMIN ) || defined( DOXYGEN )
#define DBM_SIGNAL_RTMIN SIGRTMIN
#else
#define DBM_SIGNAL_RTMIN DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Stop typed at terminal
 */
#if defined( SIGTSTP ) || defined( DOXYGEN )
#define DBM_SIGNAL_TSTP SIGTSTP
#else
#define DBM_SIGNAL_TSTP DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Background read from tty 
 */
#if defined( SIGTTIN ) || defined( DOXYGEN )
#define DBM_SIGNAL_TTIN SIGTTIN
#else
#define DBM_SIGNAL_TTIN DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Background write from tty 
 */
#if defined( SIGTTOU ) || defined( DOXYGEN )
#define DBM_SIGNAL_TTOU SIGTTOU
#else
#define DBM_SIGNAL_TTOU DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Urgent condition on socket
 */
#if defined( SIGURG ) || defined( DOXYGEN )
#define DBM_SIGNAL_URG SIGURG
#else
#define DBM_SIGNAL_URG DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief CPU limit exceeded
 */
#if defined( SIGXCPU ) || defined( DOXYGEN )
#define DBM_SIGNAL_XCPU SIGXCPU
#else
#define DBM_SIGNAL_XCPU DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief File size limit exceeded
 */
#if defined( SIGXFSZ ) || defined( DOXYGEN )
#define DBM_SIGNAL_XFSZ SIGXFSZ
#else
#define DBM_SIGNAL_XFSZ DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Virtual alarm clock
 */
#if defined( SIGVTALRM ) || defined( DOXYGEN )
#define DBM_SIGNAL_VTALRM SIGVTALRM
#else
#define DBM_SIGNAL_VTALRM DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Profiling alram clock
 */
#if defined( SIGPROF ) || defined( DOXYGEN )
#define DBM_SIGNAL_PROF SIGPROF
#else
#define DBM_SIGNAL_PROF DBM_SIGNAL_UNKNOWN
#endif

/**
 * @brief Power failure restart
 */
#if defined( SIGPWR ) || defined( DOXYGEN )
#define DBM_SIGNAL_PWR SIGPWR
#else
#define DBM_SIGNAL_PWR DBM_SIGNAL_UNKNOWN
#endif

typedef struct dbmSignalInfo
{
    dbmInt32   mSigNo;
    dbmChar  * mCauseString;
    void     * mSigInfo;
    void     * mContext;
    dbmInt32   mFatalBehavior;
} dbmSignalInfo;

/**
 * @brief default fatal behavior
 */
#define DBM_FATAL_BEHAVIOR_DEFAULT      ( 0x00000011 )

/**
 * @brief kill mask
 */
#define DBM_FATAL_BEHAVIOR_KILL_MASK    ( 0x00000001 )
/**
 * @brief kill fatal thread only
 */
#define DBM_FATAL_BEHAVIOR_KILL_THREAD  ( 0x00000000 )
/**
 * @brief kill fatal process
 */
#define DBM_FATAL_BEHAVIOR_KILL_PROCESS ( 0x00000001 )

/**
 * @brief generate core dump mask
 */
#define DBM_FATAL_BEHAVIOR_CORE_DUMP_MASK  ( 0x00000010 )
/**
 * @brief no core dump generation
 */
#define DBM_FATAL_BEHAVIOR_CORE_DUMP_FALSE ( 0x00000000 )
/**
 * @brief generate core dump
 */
#define DBM_FATAL_BEHAVIOR_CORE_DUMP_TRUE  ( 0x00000010 )

/**
 * @brief hide dbderr backtrace
 */
#define DBM_FATAL_BEHAVIOR_HIDE_ERR_BACKTRACE_MASK  ( 0x00000100 )
/**
 * @brief hide dbderr backtrace
 */
#define DBM_FATAL_BEHAVIOR_HIDE_ERR_BACKTRACE_TRUE  ( 0x00000100 )
/**
 * @brief show dbderr backtrace
 */
#define DBM_FATAL_BEHAVIOR_HIDE_ERR_BACKTRACE_FALSE ( 0x00000000 )

/**
 * dbandard fatal handler
 */
typedef void (*dbmFatalHandler)( dbmSignalInfo * aSignalInfo );


/** @} */
/** @} */

/**
 * @addtogroup dbmRing
 * @{
 */

/**
 * @brief 연결할 객체 안에 링크 구조체를 선언해 사용한다.
 * @code
 *     struct MyElement
 *     {
 *         dbmRingEntry   mLink;
 *         dbmInt32       mFoo;
 *         dbmChar      * mBar;
 *     }
 * @endcode
 */
typedef struct dbmRingEntry
{
    void * mNext;
    void * mPrev;
} dbmRingEntry;

/**
 * @brief Ring 관리를 위한 Ring Head
 */
typedef struct dbmRingHead
{
    dbmRingEntry mLink;
    dbmUInt64    mLinkOffset;
} dbmRingHead;

/** @} */

/**
 * @addtogroup dbmDynamicAllocator
 * @{
 */

typedef struct dbmDynamicAllocator
{

    dbmRingHead    mChunkRing;     /**< 할당된 chunk들의 ring */
    dbmInt64       mInitSize;      /**< Init size */
    dbmInt64       mNextSize;      /**< Next size */
    dbmUInt64      mTotalSize;     /**< 할당된 모든 chunk 메모리의 크기 */
    dbmUInt32      mAtomic;        /**< thread 동시 실행 검증용 */
} dbmDynamicAllocator;

/** @} */


/**
 * @addtogroup dbmThreadProc
 * @{
 */

/**
 * @brief Thread Handle 초기화 매크로
 */
#define DBM_INIT_THREAD_HANDLE( aThreadHandle ) \
    {                                           \
        (aThreadHandle)->mHandle = -1;          \
        (aThreadHandle)->mProc.mProcID = -1;    \
    }

#if defined( DBM_HAVE_CPUSET )

/**
 * @brief CPU set 타입 정의
 */
typedef cpu_set_t dbmCpuSet;

/**
 * @brief 할당할 CPU set의 크기
 */
#define DBM_CPU_ALLOC_SIZE CPU_ALLOC_SIZE
/**
 * @brief CPU set의 메모리 할당
 */
#define DBM_CPU_ALLOC      CPU_ALLOC
/**
 * @brief CPU set의 메모리 반환
 */
#define DBM_CPU_FREE       CPU_FREE
/**
 * @brief CPU set 초기화
 */
#define DBM_CPU_ZERO_S     CPU_ZERO_S
/**
 * @brief CPU set에 특정 CPU 설정
 */
#define DBM_CPU_SET_S      CPU_SET_S
/**
 * @brief CPU 설정 확인
 */
#define DBM_CPU_ISSET_S    CPU_ISSET_S

#else

#define DBM_CPU_SETSIZE   1024
#define DBM_NCPUBITS      (8 * DBM_SIZEOF(dbmUInt64))
#define DBM_CPUELT(aCpu)  ((aCpu) / DBM_NCPUBITS)
#define DBM_CPUMASK(aCpu) ((dbmUInt64)1 << ((aCpu) % DBM_NCPUBITS))

/**
 * @brief CPU set 타입 정의
 */
typedef struct dbmCpuSet
{
    dbmUInt64 mBits[DBM_CPU_SETSIZE / DBM_NCPUBITS];
} dbmCpuSet;
/**
 * @brief 할당할 CPU set의 크기
 */
#define DBM_CPU_ALLOC_SIZE(aCount)  ((((aCount) + DBM_NCPUBITS - 1) / DBM_NCPUBITS) * DBM_SIZEOF(dbmUInt64))
/**
 * @brief CPU set의 메모리 할당
 */
#define DBM_CPU_ALLOC(aCount) malloc( DBM_CPU_ALLOC_SIZE(aCount) )
/**
 * @brief CPU set의 메모리 반환
 */
#define DBM_CPU_FREE(aCpuSet) free( aCpuSet )
/**
 * @brief CPU set 초기화
 */
#define DBM_CPU_ZERO_S( aSetSize, aCpuSet )                     \
    do                                                          \
    {                                                           \
        dbmSize __i;                                            \
        dbmSize __sMax = (aSetSize) / DBM_SIZEOF(dbmUInt64);    \
        dbmUInt64 *__sBits = (aCpuSet)->mBits;                  \
        for( __i = 0; __i < __sMax; ++__i)                      \
        {                                                       \
            __sBits[__i] = 0;                                   \
        }                                                       \
    } while (0)
/**
 * @brief CPU set에 특정 CPU 설정
 */
#define DBM_CPU_SET_S( aCpu, aSetSize, aCpuSet )                        \
    (__extension__                                                      \
     ({ dbmSize __sCpu = (aCpu);                                        \
         __sCpu < 8 * (aSetSize)                                        \
             ? (((dbmUInt64 *)((aCpuSet)->mBits))[DBM_CPUELT(__sCpu)]   \
                |= DBM_CPUMASK(__sCpu))                                 \
             : 0; }))
/**
 * @brief CPU 설정 확인
 */
#define DBM_CPU_ISSET_S(aCpu, aSetsize, aCpuSet)                                \
    (__extension__                                                              \
     ({ dbmSize __sCpu = (aCpu);                                                \
         __sCpu < 8 * (aSetsize)                                                \
             ? ((((__const dbmUInt64 *)((aCpuSet)->mBits))[DBM_CPUELT(__sCpu)]  \
                 & DBM_CPUMASK(__sCpu))) != 0                                   \
             : 0; }))

#endif  /* DBM_HAVE_CPUSET */

/**
 * @brief thread cancellation section으로 진입함.
 */
#define DBM_ENTER_CANCELLATION_SECTION( aFunc, aArg )  pthread_cleanup_push( aFunc, aArg )
/**
 * @brief thread cancellation section을 떠남.
 */
#define DBM_LEAVE_CANCELLATION_SECTION()               pthread_cleanup_pop( 0 )

/**
 * @brief A cancellation request is deferred until the thread next calls
 */
#define DBM_THREAD_CANCEL_DEFERRED       PTHREAD_CANCEL_DEFERRED
/**
 * @brief The thread can be canceled at any time
 */
#define DBM_THREAD_CANCEL_ASYNCHRONOUS   PTHREAD_CANCEL_ASYNCHRONOUS

/** @} */

/**
 * @addtogroup dbmSemaphore
 * @{
 */

#define DBM_MAX_SEM_NAME            7
#define DBM_MAX_NAMED_SEM_NAME      15


typedef struct dbmSemaphore
{
    dbmChar       mName[DBM_MAX_SEM_NAME+1]; /**< 세마포어 이름(Null Terminated String) */
    dbmSemHandle  mHandle;
} dbmSemaphore;

typedef struct dbmNamedSemaphore
{
    dbmChar             mName[DBM_MAX_NAMED_SEM_NAME+1]; /**< 세마포어 이름(Null Terminated String) */
    dbmNamedSemHandle * mHandle;
} dbmNamedSemaphore;

typedef struct dbmUnNamedSemaphore
{
    dbmUnNamedSemHandle mHandle;
} dbmUnNamedSemaphore;

typedef struct dbmEventSemaphore
{
    dbmUnNamedSemaphore mUnNamedSemaphore;
} dbmEventSemaphore;


#define DBM_INIT_UNDO_SEMAPHORE( aSemaphore )       \
    {                                               \
        (aSemaphore)->mSemId = -1;                    \
        (aSemaphore)->mSemNum = -1;                   \
    }

typedef struct dbmUndoSemaphore
{
    dbmInt32    mSemId;
    dbmInt32    mSemNum;
} dbmUndoSemaphore;


/** @} */

/**
 * @addtogroup dbmTime
 * @{
 */

/** invalid dbmTime value */
#define DBM_INVALID_DBM_TIME  ( 0 )

/** number of microseconds per second */
#define DBM_USEC_PER_SEC DBM_TIME_C(1000000)

/** @return dbmTime as a second */
#define DBM_GET_SEC_TIME(aTime) ((aTime) / DBM_USEC_PER_SEC)

/** @return dbmTime as a usec */
#define DBM_GET_USEC_TIME(aTime) ((aTime) % DBM_USEC_PER_SEC)

/** @return dbmTime as a msec */
#define DBM_GET_MSEC_TIME(aTime) (((aTime) / 1000) % 1000)

/** @return dbmTime as a msec */
#define DBM_GET_AS_MSEC_TIME(aTime) ((aTime) / 1000)

/** @return milliseconds as an dbmTime */
#define DBM_SET_MSEC_TIME(aMsec) ((dbmTime)(aMsec) * 1000)

/** @return seconds as an dbmTime */
#define DBM_SET_SEC_TIME(aSec) ((dbmTime)(aSec) * DBM_USEC_PER_SEC)

/** @return a second and usec combination as an dbmTime */
#define DBM_SET_TIME(aSec, aUsec) ((dbmTime)(aSec) * DBM_USEC_PER_SEC   \
                                   + (dbmTime)(aUsec))

/**
 * @brief 시간 정보를 표현하는 구조체
 * @remark ANSI의 struct tm과 다르게 마이크로초를 지원한다.
 */
typedef struct dbmExpTime
{    
    dbmInt32 mMicroSecond;      /**< mSecond에서 지간 마이크로초 */
    dbmInt32 mSecond;           /**< (0-61) mMinute에서 지난 초 */
    dbmInt32 mMinute;           /**< (0-59) mHour에서 지난 분 */
    dbmInt32 mHour;             /**< (0-23) 자정에서부터 지난 시 */
    dbmInt32 mDay;              /**< (1-31) 월의 날 */
    dbmInt32 mMonth;            /**< (0-11) 년의 달 */
    dbmInt32 mYear;             /**< 1900년에서부터 지난 년 */
    dbmInt32 mWeekDay;          /**< (0-6) 일요일에서부터 지난 날 */    
    dbmInt32 mYearDay;          /**< (0-365) 1월 1일에서부터 지난 날 */    
    dbmInt32 mIsDaylightSaving; /**< 일광 절약 시간 (썸머타임) */
    dbmInt32 mGMTOffset;        /**< UTC와 차이 초 */
} dbmExpTime;

#define DBM_MAX_TIME_STRING_LENGTH    (27)

/** @} */

/**
 * @addtogroup dbmSystem
 * @{
 */

typedef struct dbmCpuInfo
{
    dbmInt64  mCpuCount;
} dbmCpuInfo;

#ifndef RLIMIT_CPU
#define RLIMIT_CPU    0
#endif

#ifndef RLIMIT_FSIZE
#define RLIMIT_FSIZE  1
#endif

#ifndef RLIMIT_DATA
#define RLIMIT_DATA   2
#endif

#ifndef RLIMIT_STACK
#define RLIMIT_STACK  3
#endif

#ifndef RLIMIT_CORE
#define RLIMIT_CORE   4
#endif

#ifndef RLIMIT_RSS
#define RLIMIT_RSS    5
#endif

#ifndef RLIMIT_NOFILE
#define RLIMIT_NOFILE 7
#endif

#ifndef RLIMIT_AS
#define RLIMIT_AS     9
#endif

/**
 * HP에서 RLIMIT_NPROC, RLIMIT_MEMLOCK 없어서 제거했음.
 * linux, hp, sun 공통 분만 적용함.
 */
typedef enum dbmResourceLimitType
{
    DBM_RESOURCE_LIMIT_CPU    = RLIMIT_CPU,     /* 초 단위의 CPU 시간 */
    DBM_RESOURCE_LIMIT_FSIZE  = RLIMIT_FSIZE,   /* 최대 파일 크기 */
    DBM_RESOURCE_LIMIT_DATA   = RLIMIT_DATA,    /* 최대 데이타 크기 */
    DBM_RESOURCE_LIMIT_STACK  = RLIMIT_STACK,   /* 최대 스택 크기 */
    DBM_RESOURCE_LIMIT_CORE   = RLIMIT_CORE,    /* 최대 코어 파일 크기 */
    DBM_RESOURCE_LIMIT_RSS    = RLIMIT_RSS,     /* 최대 거주 집합 크기 */
    DBM_RESOURCE_LIMIT_NOFILE = RLIMIT_NOFILE,  /* 최대 열 수 있는 파일의 수 */
    DBM_RESOURCE_LIMIT_AS     = RLIMIT_AS       /* 주소 공간(가상 메모리) 제한값 */
} dbmResourceLimitType;

typedef struct dbmResourceLimit
{
    dbmInt64  mCurrent;
    dbmInt64  mMax;
} dbmResourceLimit;


/** @} */

/**
 * @addtogroup dbmIni
 * @{
 */

#define DBM_MAX_INI_LINE           DBM_MAX_SQL_IDENTIFIER_BUFFER_SIZE + DBM_MAX_FILE_PATH_LENGTH
#define DBM_MAX_INI_OBJECT_NAME    DBM_MAX_SQL_IDENTIFIER_BUFFER_SIZE
#define DBM_MAX_INI_PROPERTY_NAME  DBM_MAX_SQL_IDENTIFIER_BUFFER_SIZE
#define DBM_MAX_INI_PROPERTY_VALUE DBM_MAX_FILE_PATH_LENGTH

/**
 * @brief dbmIni > dbmIniObject > dbmIniProperty
 *
 *  [OBJ1]
 *  PROPERTY_NAME1 = Property Value
 *  PROPERTY_NAME2 = Property Value
 *
 *  [OBJ2]
 *  PROPERTY_NAME1 = Property Value
 *  PROPERTY_NAME2 = Property Value
 */
typedef struct dbmIniProperty
{
    dbmRingEntry mLink;
    dbmChar      mName[DBM_MAX_INI_PROPERTY_NAME + 1];
    dbmChar      mValue[DBM_MAX_INI_PROPERTY_VALUE + 1];
} dbmIniProperty;
    
typedef struct dbmIniObject
{
    dbmRingHead      mPropertyRing;
    dbmRingEntry     mLink;
    dbmIniProperty * mProperty;
    dbmChar          mName[DBM_MAX_INI_OBJECT_NAME + 1];
} dbmIniObject;

typedef struct dbmIni
{
    dbmRingHead    mObjectRing;
    dblAllocator   mAllocator;
    dbmIniObject * mCurrentObject;
} dbmIni;

typedef enum dbmIniDataType
{
    DBM_INI_DATA_TYPE_INT64 = 100,
    DBM_INI_DATA_TYPE_STRING,
    DBM_INI_DATA_TYPE_BOOLEAN
} dbmIniDataType;

/**
 * @brief ini 파일을 parsing 시에 Property 하나에 대한 
 *        모든 정보를 저장.
 */
typedef struct dbmIniFormat
{
    dbmChar         * mObject;  /* object name */
    dbmChar         * mName;    /* property name */
    dbmIniDataType    mDataType;
    dbmChar         * mDefaultValue;
    dbmInt64          mMin;     /* dbring인 경우 자리수임 */
    dbmInt64          mMax;     /* dbring인 경우 자리수임 */
    void            * mValue;
    dbmSize           mValueSize;
} dbmIniFormat;


/** @} */

/**
 * @addtogroup dbmDigest
 * @{
 */

#define DBM_CRC32_INIT_VALUE                (0)

/** @} */

/**
 * @addtogroup dbmAlgorithm
 * @{
 */

#define DBM_DES3_KEY_SIZE                   (24)

/**
 * @brief Triple-DES context structure
 */
typedef struct dbmDes3Context
{
    dbmUInt32 mSubKeys[96]; /**<  3DES subkeys */
} dbmDes3Context;


/** @} */

/**
 * @addtogroup dbmLicense
 * @{
 */

#define  DBL_LICENSE_PLAINTEXT_LEN          (64)
#define  DBL_LICENSE_KEY_LEN                (128)
#define  DBL_LICENSE_DATE_LEN               (8)
#define  DBL_LICENSE_CORECOUNT_LEN          (8)
#define  DBL_LICENSE_RESERVED_LEN           (8)
#define  DBL_LICENSE_IDENTIFIER_LEN         (24)

#define  DBL_LICENSE_TRIALDATE_OFFSET       (0)
#define  DBL_LICENSE_IDENTIFIER_OFFSET      (DBL_LICENSE_TRIALDATE_OFFSET  + DBL_LICENSE_DATE_LEN)
#define  DBL_LICENSE_RESERVED_OFFSET        (DBL_LICENSE_IDENTIFIER_OFFSET + DBL_LICENSE_IDENTIFIER_LEN)
#define  DBL_LICENSE_CORECOUNT_OFFSET       (DBL_LICENSE_RESERVED_OFFSET   + DBL_LICENSE_RESERVED_LEN)
#define  DBL_LICENSE_STARTDATE_OFFSET       (DBL_LICENSE_CORECOUNT_OFFSET  + DBL_LICENSE_CORECOUNT_LEN)
#define  DBL_LICENSE_EXPIREDATE_OFFSET      (DBL_LICENSE_STARTDATE_OFFSET  + DBL_LICENSE_DATE_LEN)

#define  DBL_LICENSE_INFINITE_DATE          "99991231"
#define  DBL_LICENSE_MAX_CORECOUNT          "99999999"
#define  DBL_LICENSE_RESERVED               "02468ACE"
#define  DBL_LICENSE_SUPERKEY_STRING        "GLIESE_SUPER_KEY_LICENSE"
#define  DBL_LICENSE_TRIALKEY_STRING        "GLIESE_TRIAL_KEY_LICENSE"
#define  DBL_LICENSE_GENERALKEY_STRING      "GLIESE_GENERAL_LICENSE__"

#define  DBL_LICENSE_INVALID_KEY            (0)
#define  DBL_LICENSE_GENERAL_KEY            (1)
#define  DBL_LICENSE_TRIAL_KEY              (2)
#define  DBL_LICENSE_SUPER_KEY              (3)

#define  DBL_LICENSE_FILE                   "license"DBM_PATH_SEPARATOR"license"

#define  DBM_ENV_DB_HOME                    DBM_UPPER_PRODUCT_NAME"_HOME"
#define  DBM_ENV_DB_DATA                    DBM_UPPER_PRODUCT_NAME"_DATA"


typedef struct dbmLicenceInfo
{
    dbmChar       mLicenseBuffer[DBL_LICENSE_KEY_LEN + 1];
    dbmChar       mPlainTextBuffer[DBL_LICENSE_PLAINTEXT_LEN + 1];
    dbmChar       mHostName[DBL_LICENSE_IDENTIFIER_LEN + 1];
    dbmChar       mStartDate[DBL_LICENSE_DATE_LEN + 1];
    dbmChar       mExpireDate[DBL_LICENSE_DATE_LEN + 1];
    dbmChar       mTrialDate[DBL_LICENSE_DATE_LEN + 1];
    dbmChar       mCoreCount[DBL_LICENSE_CORECOUNT_LEN + 1];
    dbmChar       mReserved[DBL_LICENSE_RESERVED_LEN + 1];
    dbmBool       mIsGivenHostName;
    dbmBool       mIsGivenExpireDate;
    dbmBool       mIsGivenCoreCount;
    dbmBool       mIsGivenStartDate;
    dbmBool       mIsTrial;
    dbmBool       mIsSuper;
} dbmLicenseInfo;

/** @} */

/**
 * @addtogroup dbmSpinLock
 * @{
 */
#define  DBM_SPINLOCK_STATUS_INIT    0  /**< 아무도 latch를 획득하지 않았음 */
#define  DBM_SPINLOCK_STATUS_LOCKED  1  /**< 누군가 래치를 획득하여 작업중임 */

#define  DBM_INIT_SPIN_LOCK( aSpinLock ) { (aSpinLock) = DBM_SPINLOCK_STATUS_INIT; }

/**
 * @brief SpinLock 구조체
 */
typedef dbmUInt32 dbmSpinLock;

/** @} */



/**
 * @addtogroup dbmArrayAllocator
 * @{
 */



typedef struct dbmArrayElement  dbmArrayElement;

/**
 * @brief dbmArrayAllocator의 element header 구조체.
 * @remark  element body는 runtime시 결정되기 때문에 동적으로 할당되어 element header뒤에 위치하게 된다.
 */
struct dbmArrayElement
{
    /* 메모리를 줄이려면 아래 두 변수를 통합해도 될것 같음 */
    struct dbmArrayElement * mNextFreeElement;    /**< 사용중이 아닌 다음 Element */
};

typedef dbmStatus (*dbmCheckCancellation)( dbmBool         * aCancel,
                                           dbmErrorStack   * aErrorStack );
/**
 * @brief 배열을 이용한 메모리 할당자의 header 구조체
 * @remark    mNextFreeElement는 할당 요청이 오면 넘겨줄 element를 가르키고 있는다.
 */
typedef struct dbmArrayAllocator
{
    dbmInt64             mElementSize;        /**< Element 하나의 크기 */
    dbmInt64             mElementBodySize;    /**< 사용 가능한 Body 크기 */
    dbmInt64             mTotalElementCount;  /**< Total Element 개수 */
    dbmInt64             mUsedElementCount;   /**< Used Element 개수 */
    /* 아래 변수가 자주 변경됨으로 cpu cache만큼 padding을 주는게 좋을수 있음 */
    dbmArrayElement    * mFirstFreeElement;   /**< 사용중이 아닌 First Element */
    dbmSpinLock          mLock;
    dbmInt32             mDummy;
    dbmUInt64            mCasMissCount;
} dbmArrayAllocator;

/** @} */


/**
 * @addtogroup dbmLogger
 * @{
 */

typedef struct dbmLogger
{
    dbmChar        mFileName[DBM_MAX_FILE_NAME_LENGTH];
    dbmChar        mFilePath[DBM_MAX_FILE_PATH_LENGTH];
    dbmSemaphore   mSemaphore;
    dbmChar      * mLogMsg;
    dbmBool        mNeedLock;
    dbmInt32       mMaxFileSize;
    dbmInt64       mLastFileNo;
} dbmLogger;


#define DBM_LZ4_COMPRESS_MAX_INPUT_SIZE             0x7E000000   /* 2 113 929 216 bytes */

/** @} */

/**
 * @addtogroup dbmStaticHash
 * @{
 */

/**
 * @brief Static Hash 동시성 제어 방법
 */
#define DBM_STATICHASH_MODE_NOLOCK      0 /**< 동시성 제어 안함 */
#define DBM_STATICHASH_MODE_HASHLOCK    1 /**< Hash 전체를 하나의 latch로 동시성 제어함 */
#define DBM_STATICHASH_MODE_BUCKETLOCK  2 /**< 각 Bucket 별로 latch를 할당받아 동시성 제어함 */

/**
 * @brief Static Hash 관리를 위한 Header
 * 바로 뒤에 mBucketCount 만큼의 dbmStaticHashBucket의 배열이 있다
 */
typedef struct dbmStaticHash
{
    dbmUInt16        mBucketCount;
    dbmChar          mLockMode;
    dbmChar          mPad1;
    dbmUInt16        mLinkOffset;
    dbmUInt16        mKeyOffset;
    dbmSpinLock    * mHashLock;
#if (DBM_SIZEOF_VOIDP == 4 )
    void           * mAlign;
#endif
} dbmStaticHash;

typedef struct dbmStaticHashBucket
{
    dbmRingHead   mList;
    dbmSpinLock * mLock;
#if (DBM_SIZEOF_VOIDP == 4 )
    void        * mAlign;
#endif
} dbmStaticHashBucket;

typedef dbmUInt32 (*dbmStaticHashHashingFunc)(void * aKey, dbmUInt32 aBucketCount);
typedef dbmInt32  (*dbmStaticHashCompareFunc)(void * aKeyA, void * aKeyB);

#define DBM_STATICHASH_GET_NTH_BUCKET(hashPtr,Seq)                      \
    ((dbmStaticHashBucket*)(((dbmStaticHash*)hashPtr) + 1) + (Seq))

#define DBM_DBCHASH_BUCKET_COUNT          (127)

/** @} */

/**
 * @addtogroup UDS name
 * @{
 */

/**
 * @brief 내부 process간 통신(UDS) name 정의
 *
 * @remark
 *  listener -> DBM_BALANCER_FD_NAME -> balancer -> DBM_DISPATCHER_FD_NAME -> gdispatcher
 *  listener <- DBM_LISTENER_NAME    <- balancer <- DBM_BALANCER_NAME      <- gdispatcher
 */
#define DBM_LISTENER_NAME           "glsnr"             /**< listener에서 command및 fd전달에 대한 ack받는 UDS */
#define DBM_BALANCER_FD_NAME        "gldblnr.fd"        /**< balancer에서 fd를 받을 UDS */
#define DBM_BALANCER_NAME           "gldblnr"           /**< balancer에서 fd전달에 대한 ack받는 UDS */
#define DBM_DISPATCHER_FD_NAME      "gdsptr.fd"         /**< dispatcher에서 fd를 받을 UDS */

/* fd전송시 fd에 대한 고유한 id size */
#define DBM_FD_ID_SIZE              (16)


/** @} */

/**
 * @addtogroup dbmUuid
 * @{
 */

/**
 * @brief UUID 초기화 매크로
*/
#define DBM_INIT_UUID( aUuid )                  \
{                                               \
    (aUuid)->mData[0]  = 0;                     \
    (aUuid)->mData[1]  = 0;                     \
    (aUuid)->mData[2]  = 0;                     \
    (aUuid)->mData[3]  = 0;                     \
    (aUuid)->mData[4]  = 0;                     \
    (aUuid)->mData[5]  = 0;                     \
    (aUuid)->mData[6]  = 0;                     \
    (aUuid)->mData[7]  = 0;                     \
    (aUuid)->mData[8]  = 0;                     \
    (aUuid)->mData[9]  = 0;                     \
    (aUuid)->mData[10] = 0;                     \
    (aUuid)->mData[11] = 0;                     \
    (aUuid)->mData[12] = 0;                     \
    (aUuid)->mData[13] = 0;                     \
    (aUuid)->mData[14] = 0;                     \
    (aUuid)->mData[15] = 0;                     \
}

/**
 * @brief UUID String 크기(NULL 문자 포함)
*/
 #define DBM_UUID_STRING_SIZE   ( (DBM_SIZEOF(dbmUuid) * 2) + 1 )

#if defined __has_cpp_attribute
    #if __has_cpp_attribute(fallthrough)
        #define DBM_FALLTHROUGH __attribute__ ((fallthrough));
    #else
        #define DBM_FALLTHROUGH
    #endif
#else
    #if defined(__GNUC__) && __GNUC__ >= 7
        #define DBM_FALLTHROUGH __attribute__ ((fallthrough))
    #else
        #define DBM_FALLTHROUGH ((void)0)
    #endif
#endif

/** @} */

/** @} */

DBM_END_DECLS

#endif /* _DBMDEF_H_ */

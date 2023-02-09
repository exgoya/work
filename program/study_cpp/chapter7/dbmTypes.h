/*******************************************************************************
 * dbmTypes.h
 *
 * Copyright (c) 2011, SUNJESOFT Inc.
 *
 *
 * IDENTIFICATION & REVISION
 *        $Id: dbmTypes.h.in 26626 2018-12-21 08:45:19Z htkim $
 *
 * NOTES
 *    
 *
 ******************************************************************************/


#ifndef _DBMTYPES_H_
#define _DBMTYPES_H_ 1

/**
 * @file dbmTypes.h
 * @brief Standard Layer Type Definitions
 */

/* GENERATED FILE WARNING!  DO NOT EDIT dbmTypes.h
 *
 * You must modify dbmTypes.h.in instead.
 */

/**
 * @addtogroup DBM
 * @{
 */

/* #undef _LARGE_FILES */
#define _LARGEFILE_SOURCE 1
/* #undef _LARGEFILE64_SOURCE */
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif

#define _USE_MATH_DEFINES

#define INCL_WINSOCK_API_TYPEDEFS 1




#include <wchar.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>

#include <dlfcn.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <net/if.h>
#include <signal.h>
#include <math.h>
#include <float.h>
#include <arpa/inet.h>
#include <setjmp.h>

#include <endian.h>
#include <aio.h>

/*
  RDMA 관련 INCLUDE시에 Parsing Error가 발생하며,
  RDMA 관련 파일을 체크할 필요가 없으므로, PARSING을 하지 않도록 설정한다. 
*/
#ifndef S_SPLINT_S



#endif



/**
 * @defgroup dbmTypes Standard Layer Types Definitions
 * @{
 */

/* centOS에서 isfinite가 오류가 나서 linux compile option에
   dbd=c99 -D_XOPEN_SOURCE=700 을 추가했더니, inline 키워드가
   붙은 함수들이 ubuntu에서 linking 오류가 발생했음.
   gcc default가 c89이고 inline은 c99부터이니 아마 그동안은
   inline이 제대로 안먹혔던거 같음.
   inline을 제대로 쓰려고 알아보니 header file에 body를 
   정의해야 하며 또한 dbatic을 붙여서 정의를해야하는데,
   기존 파일들을 다 고치려니 엄두가 안나서
   일단 inline을 무시하도록 아래와 같이 재정의 합니다.
   앞으로는 inline 쓰지 마시길... -O2 이상이면 알아서 합니다
   by xcom73 

   2014/03/04: rdma빌드 오류로 인해서 linux에서 dbd=gnu99로 변경
   by lym
*/
#define inline

/* Are we big endian? */
/* #undef DBM_IS_BIGENDIAN */
#define DBM_SUPPORT_MISSALIGNED_ADDRESS 1
#define DBM_HAVE_CPUSET       1
/* #undef SUPPORT_INFINIBAND */

/* cpu type */
#define DBM_TARGET_CPU_X86_64 1
/* #undef DBM_TARGET_CPU_I386 */
/* #undef DBM_TARGET_CPU_AMD64 */
/* #undef DBM_TARGET_CPU_PPC */
/* #undef DBM_TARGET_CPU_PPC64 */
/* #undef DBM_TARGET_CPU_IA64 */
/* #undef DBM_TARGET_CPU_SPARC */
/* #undef DBM_TARGET_CPU_HPPA */
/* #undef DBM_TARGET_CPU_AARCH64 */

#define DBM_SHARED_LIBRARY_PREFIX "lib"
#define DBM_SHARED_LIBRARY_SUFFIX ".so"

#define DBM_STATIC_LIBRARY_PREFIX "lib"
#define DBM_STATIC_LIBRARY_SUFFIX ".a"


/** void형 포인터의 크기 (바이트) */
#define DBM_SIZEOF_VOIDP 8

/* Types we may use */

/** 참, 거짓을 표현 */
typedef char dbmBool;

/** 문자 타입 */
typedef char dbmChar;

/** wide형 문자 타입 */
// typedef wchar_t dbmWChar;

/** 부호를 지닌 8비트 정수 */
typedef signed char dbmInt8;
/** 부호가 없는 8비트 정수 */
typedef unsigned char dbmUInt8;

/** 부호를 지닌 16비트 정수 */
typedef signed short dbmInt16;
/** 부호가 없는 16비트 정수 */
typedef unsigned short dbmUInt16;

/** 부호를 지닌 32비트 정수 */
typedef signed int dbmInt32;
/** 부호가 없는 32비트 정수 */
typedef unsigned int dbmUInt32;

/** 부호를 지닌 64비트 정수 */
typedef signed long dbmInt64;
/** 부호가 없는 64비트 정수 */
typedef unsigned long dbmUInt64;

/** platform bit에 따른 가변 long - for XA */

#if DBM_SIZEOF_VOIDP == 4
typedef int dbmVarInt;
#else
typedef long dbmVarInt;
#endif

typedef struct dbmUInt128
{
    dbmUInt64      mHighDigit;   /**< 상위 64-bit 정수형 관리 */
    dbmUInt64      mLowDigit;    /**< 하위 64-bit 정수형 관리 */
} dbmUInt128;

/** 32비트 실수 */
typedef float dbmFloat32;

/** 64비트 실수 */
typedef double dbmFloat64;

typedef struct dbmFile
{
    int mFileDesc;
} dbmFile;

typedef DIR dbmDir; /**< native dir */
typedef void * dbmDsoHandle;
typedef void * dbmDsoSymHandle;

typedef size_t dbmSize;
typedef ssize_t dbmSsize;

typedef off_t dbmOffset;

typedef socklen_t dbmSockLen;

typedef ino_t dbmInode;

typedef struct timeval dbtTimeVal; /* native timeval */

/** number of microseconds since 00:00:00 january 1, 1970 UTC */
typedef dbmUInt64 dbmTime;

/** ANSI time_t 표현 */
typedef time_t dbmAnsiTime;

/** timer */
typedef timer_t dbmTimer;

/** signal event structure */
typedef struct sigevent dbmSigEvent;

/** signal event structure */
typedef struct itimerspec dbmTimerSpec;

/** intervals for I/O timeouts, in microseconds */
typedef dbmUInt64 dbmInterval;
/** short interval for I/O timeouts, in microseconds */
typedef dbmUInt32 dbmShortInterval;

typedef va_list dbmVarList;

typedef struct aiocb dbmAioCb;
typedef sem_t dbmSemHandle;
typedef int dbmShmHandle;
typedef sem_t dbmNamedSemHandle;
typedef sem_t dbmUnNamedSemHandle;

#define DBM_BOOL_SIZE     ( sizeof( dbmBool ) )

// #define DBM_WCHAR_SIZE    ( sizeof( dbmWChar ) )

#define DBM_INT8_SIZE     ( sizeof( dbmInt8 ) )
#define DBM_UINT8_SIZE    ( sizeof( dbmUInt8 ) )
#define DBM_INT16_SIZE    ( sizeof( dbmInt16 ) )
#define DBM_UINT16_SIZE   ( sizeof( dbmUInt16 ) )
#define DBM_INT32_SIZE    ( sizeof( dbmInt32 ) )
#define DBM_UINT32_SIZE   ( sizeof( dbmUInt32 ) )
#define DBM_INT64_SIZE    ( sizeof( dbmInt64 ) )
#define DBM_UINT64_SIZE   ( sizeof( dbmUInt64 ) )
// #define DBM_INT128_SIZE   ( sizeof( dbmInt128 ) )
#define DBM_UINT128_SIZE  ( sizeof( dbmUInt128 ) )

#define DBM_FLOAT32_SIZE  ( sizeof( dbmFloat32 ) )
#define DBM_FLOAT64_SIZE  ( sizeof( dbmFloat64 ) )


#define DBM_UINT64_HIGH_BIT   ( DBM_UINT64_C(0x8000000000000000) )
#define DBM_UINT64_LOW_BIT    ( DBM_UINT64_C(0x0000000000000001) )


/**
 * @brief 성공한다면 DBM_SUCCESS, 그렇지 않다면 DBM_FAILURE 를 갖는다.
 */
typedef enum
{
    DBM_SUCCESS = 0,
    DBM_FAILURE
} dbmStatus;

typedef struct dbmProc
{
    pid_t mProcID;
} dbmProc;

#define DBM_THREAD_FUNC 

typedef struct dbmThread dbmThread;
/**
 * @brief Worker Thread의 표준 프로토타입
 */
typedef void *(DBM_THREAD_FUNC *dbmThreadFunc)( dbmThread *, void * );

/**
 * @brief Thread 구조체
 * @note dbmThread의 제일 상위 2개의 멤버는 변경시켜서는 안된다.
 *  <BR> dbmThread를 dbmThreadHandle로 형변환 시켜서 사용하는 경우가 있다 
 */
struct dbmThread
{
    pthread_t mHandle;
    dbmProc         mProc;
    dbmStatus       mExitStatus;
    void          * mArgs;
    dbmThreadFunc   mFunction;
};

/**
 * @brief Thread Handle 구조체
 */
typedef struct dbmThreadHandle
{
    pthread_t mHandle;
    dbmProc   mProc;
} dbmThreadHandle;

/**
 * @brief Thread 속성 구조체
 */
typedef struct dbmThreadAttr
{
    pthread_attr_t mAttribute;
} dbmThreadAttr;

#define DBM_THREAD_ONCE_INIT PTHREAD_ONCE_INIT

typedef struct dbmThreadOnce
{
    pthread_once_t mOnce;
} dbmThreadOnce;

/**
 * Structure for determining user ownership.
 */
typedef uid_t dbmUserID;

/**
 * Structure for determining group ownership.
 */
typedef gid_t dbmGroupID;
typedef dev_t dbmDeviceID;


/* Mechanisms to properly type numeric literals */
#define DBM_INT64_C(val) (val##L)
#define DBM_UINT64_C(val) (val##UL)


/** OS Path Separator */
#define DBM_PATH_SEPARATOR "/"
#define DBM_PATH_SEPARATOR_CHARACTER '/'

/** mechanism to properly type dbmTime literals */
#define DBM_TIME_C(val) DBM_INT64_C(val)

#ifdef INT8_MIN
#define DBM_INT8_MIN   INT8_MIN
#else
#define DBM_INT8_MIN   (-0x7f - 1)
#endif

#ifdef INT8_MAX
#define DBM_INT8_MAX  INT8_MAX
#else
#define DBM_INT8_MAX   (0x7f)
#endif

#ifdef UINT8_MIN
#define DBM_UINT8_MIN  UINT8_MIN
#else
#define DBM_UINT8_MIN  (0)
#endif

#ifdef UINT8_MAX
#define DBM_UINT8_MAX  UINT8_MAX
#else
#define DBM_UINT8_MAX  (0xff)
#endif

#ifdef INT16_MIN
#define DBM_INT16_MIN   INT16_MIN
#else
#define DBM_INT16_MIN   (-0x7fff - 1)
#endif

#ifdef INT16_MAX
#define DBM_INT16_MAX  INT16_MAX
#else
#define DBM_INT16_MAX  (0x7fff)
#endif

#ifdef UINT16_MAX
#define DBM_UINT16_MAX  UINT16_MAX
#else
#define DBM_UINT16_MAX  (0xffff)
#endif

#ifdef UINT16_MIN
#define DBM_UINT16_MIN  UINT16_MIN
#else
#define DBM_UINT16_MIN  (0)
#endif

#ifdef INT32_MIN
#define DBM_INT32_MIN   INT32_MIN
#else
#define DBM_INT32_MIN   (-0x7fffffff - 1)
#endif

#ifdef INT32_MAX
#define DBM_INT32_MAX  INT32_MAX
#else
#define DBM_INT32_MAX  0x7fffffff
#endif

#ifdef UINT32_MAX
#define DBM_UINT32_MAX  UINT32_MAX
#else
#define DBM_UINT32_MAX  (0xffffffffU)
#endif

#ifdef UINT32_MIN
#define DBM_UINT32_MIN  UINT32_MIN
#else
#define DBM_UINT32_MIN  (0)
#endif

#ifdef INT64_MIN
#define DBM_INT64_MIN   INT64_MIN
#else
#define DBM_INT64_MIN   (DBM_INT64_C(-0x7fffffffffffffff) - 1)
#endif

#ifdef INT64_MAX
#define DBM_INT64_MAX   INT64_MAX
#else
#define DBM_INT64_MAX   DBM_INT64_C(0x7fffffffffffffff)
#endif

#ifdef UINT64_MAX
#define DBM_UINT64_MAX  UINT64_MAX
#else
#define DBM_UINT64_MAX  DBM_UINT64_C(0xffffffffffffffff)
#endif

#ifdef UINT64_MIN
#define DBM_UINT64_MIN  UINT64_MIN
#else
#define DBM_UINT64_MIN  (0)
#endif

extern const dbmUInt128 gUInt128MAX;
extern const dbmUInt128 gUInt128MIN;
extern const dbmUInt128 g10Pow19;

extern const dbmUInt64  gPreDefinedPow[];
extern const dbmInt32   gPreDefinedPowMax;

extern const dbmUInt128 gPreDefinedPowUInt128[];
extern const dbmInt32   gPreDefinedPowMaxUInt128;

#define DBM_UINT128_MAX  gUInt128MAX
#define DBM_UINT128_MIN  gUInt128MIN

#define DBM_FLOAT64_2POW32      ( (dbmFloat64) 4294967296.0 )
#define DBM_FLOAT64_2POW64      ( (dbmFloat64) 18446744073709551616.0 )

#define DBM_SIZE_MAX    (~((dbmSize)0))

#ifdef INFINITY 
#define DBM_FLOAT32_INFINITY    ( (dbmFloat32) INFINITY )
#define DBM_FLOAT64_INFINITY    ( (dbmFloat64) INFINITY )
#else
#define DBM_FLOAT32_INFINITY    ( (dbmFloat32) HUGE_VAL * HUGE_VAL )
#define DBM_FLOAT64_INFINITY    ( (dbmFloat64) HUGE_VAL * HUGE_VAL )
#endif

#ifdef FLT_DIG
#define DBM_FLT_DIG      (FLT_DIG)
#else 
#define DBM_FLT_DIG      (6)
#endif

#ifdef DBL_DIG
#define DBM_DBL_DIG         (DBL_DIG)
#define DBM_DBL_MAX_10_EXP  (DBL_MAX_10_EXP)
#define DBM_DBL_MIN_10_EXP  (DBL_MIN_10_EXP)
#else 
#define DBM_DBL_DIG         (15)
#define DBM_DBL_MAX_10_EXP  (308)
#define DBM_DBL_MIN_10_EXP  (-307)
#endif

// SHA1
#define DBM_DIGEST_SHA1_SIZE    (20)
#define DBM_DIGEST_SHA224_SIZE  (28)
#define DBM_DIGEST_SHA256_SIZE  (32)
#define DBM_DIGEST_SHA384_SIZE  (48)
#define DBM_DIGEST_SHA512_SIZE  (64)

#define DBM_DIGEST_MAX_SIZE     (DBM_DIGEST_SHA512_SIZE)
#define DBM_DIGEST_HEX_SIZE(has_size)  ((has_size) * 2 + 1)

#define DBM_PASSWORD_BUFFER_SIZE   DBM_DIGEST_HEX_SIZE( DBM_DIGEST_MAX_SIZE )

/** @} */

/**
 * @addtogroup dbmNetworkIo
 * @{
 */

/** ST Socket Descriptor */
typedef dbmInt32 dbmSocket;

/* 확인 필요: 이 부분이 "#define dbmInetAddr inet_addr" 로 변경됨. */
#define dbmInetAddr inet_addr

/**
 * @brief IPv4 in_addr을 대표하는 구조체
 */
typedef struct in_addr dbmInAddr4;

/**
 * @brief IPv6 in_addr을 대표하는 구조체
 */
typedef struct in6_addr dbmInAddr6;


/** @remark short가 16bit가 아닌 system들 때문에 dbmUInt16을 사용함... */
typedef dbmUInt16            dbmPort;

/** Socket Address 구조체 */
typedef struct dbmSockAddr
{
    union
    {
        struct sockaddr     mSockCommon; /**< Common header 용 */
        struct sockaddr_in  mIn4;  /**< IPv4 용 */
        struct sockaddr_in6 mIn6;  /**< IPv6 용 */
        struct sockaddr_un  mUn;   /**< UNIX DOMAIN 용 */
    }mSa;
} dbmSockAddr;

/**
 * @brief IO vector 구조체
 */
typedef struct iovec dbmIoVec;

/**
 * @brief Message Header 구조체
 */
typedef struct msghdr dbmMsgHdr;

/**
 * @brief Control Message Header 구조체
 */
typedef struct cmsghdr dbmCMsgHdr;


/**
 * @brief Infiniband RC Interface Handle
 */
typedef void * dbmRcHandle;


/** @} */

/**
 * @addtogroup dbmPoll
 * @{
 */

/**
 * @brief 소켓 지시자와 이벤트를 저장하기 위한 구조체
 */ 
typedef struct dbmPollFd
{
    dbmInt32 mSocketHandle; /**< 소켓 지시자 */
    dbmInt16    mReqEvents;    /**< 요청 이벤트 */
    dbmInt16    mRetEvents;    /**< 반환된 이벤트 */
} dbmPollFd;

/**
 * @brief 소켓 지시자와 이벤트를 저장하기 위한 구조체
 */ 
typedef struct dbmPollFdEx
{
    dbmPollFd   mPollFd;       /**< Native PollFd */
    void      * mUserContext;  /**< Socket과 관련된 user context */
} dbmPollFdEx;

typedef struct epoll_event dbmEpollEvent; /**< Query pollset */

/**
 * @brief 많은 수의 소켓 이벤트 관리를 위한 구조체
 */ 
typedef struct dbmPollSet
{
    
    dbmPollFdEx   * mQuerySet;       /**< query pollfd 배열 */
    dbmPollFdEx   * mResultSet;      /**< result pollfd 배열 */
    dbmInt32        mMaxPollFdNum;   /**< 생성된 pollfd의 수 */
    dbmInt32        mCurPollFdNum;   /**< 현재 이벤트를 대기할 pollfd의 수 */
    dbmBool         mUseRDMASocket;  /**< RDMA socket 사용 여부 */
    dbmInt32        mEpollFd;        /**< epoll file descriptor ( only epoll ) */
    dbmEpollEvent * mEpollEvent;     /**< Epoll Event */
    
    
    
    
} dbmPollSet;

/** @} */

/**
 * @addtogroup dbmCommMgr
 * @{
 */

/** Communication을 위한 Context 구조체 */
typedef struct dbmContext
{
    dbmBool      mUseRDMASocket;
    dbmPollFd    mPollFd;
    dbmSockAddr  mSocketAddr;
} dbmContext;

#define INVALID_SOCKET_HANDLE         ( -1 )

#define DBM_INVALIDATE_CONTEXT( aContext )            \
    ( aContext ).mPollFd.mSocketHandle = INVALID_SOCKET_HANDLE;

#define DBM_IS_INVALID_CONTEXT( aContext )              \
    ( ( aContext ).mPollFd.mSocketHandle == INVALID_SOCKET_HANDLE ? DBM_TRUE : DBM_FALSE )

/** Communication Manager에서 사용하는 Packet Header */
typedef struct dbmPacketHeader
{
    dbmInt32   mEndian;
    dbmInt32   mPacketLength;
} dbmPacketHeader;

/* 성능 향상을 위해 validation을 수행하지 않도록 하는 옵션 */
/* #undef DBM_IS_IGNORE_VALIDATION */

/** @} */

/** UUID */
typedef struct dbmUuid
{
    dbmUInt8 mData[16]; /**< the actual UUID */
} dbmUuid;

/** @} */

#endif /* _DBMTYPES_H_ */

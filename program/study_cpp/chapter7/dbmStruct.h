#ifndef __DBM_STRUCT_H_
#define __DBM_STRUCT_H_  1

#include <dbmTypes.h>
#include <dbmDef.h>
#include <dbmDefEx.h>
#include <dbmCommon.h>
#include <dbmStruct.h>

//#include <momApi.h>
//
//
//#define DBM_OBJECT_NAME_LEN (32)
//#define DBM_USER_FUNC_NAME_LEN (32)
#define DBM_CALL_BACK_TYPE_MAX (32)


typedef struct
{
    volatile dbmInt32     mLock;
    volatile dbmInt64     mWriteIdx;
    volatile dbmInt64     mReadIdx;
    dbmInt32              mElemSize;
    dbmInt32              mMaxCount;
    dbmChar             * mBuffer;
} dbmRing;


typedef struct
{
    dbmDataType   mDataType;
    dbmInt32      mSize;
    dbmInt32      mScale;
} dbmDataTypeDef;


typedef struct
{
    dbmChar  * mChunk;
    dbmInt32   mCurr;
    dbmInt32   mSize;
    void     * mNext;
} dbmMemChunk;


typedef struct
{
    dbmMemChunk    * mHead;
    dbmMemChunk    * mTail;
    dbmMemChunk    * mCurrent;
    dbmMemChunk    * mSaveChunk;
    dbmInt32         mSaveCurr;
} dbmAllocator;



typedef struct
{
    dbmInt32           mIndex;
    dbmDataType        mDataType;
    dbmChar          * mDataPtr;
    dbmInt32           mMaxSize;
    dbmInt32         * mSizePtr;
} dbmBindColDef;


typedef struct
{
    dbmExprType         mType;
    dbmDataTypeDef      mDataTypeDef;
    dbmChar           * mValue;
    dbmChar           * mAlias;
} dbmExprCommon;



typedef struct
{
    dbmChar     * mTableName1;
    dbmChar     * mTableName2;
    dbmChar     * mDataPtr1;
    dbmChar     * mDataPtr2;
} dbmRefRow;



typedef struct
{
    dbmChar        mTag[DBM_OBJECT_NAME_LEN + 1];
    struct timeval mStart;
    dbmInt64       mSum;
    dbmInt64       mCount;
} dbmPerfStat;



typedef struct
{
    volatile dbmInt32            mTransId;
    volatile dbmSlotState        mState;
    volatile dbmInt64            mIndex;
} dbmSlotStatInfo;



typedef struct
{
    dbmInt64      mSlotId;
    dbmInt64      mExtraKey;
    dbmChar     * mSlotPtr;
    dbmChar     * mOrgSlotPtr1;
    dbmChar     * mOrgSlotPtr2;
} dbmResultElem;


/*
typedef struct
{
    dbmPropId          mPropId;           // Property ID
    dbmChar          * mValue;            // Value Pointer
} dbmProps;
*/


typedef struct
{
    void             ** mShmPtr;          // Segment Pointer
    dbmChar           * mInstName;        // Segment가 속한 InstanceName
    dbmChar           * mSegmentName;     // 실제 SegmentName
    dbmInt64            mDDLCount;        // 해당 Segment의 DDL실행 횟수
} dbmShmInfo;


typedef struct dbmListElement
{
    dbmListElemType          mType;
    void                   * mElem;
    struct dbmListElement  * mPrev;
    struct dbmListElement  * mNext;
} dbmListElement;


typedef struct
{
    dbmInt32         mCount;
    dbmListElement * mHead;
    dbmListElement * mTail;
} dbmList;





typedef void ( *dbmLibFunc )( const char *, ... );


typedef struct
{
    dbmChar          * mName;
    dbmDataType        mDataType;
} dbmLibraryParam;





typedef struct
{
    dbmChar          * mAliasName;
    dbmChar          * mFuncName;
    dbmList          * mParamList;
} dbmLibraryItem;




typedef struct
{
    dbmChar          * mAliasName;
    dbmChar          * mFuncName;
    void             * mUserContext;
    dbmLibFunc         mFuncAddr;
} dbmLibFuncSymbol;





typedef struct
{
    dbmList          * mKeyList;          // Index Key List (dbmKeyColumnInfo)
    dbmShmInfo       * mShmInfo;          // dbmShmInfo
    dbmChar          * mTempBuf;          // Internal Node를 위한 임시공간
    dbmChar          * mPathInfoPtr;      // Scan Path History
    dbmChar          * mIterator;         // exec방식에서 사용할 임시저장공간
    dbmChar          * mTmpNodePtr;       // exec방식에서 사용할 Node복사 공간
} dbmIndexInfo;



typedef struct
{
    dbmList          * mRowList;
    dbmListElement   * mCurrElem;
    dbmChar          * mCurrDataPtr;
    dbmChar          * mData;
    dbmInt32           mAccessCount;
    dbmBool            mIsDesc;
    dbmInt32           mSlotCount;
    dbmChar          * mSlotArr;
    dbmIndexInfo     * mGroupIndexInfo;
    dbmIndexInfo     * mOrderIndexInfo;
    dbmInt64           mCurrNodeId;    // IndexInfo를 통해 가져올 경우 마지막 접근한 NodeId
    dbmInt32           mCurrPosition;  // IndexInfo를 통해 가져올 경우 마지막 접근한 Position in Node
    dbmInt32           mFetchLimit;
    dbmInt32           mFetchCount;
} dbmResultSet;


typedef union 
{
    dbmInt32      mInt32;
    dbmInt64      mInt64;
    dbmBool       mBool;
    dbmChar     * mStr;
} dbmPropValue;

typedef struct
{
    dbmPropValue       mValue;
} dbmPropInfo;

typedef struct
{
    dbmPropId          mPropId;
    const dbmChar    * mName;
    dbmPropValueType   mValueType;
    dbmChar          * mValue;
} dbmPropDefault;


typedef enum 
{
    E_FILE_LOG_ANCHOR = 100,
    E_FILE_REPL_ANCHOR,
    E_FILE_CAPTURE_ANCHOR,
    E_FILE_LOG,
    E_FILE_LOG_BY_FLUSHER,
    E_FILE_DATA,
    E_FILE_DIC_INST,
    E_FILE_DIC_TABLE,
    E_FILE_DIC_INDEX,
    E_FILE_DIC_COLUMN,
    E_FILE_DIC_INDEX_COLUMN,
    E_FILE_DIC_SEQUENCE,
    E_FILE_DIC_REPL,
    E_FILE_DIC_REPL_TABLE,
    E_FILE_DIC_CAPTURE,
    E_FILE_DIC_CAPTURE_TABLE,
    E_FILE_DIC_PROCEDURE,
    E_FILE_DIC_PROC_TEXT,
    E_FILE_DIC_USER_LIB,
    E_FILE_DIC_USER_LIB_FUNC,
    E_FILE_DIC_USER_LIB_PARAM,
    E_FILE_UNSENT,
    E_FILE_CAPTURE_INFO,
    E_FILE_CAPTURE_LIST,
    E_FILE_CAPTURE_DAT,
    E_FILE_MAX
} dbmFileTypeEx;




/**
 * Header size는 512 byte로 한다
 */
typedef struct
{
    dbmInt64        mFileVersion;
    dbmFileTypeEx   mFileType;
    dbmChar         mDummy[500];
} dbmFileHeader;



typedef struct
{
    volatile dbmInt64   mLogFileNo;       // Disk Logging시 기록하는 파일의 고유순서번호
    volatile dbmInt64   mLogFileOffset;   // Disk Logging시 마지막 기록한 파일Offset
    volatile dbmInt64   mCkptFileNo;      // Ckpt가 수행된 File No
    volatile dbmInt64   mArchiveFileNo;   // Archive StartNo
    volatile dbmInt64   mCaptureFileNo;   // Capture가 수행한 File No
} dbmLogInfo;



typedef struct
{
    volatile dbmInt64   mLogCacheWriteInd;
    volatile dbmInt64   mLogCacheReadInd;
    volatile dbmInt64   mLogFileNo;
    volatile dbmInt64   mOffset;
    volatile dbmTime    mCreateTime;
} dbmLogCacheIndicator;




typedef struct
{
    dbmShmInfo         * mShmInfo;        // Instance에 대한 Segment
    dbmInt32             mTransId;        // TransId
    dbmInt64             mViewSCN;        // Select시 사용할 ViewSCN
    dbmInt32             mSpinLockCount;  // TryLock을 계속 재시도해보는 횟수
    dbmInt32             mLockSleepUs;    // LockWait시 Sleep할 Time(us)
    dbmInt32             mAgingInterval;  // Aging대상인 MinView을 구해보는 주기
    dbmBool              mCommitWait;     // CommitWait Mode
    dbmBool              mMvccEnable;     // Mvcc Enable 
    dbmBool              mBeginCursor;    // Cursor 시작여부
    dbmChar            * mAnchorPtr;      // Anchor Map
    dbmChar            * mReplAnchorPtr;  // Repl Anchor Ptr
    dbmPropInfo        * mProps;          // Handle의 PropList를 포인팅
    dbmChar            * mPerfStatPtr;    // PerfMemory 할당
    dbmBool              mTraceLogMode;   // Trace Log에 PBT를 위한 여러 로그를 남길지 여부
    dbmLibFuncSymbol   * mExpiredCallBack;   
} dbmInstanceRef;


typedef struct
{
    dbmShmInfo         * mTableShm;       // Table Segment
    dbmIndexInfo       * mCurrIndex;      // 현재 사용중인 IndexInfo Pointer
    dbmList            * mIndexList;      // Table내의 모든 Index List
    dbmChar            * mTempBuf;        // Data 처리를 위한 임시 공간 할당
    dbmInt32             mRowSize;        // RowSize 정보
    dbmBool              mIsRepl;         // Repl 대상 테이블 여부
    dbmChar            * mBindBuf;        // Binding 할때 임시 공간 할당
    dbmList            * mColumnList;     // ColumnInfo (dbmDicColumn)
    dbmChar            * mDataSet;        // Data 처리를 위한 임시 공간 할당
    dbmInt64             mCreateSCN;      // Table이 생성된 SCN
    dbmInt64             mExtraKey;       // NonUnique-FetchNext 처리를 위한 ExtraKey
    dbmInt64             mLastFetchedSlot; // 마지막 Fetched된 SlotId
    dbmList            * mBindList;       // Binding 할때 항목들
    dbmInt64             mObjectId;       // Table Object ID
    dbmBool              mLatencyEnable;  // LockWait시 Sleep호출여부
    dbmBool              mIsUpdateMode;   // Update-Mode로 사용중인지 설정
    dbmInt64             mTargetSlotId;   // Update용 Slot대상
    dbmInt64             mTargetExtraKey; // Update용 ExtraKey정보
} dbmTableInfo;



typedef struct
{
    dbmChar            * mTableName;
    dbmInt32             mRowSize;
    dbmInt64             mViewSCN;
} dbmRemoteTableInfo;

typedef struct 
{
    dbmInt32            mProtocol;
    dbmSize             mSize;     // body size
    dbmTcpType          mType;
    dbmChar             mObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt32            mArraySize;      // Array Operation일때만 쓴다.
    dbmInt32            mArrayCount;     // Array Operation일때만 쓴다.

    dbmChar           * mBody;
    dbmSize             mBodyAllocSize;
} dbmReqBuf;


typedef struct 
{
    dbmInt32            mProtocol;
    dbmSize             mSize;     // body size
    dbmTcpType          mType;
    dbmInt32            mRowCount;
    dbmInt32            mIsCont;
    dbmParseType        mParseType;
    dbmInt32            mErrorCode;

    dbmChar           * mBody;
    dbmSize             mBodyAllocSize;
} dbmResBuf;


typedef struct 
{
    dbmInt32            mProtocol;
    dbmSize             mSize;     // body size
    dbmTcpType          mType;
    dbmChar             mObjectName[ DBM_OBJECT_NAME_LEN + 1 ];

    dbmChar           * mBody;
    dbmSize             mBodyAllocSize;
} dbmRepl;


typedef struct 
{
    dbmInt32            mProtocol;
    dbmSize             mSize;     // body size
    dbmTcpType          mType;

    dbmChar           * mBody;
    dbmSize             mBodyAllocSize;
} dbmReplAck;

typedef struct 
{
    dbmInt32            mProtocol;
    dbmSize             mSize;     // body size
    dbmTcpType          mType;

    dbmChar           * mBody;
    dbmSize             mBodyAllocSize;
} dbmCapture;



typedef struct
{
    dbmChar             mMode[DBM_OBJECT_NAME_LEN+1];
    dbmChar             mInstName[DBM_OBJECT_NAME_LEN+1];
    dbmChar             mCaptureName[DBM_OBJECT_NAME_LEN+1];
    dbmInt64            mSCN;
} dbmCaptureFirst;


/**
 * 통신시 보내지는 size
 */
#define DBM_REQ_HEADER_SIZE         ( sizeof(dbmReqBuf) - 16 )
#define DBM_RES_HEADER_SIZE         ( sizeof(dbmResBuf) - 16 )

#define DBM_REPL_HEADER_SIZE        ( sizeof(dbmRepl) - 16 )
#define DBM_REPL_ACK_HEADER_SIZE     ( sizeof(dbmReplAck) - 16 )

#define DBM_CAPTURE_HEADER_SIZE        ( sizeof(dbmCapture) - 16 )
#define DBM_CAPTURE_ACK_HEADER_SIZE     ( sizeof(dbmCaptureAck) - 16 )

typedef struct
{
    dbmContext           mMainSocket;     // Connect시 생긴 Socket fd
    dbmInt32             mRemoteTransId;  // Remote TransID
    dbmInt32             mAffectedCount;  // 원격에서 처리된 RowCount를 저장
    dbmReqBuf            mSendBuf;        // Send Buf
    dbmResBuf            mRecvBuf;        // Recv Buf
    dbmInt32             mRecvTimeoutMs;  // Recv Timeout
    dbmChar              mTargetIP[16];   // 원격지 서버IP
    dbmInt32             mTargetPort;     // 원격지 접속Port
    dbmList            * mTableList;      // Table의 축약정보를 List로 일단 저장해둔다.
} dbmRemoteHandle;



typedef struct
{
    dbmThread            mRetryTid;       // Recv Thread ID
    dbmThreadStat        mThreadStat;     // Recv Thread Status
    dbmContext           mMainSocket;     // Connect시 생긴 Socket fd
    dbmInt32             mRemoteTransId;  // Remote TransID
    dbmRepl              mRepl;           // Send Buf
    dbmReplAck           mReplAck;        // Recv Buf
    dbmBool              mUnSentDiskMode; // 미전송을 디스크모드로 할지 여부
    dbmChar            * mUnSentBuf;      // 미전송저장용 버퍼
    dbmFile              mUnSentFile;     // 미전송 저자용 파일Desc
    dbmInt32             mUnSentBufSize;  // 미전송저장용 버퍼의 크기
    dbmInt64             mUnSentFileNo;   // 파일번호
    dbmPropInfo        * mPropList;       // PropList Pointer
    dbmInstanceRef     * mInstRef;        // Handle의 InstRef를 가리켜야 함
    dbmChar              mPrimaryIP[16];  // Target IP
    dbmInt32             mPortNo;         // PORT
    dbmInt32             mConnTimeoutMs;
    dbmInt32             mRecvTimeoutMs;
    dbmTableInfo       * mReplUnSent;
    dbmTableInfo       * mReplLog;
    dbmInt64             mUnSentAckCount;
    dbmBool              mAsyncDML;       // Async형태로 DML을 전송할지 여부
    dbmBool              mReplDDLEnable;
    dbmChar            * mUnSentLogDir;
} dbmReplHandle;

typedef struct
{
    dbmSize       mSize;
    void       ** mAddrList;
} dbmLogCacheInfo;


typedef struct
{
    dbmFile              mFD;                 // Disk 기록을 위한 FD
    dbmInt64             mLastOffset;         // 마지막 위치
    dbmChar            * mBuffer;             // Log를 쓰기 위한 버퍼 (512Byte만 할당해놓고 N개로 연결해 기록)
    dbmChar            * mFileName;           // File Name 생성을 위한 임시버퍼
    dbmInstanceRef     * mInstRef;            // Instance Pointer
    dbmLogInfo         * mLogInfo;            // LogFile에 대한 정보 ==> dbmTrans의 LogInfo를 가리킨다.
    dbmAllocator       * mAllocator;          // Allocator
    dbmChar            * mLogDir;             // Log Dir
    dbmInt32             mSize;               // Log piece를 merge할때 알아낸 전체 크기 (BlockHeader포함)
    dbmList            * mLogList;            // Log piece List
    dbmInt64             mFileSize;           // Log File의 최대 크기 정보
    dbmInt32             mBufferSize;         // 할당한 BufferSize의 현재 크기
    dbmLogCacheInfo      mLogCacheInfo;       // LogCache정보를 저장할 포인터
} dbmDiskLogHandle;

typedef struct
{
    const dbmChar  *mName;
    dbmInt32        mCode;
} dbmKeyWord;


typedef struct
{
    dbmChar         * mBuffer;
    void            * mScanner;
    void            * mParseObj;
    dbmAllocator    * mAllocator;
    dbmInt32          mSize;
    dbmInt32          mLineNo;
    dbmInt32          mColumn;
    dbmInt32          mPosition;
    dbmInt32          mLength;
    dbmInt32          mCurrLoc;
    dbmInt32          mNextLoc;
    dbmInt32          mStmtLength;
    dbmInt32          mBindCount;
    dbmList         * mBindParamList;
    dbmErrorStack   * mErrorStack;
} dbmParserContext;



typedef struct
{
    dbmAllocator       * mAllocator;           // Stmt 에서 사용할 parser/prepare시 메모리관리자
    dbmAllocator       * mExecAllocator;       // stmt 에서 execute시에 사용할 메모리관리자
    dbmParserContext   * mParseCtx;            // parser시에 사용할 context
    void               * mPlanObj;             // parser/prepare 이후 만들어질 Plan Pointer
    dbmList            * mBindColList;         // Fetch시 사용할 변수들 모음(Remote 역시 동일하게 사용)
    dbmChar            * mSQLString;           // SQL text
    dbmChar            * mDataPtr;             // 임시성 공간
    dbmList            * mRemoteTargetList;    // Remote TargetList
    dbmList            * mRemoteBindParamList; // RemoteBindParam List
    dbmResultSet       * mRemoteResultSet;     // Remote ResultSet
    dbmInt64             mRemoteAddr;          // 원격지에서 호출될 경우의 주소값
    dbmBool              mBindStruct;          // Struct Binding Flag
    dbmInt64             mMark;                // for validation
} dbmInternalStmt;



typedef struct
{
    dbmInt32             mFileDesc;
    dbmChar            * mInstName;
    dbmChar            * mFileName;
    dbmChar            * mBuffer;
} dbmFileHandle;



typedef struct
{
    dbmInt64            mInitHandle;
    dbmInt64            mFreeHandle;
    dbmInt64            mPrepare;
    dbmInt64            mExecute;
    dbmInt64            mInsert;
    dbmInt64            mUpdate;
    dbmInt64            mSelect;
    dbmInt64            mDelete;
    dbmInt64            mEnque;
    dbmInt64            mDeque;
    dbmInt64            mAging;
    dbmInt64            mCommit;
    dbmInt64            mRollback;
    dbmInt64            mRecoveryRollback;
    dbmInt64            mRecoveryCommit;
    dbmInt64            mSplitIndex;
    dbmInt64            mRetryLockCount;
    dbmInt64            mDummy[32];
} dbmPerfInfo;


typedef struct
{
    dbmInt32            mPID;                   // Process ID
    dbmInt32            mTID;                   // Thread ID
    dbmInt32            mOldTID;                // Thread ID
    dbmInt64            mCurrUndoPage;          // 현재 사용중인 Undo Page ID
    dbmInt64            mFirstUndoPage;         // 첫번째 사용하는 Undo Page ID
    dbmInt64            mLastUndoPage;          // 현재 사용중인 Undo Page ID
    dbmInt64            mSavePointPage;         // Save Point를 찍을 경우 롤백할 현재 UndoPage ID
    dbmInt32            mSavePointOffset;       // Save Point를 찍을 경우 롤백할 현재 Page내의 Offset
    dbmInt32            mSavePointPrevOffset;   // Page내의 이전 로그가 기록된 위치
    volatile dbmInt32   mWaitForTransId;        // 내가 대기중인 상대편 TransId
    dbmChar             mWaitForObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt64            mWaitForSlotId;         // 대기하는 SlotId
    dbmInt64            mSCN;                   // 나의 SCN
    dbmInt64            mViewSCN;               // 나의 View SCN, begin되면 획득,
    dbmBool             mBeginTrans;            // 뭔가 시작했다면, init,commit,rollback,recovery시 false
    dbmTransStat        mTransStat;             // TransStat
    dbmBool             mIsLogging;             // Disk Logging Flag
    dbmBool             mIsRepl;                // Repl Flag
    dbmInt64            mHeadSlot;              // Direct Queue일 경우 정리용도
    dbmInt64            mTailSlot;              // Direct Queue일 경우 정리용도
    dbmChar             mLastIndex[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt64            mLastNodeId;
    dbmBool             mIsTreeLock;
    dbmTime             mBeginTime;             // 최초의 Tx 시작 시각인데 성능때문에 안쓸듯
    dbmInt64            mCheckAliveCnt;         // Check Alive cnt 특정값 이상되면 process begin time을 확인해본다
                                                // shared memory에 없어도 됨.
    dbmPerfInfo         mPerfInfo;              // PerfInfo
    dbmBool             mBeginXA;               // xa_start시 설정
    dbmBool             mEndXA;                 // xa_end시 설정
    dbmChar             mXID[152];              // xa_start시 설정
} dbmTrans;



typedef struct
{
    dbmInt64             mPrevPageId;           // 나의 앞쪽 UndoPage
    dbmInt64             mNextPageId;           // 나의 뒷쪽 UndoPage
    dbmInt32             mPrevOffset;           // 내가 기록한 로그의 이전 위치
    dbmInt32             mCurrOffset;           // 현재 쓸 Page내의 Offset
    dbmInt32             mTransId;              // 할당받은 TxID
} dbmUndoPageHeader;




typedef struct
{
    dbmLogCacheMode        mLogCacheMode;       // LogCache Mode
    dbmSize                mLogCacheSizePerFile;  // Create시점에 지정된 File당 LogCache Size
    dbmInt32               mLogCacheCount;      // Create시점에 지정된 LogCache 개수
    dbmInt32               mLogCacheRange;      // Create시점에 지정된 LogCache 부분 사용
} dbmLogCache;


typedef struct
{
    volatile dbmInt32      mLock;               // Trans 전체에 공유할 Lock
    volatile dbmInt32      mIsActive;           // Active 여부
    volatile dbmInt64      mSCN;                // SCN
    volatile dbmInt64      mMinViewSCN;         // beginCursor에 의한 minSCN
    volatile dbmInt64      mReplSendSCN;        // 마지막 전송한 최대 SCN
    volatile dbmInt64      mReplAckSCN;         // 마지막 수신한 최대 SCN
    volatile dbmInt64      mObjectId;           // Object Id 채번용
    dbmInt64               mLogFileSize;        // Instance 생성시 결정되면 변경할 수 없다.
    dbmBool                mIsDiskLogEnable;    // Disk Log Mode
    dbmBool                mIsThreadSleep;      // DEBUG용 TestSleep
    dbmLogCache            mLogCache;           // LogCache
    dbmTime                mCreateTime;                       // 생성시각
    dbmChar                mName[ DBM_OBJECT_NAME_LEN + 1 ];  // Name
} dbmTransHeader ;



typedef struct
{
    volatile dbmInt32    mLock;            // Row Lock
    volatile dbmInt32    mSize;            // Size인데 무의미할듯
    dbmInt64             mExtraKey;        // 내가 저장될 유일하게 찍힌 ID (Non-unique의 구분값)
    volatile dbmInt64    mSCN;             // SCN
    volatile dbmInt64    mDeleteSCN;       // deleteSCN
    volatile dbmInt64    mPrevRID;         // MVCC 수행시 나의 이전 버전이 저정된 SlotID를 가리킨다.
    volatile dbmInt64    mNextRID;         // MVCC 수행시 나의 다음 버전이 저정된 SlotID를 가리킨다.
    volatile dbmInt64    mUndoPageId;      // 현재 Tx가 기록한 BeforeImage가 저장된 UndoPageId
    volatile dbmLogType  mLogType;         // 현재 Row에 수행중인 Tx Type
    volatile dbmInt32    mUndoOffset;      // 현재 Tx가 기록된 BeforeImage가 저장된 UndoPage내의 Offset
    volatile dbmTime     mExpireTime;      // 저장된 시각.
} dbmRowHeader;



typedef struct
{
    volatile dbmInt32    mLock;
    dbmInt32             mRowSize;
    volatile dbmInt64    mExtraKey;
    dbmTableType         mTableType;
    dbmInt64             mObjectId;
    dbmTime              mCreateTime;
    dbmInt64             mCreateSCN;
    dbmChar              mName[ DBM_OBJECT_NAME_LEN + 1];
    dbmChar              mDummy[1024];
} dbmTableHeader;




typedef struct
{
    volatile dbmInt64    mStartVal;
    volatile dbmInt64    mIncrementVal;
    volatile dbmInt64    mCurrVal;
    volatile dbmInt64    mMinVal;
    volatile dbmInt64    mMaxVal;
    dbmInt32             mIsCycle;
} dbmSequenceVal;



typedef struct
{
     dbmChar           mName[ DBM_OBJECT_NAME_LEN + 1];
     dbmDataType       mDataType;
     dbmInt32          mOffset;
     dbmInt32          mSize;
} dbmColumnInfo;



typedef struct
{
     dbmChar           mName[ DBM_OBJECT_NAME_LEN + 1];
     dbmChar           mJsonPath[ DBM_JSON_DATA_SIZE + 1]; // for json
     dbmDataType       mDataType;
     dbmInt32          mOffset;
     dbmInt32          mSize;
     dbmInt32          mIsAsc;
     dbmInt32          mJoinOffset;
} dbmKeyColumnInfo;



typedef struct
{
    dbmInt32           mCount;
    dbmColumnInfo      mColumn[ 1024 ];
} dbmTableColumn;



typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmInt64           mInitSize;
    dbmInt64           mExtendSize;
    dbmInt64           mMaxSize;
} dbmDicInst;


typedef struct
{
    dbmInt64           mLastOffset;
    dbmInt64           mMark;
} dbmDicFileHeader;


typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mTableName[DBM_OBJECT_NAME_LEN + 1];
    dbmTableType       mTableType;
    dbmInt32           mColumnCount;
    dbmInt32           mRowSize;
    dbmInt32           mMsgSize;
    dbmInt32           mIndexCount;
    dbmInt64           mInitSize;
    dbmInt64           mExtendSize;
    dbmInt64           mMaxSize;
    dbmInt32           mIndexID;
    dbmChar            mExpireColumn[DBM_OBJECT_NAME_LEN + 1];
    dbmInt32           mExpireDuration;
} dbmDicTable;



typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mTableName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mIndexName[DBM_OBJECT_NAME_LEN + 1];
    dbmInt32           mIsUnique;
    dbmInt32           mKeySize;
    dbmInt32           mKeyColumnCount;
    dbmInt32           mIndexOrder;
} dbmDicIndex;



typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mTableName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mIndexName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mColumnName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mJsonPath[DBM_JSON_DATA_SIZE + 1]; // for json
    dbmInt32           mJsonKeySize;   // for json : json max key size
    dbmInt32           mOrder;
    dbmInt32           mColumnOrder;
    dbmInt32           mIsAsc;
} dbmDicIndexColumn;



typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mTableName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mColumnName[DBM_OBJECT_NAME_LEN + 1];
    dbmDataType        mDataType;
    dbmInt32           mOffset;
    dbmInt32           mSize;
    dbmInt32           mOrder;
} dbmDicColumn;




typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mSeqName[DBM_OBJECT_NAME_LEN + 1];
    dbmInt64           mStartVal;
    dbmInt64           mIncrementVal;
    dbmInt64           mCurrVal;
    dbmInt64           mMinVal;
    dbmInt64           mMaxVal;
    dbmInt32           mIsCycle;
} dbmDicSequence;




typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
} dbmDicReplInst;




typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mTableName[DBM_OBJECT_NAME_LEN + 1];
} dbmDicReplTable;




typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mCaptureName[DBM_OBJECT_NAME_LEN + 1];
} dbmDicCaptureHost;



typedef struct
{
    dbmChar            mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mCaptureName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar            mTableName[DBM_OBJECT_NAME_LEN + 1];
} dbmDicCaptureTable;


typedef struct
{
    dbmChar           mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar           mProcName[DBM_OBJECT_NAME_LEN + 1];
    dbmInt32          mPieceCount;
} dbmDicProcedure;



typedef struct
{
    dbmChar           mInstName[DBM_OBJECT_NAME_LEN + 1];
    dbmChar           mProcName[DBM_OBJECT_NAME_LEN + 1];
    dbmInt32          mPieceSeq;
    dbmChar           mText[ DBM_DIC_PROC_TEXT_LEN ];
} dbmDicProcedureText;



typedef struct
{
    dbmChar          mInstName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mSvcName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mDllName[ PATH_MAX + NAME_MAX + 1 ];
    dbmChar          mInitFunc[ DBM_USER_FUNC_NAME_LEN + 1 ];
    dbmChar          mFiniFunc[ DBM_USER_FUNC_NAME_LEN + 1 ];
    dbmInt32         mIsSyncLib;
} dbmDicUserLib;



typedef struct
{
    dbmChar          mInstName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mSvcName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mAliasName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mFuncName[ DBM_USER_FUNC_NAME_LEN + 1 ];
    dbmInt32         mParamCount;
} dbmDicUserLibFunc;



typedef struct
{
    dbmChar          mInstName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mSvcName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mAliasName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          mParamName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmDataType      mDataType;
    dbmInt32         mOrder;
} dbmDicUserLibParam;



typedef struct
{
    volatile dbmInt32      mLock;                   // Index Tree Lock
    volatile dbmInt64      mRootNodeId;             // Index Root Node ID
    volatile dbmInt64      mAllocCount;             // Node할당때 증가, 해제시 감소
    dbmBool                mIsUnique;               // Uniqueness 여부
    dbmInt32               mKeySize;                // Index Key의 크기
    dbmIndexWorkType       mWorkType;               // Split시점의 WorkType
    dbmInt64               mBeforeNewNodeToSplit;   // Split을 위해 새로 생긴 NodeId
    dbmInt64               mBeforeSrcNodeToSplit;   // Split을 할 NodeId
    dbmInt64               mBeforeParentNodeId;     // Split시점에 입력된 parentNode
    dbmInt64               mOldNewNodeToSplit;      // Split을 위해 새로 생긴 NodeId
    dbmInt64               mOldSrcNodeToSplit;      // Split을 할 NodeId
    dbmInt64               mOldParentNodeId;        // Split시점에 입력된 parentNode
    dbmInt64               mBeforeRootNode;
    dbmInt64               mBeforeRemoveNodeId;     // DeleteFreeNode시 대상노드
    dbmInt64               mRemovePrevNodeId;       // 삭제대상의 왼쪽노드ID
    dbmInt64               mRemoveNextNodeId;       // 삭제대상의 오른쪽노드ID
    volatile dbmInt32      mRecoveryTID;
    dbmTime                mCreateTime;             // Index 생성 시각
    dbmChar                mName[ DBM_OBJECT_NAME_LEN + 1]; // Index Name
    dbmChar                mDummy[1024];
} dbmIndexHeader;



typedef struct
{
    volatile dbmInt32     mLock;              // Node Lock
    volatile dbmInt32     mCount;             // Node에 저장된 Key 개수
    volatile dbmInt32     mValid;             // Node 유효성, 해제시 Invalid해짐
    volatile dbmInt64     mPrevNodeId;        // 내 노드의 이전 NodeID
    volatile dbmInt64     mNextNodeId;        // 내 노드의 다음 NodeID
    volatile dbmInt64     mModified;          // 내 노드에 변경이 발생하는 횟수
    dbmIndexBackupStat    mBackupStat;        // memmove시 backup 여부
    dbmInt32              mBeforeCount;       // 작업시점의 Count
    dbmInt32              mBeforePosition;    // 작업시점의 Position
    dbmInt64              mBeforeParentNode;  // 검색시 ParentNodeId
    dbmIndexWorkType      mWorkType;          // 작업상태
    dbmBool               mIsLeaf;            // Leaf
    dbmChar               mDummy[256];
} dbmIndexNodeHeader;



typedef struct
{
    volatile dbmInt64     mDataSlotId;        // Table Segment내의 SlotID
    volatile dbmInt64     mExtraKey;          // Extra Key (non-unique 구분용)
    volatile dbmInt64     mLeftNodeId;        // Internal Node일 경우 Left Node ID를 가리킨다.(아니면 -1)
    volatile dbmInt64     mRightNodeId;       // Internal Node일 경우 Right Node ID를 가리킨다.(아니면 -1)
} dbmIndexSlotHeader;



typedef struct
{
    dbmInt64          mPageId;                // 로그가 기록된 Page ID
    dbmInt32          mPrevOffset;            // 내 로그의 이전 로그 위치
    dbmInt32          mOffset;                // 내 로그가 기록된 Page내의 Offset
    dbmInt32          mSize;                  // 로그헤더를 제외한 로그데이터의 크기
    dbmInt32          mRowSize;               // Row Size
    dbmInt64          mSCN;                   // Commit시점에 설정될 것임 (Repl은 공유한다.)
    dbmInt64          mRelExtraKey;           // 로그와 연관된 Slot ExtraKey
    dbmInt64          mRelSlotId;             // 로그와 연관된 Slot ID
    dbmLogType        mLogType;               // DDL/DML Log Type
    dbmTableInfo    * mObjectInfo;            // 살아있을때만 유효한 TableSegment ShmInfo(Repl은 못쓴다.)
    dbmInt64          mObjectId;              // 살아있을때 ObjectInfo의 TableId
    dbmBool           mNeedSkip;                             // Paritial Rollback시 로그스킵을 위한 플래그
    dbmBool           mIsMemCommit;                          // memCommit flag
    dbmBool           mIsValid;                              // 로그의 유효성
    dbmChar           mObjectName[ DBM_OBJECT_NAME_LEN + 1 ]; // Target Object Name
    dbmChar           mAddition[ DBM_OBJECT_NAME_LEN + 1 ];   // 부가 정보
} dbmTransLogHeader;


typedef struct
{
    void            * mNodePtr;               // 현재 탐색중인 Index Node Pointer
    dbmInt64          mNodeId;                // Node ID
    dbmInt64          mModified;              // Node Modified
    dbmInt32          mCount;                 // Count
    dbmInt64          mAllocCount;            // 현시점의 전체 노드개수
    dbmInt64          mPrevNodeId;
    dbmInt64          mNextNodeId;
} dbmPathInfo;


typedef struct
{
    dbmThread                 mTID;           // Thread ID
    dbmContext                mSocket;        // Socket
    volatile dbmThreadStat    mStatus;        // Status
    dbmInt32                  mConnTimeoutMs;
    dbmInt32                  mHBInterval;
} dbmReplicaArg;



typedef struct
{
    dbmThread                 mTID;           // Thread ID
    dbmContext                mSocket;        // Socket
    volatile dbmThreadStat    mStatus;        // Status
    dbmInt32                  mConnTimeoutMs;
    dbmInt32                  mHBInterval;
} dbmRemoteArg;



typedef struct
{
    dbmInt64                  mSCN;
    dbmLogType                mLogType;
    dbmInt32                  mSize;
    dbmInt64                  mSlotId;
    dbmInt64                  mExtraKey;
    dbmBool                   mIsDeleted;
    dbmTime                   mExpireTime;
    dbmInt64                  mObjectSCN;    // ObjectSCN이 같을때 반영되도록 일단 구현은 차차하고 Reserved 해보자.
    dbmChar                   mObjectName[ DBM_OBJECT_NAME_LEN + 1];
} dbmReplLogHeader;




typedef struct
{
    dbmInt32          mLogCount;              // Log Total Count (except BlockHeader)
    dbmInt32          mBlockCount;            // 512byte로 몇개 Block으로 구성된건지 개수 (헤더포함)
    dbmInt64          mSCN;                   // 이 로그가 기록될 시점의 채번된 SCN
    dbmInt64          mLSN;                   // LogCache의 시작위치
    dbmTime           mTime;                  // Time
    dbmInt64          mMark;                  // Block Header Mark
} dbmDiskBlockHeader;


typedef struct
{
    dbmInt32          mSize;                  // 데이터 파트의 길이
    dbmLogType        mLogType;               // DDL/DML Log Type
    dbmInt64          mSlotId;                // 로그와 연관된 Slot ID
    dbmInt64          mRowSize;               // Record 길이만큼
    dbmChar           mObjectName[ DBM_OBJECT_NAME_LEN + 1]; // Table Name
    dbmBool           mIsApply;               // 반영여부
    dbmInt64          mMark;                  // Disk Log Mark
} dbmDiskLogHeader;



typedef struct
{
    dbmInt32          mMsgType;
    dbmInt32          mPriority;
    dbmInt64          mMsgId;
    dbmInt32          mMsgSize;     // msgSize or Timeout(millisecond)
    dbmTime           mInTime;
} dbmQueueMsgHeader;


/**
 * CS req : dbmProtocolHeader + dbmCsReq + data
 * CS res : dbmProtocolHeader + dbmCsRes + data
 *
 * msg type별 구조체
 * DBM_REMOTE_CONNECT_INFO ~ DBM_REMOTE_UPDATE_BY_COLS : dbmCsReq, dbmCsRes
 * DBM_REMOTE_REPL                                     : dbmCsReq, ...
 *
 */

typedef struct
{
    dbmChar              mProto[6]; // Normal=API, HTTP=POST,PUT,GET,DELETE,STATUS, JSON=JSON
    dbmInt32             mSize;     // header + body size
    dbmTcpType           mType;
} dbmTcpHeader;


typedef struct
{
    dbmChar              mObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt32             mSize;      // Array Operation일때만 쓴다.
    dbmInt32             mCount;     // Array Operation일때만 쓴다.
} dbmCsReq;

typedef struct
{
    dbmInt32            mRowCount;
    dbmInt32            mIsCont;
    dbmParseType        mParseType;
    dbmInt32            mErrorCode;
    // mErrorMsg 부분을 array로 크게 잡으면 성공인 경우에도 계속 Tcp로 전송이 됨으로 1 만 잡음.
    //  dbmCsRes는 실제로 할당되는 부분이 아니고 SendBuf(or RecvBuf)에 type casting으로 사용됨.
    dbmChar             mErrorMsg[1];   
} dbmCsRes;

#if 0
typedef struct
{
    dbmInt32             mSize;
    dbmTcpType           mLogType;
    dbmChar              mObjectName1[ DBM_OBJECT_NAME_LEN + 1 ];
} dbmRemoteCommHeader;



typedef struct
{
    dbmInt32            mSize;
    dbmInt32            mRowCount;
    dbmInt32            mIsCont;
    dbmParseType        mParseType;
    dbmInt32            mErrorCode;
    dbmChar             mErrorMsg[512];
} dbmRemoteResult;
#endif


typedef struct
{
    dbmList         * mInstantList;
    dbmChar           mObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
} dbmInstantTable;


typedef struct
{
    dbmChar         * mColumnName;
    void            * mDataPtr;
    dbmInt32          mDataSize;
    dbmDataType       mDataType;
    dbmInt32          mOffset;
    dbmInt32          mColumnSize;
    dbmBool           mIsBind;
} dbmBindingItem;


typedef struct
{
    dbmTableType   mTableType;
    dbmInt32       mSlotSize;
    dbmInt64       mCreateSCN;
    dbmChar        mInstName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar        mObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt64       mMark;
} dbmDataFileHeader;


typedef struct
{
    dbmFile        mFileDesc;
    dbmTableType   mTableType;
    dbmInt32       mSlotSize;
    dbmInt32       mStartOffset;
    dbmInt64       mCreateSCN;
    dbmInt64       mLastSCN;
    dbmChar        mObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar      * mBuffer;
} dbmDataFileInfo;



typedef struct
{
    dbmInt32       mTotalSize;
    dbmInt32       mBlockCount;
    dbmInt32       mLogCount;
    dbmInt64       mSCN;
    dbmInt64       mMark;
} dbmReplUnSentBlockHeader;



typedef struct
{
    dbmInt32       mLock;
    dbmInt64       mWriteFileNo;
    dbmInt64       mRemoveFileNo;
    dbmInt64       mWriteInd;
    dbmInt64       mReadInd;
    dbmInt64       mLogFileSize;
} dbmReplAnchor;



typedef struct
{
    dbmChar          * mName;
    dbmInt32           mErrorCode;
} dbmProcPreDefException;


typedef struct
{
    dbmChar          * mName;
    dbmInt32           mErrorCode;
    dbmChar          * mErrorMsg;
} dbmProcException;



typedef struct
{
    void                * mParentVar;
    dbmChar             * mName;
    dbmDataType           mDataType;
    dbmInt32              mSize;
    dbmChar             * mDataPtr;
} dbmProcElementVar;




typedef struct
{
    dbmChar             * mName;
    dbmProcDeclareType    mDeclareType;
    dbmDataType           mDataType;
    dbmInt32              mSize;
    dbmChar             * mDataPtr;
    dbmChar             * mSrcName1;
    dbmChar             * mSrcName2;
    dbmList             * mElementList;
    dbmExprCommon       * mInitValue;
} dbmProcVariable;




typedef struct
{
    dbmChar               * mName;
    dbmProcDeclareType      mDeclareType;
    void                  * mProcBlock;
    void                  * mSelectPlan;
} dbmProcCursor;




typedef struct
{
    dbmProcObjectType       mProcObjType;
    dbmProcDeclareType      mDeclareType;
    void                  * mProcObj;
    void                  * mElemObj;
} dbmProcIntoElem;



typedef struct
{
    dbmChar               * mName;
    dbmDataType             mDataType;
    dbmInt32                mSize;
    dbmInt32                mOffset;
} dbmProcParamElem;


typedef struct
{
    dbmChar               * mName;
    dbmProcDeclareType      mDeclareType;
    dbmDataType             mDataType;
    dbmInt32                mSize;
    dbmParamInOutType       mInOutType;
    dbmList               * mElemList;
    void                  * mTmpValue;
    dbmExprCommon         * mValueExpr;
} dbmProcParam;



/**
 * Prepare때 사용할 공통 Args
 */
typedef struct
{
    void              * mInstRef;           // Instance Ref
    dbmList           * mDicList;           // Dic Shm Ref
    dbmPropInfo       * mPropList;          // Property List
    dbmList           * mTableList;         // Handle의 Main Table List필요
    dbmAllocator      * mAllocator;         // Stmt의 Allocator
    void              * mReplHandle;        // Repl Handle
    void              * mParseObj;          // Parsing된 Object
    dbmList           * mBindParamList;     // Bind Param List
    dbmChar           * mSQLString;         // SQL String
    void              * mProcBlockStmt;     // Parser에 필요한 특정Block지정시에만 설정
    void              * mHandle;            // dbmHandle
} dbmPrepareArg;



/**
 * Execute때 사용할 공통 Args
 */
typedef struct
{
    void              * mInstRef;           // Instance Ref
    dbmList           * mDicList;           // Dic ShmInfo
    dbmPropInfo       * mPropList;          // Property List
    dbmAllocator      * mAllocator;         // Stmt의 Executor Allocator
    void              * mReplHandle;        // Repl Handle
    void              * mDiskLogHandle;     // DiskLog Handle
    void              * mPlanObj;           // Prepare시점에 생성된 Object
    dbmChar           * mSQLString;         // SQL String
    void             ** mEventCallBack;
    void              * mHandle;            // dbmHandle
} dbmExecuteArg;



/**
 * Fetch때 사용할 공통 Args
 */
typedef struct
{
    dbmList           * mTargetExprList;    // Target절에 쓰이는 ExprList
    dbmList           * mRowList;           // Temp Row List (Temporary code)
    dbmInt64            mNodeId;            // IndexInfo를 쓸때
    dbmInt32            mPosition;          // Indexinfo를 쓸때
    dbmIndexInfo      * mIndexInfo;         // Ordering시에
    dbmBool             mIsDesc;
    dbmInt32            mLimitCount;        // Limit절을 썼을 경우
} dbmFetchArg;


/**
 * LogCache Header
 */
typedef struct
{
    dbmUInt32       mBitUsage;
    dbmUInt32       mPadding;
} dbmLogCacheHeader;



/**
 * Sync function
 */


typedef struct
{
    dbmChar          * mSvcName;            // Service 대표이름
    dbmChar          * mDllName;            // create library 시 사용자가 작성한 dll
    dbmDsoHandle       mLibHandle;          // Library-Handle
    void             * mUserContext;        // 사용자Context
    dbmLibFunc         mInitFunc;           // Init Func (Func Addr)
    dbmLibFunc         mFiniFunc;           // Fini Func (Func Addr)
    dbmList          * mFuncList;           // User Function 목록
} dbmLibFuncObject;




/*
typedef struct
{
    volatile dbmInt64         mStamp;
    volatile dbmInt64         mRecvStamp;
    volatile dbmThreadStat    mStatus;
    momAttr                 * mPubAttr;               // PubAttr
    momAttr                 * mSubAttr;               // SubAttr
    momHandle               * mPubHandle;             // PubHandle
    momHandle               * mSubHandle;             // SubHandle
    dbmChar                 * mPubArea;               // Pub Area
    dbmChar                 * mSubArea;               // Sub Area
    momMsg                  * mMsg;
    dbmChar                   mHandleId[ DBM_OBJECT_NAME_LEN + 1 ]; // Unique 한 수신Topic용으로 쓰자
} dbmMomHandle;
*/



typedef struct
{
    dbmInstanceRef          * mInstRef;               // Instance ShmInfo
    dbmAllocator            * mAllocator;             // Handle 유효한 구간에서 쓸 메모리관리자
    dbmList                 * mDicTableList;          // Dictionary Table List
    dbmAllocator            * mExecAllocator;         // API에 Execute때마다 사용할 메모리관리자
    dbmList                 * mTableList;             // 처리에 필요한 Table List
    dbmPropInfo             * mProps;                 // Property List
    dbmErrorStack           * mErrorStack;            // ErrorStack
    dbmDiskLogHandle        * mDiskLogHandle;         // Disk Log Handle
    dbmReplHandle           * mReplHandle;            // 이중화가 사용될 경우 필요한 Handle
    dbmList                 * mRemoteStmtList;        // Remote Stmt List
    dbmRemoteHandle         * mRemoteHandle;          // Remote Connection Handle
    dbmFileHandle           * mTraceHandle;           // Trace Log File Handle
    dbmChar                 * mRecvTopicStr;          // RecvTopicStr
    dbmList                 * mUserLibList;           // UserLibList
    dbmChar                 * mInstName;              // Instance Name
    void                    * mEventCallBack[DBM_CALL_BACK_TYPE_MAX];  
    volatile dbmThreadStat    mMinThreadStat;
    dbmInt64                  mMark;                  // for validation
} dbmInternalHandle;




typedef struct
{
    dbmExprCommon       * mCondExpr;
    dbmExprCommon       * mValueExpr;
} dbmDecodeItem;



typedef struct
{
    void        * mEnv;
} dbmODBCEnv;


typedef struct
{
    dbmODBCEnv  * mEnv;
    void        * mHandle;
} dbmODBCDbc;


typedef struct
{
    dbmODBCDbc  * mDbc;
    void        * mStmt;
    void        * mBindTarget;
} dbmODBCStmt;


typedef struct
{
    dbmPlanType   mPlanType;
    dbmInt64      mStamp;
    dbmInt32      mErrCode;
    dbmChar       mTableName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt32      mDataLen;
    dbmChar       mData[1];           // PlanType:I (x), U/D (rowCount), S (row)
} dbmRetMessage;


typedef struct
{
    dbmPlanType   mPlanType;
    dbmInt64      mStamp;
    dbmChar       mRecvTopic[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar       mTableName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt32      mDataLen;
    dbmChar       mData[1];
} dbmMessage;


#endif


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
    dbmChar           * mInstName;        // Segment??? ?????? InstanceName
    dbmChar           * mSegmentName;     // ?????? SegmentName
    dbmInt64            mDDLCount;        // ?????? Segment??? DDL?????? ??????
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
    dbmChar          * mTempBuf;          // Internal Node??? ?????? ????????????
    dbmChar          * mPathInfoPtr;      // Scan Path History
    dbmChar          * mIterator;         // exec???????????? ????????? ??????????????????
    dbmChar          * mTmpNodePtr;       // exec???????????? ????????? Node?????? ??????
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
    dbmInt64           mCurrNodeId;    // IndexInfo??? ?????? ????????? ?????? ????????? ????????? NodeId
    dbmInt32           mCurrPosition;  // IndexInfo??? ?????? ????????? ?????? ????????? ????????? Position in Node
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
 * Header size??? 512 byte??? ??????
 */
typedef struct
{
    dbmInt64        mFileVersion;
    dbmFileTypeEx   mFileType;
    dbmChar         mDummy[500];
} dbmFileHeader;



typedef struct
{
    volatile dbmInt64   mLogFileNo;       // Disk Logging??? ???????????? ????????? ??????????????????
    volatile dbmInt64   mLogFileOffset;   // Disk Logging??? ????????? ????????? ??????Offset
    volatile dbmInt64   mCkptFileNo;      // Ckpt??? ????????? File No
    volatile dbmInt64   mArchiveFileNo;   // Archive StartNo
    volatile dbmInt64   mCaptureFileNo;   // Capture??? ????????? File No
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
    dbmShmInfo         * mShmInfo;        // Instance??? ?????? Segment
    dbmInt32             mTransId;        // TransId
    dbmInt64             mViewSCN;        // Select??? ????????? ViewSCN
    dbmInt32             mSpinLockCount;  // TryLock??? ?????? ?????????????????? ??????
    dbmInt32             mLockSleepUs;    // LockWait??? Sleep??? Time(us)
    dbmInt32             mAgingInterval;  // Aging????????? MinView??? ???????????? ??????
    dbmBool              mCommitWait;     // CommitWait Mode
    dbmBool              mMvccEnable;     // Mvcc Enable 
    dbmBool              mBeginCursor;    // Cursor ????????????
    dbmChar            * mAnchorPtr;      // Anchor Map
    dbmChar            * mReplAnchorPtr;  // Repl Anchor Ptr
    dbmPropInfo        * mProps;          // Handle??? PropList??? ?????????
    dbmChar            * mPerfStatPtr;    // PerfMemory ??????
    dbmBool              mTraceLogMode;   // Trace Log??? PBT??? ?????? ?????? ????????? ????????? ??????
    dbmLibFuncSymbol   * mExpiredCallBack;   
} dbmInstanceRef;


typedef struct
{
    dbmShmInfo         * mTableShm;       // Table Segment
    dbmIndexInfo       * mCurrIndex;      // ?????? ???????????? IndexInfo Pointer
    dbmList            * mIndexList;      // Table?????? ?????? Index List
    dbmChar            * mTempBuf;        // Data ????????? ?????? ?????? ?????? ??????
    dbmInt32             mRowSize;        // RowSize ??????
    dbmBool              mIsRepl;         // Repl ?????? ????????? ??????
    dbmChar            * mBindBuf;        // Binding ?????? ?????? ?????? ??????
    dbmList            * mColumnList;     // ColumnInfo (dbmDicColumn)
    dbmChar            * mDataSet;        // Data ????????? ?????? ?????? ?????? ??????
    dbmInt64             mCreateSCN;      // Table??? ????????? SCN
    dbmInt64             mExtraKey;       // NonUnique-FetchNext ????????? ?????? ExtraKey
    dbmInt64             mLastFetchedSlot; // ????????? Fetched??? SlotId
    dbmList            * mBindList;       // Binding ?????? ?????????
    dbmInt64             mObjectId;       // Table Object ID
    dbmBool              mLatencyEnable;  // LockWait??? Sleep????????????
    dbmBool              mIsUpdateMode;   // Update-Mode??? ??????????????? ??????
    dbmInt64             mTargetSlotId;   // Update??? Slot??????
    dbmInt64             mTargetExtraKey; // Update??? ExtraKey??????
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
    dbmInt32            mArraySize;      // Array Operation????????? ??????.
    dbmInt32            mArrayCount;     // Array Operation????????? ??????.

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
 * ????????? ???????????? size
 */
#define DBM_REQ_HEADER_SIZE         ( sizeof(dbmReqBuf) - 16 )
#define DBM_RES_HEADER_SIZE         ( sizeof(dbmResBuf) - 16 )

#define DBM_REPL_HEADER_SIZE        ( sizeof(dbmRepl) - 16 )
#define DBM_REPL_ACK_HEADER_SIZE     ( sizeof(dbmReplAck) - 16 )

#define DBM_CAPTURE_HEADER_SIZE        ( sizeof(dbmCapture) - 16 )
#define DBM_CAPTURE_ACK_HEADER_SIZE     ( sizeof(dbmCaptureAck) - 16 )

typedef struct
{
    dbmContext           mMainSocket;     // Connect??? ?????? Socket fd
    dbmInt32             mRemoteTransId;  // Remote TransID
    dbmInt32             mAffectedCount;  // ???????????? ????????? RowCount??? ??????
    dbmReqBuf            mSendBuf;        // Send Buf
    dbmResBuf            mRecvBuf;        // Recv Buf
    dbmInt32             mRecvTimeoutMs;  // Recv Timeout
    dbmChar              mTargetIP[16];   // ????????? ??????IP
    dbmInt32             mTargetPort;     // ????????? ??????Port
    dbmList            * mTableList;      // Table??? ??????????????? List??? ?????? ???????????????.
} dbmRemoteHandle;



typedef struct
{
    dbmThread            mRetryTid;       // Recv Thread ID
    dbmThreadStat        mThreadStat;     // Recv Thread Status
    dbmContext           mMainSocket;     // Connect??? ?????? Socket fd
    dbmInt32             mRemoteTransId;  // Remote TransID
    dbmRepl              mRepl;           // Send Buf
    dbmReplAck           mReplAck;        // Recv Buf
    dbmBool              mUnSentDiskMode; // ???????????? ?????????????????? ?????? ??????
    dbmChar            * mUnSentBuf;      // ?????????????????? ??????
    dbmFile              mUnSentFile;     // ????????? ????????? ??????Desc
    dbmInt32             mUnSentBufSize;  // ?????????????????? ????????? ??????
    dbmInt64             mUnSentFileNo;   // ????????????
    dbmPropInfo        * mPropList;       // PropList Pointer
    dbmInstanceRef     * mInstRef;        // Handle??? InstRef??? ???????????? ???
    dbmChar              mPrimaryIP[16];  // Target IP
    dbmInt32             mPortNo;         // PORT
    dbmInt32             mConnTimeoutMs;
    dbmInt32             mRecvTimeoutMs;
    dbmTableInfo       * mReplUnSent;
    dbmTableInfo       * mReplLog;
    dbmInt64             mUnSentAckCount;
    dbmBool              mAsyncDML;       // Async????????? DML??? ???????????? ??????
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
    dbmFile              mFD;                 // Disk ????????? ?????? FD
    dbmInt64             mLastOffset;         // ????????? ??????
    dbmChar            * mBuffer;             // Log??? ?????? ?????? ?????? (512Byte??? ??????????????? N?????? ????????? ??????)
    dbmChar            * mFileName;           // File Name ????????? ?????? ????????????
    dbmInstanceRef     * mInstRef;            // Instance Pointer
    dbmLogInfo         * mLogInfo;            // LogFile??? ?????? ?????? ==> dbmTrans??? LogInfo??? ????????????.
    dbmAllocator       * mAllocator;          // Allocator
    dbmChar            * mLogDir;             // Log Dir
    dbmInt32             mSize;               // Log piece??? merge?????? ????????? ?????? ?????? (BlockHeader??????)
    dbmList            * mLogList;            // Log piece List
    dbmInt64             mFileSize;           // Log File??? ?????? ?????? ??????
    dbmInt32             mBufferSize;         // ????????? BufferSize??? ?????? ??????
    dbmLogCacheInfo      mLogCacheInfo;       // LogCache????????? ????????? ?????????
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
    dbmAllocator       * mAllocator;           // Stmt ?????? ????????? parser/prepare??? ??????????????????
    dbmAllocator       * mExecAllocator;       // stmt ?????? execute?????? ????????? ??????????????????
    dbmParserContext   * mParseCtx;            // parser?????? ????????? context
    void               * mPlanObj;             // parser/prepare ?????? ???????????? Plan Pointer
    dbmList            * mBindColList;         // Fetch??? ????????? ????????? ??????(Remote ?????? ???????????? ??????)
    dbmChar            * mSQLString;           // SQL text
    dbmChar            * mDataPtr;             // ????????? ??????
    dbmList            * mRemoteTargetList;    // Remote TargetList
    dbmList            * mRemoteBindParamList; // RemoteBindParam List
    dbmResultSet       * mRemoteResultSet;     // Remote ResultSet
    dbmInt64             mRemoteAddr;          // ??????????????? ????????? ????????? ?????????
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
    dbmInt64            mCurrUndoPage;          // ?????? ???????????? Undo Page ID
    dbmInt64            mFirstUndoPage;         // ????????? ???????????? Undo Page ID
    dbmInt64            mLastUndoPage;          // ?????? ???????????? Undo Page ID
    dbmInt64            mSavePointPage;         // Save Point??? ?????? ?????? ????????? ?????? UndoPage ID
    dbmInt32            mSavePointOffset;       // Save Point??? ?????? ?????? ????????? ?????? Page?????? Offset
    dbmInt32            mSavePointPrevOffset;   // Page?????? ?????? ????????? ????????? ??????
    volatile dbmInt32   mWaitForTransId;        // ?????? ???????????? ????????? TransId
    dbmChar             mWaitForObjectName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt64            mWaitForSlotId;         // ???????????? SlotId
    dbmInt64            mSCN;                   // ?????? SCN
    dbmInt64            mViewSCN;               // ?????? View SCN, begin?????? ??????,
    dbmBool             mBeginTrans;            // ?????? ???????????????, init,commit,rollback,recovery??? false
    dbmTransStat        mTransStat;             // TransStat
    dbmBool             mIsLogging;             // Disk Logging Flag
    dbmBool             mIsRepl;                // Repl Flag
    dbmInt64            mHeadSlot;              // Direct Queue??? ?????? ????????????
    dbmInt64            mTailSlot;              // Direct Queue??? ?????? ????????????
    dbmChar             mLastIndex[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmInt64            mLastNodeId;
    dbmBool             mIsTreeLock;
    dbmTime             mBeginTime;             // ????????? Tx ?????? ???????????? ??????????????? ?????????
    dbmInt64            mCheckAliveCnt;         // Check Alive cnt ????????? ???????????? process begin time??? ???????????????
                                                // shared memory??? ????????? ???.
    dbmPerfInfo         mPerfInfo;              // PerfInfo
    dbmBool             mBeginXA;               // xa_start??? ??????
    dbmBool             mEndXA;                 // xa_end??? ??????
    dbmChar             mXID[152];              // xa_start??? ??????
} dbmTrans;



typedef struct
{
    dbmInt64             mPrevPageId;           // ?????? ?????? UndoPage
    dbmInt64             mNextPageId;           // ?????? ?????? UndoPage
    dbmInt32             mPrevOffset;           // ?????? ????????? ????????? ?????? ??????
    dbmInt32             mCurrOffset;           // ?????? ??? Page?????? Offset
    dbmInt32             mTransId;              // ???????????? TxID
} dbmUndoPageHeader;




typedef struct
{
    dbmLogCacheMode        mLogCacheMode;       // LogCache Mode
    dbmSize                mLogCacheSizePerFile;  // Create????????? ????????? File??? LogCache Size
    dbmInt32               mLogCacheCount;      // Create????????? ????????? LogCache ??????
    dbmInt32               mLogCacheRange;      // Create????????? ????????? LogCache ?????? ??????
} dbmLogCache;


typedef struct
{
    volatile dbmInt32      mLock;               // Trans ????????? ????????? Lock
    volatile dbmInt32      mIsActive;           // Active ??????
    volatile dbmInt64      mSCN;                // SCN
    volatile dbmInt64      mMinViewSCN;         // beginCursor??? ?????? minSCN
    volatile dbmInt64      mReplSendSCN;        // ????????? ????????? ?????? SCN
    volatile dbmInt64      mReplAckSCN;         // ????????? ????????? ?????? SCN
    volatile dbmInt64      mObjectId;           // Object Id ?????????
    dbmInt64               mLogFileSize;        // Instance ????????? ???????????? ????????? ??? ??????.
    dbmBool                mIsDiskLogEnable;    // Disk Log Mode
    dbmBool                mIsThreadSleep;      // DEBUG??? TestSleep
    dbmLogCache            mLogCache;           // LogCache
    dbmTime                mCreateTime;                       // ????????????
    dbmChar                mName[ DBM_OBJECT_NAME_LEN + 1 ];  // Name
} dbmTransHeader ;



typedef struct
{
    volatile dbmInt32    mLock;            // Row Lock
    volatile dbmInt32    mSize;            // Size?????? ???????????????
    dbmInt64             mExtraKey;        // ?????? ????????? ???????????? ?????? ID (Non-unique??? ?????????)
    volatile dbmInt64    mSCN;             // SCN
    volatile dbmInt64    mDeleteSCN;       // deleteSCN
    volatile dbmInt64    mPrevRID;         // MVCC ????????? ?????? ?????? ????????? ????????? SlotID??? ????????????.
    volatile dbmInt64    mNextRID;         // MVCC ????????? ?????? ?????? ????????? ????????? SlotID??? ????????????.
    volatile dbmInt64    mUndoPageId;      // ?????? Tx??? ????????? BeforeImage??? ????????? UndoPageId
    volatile dbmLogType  mLogType;         // ?????? Row??? ???????????? Tx Type
    volatile dbmInt32    mUndoOffset;      // ?????? Tx??? ????????? BeforeImage??? ????????? UndoPage?????? Offset
    volatile dbmTime     mExpireTime;      // ????????? ??????.
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
    volatile dbmInt64      mAllocCount;             // Node????????? ??????, ????????? ??????
    dbmBool                mIsUnique;               // Uniqueness ??????
    dbmInt32               mKeySize;                // Index Key??? ??????
    dbmIndexWorkType       mWorkType;               // Split????????? WorkType
    dbmInt64               mBeforeNewNodeToSplit;   // Split??? ?????? ?????? ?????? NodeId
    dbmInt64               mBeforeSrcNodeToSplit;   // Split??? ??? NodeId
    dbmInt64               mBeforeParentNodeId;     // Split????????? ????????? parentNode
    dbmInt64               mOldNewNodeToSplit;      // Split??? ?????? ?????? ?????? NodeId
    dbmInt64               mOldSrcNodeToSplit;      // Split??? ??? NodeId
    dbmInt64               mOldParentNodeId;        // Split????????? ????????? parentNode
    dbmInt64               mBeforeRootNode;
    dbmInt64               mBeforeRemoveNodeId;     // DeleteFreeNode??? ????????????
    dbmInt64               mRemovePrevNodeId;       // ??????????????? ????????????ID
    dbmInt64               mRemoveNextNodeId;       // ??????????????? ???????????????ID
    volatile dbmInt32      mRecoveryTID;
    dbmTime                mCreateTime;             // Index ?????? ??????
    dbmChar                mName[ DBM_OBJECT_NAME_LEN + 1]; // Index Name
    dbmChar                mDummy[1024];
} dbmIndexHeader;



typedef struct
{
    volatile dbmInt32     mLock;              // Node Lock
    volatile dbmInt32     mCount;             // Node??? ????????? Key ??????
    volatile dbmInt32     mValid;             // Node ?????????, ????????? Invalid??????
    volatile dbmInt64     mPrevNodeId;        // ??? ????????? ?????? NodeID
    volatile dbmInt64     mNextNodeId;        // ??? ????????? ?????? NodeID
    volatile dbmInt64     mModified;          // ??? ????????? ????????? ???????????? ??????
    dbmIndexBackupStat    mBackupStat;        // memmove??? backup ??????
    dbmInt32              mBeforeCount;       // ??????????????? Count
    dbmInt32              mBeforePosition;    // ??????????????? Position
    dbmInt64              mBeforeParentNode;  // ????????? ParentNodeId
    dbmIndexWorkType      mWorkType;          // ????????????
    dbmBool               mIsLeaf;            // Leaf
    dbmChar               mDummy[256];
} dbmIndexNodeHeader;



typedef struct
{
    volatile dbmInt64     mDataSlotId;        // Table Segment?????? SlotID
    volatile dbmInt64     mExtraKey;          // Extra Key (non-unique ?????????)
    volatile dbmInt64     mLeftNodeId;        // Internal Node??? ?????? Left Node ID??? ????????????.(????????? -1)
    volatile dbmInt64     mRightNodeId;       // Internal Node??? ?????? Right Node ID??? ????????????.(????????? -1)
} dbmIndexSlotHeader;



typedef struct
{
    dbmInt64          mPageId;                // ????????? ????????? Page ID
    dbmInt32          mPrevOffset;            // ??? ????????? ?????? ?????? ??????
    dbmInt32          mOffset;                // ??? ????????? ????????? Page?????? Offset
    dbmInt32          mSize;                  // ??????????????? ????????? ?????????????????? ??????
    dbmInt32          mRowSize;               // Row Size
    dbmInt64          mSCN;                   // Commit????????? ????????? ?????? (Repl??? ????????????.)
    dbmInt64          mRelExtraKey;           // ????????? ????????? Slot ExtraKey
    dbmInt64          mRelSlotId;             // ????????? ????????? Slot ID
    dbmLogType        mLogType;               // DDL/DML Log Type
    dbmTableInfo    * mObjectInfo;            // ?????????????????? ????????? TableSegment ShmInfo(Repl??? ?????????.)
    dbmInt64          mObjectId;              // ??????????????? ObjectInfo??? TableId
    dbmBool           mNeedSkip;                             // Paritial Rollback??? ??????????????? ?????? ?????????
    dbmBool           mIsMemCommit;                          // memCommit flag
    dbmBool           mIsValid;                              // ????????? ?????????
    dbmChar           mObjectName[ DBM_OBJECT_NAME_LEN + 1 ]; // Target Object Name
    dbmChar           mAddition[ DBM_OBJECT_NAME_LEN + 1 ];   // ?????? ??????
} dbmTransLogHeader;


typedef struct
{
    void            * mNodePtr;               // ?????? ???????????? Index Node Pointer
    dbmInt64          mNodeId;                // Node ID
    dbmInt64          mModified;              // Node Modified
    dbmInt32          mCount;                 // Count
    dbmInt64          mAllocCount;            // ???????????? ?????? ????????????
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
    dbmInt64                  mObjectSCN;    // ObjectSCN??? ????????? ??????????????? ?????? ????????? ???????????? Reserved ?????????.
    dbmChar                   mObjectName[ DBM_OBJECT_NAME_LEN + 1];
} dbmReplLogHeader;




typedef struct
{
    dbmInt32          mLogCount;              // Log Total Count (except BlockHeader)
    dbmInt32          mBlockCount;            // 512byte??? ?????? Block?????? ??????????????? ?????? (????????????)
    dbmInt64          mSCN;                   // ??? ????????? ????????? ????????? ????????? SCN
    dbmInt64          mLSN;                   // LogCache??? ????????????
    dbmTime           mTime;                  // Time
    dbmInt64          mMark;                  // Block Header Mark
} dbmDiskBlockHeader;


typedef struct
{
    dbmInt32          mSize;                  // ????????? ????????? ??????
    dbmLogType        mLogType;               // DDL/DML Log Type
    dbmInt64          mSlotId;                // ????????? ????????? Slot ID
    dbmInt64          mRowSize;               // Record ????????????
    dbmChar           mObjectName[ DBM_OBJECT_NAME_LEN + 1]; // Table Name
    dbmBool           mIsApply;               // ????????????
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
 * msg type??? ?????????
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
    dbmInt32             mSize;      // Array Operation????????? ??????.
    dbmInt32             mCount;     // Array Operation????????? ??????.
} dbmCsReq;

typedef struct
{
    dbmInt32            mRowCount;
    dbmInt32            mIsCont;
    dbmParseType        mParseType;
    dbmInt32            mErrorCode;
    // mErrorMsg ????????? array??? ?????? ????????? ????????? ???????????? ?????? Tcp??? ????????? ????????? 1 ??? ??????.
    //  dbmCsRes??? ????????? ???????????? ????????? ????????? SendBuf(or RecvBuf)??? type casting?????? ?????????.
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
 * Prepare??? ????????? ?????? Args
 */
typedef struct
{
    void              * mInstRef;           // Instance Ref
    dbmList           * mDicList;           // Dic Shm Ref
    dbmPropInfo       * mPropList;          // Property List
    dbmList           * mTableList;         // Handle??? Main Table List??????
    dbmAllocator      * mAllocator;         // Stmt??? Allocator
    void              * mReplHandle;        // Repl Handle
    void              * mParseObj;          // Parsing??? Object
    dbmList           * mBindParamList;     // Bind Param List
    dbmChar           * mSQLString;         // SQL String
    void              * mProcBlockStmt;     // Parser??? ????????? ??????Block??????????????? ??????
    void              * mHandle;            // dbmHandle
} dbmPrepareArg;



/**
 * Execute??? ????????? ?????? Args
 */
typedef struct
{
    void              * mInstRef;           // Instance Ref
    dbmList           * mDicList;           // Dic ShmInfo
    dbmPropInfo       * mPropList;          // Property List
    dbmAllocator      * mAllocator;         // Stmt??? Executor Allocator
    void              * mReplHandle;        // Repl Handle
    void              * mDiskLogHandle;     // DiskLog Handle
    void              * mPlanObj;           // Prepare????????? ????????? Object
    dbmChar           * mSQLString;         // SQL String
    void             ** mEventCallBack;
    void              * mHandle;            // dbmHandle
} dbmExecuteArg;



/**
 * Fetch??? ????????? ?????? Args
 */
typedef struct
{
    dbmList           * mTargetExprList;    // Target?????? ????????? ExprList
    dbmList           * mRowList;           // Temp Row List (Temporary code)
    dbmInt64            mNodeId;            // IndexInfo??? ??????
    dbmInt32            mPosition;          // Indexinfo??? ??????
    dbmIndexInfo      * mIndexInfo;         // Ordering??????
    dbmBool             mIsDesc;
    dbmInt32            mLimitCount;        // Limit?????? ?????? ??????
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
    dbmChar          * mSvcName;            // Service ????????????
    dbmChar          * mDllName;            // create library ??? ???????????? ????????? dll
    dbmDsoHandle       mLibHandle;          // Library-Handle
    void             * mUserContext;        // ?????????Context
    dbmLibFunc         mInitFunc;           // Init Func (Func Addr)
    dbmLibFunc         mFiniFunc;           // Fini Func (Func Addr)
    dbmList          * mFuncList;           // User Function ??????
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
    dbmChar                   mHandleId[ DBM_OBJECT_NAME_LEN + 1 ]; // Unique ??? ??????Topic????????? ??????
} dbmMomHandle;
*/



typedef struct
{
    dbmInstanceRef          * mInstRef;               // Instance ShmInfo
    dbmAllocator            * mAllocator;             // Handle ????????? ???????????? ??? ??????????????????
    dbmList                 * mDicTableList;          // Dictionary Table List
    dbmAllocator            * mExecAllocator;         // API??? Execute????????? ????????? ??????????????????
    dbmList                 * mTableList;             // ????????? ????????? Table List
    dbmPropInfo             * mProps;                 // Property List
    dbmErrorStack           * mErrorStack;            // ErrorStack
    dbmDiskLogHandle        * mDiskLogHandle;         // Disk Log Handle
    dbmReplHandle           * mReplHandle;            // ???????????? ????????? ?????? ????????? Handle
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


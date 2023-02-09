#ifndef __DBM_PARSER_OBJECT_H_
#define __DBM_PARSER_OBJECT_H_ 1




typedef enum
{
    DBM_PARSE_EXPR_INVALID = 0,
    DBM_PARSE_EXPR_CONST,
    DBM_PARSE_EXPR_FUNCTION,
    DBM_PARSE_EXPR_IDENTIFIER,
    DBM_PARSE_EXPR_BIND_PARAM,
    DBM_PARSE_EXPR_HOST_VARIABLE,
    DBM_PARSE_EXPR_USER_LIB_FUNCTION,
    DBM_PARSE_EXPR_NULL,
    DBM_PARSE_EXPR_MAX
} dbmParseExprType;


typedef enum
{
    DBM_PARSE_FUNCTION_INVALID = 0,
    DBM_PARSE_FUNCTION_NE,
    DBM_PARSE_FUNCTION_EQ,
    DBM_PARSE_FUNCTION_LT,
    DBM_PARSE_FUNCTION_LE,
    DBM_PARSE_FUNCTION_GE,
    DBM_PARSE_FUNCTION_GT,
    DBM_PARSE_FUNCTION_LIKE,
    DBM_PARSE_FUNCTION_AND,
    DBM_PARSE_FUNCTION_OR,
    DBM_PARSE_FUNCTION_PLUS,
    DBM_PARSE_FUNCTION_MINUS,
    DBM_PARSE_FUNCTION_MULTIPLE,
    DBM_PARSE_FUNCTION_DIVIDE,
    DBM_PARSE_FUNCTION_COUNT,
    DBM_PARSE_FUNCTION_SUM,
    DBM_PARSE_FUNCTION_AVG,
    DBM_PARSE_FUNCTION_MINVAL,
    DBM_PARSE_FUNCTION_MAXVAL,
    DBM_PARSE_FUNCTION_SYSDATE,
    DBM_PARSE_FUNCTION_DUMP,
    DBM_PARSE_FUNCTION_CONCAT,
    DBM_PARSE_FUNCTION_ABS,
    DBM_PARSE_FUNCTION_MOD,
    DBM_PARSE_FUNCTION_CEIL,
    DBM_PARSE_FUNCTION_FLOOR,
    DBM_PARSE_FUNCTION_ROUND,
    DBM_PARSE_FUNCTION_TRUNC,
    DBM_PARSE_FUNCTION_SUBSTR,
    DBM_PARSE_FUNCTION_NEXTVAL,
    DBM_PARSE_FUNCTION_CURRVAL,
    DBM_PARSE_FUNCTION_IN,
    DBM_PARSE_FUNCTION_HEX,
    DBM_PARSE_FUNCTION_DIGEST,
    DBM_PARSE_FUNCTION_LENGTH,
    DBM_PARSE_FUNCTION_LPAD,
    DBM_PARSE_FUNCTION_RPAD,
    DBM_PARSE_FUNCTION_LTRIM,
    DBM_PARSE_FUNCTION_RTRIM,
    DBM_PARSE_FUNCTION_TRIM,
    DBM_PARSE_FUNCTION_DATETIME_STR,
    DBM_PARSE_FUNCTION_RANDOM,
    DBM_PARSE_FUNCTION_DECODE,
    DBM_PARSE_FUNCTION_UPPER,
    DBM_PARSE_FUNCTION_LOWER,
    DBM_PARSE_FUNCTION_NVL,
    DBM_PARSE_FUNCTION_TO_DATE,
    DBM_PARSE_FUNCTION_TO_TIMESTAMP,
    DBM_PARSE_FUNCTION_DATEDIFF,
    DBM_PARSE_FUNCTION_SESSION_ID,
    DBM_PARSE_FUNCTION_USERENV,
    DBM_PARSE_FUNCTION_JSON_ADD,
    DBM_PARSE_FUNCTION_JSON_DELETE,
    DBM_PARSE_FUNCTION_JSON_KEY,
    DBM_PARSE_FUNCTION_JSON_QUERY,
    DBM_PARSE_FUNCTION_JSON_STRING,
    DBM_PARSE_FUNCTION_JSON_VALUE,
    DBM_PARSE_FUNCTION_EMPTY_BLOB,
    DBM_PARSE_FUNCTION_EMPTY_CLOB,
    DBM_PARSE_FUNCTION_HEXTORAW,
    DBM_PARSE_FUNCTION_ISNULL,
    DBM_PARSE_FUNCTION_POWER,
    DBM_PARSE_FUNCTION_SQRT,
    DBM_PARSE_FUNCTION_EXP,
    DBM_PARSE_FUNCTION_LN,
    DBM_PARSE_FUNCTION_LOG,
    DBM_PARSE_FUNCTION_REPLACE,
    DBM_PARSE_FUNCTION_INSTR,
    DBM_PARSE_FUNCTION_EXTRACT,
    DBM_PARSE_FUNCTION_MAX
} dbmParseFunctionType;


typedef enum
{
    DBM_PARSE_DATA_TYPE_INVALID,
    DBM_PARSE_DATA_TYPE_SHORT,
    DBM_PARSE_DATA_TYPE_INT,
    DBM_PARSE_DATA_TYPE_DOUBLE,
    DBM_PARSE_DATA_TYPE_FLOAT,
    DBM_PARSE_DATA_TYPE_LONG,
    DBM_PARSE_DATA_TYPE_CHAR,
    DBM_PARSE_DATA_TYPE_DATE,
    DBM_PARSE_DATA_TYPE_POINTER,
    DBM_PARSE_DATA_TYPE_VAL_32,
    DBM_PARSE_DATA_TYPE_VAL_64,
    DBM_PARSE_DATA_TYPE_NULL,
    DBM_PARSE_DATA_TYPE_MAX
} dbmParseDataType;


typedef struct
{
    dbmParseType       mType;
    dbmChar          * mValue;
    dbmInt32           mLineNo;
    dbmInt32           mColumn;
    dbmBool            mIsDoubleQuote;
} dbmParseValue;


typedef struct
{
    dbmParseType       mType;
    dbmParseDataType   mDataType;
    dbmInt32           mSize;
} dbmParseDataTypeDef;


typedef struct
{
    dbmParseType             mType;
    dbmParseValue          * mName;
    dbmParseDataTypeDef    * mDataTypeDef;
} dbmParseColumnDef;




typedef struct
{
    dbmParseType             mType;
} dbmParseDCLStmt;



typedef struct
{
    dbmParseType             mType;
    dbmParseValue          * mSessionId;
} dbmParseSessionTermStmt;



typedef struct
{
    dbmParseType             mType;
    dbmList                * mTableList;
} dbmParseAgingStmt;



typedef struct
{
    dbmParseType             mType;
    dbmList                * mList;
} dbmParseOrderByList;




typedef struct
{
    dbmParseType            mType;
    dbmParseValue         * mStart;
    dbmParseValue         * mCount;
} dbmParseLimit;



typedef struct
{
    dbmParseType             mType;
    dbmParseFunctionType     mFuncType;
    dbmParseValue          * mName;
    dbmParseValue          * mValue;        // for json
    dbmParseValue          * mMaxSize;      // for json
    dbmBool                  mIsAsc;
} dbmParseKeyColumnDef;


typedef struct
{
    dbmParseType             mType;
    dbmParseExprType         mExprType;
    void                   * mOrgExpr;
    dbmParseValue          * mAlias;
} dbmParseExpr;


typedef struct
{
    dbmParseType            mType;
    dbmChar               * mVarName;
    dbmInt32                mBindId;
} dbmParseBindParam;



typedef struct
{
    dbmParseType            mType;
    dbmList               * mFuncName;
    dbmList               * mArgs;
} dbmParseUserLibraryFunction;


typedef struct
{
    dbmParseType            mType;
    dbmParseFunctionType    mFuncType;
    dbmChar               * mOrgStr;
    dbmParseExpr          * mLeftArg;         //@todo 죄다 List화 해야 할듯 함. 
    dbmParseExpr          * mRightArg;   
    dbmParseExpr          * mAdditionalArg1;
    dbmParseExpr          * mAdditionalArg2;
} dbmParseFunction;


typedef struct
{
    dbmParseType            mType;
    dbmBool                 mIsTargetJson;
    void                  * mTargetColumn;    // Identifier 또는 QuoteChain으로 동작
    dbmParseExpr          * mValueExpr;
} dbmParseUpdateSetItem;


typedef struct
{
    dbmParseType           mType;
    dbmParseValue        * mTableName;
    dbmParseValue        * mAlias;
} dbmParseTableSource;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mInitOption;
    dbmParseValue       * mExtendOption;
    dbmParseValue       * mMaxOption;
} dbmParseCreateInstStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mMsgSize;
    dbmParseValue       * mInitOption;
    dbmParseValue       * mExtendOption;
    dbmParseValue       * mMaxOption;
    dbmBool               mIsDirect;
} dbmParseCreateQueueStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mColumn;
    dbmParseValue       * mTimeExpr;
    dbmParseValue       * mTimeUnit;
} dbmParseExpireOption;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTargetTable;
    dbmList             * mTargetList;
} dbmParseCQSet;




typedef struct
{
    dbmParseType            mType;
    dbmParseValue         * mName;
    dbmParseExpireOption  * mExpireOption;
    dbmParseCQSet         * mCQSet;
    dbmParseValue         * mInitOption;
    dbmParseValue         * mExtendOption;
    dbmParseValue         * mMaxOption;
} dbmParseCreateWindowStmt;



typedef struct
{
    dbmParseType          mType;
    dbmTableType          mTableType;
    dbmParseValue       * mName;
    void                * mColumnListOrSize;
    dbmParseValue       * mInitOption;
    dbmParseValue       * mExtendOption;
    dbmParseValue       * mMaxOption;
} dbmParseCreateTableStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmList             * mColumnList;
    dbmParseValue       * mMaxSize;
    dbmParseValue       * mInitOption;
    dbmParseValue       * mExtendOption;
    dbmParseValue       * mMaxOption;
} dbmParseCreateDataSetStmt;




typedef struct
{
    dbmParseType          mType;
    dbmBool               mIsUnique;
    dbmParseValue       * mIndexName;
    dbmParseValue       * mTableName;
    dbmList             * mKeyList;
} dbmParseCreateIndexStmt;




typedef struct
{
    dbmParseValue       * mAliasName;
    dbmParseValue       * mFuncName;
    dbmList             * mParamList;
} dbmParseLibraryItem;





typedef struct
{
    dbmParseType          mType;
    dbmBool               mIsSyncLib;
    dbmParseValue       * mObjectName;
    dbmParseValue       * mDllName;
    dbmParseLibraryItem * mInitFunc;
    dbmParseLibraryItem * mFiniFunc;
    dbmList             * mFuncList;
} dbmParseCreateLibraryStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mInstName;
} dbmParseDropInstStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
} dbmParseDropTableStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mSeqName;
} dbmParseDropSequenceStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mSeqName;
    dbmParseValue       * mCurrVal;
} dbmParseAlterSequenceStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
    dbmParseValue       * mOrgColumn;
    dbmParseValue       * mNewColumn;
} dbmParseAlterTableRenameColumnStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
} dbmParseAlterTableCompactStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
    dbmParseColumnDef   * mColumnDef;
    dbmParseExpr        * mDefaultVal;
} dbmParseAlterTableAddColumnStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
    dbmParseValue       * mColumnName;
} dbmParseAlterTableDropColumnStmt;





typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
    dbmParseValue       * mIndexName;
} dbmParseRebuildIndexStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mIndexName;
} dbmParseDropIndexStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mSvcName;
} dbmParseDropLibraryStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTableName;
} dbmParseTruncateStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mSeqName;
    dbmParseValue       * mStartVal;
    dbmParseValue       * mIncrementVal;
    dbmParseValue       * mMaxVal;
    dbmParseValue       * mMinVal;
    dbmParseValue       * mIsCycle;
} dbmParseCreateSequenceStmt;



typedef struct
{
    dbmParseType          mType;
    dbmReplActDef         mReplAct;
    dbmList             * mTableList;
} dbmParseAlterReplSyncStmt;




typedef struct
{
    dbmParseType          mType;
    dbmBool               mIsDrop;
    dbmList             * mTableList;
} dbmParseAlterReplModStmt;




typedef struct
{
    dbmParseType          mType;
} dbmParseAlterResetPerfStmt;



typedef struct
{
    dbmParseType          mType;
    dbmBool               mIsActive;
} dbmParseAlterSystemInstanceStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mInstName;
    dbmParseValue       * mFileNo;
} dbmParseAlterSystemResetCkptFileStmt;



typedef struct
{
    dbmParseType          mType;
    dbmList             * mTableList;
} dbmParseCreateReplStmt;



typedef struct
{
    dbmParseType          mType;
} dbmParseDropReplStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mCaptureName;
    dbmList             * mTableList;
} dbmParseCreateCaptureStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mCaptureName;
} dbmParseDropCaptureStmt;




typedef struct
{
    dbmParseType          mType;
    dbmList             * mNameList;
    dbmList             * mColumnList;
    dbmList             * mValueList;
} dbmParseOraInsertStmt;



typedef struct
{
    dbmParseType          mType;
    dbmList             * mNameList;
    dbmList             * mSetList;
    dbmParseExpr        * mWhereExpr;
} dbmParseOraUpdateStmt;




typedef struct
{
    dbmParseType          mType;
    dbmList             * mNameList;
    dbmParseExpr        * mWhereExpr;
} dbmParseOraDeleteStmt;






typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmList             * mColumnList;
    dbmList             * mValueList;
    dbmParseValue       * mExpiredTime;
} dbmParseInsertStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmList             * mSetList;
    dbmParseExpr        * mWhereExpr;
} dbmParseUpdateStmt;





typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseExpr        * mWhereExpr;
} dbmParseDeleteStmt;




typedef struct
{
    dbmParseType          mType;
    dbmList             * mTargetList;
    dbmList             * mTableList;
    dbmParseExpr        * mWhereExpr;
    dbmList             * mGroupByList;
    dbmList             * mOrderByList;
    dbmBool               mIsForUpdate;
    dbmParseLimit       * mLimit;
} dbmParseSelectStmt;




typedef struct
{
    dbmParseType          mType;
    dbmList             * mTargetList;
    dbmList             * mIntoList;
    dbmList             * mTableList;
    dbmParseExpr        * mWhereExpr;
    dbmList             * mGroupByList;
    dbmBool               mIsForUpdate;
} dbmParseSelectIntoStmt;





typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmList             * mColumnList;
    dbmList             * mValueList;
} dbmParseEnqueueStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseExpr        * mWhereExpr;
    dbmParseValue       * mTimeOut;
} dbmParseDequeueStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mQuery;
    dbmParseValue       * mSourceDSN;
    dbmParseValue       * mSourceUID;
    dbmParseValue       * mSourcePWD;
    dbmParseValue       * mTargetTable;
    dbmList             * mTargetColList;
    dbmParseValue       * mExpiredTime;
} dbmParseLoadStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mTargetTable;
    dbmList             * mColumnList;
    dbmParseValue       * mSourceQuery;
    dbmParseValue       * mTargetDSN;
    dbmParseValue       * mTargetUID;
    dbmParseValue       * mTargetPWD;
} dbmParseSyncStmt;




typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mProcName;
    dbmList             * mParamList;
} dbmParseExecProcStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mSvrName;
    dbmParseValue       * mProcessCnt;
} dbmParseAlterGsbProcCntStmt;

typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mHostPort;
    dbmParseValue       * mClientMax;
    dbmParseValue       * mProcessMax;
    dbmParseValue       * mUseInflux;
    dbmParseValue       * mInfluxIp;
    dbmParseValue       * mInfluxPort;
    dbmParseValue       * mInfluxDb;
} dbmParseCreateGsbNodeStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
} dbmParseDropGsbNodeStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mNodeName;
    dbmParseValue       * mInfluxIp;
    dbmParseValue       * mInfluxPort;
    dbmParseValue       * mInfluxDb;
} dbmParseCreateGsbMonitorStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
} dbmParseDropGsbMonitorStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mNodeName;
} dbmParseCreateGsbSvrGrpStmt;

typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
} dbmParseDropGsbSvrGrpStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mSvrGrpName;
    dbmParseValue       * mProcessMin;
    dbmParseValue       * mProcessCnt;
    dbmParseValue       * mProcessMax;
    dbmParseValue       * mQSize;
} dbmParseCreateGsbSvrStmt;

typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
} dbmParseDropGsbSvrStmt;


typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
    dbmParseValue       * mSvrName;
    dbmParseValue       * mLibrary;
    dbmParseValue       * mFunction;
} dbmParseCreateGsbSvcStmt;

typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mName;
} dbmParseDropGsbSvcStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParamInOutType     mInOut;
} dbmParseParamInOut;



typedef struct
{
    dbmParseType            mType;
    dbmProcDeclareType      mDeclareType;
    void                  * mDeclareDef;
} dbmParseProcDataTypeDef;



typedef struct
{
    dbmParseType                 mType;
    dbmParseValue              * mName;
    dbmParamInOutType            mInOutType;
    dbmParseProcDataTypeDef    * mDataTypeDef;
} dbmParseParamDef;



typedef struct
{
    dbmParseType             mType;
    dbmInt32                 mLineNo;
    dbmInt32                 mColumn;
    dbmProcDeclareType       mDeclareType;
    void                   * mItem;
} dbmParseDeclareItem;


typedef struct
{
    dbmParseType                 mType;
    dbmParseValue              * mName;
    dbmParseProcDataTypeDef    * mDataTypeDef;
    dbmParseExpr               * mInitValue;
} dbmParseDeclareVar;



typedef struct
{
    dbmParseType             mType;
    dbmProcDeclareType       mDeclareType;
    dbmParseValue          * mName;
    dbmList                * mParamList;
    dbmParseSelectStmt     * mSelectStmt;
} dbmParseDeclareCursor;




typedef struct
{
    dbmParseType             mType;
    dbmProcDeclareType       mDeclareType;
    dbmParseValue          * mName;
    dbmParseValue          * mErrorCode;
} dbmParseDeclareException;




typedef struct
{
    dbmParseType             mType;
    dbmInt32                 mLineNo;
    dbmInt32                 mColumn;
    dbmList                * mDeclareList;
    dbmList                * mStmtList;
    dbmList                * mExceptionList;
} dbmParseProcBlockStmt;


typedef struct
{
    dbmParseType             mType;
    dbmParseValue          * mName;
    dbmList                * mParamList;
    dbmParseProcBlockStmt  * mBlockStmt;
    dbmBool                  mIsReplace;
} dbmParseCreateProcStmt;


typedef struct
{
    dbmProcStmtType          mStmtType;
    dbmInt32                 mLineNo;
    dbmInt32                 mColumn;
    dbmParseValue          * mLabelName;
} dbmParseProcCommon;



typedef struct
{
    dbmList                * mNameList;
    dbmParseExpr           * mValueExpr;
} dbmParseProcAssignStmt;



typedef struct
{
    dbmParseExpr           * mValueExpr;
} dbmParseProcPutLineStmt;



typedef struct
{
    dbmParseValue           * mName;
    dbmList                 * mStmtList;
    dbmInt32                  mLineNo;
    dbmInt32                  mColumn;
} dbmParseProcExceptionItem;



typedef struct
{
    dbmParseType             mType;
    dbmParseProcCommon       mCommon;
    void                   * mStmt;
} dbmParseProcStmt;



typedef struct
{
    dbmParseExpr           * mCondExpr;
    dbmList                * mStmtList;
} dbmParseProcIfItem;



typedef struct
{
    dbmParseProcIfItem     * mFirstIf;
    dbmList                * mElseList;
    dbmParseProcIfItem     * mLast;
} dbmParseProcIfStmt;



typedef struct
{
    dbmList                * mStmtList;
} dbmParseProcLoopStmt;



typedef struct
{
    dbmParseExpr           * mCondExpr;
} dbmParseProcExitStmt;



typedef struct
{
    dbmParseExpr           * mCondExpr;
} dbmParseProcContinueStmt;




typedef struct
{
    dbmParseExpr           * mValueExpr;
    dbmList                * mCondList;
    dbmParseProcIfItem     * mElse;
} dbmParseProcSimpleCaseStmt;



typedef struct
{
    dbmList                * mCondList;
    dbmParseProcIfItem     * mElse;
} dbmParseProcSearchedCaseStmt;



typedef struct
{
    dbmParseDeclareVar     * mParseName;
    dbmBool                  mIsReverse;
    dbmParseExpr           * mFirstExpr;
    dbmParseExpr           * mLastExpr;
    dbmList                * mStmtList;
} dbmParseProcForLoopStmt;



typedef struct
{
    dbmParseExpr           * mCondExpr;
    dbmList                * mStmtList;
} dbmParseProcWhileLoopStmt;



typedef struct
{
    dbmParseValue          * mName;
} dbmParseProcGotoStmt;




typedef struct
{
    dbmParseValue          * mName;
    dbmList                * mParamList;
} dbmParseProcOpenCursorStmt;



typedef struct
{
    dbmParseValue          * mName;
    dbmList                * mIntoList;
} dbmParseProcFetchCursorStmt;



typedef struct
{
    dbmParseValue          * mName;
} dbmParseProcCloseCursorStmt;



typedef struct
{
    dbmParseValue          * mName;
    dbmParseValue          * mErrorCode;
    dbmParseValue          * mErrorMsg;
} dbmParseProcRaiseStmt;                       // RAISE, RAISE_APPLICATION_ERROR이 겸용해서 쓰는중



typedef struct
{
    dbmParseValue          * mName;
    dbmList                * mArgList;
} dbmParseProcCallProcStmt;



typedef struct
{
    dbmParseType          mType;
    dbmParseValue       * mProcName;
} dbmParseDropProcStmt;



typedef struct
{
    dbmParseValue       * mName;
    dbmParseDataType      mDataType;
} dbmParseLibraryParam;



typedef struct
{
    dbmParseType          mType;
    dbmParseExpr        * mCondExpr;
    dbmParseExpr        * mValueExpr;
} dbmParseDecodeItem;



dbmParseValue  * dbmMakeIntValue( dbmParserContext     * aCtx,
                                  dbmBool                aIsMinus,
                                  dbmChar              * aValue );

dbmParseValue  * dbmMakeNumberValue( dbmParserContext     * aCtx,
                                     dbmBool                aIsMinus,
                                     dbmChar              * aValue );

dbmParseValue  * dbmMakeIdentifier( dbmParserContext     * aCtx,
                                    dbmChar              * aValue );

dbmParseValue  * dbmMakeIdentifierList( dbmParserContext     * aCtx,
                                        dbmList              * aList );

dbmParseValue * dbmMakeStrValue( dbmParserContext   * aCtx,
                                 dbmChar            * aValue );

dbmParseDataTypeDef  * dbmMakeDataTypeDef( dbmParserContext     * aCtx,
                                           dbmParseDataType       aDataType,
                                           dbmInt32               aSize );

dbmParseColumnDef  * dbmMakeColumnDef( dbmParserContext     * aCtx,
                                       dbmParseValue        * aName,
                                       dbmParseDataTypeDef  * aDataTypeDef );

dbmParseKeyColumnDef  * dbmMakeKeyColumnDef( dbmParserContext     * aCtx,
                                             dbmParseFunctionType   aFuncType,
                                             dbmParseValue        * aName,
                                             dbmParseValue        * aValue,
                                             dbmParseValue        * aMaxSize,
                                             void                 * aIsAsc );

dbmParseParamDef  * dbmMakeParamDef( dbmParserContext         * aCtx,
                                     dbmParseValue            * aName,
                                     dbmParseParamInOut       * aInOutType,
                                     dbmParseProcDataTypeDef  * aDataTypeDef );

dbmParseBindParam  * dbmMakeBindParam( dbmParserContext     * aCtx,
                                       dbmChar              * aVarName );

dbmParseExpr  * dbmMakeParseExpr( dbmParserContext     * aCtx,
                                  dbmParseExprType       aExprType,
                                  void                 * aOrgExpr );

dbmParseFunction  * dbmMakeParseFunction( dbmParserContext     * aCtx,
                                          dbmParseFunctionType   aFuncType,
                                          void                 * aLeftArg,
                                          void                 * aRightArg,
                                          void                 * aAdditionalArg1,
                                          void                 * aAdditionalArg2 );

dbmParseUpdateSetItem * dbmMakeUpdateSetItem( dbmParserContext       * aCtx,
                                              dbmBool                  aIsJson,
                                              void                   * aColumn,
                                              dbmParseExpr           * aValue );

dbmParseTableSource  * dbmMakeTableSource( dbmParserContext     * aCtx,
                                           dbmParseValue        * aTableName,
                                           dbmParseValue        * aAlias );

dbmParseCreateInstStmt * dbmMakeCreateInstanceStmt( dbmParserContext    * aCtx,
                                                    dbmParseValue       * aInstName,
                                                    dbmParseValue       * aInitOption,
                                                    dbmParseValue       * aExtendOption,
                                                    dbmParseValue       * aMaxOption );

dbmParseCreateQueueStmt  * dbmMakeCreateQueueStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aName,
                                                   dbmParseValue        * aMsgSize,
                                                   dbmParseValue        * aInitOption,
                                                   dbmParseValue        * aExtendOption,
                                                   dbmParseValue        * aMaxOption,
                                                   dbmBool                aIsDirect );

dbmParseCreateTableStmt  * dbmMakeCreateTableStmt( dbmParserContext     * aCtx,
                                                   dbmTableType           aTableType,
                                                   dbmParseValue        * aName,
                                                   void                 * aColumnList,
                                                   dbmParseValue        * aInitOption,
                                                   dbmParseValue        * aExtendOption,
                                                   dbmParseValue        * aMaxOption );

dbmParseCreateDataSetStmt  * dbmMakeCreateDataSetStmt( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aName,
                                                       dbmList              * aColumnList,
                                                       dbmParseValue        * aMaxSize,
                                                       dbmParseValue        * aInitOption,
                                                       dbmParseValue        * aExtendOption,
                                                       dbmParseValue        * aMaxOption );

dbmParseCreateIndexStmt  * dbmMakeCreateIndexStmt( dbmParserContext     * aCtx,
                                                   dbmBool                aIsUnique,
                                                   dbmParseValue        * aIndexName,
                                                   dbmParseValue        * aTableName,
                                                   dbmList              * aKeyList );

dbmParseDropInstStmt  * dbmMakeDropInstanceStmt( dbmParserContext     * aCtx,
                                                 dbmParseValue        * aInstName );

dbmParseDropTableStmt  * dbmMakeDropTableStmt( dbmParserContext     * aCtx,
                                               dbmParseType           aParseType,
                                               dbmParseValue        * aTableName );

dbmParseDropSequenceStmt  * dbmMakeDropSequenceStmt( dbmParserContext     * aCtx,
                                                     dbmParseValue        * aSeqName );

dbmParseDropIndexStmt  * dbmMakeDropIndexStmt( dbmParserContext     * aCtx,
                                               dbmParseValue        * aIndexName );

dbmParseTruncateStmt  * dbmMakeTruncateStmt( dbmParserContext     * aCtx,
                                             dbmParseType           aParseType,
                                             dbmParseValue        * aTableName );

dbmParseInsertStmt  * dbmMakeInsertStmt( dbmParserContext     * aCtx,
                                         dbmParseValue        * aName,
                                         dbmList              * aColumnList,
                                         dbmList              * aValueList,
                                         dbmParseValue        * aExpiredTime );

dbmParseUpdateStmt  * dbmMakeUpdateStmt( dbmParserContext     * aCtx,
                                         dbmParseType           aParseType,
                                         dbmParseValue        * aName,
                                         dbmList              * aSetList,
                                         dbmParseExpr         * aWhereExpr );

dbmParseDeleteStmt  * dbmMakeDeleteStmt( dbmParserContext     * aCtx,
                                         dbmParseValue        * aName,
                                         dbmParseExpr         * aWhereExpr );

dbmParseSelectStmt  * dbmMakeSelectStmt( dbmParserContext     * aCtx,
                                         dbmList              * aTargetList,
                                         dbmList              * aTableList,
                                         dbmParseExpr         * aWhereExpr,
                                         dbmList              * aGroupByList,
                                         dbmList              * aOrderByList,
                                         dbmParseValue        * aForUpdate,
                                         dbmParseLimit        * aLimit );

dbmParseEnqueueStmt  * dbmMakeEnqueueStmt( dbmParserContext     * aCtx,
                                           dbmParseValue        * aName,
                                           dbmList              * aColumnList,
                                           dbmList              * aValueList );

dbmParseDequeueStmt  * dbmMakeDequeueStmt( dbmParserContext     * aCtx,
                                           dbmParseValue        * aName,
                                           dbmParseExpr         * aWhereExpr,
                                           dbmParseValue        * aTimeOut );

dbmParseAlterReplSyncStmt  * dbmMakeAlterReplSyncStmt( dbmParserContext     * aCtx,
                                                       dbmReplActDef          aReplAct,
                                                       dbmList              * aTableList );

dbmParseAlterReplModStmt  * dbmMakeAlterReplModStmt( dbmParserContext     * aCtx,
                                                     dbmBool                aIsDrop,
                                                     dbmList              * aTableList );

dbmParseCreateSequenceStmt  * dbmMakeCreateSequenceStmt( dbmParserContext     * aCtx,
                                                         dbmParseValue        * aSeqName,
                                                         dbmParseValue        * aStartVal,
                                                         dbmParseValue        * aIncrementVal,
                                                         dbmParseValue        * aMaxVal,
                                                         dbmParseValue        * aMinVal,
                                                         dbmParseValue        * aIsCycle );

dbmParseAlterSequenceStmt  * dbmMakeAlterSequenceStmt( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aSeqName,
                                                       dbmParseValue        * aCurrVal );


dbmParseCreateReplStmt  * dbmMakeCreateReplStmt( dbmParserContext     * aCtx,
                                                 dbmList              * aTableList );

dbmParseDropReplStmt  * dbmMakeDropReplStmt( dbmParserContext     * aCtx );

dbmParseAlterSystemInstanceStmt  * dbmMakeAlterSystemInstanceStmt( dbmParserContext     * aCtx,
                                                                   dbmBool                aIsActive );

dbmParseAlterSystemResetCkptFileStmt  * dbmMakeAlterSystemResetCkptFileStmt( dbmParserContext     * aCtx,
                                                                             dbmParseValue        * aInstName,
                                                                             dbmParseValue        * aFileNo );

dbmParseCreateCaptureStmt  * dbmMakeCreateCaptureStmt( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aReplName,
                                                       dbmList              * aTableList );

dbmParseDropCaptureStmt  * dbmMakeDropCaptureStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aReplName );

dbmParseRebuildIndexStmt  * dbmMakeAlterRebuildIndexStmt( dbmParserContext     * aCtx,
                                                          dbmParseValue        * aTableName,
                                                          dbmParseValue        * aIndexName );

dbmParseDeclareItem  * dbmMakeProcDeclareItem( dbmParserContext     * aCtx,
                                               dbmProcDeclareType     aDeclareType,
                                               void                 * aItem );

dbmParseDeclareVar  * dbmMakeProcDeclareVar( dbmParserContext         * aCtx,
                                             dbmParseValue            * aName,
                                             dbmParseProcDataTypeDef  * aDataTypeDef,  
                                             dbmParseExpr             * aInitValue );

dbmParseDeclareCursor  * dbmMakeProcDeclareCursor( dbmParserContext     * aCtx,
                                                   dbmProcDeclareType     aDeclareType,
                                                   dbmParseValue        * aName,
                                                   dbmList              * aParamList,
                                                   dbmParseSelectStmt   * aSelectStmt );

dbmParseDeclareException  * dbmMakeProcDeclareException( dbmParserContext     * aCtx,
                                                         dbmProcDeclareType     aDeclareType,
                                                         dbmParseValue        * aName,
                                                         dbmParseValue        * aErrorCode );

dbmParseCreateProcStmt  * dbmMakeCreateProcStmt( dbmParserContext       * aCtx,
                                                 dbmParseValue          * aName,
                                                 dbmList                * aParamList,
                                                 dbmParseProcBlockStmt  * aBlockStmt,
                                                 dbmBool                  aIsReplace );

dbmParseExecProcStmt  * dbmMakeExecProcStmt( dbmParserContext     * aCtx,
                                             dbmParseValue        * aProcName,
                                             dbmList              * aParamList );

dbmParseProcBlockStmt  * dbmMakeProcBlockStmt( dbmParserContext     * aCtx,
                                               dbmList              * aDeclareList,
                                               dbmList              * aStmtList,
                                               dbmList              * aExceptionList );

dbmParseProcStmt  * dbmMakeProcStmt( dbmParserContext     * aCtx,
                                     dbmProcStmtType        aStmtType,
                                     dbmParseValue        * aLabelName,
                                     void                 * aStmt );

dbmParseProcAssignStmt  * dbmMakeProcAssignStmt( dbmParserContext     * aCtx,
                                                 dbmList              * aNameList,
                                                 dbmParseExpr         * aValueExpr );

dbmParseProcPutLineStmt  * dbmMakeProcPutLineStmt( dbmParserContext     * aCtx,
                                                   dbmParseExpr         * aValueExpr );

dbmParseSelectIntoStmt  * dbmMakeSelectIntoStmt( dbmParserContext     * aCtx,
                                                 dbmList              * aTargetList,
                                                 dbmList              * aIntoList,
                                                 dbmList              * aTableList,
                                                 dbmParseExpr         * aWhereExpr,
                                                 dbmList              * aGroupByList,
                                                 dbmParseValue        * aForUpdate );

dbmParseProcExceptionItem  * dbmMakeProcExceptionItem( dbmParserContext     * aCtx,
                                                       dbmParseValue        * aName,
                                                       dbmList              * aStmtList );

dbmParseProcIfItem  * dbmMakeProcIfItem( dbmParserContext     * aCtx,
                                         dbmParseExpr         * aCondExpr,
                                         dbmList              * aStmtList );

dbmParseProcIfStmt  * dbmMakeProcIfStmt( dbmParserContext     * aCtx,
                                         dbmParseProcIfItem   * aFirstIf,
                                         dbmList              * aElseList,
                                         dbmParseProcIfItem   * aLast );

dbmParseProcExitStmt  * dbmMakeProcExitStmt( dbmParserContext     * aCtx,
                                             dbmParseExpr         * aCondExpr );

dbmParseProcContinueStmt  * dbmMakeProcContinueStmt( dbmParserContext     * aCtx,
                                                     dbmParseExpr         * aCondExpr );

dbmParseProcLoopStmt  * dbmMakeProcLoopStmt( dbmParserContext     * aCtx,
                                             dbmList              * aStmtList );

dbmParseProcSimpleCaseStmt  * dbmMakeProcSimpleCaseStmt( dbmParserContext     * aCtx,
                                                         dbmParseExpr         * aValueExpr,
                                                         dbmList              * aCondList,
                                                         dbmParseProcIfItem   * aElse );

dbmParseProcSearchedCaseStmt  * dbmMakeProcSearchedCaseStmt( dbmParserContext     * aCtx,
                                                             dbmList              * aCondList,
                                                             dbmParseProcIfItem   * aElse );

dbmParseProcForLoopStmt  * dbmMakeProcForLoopStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aNameList,
                                                   dbmBool                aIsReverse,
                                                   dbmParseExpr         * aFirstExpr,
                                                   dbmParseExpr         * aLastExpr,
                                                   dbmList              * aStmtList );

dbmParseProcWhileLoopStmt  * dbmMakeProcWhileLoopStmt( dbmParserContext     * aCtx,
                                                       dbmParseExpr         * aCondExpr,
                                                       dbmList              * aStmtList );

dbmParseProcGotoStmt  * dbmMakeProcGotoStmt( dbmParserContext     * aCtx,
                                             dbmParseValue        * aName );


dbmParseProcOpenCursorStmt  * dbmMakeProcOpenCursorStmt( dbmParserContext     * aCtx,
                                                         dbmParseValue        * aName,
                                                         dbmList              * aParamList );

dbmParseProcFetchCursorStmt  * dbmMakeProcFetchCursorStmt( dbmParserContext     * aCtx,
                                                           dbmParseValue        * aName,
                                                           dbmList              * aIntoList );

dbmParseProcCloseCursorStmt  * dbmMakeProcCloseCursorStmt( dbmParserContext     * aCtx,
                                                           dbmParseValue        * aName );
 
dbmParseProcRaiseStmt  * dbmMakeProcRaiseStmt( dbmParserContext     * aCtx,
                                               dbmParseValue        * aName,
                                               dbmParseValue        * aErrorCode,
                                               dbmParseValue        * aErrorMsg );

dbmParseProcCallProcStmt  * dbmMakeProcCallProcStmt( dbmParserContext     * aCtx,
                                                     dbmParseValue        * aName,
                                                     dbmList              * aArgList );

dbmParseDropProcStmt  * dbmMakeDropProcedureStmt( dbmParserContext     * aCtx,
                                                  dbmParseValue        * aProcName );

dbmParseParamInOut  * dbmMakeParamInOut( dbmParserContext     * aCtx,
                                         dbmParamInOutType      aInOut );

dbmParseProcDataTypeDef  * dbmMakeProcDataTypeDef( dbmParserContext     * aCtx,
                                                   dbmProcDeclareType     aDeclareType,
                                                   void                 * aDeclareDef );

dbmParseAlterTableRenameColumnStmt  * dbmMakeAlterTableRenameColumnStmt( dbmParserContext     * aCtx,
                                                                         dbmParseValue        * aTableName,
                                                                         dbmParseValue        * aOrgColumn,
                                                                         dbmParseValue        * aNewColumn );

dbmParseOrderByList  * dbmMakeOrderByList( dbmParserContext     * aCtx,
                                           dbmList              * aList );


dbmParseCreateLibraryStmt  * dbmMakeCreateLibraryStmt( dbmParserContext     * aCtx,
                                                       dbmBool                aIsSyncLib,
                                                       dbmParseValue        * aObjectName,
                                                       dbmParseValue        * aDllName,
                                                       dbmParseLibraryItem  * aInitFunc,
                                                       dbmParseLibraryItem  * aFiniFunc,
                                                       dbmList              * aFuncList );

dbmParseDropLibraryStmt  * dbmMakeDropLibraryStmt( dbmParserContext     * aCtx,
                                                   dbmParseValue        * aSvcName );

dbmParseUserLibraryFunction  * dbmMakeParseUserLibFunction( dbmParserContext     * aCtx,
                                                            dbmList              * aFuncName,
                                                            dbmList              * aArgs );

dbmParseCreateGsbNodeStmt * dbmMakeCreateGsbNodeStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName,
                                dbmParseValue        * aHostPort,
                                dbmParseValue        * aClientMax,
                                dbmParseValue        * aProcessMax );

dbmParseDropGsbNodeStmt * dbmMakeDropGsbNodeStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName );


dbmParseCreateGsbMonitorStmt * dbmMakeCreateGsbMonitorStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName,
                                dbmParseValue        * aNodeName,
                                dbmParseValue        * aInfluxIp,
                                dbmParseValue        * aInfluxPort,
                                dbmParseValue        * aInfluxDb );

dbmParseDropGsbMonitorStmt * dbmMakeDropGsbMonitorStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName );


dbmParseCreateGsbSvrGrpStmt * dbmMakeCreateGsbSvrGrpStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName,
                                dbmParseValue        * aNodeName );

dbmParseDropGsbSvrGrpStmt * dbmMakeDropGsbSvrGrpStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName );

dbmParseCreateGsbSvrStmt * dbmMakeCreateGsbSvrStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName,
                                dbmParseValue        * aSvrGrpName,
                                dbmParseValue        * aProcessMin,
                                dbmParseValue        * aProcessCnt,
                                dbmParseValue        * aProcessMax,
                                dbmParseValue        * aQSize );

dbmParseDropGsbSvrStmt * dbmMakeDropGsbSvrStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName );


dbmParseCreateGsbSvcStmt * dbmMakeCreateGsbSvcStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName,
                                dbmParseValue        * aSvrName,
                                dbmParseValue        * aLibrary,
                                dbmParseValue        * aFunction );

dbmParseDropGsbSvcStmt * dbmMakeDropGsbSvcStmt( 
                                dbmParserContext     * aCtx,
                                dbmParseValue        * aName );

dbmParseAlterGsbProcCntStmt * dbmMakeAlterGsbProcCntStmt( 
                                 dbmParserContext     * aCtx,
                                 dbmParseValue        * aSvrName,
                                 dbmParseValue        * aProcessCnt );

dbmParseDecodeItem * dbmMakeParseDecodeItem( dbmParserContext     * aCtx,
                                             dbmParseExpr         * aCondExpr,
                                             dbmParseExpr         * aValueExpr );

dbmParseDCLStmt  * dbmMakeCreateDCLStmt( dbmParserContext     * aCtx,
                                         dbmBool                aIsCommit );

dbmParseAlterResetPerfStmt  * dbmMakeAlterResetPerfStmt( dbmParserContext     * aCtx );

dbmParseValue  * dbmMakeIdentifierDoubleQuote( dbmParserContext     * aCtx,
                                               dbmChar              * aValue );

dbmParseAgingStmt  * dbmMakeAlterAgingStmt( dbmParserContext     * aCtx,
                                            dbmList              * aTableList );

dbmParseLoadStmt  * dbmMakeLoadStmt( dbmParserContext     * aCtx,
                                     dbmParseValue        * aTargetTable,
                                     dbmList              * aTargetColList,
                                     dbmParseValue        * aQuery,
                                     dbmParseValue        * aSourceDSN,
                                     dbmParseValue        * aSourceUID,
                                     dbmParseValue        * aSourcePWD,
                                     dbmParseValue        * aExpiredTime );

dbmParseSyncStmt  * dbmMakeSyncStmt( dbmParserContext     * aCtx,
                                     dbmParseValue        * aTargetTable,
                                     dbmList              * aColumnList,
                                     dbmParseValue        * SourceQuery,
                                     dbmParseValue        * aTargetDSN,
                                     dbmParseValue        * aTargetUID,
                                     dbmParseValue        * aTargetPWD );

dbmParseAlterTableCompactStmt  * dbmMakeAlterTableCompactStmt( dbmParserContext     * aCtx,
                                                               dbmParseValue        * aTableName );

dbmParseAlterTableAddColumnStmt  * dbmMakeAlterTableAddColumnStmt( dbmParserContext     * aCtx,
                                                                   dbmParseValue        * aTableName,
                                                                   dbmParseColumnDef    * aColumnDef,
                                                                   dbmParseExpr         * aDefaultVal );

dbmParseAlterTableDropColumnStmt  * dbmMakeAlterTableDropColumnStmt( dbmParserContext     * aCtx,
                                                                     dbmParseValue        * aTableName,
                                                                     dbmParseValue        * aColumnName );

dbmParseLimit  * dbmMakeParseLimit( dbmParserContext     * aCtx,
                                    dbmParseValue        * aStart,
                                    dbmParseValue        * aCount );

dbmParseSessionTermStmt  * dbmMakeAlterTermSessionStmt( dbmParserContext     * aCtx,
                                                        dbmParseValue        * aSessionId );

dbmParseOraInsertStmt  * dbmMakeOraInsertStmt( dbmParserContext     * aCtx,
                                               dbmList              * aName,
                                               dbmList              * aColumnList,
                                               dbmList              * aValueList );

dbmParseOraUpdateStmt  * dbmMakeOraUpdateStmt( dbmParserContext     * aCtx,
                                               dbmParseType           aParseType,
                                               dbmList              * aName,
                                               dbmList              * aSetList,
                                               dbmParseExpr         * aWhereExpr );

dbmParseOraDeleteStmt  * dbmMakeOraDeleteStmt( dbmParserContext     * aCtx,
                                               dbmList              * aName,
                                               dbmParseExpr         * aWhereExpr );

#endif


#include <dbmUtils.h>
#include <sys/syscall.h>
//#include <dbmDicTable.h>

#ifdef _DBM_RTF
static dbmInt32    gRTFCount = 0;
#endif

#ifdef DBM_DEBUG
dbmTransHeader   * gTransHdr = NULL;
#endif



#define DBM_SET_SYSTEM_ERROR( aErrorNo, aErrorStack ) dbeSetSystemError( (aErrorNo), (dbmChar *)(__func__), (aErrorStack) )
void dbeSetSystemError( dbmInt32        aErrorNo,
                        dbmChar       * aFuncName,
                        dbmErrorStack * aErrorStack );


//extern dbmDicTableDef     gDbmDicTable[];
extern dbmChar          * __progname;

void dbmTrimAll( dbmChar    * aSrc )
{
    dbmTrimRight( aSrc );
    dbmTrimLeft( aSrc );
}



void dbmTrimRight( dbmChar * aSrc )
{
    dbmInt32 sLen;
    dbmInt32 i;


    DBM_TRY_THROW( aSrc != NULL, RAMP_FINISH );
    
    sLen = dbmStrlen( aSrc );

    for( i = (sLen - 1); i >= 0 ; i-- )
    {
        if( aSrc[i] == ' ') 
        {
           aSrc[i] = 0x00;
        }
        else
        {
           break;
        }
    }


    DBM_RAMP( RAMP_FINISH )

    return;
}



void dbmTrimLeft( dbmChar    * aSrc )
{
    dbmInt32 sLen;
    dbmInt32 i = 0;


    DBM_TRY_THROW( aSrc != NULL, RAMP_FINISH );
    
    i = 0;
    sLen = dbmStrlen( aSrc );

    while( i < sLen )
    {
        if( aSrc[i] == ' ' || aSrc[i] == '\n' ) 
        {
           dbmMemmove( aSrc + i, aSrc + i + 1, sLen );
           aSrc[ sLen - 1 ] = 0x00;
           sLen = dbmStrlen( aSrc );
           i = 0;
           continue;
        }
        else
        {
           break;
        }

        i ++;
    }


    DBM_RAMP( RAMP_FINISH )

    return;
}




void dbmUpperString( dbmChar * aSrc )
{
    dbmInt32 sLen;
    dbmInt32 i;


    DBM_TRY_THROW( aSrc != NULL, RAMP_FINISH );
    
    sLen = dbmStrlen( aSrc );

    for( i = 0; i < sLen ; i++ )
    {
        aSrc[i] = dbmToupper( aSrc[i] );
    }


    DBM_RAMP( RAMP_FINISH )

    return;
}




dbmInt32 dbmGetPID()
{
    return (dbmInt32)getpid();
}



dbmInt32 dbmGetTID()
{
    return (dbmInt32)syscall (SYS_gettid);
}


/**
 * test계속 돌려서 아래 LOG가 안나오면 signal관련 부분은 삭제해도 될듯.
 */
dbmInt32 dbmKill( dbmInt32          aTransId,
                  dbmInt32          aTID,
                  dbmTransHeader  * aTransHdr,
                  dbmErrorStack   * aErrorStack )


{
#if 1
    dbmInt32      sRet;

    // AllocTrans 시점에 중복TID가 접속못하게 방어한다.
    sRet = syscall ( SYS_tkill, aTID, 0 );

    if( sRet != 0 && errno == ESRCH )
    {
        return DBM_FAILURE;
    }
    else
    {
        return DBM_SUCCESS;
    }
#else
    dbmUndoSemaphore         sUndoSema;
    dbmBool                  sIsBind;

    if( aTransId >= 0 )
    {
        sUndoSema.mSemId = aTransHdr->mSemId;
        sUndoSema.mSemNum = aTransId;

        if( dbmGetUndoSemaphoreState( &sUndoSema,
                                      &sIsBind,
                                      aErrorStack ) == DBM_SUCCESS )
        {
            if( sIsBind == DBM_FALSE )
            {
                DBM_TRACE( "aTrans(%d) TID(%d) already killed\n", aTransId, aTID );
            }

            return ( sIsBind == DBM_FALSE ) ? DBM_FAILURE : DBM_SUCCESS;
        }
        else
        {
            DBM_ASSERT( 0 );
            return DBM_SUCCESS;
        }
    }
    else
    {
        // @todo 전체 다 수정하기 전까지
        // 지원하지 못한다. 일단 살은거라고 판단하고 대기시키자.
        return DBM_SUCCESS;
    }
#endif
}



/**
 * aCheckTime : TRUE이면 /proc/pid의 process 시작 시간까지 비교한다. FALSE이면 가끔 시간을 비교한다.
 * DBM을 사용하는 process가 비정상 종료했는데 우연히 다른 app가 동일한 pid로 실행되었을수 있다.
 * 이 경우 aCheckTime이 TRUE로 설정되면 /proc/pid의 process 시작 시간을 비교하여 검증 가능하다.
 * 이 방법은 성능이 느려짐으로 성능과 관련 없는 부분에서만 사용해야 한다.
 * index복구 등에서는 dbmIsAliveProcess를 두번 호출하는 경우는 aCheckTime를 동일하게 설정해야 하는데
 * 이 경우 DBM_TRUE를 사용한다.
 * 성능이 중요한 부분은 DBM_FALSE를 사용해야 하고 두번 호출하면 감지가 안될수 있다.
 */
dbmStatus dbmIsAliveProcess( dbmInt32          aTransId,
                             dbmInt32          aTID, 
                             dbmTransHeader  * aTransHdr,
                             dbmBool         * aIsAlive,
                             dbmBool           aCheckTime,
                             dbmErrorStack   * aErrorStack )
{
    dbmProc     sProc;
    dbmTrans  * sTrans = NULL;
    dbmTime     sProcBeginTime = 0;
    dbmInt32    i;

    if( aTID == DBM_NOT_USED )
    {
        *aIsAlive = DBM_TRUE;
        DBM_THROW( RAMP_SUCCESS );
    }

    sProc.mProcID = aTID;

    *aIsAlive = dbmIsActiveProc( &sProc );

#if 0
    // test용도 : 죽었는데 살았다고 판단하게 함
    if( *aIsAlive == DBM_FALSE )
    {
        *aIsAlive = DBM_TRUE;
//        DBM_TRACE("TID(%d) killed : test용도 : 죽었는데 살았다고 판단하게 함 \n", aTID);
    }
#endif

    if( *aIsAlive == DBM_TRUE )
    {
        /*
         * /proc/pid 로 bigin time을 비교해서 진짜 pid 중복 오류를 막는다.
         */

        if( aTransId == DBM_NOT_USED )
        {
            for( i = 0; i < DBM_MAX_TRANS; i ++ )
            {
                sTrans = dbmGetTrans( aTransHdr, i );

                if( sTrans->mPID == aTID )
                {
                    break;
                }
            }

            if( i == DBM_MAX_TRANS )
            {
                DBM_THROW( RAMP_SUCCESS );
            }
        }
        else
        {
            sTrans = dbmGetTrans( aTransHdr, aTransId );
        }

        /**
         * aCheckTime이 FALSE라도 가끔은 TRUE로 바꿔준다.
         */
        if( aCheckTime == DBM_FALSE )
        {
            if( sTrans->mCheckAliveCnt > 1000000 )
            {
                aCheckTime = DBM_TRUE;
                sTrans->mCheckAliveCnt = 0;
            }
            sTrans->mCheckAliveCnt++;
        }

        DBM_TRY_THROW( aCheckTime == DBM_TRUE, RAMP_SUCCESS );

        if( dbmGetProcName( &sProc, NULL, 0, &sProcBeginTime, aErrorStack ) == DBM_SUCCESS )
        {
            /*
             * process가 살아 있는데 TxBeginTime보다 나중이면 다른process임으로 죽은걸로 한다.
             * dbmGetProcName에서 가져오는 시간에서 최대 0.01초 오차가 있을수 있다.
             * (bootup시간(/proc/uptime) 이 소수점 두자리만 나옴
             * 그래서 sProcBeginTime-10000 으로 비교함.
             */

            if( sTrans->mBeginTime < (sProcBeginTime - 900000L)  )
            {
                DBM_TRACE("TID(%d) killed : Tx(%ld), Proc(%ld)\n",
                          aTID, sTrans->mBeginTime, sProcBeginTime );

                *aIsAlive = DBM_FALSE;
            }
            else
            {
                *aIsAlive = DBM_TRUE;
            }
        }
        else
        {
            dbmPopError( aErrorStack );

            /*
             * process 정보가 없음으로 죽은거임
             */
            *aIsAlive = DBM_FALSE;
            DBM_TRACE("TID(%d) killed : signal(0) success but dbmGetProcName fail\n", aTID);
        }
    }

    DBM_RAMP( RAMP_SUCCESS );

    return DBM_SUCCESS;
}




void dbmNoSleep( dbmInt32 aSleepTime )
{
#if 0
    struct timespec sStart;
    struct timespec sEnd;
    dbmInt64 sDiff = 0;

    clock_gettime( CLOCK_REALTIME, & sStart );
  
    
    while( 1 )
    {
        clock_gettime( CLOCK_REALTIME, & sEnd );

        sDiff = (sEnd.tv_sec + sEnd.tv_nsec / 1000000000.0) -
                (sStart.tv_sec + sStart.tv_nsec / 1000000000.0) ;

        if( sDiff > aSleepTime )
        {
            return;
        }
        cpu_relax();
    }
    clock_gettime( CLOCK_REALTIME, & sEnd );
#else
    if( aSleepTime > 0 )
    {
        dbmSleep( aSleepTime );
    }
#endif
}


void dbmWaitStatus( volatile dbmThreadStat   * aVal,
                    dbmThreadStat              aInitVal,
                    dbmThreadStat              aStat )
{
    if( aInitVal != DBM_STAT_INVALID && (*aVal) != aStat )
    {
        dbmSetStatus( aVal, aInitVal );
    }

    while( 1 )
    {
        if( (*aVal) == aStat ||
            (*aVal) == DBM_STAT_DIE ||
            (*aVal) == DBM_STAT_ERROR )
        {
            break;
        }
        else 
        {
            usleep(1);
        }
    }
}



void dbmSetStatus( volatile dbmThreadStat   * aVal,
                   dbmThreadStat              aStat )
{
    dbmAtomicSet32( aVal, aStat ); 
}




dbmInt64 dbmGetCpuCount()
{
    return dbmGetCpuTick();
}



dbmStatus dbmDaemonize( dbmBool         * aIsChild,
                        dbmErrorStack   * aErrorStack )
{
    dbmProc      sProc;

    DBM_TRY( dbmForkProc( &sProc, aIsChild, aErrorStack ) == DBM_SUCCESS );

    return DBM_SUCCESS;

    DBM_FINISH

    return DBM_FAILURE;
}


#ifdef _DBM_RTF
dbmInt32 DBM_RTF_( const dbmChar * aName )
{
    dbmChar         sTestName[256];
    dbmChar         sEnvValue[256];
    dbmInt64        sTestCount = 0;
    dbmInt64        sTestSleep = 0;
    dbmInt64        sTestSleepMs = 0;
    dbmInt64        sTestRtn = 0;
    dbmInt64        sTestNoPrt = 0;
    dbmBool         sIsFound;
    dbmErrorStack   sErrorStack;

    dbmClearErrorStack( &sErrorStack );

    // Get RTF name
    if( dbmGetEnv( sTestName, sizeof(sTestName), "DBM_RTF", &sIsFound, &sErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT( 0 );
    }

    DBM_TRY_THROW( sIsFound == DBM_TRUE, RAMP_FINISH );
    DBM_TRY_THROW( dbmStrcmp( sTestName, aName ) == 0, RAMP_FINISH );


    // Get RTF Loop Count
    if( dbmGetEnv( sEnvValue, sizeof(sEnvValue), "DBM_RTF_COUNT", &sIsFound, &sErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT( 0 );
    }

    if( sIsFound == DBM_TRUE )
    {
        sTestCount = dbmAtol( sEnvValue );
    }
    else
    {
        sTestCount = 1;
    }


    // Get RTF Sleep Time
    if( dbmGetEnv( sEnvValue, sizeof(sEnvValue), "DBM_RTF_SLEEP", &sIsFound, &sErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT( 0 );
    }

    if( sIsFound == DBM_TRUE )
    {
        sTestSleep = dbmAtol( sEnvValue );
    }
    else
    {
        sTestSleep = 0;
    }

    // Get RTF SleepMs Time
    if( dbmGetEnv( sEnvValue, sizeof(sEnvValue), "DBM_RTF_SLEEP_MS", &sIsFound, &sErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT( 0 );
    }

    if( sIsFound == DBM_TRUE )
    {
        sTestSleepMs = dbmAtol( sEnvValue );
    }
    else
    {
        sTestSleepMs = 0;
    }


    // Get RTF rtn
    if( dbmGetEnv( sEnvValue, sizeof(sEnvValue), "DBM_RTF_RTN", &sIsFound, &sErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT( 0 );
    }

    if( sIsFound == DBM_TRUE )
    {
        sTestRtn = dbmAtol( sEnvValue );
    }
    else
    {
        sTestRtn = 0;
    }


    // Get RTF No print
    if( dbmGetEnv( sEnvValue, sizeof(sEnvValue), "DBM_RTF_NO_PRT", &sIsFound, &sErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT( 0 );
    }

    if( sIsFound == DBM_TRUE )
    {
        sTestNoPrt = dbmAtol( sEnvValue );
    }
    else
    {
        sTestNoPrt = 0;
    }


    gRTFCount ++;   
    if( gRTFCount == sTestCount || sTestCount == -1 )
    {
        if( sTestNoPrt == 0 )
        {
            DBM_TRACE( "RTF (%s) raised\n", sTestName );
            dbmPrintf( "RTF(%s), COUNT(%ld), SLEEP(%ld)\n", sTestName, sTestCount, sTestSleep );
            fflush( stdout );
        }

        if( sTestSleep == 0 && sTestSleepMs == 0 && sTestRtn == 0 )
        {
            dbmExit( 0 );
        }

        dbmSleep( DBM_SET_SEC_TIME(sTestSleep) );
        dbmSleep( DBM_SET_MSEC_TIME(sTestSleepMs) );
    }

    DBM_RAMP( RAMP_FINISH )

    return sTestRtn;
}


void dbmSetRtfCount( dbmInt32   sCnt )
{
    gRTFCount = sCnt;
}


#endif

dbmInt32 dbmMakeErrorMessage( dbmChar             * aBuffer,
                              dbmSize               aBufferSize,
                              dbmErrorData        * aErrorData,
                              dbmPrintErrorLevel    aErrorLevel )
{
    dbmInt32 sLength;

    if( aErrorLevel == DBM_PRINT_ERROR_LEVEL_DETAIL_MESSAGE )
    {
        if( aErrorData->mDetailErrorMessage[0] == 0x00 )
        {
            sLength = dbmSnprintf( aBuffer,
                                   aBufferSize,
                                   "ERR-%d] %s",
                                   aErrorData->mErrorCode,
                                   aErrorData->mErrorMessage );
        }
        else
        {
            sLength = dbmSnprintf( aBuffer,
                                   aBufferSize,
                                   "ERR-%d] %s: %s",
                                   aErrorData->mErrorCode,
                                   aErrorData->mErrorMessage,
                                   aErrorData->mDetailErrorMessage );
        }
    }
    else if( aErrorLevel == DBM_PRINT_ERROR_LEVEL_MESSAGE )
    {
        sLength = dbmSnprintf( aBuffer,
                               aBufferSize,
                               "ERR-%d] %s",
                               aErrorData->mErrorCode,
                               aErrorData->mErrorMessage );
    }
    else
    {
        sLength = dbmSnprintf( aBuffer,
                               aBufferSize,
                               "ERR-%d]",
                               aErrorData->mErrorCode );
    }

    return sLength;
}

void dbmPrintErrorStack( dbmErrorStack * sErrorStack )
{
    dbmInt32 i;
    dbmChar  sBuffer[1024];

    for( i = sErrorStack->mTop; i >= 0; i-- )
    {
        dbmMakeErrorMessage( sBuffer,
                             DBM_SIZEOF(sBuffer),
                             &sErrorStack->mErrorData[i],
                             DBM_PRINT_ERROR_LEVEL_DETAIL_MESSAGE );

        dbmPrintf("%s\n", sBuffer );
    }
}

dbmBool dbmGetEnvBool( dbmChar          * aEnvKey,
                       dbmErrorStack    * aErrorStack )
{
    dbmChar     sEnvValue[256];
    dbmBool     sIsFound;

    if( dbmGetEnv( sEnvValue,
                   DBM_SIZEOF(sEnvValue),
                   aEnvKey,
                   &sIsFound,
                   aErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT(0);
        dbmPopError( aErrorStack );
        DBM_TRY( 0 );
    }

    DBM_TRY( sIsFound == DBM_TRUE );

    DBM_TRY( dbmStrcmp( sEnvValue, "1" ) == 0 ||
             dbmStrcasecmp( sEnvValue, "on" ) == 0 ||
             dbmStrcasecmp( sEnvValue, "true" ) == 0 );

    return DBM_TRUE;

    DBM_FINISH

    return DBM_FALSE;
}


dbmStatus dbmGetEnvString( dbmChar          * aEnvKey,
                           dbmChar          * aEnvValue,
                           dbmSize            aEnvValueSize,
                           dbmErrorStack    * aErrorStack )
{
    dbmBool     sIsFound;

    if( dbmGetEnv( aEnvValue,
                   aEnvValueSize,
                   aEnvKey,
                   &sIsFound,
                   aErrorStack ) != DBM_SUCCESS )
    {
        DBM_ASSERT(0);

        dbmPopError( aErrorStack );
        DBM_TRY( 0 );
    }

    DBM_TRY( sIsFound == DBM_TRUE );


    return DBM_SUCCESS;

    DBM_FINISH

    return DBM_FAILURE;
}

dbmStatus dbmGetDbfFileName( dbmChar            * aFileName,
                             dbmSize              aFileNameSize,
                             dbmChar            * aDataPath,
                             const dbmChar      * aName,
                             dbmErrorStack      * aErrorStack )
{
    dbmChar              sEnvValue[PATH_MAX];
    dbmBool              sIsFound;

    /**
     * 경로를 통해 파일명을 정한다.
     */

    if( aDataPath != NULL )
    {
        dbmSnprintf( aFileName,
                     aFileNameSize,
                     "%s/%s.dbf",
                     aDataPath,
                     aName );
    }
    else
    {
        if( dbmGetEnv( sEnvValue,
                       sizeof(sEnvValue),
                       "DBM_DISK_DATA_FILE_DIR",
                       &sIsFound,
                       aErrorStack ) != DBM_SUCCESS )
        {
            DBM_ASSERT( 0 );
        }

        if( sIsFound == DBM_TRUE )
        {
            dbmSnprintf( aFileName,
                         aFileNameSize,
                         "%s/%s.dbf",
                         sEnvValue,
                         aName );
        }
        else
        {
            if( dbmGetEnv( sEnvValue,
                           sizeof(sEnvValue),
                           "DBM_HOME",
                           &sIsFound,
                           aErrorStack ) != DBM_SUCCESS )
            {
                DBM_ASSERT( 0 );
            }

            DBM_ASSERT( sIsFound == DBM_TRUE );

            dbmSnprintf( aFileName,
                         aFileNameSize,
                         "%s/dbf/%s.dbf",
                         sEnvValue,
                         aName );
        }
    }

    return DBM_SUCCESS;
}





dbmStatus dbmParseTime( dbmChar         * aTimeStr,
                        dbmInt32          aMicroPos,
                        dbmChar         * aFormat,
                        dbmTime         * aTime,
                        dbmErrorStack   * aErrorStack )
{
    struct tm           sTm;

    dbmMemset( &sTm, 0x00, sizeof(sTm) );

    DBM_TRY_THROW( strptime( aTimeStr, aFormat, &sTm ) != NULL,
                   RAMP_ERR_STR_TO_DATE_FAIL );

    *aTime = mktime( &sTm ) * 1000000;
    if( aMicroPos > 0 )
    {
        *aTime += dbmAtol( aTimeStr + aMicroPos ); // Fix시켰는데 Date Format을 지원할려면 변경해야 함
    }

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_STR_TO_DATE_FAIL )
    {
        //dbmPrintf( "ERR] fail to convert string to date-format ( %s, %s )\n", aTimeStr, aFormat );
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );

    }

    DBM_FINISH

    return DBM_FAILURE;
}


/**
 * 인터넷 뒤져보니 pread, pwrite는 lseek와 read,write로 구현된걸로 되어 있음.
 * 시간 되면 pread, pwrite와 성능 비교해 보자
 */
dbmStatus dbmPRead( dbmFile       * aFile,
                    void          * aBuffer,
                    dbmSize         aBytes,
                    dbmOffset       aOffset,
                    dbmErrorStack * aErrorStack )
{

    dbmSize sResult;
//    dbmOffset sOldOffset = 0;

//    DBM_TRY( dbmSeekFile( aFile, DBM_FSEEK_CUR, &sOldOffset, aErrorStack ) == DBM_SUCCESS );

    DBM_TRY( dbmSeekFile( aFile, SEEK_SET, &aOffset, aErrorStack ) == DBM_SUCCESS );

    DBM_TRY( dbmReadFile( aFile, aBuffer, aBytes, &sResult, aErrorStack ) == DBM_SUCCESS );

    DBM_TRY_THROW( aBytes == sResult, RAMP_ERR_FILE_READ );

    // pread만 사용하면 처음과 마지막 seek는 필요 없을것 같기도 함.
//    DBM_TRY( dbmSeekFile( aFile, SEEK_SET, &sOldOffset, aErrorStack ) == DBM_SUCCESS );

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_FILE_READ )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FILE_READ_FAIL,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    return DBM_FAILURE;
}



dbmStatus dbmPWrite( dbmFile       * aFile,
                     void          * aBuffer,
                     dbmSize         aBytes,
                     dbmOffset       aOffset,
                     dbmErrorStack * aErrorStack )
{

    dbmSize sResult;
    dbmOffset sOldOffset = 0;

    DBM_TRY( dbmSeekFile( aFile, DBM_FSEEK_CUR, &sOldOffset, aErrorStack ) == DBM_SUCCESS );

    DBM_TRY( dbmSeekFile( aFile, SEEK_SET, &aOffset, aErrorStack ) == DBM_SUCCESS );

    DBM_TRY( dbmWriteFile( aFile, aBuffer, aBytes, &sResult, aErrorStack ) == DBM_SUCCESS );

    DBM_TRY_THROW( aBytes == sResult, RAMP_ERR_FILE_WRITE );

    // pwrite만 사용하면 처음과 마지막 seek는 필요 없을것 같기도 함.
    DBM_TRY( dbmSeekFile( aFile, SEEK_SET, &sOldOffset, aErrorStack ) == DBM_SUCCESS );

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_FILE_WRITE )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_FILE_WRITE_FAIL,
                      NULL,
                      aErrorStack );
    }

    DBM_FINISH

    return DBM_FAILURE;
}

dbmStatus dbmPrintf( const dbmChar *aFormat,
                     ...)
{
    dbmChar     sBuff[4096];
    dbmChar   * sLargeBuff = NULL;
    dbmSize     sBuffSize = 4096;
    dbmSize     sReturn;
    va_list     sVarArgList;

    va_start(sVarArgList, aFormat);
    sReturn = dbmVsnprintf(sBuff, DBM_SIZEOF(sBuff), aFormat, sVarArgList);
    va_end(sVarArgList);

    while( sReturn >= sBuffSize - 1 )
    {
        sBuffSize = sBuffSize * 10;

        if( sLargeBuff != NULL )
        {
            free( sLargeBuff );
        }

        sLargeBuff = malloc( sBuffSize );

        va_start(sVarArgList, aFormat);
        sReturn = dbmVsnprintf(sLargeBuff, sBuffSize, aFormat, sVarArgList);
        va_end(sVarArgList);
    }

    if( sLargeBuff != NULL )
    {
        fputs( sLargeBuff, stdout );
        free( sLargeBuff );
    }
    else
    {
        fputs( sBuff, stdout );
    }

    fflush( stdout );

    return DBM_SUCCESS;
}



void dbmReplaceSpecialChar( char    * aStr )
{
    dbmChar        sBackWord[1024];
    dbmInt32       sLen = 0;
    dbmInt32       i = 0;
    dbmBool        sFound = DBM_FALSE;


    DBM_TRY_THROW( aStr != NULL, RAMP_FINISH );
    DBM_TRY_THROW( dbmStrlen( aStr ) > 0, RAMP_FINISH );

    sLen = dbmStrlen( aStr );
    i = 0;

    while( i < sLen )
    {
        sFound = DBM_FALSE;

        if( aStr[i] == '\\' )
        {
            dbmMemset( sBackWord, 0x00, DBM_SIZEOF( sBackWord ) );
            dbmStrcpy( sBackWord, (aStr + i + 2) );

            switch( aStr[i + 1] )
            {
                case 'n' :
                {
                    aStr[ i ] = '\n';
                    aStr[ i + 1 ] = 0x00;
                    sFound = DBM_TRUE;
                    break;
                }

                case 'r' :
                {
                    aStr[ i ] = '\r';
                    aStr[ i + 1 ] = 0x00;
                    sFound = DBM_TRUE;
                    break;
                }

                case 't' :
                {
                    aStr[ i ] = '\t';
                    aStr[ i + 1 ] = 0x00;
                    sFound = DBM_TRUE;
                    break;
                }

                default: 
                {
                    sFound = DBM_TRUE;
                    break;
                }
            }

            if( sFound == DBM_TRUE )
            {
                dbmStrcat( aStr, sBackWord );
                aStr[ sLen ] = 0x00;
            }
        }

        i++;
        sLen = dbmStrlen( aStr );
    }


    DBM_RAMP( RAMP_FINISH )

    return;
}




void dbmReplaceSpecialCharToPlain( char    * aStr )
{
    dbmChar        sText[1024];
    dbmInt32       sLen = 0;
    dbmInt32       i = 0;
    dbmInt32       sPos = 0;


    DBM_TRY_THROW( aStr != NULL, RAMP_FINISH );
    DBM_TRY_THROW( dbmStrlen( aStr ) > 0, RAMP_FINISH );

    dbmMemset( sText, 0x00, sizeof(sText) );
    sLen = dbmStrlen( aStr );

    for( i = 0 ; i < sLen ; i ++ )
    {
        if( aStr[i] == '\r' )
        {
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = 'r'; sPos ++;
        }
        else if( aStr[i] == '\n' )
        {
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = 'n'; sPos ++;
        }
        else if( aStr[i] == '\t' )
        {
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = 't'; sPos ++;
        }
        else if( aStr[i] == '|' )
        {
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = '|'; sPos ++;
        }
        else if( aStr[i] == '&' )
        {
            sText[sPos] = '\\'; sPos ++;
            sText[sPos] = '&'; sPos ++;
        }
        else
        {
            sText[sPos] = aStr[i];
            sPos ++;
        }
    }

    dbmStrcpy( aStr, sText );
    aStr[ dbmStrlen(sText) ] = 0x00;

    DBM_RAMP( RAMP_FINISH )

    return;
}

dbmStatus dbmHexPrt( const dbmChar * aTitle,
                     const void    * aData,
                     dbmSize         aSize )
{
    dbmUInt32 i;
    const dbmUInt8 * sData = aData;
    char sBuff[4096];
    int  sBufLen = 0;

    sBufLen = sprintf( sBuff, "[%s] %ld bytes (%s) \n", aTitle, aSize, __progname );

    for( i = 0; i < aSize; i++ )
    {
        if( i > 0 && i % 16 == 0 )
        {
            sBufLen += sprintf( sBuff + sBufLen, "\n" );
        }

        sBufLen += sprintf( sBuff + sBufLen, "%02X ", sData[i] );

        if( sBufLen > 4000 )
        {
            sBufLen += sprintf( sBuff + sBufLen, "\n" );
            break;
        }
    }

    if( i % 16 != 0 )
    {
        sBufLen += sprintf( sBuff + sBufLen, "\n" );
    }

    DBM_TRACE( "%s \n", sBuff );
//    printf("%s \n", sBuff);

    return DBM_SUCCESS;
}


dbmStatus dbmTransLogHdrPrt( const dbmChar     * aTitle,
                             dbmTransLogHeader * aLogHdr )
{
    fprintf( stdout, "= dbmTransLogHdrPrt[%s] \n", aTitle );
    fprintf( stdout, "PrevOffset %d \n", aLogHdr->mPrevOffset );
    fprintf( stdout, "Offset %d \n", aLogHdr->mOffset );
    fprintf( stdout, "Size %d \n", aLogHdr->mSize );
    fprintf( stdout, "RowSize %d \n", aLogHdr->mRowSize );
    fprintf( stdout, "LogType %s \n", dbmGetLogTypeStr( aLogHdr->mLogType ) );
    fprintf( stdout, "SCN %ld \n", aLogHdr->mSCN );
    fprintf( stdout, "RelExtraKey %ld \n", aLogHdr->mRelExtraKey );
    fprintf( stdout, "RelSlotId %ld \n", aLogHdr->mRelSlotId );
    fprintf( stdout, "ObjectInfo %p \n", (void *)aLogHdr->mObjectInfo );
    fprintf( stdout, "ObjectName %s \n", aLogHdr->mObjectName );
    fprintf( stdout, "Addition %s \n", aLogHdr->mAddition );
    fprintf( stdout, "NeedSkip %d \n", aLogHdr->mNeedSkip );
    fprintf( stdout, "IsMemCommit %d \n", aLogHdr->mIsMemCommit );
    fprintf( stdout, "IsValid %d \n", aLogHdr->mIsValid );

    dbmHexPrt( "LogHdr", aLogHdr, sizeof(dbmTransLogHeader) );

    return DBM_SUCCESS;
}


void dbmDebugInfo()
{
#ifdef DBM_DEBUG

    fflush( stdout );
#endif
}





dbmStatus dbmConvertNormalValue( dbmAllocator       * aAllocator,
                                 dbmChar            * aVal,
                                 dbmPropValue       * aOutput,
                                 dbmPropValueType     aValueType,
                                 dbmErrorStack      * aErrorStack )
{
    dbmChar   * sTmpArea = NULL;
    dbmChar   * sEnvVal = NULL;
    dbmChar     sEnvName[128];
    dbmChar     sVal[1024];
    dbmInt64    sLongVal = 0;
    dbmInt32    sIntVal = 0;
    dbmInt32    sLen;
    dbmInt32    sStartPos = 0;
    dbmInt32    sEndPos = 0;
    dbmInt32    i;
    dbmInt32    j;

    switch( aValueType )
    {
        /**
         * Case 12G or 12M 등을 쓴 경우
         */

        case DBM_VALUE_TYPE_BIT:
        {
            DBM_TRY_THROW( aVal != NULL, RAMP_ERR_INVALID );

            dbmMemset( sVal, 0x00, sizeof(sVal) );
            dbmStrcpy( sVal, aVal );
//            DBM_TRACE("CACHE LOG %s \n", sVal );
            sLen = dbmStrlen( aVal );

            sTmpArea = dbmStrchr( sVal, '-' );
            if( sTmpArea != NULL )
            {
                *sTmpArea = 0x00;
                sTmpArea++;
            }
            else
            {
                sTmpArea = sVal;
            }

            i = atoi( sVal );
            j = atoi( sTmpArea ) + 1;

            (*aOutput).mInt32 = 0;
            
            while( i < j )
            {
                sIntVal = 1 << i;

                (*aOutput).mInt32 += sIntVal;

//                DBM_TRACE("CACHE LOG %x, %x \n", sIntVal, (*aOutput).mInt32 );

                i++;
            }


            break;
        }

        case DBM_VALUE_TYPE_NUM:
        {
            DBM_TRY_THROW( aVal != NULL, RAMP_ERR_INVALID );

            (*aOutput).mInt32 = atoi( aVal );

            break;
        }

        case DBM_VALUE_TYPE_SIZE:
        {
            DBM_TRY_THROW( aVal != NULL, RAMP_ERR_INVALID );

            dbmMemset( sVal, 0x00, sizeof(sVal) );
            dbmStrcpy( sVal, aVal );
            sLen = dbmStrlen( aVal );

            if( sVal[ sLen - 1 ] == 'K' || sVal[ sLen - 1 ] == 'k' )
            {
                sVal[ sLen - 1 ] = 0x00;
                sLongVal = atol(sVal ) * (1024);
            }
            else if( sVal[ sLen - 1 ] == 'M' || sVal[ sLen - 1 ] == 'm' )
            {
                sVal[ sLen - 1 ] = 0x00;
                sLongVal = atol(sVal ) * (1024 * 1024);
            }
            else if( sVal[ sLen - 1 ] == 'G' || sVal[ sLen - 1 ] == 'g' )
            {
                sVal[ sLen - 1 ] = 0x00;
                sLongVal = atol(sVal ) * (1024 * 1024 * 1024);
            }
            else
            {
                sLongVal = atol( sVal );
            }
            (*aOutput).mInt64 = sLongVal;

            break;
        }

        /**
         * Path등에 ${} 이런게 설정된 경우
         */
        
        case DBM_VALUE_TYPE_PATH:
        {
            if( aVal == NULL )
            {
                (*aOutput).mStr = NULL;
                break;
            }

            dbmMemset( sVal, 0x00, sizeof(sVal) );
            dbmStrcpy( sVal, aVal );
            sLen = dbmStrlen( sVal );

            sTmpArea = (dbmChar *)malloc( sLen * 2 );

            for( i = 0 ; i < sLen ; i ++ )
            {
                if( dbmStrncmp( sVal + i, "${", 2 ) == 0 )
                {
                    sStartPos = i + 2;
                    for( j = i + 1; j < sLen ; j ++ )
                    {
                        if( sVal[j] == '}' )
                        {
                            sEndPos = j;
                            break;
                        }
                    }

                    dbmMemset( sTmpArea, 0x00, (sLen * 2) );
                    dbmMemcpy( sTmpArea, (sVal + sEndPos + 1), (sLen - sEndPos));

                    dbmMemset( sEnvName, 0x00, sizeof(sEnvName) );
                    dbmStrncpy( sEnvName, (sVal + sStartPos), (sEndPos-sStartPos)+1 );

                    sEnvVal = getenv( sEnvName );

                    if( sEnvVal != NULL )
                    {
                        sVal[ i ] = 0x00;
                        dbmStrcat( sVal, sEnvVal );
                        sVal[ i + dbmStrlen(sEnvVal) ] = 0x00;
                        dbmStrcat( sVal, sTmpArea );

                        sLen = dbmStrlen( sVal );
                     }
                }
            }

            free( sTmpArea );
 
            DBM_TRY( dbmAllocMemory( aAllocator,
                                     dbmStrlen( sVal ) + 1,
                                     (void **)&((*aOutput).mStr),
                                     aErrorStack ) == DBM_SUCCESS );

            dbmStrcpy( (*aOutput).mStr, sVal );

            break;
        }

        case DBM_VALUE_TYPE_STRING:
        {
            if( aVal == NULL )
            {
                (*aOutput).mStr = NULL;
                break;
            }
            DBM_TRY( dbmAllocMemory( aAllocator,
                                     dbmStrlen( aVal ) + 1,
                                     (void **)&((*aOutput).mStr),
                                     aErrorStack ) == DBM_SUCCESS );

            dbmStrcpy( (*aOutput).mStr, aVal );
            break;
        }


        /**
         * Boolean인데 ON, TRUE등등으로 설정한 경우
         */

        case DBM_VALUE_TYPE_BOOLEAN:
        {
            DBM_TRY_THROW( aVal != NULL, RAMP_ERR_INVALID );

            dbmMemset( sVal, 0x00, sizeof(sVal) );
            dbmStrcpy( sVal, aVal );

            if( dbmStrcmp( sVal, "1" ) == 0 )
            {
                (*aOutput).mBool = DBM_TRUE;
            }
            else if( dbmStrcmp( sVal, "0" ) == 0 )
            {
                (*aOutput).mBool = DBM_FALSE;
            }
            else
            {
                dbmUpperString( sVal );
                if( dbmStrcmp( sVal, "TRUE" ) == 0 || dbmStrcmp( sVal, "ON" ) == 0 )
                {
                    (*aOutput).mBool = DBM_TRUE;
                }
                else
                {
                    (*aOutput).mBool = DBM_FALSE;
                }
            }
 
            break;
        }

        default:
        {
            DBM_ASSERT( 0 );
            break;
        }
    }

    return DBM_SUCCESS;

    DBM_CATCH( RAMP_ERR_INVALID )
    {
         dbmPushError( DBM_ERROR_LEVEL_ABORT,
                       DBM_ERRCODE_INVALID_ARGS,
                       NULL,
                       aErrorStack );
    }
    DBM_FINISH

    return DBM_FAILURE;
}



#if 0
void dbmPerfStart( dbmChar         * aPerfStatPtr,
                   const dbmChar   * aTag )
{
    dbmPerfStat           * sPerfStat;
    dbmInt32                i;
    dbmInt32                sIndex = DBM_NOT_USED;


    if( aPerfStatPtr == NULL ) return;

    for( i = 0 ; i < 128; i ++ )
    {
        sPerfStat = (dbmPerfStat *)(aPerfStatPtr + (sizeof(dbmPerfStat) * i) );
        if( sPerfStat->mTag[0] == 0x00 )
        {
            dbmStrcpy( sPerfStat->mTag, aTag );
            sIndex = i;
            break;
        }
        else
        {
            if( dbmStrcmp( aTag, sPerfStat->mTag ) == 0 )
            {
                sIndex = i;
                break;
            }
        }
    }

    
    if( sIndex != DBM_NOT_USED )
    {
        gettimeofday( &sPerfStat->mStart, NULL );
    }
}





void dbmPerfEnd( dbmChar         * aPerfStatPtr,
                 const dbmChar   * aTag )
{
    dbmPerfStat           * sPerfStat;
    struct timeval          sEnd;
    dbmInt64                sGap;
    dbmInt32                i;
    dbmInt32                sIndex = DBM_NOT_USED;

    if( aPerfStatPtr == NULL ) return;

    // 시간은 먼저 구해놓고
    gettimeofday( &sEnd, NULL );

    for( i = 0 ; i < 128; i ++ )
    {
        sPerfStat = (dbmPerfStat *)(aPerfStatPtr + (sizeof(dbmPerfStat) * i) );
        if( sPerfStat->mTag[0] == 0x00 )
        {
            sIndex = i;
            break;
        }
        else
        {
            if( dbmStrcmp( aTag, sPerfStat->mTag ) == 0 )
            {
                sIndex = i;
                break;
            }
        }
    }

    
    if( sIndex != DBM_NOT_USED )
    {
        sGap = (sEnd.tv_sec - sPerfStat->mStart.tv_sec) * 1000000 + sEnd.tv_usec - sPerfStat->mStart.tv_usec;
        sPerfStat->mSum = sPerfStat->mSum + sGap;
        sPerfStat->mCount ++;
    }
}



void dbmPerfPrint( dbmChar       * aPerfStatPtr )
{
    dbmPerfStat           * sPerfStat;
    dbmInt32                i;


    if( aPerfStatPtr == NULL ) return;

    for( i = 0 ; i < 128; i ++ )
    {
        sPerfStat = (dbmPerfStat *)(aPerfStatPtr + (sizeof(dbmPerfStat) * i) );
        if( sPerfStat->mTag[0] == 0x00 )
        {
            break;
        }

        fprintf( stdout, "Thr-%d) %s Sum=%6ld Count=%ld Avg=%ld\n",
                 dbmGetTID(),
                 sPerfStat->mTag,
                 sPerfStat->mSum / 1000000,
                 sPerfStat->mCount,
                 (sPerfStat->mSum / sPerfStat->mCount ) );
        fflush( stdout );
    } 
}
#endif


/**
 * @breif 중복체크 
 * true 면 떠있는거고  false면 없는 상태라고 본다.
 */
dbmBool dbmIsRunProcess( const char         * aOpt1,
                         const char         * aOpt2,
                         dbmErrorStack      * aErrorStack )
{
    dbmBool     sIsRun;
    dbmFile     sFile;
    dbmChar     sFileName[256];
    dbmChar     sShmPrefix[64];
    dbmBool     sIsFound;
    dbmChar     sWriteBuff[32];

    DBM_TRY( dbmGetEnv( sShmPrefix, DBM_SIZEOF(sShmPrefix), DBM_SHM_PREFIX, &sIsFound, aErrorStack )
              == DBM_SUCCESS );

    if( sIsFound == DBM_FALSE )
    {
        dbmSnprintf( sFileName, DBM_SIZEOF(sFileName),
                     "/tmp/.dbm.%s",
                     __progname );
    }
    else
    {
        dbmSnprintf( sFileName, DBM_SIZEOF(sFileName),
                     "/tmp/.dbm.%s.%s",
                     sShmPrefix,
                     __progname );
    }

    if( aOpt1 != NULL && aOpt1[0] != 0x00 )
    {
        dbmStrcat( sFileName, "." );
        dbmStrcat( sFileName, aOpt1 );
    }

    if( aOpt2 != NULL && aOpt2[0] != 0x00 )
    {
        dbmStrcat( sFileName, "." );
        dbmStrcat( sFileName, aOpt2 );
    }

    DBM_TRY( dbmOpenFile( &sFile,
                          sFileName,
                          DBM_FOPEN_CREATE | DBM_FOPEN_WRITE | DBM_FOPEN_TRUNCATE | DBM_FOPEN_BINARY,
                          DBM_PERM_DEFAULT,
                          aErrorStack ) == DBM_SUCCESS );

    if( dbmLockFile( &sFile,
                     DBM_FLOCK_EXCLUSIVE | DBM_FLOCK_NONBLOCK,
                     aErrorStack ) == DBM_SUCCESS )
    {
        dbmSnprintf( sWriteBuff, DBM_SIZEOF(sWriteBuff),
                     "%d\n", 
                     dbmGetPID() );


        DBM_TRY( dbmWriteFile( &sFile,
                               sWriteBuff,
                               dbmStrlen( sWriteBuff ),
                               NULL,
                               aErrorStack ) == DBM_SUCCESS );

        sIsRun = DBM_FALSE;
    }
    else
    {
        DBM_TRY( dbmCloseFile( &sFile,
                               aErrorStack ) == DBM_SUCCESS );

        sIsRun = DBM_TRUE;
    }

    return sIsRun;

    DBM_FINISH

    return DBM_FALSE;
}

dbmStatus dbmWriteFileHeader( dbmFile       * aFileDesc, 
                              dbmFileTypeEx   aFileType,
                              dbmErrorStack * aErrorStack )
{
    dbmFileHeader     sFileHeader;

/*
#ifdef DBM_DEBUG
    dbmOffset         sOffset = 0;

    DBM_TRY( dbmSeekFile( aFileDesc,
                          DBM_FSEEK_END,
                          &sOffset,
                          aErrorStack ) == DBM_SUCCESS );
    DBM_ASSERT( sOffset == 0 );
#endif
*/


    sFileHeader.mFileType = aFileType;

    // version은 현재 모두 1로 하고 변경 필요하면 여기서 type별로 관리하도록 한다.
    sFileHeader.mFileVersion = 1;

    DBM_TRY( dbmWriteFile( aFileDesc,
                           &sFileHeader,
                           sizeof(dbmFileHeader),
                           NULL,
                           aErrorStack )
             == DBM_SUCCESS );

    return DBM_SUCCESS;

    DBM_FINISH

    DBM_DASSERT(0);

    return DBM_FAILURE;
}


dbmStatus dbmSkipFileHeader( dbmFile       * aFileDesc, 
                             dbmErrorStack * aErrorStack )
{
    dbmOffset               sOffset;

    sOffset = DBM_FILE_HEADER_SIZE;
    DBM_TRY( dbmSeekFile( aFileDesc,
                          DBM_FSEEK_SET,
                          &sOffset,
                          aErrorStack ) == DBM_SUCCESS );

    DBM_DASSERT( sOffset == DBM_FILE_HEADER_SIZE );

    return DBM_SUCCESS;

    DBM_FINISH

    DBM_DASSERT(0);

    return DBM_FAILURE;
}





#ifdef DBM_DEBUG
void _TEST_SLEEP()
{
    dbmErrorStack    sErrorStack;
    dbmChar          sInstName[ DBM_OBJECT_NAME_LEN + 1 ];
    dbmChar          sBuffer[ DBM_KEY_NAME_LEN + 1 ];
    dbmBool          sFound = DBM_FALSE;
    dbmChar        * sRetPtr = NULL;
    static dbmBool   sIsStat = DBM_FALSE;
    int              sRand;

    // 전역변수가 NULL이면 shm attach
    if( gTransHdr == NULL )
    {
        dbmClearErrorStack( &sErrorStack );

        dbmGetEnv( sInstName, sizeof(sInstName), "DBM_INSTANCE", &sFound, &sErrorStack );
        if( sFound == DBM_FALSE )
        {
            return;
        }
        dbmUpperString( sInstName );

        (void) dbmMakeKeyName( sInstName,
                               sInstName,
                               0,
                               sBuffer,
                               &sErrorStack );

        if( dbmAttachPosixShm( sBuffer,
                               (sizeof( dbmSegmentHeader ) + sizeof( dbmTransHeader )),
                               (void **)& sRetPtr,
                               &sErrorStack ) == DBM_FAILURE )
        {
            return;
        }

        gTransHdr = (dbmTransHeader *)(sRetPtr + sizeof(dbmSegmentHeader));
        DBM_TRACE( "THREAD_SLEEP_SET SUCCESS (Stat=%d)\n", gTransHdr->mIsThreadSleep );
        sIsStat = gTransHdr->mIsThreadSleep;
    }

    if( sIsStat != gTransHdr->mIsThreadSleep )
    {
        DBM_TRACE( "THREAD_SLEEP_SET CHANGED (Stat=%d)\n", gTransHdr->mIsThreadSleep );
        sIsStat = gTransHdr->mIsThreadSleep;
    }
    
    // sleep이 off면 그냥 return
    if( gTransHdr->mIsThreadSleep == DBM_FALSE )
    {
        return ;
    }

    sRand = rand();
    if( sRand % 7 == 0 )
    {
        dbmSleep(1000 * 2);
    }
}
#endif



#if 0
void dbmConvTimeValInternal( unsigned long        aTimeVal,
                             struct timeval     * aOut )
{
    aOut->tv_sec = aTimeVal / 1000000;
    aOut->tv_usec = aTimeVal % 1000000;
}
#endif




void dbmLowerString( dbmChar     * aOrg,  
                     dbmInt32      aEnd )
{
    int i;

    for( i = 0; i < aEnd ; i++ )
    {
        aOrg[i] = dbmTolower( aOrg[i] );
    }

    return;
}



dbmUInt64 dbmGetConsistentHashValue( dbmUInt64 aKey, 
                                     dbmUInt32 aBucket )
{
    dbmUInt64 sRet = -1;
    dbmUInt64 sVal = 0;

    while( sVal < aBucket )
    {
        sRet = sVal;
        aKey = aKey * 2862933555777941757ULL + 1;
        sVal = (sRet + 1) * (double)(1LL << 31) / (double)((aKey >> 33) + 1 );
    }

    return sRet;
}


#if 0
dbmStatus dbmGetInode( const dbmChar   * aKeyName,
                       ino_t           * aValue,
                       dbmErrorStack   * aErrorStack )
{
    struct stat       sFileStat;
    dbmChar           sPrefix[1024];
    dbmChar           sPrefixName[1024];
    dbmChar           sFileName[1024];
    dbmInt32          sFD   = DBM_NOT_USED;
    dbmBool           sIsFound;

    /**
     * Validate Parameters
     */

    DBM_TRY_THROW( aKeyName != NULL, RAMP_ERR_INVALID_ARGS );

    DBM_TRY( dbmCheckShmDir( aErrorStack ) == DBM_SUCCESS );

    /**
     * Prefix환경변수가 존재하면 앞단에 추가한다.
     */

    dbmMemset( sPrefixName, 0x00, sizeof( sPrefixName ) );

    DBM_TRY( dbmGetEnv( sPrefix, sizeof(sPrefix), DBM_SHM_PREFIX, &sIsFound, aErrorStack )
             == DBM_SUCCESS );

    if( sIsFound == DBM_TRUE )
    {
        if( aKeyName[0] != gDbmShmDirChar )
        {
            dbmSnprintf( sPrefixName, sizeof(sPrefixName)-1, "%s%c%s",
                         sPrefix,
                         gDbmShmDirChar,
                         aKeyName );
        }
        else
        {
            dbmSnprintf( sPrefixName, sizeof(sPrefixName)-1, "%s%s",
                         sPrefix,
                         aKeyName );
        }
    }
    else
    {
        dbmStrcpy( sPrefixName, aKeyName );
    }



    /**
     *  shm open
     */

    if( sPrefixName[0] != '/' )
    {
        dbmSnprintf( sFileName, sizeof(sFileName) - 1, "/%s", sPrefixName );
    }
    else
    {
        dbmSnprintf( sFileName, sizeof(sFileName) - 1, "%s", sPrefixName );
    }

    sFD = shm_open( sFileName,
                    O_RDWR,
                    S_IRUSR | S_IWUSR | S_IRGRP );
    DBM_TRY_THROW( sFD > 0, RAMP_ERR_OPEN_FAIL );


    /**
     * Get File Stat & check size
     */

    DBM_TRY_THROW( fstat( sFD, &sFileStat ) == DBM_SUCCESS,
                   RAMP_ERR_FSTAT_FAIL );


    // return
    close( sFD );

    *aValue = sFileStat.st_ino;
    return DBM_SUCCESS;


    /**
     * 오류종료
     */

    DBM_CATCH( RAMP_ERR_INVALID_ARGS )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_INVALID_ARGS,
                      NULL,
                      aErrorStack );
    }

    DBM_CATCH_NOLOG( RAMP_ERR_OPEN_FAIL )
    {
        if( dbmGetEnvBool( "DBM_TEST_CASE", aErrorStack ) == DBM_TRUE )
        {
            aKeyName = "testcase";
        }
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_SHM_OPEN_FAIL,
                      NULL,
                      aErrorStack,
                      aKeyName );
        DBM_SET_SYSTEM_ERROR( errno, aErrorStack );
    }

    DBM_CATCH( RAMP_ERR_FSTAT_FAIL )
    {
        dbmPushError( DBM_ERROR_LEVEL_ABORT,
                      DBM_ERRCODE_SHM_FSTAT_FAIL,
                      NULL,
                      aErrorStack,
                      aKeyName );
        DBM_SET_SYSTEM_ERROR( errno, aErrorStack );
    }


    DBM_FINISH;

    if( sFD != DBM_NOT_USED )
    {
        close( sFD );
    }

    return DBM_FAILURE;
}
#endif




dbmInt64 dbmGetElapTime( struct timeval  aStartTime )
{
    struct timeval sEndTime;
    dbmInt64       sElap;

    gettimeofday( &sEndTime, NULL );
    sElap = (sEndTime.tv_usec - aStartTime.tv_usec) + 
                (sEndTime.tv_sec - aStartTime.tv_sec) * 1000000;

    return sElap;
}





void dbmRemoveString( dbmChar * aSrc,
                      dbmChar * aWord )
{
    dbmInt32      sLen = dbmStrlen( aSrc );
    dbmInt32      sWordLen = dbmStrlen( aWord );
    dbmInt32      i;


    for( i = 0 ; i < sLen ; i ++ )
    {
        if( dbmStrncmp( (aSrc + i), aWord, sWordLen ) == 0 )
        {
            dbmMemset( (aSrc + i), 0x20, sWordLen );
        }
    }
}

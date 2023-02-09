#ifndef __DBM_UTILS_H_
#define __DBM_UTILS_H_ 1


#include <dbmCommon.h>
#include <dbmStruct.h>
#include <dbmErrorCode.h>

void dbmTrimRight( dbmChar * aSrc );

void dbmTrimLeft( dbmChar * aSrc );

void dbmTrimAll( dbmChar * aSrc );

void dbmUpperString( dbmChar * aSrc );

void dbmLowerString( dbmChar     * aOrg,
                     dbmInt32      aEnd );

dbmInt32 dbmGetPID();

dbmInt32 dbmGetTID();

dbmInt32 dbmKill( dbmInt32          aTransId,
                  dbmInt32          aTID,
                  dbmTransHeader  * aTransHdr,
                  dbmErrorStack   * aErrorStack );

dbmStatus dbmIsAliveProcess( dbmInt32          aTransId,
                             dbmInt32          aTID, 
                             dbmTransHeader  * aTransHdr,
                             dbmBool         * aIsAlive,
                             dbmBool           aCheckTime,
                             dbmErrorStack   * aErrorStack );

void dbmNoSleep( dbmInt32 aSleepTime );

void dbmWaitStatus( volatile dbmThreadStat   * aVal,
                    dbmThreadStat              aInitVal,
                    dbmThreadStat              aStat );

void dbmSetStatus( volatile dbmThreadStat    * aVal,
                   dbmThreadStat               aStat );

dbmInt64 dbmGetCpuCount();

dbmStatus dbmDaemonize( dbmBool         * aIsChild,
                        dbmErrorStack   * aErrorStack );


#ifdef _DBM_RTF
#define DBM_RTF     DBM_RTF_
dbmInt32 DBM_RTF_( const dbmChar * aName );
void dbmSetRtfCount( dbmInt32   sCnt );
#else
#define DBM_RTF     (void)
#endif

dbmInt32 dbmMakeErrorMessage( dbmChar             * aBuffer,
                              dbmSize               aBufferSize,
                              dbmErrorData        * aErrorData,
                              dbmPrintErrorLevel    aErrorLevel );

void dbmPrintErrorStack( dbmErrorStack * sErrorStack );

dbmBool dbmGetEnvBool( dbmChar          * aEnvKey,
                       dbmErrorStack    * aErrorStack );

dbmStatus dbmGetDbfFileName( dbmChar            * aFileName,
                             dbmSize              aFileNameSize,
                             dbmChar            * aDataPath,
                             const dbmChar      * aName,
                             dbmErrorStack      * aErrorStack );

dbmStatus dbmParseTime( dbmChar         * aTimeStr,
                        dbmInt32          aMicroPos,
                        dbmChar         * aFormat,
                        dbmTime         * aTime,
                        dbmErrorStack   * aErrorStack );


dbmStatus dbmPRead( dbmFile       * aFile,
                    void          * aBuffer,
                    dbmSize         aBytes,
                    dbmOffset       aOffset,
                    dbmErrorStack * aErrorStack );

dbmStatus dbmPWrite( dbmFile       * aFile,
                     void          * aBuffer,
                     dbmSize         aBytes,
                     dbmOffset       aOffset,
                     dbmErrorStack * aErrorStack );

dbmStatus dbmPrintf( const dbmChar *aFormat,
                       ...);


void dbmReplaceSpecialChar( char  * );

void dbmReplaceSpecialCharToPlain( char *);

dbmChar * dbmGetLogTypeStr( dbmLogType aLogType );

dbmStatus dbmHexPrt( const dbmChar * aTitle,
                     const void    * aData,
                     dbmSize         aSize );

dbmStatus dbmTransLogHdrPrt( const dbmChar     * aTitle,
                             dbmTransLogHeader * aLogHdr );

void dbmDebugInfo();

void dbmGetVersionString( dbmChar * aBuffer,
                          dbmInt32  aBufferSize );
 
dbmStatus dbmConvertNormalValue( dbmAllocator       * aAllocator,
                                 dbmChar            * aVal,
                                 dbmPropValue       * aOutput,
                                 dbmPropValueType     aValueType,
                                 dbmErrorStack      * aErrorStack );

void dbmPerfStart( dbmChar         * aPerfStatPtr,
                   const dbmChar   * aTag );


void dbmPerfEnd( dbmChar         * aPerfStatPtr,
                 const dbmChar   * aTag );


void dbmPerfPrint( dbmChar         * aPerfStatPtr );

dbmBool dbmIsRunProcess( const char         * aOpt1,
                         const char         * aOpt2,
                         dbmErrorStack      * aErrorStack );

dbmStatus dbmWriteFileHeader( dbmFile       * aFileDesc, 
                              dbmFileTypeEx   aFileType,
                              dbmErrorStack * aErrorStack );

dbmStatus dbmSkipFileHeader( dbmFile       * aFileDesc, 
                             dbmErrorStack * aErrorStack );

void dbmConvTimeValInternal( unsigned long        aTimeVal,
                             struct timeval     * aOut );


dbmUInt64 dbmGetConsistentHashValue( dbmUInt64 aKey,
                                     dbmUInt32 aBucket );

dbmStatus dbmGetInode( const dbmChar   * aKeyName,
                       ino_t           * aValue,
                       dbmErrorStack   * aErrorStack );

dbmInt64 dbmGetElapTime( struct timeval  aStartTime );

void dbmRemoveString( dbmChar * aSrc,
                      dbmChar * aWord );


#ifdef DBM_DEBUG

#define TEST_SLEEP      _TEST_SLEEP
void _TEST_SLEEP();
#else
#define TEST_SLEEP()     (void)( 1 )
#endif


#endif

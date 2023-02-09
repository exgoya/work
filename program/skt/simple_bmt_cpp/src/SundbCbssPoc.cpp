#include "SundbCbssPoc.h"


/****************************************************************************** 
* Static Function Prototype
******************************************************************************/
static void usage ( );
static void _sundb_setArg ( int* pArgc, char** ppArgv );
static char* _sundb_getArg ( const char* name, const char* long_name );
static char* _sundb_getArg_ ( const char* name );
static int sunPthreadStart ( );
static void* sundbPocStart( void* param );

/****************************************************************************** 
* PARAM Thread Array
******************************************************************************/
typedef struct PARAM
{
    int idx;            // thread number
    int type;           // 1:ind 2:sum 3:ind & sum
    char dml[1];        // 1:insert 2:update 3:delete 4:select
    int db_type;          // 1:group 2:no-group
    int scenario;
    int s_max_count;    // session Max Cont
    int t_max_count;    // transaction Max Count
} PARAM;

/****************************************************************************** 
* Global Static Common Declare
******************************************************************************/
int             _sundb_argc = 0;   
const char**    _sundb_argv = NULL;
int             _catch_err = 0;
int             g_use_client;
char            g_use_dml[1];
int             g_use_max_count;
PARAM           thr_param[SUNDB_MAX_CLIENT];

/****************************************************************************** 
* Name : sundbPocStart
******************************************************************************/
void* sundbPocStart ( void* param )
{
    SundbCbssPoc*   sSundbPoc = NULL;

    try
    {
        sSundbPoc = new SundbCbssPoc ( (int)(((PARAM*)param)->idx) ,
                                       (char*)(((PARAM*)param)->dml),
                                       (int)(((PARAM*)param)->scenario),
                                       (int)(((PARAM*)param)->s_max_count),
                                       (int)(((PARAM*)param)->t_max_count)
                                       );


        if ( sSundbPoc->sundbPocStart() != 0 )
        {
            throw(-1);
        }

        delete ( sSundbPoc );


        return NULL;
    }
    catch ( int sExpNo )
    {

        if ( sExpNo == -1 )
        {
            _PRT ( " sundbPocStart Error[%d] \n", sExpNo );
        }
    }

    return NULL;
}

/****************************************************************************** 
* Name : sunPthreadStart
******************************************************************************/
int sunPthreadStart ()
{
    int i;
    int status;
    int err;
    void* tret;

    // thread declare
    pthread_t      tid[g_use_client+1];

    for ( i=1 ; i <= g_use_client; i ++ )
    {

        // type
        thr_param[i].idx = i;
        memcpy( thr_param[i].dml , g_use_dml, 1 ); 
        thr_param[i].s_max_count = g_use_client;
        thr_param[i].t_max_count = g_use_max_count;
        thr_param[i].scenario = SUNDB_SCENARIO;

        status = pthread_create( &tid[i], NULL, sundbPocStart, &thr_param[i]);

        if ( status < 0 )
        {
            fprintf( stdout, "pthread create rror \n" );
            return -1;
        }

    }

    for ( i=1 ; i <= g_use_client; i ++ )
    {
        err = pthread_join ( tid[i], &tret );
        if ( err != 0 )
        {
            fprintf(stdout, "can't join with thread 2: %s\n", strerror(err));
        }
    }

    return 0;

}

/****************************************************************************** 
* Name : _sundb_getArg_
******************************************************************************/
char* _sundb_getArg_ ( const char* name )
{
    int     i;
    char    sName[32];
    int     sLen;
    int     sWithVal = 0;

    try
    {
        if ( _sundb_argv == NULL )
            throw( -1 );

        if ( name == NULL )
            return NULL;

        assert ( _sundb_argc > 0 );
        assert ( name != NULL && strlen ( name ) != 0 );

        memcpy ( sName, name, sizeof( sName ) );
        sLen = strlen ( sName );

        if ( sName[sLen-1] == ':' )
        {
            sLen--;
            sName[sLen] = 0;
            sWithVal = 1;
        }


        for ( i = 1; i < _sundb_argc; i++ )
        {
            if ( _sundb_argv[i][0] != '-' || _sundb_argv[i][1] != sName[0] )
                continue;

            if ( strcmp ( _sundb_argv[i] + 1, sName ) != 0 )
                continue;

            if ( sWithVal == 0 )
                return (char*)_sundb_argv[i];

            if ( i + 1 >= _sundb_argc || _sundb_argv[i+1][0] == '-' )
                return NULL;

            return (char*)_sundb_argv[i+1];
        }

        return NULL;
    }
    catch ( int sExpNo )
    {
        if ( sExpNo == -1 )
        {
            _PRT ( " _sundb_getArgv_ error [%d] \n", sExpNo );
        }
    }

    return NULL;
}


/****************************************************************************** 
* Name : _sundb_getArg
******************************************************************************/
char* _sundb_getArg ( const char* name, const char* long_name )
{
    char    sName[32] = { '-' };
    char*   pChar = NULL;

    pChar = _sundb_getArg_( name );

    if ( pChar == NULL && long_name != NULL )
    {
        strncpy ( &sName[1], long_name, strlen(long_name) + 1 );
        pChar = _sundb_getArg_( sName );
    }

    return pChar;

}

/****************************************************************************** 
* Name : Usage
******************************************************************************/
void usage ( )
{

    _PRT ( "Usage : %s [-h] [-c] thread count [-u] <i:Insert/u:update/d:delete/s:select> [-m] transaction count\n", _sundb_argv[0] );
    _PRT ( "\n" );
    _PRT ( "Option:\n" );
    _PRT ( " -h : This help message\n" );
    _PRT ( " -c : 10 : client process 10 \n" );
    _PRT ( " -u : i:Insert - u:update - d:delete - s:select \n" );
    _PRT ( " -m : clietn transaction count 1000건\n" );
    _PRT ( " SundbCbssPoc -c 10 -u i -m 1000\n" ); 

    exit(-1);
}


/****************************************************************************** 
* Name : _sundb_setArg
******************************************************************************/
void _sundb_setArg ( int* pArgc, char** ppArgv )
{
    try
    {
        if ( _sundb_argv != NULL )
        {
            _catch_err = -1;
            throw ( _catch_err );
        }

        _sundb_argc = *pArgc;
        _sundb_argv = (const char**)ppArgv;

    }
    catch( int _catch_err )
    {
        if ( _catch_err == -1 )
        {   
            _PRT (" _sundb_setArg Error [%d] \n", _catch_err );
        }
    }
}


/****************************************************************************** 
* Name : sundbPocDelete
******************************************************************************/
int SundbCbssPoc::sundbPocDelete()
{
    char sSql[512]= "\0";

    try
    {
        sStep = 1;
        //ODBC Connect()
        if ( (_rc = sundbOdbcConnect()) != 0 )
        {
            throw( _rc );
        } 

        sStep = 2;
        //ODBC Setup()

        sStep = 3;
        //ODBC Alloc()
        if ( ( _rc = sundbOdbcAlloc() ) != 0 )
        {
            throw ( _rc );
        }        

        // sql string set 3:delete
        _sundb_sql_set ( sSql, 3, mScenario );

        sStep = 4;
        //ODBC Preapre()
        if ( ( _rc = sundbOdbcPrepare ( sSql ) ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 5;
        //ODBC BindParameter()
        if ( ( _rc = sundbOdbcBindParaMeter () ) != 0  )
        {
            throw ( _rc );
        }

        sStep = 6;
        //ODBC ColBind() -- insert X

        //DATA VECTOR()
        // _sundb_vector_set ( (DATA *)sStruPt, mIdx, &sMax, &sMin ); 
        _sundb_vector_set ( mIdx, &sMax, &sMin, mTransMax );


        sStep = 7;
        //ODBC EXECTUE()
        if ( ( _rc = sundbOdbcExecute () ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 8;
        //ODBC HANDLE END()
        if ( ( _rc = sundbOdbcFreeEnd() ) != 0 )
        {
            throw ( _rc );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == 1 )
        {
            printf ( "thr[%d] : sundbOdbcConnect Error[%d] \n", mIdx,  _catch_err );
        } 
        else
        if ( _catch_err == 3 )
        {
            printf ( "thr[%d] : sundbOdbcAlloc Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 4 )
        {
            printf ( "thr[%d] : sundbOdbcPrepare Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 5 )
        {
            printf ( "thr[%d] : sundbOdbcBindParaMeter Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 7 )
        {
            printf ( "thr[%d] : sundbOdbcExecute Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 8 )
        {
            printf ( "thr[%d] : sundbOdbcFreeEnd Error[%d] \n", mIdx, _catch_err );
        } 

        SQLFreeStmt(sStmt, SQL_CLOSE);
        SQLDisconnect( sDbc );
        SQLFreeHandle( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
}

/****************************************************************************** 
* Name : sundbPocInd
******************************************************************************/
int SundbCbssPoc::sundbPocInd()
{
    try
    {
        gettimeofday ( &sStart , NULL ) ;

        //Ind Performance Check
        switch ( tolower( mDml[0]) )
        {
            case 'i':
                sundbPocInsert();

                break;

            case 'u' :
                sundbPocUpdate();

                break;

            case 's' :
                sundbPocSelect();

                break;

            case 'd' :
                sundbPocDelete();

                break;

            default :
                throw ( -1 );
        }

        gettimeofday ( &sEnd , NULL ) ;

        sDiff = ( sEnd.tv_sec + sEnd.tv_usec/1000000.0 ) - ( sStart.tv_sec + sStart.tv_usec/1000000.0);
        //printf ( "[%d]:%.6f us \n", mIdx, sDiff ) ;
        printf ( "[%d] : %.0f TPS \n", mIdx, (double)mTransMax / sDiff );

        return 0;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
            _PRT( " sundbPocInd Error [%d] \n", _catch_err );


        return _catch_err;
    }

}


/****************************************************************************** 
* Name : sundbOdbcConnect
******************************************************************************/
int SundbCbssPoc::sundbOdbcConnect()
{
    char    sDbcStr[64] = {0x00};

    try
    {
        sStep = 1;
        if ( (_rc = SQLAllocEnv ( &s_env )) != SQL_SUCCESS )
        {
            throw ( sStep );
        }

        SQLSetEnvAttr( s_env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0 );

        sStep = 2;
        if ( ( _rc = SQLAllocConnect ( s_env, &sDbc ) ) != SQL_SUCCESS )
        {
            throw ( _rc );
        }

        _sundb_dbc_name_set ( sDbcStr, 1 );

        sStep = 3;
        if ( ( _rc = SQLConnect ( sDbc,
                        (SQLCHAR*)sDbcStr,
                        SQL_NTS,
                        (SQLCHAR*)"test",
                        SQL_NTS,
                        (SQLCHAR*)"test",
                        SQL_NTS ) ) != SQL_SUCCESS )
        {
            throw ( sStep );
        }

        return SQL_SUCCESS;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == 1 )
        {
            _PRT ( " SQLAllocEnv Error [%d] \n", _catch_err );
        }
        else if ( _catch_err == 2 )
        {
            _PRT ( "SQLAllocConnect Error [%d] \n", _catch_err );
        }
        else
        {
            _PRT ( " Connect Error \n" );

        }

        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbOdbcAlloc
******************************************************************************/
int SundbCbssPoc::sundbOdbcAlloc()
{
    try
    {
        if ( ( _rc = SQLSetConnectAttr(sDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_INTEGER) ) != SQL_SUCCESS )
        {
            throw( 1 );
        }

        if ( ( _rc = SQLAllocStmt( sDbc, &sStmt ) ) != SQL_SUCCESS )
        {
            throw( 2 );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        if ( sStep == 1 )
        {
            _PRT( "SQLSetConnectAttr Error[%d] \n", _catch_err );
        }
        else
        {
            _PRT( "SQLAllocStmt Error [%d] \n", _catch_err );
        }

        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbOdbcPrepare
******************************************************************************/
int SundbCbssPoc::sundbOdbcPrepare( char* aSql )
{
    try
    {

        if ( SQLPrepare(sStmt,(SQLCHAR *)aSql, SQL_NTS) != SQL_SUCCESS )
        {
            _PRT ( "SQLPrepare Insert miss error \n" );

            throw ( -1 );
        }

        return 0;
    }
    catch ( int _catch_err )
    {

        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbOdbcBindParaMeter
******************************************************************************/
int SundbCbssPoc::sundbOdbcBindParaMeter()
{
    try
    {
        switch ( mDml[0] )
        {
            case 'i': //insert
                switch ( mScenario )
                {
                    case 1:
                        if ( SQLBindParameter( sStmt,
                                     1,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     130,
                                     0,
                                     mRecord1.sIdentifier,
                                     sizeof(mRecord1.sIdentifier),
                                     &mRecord1Ind.sIdentifier) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     2,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     84,
                                     0,
                                     mRecord1.sKey_index_p,
                                     sizeof(mRecord1.sKey_index_p),
                                     &mRecord1Ind.sKey_index_p) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     3,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     196,
                                     0,
                                     mRecord1.sKey_index_s,
                                     sizeof(mRecord1.sKey_index_s),
                                     &mRecord1Ind.sKey_index_s) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     4,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     1024,
                                     0,
                                     mRecord1.sPayload,
                                     sizeof(mRecord1.sPayload),
                                     &mRecord1Ind.sPayload) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     5,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_CHAR,
                                     8,
                                     0,
                                     mRecord1.sOpen_date,
                                     sizeof(mRecord1.sOpen_date),
                                     &mRecord1Ind.sOpen_date) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     6,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_CHAR,
                                     6,
                                     0,
                                     mRecord1.sOpen_time,
                                     sizeof(mRecord1.sOpen_time),
                                     &mRecord1Ind.sOpen_time) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        break;

                    default :
                        throw(-1);
                }

                break;

            case 'u': //update
                switch ( mScenario )
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        if ( SQLBindParameter( sStmt,
                                     1,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     84,
                                     0,
                                     mRecord1.sKey_index_p,
                                     sizeof(mRecord1.sKey_index_p),
                                     &mRecord1Ind.sKey_index_p) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     2,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     196,
                                     0,
                                     mRecord1.sKey_index_s,
                                     sizeof(mRecord1.sKey_index_s),
                                     &mRecord1Ind.sKey_index_s) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     3,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     1024,
                                     0,
                                     mRecord1.sPayload,
                                     sizeof(mRecord1.sPayload),
                                     &mRecord1Ind.sPayload) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     4,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_CHAR,
                                     8,
                                     0,
                                     mRecord1.sOpen_date,
                                     sizeof(mRecord1.sOpen_date),
                                     &mRecord1Ind.sOpen_date) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     5,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_CHAR,
                                     6,
                                     0,
                                     mRecord1.sOpen_time,
                                     sizeof(mRecord1.sOpen_time),
                                     &mRecord1Ind.sOpen_time) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     6,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     130,
                                     0,
                                     mRecord1.sIdentifier,
                                     sizeof(mRecord1.sIdentifier),
                                     &mRecord1Ind.sIdentifier) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }


                        break;

                    default:
                        throw(-2);
                }

                break;

            case 'd': //delete
                if ( SQLBindParameter( sStmt,
                             1,
                             SQL_PARAM_INPUT,
                             SQL_C_CHAR,
                             SQL_VARCHAR,
                             130,
                             0,
                             mRecord1.sIdentifier,
                             sizeof(mRecord1.sIdentifier),
                             &mRecord1Ind.sIdentifier) != SQL_SUCCESS )
                {   
                    printf("SQLBindParmeter miss error \n" );
                    PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                    throw(-1);
                }

                break;

            case 's': //select
                switch ( mScenario )
                {
                    case 1:
                        if ( SQLBindParameter( sStmt,
                                     1,
                                     SQL_PARAM_OUTPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     84,
                                     0,
                                     mRecord1.sKey_index_p,
                                     sizeof(mRecord1.sKey_index_p),
                                     &mRecord1Ind.sKey_index_p) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     2,
                                     SQL_PARAM_OUTPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     196,
                                     0,
                                     mRecord1.sKey_index_s,
                                     sizeof(mRecord1.sKey_index_s),
                                     &mRecord1Ind.sKey_index_s) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     3,
                                     SQL_PARAM_OUTPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     1024,
                                     0,
                                     mRecord1.sPayload,
                                     sizeof(mRecord1.sPayload),
                                     &mRecord1Ind.sPayload) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     4,
                                     SQL_PARAM_OUTPUT,
                                     SQL_C_CHAR,
                                     SQL_CHAR,
                                     8,
                                     0,
                                     mRecord1.sOpen_date,
                                     sizeof(mRecord1.sOpen_date),
                                     &mRecord1Ind.sOpen_date) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     5,
                                     SQL_PARAM_OUTPUT,
                                     SQL_C_CHAR,
                                     SQL_CHAR,
                                     6,
                                     0,
                                     mRecord1.sOpen_time,
                                     sizeof(mRecord1.sOpen_time),
                                     &mRecord1Ind.sOpen_time) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        if ( SQLBindParameter( sStmt,
                                     6,
                                     SQL_PARAM_INPUT,
                                     SQL_C_CHAR,
                                     SQL_VARCHAR,
                                     130,
                                     0,
                                     mRecord1.sIdentifier,
                                     sizeof(mRecord1.sIdentifier),
                                     &mRecord1Ind.sIdentifier) != SQL_SUCCESS )
                        {   
                            printf("SQLBindParmeter miss error \n" );
                            PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );
                            throw(-1);
                        }

                        break;

                    default:
                        throw(-4);
                }

                break;

            default:
                throw(-1);

        }

        return 0;
    }
    catch ( int _catch_err )
    {
        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
}

/****************************************************************************** 
* Name : sundbOdbcExecute_s (SELECT)
******************************************************************************/
int SundbCbssPoc::sundbOdbcExecute_s()
{
    int i;

    mRecordInd.sC6 = 0;

    try
    {
        for ( i=sMin; i <= sMax; i ++ )
        {
            /* PK Input String Set */
            mRecord1Ind.sIdentifier = _sundb_scenario_sql_set ( (char*)mRecord1.sIdentifier, 1, i );
retry:
            _rc = SQLExecute( sStmt );
            if ( _rc != SQL_SUCCESS )
            {

                _rc = PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

                if ( _rc == 19068 )
                {
                    _PRT ( " select fail-over [%d] \n", _rc );

                    goto retry;
                }
                throw ( _rc );
            }

#if 0 //cursor close
                //while ( SQLFetch(sStmt) != SQL_NO_DATA_FOUND )
                //{
                //    //printf ( "[%ld]\n", sInputUserId );
                //}

                //SQLFreeStmt(sStmt, SQL_CLOSE);
#endif
                //_PRT ( "sInputUserId[%ld]\n", sInputUserId );
        }

        _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
        if ( _rc != SQL_SUCCESS )
        {
            throw( _rc );
        }

        free ( mRecord.sC6 );

        return 0;
    }
    catch ( int _catch_err )
    {
        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        free ( mRecord.sC6 );

        return _catch_err;
    }
}


/****************************************************************************** 
* Name : sundbOdbcExecute_i (INSERT)
******************************************************************************/
int SundbCbssPoc::sundbOdbcExecute_i()
{
    int i;

    mRecord1Ind.sKey_index_p = _sundb_scenario_sql_set ( (char*)mRecord1.sKey_index_p, 2 );
    mRecord1Ind.sKey_index_s = _sundb_scenario_sql_set ( (char*)mRecord1.sKey_index_s, 3 );
    mRecord1Ind.sPayload     = _sundb_scenario_sql_set ( (char*)mRecord1.sPayload    , 4 );
    mRecord1Ind.sOpen_date   = _sundb_scenario_sql_set ( (char*)mRecord1.sOpen_date  , 5 );
    mRecord1Ind.sOpen_time   = _sundb_scenario_sql_set ( (char*)mRecord1.sOpen_time  , 6 );

    try
    {
        for ( i=sMin; i <= sMax; i ++ )
        {
            /* PK Input String Set */
            mRecord1Ind.sIdentifier = _sundb_scenario_sql_set ( (char*)mRecord1.sIdentifier, 1, i );

            _rc = SQLExecute( sStmt );
            if ( _rc != SQL_SUCCESS )
            {
                throw ( _rc );
            }

            _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }
        }

        _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
        if ( _rc != SQL_SUCCESS )
        {
            throw( _rc );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
} /* End of sundbOdbcExecute_i() */

/****************************************************************************** 
* Name : sundbOdbcExecute_u (UPDATE)
******************************************************************************/
int SundbCbssPoc::sundbOdbcExecute_u()
{
    int i;

    mRecord1Ind.sKey_index_p = _sundb_scenario_sql_set ( (char*)mRecord1.sKey_index_p, 8 );
    mRecord1Ind.sKey_index_s = _sundb_scenario_sql_set ( (char*)mRecord1.sKey_index_s, 9 );
    mRecord1Ind.sPayload     = _sundb_scenario_sql_set ( (char*)mRecord1.sPayload    , 10 );
    mRecord1Ind.sOpen_date   = _sundb_scenario_sql_set ( (char*)mRecord1.sOpen_date  , 11 );
    mRecord1Ind.sOpen_time   = _sundb_scenario_sql_set ( (char*)mRecord1.sOpen_time  , 12 );

    try
    {
        for ( i=sMin; i <= sMax; i ++ )
        {
            /* PK Input String Set */
            mRecord1Ind.sIdentifier = _sundb_scenario_sql_set ( (char*)mRecord1.sIdentifier, 7, i );

            _rc = SQLExecute( sStmt );
            if ( _rc != SQL_SUCCESS )
            {
                throw ( _rc );
            }

            _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }
        }

        _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
        if ( _rc != SQL_SUCCESS )
        {
            throw( _rc );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
} /* End of sundbOdbcExecute_u() */

/****************************************************************************** 
* Name : sundbOdbcExecute_d (DELETE)
******************************************************************************/
int SundbCbssPoc::sundbOdbcExecute_d()
{
    int i;

    try
    {
        for ( i=sMin; i <= sMax; i ++ )
        {
            /* PK Input String Set */
            mRecord1Ind.sIdentifier = _sundb_scenario_sql_set ( (char*)mRecord1.sIdentifier, 7, i );

            _rc = SQLExecute( sStmt );
            if ( _rc != SQL_SUCCESS )
            {
                throw ( _rc );
            }

            _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }
        }

        _rc = SQLEndTran( SQL_HANDLE_DBC, sDbc, SQL_COMMIT );
        if ( _rc != SQL_SUCCESS )
        {
            throw( _rc );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
} /* End of sundbOdbcExecute_d() */

/****************************************************************************** 
* Name : sundbOdbcExecute
******************************************************************************/
int SundbCbssPoc::sundbOdbcExecute()
{
    try
    {
        if ( mDml[0] == 'i' ) //Insert
        {
            _rc = sundbOdbcExecute_i();
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }

        }
        else
        if ( mDml[0] == 'u' ) //Update
        {
            _rc = sundbOdbcExecute_u();
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }

        }
        else
        if ( mDml[0] == 'd' ) //Delete
        {
            _rc = sundbOdbcExecute_d();
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }

        }
        else //Select
        {
            _rc = sundbOdbcExecute_s();
            if ( _rc != SQL_SUCCESS )
            {
                throw( _rc );
            }
        }

        return 0;
    }
    catch ( int _catch_err )
    {

        _PRT( " I/U/D/S Error [%c] SQL ERROR[%d]  \n", mDml[0], _catch_err );
        PrintDiagnosticRecord( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbOdbcFreeEnd
******************************************************************************/
int SundbCbssPoc::sundbOdbcFreeEnd()
{
    try
    {

        SQLFreeStmt(sStmt, SQL_CLOSE);
        SQLDisconnect( sDbc );
        SQLFreeHandle( SQL_HANDLE_STMT, sStmt );

        return 0;
    }
    catch ( int _catch_err )
    {
        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbPocInsert
******************************************************************************/
int SundbCbssPoc::sundbPocInsert()
{
    char sSql[512]= "\0";

    try
    {
        sStep = 1;
        //ODBC Connect()
        if ( (_rc = sundbOdbcConnect()) != 0 )
        {
            throw( _rc );
        } 

        sStep = 2;
        //ODBC Setup()

        sStep = 3;
        //ODBC Alloc()
        if ( ( _rc = sundbOdbcAlloc() ) != 0 )
        {
            throw ( _rc );
        }        

        // sql string set 1:insert
        _sundb_sql_set ( sSql, 1, mScenario );

        sStep = 4;
        //ODBC Preapre()
        if ( ( _rc = sundbOdbcPrepare ( sSql ) ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 5;
        //ODBC BindParameter()
        if ( ( _rc = sundbOdbcBindParaMeter () ) != 0  )
        {
            throw ( _rc );
        }

        sStep = 6;
        //ODBC ColBind() -- insert X

        //DATA VECTOR()
        _sundb_vector_set ( mIdx, &sMax, &sMin, mTransMax );


        sStep = 7;
        //ODBC EXECTUE()
        if ( ( _rc = sundbOdbcExecute () ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 8;
        //ODBC HANDLE END()
        if ( ( _rc = sundbOdbcFreeEnd() ) != 0 )
        {
            throw ( _rc );
        }


        return 0;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == 1 )
        {
            printf ( "thr[%d] : sundbOdbcConnect Error[%d] \n", mIdx,  _catch_err );
        } 
        else
        if ( _catch_err == 3 )
        {
            printf ( "thr[%d] : sundbOdbcAlloc Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 4 )
        {
            printf ( "thr[%d] : sundbOdbcPrepare Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 5 )
        {
            printf ( "thr[%d] : sundbOdbcBindParaMeter Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 7 )
        {
            printf ( "thr[%d] : sundbOdbcExecute Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 8 )
        {
            printf ( "thr[%d] : sundbOdbcFreeEnd Error[%d] \n", mIdx, _catch_err );
        } 
        else
        {
            printf ( "thr[%d] :  Error[%d] \n", mIdx, _catch_err );
        }


        SQLFreeStmt(sStmt, SQL_CLOSE);
        SQLDisconnect( sDbc );
        SQLFreeHandle( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
}

/****************************************************************************** 
* Name : sundbPocUpdate
******************************************************************************/
int SundbCbssPoc::sundbPocUpdate()
{
    char sSql[512]= "\0";

    try
    {
        sStep = 1;
        //ODBC Connect()
        if ( (_rc = sundbOdbcConnect()) != 0 )
        {
            throw( _rc );
        } 

        sStep = 2;
        //ODBC Setup()

        sStep = 3;
        //ODBC Alloc()
        if ( ( _rc = sundbOdbcAlloc() ) != 0 )
        {
            throw ( _rc );
        }        

        // sql string set 2:update
        _sundb_sql_set ( sSql, 2, mScenario );

        sStep = 4;
        //ODBC Preapre()
        if ( ( _rc = sundbOdbcPrepare ( sSql ) ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 5;
        //ODBC BindParameter()
        if ( ( _rc = sundbOdbcBindParaMeter () ) != 0  )
        {
            throw ( _rc );
        }

        sStep = 6;
        //ODBC ColBind() -- insert X

        //DATA VECTOR()
        // _sundb_vector_set ( (DATA *)sStruPt, mIdx, &sMax, &sMin ); 
        _sundb_vector_set ( mIdx, &sMax, &sMin, mTransMax );


        sStep = 7;
        //ODBC EXECTUE()
        if ( ( _rc = sundbOdbcExecute () ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 8;
        //ODBC HANDLE END()
        if ( ( _rc = sundbOdbcFreeEnd() ) != 0 )
        {
            throw ( _rc );
        }


        return 0;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == 1 )
        {
            printf ( "thr[%d] : sundbOdbcConnect Error[%d] \n", mIdx,  _catch_err );
        } 
        else
        if ( _catch_err == 3 )
        {
            printf ( "thr[%d] : sundbOdbcAlloc Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 4 )
        {
            printf ( "thr[%d] : sundbOdbcPrepare Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 5 )
        {
            printf ( "thr[%d] : sundbOdbcBindParaMeter Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 7 )
        {
            printf ( "thr[%d] : sundbOdbcExecute Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 8 )
        {
            printf ( "thr[%d] : sundbOdbcFreeEnd Error[%d] \n", mIdx, _catch_err );
        } 

        SQLFreeStmt(sStmt, SQL_CLOSE);
        SQLDisconnect( sDbc );
        SQLFreeHandle( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbOdbcBindCol
******************************************************************************/
int SundbCbssPoc::sundbOdbcBindCol()
{
    try
    {
        _rc = SQLBindCol(sStmt, 1, SQL_C_SBIGINT, &sInputUserId, 0, NULL);

        sStep = 1;

        if ( _rc != SQL_SUCCESS )
        {
            throw ( _rc );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        if ( sStep == 1 )
        {
            _PRT ( " SQLBindCol Error \n" );
        }

        return _catch_err;
    }

}

/****************************************************************************** 
* Name : sundbPocSelect
******************************************************************************/
int SundbCbssPoc::sundbPocSelect()
{
    char sSql[512]= "\0";

    try
    {
        sStep = 1;
        //ODBC Connect()
        if ( (_rc = sundbOdbcConnect()) != 0 )
        {
            throw( _rc );
        } 

        sStep = 2;
        //ODBC Setup()

        sStep = 3;
        //ODBC Alloc()
        if ( ( _rc = sundbOdbcAlloc() ) != 0 )
        {
            throw ( _rc );
        }        

        // sql string set 4:select
        _sundb_sql_set ( sSql, 4, mScenario );

        sStep = 4;
        //ODBC Preapre()
        if ( ( _rc = sundbOdbcPrepare ( sSql ) ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 5;
        //ODBC BindParameter()
        if ( ( _rc = sundbOdbcBindParaMeter () ) != 0  )
        {
            throw ( _rc );
        }

        sStep = 6;
        //ODBC ColBind() - Fetch X
        //if (  ( _rc = sundbOdbcBindCol () ) != 0 )
        //{
        //    throw ( _rc );
        //}

        //DATA VECTOR()
        // _sundb_vector_set ( (DATA *)sStruPt, mIdx, &sMax, &sMin ); 
        _sundb_vector_set ( mIdx, &sMax, &sMin, mTransMax );


        sStep = 7;
        //ODBC EXECTUE()
        if ( ( _rc = sundbOdbcExecute () ) != 0 )
        {
            throw ( _rc );
        }

        sStep = 8;
        //ODBC HANDLE END()
        if ( ( _rc = sundbOdbcFreeEnd() ) != 0 )
        {
            throw ( _rc );
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == 1 )
        {
            printf ( "thr[%d] : sundbOdbcConnect Error[%d] \n", mIdx,  _catch_err );
        } 
        else
        if ( _catch_err == 3 )
        {
            printf ( "thr[%d] : sundbOdbcAlloc Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 4 )
        {
            printf ( "thr[%d] : sundbOdbcPrepare Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 5 )
        {
            printf ( "thr[%d] : sundbOdbcBindParaMeter Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 7 )
        {
            printf ( "thr[%d] : sundbOdbcExecute Error[%d] \n", mIdx, _catch_err );
        } 
        else
        if ( _catch_err == 8 )
        {
            printf ( "thr[%d] : sundbOdbcFreeEnd Error[%d] \n", mIdx, _catch_err );
        } 

        SQLFreeStmt(sStmt, SQL_CLOSE);
        SQLDisconnect( sDbc );
        SQLFreeHandle( SQL_HANDLE_STMT, sStmt );

        return _catch_err;
    }
}


/****************************************************************************** 
* Name : sundbPocStart
******************************************************************************/
int SundbCbssPoc::sundbPocStart()
{
    try
    {
        if ( sundbPocInd() != 0 )
        {
            throw(1);
        }

        return 0;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == 1 )
        {
            _PRT ( " sundbPocStart Kind Error [%d] \n", _catch_err );
        }

        exit(-1);
    }
}


/****************************************************************************** 
* MAIN                                                                         
******************************************************************************/
int main ( int argc, char** argv )
{
    int     sRC;
    char*   pChar = NULL;

    try
    {
        // Common Argu Set
        _sundb_setArg ( &argc, argv );

        /**************************************************
        * Input Paramenter Checking.
        **************************************************/
        pChar = _sundb_getArg ( "h", "help" );
        if ( pChar != NULL )
        {
            usage();
            return 0;
        }

        pChar = _sundb_getArg_ ( "c:" );
        if (  pChar != NULL )
        {
                g_use_client = atoi ( pChar );
        }
        else
        {
                usage();
        }

        pChar = _sundb_getArg_ ( "u:" );
        if (  pChar != NULL )
        {
            memcpy ( g_use_dml, pChar, 1 );
        }
        else
        {
            usage();
        }

        pChar = _sundb_getArg_ ( "m:" );
        if (  pChar != NULL )
        {
            g_use_max_count = atoi ( pChar ); 
        }
        else
        {
            usage();
        }

        _PRT ( " thread_count[%d] g_use_dml[%c]  g_use_max_count[%d] \n", g_use_client, g_use_dml[0], g_use_max_count );

        sRC = sunPthreadStart ( );
        if ( sRC )
        {
            _PRT ( "sundb pthread Error[%d] \n ", sRC );
            exit ( -1 );
        }

    }
    catch ( int err )
    {
        _PRT(" ");
    }
}


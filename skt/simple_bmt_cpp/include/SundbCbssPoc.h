#ifndef __CBSS_POC_H__
#define __CBSS_POC_H__

#include "SundbDefine.h"
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <map>
#include <queue>
#include <typeinfo>
#include <list>
#include <assert.h>
#include <goldilocks.h>
#include <sys/time.h>
#include <unistd.h>
#include <algorithm>
#include <numeric>

using namespace std;


/****************************************************************************** 
* Common Module Declare
******************************************************************************/
//extern void _sundb_setArg2 ( int* pArgc, char** ppArgv );
extern void _sundb_setArg2 ( );
extern void _sundb_group_process( int* aGroup, int aUseGroup, int aIdx );
extern void _sundb_dbc_name_set ( char* sDbcName, int sGroup );
extern void _sundb_sql_set ( char* aSql, int aType, int aScenario );
extern void _sundb_vector_set ( int aIdx, int* aMax,int* aMin,int aTransMax );
extern void _sundb_max_search_id ( int* aGroup, int aIdx, int aSessMax );
extern int  _sundb_scenario_sql_set ( char* aString, int aType, int aSequence = 0 );
extern int  PrintDiagnosticRecord( SQLSMALLINT aHandleType, SQLHANDLE aHandle );

/****************************************************************************** 
* Common DEFINE
******************************************************************************/
#define SUNDB_MAX_CLIENT 2048
#define SUNDB_SCENARIO 1

/****************************************************************************** 
* Common SQL DEFINE
******************************************************************************/
#define SUNDB_SELECT "select * from dual"
#define DB_FAILOVER(code) (code==-19068)

/****************************************************************************** 
* Golbal Common Module Declare
******************************************************************************/

class SundbCbssPoc 
{
public:
    // public declare type
    int     _catch_err;

    //Global struct create
    SundbCbssPoc ( int aIdx, char* aDml, int aScenario,int aSession,int aTransMax )
    {
        mIdx        = aIdx;
        memcpy ( mDml, aDml, strlen(aDml) );
        mScenario   = aScenario;
        mSessMax    = aSession;
        mTransMax   = aTransMax;
    }


    /* sundb poc main start */
    int sundbPocStart ();

    // private declare 
private:
    int     mIdx;
    int     mType;
    char    mDml[1];
    int     mDbType;
    int     mScenario;
    int     mSessMax;
    int     mTransMax;
    int     _rc;
    int     sStep;
    int     sMin;
    int     sMax;
    struct  timeval sStart, sEnd;
    double  sDiff;

    /*******************************************************
    * NAME : ODBC Module Struct
    *******************************************************/
    //### compiler 4.4.x
    SQLHENV         s_env   ;
    SQLHDBC         sDbc    ;
    SQLHSTMT        sStmt   ;
    SQLHSTMT        sStmt_d ;
    SQLHSTMT        sStmt_u ;

    //### compiler 4.7.x
    //SQLHENV         s_env   = NULL;
    //SQLHDBC         sDbc    = NULL;
    //SQLHSTMT        sStmt   = NULL;
    //SQLHSTMT        sStmt_d = NULL;
    //SQLHSTMT        sStmt_u = NULL;

    typedef struct {
    SQLINTEGER          sC1;
    SQLBIGINT           sC2;
    SQLSMALLINT         sC3;
    SQLCHAR             sC4[1000];
    SQLCHAR             sC5[100];
    char*               sC6;
    } Record;
    
    typedef struct {
        SQLLEN              sC1 ;
        SQLLEN              sC2 ;
        SQLLEN              sC3 ;
        SQLLEN              sC4 ;
        SQLLEN              sC5 ;
        SQLLEN              sC6 ;
    } RecordInd ;


    // ### APP STRUCT 
    typedef struct {
        SQLCHAR             sIdentifier [130  + 1];
        SQLCHAR             sKey_index_p[84   + 1];
        SQLCHAR             sKey_index_s[196  + 1];
        SQLCHAR             sPayload    [1024 + 1];
        SQLCHAR             sOpen_date  [8    + 1];
        SQLCHAR             sOpen_time  [6    + 1];
    } Record1;

    typedef struct {
        SQLLEN              sIdentifier ;
        SQLLEN              sKey_index_p;
        SQLLEN              sKey_index_s;
        SQLLEN              sPayload    ;
        SQLLEN              sOpen_date  ;
        SQLLEN              sOpen_time  ;
    } Record1Ind ;


    Record          mRecord;
    RecordInd       mRecordInd;

    Record1          mRecord1;
    Record1Ind       mRecord1Ind;

    SQLBIGINT       sUserId    ;
    SQLLEN          sUserIdInd ;

    SQLBIGINT       sTpoBjId   ;
    SQLLEN          sTpoBjIdInd;

    SQLINTEGER      sType;
    SQLLEN          sTypeInd;

    SQLINTEGER      sChannelNo;
    SQLLEN          sChannelNoInd;

    SQLBIGINT       sInputUserId;
    SQLLEN          sInputUserIdInd;

    SQLCHAR         sEvent_Id[19];
    SQLLEN          sEvent_Id_Len;

    SQLCHAR         sPara_Name[51];
    SQLLEN          sPara_Name_Len;



    // private Function
private:
    // ind processing
    int sundbPocInd();

    // Ind Insert
    int sundbPocInsert();
    // Ind Update
    int sundbPocUpdate();
    // Ind Delete
    int sundbPocDelete();
    // Ind Select
    int sundbPocSelect();

    /*******************************************************
    * NAME : ODBC Module
    *******************************************************/
    int sundbOdbcConnect();
    int sundbOdbcAlloc();
    int sundbOdbcPrepare( char* aSql );
    int sundbOdbcBindParaMeter();
    int sundbOdbcExecute();
    int sundbOdbcFreeEnd();
    int sundbOdbcBindCol();
    int sundbOdbcExecute_s();
    int sundbOdbcExecute_i();
    int sundbOdbcExecute_u();
    int sundbOdbcExecute_d();

};

#endif



#include "SundbCbssPoc.h"

//void _sundb_setArg2 ( int* pArgc, char** ppArgv )
void _sundb_setArg2 ()
{
    try
    {
        _PRT("aaa\n");
        //if ( _sundb_argv != NULL )
        //{
        //    _cathc_err = -1;
        //    throw ( _cathc_err );
        //}

        //_sundb_argc = *pArgc;
        //_sundb_argv = (const char**)ppArgv;

    }
    catch( int _cathc_err )
    {
        if ( _cathc_err == -1 )
        {   
            _PRT (" _sundb_setArg Error [%d] \n", _cathc_err );
        }
    }
}

/*****************************************************************
* Name : _sundb_max_search_id
*        group no return
*****************************************************************/
void _sundb_max_search_id ( int* aGroup, int aIdx, int aSessMax )
{
    try
    {
        if ( aIdx > (aSessMax-3) )
        {
            /* Max Index TRUE */
            *aGroup = 1;
        }
        else
        {
            /* NO-MAX Index FALUE */
            *aGroup = 0;
        }
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
        {   
            _PRT (" _sundb_group_process Error [%d] \n", _catch_err );
        }
    }

}
/*****************************************************************
* Name : _sundb_group_process
*        group no return
*****************************************************************/
void _sundb_group_process ( int* aGroup, int aUseGroup, int aIdx )
{
    int sGroupCheck;

    try
    {
        //return : 1,2,0 ... 1,2,0
        // hash /range 일단 동일한 group으로 반환 한다.
        if ( aUseGroup == 1 )
        {
            //Use Group
            sGroupCheck = aIdx % 3;
        }
        else
        {
            //No-Group
            sGroupCheck = aIdx % 3;
        }


        /* IDX 1 : 1 -> GROUP 1, IDX 2 : 2 ->GROUP2 , IDX 3(0) -> GROUP3 */
        
        if ( sGroupCheck == 1 )
        {
            *aGroup = 1;
        }
        else if ( sGroupCheck == 2 )
        {
            *aGroup = 2;
        }
        else
        {
            *aGroup = 3;
        }


    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
        {   
            _PRT (" _sundb_group_process Error [%d] \n", _catch_err );
        }
    }

}

/*****************************************************************
* Name : _sundb_dbc_name_set
*        dbc name return
*****************************************************************/
void _sundb_dbc_name_set ( char* sDbcName, int sGroup )
{

    try
    {
        if ( sGroup == 1 )
        {
            memcpy ( sDbcName, "GOLDILOCKS", strlen("GOLDILOCKS") );
        }
        else
        if ( sGroup == 2 )
        {
            memcpy ( sDbcName, "GOLDILOCKS2", strlen("GOLDILOCKS2") );
        }
        else
        {
            memcpy ( sDbcName, "GOLDILOCKS3", strlen("GOLDILOCKS3") );
        }
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
        {
            _PRT ( " _sundb_dbc_name_set error [%d] \n", _catch_err );
        }

    }

}


/*****************************************************************
* Name : _sundb_scenario_sql_set
*        sql scenario string set
*****************************************************************/
int _sundb_scenario_sql_set ( char* aString, int aType, int aSequence )
{
    int sRC;

    try
    {
        switch ( aType )
        {
            /* INSERT */
            case 1:
                sRC = sprintf( aString, "xxxx%d", aSequence);
                break;

            case 2:
                sRC = sprintf( aString, "sKey_index_p");
                break;

            case 3:
                sRC = sprintf( aString, "sKey_index_s");
                break;

            case 4:
                sRC = sprintf( aString, "sPayload");
                break;

            case 5:
                sRC = sprintf( aString, "20220324");
                break;

            case 6:
                sRC = sprintf( aString, "120124");
                break;

            /* UPDATE */
            case 7:
                sRC = sprintf( aString, "xxxx%d", aSequence);
                break;

            case 8:
                sRC = sprintf( aString, "sKey_index_p_update");
                break;

            case 9:
                sRC = sprintf( aString, "sKey_index_s_update");
                break;

            case 10:
                sRC = sprintf( aString, "sPayload_upadte");
                break;

            case 11:
                sRC = sprintf( aString, "20220325");
                break;

            case 12:
                sRC = sprintf( aString, "120125");
                break;

            case 13:
                sprintf( aString, "CALL_END_TM");
                break;

            case 14:
                sprintf( aString, "IO_SUBCHG_PRODUCT.SMS_COMMAND");
                break;

            case 15:
                sprintf( aString, "smsAttr");
                break;

            case 16:
                sprintf( aString, "KB_RATE_04");
                break;

            case 17:
                sprintf( aString, "KB_RATE");
                break;

            case 18:
                sprintf( aString, "f1/f2/f3");
                break;

            case 19:
                sprintf( aString, "V1");
                break;

            case 20:
                sprintf( aString, "F1/F2/F3");
                break;

            case 21:
                sprintf( aString, "RATE");
                break;

            case 22:
                sprintf( aString, "MAX_FEE");
                break;

            case 23:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.PROD_INST_ID");
                break;

            case 24:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.MSISDN");
                break;

            case 25:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.USER_TYPE");
                break;

            case 26:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.PROV_CD");
                break;

            case 27:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.PRODUCT_ATTR");
                break;

            case 28:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.PRODUCT_ID");
                break;

            case 29:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.PRODUCT_STATUS");
                break;

            case 30:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.SUBSCRIBE_EFFC_TM");
                break;

            case 31:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.SUBSCRIBE_EXPIRED_TM");
                break;

            case 32:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.ACTIVE_TM");
                break;

            case 33:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.EXPIRED_TM");
                break;

            case 34:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.FEE_TYPE");
                break;

            case 35:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.FEE");
                break;

            case 36:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.CHANNEL_CD");
                break;

            case 37:
                sprintf( aString, "IO_SUBCHG_SUBSCRIBE_RELA.PAY_MODE");
                break;

            case 38:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_ID");
                break;

            case 39:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_CODE");
                break;

            case 40:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_ATTR");
                break;

            case 41:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_CATALOG");
                break;

            case 42:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_CATEGORY            ");
                break;

            case 43:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_BILLING_ATTR        ");
                break;

            case 44:
                sprintf( aString, "IO_SUBCHG_PRODUCT.BUSINESS_PRICE              ");
                break;

            case 45:
                sprintf( aString, "IO_SUBCHG_PRODUCT.ACCOUNT_TARIFF              ");
                break;

            case 46:
                sprintf( aString, "IO_SUBCHG_PRODUCT.SUBSCRIBE_DAYS              ");
                break;

            case 47:
                sprintf( aString, "IO_SUBCHG_PRODUCT.MAX_TIMES_MONTH             ");
                break;

            case 48:
                sprintf( aString, "IO_SUBCHG_PRODUCT.MAX_TIMES                   ");
                break;

            case 49:
                sprintf( aString, "IO_SUBCHG_PRODUCT.PRODUCT_DAYS                ");
                break;

            case 50:
                sprintf( aString, "IO_SUBCHG_PRODUCT.DATA                        ");
                break;
            default:
                throw ( -1 );
#if 0
            case 51:
                sprintf( aString, "IO_SUBCHG_PRODUCT.VOICE                       ");
                break;

            case 52:
                sprintf( aString, "IO_SUBCHG_PRODUCT.SMS                         ");
                break;

            case 53:
                sprintf( aString, "IO_SUBCHG_PRODUCT.EFFC_TM                     ");
                break;

            case 54:
                sprintf( aString, "IO_SUBCHG_PRODUCT.STOPPING_TM                 ");
                break;

            case 55:
                sprintf( aString, "IO_SUBCHG_PRODUCT.EXPIRED_TM                  ");
                break;

            case 56:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.CARRIER_CD               ");
                break;

            case 57:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.MODEL                    ");
                break;

            case 58:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.RATE                     ");
                break;

            case 59:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.RATE_UNIT                ");
                break;

            case 60:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.MAX_FEE                  ");
                break;

            case 61:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.MAX_DATA                 ");
                break;

            case 62:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.EFFC_TM                  ");
                break;

            case 63:
                sprintf( aString, "IO_CARRCHG_GGSN_RATE.EXPIRED_TM               ");
                break;
#endif
        }

        return sRC;
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
        {
            _PRT ( " _sundb_scenario_sql_set  kind error [%d] \n", _catch_err );
        }

        return -1;
    }
}

/*****************************************************************
* Name : _sundb_sql_set
*        sql string set
*****************************************************************/
void _sundb_sql_set ( char* aSql, int aType, int aScenario )
{
    try
    {
        switch ( aType )
        {
            case 1: //insert
                switch ( aScenario )
                {
                    case 1:
                        sprintf( aSql, "INSERT INTO T_PG_ADS_LTE_SESSION_INFO VALUES(?, ?, ?, ?, ?, ?, sysdate )");
                        break;

                    default: 
                        _PRT ( " insert aScenario Error \n" );
                        throw ( -1 );
                }

                break;

            case 2: //update
                switch ( aScenario )
                {
                    case 1:
                        sprintf( aSql, "UPDATE T_PG_ADS_LTE_SESSION_INFO SET KEY_INDEX_P=?, KEY_INDEX_S=?, PAYLOAD=?, OPEN_DATE=?, OPEN_TIME=?, UPDATE_TIME=sysdate where IDENTIFIER=?" );
                        break;

                    default: 
                        _PRT ( " update aScenario Error \n" );
                        throw ( -1 );
                }

                break;
            case 3: //delete
                switch ( aScenario )               
                {
                    case 1:
                        sprintf( aSql, "DELETE FROM T_PG_ADS_LTE_SESSION_INFO where IDENTIFIER = ?" );
                        break;
                    default:
                    _PRT ( " delete aScenario error \n " );
                    throw ( -1 );
                }

                break;

            case 4: //select
                switch ( aScenario )
                {
                    case 1:
                        sprintf( aSql, "SELECT KEY_INDEX_P, KEY_INDEX_S, PAYLOAD, OPEN_DATE, OPEN_TIME into ?, ?, ?, ?, ? from T_PG_ADS_LTE_SESSION_INFO where IDENTIFIER = ?" );
                        break;

                    default: 
                        _PRT ( " update aScenario Error \n" );
                        throw ( -1 );
                }

                break;

            default:
                throw ( -1 );
        }
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
        {
            _PRT ( " _sundb_sql_set kind error [%d] \n", _catch_err );
        }

    }

}

/*****************************************************************
* Name : _sundb_sql_set
*        clinet start End set
*****************************************************************/
void _sundb_vector_set ( int aIdx, int* aMax,int* aMin, int aTransMax )
{

    try
    {
        *aMin = aIdx;
        
        // 2017.11.16 -shw- parameter edit
        //*aMax = *aMin * SUNDB_CLIENT_PROCESS_CNT;
        *aMax = *aMin * aTransMax;

        /* 2017.09.21 -shw- edit */
        //if ( *aMin != 1 && aType == 3 )
        if ( *aMin != 1 )
        {

            /*
             2-1 = 1 * 200000 = 200000 + 1 = 200001
             3-1 = 2 * 200000 = 400000 + 1 = 400001
             4-1 = 3 * 200000 = 600000 + 1 = 600001
            */

            //*aMin = ( (*aMin-1) * SUNDB_CLIENT_PROCESS_CNT ) + 1 ;
            *aMin = ( (*aMin-1) * aTransMax ) + 1 ;
            //*aMin = ( (*aMin-1) * 20 ) + 1 ;
        }
    }
    catch ( int _catch_err )
    {
        if ( _catch_err == -1 )
        {   
            _PRT (" _sundb_vector_set Error [%d] \n", _catch_err );
        }
    }
}


/*****************************************************************
* Name : PrintDiagnosticRecord
*        odbc error _PRT
*****************************************************************/
int PrintDiagnosticRecord( SQLSMALLINT aHandleType, SQLHANDLE aHandle )
{   
    SQLCHAR       sSQLState[6];
    SQLINTEGER    sNaiveError;
    SQLSMALLINT   sTextLength;
    SQLCHAR       sMessageText[SQL_MAX_MESSAGE_LENGTH];
    SQLSMALLINT   sRecNumber = 1;
    SQLRETURN     sReturn;
    
    /* SQLGetDiagRec returns the currrent values that contains error, warning */
    while( 1 )
    {   
        sReturn = SQLGetDiagRec( aHandleType,
                                 aHandle,
                                 sRecNumber,
                                 sSQLState,
                                 &sNaiveError,
                                 sMessageText,
                                 100,
                                 &sTextLength );
        
        if( sReturn == SQL_NO_DATA )
        {   
            _PRT ( " sReturn No Data \n" );

            break;
        }
        
        _PRT("\n=============================================\n" );
        _PRT("SQL_DIAG_SQLSTATE     : %s\n", sSQLState );
        _PRT("SQL_DIAG_NATIVE       : %d\n", sNaiveError );
        _PRT("SQL_DIAG_MESSAGE_TEXT : %s\n", sMessageText );
        _PRT("=============================================\n" );
        
        break;
    }
    
    return sNaiveError;
}


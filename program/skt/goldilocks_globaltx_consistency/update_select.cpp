#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <goldilocks.h>

#define SQL_LEN 1000
#define MSG_LEN 1024

SQLHENV  env;  // Environment Handle
SQLHDBC  dbc;  // Connection Handle
int      conn_flag;

SQLRETURN alloc_handle();
SQLRETURN db_connect();
void free_handle();

SQLRETURN execute_update1(int anum);
SQLRETURN execute_select(int anum);
SQLRETURN commit();

void execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q);

char *table_name = "TEST_GTX";
int tx_level = 0;

int main(int argc, char **argv)
{
    SQLRETURN    rc;
    int          count = 0;

    env = SQL_NULL_HENV;
    dbc = SQL_NULL_HDBC;
    conn_flag = 0;

    if (argc > 1)
    {
        tx_level = atoi(argv[1]);
    }

    /* allocate handle */
    rc = alloc_handle();
    if ( rc != SQL_SUCCESS )
    {
        free_handle();
        exit(1);
    }

    /* Connect to Altibase Server */
    rc = db_connect();
    if ( rc != SQL_SUCCESS )
    {
        free_handle();
        exit(1);
    }

    /* transaction */
    int i=0;
    while(1)
    {   
        
        rc = execute_update1(i);
        if ( rc != SQL_SUCCESS )
        {
            free_handle();
            exit(1);
        }

        rc = commit();
        if ( rc != SQL_SUCCESS )
        {
            free_handle();
            exit(1);
        }

        rc = execute_select(i);
        if ( rc != SQL_SUCCESS )
        {
            printf("exit count : %d\n", count);
            free_handle();
            exit(1);
        }

        if( (++count) %  1000 == 0 )
        {
            printf("count : %d\n", count);
        }

        i++;
    }

    /* disconnect, free handles */
    free_handle();

    return 0;
}

static void print_diagnostic(SQLSMALLINT aHandleType, SQLHANDLE aHandle)
{
    SQLRETURN   rc;
    SQLSMALLINT sRecordNo;
    SQLCHAR     sSQLSTATE[6];
    SQLCHAR     sMessage[2048];
    SQLSMALLINT sMessageLength;
    SQLINTEGER  sNativeError;

    sRecordNo = 1;

    while ((rc = SQLGetDiagRec(aHandleType,
                               aHandle,
                               sRecordNo,
                               sSQLSTATE,
                               &sNativeError,
                               sMessage,
                               sizeof(sMessage),
                               &sMessageLength)) != SQL_NO_DATA)
    {
        printf("Diagnostic Record %d\n", sRecordNo);
        printf("     SQLSTATE     : %s\n", sSQLSTATE);
        printf("     Message text : %s\n", sMessage);
        printf("     Message len  : %d\n", sMessageLength);
        printf("     Native error : 0x%X\n", sNativeError);

        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
        {
            break;
        }

        sRecordNo++;
    }
}

void execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q)
{
    printf("Error : %s\n",q);

    if (aStmt == SQL_NULL_HSTMT)
    {
        if (aCon != SQL_NULL_HDBC)
        {
            print_diagnostic(SQL_HANDLE_DBC, aCon);
        }
    }
    else
    {
        print_diagnostic(SQL_HANDLE_STMT, aStmt);
    }
}


SQLRETURN alloc_handle()
{
    /* allocate Environment handle */
    if (SQLAllocHandle(SQL_HANDLE_ENV,NULL,&env) != SQL_SUCCESS)
    {
        printf("SQLAllocEnv error!!\n");
        return SQL_ERROR;
    }

    if (SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,0) != SQL_SUCCESS)
    {
        printf("SQLSetEnvAttr error!!\n");
        return SQL_ERROR;
    }


    /* allocate Connection handle */
    if (SQLAllocHandle(SQL_HANDLE_DBC,env, &dbc) != SQL_SUCCESS) 
    {
        printf("SQLAllocConnect error!!\n");
        return SQL_ERROR;
    }
    return SQL_SUCCESS;
}

void free_handle()
{
    if ( conn_flag == 1 )
    {
        /* close connection */
        SQLDisconnect( dbc );
    }
    /* free connection handle */
    if ( dbc != NULL )
    {
        SQLFreeHandle(SQL_HANDLE_DBC, dbc );
    }
    if ( env != NULL )
    {
        SQLFreeHandle(SQL_HANDLE_ENV, env );
    }
}

SQLRETURN db_connect()
{
    char    *USERNAME = "test";        // user name
    char    *PASSWD   = "test";    // user password
    char    *NLS      = "utf8";   // NLS_USE ( KO16KSC5601, US7ASCII )
    char     connStr[1024];
    SQLINTEGER  option;

    sprintf(connStr,
            "DSN=GOLDILOCKS2;UID=%s;PWD=%s;", USERNAME, PASSWD);

    /* establish connection */
    if (SQLDriverConnect( dbc, NULL, (SQLCHAR *)connStr, SQL_NTS,
                          NULL, 0, NULL,
                          SQL_DRIVER_NOPROMPT ) != SQL_SUCCESS)
    {
        execute_err(dbc, SQL_NULL_HSTMT, "SQLDriverConnect");
        return SQL_ERROR;
    }

    conn_flag = 1;

    //if (tx_level == 1)
    //{
    //    option = ALTIBASE_SHARD_SINGLE_NODE_TRANSACTION;
    //}
    //else if (tx_level == 2)
    //{
    //    option = ALTIBASE_SHARD_MULTIPLE_NODE_TRANSACTION;
    //}
    //else if (tx_level == 3)
    //{
    //    option = ALTIBASE_SHARD_GLOBAL_TRANSACTION;
    //}
    //else
    //{
    //    option = 0;
    //}

        option = 0;
    /* AutoCommit off */
    if (SQLSetConnectAttr(dbc, SQL_ATTR_AUTOCOMMIT,
                          (void*)SQL_AUTOCOMMIT_OFF, option) != SQL_SUCCESS)
    {
        execute_err(dbc, SQL_NULL_HSTMT, "Autocommit OFF");
        return SQL_ERROR;
    }

    return SQL_SUCCESS;
}

SQLRETURN execute_update1(int anum)
{
    SQLHSTMT     stmt1 = SQL_NULL_HSTMT;
    SQLHSTMT     stmt2 = SQL_NULL_HSTMT;
    SQLRETURN    rc;
    char         query1[SQL_LEN];
    char         query2[SQL_LEN];

    /* allocate Statement handle */
    if (SQL_ERROR == SQLAllocStmt(dbc, &stmt1)) 
    {
        printf("SQLAllocStmt stmt1 error!!\n");
        return SQL_ERROR;
    }

    if (SQL_ERROR == SQLAllocStmt(dbc, &stmt2)) 
    {
        printf("SQLAllocStmt stmt2 error!!\n");
        return SQL_ERROR;
    }

    sprintf(query1,"UPDATE %s SET AMOUNT=%d WHERE ACCOUNT = 'A'", table_name,anum);
    sprintf(query2,"UPDATE %s SET AMOUNT=%d WHERE ACCOUNT = 'B'", table_name,anum);

    if (SQLPrepare(stmt1, (SQLCHAR *)query1, SQL_NTS) != SQL_SUCCESS)
    {
        execute_err(dbc, stmt1, query1);
        SQLFreeStmt(stmt1, SQL_DROP);
        return SQL_ERROR;
    }

    if (SQLPrepare(stmt2, (SQLCHAR *)query2, SQL_NTS) != SQL_SUCCESS)
    {
        execute_err(dbc, stmt2, query2);
        SQLFreeStmt(stmt2, SQL_DROP);
        return SQL_ERROR;
    }

    rc = SQLExecute(stmt1);
    if (rc != SQL_SUCCESS)
    {
        execute_err(dbc, stmt1, "SQLExecute stmt1 : ");
        SQLFreeStmt(stmt1, SQL_DROP);
        return SQL_ERROR;
    }

    rc = SQLExecute(stmt2);
    if (rc != SQL_SUCCESS)
    {
        execute_err(dbc, stmt2, "SQLExecute stmt1 : ");
        SQLFreeStmt(stmt2, SQL_DROP);
        return SQL_ERROR;
    }

    SQLFreeStmt(stmt1, SQL_DROP);
    SQLFreeStmt(stmt2, SQL_DROP);

    return SQL_SUCCESS;
}
SQLRETURN execute_select(int anum)
{
    SQLHSTMT     stmt = SQL_NULL_HSTMT;
    SQLRETURN    rc;
    char         query[SQL_LEN];
    int          amount = 0;

    /* allocate Statement handle */
    //if (SQL_ERROR == SQLAllocStmt(dbc, &stmt))
    if (SQL_ERROR == SQLAllocHandle(SQL_HANDLE_STMT,dbc, &stmt))
    {
        printf("SQLAllocStmt error!!\n");
        return SQL_ERROR;
    }

    sprintf(query,"SELECT SUM(AMOUNT) FROM %s", table_name);

    if (SQLPrepare(stmt, (SQLCHAR *)query, SQL_NTS) != SQL_SUCCESS)
    {
        execute_err(dbc, stmt, query);
        SQLFreeStmt(stmt, SQL_DROP);
        return SQL_ERROR;
    }

    /* binds application data buffers to columns in the result set */
    if (SQLBindCol(stmt, 1, SQL_C_LONG,
                   &amount, sizeof(amount), NULL) != SQL_SUCCESS)
    {
        printf("SQLBindCol error!!!\n");
        execute_err(dbc, stmt, query);
        SQLFreeStmt(stmt, SQL_DROP);
        return SQL_ERROR;
    }

    /* executes a prepared statement */
    rc = SQLExecute(stmt);
    if (rc != SQL_SUCCESS)
    {
        execute_err(dbc, stmt, "SQLExecute : ");
        SQLFreeStmt(stmt, SQL_DROP);
        return SQL_ERROR;
    }


    while ( (rc = SQLFetch(stmt)) != SQL_NO_DATA )
    {
        if (rc != SQL_SUCCESS)
        {
            execute_err(dbc, stmt, "SQLExecute : ");
            break;
        }

        if( amount != (anum * 2) )
        {
            printf("sum of amount(%d) is not %d * 2 \n", amount, anum );
            SQLFreeStmt(stmt, SQL_DROP);

            return -1;
        }
    }

    SQLFreeStmt(stmt, SQL_DROP);

    return SQL_SUCCESS;
}

SQLRETURN commit()
{
    SQLRETURN    rc;

    rc = SQLEndTran(SQL_HANDLE_DBC, dbc, SQL_COMMIT);
    if (rc != SQL_SUCCESS)
    {
        execute_err(dbc, SQL_NULL_HSTMT, "SQLEndTran : ");
        return SQL_ERROR;
    }

    return SQL_SUCCESS;
}


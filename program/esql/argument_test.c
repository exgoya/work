/***********************************************
 * This code is inserted automatically by gpec
 ***********************************************/
#include <goldilocksesql.h>
typedef struct {
  int mCharMap;
} zlpOption;
static zlpOption gZlpOption = {1};
/***********************************************
 * End of gpec automatic inclusion
 ***********************************************/


#line __LINE__ "argument_test.c"
/*
 * sample1.gc
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* EXEC SQL INCLUDE SQLCA; */
#include "sqlca.h"
#line 10 "argument_test.gc"


#define  SUCCESS  0
#define  FAILURE  -1

#define  PRINT_SQL_ERROR(aMsg)                                      \
    {                                                               \
        printf("\n");                                               \
        printf(aMsg);                                               \
        printf("\nSQLCODE : %d\nSQLSTATE : %s\nERROR MSG : %s\n",   \
               sqlca.sqlcode,                                       \
               SQLSTATE,                                            \
               sqlca.sqlerrm.sqlerrmc );                            \
    }

int Connect(char *aHostInfo, char *aUserID, char *sPassword);

int main(int argc, char **argv)
{
    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 29 "argument_test.gc"

    int          sEmpNo[2];
    /* varchar      sEName[2][20 + 1]; */
    struct { int len; char arr[20 + 1]; } sEName[2];
#line 31 "argument_test.gc"

    long         sSalary[2];
    /* EXEC SQL END DECLARE SECTION; */
#line 33 "argument_test.gc"


    printf("Connect GOLDILOCKS ...\n");
    if(Connect("DSN=GOLDILOCKS", "test", "test") != SUCCESS)
    {
        goto fail_exit;
    }

/* EXEC SQL BEGIN DECLARE SECTION; */
#line 41 "argument_test.gc"

typedef struct _BUFF_TEST {
    int         medo_tot_qty;
    int         mesu_tot_qty;
} BUFF_TEST;

BUFF_TEST          Buff;
/* EXEC SQL END DECLARE SECTION; */
#line 48 "argument_test.gc"


/* EXEC SQL
SELECT 1234
INTO  :Buff_medo_tot_qty
FROM DUAL */
{
    sqlargs_t sqlargs;
#line 85 "argument_test.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 2;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"SELECT 1234\n"
"INTO  :Buff_medo_tot_qty\n"
"FROM DUAL\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[1];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 1;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(Buff.medo_tot_qty);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(Buff.medo_tot_qty);
    sqlhv[0].value = (void *)&Buff.medo_tot_qty;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlargs.ipos = 12;
    sqlargs.fpos = 37;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 53 "argument_test.gc"


    /***********************************************
     * Retrieve MAX salary
     **********************************************/
    /* EXEC SQL SELECT empno, ename, sal INTO   :sEmpNo, :sEName, :sSalary FROM   EMP ORDER BY SAL DESC limit 1 */
{
    sqlargs_t sqlargs;
#line 143 "argument_test.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 2;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"SELECT empno, ename, sal INTO   :sEmpNo, :sEName, :sSalary FROM   EMP ORDER BY SAL DESC limit 1\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[3];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 3;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 2;
    sqlhv[0].buflen = sizeof(sEmpNo);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sEmpNo[0]);
    sqlhv[0].value = (void *)sEmpNo;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 2;
    sqlhv[1].buflen = 20 + 1;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sEName[0]);
    sqlhv[1].value = (void *)sEName;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 7;
    sqlhv[2].arr_size = 2;
    sqlhv[2].buflen = sizeof(sSalary);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sSalary[0]);
    sqlhv[2].value = (void *)sSalary;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlargs.ipos = 25;
    sqlargs.fpos = 59;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 58 "argument_test.gc"


    if(sqlca.sqlcode == SQL_NO_DATA) { printf( "No data.\n" ); }
    else if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("[ERROR] SQL ERROR -"); }


    printf( "Max salary employee:\n" );
    printf( "EMPNO: [%d], ENAME : [%s], Salary : [%ld]\n",
            sEmpNo[0], sEName[0].arr, sSalary[0] );

    /* EXEC SQL COMMIT WORK RELEASE */
{
    sqlargs_t sqlargs;
#line 228 "argument_test.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 20;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 1, 1);
}
#line 68 "argument_test.gc"

    if(sqlca.sqlcode != 0)
    {
        PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
        goto fail_exit;
    }

    printf("SUCCESS\n");
    printf("############################\n");

    return 0;

  fail_exit:

    printf("FAILURE\n");
    printf("############################\n\n");

    /* EXEC SQL ROLLBACK WORK RELEASE */
{
    sqlargs_t sqlargs;
#line 278 "argument_test.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 21;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 0, 1);
}
#line 85 "argument_test.gc"


    return 0;
}

int Connect(char *aHostInfo, char *aUserID, char *sPassword)
{
    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 92 "argument_test.gc"

    /* VARCHAR  sUid[80]; */
    struct { int len; char arr[80]; } sUid;
#line 93 "argument_test.gc"

    /* VARCHAR  sPwd[20]; */
    struct { int len; char arr[20]; } sPwd;
#line 94 "argument_test.gc"

    /* VARCHAR  sConnStr[1024]; */
    struct { int len; char arr[1024]; } sConnStr;
#line 95 "argument_test.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 96 "argument_test.gc"


    /*----------------------------------------------
      Log on GOLDILOCKS
      ------------------------------------------------*/
    strcpy((char *)sUid.arr, aUserID);
    sUid.len = (short)strlen((char *)sUid.arr);
    strcpy((char *)sPwd.arr, sPassword);
    sPwd.len = (short)strlen((char *)sPwd.arr);
    strcpy((char *)sConnStr.arr, aHostInfo);
    sConnStr.len = (short)strlen((char *)sConnStr.arr);

    /* DB 연결 */
    /* EXEC SQL CONNECT :sUid IDENTIFIED BY :sPwd USING :sConnStr */
{
    sqlargs_t sqlargs;
#line 348 "argument_test.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 41;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Connect(NULL, &sqlargs, sConnStr.arr, sUid.arr, sPwd.arr);
}
#line 109 "argument_test.gc"

    if(sqlca.sqlcode != 0)
    {
        goto fail_exit;
    }

    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] Connection Failure!");

    return FAILURE;
}


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


#line __LINE__ "cursor_sleep.c"
/*
 * sample2.gc
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>


/* EXEC SQL INCLUDE SQLCA; */
#include "sqlca.h"
#line 14 "cursor_sleep.gc"


#define  FAILURE  -1
#define  SUCCESS 0

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

void CalTime(struct timeval startTime,struct timeval endTime, char *inte){
    struct timeval gepTime;
    gepTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
    gepTime.tv_usec = endTime.tv_usec - startTime.tv_usec;

    if ( gepTime.tv_usec < 0 )
    {
        printf("xxl\n");
        gepTime.tv_sec = gepTime.tv_sec - 1;
        gepTime.tv_usec = gepTime.tv_usec + 1000000;
    }
    printf("%s ellapsed time [%02ld.%02ld] second\n",inte, gepTime.tv_sec, gepTime.tv_usec);


}
int main(int argc, char **argv)
{

    struct timeval startTimeA , startTimeB, endTimeA, endTimeB;

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 51 "cursor_sleep.gc"

    int          sEmpNo;
    /* varchar      sEName[20 + 1]; */
    struct { int len; char arr[20 + 1]; } sEName;
#line 53 "cursor_sleep.gc"

    char         sJob[20];
    long         sSalary;
    /* EXEC SQL END DECLARE SECTION; */
#line 56 "cursor_sleep.gc"


    int  sRecordCount = 0;

    printf("Connect GOLDILOCKS ...\n");
    if(Connect("DSN=GOLDILOCKS", "test", "test") != SUCCESS)
    {
        goto fail_exit;
    }
    /* EXEC SQL ALTER SESSION SET TRACE_LOG_ID = 111111 */
{
    sqlargs_t sqlargs;
#line 93 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"ALTER SESSION SET TRACE_LOG_ID = 111111;\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 65 "cursor_sleep.gc"
 if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("[ERROR] SQL ERROR -"); }
    /* EXEC SQL ALTER SESSION SET TRACE_LOG_TIME_DETAIL = 1 */
{
    sqlargs_t sqlargs;
#line 129 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"ALTER SESSION SET TRACE_LOG_TIME_DETAIL = 1;\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 66 "cursor_sleep.gc"
 if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("[ERROR] SQL ERROR -"); }
    /* EXEC SQL ALTER SESSION SET TRACE_LONG_RUN_TIMER = 1 */
{
    sqlargs_t sqlargs;
#line 165 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"ALTER SESSION SET TRACE_LONG_RUN_TIMER = 1;\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 67 "cursor_sleep.gc"
 if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("[ERROR] SQL ERROR -"); }
    /* EXEC SQL ALTER SESSION SET TRACE_LONG_RUN_CURSOR = 1 */
{
    sqlargs_t sqlargs;
#line 201 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"ALTER SESSION SET TRACE_LONG_RUN_CURSOR = 1;\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 68 "cursor_sleep.gc"
 if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("[ERROR] SQL ERROR -"); }
    /* EXEC SQL ALTER SESSION SET TRACE_LONG_RUN_SQL = 1 */
{
    sqlargs_t sqlargs;
#line 237 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"ALTER SESSION SET TRACE_LONG_RUN_SQL = 1;\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 69 "cursor_sleep.gc"
 if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("[ERROR] SQL ERROR -"); }

    /***********************************************
     * Retrieve employee
     **********************************************/
    gettimeofday( &startTimeA, NULL );
    /* EXEC SQL
        DECLARE EMP_CUR CURSOR FOR
        SELECT empno, ename, job, sal
        FROM   EMP 
        union  SELECT empno, ename, job, sal FROM   EMP  */
{
    sqlargs_t sqlargs;
#line 282 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 29;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"SELECT empno, ename, job, sal\n"
"        FROM   EMP \n"
"        union  SELECT empno, ename, job, sal FROM   EMP ;\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlcurprops_t sqlcurprops;
    sqlcursor_t   sqlcursor;
#line 315 "cursor_sleep.c"
    sqlcursor.sqlcurprops = &sqlcurprops;
    sqlargs.sqlcursor = &sqlcursor;
    sqlcursor.sqlcname = (char *)"EMP_CUR";
    sqlcursor.sqldynstmt = NULL;
    sqlcurprops.org_type = 2;
    sqlcurprops.cur_type = 1;
    sqlcurprops.sensitivity = 0;
    sqlcurprops.scrollability = 0;
    sqlcurprops.holdability = 0;
    sqlcurprops.updatability = 0;
    sqlcurprops.returnability = 0;
    DBESQL_DeclareCursor(NULL, &sqlargs);
}
#line 79 "cursor_sleep.gc"

    /* EXEC SQL OPEN EMP_CUR */
{
    sqlargs_t sqlargs;
#line 334 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 30;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlcursor_t   sqlcursor;
    sqlargs.sqlcursor = &sqlcursor;
    sqlcursor.sqlcname = (char *)"EMP_CUR";
    DBESQL_OpenCursor(NULL, &sqlargs);
}
#line 80 "cursor_sleep.gc"

    if(sqlca.sqlcode != 0)
    {
        PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
        goto fail_exit;
    }

    gettimeofday( &endTimeA, NULL );

    gettimeofday( &startTimeB, NULL );
 
    printf(" EMPNO    ENAME                JOB      SALARY\n");
    printf("====== ==================== ========== ========\n");

    while( 1 )
    {
        /* EXEC SQL
            FETCH EMP_CUR
            INTO  :sEmpNo, :sEName, :sJob, :sSalary */
{
    sqlargs_t sqlargs;
#line 389 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 32;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlfetch_t   sqlfetch;
    sqlfetch.sqlfph = 0;
    sqlfetch.sqlfpl = 0;
    sqlfetch.offsethv = NULL;
    sqlargs.sqlfetch = &sqlfetch;
    sqlfetch.sqlcname = (char *)"EMP_CUR";
    sqlfetch.sqlcv = NULL;
    sqlfetch.sqlfo = 0;
    sqlhv_t sqlhv[4];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 4;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(sEmpNo);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sEmpNo);
    sqlhv[0].value = (void *)&sEmpNo;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = 20 + 1;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sEName);
    sqlhv[1].value = (void *)&sEName;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 13;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = 20;
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sJob);
    sqlhv[2].value = (void *)sJob;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlhv[3].io_type = 1;
    sqlhv[3].data_type = 7;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(sSalary);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 0;
    sqlhv[3].el_size = sizeof(sSalary);
    sqlhv[3].value = (void *)&sSalary;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].buf_max = -1;
    DBESQL_FetchCursor(NULL, &sqlargs);
}
#line 98 "cursor_sleep.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            break;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }

        sRecordCount ++;
        usleep(5000);
        printf("%6d %20s %10s %8ld\n",
               sEmpNo, sEName.arr, sJob, sSalary);
    }

    printf("====== ==================== ========== ========\n");
    printf("Record Count = %d\n", sRecordCount);
    printf("====== ==================== ========== ========\n");

        //sleep(10);
    /* EXEC SQL CLOSE EMP_CUR */
{
    sqlargs_t sqlargs;
#line 505 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 31;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlcursor_t   sqlcursor;
    sqlargs.sqlcursor = &sqlcursor;
    sqlcursor.sqlcname = (char *)"EMP_CUR";
    sqlcursor.sqlcv = NULL;
    sqlcursor.sqlcurprops = NULL;
    DBESQL_CloseCursor(NULL, &sqlargs);
}
#line 121 "cursor_sleep.gc"

    if(sqlca.sqlcode != 0)
    {
        PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
        goto fail_exit;
    }
    gettimeofday( &endTimeB, NULL );

    CalTime(startTimeA,endTimeA, "exec time ");
    CalTime(startTimeB,endTimeB, "cursor time ");
    CalTime(startTimeA,endTimeB, "all time ");

    /* EXEC SQL COMMIT WORK RELEASE */
{
    sqlargs_t sqlargs;
#line 556 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 22;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 1, 1);
}
#line 133 "cursor_sleep.gc"

    if(sqlca.sqlcode != 0)
    {
        PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
        goto fail_exit;
    }

    printf("\n\nSUCCESS\n");
    printf("############################\n");

    return 0;

  fail_exit:

    printf("\n\nFAILURE\n");
    printf("############################\n\n");

    /* EXEC SQL ROLLBACK WORK RELEASE */
{
    sqlargs_t sqlargs;
#line 607 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 23;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 0, 1);
}
#line 150 "cursor_sleep.gc"


    return 0;
}

int Connect(char *aHostInfo, char *aUserID, char *sPassword)
{
    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 157 "cursor_sleep.gc"

    /* VARCHAR  sUid[80]; */
    struct { int len; char arr[80]; } sUid;
#line 158 "cursor_sleep.gc"

    /* VARCHAR  sPwd[20]; */
    struct { int len; char arr[20]; } sPwd;
#line 159 "cursor_sleep.gc"

    /* VARCHAR  sConnStr[1024]; */
    struct { int len; char arr[1024]; } sConnStr;
#line 160 "cursor_sleep.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 161 "cursor_sleep.gc"


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
#line 678 "cursor_sleep.c"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.sqldesc   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.ipos       = 0;
    sqlargs.fpos       = 0;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 48;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Connect(NULL, &sqlargs, sConnStr.arr, sUid.arr, sPwd.arr);
}
#line 174 "cursor_sleep.gc"

    if(sqlca.sqlcode != 0)
    {
        goto fail_exit;
    }

    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] Connection Failure!");

    return FAILURE;
}


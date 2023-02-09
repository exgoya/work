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


#line __LINE__ "query.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/* EXEC SQL INCLUDE SQLCA; */
#include "sqlca.h"
#line 7 "query.gc"


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
//EXEC SQL BEGIN DECLARE SECTION;
//EXEC SQL INCLUDE query.hpp;
//EXEC SQL END DECLARE SECTION;

//#include "query.hpp"
int Connect(char *aHostInfo, char *aUserID, char *sPassword);
int Query1();
int Query2();
int Query3();
int Query4();
int Query5();
int Query6();
int Query7();
int Query8();

int run(); int i; int arr;// int crr;

int main(int argc, char **argv)
{
    if(argc != 3){
        printf("use >> ./query [array count] [query number]\n");
        exit(1);
    }
    printf("Connect GOLDILOCKS ...\n");
    if(Connect("DSN=GOLDILOCKS", "sys", "gliese") != SUCCESS)
    {
        goto fail_exit;
    }

    arr = atoi(argv[1]);
    int cNum = atoi(argv[2]);

    if(run(cNum) != SUCCESS)
    {
        goto fail_exit;
    }

    /* EXEC SQL DISCONNECT ALL */
{
    sqlargs_t sqlargs;
#line 79 "query.c"
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
    DBESQL_Disconnect(NULL, &sqlargs, NULL, 1);
}
#line 58 "query.gc"

    return 0;

  fail_exit:

    printf("FAILURE\n");
    printf("############################\n\n");

    /* EXEC SQL DISCONNECT ALL */
{
    sqlargs_t sqlargs;
#line 120 "query.c"
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
    DBESQL_Disconnect(NULL, &sqlargs, NULL, 1);
}
#line 66 "query.gc"


    return 0;
}

int run(int cNum){
    struct timeval start,end,diff;
    int sPrevArr = arr;

    arr = 1;
//    switch(cNum){
//        case 1  : if(Query1()   != SUCCESS){ goto fail_exit; } break;
//        case 2  : if(Query2()   != SUCCESS){ goto fail_exit; } break;
//        case 3  : if(Query3()   != SUCCESS){ goto fail_exit; } break;
//        case 4  : if(Query4()   != SUCCESS){ goto fail_exit; } break;
//        case 5  : if(Query5()   != SUCCESS){ goto fail_exit; } break;
//        case 6  : if(Query6()   != SUCCESS){ goto fail_exit; } break;
//        case 7  : if(Query7()   != SUCCESS){ goto fail_exit; } break;
//        case 8  : if(Query8()   != SUCCESS){ goto fail_exit; } break;
//
//        default : printf("no parameter.."); goto fail_exit;
//    }
 
    arr = sPrevArr;
    gettimeofday(&start,NULL);

    //if(Query(cNum) != SUCCESS){ goto fail_exit; } break;
    switch(cNum){
        case 1  : if(Query1()   != SUCCESS){ goto fail_exit; } break;
        case 2  : if(Query2()   != SUCCESS){ goto fail_exit; } break;
        case 3  : if(Query3()   != SUCCESS){ goto fail_exit; } break;
        case 4  : if(Query4()   != SUCCESS){ goto fail_exit; } break;
        case 5  : if(Query5()   != SUCCESS){ goto fail_exit; } break;
        case 6  : if(Query6()   != SUCCESS){ goto fail_exit; } break;
        case 7  : if(Query7()   != SUCCESS){ goto fail_exit; } break;
        case 8  : if(Query8()   != SUCCESS){ goto fail_exit; } break;
        
        default : printf("no parameter.."); goto fail_exit;
    }
            
    gettimeofday(&end,NULL);

    diff.tv_sec=end.tv_sec-start.tv_sec;
    if( end.tv_usec > start.tv_usec )
    {
        diff.tv_usec=end.tv_usec-start.tv_usec;
    }
    else
    {
        diff.tv_usec=1000000 + end.tv_usec - start.tv_usec;
        diff.tv_sec--;
    }

    double ell = diff.tv_sec*1000000 + diff.tv_usec;
    double tps = arr/(ell/1000000);
    printf("SUCCESS\n");
    printf("############################################\n");
    printf("    SUCCESS        :   %d\n",i);
    printf("    SUM USEC       :   %lf us\n",ell);
    printf("    AVG USEC       :   %lf us\n",ell/i);
    printf("    TPS            :   %0.2lf TPS\n",tps);
    printf("############################################\n");
   
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] Run Function FAILURE!");
    return FAILURE;

}


int Connect(char *aHostInfo, char *aUserID, char *sPassword)
{
    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 141 "query.gc"

    /* VARCHAR  sUid[80]; */
    struct { int len; char arr[80]; } sUid;
#line 142 "query.gc"

    /* VARCHAR  sPwd[20]; */
    struct { int len; char arr[20]; } sPwd;
#line 143 "query.gc"

    /* VARCHAR  sConnStr[1024]; */
    struct { int len; char arr[1024]; } sConnStr;
#line 144 "query.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 145 "query.gc"


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
#line 258 "query.c"
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
#line 158 "query.gc"

    if(sqlca.sqlcode != 0)
    {
        goto fail_exit;
    }

    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] Connection Failure!");

    return FAILURE;
}
int Query1(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 174 "query.gc"

        int             dbintSno       ; 
        /* VARCHAR         dbstrSname     [10+1]; */
        struct { int len; char arr[10+1]; } dbstrSname;
#line 176 "query.gc"

        int             dbintUseAmt;
        /* TIMESTAMP       dbDate; */
        SQL_TIMESTAMP_STRUCT dbDate;
#line 178 "query.gc"

        /* VARCHAR         dbstrText [100+1]; */
        struct { int len; char arr[100+1]; } dbstrText;
#line 179 "query.gc"

        /* VARCHAR         xxno[100+1]; */
        struct { int len; char arr[100+1]; } xxno;
#line 180 "query.gc"

        int         xno=0;
    /* EXEC SQL END DECLARE SECTION; */
#line 182 "query.gc"


//xxno=0;
    strcpy((char *)xxno.arr, "0");
    xxno.len = (short)strlen((char *)xxno.arr);
    //char origin[] = "0";

    //strcpy(xxno, origin);

    for(i=0;i < arr;i++){

        /* EXEC SQL
            SELECT *
            INTO :dbintSno   ,     
                 :dbstrSname ,     
                 :dbintUseAmt,
                 :dbDate     ,         
                 :dbstrText 
            FROM INSERT_DATA_TEST_1
            order by sno desc
            limit 1  */
{
    sqlargs_t sqlargs;
#line 351 "query.c"
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
    sqlargs.sqlstmt = (char *)"SELECT *\n"
"            INTO :dbintSno   ,     \n"
"                 :dbstrSname ,     \n"
"                 :dbintUseAmt,\n"
"                 :dbDate     ,         \n"
"                 :dbstrText \n"
"            FROM INSERT_DATA_TEST_1\n"
"            order by sno desc\n"
"            limit 1\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[5];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 5;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(dbintSno);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbintSno);
    sqlhv[0].value = (void *)&dbintSno;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = 10+1;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstrSname);
    sqlhv[1].value = (void *)&dbstrSname;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 5;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(dbintUseAmt);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(dbintUseAmt);
    sqlhv[2].value = (void *)&dbintUseAmt;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlhv[3].io_type = 1;
    sqlhv[3].data_type = 23;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(dbDate);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 6;
    sqlhv[3].el_size = sizeof(dbDate);
    sqlhv[3].value = (void *)&dbDate;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].buf_max = -1;
    sqlhv[4].io_type = 1;
    sqlhv[4].data_type = 14;
    sqlhv[4].arr_size = 0;
    sqlhv[4].buflen = 100+1;
    sqlhv[4].precision = 0;
    sqlhv[4].scale = 0;
    sqlhv[4].el_size = sizeof(dbstrText);
    sqlhv[4].value = (void *)&dbstrText;
    sqlhv[4].ind_type = -1;
    sqlhv[4].ind_el_size = 0;
    sqlhv[4].indicator = NULL;
    sqlhv[4].buf_max = -1;
    sqlargs.ipos = 21;
    sqlargs.fpos = 193;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 202 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            printf( "NO DATA.\n" );
            goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }

    }
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}

int Query2(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 226 "query.gc"

        int             dbintSno       ; 
        /* VARCHAR         dbstrSname     [10+1]; */
        struct { int len; char arr[10+1]; } dbstrSname;
#line 228 "query.gc"

        int             dbintUseAmt;
        /* TIMESTAMP       dbDate; */
        SQL_TIMESTAMP_STRUCT dbDate;
#line 230 "query.gc"

        /* VARCHAR         dbstrText [100+1]; */
        struct { int len; char arr[100+1]; } dbstrText;
#line 231 "query.gc"

        /* VARCHAR         xxno[100+1]; */
        struct { int len; char arr[100+1]; } xxno;
#line 232 "query.gc"

        int         xno=0;
    /* EXEC SQL END DECLARE SECTION; */
#line 234 "query.gc"


//xxno=0;
    strcpy((char *)xxno.arr, "0");
    xxno.len = (short)strlen((char *)xxno.arr);
    //char origin[] = "0";

    //strcpy(xxno, origin);

    for(i=0;i < arr;i++){

        /* EXEC SQL
            SELECT *
            INTO :dbintSno   ,     
                 :dbstrSname ,     
                 :dbintUseAmt,
                 :dbDate     ,         
                 :dbstrText 
            FROM (
                select * from 
                INSERT_DATA_TEST_1
                order by sno desc
            )
            where rownum = 1
             */
{
    sqlargs_t sqlargs;
#line 530 "query.c"
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
    sqlargs.sqltype = 1;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"SELECT *\n"
"            INTO :dbintSno   ,     \n"
"                 :dbstrSname ,     \n"
"                 :dbintUseAmt,\n"
"                 :dbDate     ,         \n"
"                 :dbstrText \n"
"            FROM (\n"
"                select * from \n"
"                INSERT_DATA_TEST_1\n"
"                order by sno desc\n"
"            )\n"
"            where rownum = 1\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[5];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 5;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(dbintSno);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbintSno);
    sqlhv[0].value = (void *)&dbintSno;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = 10+1;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstrSname);
    sqlhv[1].value = (void *)&dbstrSname;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 5;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(dbintUseAmt);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(dbintUseAmt);
    sqlhv[2].value = (void *)&dbintUseAmt;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlhv[3].io_type = 1;
    sqlhv[3].data_type = 23;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(dbDate);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 6;
    sqlhv[3].el_size = sizeof(dbDate);
    sqlhv[3].value = (void *)&dbDate;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].buf_max = -1;
    sqlhv[4].io_type = 1;
    sqlhv[4].data_type = 14;
    sqlhv[4].arr_size = 0;
    sqlhv[4].buflen = 100+1;
    sqlhv[4].precision = 0;
    sqlhv[4].scale = 0;
    sqlhv[4].el_size = sizeof(dbstrText);
    sqlhv[4].value = (void *)&dbstrText;
    sqlhv[4].ind_type = -1;
    sqlhv[4].ind_el_size = 0;
    sqlhv[4].indicator = NULL;
    sqlhv[4].buf_max = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 258 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            printf( "NO DATA.\n" );
            goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }

    }
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}



int Query3(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 284 "query.gc"

        int             dbintSno       ; 
        /* VARCHAR         dbstrSname     [10+1]; */
        struct { int len; char arr[10+1]; } dbstrSname;
#line 286 "query.gc"

        int             dbintUseAmt;
        /* TIMESTAMP       dbDate; */
        SQL_TIMESTAMP_STRUCT dbDate;
#line 288 "query.gc"

        /* VARCHAR         dbstrText [100+1]; */
        struct { int len; char arr[100+1]; } dbstrText;
#line 289 "query.gc"

        /* VARCHAR         xxno[100+1]; */
        struct { int len; char arr[100+1]; } xxno;
#line 290 "query.gc"

        int         xno=0;
    /* EXEC SQL END DECLARE SECTION; */
#line 292 "query.gc"


//xxno=0;
    strcpy((char *)xxno.arr, "0");
    xxno.len = (short)strlen((char *)xxno.arr);
    //char origin[] = "0";

    //strcpy(xxno, origin);

    for(i=0;i < arr;i++){

        /* EXEC SQL UPDATE DEDUCTION 
            SET (USE_AMT, SNAME, MOD_DATE) = (10+1, 10, SYSTIMESTAMP) WHERE SNO = 99 */
{
    sqlargs_t sqlargs;
#line 700 "query.c"
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
    sqlargs.sqltype = 8;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"UPDATE DEDUCTION \n"
"            SET (USE_AMT, SNAME, MOD_DATE) = (10+1, 10, SYSTIMESTAMP) WHERE SNO = 99\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 304 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            printf( "NO DATA.\n" );
            goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }
        /* EXEC SQL COMMIT WORK */
{
    sqlargs_t sqlargs;
#line 747 "query.c"
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
    DBESQL_EndTran(NULL, &sqlargs, 1, 0);
}
#line 316 "query.gc"

        if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }
    }
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}

int Query4(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 333 "query.gc"

        int             dbintSno       ; 
        /* VARCHAR         dbstrSname     [100+1]; */
        struct { int len; char arr[100+1]; } dbstrSname;
#line 335 "query.gc"

        int         xno=0;
    /* EXEC SQL END DECLARE SECTION; */
#line 337 "query.gc"


//xxno=0;
    //char origin[] = "0";
    //strcpy(xxno, origin);

    for(i=0;i < arr;i++){

        /* EXEC SQL
            select * 
            INTO :dbintSno   ,     
                 :dbstrSname 
            from in_test where c2 in ('asdf','asdf','asde') limit 1
            */
{
    sqlargs_t sqlargs;
#line 821 "query.c"
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
    sqlargs.sqlstmt = (char *)"select * \n"
"            INTO :dbintSno   ,     \n"
"                 :dbstrSname \n"
"            from in_test where c2 in ('asdf','asdf','asde') limit 1\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[2];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 2;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(dbintSno);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbintSno);
    sqlhv[0].value = (void *)&dbintSno;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = 100+1;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstrSname);
    sqlhv[1].value = (void *)&dbstrSname;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlargs.ipos = 22;
    sqlargs.fpos = 88;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 350 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            //printf( "NO DATA.\n" );
            //goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }

    }
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}




int Query5(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 377 "query.gc"

        int             dbintSno       ; 
        /* VARCHAR         dbstrSname     [100+1]; */
        struct { int len; char arr[100+1]; } dbstrSname;
#line 379 "query.gc"

        int         xno=0;
    /* EXEC SQL END DECLARE SECTION; */
#line 381 "query.gc"


//xxno=0;
    //char origin[] = "0";
    //strcpy(xxno, origin);

    for(i=0;i < arr;i++){

        /* EXEC SQL
            select * 
            INTO :dbintSno   ,     
                 :dbstrSname 
            from in_test where instr('asdfasdfadienalsdkflnasdf',c2) >=1 limit 1 */
{
    sqlargs_t sqlargs;
#line 937 "query.c"
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
    sqlargs.sqlstmt = (char *)"select * \n"
"            INTO :dbintSno   ,     \n"
"                 :dbstrSname \n"
"            from in_test where instr('asdfasdfadienalsdkflnasdf',c2) >=1 limit 1\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[2];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 2;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(dbintSno);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbintSno);
    sqlhv[0].value = (void *)&dbintSno;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = 100+1;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstrSname);
    sqlhv[1].value = (void *)&dbstrSname;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlargs.ipos = 22;
    sqlargs.fpos = 88;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 393 "query.gc"

           ;

        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            //printf( "NO DATA.\n" );
            //goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }

    }
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}

int Query6(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 418 "query.gc"

        /* LONGVARCHAR         dbstr1; */
        SQL_LONG_VARIABLE_LENGTH_STRUCT dbstr1;
#line 419 "query.gc"

        /* LONGVARCHAR         dbstr2; */
        SQL_LONG_VARIABLE_LENGTH_STRUCT dbstr2;
#line 420 "query.gc"

        /* LONGVARCHAR         dbstr3; */
        SQL_LONG_VARIABLE_LENGTH_STRUCT dbstr3;
#line 421 "query.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 422 "query.gc"


    dbstr1.arr = malloc(1048576);
    dbstr2.arr = malloc(1048576);
    dbstr3.arr = malloc(1048576);
 
    for(i=0;i < arr;i++){
    dbstr1.len = 10000;
    dbstr2.len = 10000;
    dbstr3.len = 10000;


        /* EXEC SQL
        SELECT
            IN_HTTP_PAYLOAD
            ,OUT_HTTP_PAYLOAD
            ,SMF_OUT_HTTP_PAYLOAD
            INTO
            :dbstr1,:dbstr2,:dbstr3
            FROM    T_AF_SESSION_INFO_TEST A
            WHERE
//            A.SM_POLICY_ID = '03010303000-01-166606059501310434053507370535043611'
            A.SM_POLICY_ID = 'asdf'
            ORDER BY A.CREATE_TIME DESC     */
{
    sqlargs_t sqlargs;
#line 1068 "query.c"
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
    sqlargs.sqlstmt = (char *)"SELECT\n"
"            IN_HTTP_PAYLOAD\n"
"            ,OUT_HTTP_PAYLOAD\n"
"            ,SMF_OUT_HTTP_PAYLOAD\n"
"            INTO\n"
"            :dbstr1,:dbstr2,:dbstr3\n"
"            FROM    T_AF_SESSION_INFO_TEST A\n"
"            WHERE\n"
"//            A.SM_POLICY_ID = '03010303000-01-166606059501310434053507370535043611'\n"
"            A.SM_POLICY_ID = 'asdf'\n"
"            ORDER BY A.CREATE_TIME DESC\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[3];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 3;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 15;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(dbstr1);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbstr1);
    sqlhv[0].value = (void *)&dbstr1;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 15;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(dbstr2);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstr2);
    sqlhv[1].value = (void *)&dbstr2;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 15;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(dbstr3);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(dbstr3);
    sqlhv[2].value = (void *)&dbstr3;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlargs.ipos = 111;
    sqlargs.fpos = 164;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 445 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            //printf( "NO DATA.\n" );
            //goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }
        }
        free( dbstr1.arr );
        free( dbstr2.arr );
        free( dbstr3.arr );



    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}


int Query7(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 475 "query.gc"

        /* LONGVARCHAR         dbstr1; */
        SQL_LONG_VARIABLE_LENGTH_STRUCT dbstr1;
#line 476 "query.gc"

        /* LONGVARCHAR         dbstr2; */
        SQL_LONG_VARIABLE_LENGTH_STRUCT dbstr2;
#line 477 "query.gc"

        /* LONGVARCHAR         dbstr3; */
        SQL_LONG_VARIABLE_LENGTH_STRUCT dbstr3;
#line 478 "query.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 479 "query.gc"


    dbstr1.arr = malloc(1048576);
    dbstr2.arr = malloc(1048576);
    dbstr3.arr = malloc(1048576);
 
    for(i=0;i < arr;i++){
    dbstr1.len = 10000;
    dbstr2.len = 10000;
    dbstr3.len = 10000;


        /* EXEC SQL
        SELECT
            IN_HTTP_PAYLOAD
            ,OUT_HTTP_PAYLOAD
            ,SMF_OUT_HTTP_PAYLOAD
            INTO
            :dbstr1,:dbstr2,:dbstr3
            FROM    T_AF_SESSION_INFO A
            WHERE
//            A.SM_POLICY_ID = '03010303000-01-166606059501310434053507370535043611'
            A.SM_POLICY_ID = 'asdf'
            ORDER BY A.CREATE_TIME DESC     */
{
    sqlargs_t sqlargs;
#line 1223 "query.c"
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
    sqlargs.sqlstmt = (char *)"SELECT\n"
"            IN_HTTP_PAYLOAD\n"
"            ,OUT_HTTP_PAYLOAD\n"
"            ,SMF_OUT_HTTP_PAYLOAD\n"
"            INTO\n"
"            :dbstr1,:dbstr2,:dbstr3\n"
"            FROM    T_AF_SESSION_INFO A\n"
"            WHERE\n"
"//            A.SM_POLICY_ID = '03010303000-01-166606059501310434053507370535043611'\n"
"            A.SM_POLICY_ID = 'asdf'\n"
"            ORDER BY A.CREATE_TIME DESC\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[3];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 3;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 15;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(dbstr1);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbstr1);
    sqlhv[0].value = (void *)&dbstr1;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 15;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(dbstr2);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstr2);
    sqlhv[1].value = (void *)&dbstr2;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 15;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(dbstr3);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(dbstr3);
    sqlhv[2].value = (void *)&dbstr3;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlargs.ipos = 111;
    sqlargs.fpos = 164;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 502 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            //printf( "NO DATA.\n" );
            //goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }
        }
        free( dbstr1.arr );
        free( dbstr2.arr );
        free( dbstr3.arr );



    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}


int Query8(){

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 532 "query.gc"

        /* VARCHAR         dbstr1[100]; */
        struct { int len; char arr[100]; } dbstr1;
#line 533 "query.gc"

        /* VARCHAR         dbstr2[100]; */
        struct { int len; char arr[100]; } dbstr2;
#line 534 "query.gc"

        /* VARCHAR         dbstr3[100]; */
        struct { int len; char arr[100]; } dbstr3;
#line 535 "query.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 536 "query.gc"

 
    for(i=0;i < arr;i++){

        /* EXEC SQL
        SELECT
            ASC_ID 
            ,SM_POLICY_ID
            ,SUPI
            INTO
            :dbstr1,:dbstr2,:dbstr3
            FROM    T_AF_SESSION_INFO A
            WHERE
//            A.SM_POLICY_ID = '03010303000-01-166606059501310434053507370535043611'
            A.SM_POLICY_ID = 'asdf'
            ORDER BY A.CREATE_TIME DESC     */
{
    sqlargs_t sqlargs;
#line 1370 "query.c"
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
    sqlargs.sqlstmt = (char *)"SELECT\n"
"            ASC_ID \n"
"            ,SM_POLICY_ID\n"
"            ,SUPI\n"
"            INTO\n"
"            :dbstr1,:dbstr2,:dbstr3\n"
"            FROM    T_AF_SESSION_INFO A\n"
"            WHERE\n"
"//            A.SM_POLICY_ID = '03010303000-01-166606059501310434053507370535043611'\n"
"            A.SM_POLICY_ID = 'asdf'\n"
"            ORDER BY A.CREATE_TIME DESC\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[3];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 3;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 14;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = 100;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(dbstr1);
    sqlhv[0].value = (void *)&dbstr1;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 14;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = 100;
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(dbstr2);
    sqlhv[1].value = (void *)&dbstr2;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 14;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = 100;
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(dbstr3);
    sqlhv[2].value = (void *)&dbstr3;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    sqlargs.ipos = 83;
    sqlargs.fpos = 136;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 551 "query.gc"


        if(sqlca.sqlcode == SQL_NO_DATA)
        {
            //printf( "NO DATA.\n" );
            //goto fail_exit;
        }
        else if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("[ERROR] SQL ERROR -");
            goto fail_exit;
        }
        }
    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR("[ERROR] QUERY1 FAILURE!");
    return FAILURE;  
}



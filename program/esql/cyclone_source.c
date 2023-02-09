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


#line __LINE__ "cyclone_source.c"
/*
 * cyclone_source.gc 
 * dml 작업 수행
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/* EXEC SQL INCLUDE SQLCA; */
#include "sqlca.h"
#line 15 "cyclone_source.gc"


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

//CREATE TABLE DEDUCTION
//(
// SNO NUMBER PRIMARY KEY
//,SNAME VARCHAR(10)
//,USE_AMT NUMBER
//,MOD_DATE TIMESTAMP
//)
//SHARDING BY HASH(SNO)

int Connect(char *aHostInfo, char *aUserID, char *sPassword);
int RunProc(int arrCount, int exeCount, int procNo);
int RunReset();

int main(int argc, char **argv)
{
    int arrCount=0;
    int exeCount=0;
    int N = 0;
     
    if(argc == 4){
        arrCount = atoi(argv[1]);
        exeCount = atoi(argv[2]);
        N = atoi(argv[3]);
    }else{
        printf("argument error..\n");
        printf("use >> ./cyclone_source [commit array count] [execution count] [process count]\n");
        exit(0);
    }

    pid_t pid[N]; /* process id */
    int childStatus;
    int i;

    RunReset();
    for (i = 0; i < N; i++)
    {
        pid[i] = fork();
            //usleep(50000);

        if (pid[i] == 0)
        {

            //child work area
            printf("Now pid[%d] start work\n",i);

            RunProc(arrCount,exeCount,i*arrCount*1000);

            printf("Now pid[%d] is die\n",i);
            exit(100+i);
        }
        // Create multiple child processes
    }

    for (i = 0; i < N; i++)
    {
        pid_t terminatedChild = wait(&childStatus);

        if (WIFEXITED(childStatus))
        {
            // The child process has termindated normally

            printf("Child %d has terminated with exit status %d\n", terminatedChild, WEXITSTATUS(childStatus));
        }

        else
            printf("Child %d has terminated abnormally\n", terminatedChild);
    }  
    return 0;
}

int RunReset(){

    printf("Connect GOLDILOCKS ...\n");
    if(Connect("DSN=GOLDILOCKS", "sys", "gliese") != SUCCESS)
    {
        goto fail_exit;
    }
    //초기화
    /* EXEC SQL UPDATE DEDUCTION SET USE_AMT=0 */
{
    sqlargs_t sqlargs;
#line 128 "cyclone_source.c"
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
    sqlargs.sqlstmt = (char *)"UPDATE DEDUCTION SET USE_AMT=0\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 107 "cyclone_source.gc"

        if(sqlca.sqlcode == SQL_NO_DATA) { printf( "No data.\n" ); }
        else if(sqlca.sqlcode != 0) { PRINT_SQL_ERROR("1 [ERROR] SQL ERROR -"); goto fail_exit; }

    /* EXEC SQL COMMIT WORK RELEASE */
{
    sqlargs_t sqlargs;
#line 166 "cyclone_source.c"
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
#line 111 "cyclone_source.gc"

    if(sqlca.sqlcode != 0)
    {
        PRINT_SQL_ERROR("2 [ERROR] SQL ERROR -");
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
#line 217 "cyclone_source.c"
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
#line 129 "cyclone_source.gc"


    return 0;
}

int RunProc(int arrCount, int exeCount, int procNo){
    //printf("%d, %d, %d \n",arrCount, exeCount, procNo);
    struct timeval startTime, endTime, gepTime;

    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 138 "cyclone_source.gc"

    int          sNo=0;
    int          cNo=0;
    int          sAmt=0;
    /* EXEC SQL END DECLARE SECTION; */
#line 142 "cyclone_source.gc"


    printf("Connect GOLDILOCKS ...\n");
    if(Connect("DSN=GOLDILOCKS", "sys", "gliese") != SUCCESS)
    {
        goto fail_exit;
    }

    int i;
    int mi;
    for(mi=0; mi < exeCount; mi++){
        cNo = mi;
        //start time
        gettimeofday( &startTime, NULL );

printf( "%d , %d llll \n" , procNo, procNo+arrCount);
        for (i = procNo; i < procNo+arrCount; i++){
            sNo = i;
            //printf("%d\n",i);
            /* EXEC SQL SELECT USE_AMT INTO :sAmt FROM DEDUCTION WHERE SNO = :sNo FOR UPDATE NOWAIT */
{
    sqlargs_t sqlargs;
#line 286 "cyclone_source.c"
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
    sqlargs.sqlstmt = (char *)"SELECT USE_AMT INTO :sAmt FROM DEDUCTION WHERE SNO = :sNo FOR UPDATE NOWAIT\n"
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
    sqlhv[0].buflen = sizeof(sAmt);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sAmt);
    sqlhv[0].value = (void *)&sAmt;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 5;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sNo);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sNo);
    sqlhv[1].value = (void *)&sNo;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlargs.ipos = 15;
    sqlargs.fpos = 26;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 161 "cyclone_source.gc"

            if(sqlca.sqlcode == SQL_NO_DATA) { 
                //printf( "No data.\n" ); 
                /* EXEC SQL INSERT INTO DEDUCTION VALUES (:sNo, :cNo , 0, SYSTIMESTAMP) */
{
    sqlargs_t sqlargs;
#line 352 "cyclone_source.c"
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
    sqlargs.sqltype = 6;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"INSERT INTO DEDUCTION VALUES (:sNo, :cNo , 0, SYSTIMESTAMP)\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[2];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 2;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(sNo);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sNo);
    sqlhv[0].value = (void *)&sNo;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 5;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(cNo);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(cNo);
    sqlhv[1].value = (void *)&cNo;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 164 "cyclone_source.gc"

                if(sqlca.sqlcode != 0) { 
                    PRINT_SQL_ERROR("3 [ERROR] SQL ERROR -");
                    goto fail_exit; 
                } else if(sqlca.sqlcode == -19068) { PRINT_SQL_ERROR("4 [ERROR] SQL ERROR -"); mi--; break;}
                //printf( "Insert ok.\n" ); 
            } else if(sqlca.sqlcode == 0) {
                /* EXEC SQL UPDATE DEDUCTION SET (USE_AMT, SNAME, MOD_DATE) = (:sAmt+1, :cNo, SYSTIMESTAMP) WHERE SNO = :sNo */
{
    sqlargs_t sqlargs;
#line 420 "cyclone_source.c"
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
    sqlargs.sqlstmt = (char *)"UPDATE DEDUCTION SET (USE_AMT, SNAME, MOD_DATE) = (:sAmt+1, :cNo, SYSTIMESTAMP) WHERE SNO = :sNo\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.cumulative = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[3];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 3;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 5;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(sAmt);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sAmt);
    sqlhv[0].value = (void *)&sAmt;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].buf_max = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 5;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(cNo);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(cNo);
    sqlhv[1].value = (void *)&cNo;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].buf_max = -1;
    sqlhv[2].io_type = 0;
    sqlhv[2].data_type = 5;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(sNo);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sNo);
    sqlhv[2].value = (void *)&sNo;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].buf_max = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 171 "cyclone_source.gc"

                if(sqlca.sqlcode != 0) { 
                    PRINT_SQL_ERROR("5 [ERROR] SQL ERROR -"); 
                    goto fail_exit; 
                } else if(sqlca.sqlcode == -19068) { PRINT_SQL_ERROR("6 [ERROR] SQL ERROR -"); mi--; break;}
            } else if(sqlca.sqlcode == -19068) { PRINT_SQL_ERROR("7 [ERROR] SQL ERROR -"); mi--; break;} 
            else { 
                PRINT_SQL_ERROR("8 [ERROR] SQL ERROR -") goto fail_exit; 
            }
         /* EXEC SQL COMMIT WORK */
{
    sqlargs_t sqlargs;
#line 502 "cyclone_source.c"
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
#line 180 "cyclone_source.gc"

        if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("9 [ERROR] SQL ERROR -");
            goto fail_exit;
        } else if(sqlca.sqlcode == -19068) { PRINT_SQL_ERROR("10 [ERROR] SQL ERROR -"); mi--; break;}


        }

        /* EXEC SQL COMMIT WORK */
{
    sqlargs_t sqlargs;
#line 545 "cyclone_source.c"
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
#line 190 "cyclone_source.gc"

        if(sqlca.sqlcode != 0)
        {
            PRINT_SQL_ERROR("9 [ERROR] SQL ERROR -");
            goto fail_exit;
        } else if(sqlca.sqlcode == -19068) { PRINT_SQL_ERROR("10 [ERROR] SQL ERROR -"); mi--; break;}

        //end time
        gettimeofday( &endTime, NULL );

        gepTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
        gepTime.tv_usec = endTime.tv_usec - startTime.tv_usec;

        if ( gepTime.tv_usec < 0 )
        {
        gepTime.tv_sec = gepTime.tv_sec - 1;
        gepTime.tv_usec = gepTime.tv_usec + 1000000;
        }
    if (cNo % 1000 == 0){
        printf("commit number: %d,ellapsed time [%02ld.%02ld] second\n",cNo, gepTime.tv_sec, gepTime.tv_usec);
        }
            
    }

    /* EXEC SQL COMMIT WORK RELEASE */
{
    sqlargs_t sqlargs;
#line 602 "cyclone_source.c"
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
#line 214 "cyclone_source.gc"

    if(sqlca.sqlcode != 0)
    {
        PRINT_SQL_ERROR("11 [ERROR] SQL ERROR -");
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
#line 652 "cyclone_source.c"
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
#line 231 "cyclone_source.gc"


    return 0;
}

int Connect(char *aHostInfo, char *aUserID, char *sPassword)
{
    /* EXEC SQL BEGIN DECLARE SECTION; */
#line 238 "cyclone_source.gc"

    /* VARCHAR  sUid[80]; */
    struct { int len; char arr[80]; } sUid;
#line 239 "cyclone_source.gc"

    /* VARCHAR  sPwd[20]; */
    struct { int len; char arr[20]; } sPwd;
#line 240 "cyclone_source.gc"

    /* VARCHAR  sConnStr[1024]; */
    struct { int len; char arr[1024]; } sConnStr;
#line 241 "cyclone_source.gc"

    /* EXEC SQL END DECLARE SECTION; */
#line 242 "cyclone_source.gc"


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
#line 722 "cyclone_source.c"
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
#line 255 "cyclone_source.gc"

    if(sqlca.sqlcode != 0)
    {
        goto fail_exit;
    }

    return SUCCESS;

  fail_exit:

    PRINT_SQL_ERROR(" 12 [ERROR] Connection Failure!");

    return FAILURE;
}


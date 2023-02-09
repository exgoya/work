#ifndef __DBM_ERR_CODE_H_
#define __DBM_ERR_CODE_H_ 1

#define    DBM_ERRCODE_ERROR                        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 0 )
#define    DBM_ERRCODE_INVALID_ARGS                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 1 )
#define    DBM_ERRCODE_MEMORY_NOT_SUFFICIENT        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 2 )
#define    DBM_ERRCODE_FAIL_TO_ALLOC_MEMORY         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 3 )
#define    DBM_ERRCODE_NOT_IMPL                     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 4 )
#define    DBM_ERRCODE_ALREADY_SHM_EXIST            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 5 )
#define    DBM_ERRCODE_CREATE_SHM_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 6 )
#define    DBM_ERRCODE_INIT_SHM_FAIL                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 7 )
#define    DBM_ERRCODE_ATTACH_SHM_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 8 )
#define    DBM_ERRCODE_SHM_OPEN_FAIL                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 9 )
#define    DBM_ERRCODE_SHM_FSTAT_FAIL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 10 )
#define    DBM_ERRCODE_SHM_INVALID_SIZE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 11 )
#define    DBM_ERRCODE_MMAP_FAIL                    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 12 )
#define    DBM_ERRCODE_DETACH_SHM_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 13 )
#define    DBM_ERRCODE_DROP_FAIL                    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 14 )
#define    DBM_ERRCODE_CREATE_SHM_DIR_FAIL          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 15 )
#define    DBM_ERRCODE_INVALID_SLOT_NO              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 16 )
#define    DBM_ERRCODE_NO_EXIST_DIC                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 17 )
#define    DBM_ERRCODE_NOT_DEF_INSTANCE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 18 )
#define    DBM_ERRCODE_NOT_EXIST_TABLE              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 19 )
#define    DBM_ERRCODE_NOT_EXIST_COLUMN             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 20 )
#define    DBM_ERRCODE_MAX_SEGMENT                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 21 )
#define    DBM_ERRCODE_NO_SPACE                     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 22 )
#define    DBM_ERRCODE_CONNECT_FAIL                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 23 )
#define    DBM_ERRCODE_SEND_FAIL                    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 24 )
#define    DBM_ERRCODE_RECV_FAIL                    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 25 )
#define    DBM_ERRCODE_HB_FAIL                      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 26 )


#define    DBM_ERRCODE_INIT_HANDLE_FAIL             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 27 )
#define    DBM_ERRCODE_ALLOC_HANDLE_FAIL            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 28 )
#define    DBM_ERRCODE_NEED_VALUE_NULL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 29 )
#define    DBM_ERRCODE_FREE_HANDLE_FAIL             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 30 )
#define    DBM_ERRCODE_ALLOC_STMT_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 31 )
#define    DBM_ERRCODE_INIT_PARSE_CTX_FAIL          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 32 )
#define    DBM_ERRCODE_EXECUTE_FAIL                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 33 )
#define    DBM_ERRCODE_INVALID_STMT_TYPE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 34 )
#define    DBM_ERRCODE_INVALID_PLAN_TYPE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 35 )
#define    DBM_ERRCODE_INVALID_DATA_TYPE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 36 )
#define    DBM_ERRCODE_INVALID_TABLE_SIZE_OPTION    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 37 )
#define    DBM_ERRCODE_PREPARE_FAIL                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 38 )
#define    DBM_ERRCODE_FREE_STMT_FAIL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 39 )
#define    DBM_ERRCODE_INVALID_EXPR_TYPE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 40 )
#define    DBM_ERRCODE_ALLOC_MEM_FAIL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 41 )
#define    DBM_ERRCODE_INVALID_BUILT_FUNC           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 42 )
#define    DBM_ERRCODE_INVALID_SEGMENT              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 43 )
#define    DBM_ERRCODE_ALLOC_TRANS_FAIL             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 44 )
#define    DBM_ERRCODE_DATA_COUNT_MISMATCH          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 45 )
#define    DBM_ERRCODE_INVALID_COLUMN               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 46 )
#define    DBM_ERRCODE_INVALID_EXPR                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 47 )
#define    DBM_ERRCODE_CONVERT_DATA_FAIL            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 48 )
#define    DBM_ERRCODE_BINDING_COL_FAIL             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 49 )
#define    DBM_ERRCODE_CONVERT_OVERFLOW             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 50 )
#define    DBM_ERRCODE_NO_MORE_DATA                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 51 )
#define    DBM_ERRCODE_DIVIDE_BY_ZERO               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 52 )
#define    DBM_ERRCODE_INVALID_GROUP_BY             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 53 )
#define    DBM_ERRCODE_NOT_EXIST_INDEX              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 54 )
#define    DBM_ERRCODE_KEY_DUPLICATED               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 55 )
#define    DBM_ERRCODE_INDEX_KEY_NOT_FOUND          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 56 )
#define    DBM_ERRCODE_INVALID_LOG_TYPE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 57 )
#define    DBM_ERRCODE_DUP_COLUMN_NAME              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 58 )
#define    DBM_ERRCODE_INVALID_DATA_SIZE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 59 )
#define    DBM_ERRCODE_CHANGE_SCN_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 60 )
#define    DBM_ERRCODE_INVALID_SCN                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 61 )
#define    DBM_ERRCODE_COMMIT_PROC_FAIL             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 62 )
#define    DBM_ERRCODE_ROLLBACK_PROC_FAIL           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 63 )
#define    DBM_ERRCODE_DUP_INDEX_KEY_COLUMN         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 64 )
#define    DBM_ERRCODE_DUP_COLUMN_DEFINED           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 65 )
#define    DBM_ERRCODE_OPEN_DISK_LOG_FAIL           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 66 )
#define    DBM_ERRCODE_LSEEK_DISK_LOG_FAIL          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 67 )
#define    DBM_ERRCODE_SWITCH_DISK_LOG_FAIL         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 68 )
#define    DBM_ERRCODE_WRITE_DISK_LOG_FAIL          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 69 )
#define    DBM_ERRCODE_FSYNC_DISK_LOG_FAIL          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 70 )
#define    DBM_ERRCODE_READ_DISK_LOG_FAIL           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 71 )
#define    DBM_ERRCODE_INVALID_DISK_LOG             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 72 )
#define    DBM_ERRCODE_INVALID_TABLE_TYPE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 73 )
#define    DBM_ERRCODE_NOT_ALLOWED_COLUMN           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 74 )
#define    DBM_ERRCODE_INVALID_INDEX_STAT           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 75 )
#define    DBM_ERRCODE_INVALID_TRY                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 76 )
#define    DBM_ERRCODE_INST_ALREADY_EXISTS          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 77 )
#define    DBM_ERRCODE_INDEX_ALREADY_EXISTS         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 78 )
#define    DBM_ERRCODE_ALREADY_EXISTS_TABLE         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 79 )
#define    DBM_ERRCODE_DEAD_LOCK_DETECT             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 80 )
#define    DBM_ERRCODE_TOO_LONG_NAME                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 81 )
#define    DBM_ERRCODE_INVALID_BIND_PARAM           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 82 )
#define    DBM_ERRCODE_MISMATCH_BIND_COL            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 83 )
#define    DBM_ERRCODE_NEED_DICT_HANDLE             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 84 )
#define    DBM_ERRCODE_NOT_EXISTS_INST              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 85 )
#define    DBM_ERRCODE_INVALID_KEY_DATA_TYPE        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 86 )
#define    DBM_ERRCODE_TIMEOUT                      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 87 )
#define    DBM_ERRCODE_NOT_ALLOWED_OPERATION        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 88 )
#define    DBM_ERRCODE_TOO_BIG_ROWSIZE              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 89 )
#define    DBM_ERRCODE_NEED_COMMIT_OR_ROLLBACK      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 90 )
#define    DBM_ERRCODE_TOO_BIG_TO_WRITE_LOG         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 91 )

#define    DBM_ERRCODE_FAIL_TO_PARSE                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 92 )
#define    DBM_ERRCODE_NEED_INDEX                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 93 )
#define    DBM_ERRCODE_INVALID_SEQ_OPTION           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 94 )
#define    DBM_ERRCODE_SEQUENCE_MAXVALUE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 95 )
#define    DBM_ERRCODE_SEQUENCE_NOT_DEF_CURRVAL     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 96 )
#define    DBM_ERRCODE_NOT_ENOUGH_BUFF              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 97 )
#define    DBM_ERRCODE_INVALID_LICENSE              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 98 )
#define    DBM_ERRCODE_INVALID_OFFSET               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 99 )
#define    DBM_ERRCODE_TOO_MANY_ROWS                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 100 )
#define    DBM_ERRCODE_CHECK_DIC_FAIL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 101 )
#define    DBM_ERRCODE_THREAD_FAIL                  DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 102 )
#define    DBM_ERRCODE_FILE_READ_FAIL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 103 )
#define    DBM_ERRCODE_FILE_WRITE_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 104 )
#define    DBM_ERRCODE_NOT_ACTIVE_INSTANCE          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 105 )
#define    DBM_ERRCODE_DIRECT_INVALID_KEY_DATA_TYPE DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 106 )
#define    DBM_ERRCODE_DIRECT_NEED_INDEX            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 107 )
#define    DBM_ERRCODE_FAIL_TO_PREPARE_DISK_LOG     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 108 )
#define    DBM_ERRCODE_FAIL_TO_PREPARE_REPL         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 109 )
#define    DBM_ERRCODE_FAIL_TO_PREPARE_TABLE        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 110 )
#define    DBM_ERRCODE_NOT_FOUND                    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 111 )
#define    DBM_ERRCODE_REPL_NOT_CONNECTED           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 112 )
#define    DBM_ERRCODE_TOO_MANY_RESULT              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 113 )
#define    DBM_ERRCODE_NOT_EXIST_PROC               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 114 )
#define    DBM_ERRCODE_ALREADY_EXIST_PROC           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 115 )
#define    DBM_ERRCODE_INVALID_IDENTIFIER           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 116 )
#define    DBM_ERRCODE_CASE_NOT_FOUND               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 117 )
#define    DBM_ERRCODE_CURSOR_ALREADY_OPENED        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 118 )
#define    DBM_ERRCODE_CURSOR_NOT_OPENED            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 119 )
#define    DBM_ERRCODE_EXCEPTION_DUPLICATED         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 120 )
#define    DBM_ERRCODE_RAISE_USER_EXCEPTION         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 121 )
#define    DBM_ERRCODE_UNHANDLE_EXCEPTION           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 122 )
#define    DBM_ERRCODE_PREPARE_PROCEDURE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 123 )
#define    DBM_ERRCODE_EXIT_ONLY_AT_LOOP            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 124 )
#define    DBM_ERRCODE_EXECUTE_PROC_FAIL            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 125 )
#define    DBM_ERRCODE_CHANGED_PLAN                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 126 )
#define    DBM_ERRCODE_ALREADY_ATTACH_TID           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 127 )
#define    DBM_ERRCODE_TOO_MANY_SEGMENT_EXTEND      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 128 )
#define    DBM_ERRCODE_GET_SEMAPHORE                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 129 )
#define    DBM_ERRCODE_CURSOR_API_ALREADY_OPENED    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 130 )
#define    DBM_ERRCODE_CURSOR_API_ALREADY_CLOSED    DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 131 )
#define    DBM_ERRCODE_DDL_RAISED                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 132 )
#define    DBM_ERRCODE_BEGIN_TRANS_STAT             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 133 )
#define    DBM_ERRCODE_NEED_NO_TX_AT_DDL            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 134 )
#define    DBM_ERRCODE_ALREADY_EXIST_LIB            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 135 )
#define    DBM_ERRCODE_NOT_EXIST_LIB                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 136 )
#define    DBM_ERRCODE_EXECUTE_USER_FUNC_FAIL       DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 137 )
#define    DBM_ERRCODE_INVALID_TIME_OPTION          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 138 )

#define    DBM_ERRCODE_PORT_OUT_OF_RANGE            DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 139 )
#define    DBM_ERRCODE_CLIENT_MAX_OUT_OF_RANGE      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 140 )
#define    DBM_ERRCODE_PROCESS_MAX_OUT_OF_RANGE     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 141 )
#define    DBM_ERRCODE_PROCESS_MIN_OUT_OF_RANGE     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 142 )
#define    DBM_ERRCODE_PROCESS_CNT_OUT_OF_RANGE     DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 143 )
#define    DBM_ERRCODE_QUEUE_SIZE_OUT_OF_RANGE      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 144 )
#define    DBM_ERRCODE_GSB_CREATE_FAIL              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 145 )
#define    DBM_ERRCODE_GSB_DROP_FAIL                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 146 )
#define    DBM_ERRCODE_INVALID_JSON_KEY_VALUE       DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 147 )
#define    DBM_ERRCODE_INVALID_JSON_VALUE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 148 )
#define    DBM_ERRCODE_ALREADY_EXISTS_REPL          DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 149 )
#define    DBM_ERRCODE_INVALID_DIRECT_TABLE_INDEX   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 150 )
#define    DBM_ERRCODE_INVALID_REPL_DIR             DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 151 )
#define    DBM_ERRCODE_INVALID_PROP                 DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 152 )
#define    DBM_ERRCODE_JOIN_NEED_INDEX              DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 153 )
#define    DBM_ERRCODE_DDL_NOT_ALLOWED_IN_REPL      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 154 )
#define    DBM_ERRCODE_NEED_INDEX_ON_OPERATION      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 155 )
#define    DBM_ERRCODE_ODBC_CALL_FAIL               DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 156 )
#define    DBM_ERRCODE_NOT_EXIST_DSN                DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 157 )
#define    DBM_ERRCODE_ODBC_LIB_OPEN_FAIL           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 158 )
#define    DBM_ERRCODE_ODBC_GET_SYMBOL_FAIL         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 159 )
#define    DBM_ERRCODE_INVALID_JSON_KEY_SIZE        DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 160 )
#define    DBM_ERRCODE_ERROR_HTTP                   DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 161 )
#define    DBM_ERRCODE_INVALID_LIMIT_OPTION         DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 162 )
#define    DBM_ERRCODE_NOT_ALLOWED_UPDATE           DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 163 )
#define    DBM_ERRCODE_NOT_INVALID_CREATE_TIME      DBM_MAKE_ERRCODE( DBM_ERROR_MODULE_DBM, 164 )



/**
 * << 주의 >>
 * 여기에 error code추가시 dbmErrorCode.h.in 파일을 수정해야 함.
 * dbmErrorCode.h 는 자동 생성 파일임.
 * 여기에 항목 추가시 steDbmError.c 에 error code에 대한 설명도 추가해야함.
 */

#endif

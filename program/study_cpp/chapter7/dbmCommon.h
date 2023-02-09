#ifndef __DBM_COMMON_H
#define __DBM_COMMON_H 1

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif



#define DBM_MAX_TRANS             (1024)
#define DBM_ALIGN_SIZE(A)         DBM_ALIGN_DEFAULT(A)   // 그냥 8의 배수로만 처리한다.
#define DBM_INVERT_BIT(data,loc)  ((data) ^= (0x1<<(loc)))
#define DBM_CHECK_BIT(data,loc)   ((data) & (0x1<<(loc)))
#define DBM_BITMAP_SLOT_SIZE      (8)
#define DBM_BITMAP_ARR_SIZE       (1024*1024*10)
#define DBM_FILE_HEADER_SIZE      (DBM_SIZEOF(dbmFileHeader))


#define ROUND(X,POS) ( floor( (X) * pow( 10.0, POS ) + 0.5 ) / pow( 10.0, POS ) )
#define OFFSET(A, B) ( (A + B - 1) & ~(A - 1) )


#define DBM_SHM_DIR                       "DBM_SHM_DIR"
#define DBM_SHM_PREFIX                    "DBM_SHM_PREFIX"
#define DBM_NOT_USED                      (-1)
#define DBM_NOT_USED_LONG                 (dbmInt64)(-1L)
#define DBM_INFINITE_SCN                  (dbmInt64)(-1L)
#define DBM_NO_SPACE                      (dbmInt64)(-2L)
#define DBM_OBJECT_NAME_LEN               (32)
#define DBM_USER_FUNC_NAME_LEN            (128)
#define DBM_KEY_NAME_LEN                  (256)
#define DBM_JSON_ERR_MSG_LEN              (1024)


#define DBM_DEFAULT_DISK_LOG_FILE_SIZE    "100M"
#define DBM_DEFAULT_LOG_CACHE_SIZE        "1G"
#define DBM_DEFAULT_LOG_CACHE_COUNT       "2"
#define DBM_DISK_BLOCK_HEADER_MARK        (dbmInt64)(91249584939201L)
#define DBM_DISK_BLOCK_END_MARK           (dbmInt64)(72128144838702L)
#define DBM_DISK_LOG_MARK                 (dbmInt64)(91249584939202L)
#define DBM_DISK_DATAFILE_MARK            (dbmInt64)(91249584939203L)
#define DBM_REPL_UNSENT_BLOCK_MARK        (dbmInt64)(48182636482816L)
#define DBM_DISK_BLOCK_SIZE               (512)
#define DBM_TCP_BUFFER_SIZE               (32 * 1024)
#define DBM_TCP_CS_PROTOCOL               (0x03)
#define DBM_TCP_REPL_PROTOCOL             (0x04)
#define DBM_TCP_CAPTURE_PROTOCOL          (0x05)
#define DBM_BUFFER_SIZE                   (32 * 1024)

#define DBM_TCP_CONN_TIMEOUT              "10000000"
#define DBM_TCP_RECV_TIMEOUT              "10000000"
#define DBM_REPL_CONN_TIMEOUT             "10000000"
#define DBM_REPL_RECV_TIMEOUT             "10000000"
#define DBM_LOCK_SLEEP_TIME               "40"
#define DBM_TRANS_SLOT_SIZE               (1024 * 1024)
#define DBM_INDEX_MAX_DEPTH               (32)
#define DBM_INDEX_MAX_SLOT_COUNT          (512)
#define DBM_INDEX_MAX_KEY_SIZE            (1024)
#define DBM_INDEX_FETCH_ARR_SIZE          (16)
#define DBM_MAX_COLUMN_COUNT              (10240)


#define DBM_JSON_DATA_SIZE                (128)
#define DBM_JSON_BEGIN_TIME_FIELD         "_DBM_BEGIN_TIME_"


#endif

%{
#include <dbmParser.h>
#include <dbmParserObject.h>
int yylex();
int yyerror( void           * aLocation,
             void           * aParam,
             void           * aScanner,
             const char     * aMsg );
%}

%pure-parser
%locations

%parse-param {dbmParserContext   * param}
%parse-param {void               * scanner}
%lex-param   {yyscan_t           * scanner}

%left TOK_PLUS
%left TOK_MINUS
%left TOK_ASTERISK
%left TOK_SOLIDUS
%left TOK_AND
%left TOK_OR
%right TOK_LEFT_PAREN
%left TOK_RIGHT_PAREN
%left TOK_CONCAT_OPER


%token
TOK_COLON
TOK_COMMA
TOK_SEMICOLON
TOK_PERIOD
TOK_QUESTION
TOK_QUOTE
TOK_DOUBLE_QUOTE
TOK_UNDERSCORE
TOK_PERCENT
TOK_COMMENT_TERM
TOK_DOLLAR_SIGN
TOK_SHARP 
TOK_AT_SIGN


%token
TOK_ASTERISK
TOK_MINUS
TOK_PLUS
TOK_SOLIDUS
TOK_CONCAT_OPER
TOK_PROC_ASSIGN
TOK_PROC_ITER
TOK_PROC_LEFT_LABEL
TOK_PROC_RIGHT_LABEL


%token
TOK_ABS
TOK_ACTIVE
TOK_ADD
TOK_AGING
TOK_ALL
TOK_ALTER
TOK_AS
TOK_ASCENDING
TOK_AVG
TOK_BEGIN
TOK_BY
TOK_CALL
TOK_CAPTURE
TOK_CASE
TOK_CEIL
TOK_CHECKPOINT
TOK_CLOSE
TOK_COLUMN
TOK_COMMIT
TOK_COMPACT
TOK_CONCAT
TOK_CONTINUE
TOK_CREATE
TOK_CURRVAL
TOK_CURSOR
TOK_CYCLE
TOK_DBMSOUTPUT
TOK_DECLARE
TOK_DECODE
TOK_DEFAULT
TOK_DELETE
TOK_DEQUEUE
TOK_DESCENDING
TOK_DIGEST
TOK_DIRECT
TOK_DROP
TOK_DUMP
TOK_DURATION
TOK_ELSE
TOK_ELSIF
TOK_EMPTY_BLOB
TOK_EMPTY_CLOB
TOK_END
TOK_ENQUEUE
TOK_EXEC
TOK_EXCEPTION
TOK_EXCEPTION_INIT
TOK_EXIT
TOK_EXP
TOK_EXPIRED
TOK_EXTEND
TOK_EXTERNAL
TOK_EXTRACT
TOK_FETCH
TOK_FIELDS
TOK_FINI
TOK_FLOOR
TOK_FOR
TOK_FOUND
TOK_FROM
TOK_FUNCTION
TOK_GOTO
TOK_GROUP
TOK_GSB
TOK_HEX
TOK_HEXTORAW
TOK_HOST_VARIABLE
TOK_IF
TOK_IN
TOK_INSTR
TOK_IS
TOK_ISOPEN
TOK_INOUT
TOK_INACTIVE
TOK_INCREMENT
TOK_IDENTIFIER
TOK_INDEX
TOK_INIT
TOK_INSERT
TOK_INSTANCE
TOK_INTERVAL
TOK_INTO
TOK_JSON_ADD
TOK_JSON_DELETE
TOK_JSON_KEY
TOK_JSON_QUERY
TOK_JSON_STRING
TOK_JSON_VALUE
TOK_LENGTH
TOK_LIBRARY
TOK_LIKE
TOK_LIMIT
TOK_LN
TOK_LOAD
TOK_LOCAL
TOK_LOG
TOK_LOOP
TOK_LOWER
TOK_LPAD
TOK_LTRIM
TOK_MAX
TOK_MAXVALUE
TOK_MIN
TOK_MINVALUE
TOK_MOD
TOK_MONITOR
TOK_NEXTVAL
TOK_NOCYCLE
TOK_NODE
TOK_NOTFOUND
TOK_NULL
TOK_NVL
TOK_ON
TOK_OPEN
TOK_ORDER
TOK_OTHERS
TOK_OUT
TOK_PARAMETER
TOK_PARAM_PTR
TOK_PARAM_32
TOK_PARAM_64
TOK_PERF
TOK_POWER
TOK_PRAGMA
TOK_PROCEDURE
TOK_PROCESS
TOK_PUT_LINE
TOK_QUOTE_STRING
TOK_DOUBLE_QUOTE_STRING
TOK_QUEUE
TOK_RAISE
TOK_RAISE_APPLICATION_ERROR
TOK_RANDOM
TOK_REBUILD
TOK_RENAME
TOK_RESET
TOK_REPL
TOK_REPLACE
TOK_RETURN
TOK_REVERSE
TOK_RPAD
TOK_ROLLBACK
TOK_ROUND
TOK_ROWCOUNT
TOK_ROWTYPE
TOK_RTRIM
TOK_SELECT
TOK_SEQUENCE
TOK_SERVER
TOK_SERVICE
TOK_SESSION
TOK_SESSION_ID
TOK_SET
TOK_SLOT
TOK_SIZE
TOK_SQL
TOK_SQRT
TOK_START
TOK_SUBSTR
TOK_SUM
TOK_SUMMARY
TOK_SYNC
TOK_SYSDATE
TOK_SYSTEM
TOK_TABLE
TOK_TARGET
TOK_TERMINATE
TOK_THEN
TOK_TIMEOUT
TOK_TO
TOK_TO_DATE
TOK_TO_TIMESTAMP
TOK_TRIM
TOK_TRUNC
TOK_TRUNCATE
TOK_TYPE
TOK_UNIQUE
TOK_UPDATE
TOK_UPPER
TOK_USERENV
TOK_USING
TOK_UINT
TOK_UNUM
TOK_VALUES
TOK_WHEN
TOK_WHERE
TOK_WHILE
TOK_WITH




%token
TOK_CHAR
TOK_DATE
TOK_DATEDIFF
TOK_DATETIME_STR
TOK_DOUBLE
TOK_FLOAT
TOK_LONG
TOK_INT
TOK_INTEGER
TOK_SHORT


%token
TOK_AND
TOK_COUNT
TOK_EQ
TOK_GT
TOK_GE
TOK_LE
TOK_LT
TOK_NE
TOK_OR


%start start_syntax

%%
start_syntax: ddl_stmt
              {
                  param->mParseObj = v1;
              }
              | dml_stmt
              {
                  param->mParseObj = v1;
              }
              | dcl_stmt
              {
                  param->mParseObj = v1;
              }
              ;


ddl_stmt: create_instance_stmt
          {
              v0 = v1;
          }
          | create_table_stmt
          {
              v0 = v1;
          }
          | create_queue_stmt
          {
              v0 = v1;
          }
          | create_index_stmt
          {
              v0 = v1;
          }
          | create_external_library_stmt
          {
              v0 = v1;
          }
          | create_sync_library_stmt
          {
              v0 = v1;
          }
          | drop_instance_stmt
          {
              v0 = v1;
          }
          | drop_table_stmt
          {
              v0 = v1;
          }
          | drop_index_stmt
          {
              v0 = v1;
          }
          | drop_library_stmt
          {
              v0 = v1;
          }
          | truncate_stmt
          {
              v0 = v1;
          }
          | alter_system_stmt
          {
              v0 = v1;
          }
          | alter_gsb_stmt
          {
              v0 = v1;
          }
          | create_sequence_stmt
          {
              v0 = v1;
          }
          | drop_sequence_stmt
          {
              v0 = v1;
          }
          | alter_sequence_stmt
          {
              v0 = v1;
          }
          | alter_table_stmt
          {
              v0 = v1;
          }
          | rebuild_index_stmt
          {
              v0 = v1;
          }
          | create_repl_stmt
          {
              v0 = v1;
          }
          | drop_repl_stmt
          {
              v0 = v1;
          }
          | create_capture_stmt
          {
              v0 = v1;
          }
          | drop_capture_stmt
          {
              v0 = v1;
          }
          | create_procedure_stmt
          {
              v0 = v1;
          }
          | drop_procedure_stmt
          {
              v0 = v1;
          }
          ;


dml_stmt: insert_stmt
          {
              v0 = v1;
          }
          | update_stmt
          {
              v0 = v1;
          }
          | delete_stmt
          {
              v0 = v1;
          }
          | select_stmt
          {
              v0 = v1;
          }
          | enqueue_stmt
          {
              v0 = v1;
          }
          | dequeue_stmt
          {
              v0 = v1;
          }
          | load_stmt
          {
              v0 = v1;
          }
          | sync_stmt
          {
              v0 = v1;
          }
          | exec_proc_stmt
          {
              v0 = v1;
          }
          | proc_block_section
          {
              v0 = v1;
          }
          | ora_insert_stmt
          {
              v0 = v1;
          }
          | ora_update_stmt
          {
              v0 = v1;
          }
          | ora_delete_stmt
          {
              v0 = v1;
          }
          ;


dcl_stmt: TOK_COMMIT
          {
              v0 = dbmMakeCreateDCLStmt( param,
                                         DBM_TRUE );
          }
          | TOK_ROLLBACK
          {
              v0 = dbmMakeCreateDCLStmt( param,
                                         DBM_FALSE );
          }
          ;


create_instance_stmt: TOK_CREATE TOK_INSTANCE identifier
                      obj_init_option
                      obj_extend_option
                      obj_max_option
                      {
                          v0 = dbmMakeCreateInstanceStmt( param,
                                                          v3,    // instName,
                                                          v4,    // InitOption
                                                          v5,    // extendOption
                                                          v6 );  // MaxOption
                      }
                      ;

create_queue_stmt: TOK_CREATE TOK_QUEUE identifier
                   TOK_SIZE int_val
                   obj_init_option
                   obj_extend_option
                   obj_max_option
                   {
                       v0 = dbmMakeCreateQueueStmt( param,
                                                    v3,      // NameList
                                                    v5,      // MsgSizeOption
                                                    v6,      // InitOption
                                                    v7,      // ExtendOption
                                                    v8,      // MaxOption
                                                    DBM_FALSE );   
                   }
/*                   |
                   TOK_CREATE TOK_DIRECT TOK_QUEUE identifier
                   TOK_SIZE int_val
                   obj_init_option
                   obj_extend_option
                   obj_max_option
                   {
                       v0 = dbmMakeCreateQueueStmt( param,
                                                    v4,      // NameList
                                                    v6,      // MsgSizeOption
                                                    v7,      // InitOption
                                                    v8,      // ExtendOption
                                                    v9,      // MaxOption
                                                    DBM_TRUE );    
                   }
*/
                   ;


create_table_stmt: TOK_CREATE TOK_TABLE identifier
                   TOK_LEFT_PAREN column_def_list TOK_RIGHT_PAREN
                   obj_init_option
                   obj_extend_option
                   obj_max_option
                   {
                       v0 = dbmMakeCreateTableStmt( param,
                                                    DBM_TABLE_TYPE_TABLE,
                                                    v3,      // NameList
                                                    v5,      // ColumnList
                                                    v7,      // InitOption
                                                    v8,      // ExtendOption
                                                    v9 );    // MaxOption
                   }
                   | 
                   TOK_CREATE TOK_DIRECT TOK_TABLE identifier
                   TOK_LEFT_PAREN column_def_list TOK_RIGHT_PAREN
                   obj_max_option
                   {
                       v0 = dbmMakeCreateTableStmt( param,
                                                    DBM_TABLE_TYPE_DIRECT_TABLE,
                                                    v4,      // NameList
                                                    v6,      // ColumnList
                                                    NULL,    // InitOption
                                                    NULL,    // ExtendOption
                                                    v8 );    // MaxOption
                   }
                   ;



create_index_stmt: TOK_CREATE TOK_UNIQUE TOK_INDEX identifier TOK_ON identifier
                   TOK_LEFT_PAREN index_key_list TOK_RIGHT_PAREN
                   {
                       v0 = dbmMakeCreateIndexStmt( param,
                                                    DBM_TRUE,  // IsUnique
                                                    v4,        // IndexName
                                                    v6,        // TableName
                                                    v8 );      // KeyList
                   }
                   |
                   TOK_CREATE TOK_INDEX identifier TOK_ON identifier
                   TOK_LEFT_PAREN index_key_list TOK_RIGHT_PAREN
                   {
                       v0 = dbmMakeCreateIndexStmt( param,
                                                    DBM_FALSE, // IsUnique
                                                    v3,        // IndexName
                                                    v5,        // TableName
                                                    v7 );      // KeyList
                   }
                   ;


create_external_library_stmt: TOK_CREATE TOK_EXTERNAL TOK_LIBRARY identifier
                              TOK_LOAD quote_val 
                              user_lib_init_func
                              user_lib_fini_func
                              user_lib_func_list
                              {
                                  v0 = dbmMakeCreateLibraryStmt( param,
                                                                 DBM_FALSE,
                                                                 v4,
                                                                 v6,
                                                                 v7,
                                                                 v8,
                                                                 v9 );
                              }
                              ;


create_sync_library_stmt: TOK_CREATE TOK_SYNC TOK_LIBRARY identifier
                          TOK_LOAD quote_val 
                          user_lib_init_func
                          user_lib_fini_func
                          user_lib_func_list
                          {
                              v0 = dbmMakeCreateLibraryStmt( param,
                                                             DBM_TRUE,
                                                             v4,
                                                             v6,
                                                             v7,
                                                             v8,
                                                             v9 );
                          }
                          ;


user_lib_init_func: /* empty */
                    {
                        v0 = NULL;
                    }
                    | TOK_INIT quote_val //parameter_def
                    {
                        dbmParseLibraryItem     * sItem = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mFuncName = v2;
                        //sItem->mParamList = v3;

                        v0 = sItem;
                    }
                    ;


user_lib_fini_func: /* empty */
                    {
                        v0 = NULL;
                    }
                    | TOK_FINI quote_val //parameter_def
                    {
                        dbmParseLibraryItem     * sItem = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mFuncName = v2;
                        //sItem->mParamList = v3;

                        v0 = sItem;
                    }
                    ;


user_lib_func_list: /* Empty */
                    {
                    }
                    | TOK_FUNCTION identifier quote_val //parameter_def
                    {
                        dbmParseLibraryItem    * sItem = NULL;
                        dbmList                * sList = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mAliasName = v2;
                        sItem->mFuncName = v3;
                        //sItem->mParamList = v4;

                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    sItem,
                                    param->mErrorStack );
 
                        v0 = sList;
                    }
                    | user_lib_func_list TOK_COMMA identifier quote_val //parameter_def
                    {
                        dbmParseLibraryItem    * sItem = NULL;

                        dbmAllocMemory( param->mAllocator,
                                        sizeof(dbmParseLibraryItem),
                                        (void **)&sItem,
                                        param->mErrorStack );

                        dbmMemset( sItem, 0x00, sizeof(dbmParseLibraryItem) );
 
                        sItem->mAliasName = v3;
                        sItem->mFuncName = v4;
                        //sItem->mParamList = v5;


                        dbmAddList( param->mAllocator,
                                    v1,
                                    DBM_LIST_ELEM_POINTER,
                                    sItem,
                                    param->mErrorStack );

                        v0 = v1;
                    }
                    ;



/****
parameter_def: // Empty
               {
                   v0 = NULL;
               }
               | TOK_LEFT_PAREN parameter_list TOK_RIGHT_PAREN
               {
                   v0 = v2;
               }
               ;

parameter_list: parameter_item 
                {
                    dbmList   * sList = NULL;
                    dbmCreateList( param->mAllocator,
                                   &sList,
                                   param->mErrorStack );

                    dbmAddList( param->mAllocator,
                                sList,
                                DBM_LIST_ELEM_POINTER,
                                v1,
                                param->mErrorStack );

                    v0 = sList;
                }
                | parameter_list TOK_COMMA parameter_item
                {
                    dbmAddList( param->mAllocator,
                                v1,
                                DBM_LIST_ELEM_POINTER,
                                v3,
                                param->mErrorStack );

                    v0 = v1;
                }
                ;

parameter_item: identifier TOK_PARAM_PTR
                {
                    dbmParseLibraryParam    * sItem = NULL;

                    dbmAllocMemory( param->mAllocator,
                                    sizeof(dbmParseLibraryParam),
                                    (void **)&sItem,
                                    param->mErrorStack );
 
                    sItem->mName = v1;
                    sItem->mDataType = DBM_PARSE_DATA_TYPE_POINTER;

                    v0 = sItem;
                }
                | identifier TOK_PARAM_32
                {
                    dbmParseLibraryParam    * sItem = NULL;

                    dbmAllocMemory( param->mAllocator,
                                    sizeof(dbmParseLibraryParam),
                                    (void **)&sItem,
                                    param->mErrorStack );

                    sItem->mName = v1;
                    sItem->mDataType = DBM_PARSE_DATA_TYPE_VAL_32;

                    v0 = sItem;
                }
                | identifier TOK_PARAM_64
                {
                    dbmParseLibraryParam    * sItem = NULL;

                    dbmAllocMemory( param->mAllocator,
                                    sizeof(dbmParseLibraryParam),
                                    (void **)&sItem,
                                    param->mErrorStack );

                    sItem->mName = v1;
                    sItem->mDataType = DBM_PARSE_DATA_TYPE_VAL_64;

                    v0 = sItem;
                }
                ;
****/

drop_instance_stmt: TOK_DROP TOK_INSTANCE identifier
                    {
                        v0 = dbmMakeDropInstanceStmt( param,
                                                      v3 );
                    }
                    ;


drop_procedure_stmt: TOK_DROP TOK_PROCEDURE identifier
                     {
                         v0 = dbmMakeDropProcedureStmt( param,
                                                        v3 );
                     }
                     ;



drop_table_stmt: TOK_DROP TOK_TABLE identifier
                 {
                     v0 = dbmMakeDropTableStmt( param,
                                                DBM_PARSE_TYPE_DROP_TABLE_STMT,
                                                v3 );
                 }
                 | TOK_DROP TOK_QUEUE identifier
                 {
                     v0 = dbmMakeDropTableStmt( param,
                                                DBM_PARSE_TYPE_DROP_QUEUE_STMT,
                                                v3 );
                 }
                 ;

drop_index_stmt: TOK_DROP TOK_INDEX identifier
                 {
                     v0 = dbmMakeDropIndexStmt( param,
                                                v3 );
                 }
                 ;


drop_library_stmt: TOK_DROP TOK_LIBRARY identifier
                   {
                        v0 = dbmMakeDropLibraryStmt( param,
                                                     v3 );
                   }
                   ;


truncate_stmt: TOK_TRUNCATE TOK_TABLE identifier
               {
                     v0 = dbmMakeTruncateStmt( param,
                                               DBM_PARSE_TYPE_TRUNCATE_TABLE_STMT,
                                               v3 );
               }
               | TOK_TRUNCATE TOK_QUEUE identifier
               {
                     v0 = dbmMakeTruncateStmt( param,
                                               DBM_PARSE_TYPE_TRUNCATE_QUEUE_STMT,
                                               v3 );
               }
               ;

alter_system_stmt: repl_send_stmt
                   {
                       v0 = v1;
                   }
                   | repl_mod_stmt
                   {
                       v0 = v1;
                   }
                   | change_instance_active_stmt
                   {
                       v0 = v1;
                   }
                   | reset_ckpt_fileno_stmt
                   {
                       v0 = v1;
                   }
                   | reset_perf_stmt
                   {
                       v0 = v1;
                   }
                   | execute_aging_stmt
                   {
                       v0 = v1;
                   }
                   | session_kill_stmt
                   {
                       v0 = v1;
                   }
                   ;


session_kill_stmt: TOK_ALTER TOK_SESSION TOK_TERMINATE int_val
                   {
                       v0 = dbmMakeAlterTermSessionStmt( param,
                                                         v4 );
                   }
                   ;


execute_aging_stmt: TOK_ALTER TOK_SYSTEM TOK_AGING
                    {
                        v0 = dbmMakeAlterAgingStmt( param,
                                                    NULL );
                    }
                    | TOK_ALTER TOK_SYSTEM TOK_AGING identifier_list
                    {
                        v0 = dbmMakeAlterAgingStmt( param,
                                                    v4 );
                    }
                    ;



alter_table_stmt: TOK_ALTER TOK_TABLE identifier TOK_RENAME TOK_COLUMN identifier TOK_TO identifier
                  {
                      v0 = dbmMakeAlterTableRenameColumnStmt( param,
                                                              v3,
                                                              v6,
                                                              v8 );       
                  }
                  | TOK_ALTER TOK_TABLE identifier TOK_ADD TOK_COLUMN TOK_LEFT_PAREN column_def default_val TOK_RIGHT_PAREN
                  {
                      v0 = dbmMakeAlterTableAddColumnStmt( param,
                                                           v3,
                                                           v7,
                                                           v8 );
                  }
                  | TOK_ALTER TOK_TABLE identifier TOK_DROP TOK_COLUMN identifier
                  {
                      v0 = dbmMakeAlterTableDropColumnStmt( param,
                                                            v3,
                                                            v6 );
                  }
                  | TOK_ALTER TOK_TABLE identifier TOK_COMPACT
                  {
                      v0 = dbmMakeAlterTableCompactStmt( param,
                                                         v3 );
                  }
                  ;


default_val: /* empty */
             {
                 v0 = NULL;
             }
             | TOK_DEFAULT value_expr
             {
                 v0 = v2;
             }
             ;


rebuild_index_stmt: TOK_ALTER TOK_TABLE identifier TOK_REBUILD identifier
                    {
                        v0 = dbmMakeAlterRebuildIndexStmt( param,
                                                           v3,
                                                           v5 );
                    }
                    ;
 


create_sequence_stmt: TOK_CREATE TOK_SEQUENCE identifier
                      seq_start_with
                      seq_increment
                      seq_max
                      seq_min
                      seq_cycle
                      {
                          v0 = dbmMakeCreateSequenceStmt( param,
                                                          v3,
                                                          v4,
                                                          v5,
                                                          v6, // max
                                                          v7, // min
                                                          v8 );
                      }
                      ;

drop_sequence_stmt: TOK_DROP TOK_SEQUENCE identifier
                    {
                        v0 = dbmMakeDropSequenceStmt( param,
                                                      v3 );
                    }
                    ;

alter_sequence_stmt: TOK_ALTER TOK_SEQUENCE identifier 
                     TOK_SET TOK_CURRVAL TOK_EQ int_val
                     {
                         v0 = dbmMakeAlterSequenceStmt( param,
                                                        v3,
                                                        v7 );
                     }
                     ;


seq_start_with: /* Empty */
                {
                   v0 = dbmMakeIntValue( param,
                                         DBM_FALSE,
                                         "1" );
                }
                |
                TOK_START TOK_WITH int_val
                {
                    v0 = v3;
                }
                ;

seq_increment: /* Empty */
               {
                   v0 = dbmMakeIntValue( param,
                                         DBM_FALSE,
                                         "1" );
               }
               |
               TOK_INCREMENT TOK_BY int_val
               {
                   v0 = v3;
               }
               ;

seq_max: /* Empty */
         {
             v0 = dbmMakeIntValue( param,
                                   DBM_FALSE,
                                   "MAX" );
         }
         | 
         TOK_MAXVALUE int_val
         {
             v0 = v2;
         }
         ;

seq_min: /* Empty */
         {
             v0 = dbmMakeIntValue( param,
                                   DBM_FALSE,
                                   "MIN" );
         }
         |
         TOK_MINVALUE int_val
         {
             v0 = v2;
         }
         ;

seq_cycle: /* empty */
           {
               v0 = dbmMakeIntValue( param,
                                     DBM_FALSE,
                                     "N" );
           }
           | TOK_CYCLE
           {
               v0 = dbmMakeIntValue( param,
                                     DBM_FALSE,
                                     "Y" );
           }
           | TOK_NOCYCLE
           {
               v0 = dbmMakeIntValue( param,
                                     DBM_FALSE,
                                     "N" );
           }
           ;

repl_send_stmt: TOK_ALTER TOK_SYSTEM TOK_REPL TOK_SYNC
                {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_SYNC,
                                                   NULL );
                }
                | TOK_ALTER TOK_SYSTEM TOK_REPL TOK_SYNC TOK_LOCAL
                {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_LOCAL_SYNC,
                                                   NULL );
                }
                | TOK_ALTER TOK_SYSTEM TOK_REPL TOK_SYNC TOK_ALL
                {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_FULL_SYNC,
                                                   NULL );
                }
                | TOK_ALTER TOK_SYSTEM TOK_REPL TOK_SYNC identifier_list
                {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_FULL_SYNC,
                                                   v5 );
                }
                | TOK_ALTER TOK_SYSTEM TOK_REPL TOK_RESET
                {
                    v0 = dbmMakeAlterReplSyncStmt( param,
                                                   DBM_REPL_ACT_RESET,
                                                   NULL );
                }
                ;

repl_mod_stmt: TOK_ALTER TOK_REPL TOK_ADD TOK_TABLE identifier_list
               {
                   v0 = dbmMakeAlterReplModStmt( param,
                                                 DBM_FALSE,
                                                 v5 );
               }
               | TOK_ALTER TOK_REPL TOK_DROP TOK_TABLE identifier_list
               {
                   v0 = dbmMakeAlterReplModStmt( param,
                                                 DBM_TRUE,
                                                 v5 );
               }
               ;

reset_perf_stmt: TOK_ALTER TOK_SYSTEM TOK_RESET TOK_PERF
                 {
                     v0 = dbmMakeAlterResetPerfStmt( param );
                 }
                 ;


change_instance_active_stmt: TOK_ALTER TOK_SYSTEM TOK_INSTANCE TOK_ACTIVE
                             {
                                 v0 = dbmMakeAlterSystemInstanceStmt( param,
                                                                      DBM_TRUE );
                             }
                             | TOK_ALTER TOK_SYSTEM TOK_INSTANCE TOK_INACTIVE
                             {
                                 v0 = dbmMakeAlterSystemInstanceStmt( param,
                                                                      DBM_FALSE );
                             }
                             ;


reset_ckpt_fileno_stmt: TOK_ALTER TOK_SYSTEM TOK_RESET TOK_CHECKPOINT identifier int_val
                        {
                            v0 = dbmMakeAlterSystemResetCkptFileStmt( param,
                                                                      v5,
                                                                      v6 );
                        }
                        ;


create_repl_stmt: TOK_CREATE TOK_REPL TOK_TABLE value_expr_list
                  {
                      v0 = dbmMakeCreateReplStmt( param,
                                                  v4 );
                  }
                  ;

drop_repl_stmt: TOK_DROP TOK_REPL 
                {
                    v0 = dbmMakeDropReplStmt( param );
                }
                ;


create_capture_stmt: TOK_CREATE TOK_CAPTURE identifier 
                     TOK_TABLE value_expr_list
                     {
                         v0 = dbmMakeCreateCaptureStmt( param,
                                                        v3,
                                                        v5 );
                     }
                     ;


drop_capture_stmt: TOK_DROP TOK_CAPTURE identifier 
                {
                    v0 = dbmMakeDropCaptureStmt( param,
                                                 v3 );
                }
                ;


ora_insert_stmt: TOK_INSERT TOK_INTO double_quote_chain
                 TOK_LEFT_PAREN ora_insert_columns TOK_RIGHT_PAREN
                 TOK_VALUES TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeOraInsertStmt( param,
                                                v3,      // TableName
                                                v5,      // Columns
                                                v9 );    // ValueList
                 }
                 ;


ora_insert_columns: double_quote_val
                    {
                        dbmList       * sList = NULL;
   
                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v1,
                                    param->mErrorStack );
   
                        v0 = sList;
                    }
                    | ora_insert_columns TOK_COMMA double_quote_val
                    {
                        dbmList          * sList = v1;
  
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v3,
                                    param->mErrorStack );
                        v0 = sList;
                    }
                    ;
 



insert_stmt: TOK_INSERT TOK_INTO identifier
             insert_columns
             TOK_VALUES TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
             expired_time
             {
                 v0 = dbmMakeInsertStmt( param,
                                         v3,      // TableName
                                         v4,      // Columns
                                         v7,      // values
                                         v9 );    
             }
             ;

expired_time: /* empty */
              {
                  v0 = NULL;
              }
              | TOK_EXPIRED int_val
              {
                  v0 = v2;
              }
              ;


ora_update_stmt: TOK_UPDATE double_quote_chain
                 TOK_SET update_target_list
                 where_cond_expr
                 {
                     v0 = dbmMakeOraUpdateStmt( param,
                                                DBM_PARSE_TYPE_UPDATE_STMT,
                                                v2,      // TableName
                                                v4,      // Set List
                                                v5 );    // where 
                 }
                 ;



update_stmt: TOK_UPDATE identifier
             TOK_SET update_target_list
             where_cond_expr
             {
                 v0 = dbmMakeUpdateStmt( param,
                                         DBM_PARSE_TYPE_UPDATE_STMT,
                                         v2,      // TableName
                                         v4,      // Set List
                                         v5 );    // where 
             }
             ;


json_function_item: TOK_JSON_ADD TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_ADD,
                                                   v3,
                                                   v5,
                                                   NULL, 
                                                   NULL );
                    }
                    | TOK_JSON_DELETE TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_DELETE,
                                                   v3,
                                                   v5,
                                                   NULL,
                                                   NULL );
                    }
                    | TOK_JSON_QUERY TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_QUERY,
                                                   v3,
                                                   v5,
                                                   NULL,
                                                   NULL );
                    }
                    | TOK_JSON_VALUE TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_VALUE,
                                                   v3,
                                                   v5,
                                                   NULL,
                                                   NULL );
                    }
                    | TOK_JSON_VALUE TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                    {
                        v0 = dbmMakeParseFunction( param,
                                                   DBM_PARSE_FUNCTION_JSON_VALUE,
                                                   v3,
                                                   NULL,
                                                   NULL,
                                                   NULL );
                    }
                    ;


ora_delete_stmt: TOK_DELETE TOK_FROM double_quote_chain
                 where_cond_expr
                 {
                     v0 = dbmMakeOraDeleteStmt( param,
                                                v3,      // TableName
                                                v4 );    // where 
                 }
                 ;



delete_stmt: TOK_DELETE TOK_FROM identifier
             where_cond_expr
             {
                 v0 = dbmMakeDeleteStmt( param,
                                         v3,      // TableName
                                         v4 );    // where 
             }
             ;


select_stmt: TOK_SELECT value_expr_list
             TOK_FROM table_source_list
             where_cond_expr
             group_by_list
             order_by_stmt
             for_update
             limit_phrase
             {
                 v0 = dbmMakeSelectStmt( param,
                                         v2,       // Target List
                                         v4,       // Table
                                         v5,       // Where
                                         v6,       // Group By
                                         v7,       // Order By
                                         v8,       // for update
                                         v9 );     // limit
             }
             |
             TOK_SELECT TOK_ASTERISK
             TOK_FROM table_source_list
             where_cond_expr
             order_by_stmt
             for_update
             limit_phrase
             {
                 v0 = dbmMakeSelectStmt( param,
                                         NULL,     // Target List (ALL COLUMN)
                                         v4,       // Table
                                         v5,       // Where
                                         NULL,     // Group by
                                         v6,       // Order by
                                         v7,       // for update
                                         v8 );     // limit
             }
             ;


limit_phrase: /* Empty */
              {
                  v0 = NULL;
              }
              | TOK_LIMIT int_val
              {
                  v0 = dbmMakeParseLimit( param, NULL, v2 );
              }
              | TOK_LIMIT int_val TOK_COMMA int_val
              {
                  v0 = dbmMakeParseLimit( param, v2, v4 );
              }
              ;
              


enqueue_stmt: TOK_ENQUEUE TOK_INTO identifier
              insert_columns
              TOK_VALUES TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
              {
                  v0 = dbmMakeEnqueueStmt( param,
                                           v3,      // TableName
                                           v4,      // Columns
                                           v7 );    // Values
              }
              ;

dequeue_stmt: TOK_DEQUEUE TOK_FROM identifier
              where_cond_expr
              {
                  v0 = dbmMakeDequeueStmt( param,
                                           v3,       // Table
                                           v4,       // where
                                           NULL );   // Timeout
              }
              |
              TOK_DEQUEUE TOK_FROM identifier
              where_cond_expr
              TOK_TIMEOUT int_val
              {
                  v0 = dbmMakeDequeueStmt( param,
                                           v3,       // Table
                                           v4,       // where
                                           v6 );     // Timeout
              }
              ;


load_stmt: TOK_LOAD TOK_INTO identifier insert_columns
           TOK_FROM quote_val TOK_USING identifier 
           TOK_LEFT_PAREN quote_val TOK_COMMA quote_val TOK_RIGHT_PAREN
           expired_time
           {
               v0 = dbmMakeLoadStmt( param,
                                     v3,       // targetTable
                                     v4,       // TargetTable columnTargetList
                                     v6,       // SourceQuery
                                     v8,       // SourceDSN
                                     v10,      // SourceUid
                                     v12,      // SourcePwd
                                     v14 );    // expiredTime
           };


sync_stmt: TOK_SYNC TOK_INTO identifier insert_columns  TOK_FROM quote_val TOK_USING identifier 
           TOK_LEFT_PAREN quote_val TOK_COMMA quote_val TOK_RIGHT_PAREN
           {
               v0 = dbmMakeSyncStmt( param,
                                     v3,       // targetTable
                                     v4,       // targetColumnList
                                     v6,       // sourceQuery
                                     v8,       // targetDSN
                                     v10,      // targetUid
                                     v12 );    // targetPwd
           };



exec_proc_stmt: TOK_CALL identifier TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN 
                {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              v4 );
                }
                | TOK_EXEC identifier TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              v4 );
                }    
                | TOK_EXEC identifier 
                {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              NULL );
                }    
                | TOK_EXEC identifier TOK_LEFT_PAREN TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeExecProcStmt( param,
                                              v2,
                                              NULL );
                }    
                ;


index_key_list: index_key_column
                {
                    dbmList    * sList = NULL;

                    dbmCreateList( param->mAllocator,
                                   &sList,
                                   param->mErrorStack );
   
                    dbmAddList( param->mAllocator,
                                sList,
                                DBM_LIST_ELEM_POINTER,
                                v1,
                                param->mErrorStack );
 
                    v0 = sList;
                }
                | index_key_list TOK_COMMA index_key_column
                {
                    dbmAddList( param->mAllocator,
                                v1,
                                DBM_LIST_ELEM_POINTER,
                                v3,
                                param->mErrorStack );
  
                    v0 = v1;
                };



index_key_column: identifier ordering
                  {
                      v0 = dbmMakeKeyColumnDef( param,
                                                DBM_PARSE_FUNCTION_INVALID,
                                                v1,
                                                NULL,
                                                NULL,
                                                v2 );
                  }
                  | double_quote_val ordering
                  {
                      v0 = dbmMakeKeyColumnDef( param,
                                                DBM_PARSE_FUNCTION_INVALID,
                                                v1,
                                                NULL,
                                                NULL,
                                                v2 );
                  }
                  | TOK_JSON_KEY TOK_LEFT_PAREN identifier TOK_COMMA quote_val TOK_COMMA int_val TOK_RIGHT_PAREN ordering
                  {
                      v0 = dbmMakeKeyColumnDef( param,
                                                DBM_PARSE_FUNCTION_JSON_KEY,
                                                v3,
                                                v5,
                                                v7,
                                                v9 );
                  }
                  ;


order_by_stmt: /* empty */
               {
                   v0 = NULL;
               }
               | TOK_ORDER TOK_BY value_expr_list
               {
                   v0 = v3;
               }
               ;


ordering: /* empty */
          {
              v0 = NULL;
          }
          | TOK_ASCENDING
          {
              v0 = NULL;
          }
          | TOK_DESCENDING
          {
              v0 = v1;
          }
          ;


group_by_list: /* Empty */
               {
                   v0 = NULL;
               }
               | TOK_GROUP TOK_BY value_expr_list
               {
                   v0 = v3;
               }
               ;


for_update: /* Empty */
            {
                v0 = NULL;
            }
            | TOK_FOR TOK_UPDATE
            {
                dbmParseValue *sVal;

                dbmAllocMemory( param->mAllocator,
                                sizeof(dbmParseValue),
                                (void **)&sVal,
                                param->mErrorStack );

                sVal->mType = DBM_PARSE_TYPE_IDENTIFIER;
                sVal->mValue = NULL;

                v0 = sVal;
            }
            ;


table_source_list: table_source
                   {
                       dbmList       * sList = NULL;

                       dbmCreateList( param->mAllocator,
                                      &sList,
                                      param->mErrorStack );
   
                       dbmAddList( param->mAllocator,
                                   sList,
                                   DBM_LIST_ELEM_POINTER,
                                   v1,
                                   param->mErrorStack );
  
                       v0 = sList;
 
                   }
                   | table_source_list TOK_COMMA table_source
                   {
                       dbmAddList( param->mAllocator,
                                   v1,
                                   DBM_LIST_ELEM_POINTER,
                                   v3,
                                   param->mErrorStack );
  
                       v0 = v1;
                   }
                   ;


table_source: identifier
              {
                  v0 = dbmMakeTableSource( param,
                                           v1,
                                           NULL );
              }
              | identifier identifier
              {
                  v0 = dbmMakeTableSource( param,
                                           v1,
                                           v2 );
              }
              ;
              


update_target_list: update_item
                    {
                        dbmList       * sList = NULL;

                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    v1,
                                    param->mErrorStack );
   
                        v0 = sList;
                    }
                    | update_target_list TOK_COMMA update_item
                    {
                        dbmAddList( param->mAllocator,
                                    v1,
                                    DBM_LIST_ELEM_POINTER,
                                    v3,
                                    param->mErrorStack );
 
                        v0 = v1;
                    }
                    ;


update_item: identifier TOK_EQ value_expr
             {
                 v0 = dbmMakeUpdateSetItem( param,
                                            DBM_FALSE,
                                            v1,     // Column
                                            v3 );   // Value
             }
             | json_function_item
             {
                 v0 = v1;
             }
             | double_quote_chain TOK_EQ value_expr
             {
                 v0 = dbmMakeUpdateSetItem( param,
                                            DBM_TRUE,
                                            v1,     // Column
                                            v3 );   // Value
             }
             ;



where_cond_expr: /* Empty */
                 {
                     v0 = NULL;
                 }
                 | TOK_WHERE value_expr
                 {
                     v0 = v2;
                 }
                 ;


insert_columns: /* Empty */
                {
                    v0 = NULL;
                }
                | TOK_LEFT_PAREN identifier_list TOK_RIGHT_PAREN 
                {
                    v0 = v2;
                }
                ;


column_def_list: column_def
                 {
                     dbmList       * sList = NULL;

                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
                 | column_def_list TOK_COMMA column_def
                 {
                     dbmAddList( param->mAllocator,
                                 v1,
                                 DBM_LIST_ELEM_POINTER,
                                 v3,
                                 param->mErrorStack );
                     v0 = v1;
                 }
                 ;


column_def: identifier declare_data_type 
            {
                v0 = dbmMakeColumnDef( param,
                                       v1,
                                       v2 );    
            }
            ;


declare_data_type: TOK_SHORT
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_SHORT,
                                                sizeof(dbmUInt16) );
                   }
                   | TOK_INTEGER
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_INT,
                                                sizeof(int) );
                   }
                   | TOK_INT
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_INT,
                                                sizeof(int) );
                   }
                   | TOK_FLOAT
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_FLOAT,
                                                sizeof(float) );
                   }
                   | TOK_DOUBLE
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_DOUBLE,
                                                sizeof(double) );
                   }
                   | TOK_LONG
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_LONG,
                                                sizeof(long) );
                   }
                   | TOK_CHAR TOK_LEFT_PAREN int_val TOK_RIGHT_PAREN
                   {
                       dbmParseValue *sVal = (dbmParseValue *)v3;
                      
                       if( (sVal != NULL) && (sVal->mType == DBM_PARSE_TYPE_UINT) )
                       {
                           v0 = dbmMakeDataTypeDef( param,
                                                    DBM_PARSE_DATA_TYPE_CHAR,
                                                    atoi(sVal->mValue) );
                       }
                   }
                   | TOK_DATE
                   {
                       v0 = dbmMakeDataTypeDef( param,
                                                DBM_PARSE_DATA_TYPE_DATE,
                                                sizeof(dbmTime) );
                   }
                   ;


obj_init_option: /* Empty */
                 {
                     v0 = NULL;
                 }
                 | TOK_INIT int_val
                 {
                     v0 = v2;
                 }
                 ;


obj_extend_option: /* Empty */
                   {
                       v0 = NULL;
                   }
                   | TOK_EXTEND int_val
                   {
                       v0 = v2;
                   }
                   ;


obj_max_option: /* Empty */
                {
                    v0 = NULL;
                }
                | TOK_MAX int_val
                {
                    v0 = v2;
                }
                ;




create_procedure_stmt: TOK_CREATE TOK_PROCEDURE identifier 
                       proc_param_phrase
                       TOK_IS
                       proc_block_section
                       TOK_SEMICOLON
                       TOK_SOLIDUS
                       {
                           v0 = dbmMakeCreateProcStmt( param,
                                                       v3,    // ProcName
                                                       v4,    // ParamList
                                                       v6,    // Proc Block
                                                       DBM_FALSE );
                       }
                       | TOK_CREATE TOK_OR TOK_REPLACE TOK_PROCEDURE identifier 
                       proc_param_phrase
                       TOK_IS
                       proc_block_section
                       TOK_SEMICOLON
                       TOK_SOLIDUS
                       {
                           v0 = dbmMakeCreateProcStmt( param,
                                                       v5,    // ProcName
                                                       v6,    // ParamList
                                                       v8,    // Proc Block
                                                       DBM_TRUE );
                       }
                       ;

proc_param_phrase: /* empty */
                   {
                       v0 = NULL;
                   }
                   | TOK_LEFT_PAREN proc_param_section TOK_RIGHT_PAREN
                   {
                       v0 = v2;
                   }
                   | TOK_LEFT_PAREN TOK_RIGHT_PAREN
                   {
                       v0 = NULL;
                   }
                   ;


proc_block_section: proc_declare_section 
                    TOK_BEGIN  proc_stmt_list proc_block_exception TOK_END 
                    {
                        v0 = dbmMakeProcBlockStmt( param,
                                                   v1,
                                                   v3,
                                                   v4 );
                    }
                    | TOK_BEGIN  proc_stmt_list proc_block_exception TOK_END 
                    {
                        v0 = dbmMakeProcBlockStmt( param,
                                                   NULL,
                                                   v2,
                                                   v3 );
                    }
                    | TOK_DECLARE proc_declare_section
                      TOK_BEGIN proc_stmt_list proc_block_exception TOK_END 
                    {
                        v0 = dbmMakeProcBlockStmt( param,
                                                   v2,
                                                   v4,
                                                   v5 );
                    }
                    ;

proc_block_exception: /* empty */
                      {
                          v0 = NULL;
                      }
                      | TOK_EXCEPTION proc_exception_list
                      {
                          v0 = v2;
                      }
                      ;

proc_exception_list: proc_exception_item
                     {
                         dbmList       * sList = NULL;
  
                         dbmCreateList( param->mAllocator,
                                        &sList,
                                        param->mErrorStack );

                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v1,
                                     param->mErrorStack );

                         v0 = sList;
                     }
                     | proc_exception_list proc_exception_item
                     {
                         dbmList        * sList = (dbmList *)v1;
 
                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v2,
                                     param->mErrorStack );
     
                         v0 = sList;
                     }
                     ;

proc_exception_item: TOK_WHEN identifier TOK_THEN proc_stmt_list
                     {
                         v0 = dbmMakeProcExceptionItem( param,
                                                        v2,
                                                        v4 );
                     }
                     ;



proc_stmt_list:  proc_stmt
                 {
                     dbmList       * sList = NULL;
  
                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
                 | proc_stmt_list proc_stmt
                 {
                     dbmList        * sList = (dbmList *)v1;
 
                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v2,
                                 param->mErrorStack );
 
                     v0 = sList;
                 }
                 ;


proc_label: /* Empty */
            {
                v0 = NULL;
            }
            | TOK_PROC_LEFT_LABEL identifier TOK_PROC_RIGHT_LABEL
            {
                v0 = v2;
            }
            ;


proc_stmt: proc_label proc_block_section TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_BLOCK,
                                     v1,
                                     v2 );
           }
           | proc_label TOK_NULL TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_NULL,
                                     v1,
                                     NULL );
           }
           | proc_label identifier_chain TOK_PROC_ASSIGN value_expr TOK_SEMICOLON
           {
               dbmParseProcAssignStmt     * sStmt = NULL;
               sStmt = dbmMakeProcAssignStmt( param,
                                              v2,
                                              v4 );
 
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_ASSIGN,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_DBMSOUTPUT TOK_PERIOD TOK_PUT_LINE TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN TOK_SEMICOLON
           {
               dbmParseProcPutLineStmt     * sStmt = NULL;
               sStmt = dbmMakeProcPutLineStmt( param,
                                               v6 );
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_PUTLINE,
                                     v1,
                                     sStmt );
           }
           | proc_label 
           TOK_SELECT value_expr_list
           TOK_INTO identifier_list
           TOK_FROM table_source_list
           where_cond_expr
           group_by_list
           for_update TOK_SEMICOLON
           {
               dbmParseSelectIntoStmt *sStmt = NULL;

               sStmt = dbmMakeSelectIntoStmt( param,
                                              v3,       // Target List
                                              v5,       // IntoList
                                              v7,       // Table
                                              v8,       // Where
                                              v9,     // Group By
                                              v10 );     // for update
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SELECT_INTO,
                                     v1,
                                     sStmt );
           }
           | proc_label
           TOK_SELECT TOK_ASTERISK
           TOK_INTO identifier_list
           TOK_FROM table_source_list
           where_cond_expr
           group_by_list
           for_update TOK_SEMICOLON
           {
               dbmParseSelectIntoStmt *sStmt = NULL;

               sStmt = dbmMakeSelectIntoStmt( param,
                                              NULL,       // Target List
                                              v5,       // IntoList
                                              v7,       // Table
                                              v8,       // Where
                                              v9,     // Group By
                                              v10 );     // for update
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SELECT_INTO,
                                     v1,
                                     sStmt );
           }
           | proc_label insert_stmt TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_INSERT,
                                     v1,
                                     v2 );
           }
           | proc_label update_stmt TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_UPDATE,
                                     v1,
                                     v2 );
           }
           | proc_label delete_stmt TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_DELETE,
                                     v1,
                                     v2 );
           }
           | proc_label proc_if_stmt TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_IF,
                                     v1,
                                     v2 );
           }
           | proc_label TOK_LOOP proc_stmt_list TOK_END TOK_LOOP TOK_SEMICOLON
           {
               dbmParseProcLoopStmt    * sStmt = NULL;

               sStmt = dbmMakeProcLoopStmt( param,
                                            v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_LOOP,
                                     v1,
                                     sStmt );
           }
           | proc_label proc_exit_stmt
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_EXIT,
                                     v1,
                                     v2 );
           }
           | proc_label proc_continue_stmt
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_CONTINUE,
                                     v1,
                                     v2 );
           }
           | proc_label TOK_CASE value_expr proc_case_when_list proc_case_end TOK_SEMICOLON
           {
               dbmParseProcSimpleCaseStmt    * sStmt = NULL;

               sStmt = dbmMakeProcSimpleCaseStmt( param,
                                                  v3,
                                                  v4,
                                                  v5 );
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SIMPLE_CASE,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_CASE proc_case_when_list proc_case_end TOK_SEMICOLON
           {
               dbmParseProcSearchedCaseStmt    * sStmt = NULL;

               sStmt = dbmMakeProcSearchedCaseStmt( param,
                                                    v3,
                                                    v4 );
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_SEARCH_CASE,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_FOR identifier TOK_IN value_expr TOK_PROC_ITER value_expr 
             TOK_LOOP 
               proc_stmt_list 
             TOK_END TOK_LOOP TOK_SEMICOLON
           {
               dbmParseProcForLoopStmt     * sStmt = NULL;

               sStmt = dbmMakeProcForLoopStmt( param,
                                               v3,
                                               DBM_FALSE,
                                               v5,
                                               v7,
                                               v9 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_FOR_LOOP,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_FOR identifier TOK_IN TOK_REVERSE value_expr TOK_PROC_ITER value_expr 
             TOK_LOOP 
               proc_stmt_list 
             TOK_END TOK_LOOP TOK_SEMICOLON
           {
               dbmParseProcForLoopStmt     * sStmt = NULL;

               sStmt = dbmMakeProcForLoopStmt( param,
                                               v3,
                                               DBM_TRUE,
                                               v6,
                                               v8,
                                               v10 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_FOR_LOOP,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_WHILE value_expr TOK_LOOP proc_stmt_list TOK_END TOK_LOOP TOK_SEMICOLON
           {
               dbmParseProcWhileLoopStmt      * sStmt = NULL;

               sStmt = dbmMakeProcWhileLoopStmt( param,
                                                 v3,
                                                 v5 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_WHILE_LOOP,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_GOTO identifier TOK_SEMICOLON
           {
               dbmParseProcGotoStmt      * sStmt = NULL;

               sStmt = dbmMakeProcGotoStmt( param,
                                            v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_GOTO,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_OPEN identifier proc_param_using TOK_SEMICOLON
           {
               dbmParseProcOpenCursorStmt     * sStmt = NULL;

               sStmt = dbmMakeProcOpenCursorStmt( param,
                                                  v3,
                                                  v4 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_OPEN_CURSOR,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_FETCH identifier TOK_INTO identifier_list TOK_SEMICOLON
           {
               dbmParseProcFetchCursorStmt     * sStmt = NULL;

               sStmt = dbmMakeProcFetchCursorStmt( param,
                                                   v3,
                                                   v5 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_FETCH_CURSOR,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_CLOSE identifier TOK_SEMICOLON
           {
               dbmParseProcCloseCursorStmt     * sStmt = NULL;

               sStmt = dbmMakeProcCloseCursorStmt( param,
                                                   v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_CLOSE_CURSOR,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_RAISE proc_raise_item TOK_SEMICOLON
           {
               dbmParseProcRaiseStmt     * sStmt = NULL;

               sStmt = dbmMakeProcRaiseStmt( param,
                                             v3,
                                             NULL,
                                             NULL );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_RAISE,
                                     v1,
                                     sStmt );
 
           }
           | proc_label TOK_RAISE_APPLICATION_ERROR TOK_LEFT_PAREN minus_val TOK_COMMA quote_val TOK_RIGHT_PAREN TOK_SEMICOLON
           {
               dbmParseProcRaiseStmt     * sStmt = NULL;

               sStmt = dbmMakeProcRaiseStmt( param,
                                             NULL,
                                             v4,
                                             v6 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_RAISE,
                                     v1,
                                     sStmt );
           }
           | proc_label identifier proc_param_using TOK_SEMICOLON
           {
               dbmParseProcCallProcStmt     * sStmt = NULL;

               sStmt = dbmMakeProcCallProcStmt( param,
                                                v2,
                                                v3 );

               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_CALL_PROC,
                                     v1,
                                     sStmt );
           }
           | proc_label TOK_COMMIT TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_COMMIT,
                                     v1,
                                     NULL );
           }
           | proc_label TOK_ROLLBACK TOK_SEMICOLON
           {
               v0 = dbmMakeProcStmt( param,
                                     DBM_PROC_STMT_TYPE_ROLLBACK,
                                     v1,
                                     NULL );
           }
           ;


proc_raise_item: /* empty */
                 {
                     v0 = NULL;
                 }
                 | identifier
                 {
                     v0 = v1;
                 }
                 ;


proc_param_using: /* empty */
                 {
                     dbmList       * sList = NULL;
  
                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );
 
                     v0 = sList;
                 }
                 | TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
                 {
                     v0 = v2;
                 }
                 ;



proc_case_when_list: proc_case_when_item
                     {
                         dbmList       * sList = NULL;
  
                         dbmCreateList( param->mAllocator,
                                        &sList,
                                        param->mErrorStack );
  
                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v1,
                                     param->mErrorStack );
    
                         v0 = sList;
                     }
                     | proc_case_when_list proc_case_when_item
                     {
                         dbmList        * sList = (dbmList *)v1;

                         dbmAddList( param->mAllocator,
                                     sList,
                                     DBM_LIST_ELEM_POINTER,
                                     v2,
                                     param->mErrorStack );
 
                          v0 = sList;
                     }
                     ;

                       
proc_case_when_item: TOK_WHEN value_expr TOK_THEN proc_stmt_list
                     {
                         v0 = dbmMakeProcIfItem( param,
                                                 v2,
                                                 v4 );
                     }
                     ;


proc_case_end: TOK_END TOK_CASE
               {
                   v0 = NULL;
               }
               | TOK_ELSE proc_stmt_list TOK_END TOK_CASE
               {
                   v0 = dbmMakeProcIfItem( param,
                                           NULL,
                                           v2 );
               }
               ;
 

proc_exit_stmt: TOK_EXIT TOK_SEMICOLON
                {
                    v0 = dbmMakeProcExitStmt( param,
                                              NULL );
                }
                | TOK_EXIT TOK_WHEN value_expr TOK_SEMICOLON
                {
                    v0 = dbmMakeProcExitStmt( param,
                                              v3 );
                }
                ;


proc_continue_stmt: TOK_CONTINUE TOK_SEMICOLON
                    {
                        v0 = dbmMakeProcContinueStmt( param,
                                                      NULL );
                    } 
                    | TOK_CONTINUE TOK_WHEN value_expr TOK_SEMICOLON
                    {
                        v0 = dbmMakeProcContinueStmt( param,
                                                      v3 );
                    }
                    ;


proc_if_stmt: TOK_IF value_expr TOK_THEN proc_stmt_list proc_else_stmt 
              {
                  dbmParseProcIfItem    * sItem = NULL;

                  sItem = dbmMakeProcIfItem( param,
                                             v2,
                                             v4 );
                  
                  v0 = dbmMakeProcIfStmt( param,
                                          sItem,
                                          NULL,
                                          v5 );
              }
              | TOK_IF value_expr TOK_THEN proc_stmt_list proc_elseif_list proc_else_stmt 
              {
                  dbmParseProcIfItem    * sItem = NULL;

                  sItem = dbmMakeProcIfItem( param,
                                             v2,
                                             v4 );
                  
                  v0 = dbmMakeProcIfStmt( param,
                                          sItem,     // if
                                          v5,        // else if
                                          v6 );      // else
              }
              ;

proc_else_stmt: TOK_END TOK_IF
                {
                    v0 = NULL;
                } 
                | TOK_ELSE proc_stmt_list TOK_END TOK_IF
                {
                    v0 = dbmMakeProcIfItem( param,
                                            NULL,
                                            v2 );
                }
                ;

proc_else_stmt: TOK_ELSIF value_expr TOK_THEN proc_stmt_list
                {
                    v0 = dbmMakeProcIfItem( param,
                                            v2,
                                            v4 );
                }
                ;

proc_elseif_list: proc_else_stmt
                  {
                      dbmList       * sList = NULL;
  
                      dbmCreateList( param->mAllocator,
                                     &sList,
                                     param->mErrorStack );
  
                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_POINTER,
                                  v1,
                                  param->mErrorStack );
 
                      v0 = sList;
                  }
                  | proc_elseif_list proc_else_stmt
                  {
                      dbmList        * sList = (dbmList *)v1;

                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_POINTER,
                                  v2,
                                  param->mErrorStack );
 
                       v0 = sList;
                  }
                  ;


proc_declare_section: declare_proc_item
                      {
                           dbmList       * sList = NULL;
  
                           dbmCreateList( param->mAllocator,
                                          &sList,
                                          param->mErrorStack );
  
                           dbmAddList( param->mAllocator,
                                       sList,
                                       DBM_LIST_ELEM_POINTER,
                                       v1,
                                       param->mErrorStack );
 
                           v0 = sList;
                      }
                      | proc_declare_section declare_proc_item
                      {
                           dbmList        * sList = (dbmList *)v1;
 
                           dbmAddList( param->mAllocator,
                                       sList,
                                       DBM_LIST_ELEM_POINTER,
                                       v2,
                                       param->mErrorStack );
 
                           v0 = sList;
                      }
                      ;



proc_declare_data_type: declare_data_type
                        {
                            v0 = dbmMakeProcDataTypeDef( param,
                                                         DBM_PROC_VAR_TYPE_SCALAR,
                                                         v1 );
                        }
                        | identifier_chain TOK_PERCENT TOK_TYPE
                        {
                            v0 = dbmMakeProcDataTypeDef( param,
                                                         DBM_PROC_VAR_TYPE_TYPE,
                                                         v1 );
                        }
                        | identifier_chain TOK_PERCENT TOK_ROWTYPE
                        {
                            v0 = dbmMakeProcDataTypeDef( param,
                                                         DBM_PROC_VAR_TYPE_ROWTYPE,
                                                         v1 );
                        }
                        ;


declare_proc_item: identifier proc_declare_data_type TOK_SEMICOLON
                   {
                       dbmParseDeclareVar  * sVar = NULL;

                       sVar = dbmMakeProcDeclareVar( param,
                                                     v1,
                                                     v2,
                                                     NULL );
 
                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_VAR,
                                                    sVar );
                   }
                   | identifier proc_declare_data_type TOK_PROC_ASSIGN value_expr TOK_SEMICOLON
                   {
                       dbmParseDeclareVar  * sVar = NULL;

                       sVar = dbmMakeProcDeclareVar( param,
                                                     v1,
                                                     v2,
                                                     v4 );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_VAR,
                                                    sVar );
                   }
                   | TOK_CURSOR identifier proc_cursor_param TOK_IS select_stmt TOK_SEMICOLON
                   {
                       dbmParseDeclareCursor  * sCursor = NULL;

                       sCursor = dbmMakeProcDeclareCursor( param,
                                                           DBM_PROC_VAR_TYPE_CURSOR,
                                                           v2,
                                                           v3, 
                                                           v5 );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_CURSOR,
                                                    sCursor );
                   }
                   | identifier TOK_EXCEPTION TOK_SEMICOLON
                   {
                       dbmParseDeclareException  * sException = NULL;

                       sException = dbmMakeProcDeclareException( param,
                                                                 DBM_PROC_VAR_TYPE_EXCEPTION,
                                                                 v1,
                                                                 NULL );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_EXCEPTION,
                                                    sException );
                   }
                   | TOK_PRAGMA TOK_EXCEPTION_INIT TOK_LEFT_PAREN identifier TOK_COMMA minus_val TOK_RIGHT_PAREN TOK_SEMICOLON
                   {
                       dbmParseDeclareException  * sException = NULL;

                       sException = dbmMakeProcDeclareException( param,
                                                                 DBM_PROC_VAR_TYPE_EXCEPTION_INIT,
                                                                 v4,
                                                                 v6 );

                       v0 = dbmMakeProcDeclareItem( param,
                                                    DBM_PROC_VAR_TYPE_EXCEPTION_INIT,
                                                    sException );
                   }
                   ;


proc_cursor_param: /* Empty */
                   {
                       v0 = NULL;
                   }
                   | TOK_LEFT_PAREN proc_param_section TOK_RIGHT_PAREN
                   {
                       v0 = v2;
                   }
                   ;



proc_param_section: param_item
                    {
                        dbmList       * sList = NULL;
  
                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
  
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    v1,
                                    param->mErrorStack );
 
                        v0 = sList;
                    }
                    | proc_param_section TOK_COMMA param_item
                    {
                        dbmList        * sList = (dbmList *)v1;
 
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_POINTER,
                                    v3,
                                    param->mErrorStack );
 
                        v0 = sList;
                    }
                    ;


param_item: identifier proc_param_in_out proc_declare_data_type
            {
                v0 = dbmMakeParamDef( param,
                                      v1,
                                      v2,
                                      v3 );    
            }
            ;


proc_param_in_out: /* empty */
                   {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_IN );
                   }
                   | TOK_IN
                   {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_IN );
                   }
                   | TOK_OUT
                   {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_OUT );
                   }
                   | TOK_INOUT
                   {
                       v0 = dbmMakeParamInOut( param,
                                               DBM_PARAM_TYPE_INOUT );
                   }
                   ;


int_val: TOK_UINT
         {
             v0 = dbmMakeIntValue( param,
                                   DBM_FALSE,
                                   v1 );
         }
         | minus_val
         {
             v0 = v1;
         }
         ;


minus_val: TOK_MINUS TOK_UINT
           {
               v0 = dbmMakeIntValue( param,
                                     DBM_TRUE,
                                     v2 );
           }
           ;


num_val: TOK_UNUM
         {
             v0 = dbmMakeNumberValue( param,
                                      DBM_FALSE,
                                      v1 );
         }
         | TOK_MINUS TOK_UNUM
         {
             v0 = dbmMakeNumberValue( param,
                                      DBM_TRUE,
                                      v2 );
         }
         ;

identifier: TOK_IDENTIFIER
            {
                v0 = dbmMakeIdentifier( param,
                                        v1 );
            }
            | TOK_OTHERS
            {
                v0 = dbmMakeIdentifier( param,
                                        v1 );
            }
            ;


proc_attrib_var: TOK_SQL TOK_PERCENT proc_attribute
                 {
                     dbmChar          * sVal = (dbmChar *)v1;
                     dbmChar          * sAttr = (dbmChar *)v3;
                     dbmChar          * sStr = NULL;
                     dbmInt32           sLen1 = 0;
                     dbmInt32           sLen2 = 0;
                     
                     sLen1 = dbmStrlen( sVal );
                     sLen2 = dbmStrlen( sAttr );

                     dbmAllocMemory( param->mAllocator,
                                     (sLen1 + sLen2 + 2),
                                     (void **)&sStr,
                                     param->mErrorStack );

                     dbmMemset( sStr, 0x00, (sLen1 + sLen2 + 2) );
                     dbmSnprintf( sStr, (sLen1 + sLen2 + 2), "%s%%%s", sVal, sAttr );

                     v0 = dbmMakeIdentifier( param,
                                             sStr );
                 }
                 | identifier TOK_PERCENT proc_attribute
                 {
                     dbmChar          * sVal = (dbmChar *)((dbmParseValue *)v1)->mValue;
                     dbmChar          * sAttr = (dbmChar *)v3;
                     dbmChar          * sStr = NULL;
                     dbmInt32           sLen1 = 0;
                     dbmInt32           sLen2 = 0;
                     
                     sLen1 = dbmStrlen( sVal );
                     sLen2 = dbmStrlen( sAttr );

                     dbmAllocMemory( param->mAllocator,
                                     (sLen1 + sLen2 + 2),
                                     (void **)&sStr,
                                     param->mErrorStack );

                     dbmMemset( sStr, 0x00, (sLen1 + sLen2 + 2) );
                     dbmSnprintf( sStr, (sLen1 + sLen2 + 2), "%s%%%s", sVal, sAttr );

                     v0 = dbmMakeIdentifier( param,
                                             sStr );
                 }
                 ;

proc_attribute: TOK_ISOPEN
                {
                    v0 = v1;
                }
                | TOK_FOUND
                {
                    v0 = v1;
                }
                | TOK_NOTFOUND
                {
                    v0 = v1;
                }
                | TOK_ROWCOUNT
                {
                    v0 = v1;
                }
                ;


host_variable: TOK_HOST_VARIABLE
               {
                   dbmParseBindParam *sVar = dbmMakeBindParam( param,
                                                               v1 );
                   v0 = sVar;
               }
               ;

dynamic_param: TOK_QUESTION
               {
                    dbmParseBindParam *sVar = dbmMakeBindParam( param,
                                                                NULL );
                    v0 = sVar;
               }
               ;

quote_val: TOK_QUOTE_STRING
            {
                v0 = dbmMakeStrValue( param,
                                      v1 );
            }
            ;


double_quote_val: TOK_DOUBLE_QUOTE_STRING
                  {
                      v0 = dbmMakeIdentifierDoubleQuote( param,
                                                         v1 );
                  }
                  ;




identifier_chain: identifier
                  {
                      dbmList       * sList = NULL;
 
                      dbmCreateList( param->mAllocator,
                                     &sList,
                                     param->mErrorStack );
 
                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_STRING,
                                  v1,
                                  param->mErrorStack );
 
                      v0 = sList;
                  }
                  | identifier_chain TOK_PERIOD identifier
                  {
                      dbmList          * sList = v1;

                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_STRING,
                                  v3,
                                  param->mErrorStack );
                      v0 = sList;
                  }
                  ;



double_quote_chain: double_quote_val
                    {
                        dbmList       * sList = NULL;
   
                        dbmCreateList( param->mAllocator,
                                       &sList,
                                       param->mErrorStack );
   
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v1,
                                    param->mErrorStack );
   
                        v0 = sList;
                    }
                    | double_quote_chain TOK_PERIOD double_quote_val
                    {
                        dbmList          * sList = v1;
  
                        dbmAddList( param->mAllocator,
                                    sList,
                                    DBM_LIST_ELEM_STRING,
                                    v3,
                                    param->mErrorStack );
                        v0 = sList;
                    }
                    ;
  


identifier_list: identifier_chain
                 {
                     dbmList       * sList = NULL;

                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_STRING,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
                 | identifier_list TOK_COMMA identifier_chain
                 {
                     dbmAddList( param->mAllocator,
                                 v1,
                                 DBM_LIST_ELEM_STRING,
                                 v3,
                                 param->mErrorStack );
                     v0 = v1;
                 }
                 ;



value_expr: value_OR
            {
                v0 = v1;
            }
            | value_OR TOK_AS identifier
            {
                dbmParseExpr    * sExpr = v1;
                sExpr->mAlias = v3;
                v0 = sExpr;
            }
            ;


value_expr_list: value_expr
                 {
                     dbmList       * sList = NULL;

                     dbmCreateList( param->mAllocator,
                                    &sList,
                                    param->mErrorStack );

                     dbmAddList( param->mAllocator,
                                 sList,
                                 DBM_LIST_ELEM_POINTER,
                                 v1,
                                 param->mErrorStack );

                     v0 = sList;
                 }
                 | value_expr_list TOK_COMMA value_expr
                 {
                     dbmAddList( param->mAllocator,
                                 v1,
                                 DBM_LIST_ELEM_POINTER,
                                 v3,
                                 param->mErrorStack );
                     v0 = v1;
                 }
                 ;


value_OR: value_AND
          {
              v0 = v1;
          }
          | value_OR TOK_OR value_AND 
          {
               dbmParseFunction * sFunc = NULL;

               sFunc = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_OR,
                                             v1,
                                             v3,
                                             NULL,
                                             NULL );

               v0 = dbmMakeParseExpr( param,
                                      DBM_PARSE_EXPR_FUNCTION,
                                      sFunc );
          }
          | TOK_LEFT_PAREN value_OR TOK_OR value_AND TOK_RIGHT_PAREN
          {
               dbmParseFunction * sFunc = NULL;

               sFunc = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_OR,
                                             v2,
                                             v4,
                                             NULL,
                                             NULL );

               v0 = dbmMakeParseExpr( param,
                                      DBM_PARSE_EXPR_FUNCTION,
                                      sFunc );
          }
          ;


value_AND: value_single
           {
               v0 = v1;              
           }
           | TOK_LEFT_PAREN value_OR TOK_RIGHT_PAREN
           {
               v0 = v2;              
           }
           | value_AND TOK_AND value_AND
           {
               dbmParseFunction * sFunc = NULL;
               sFunc = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_AND,
                                             v1,
                                             v3,
                                             NULL,
                                             NULL );

               v0 = dbmMakeParseExpr( param,
                                      DBM_PARSE_EXPR_FUNCTION,
                                      sFunc );
           }
           ;


value_single: const_value
              {
                 v0 = v1;
              }
              | comp_function
              {
                  v0 = dbmMakeParseExpr( param,
                                         DBM_PARSE_EXPR_FUNCTION,
                                         v1 );
              }
              ;


const_value: identifier_chain
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_IDENTIFIER,
                                        v1 );
             }
             | double_quote_chain
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_IDENTIFIER,
                                        v1 );
             }
             | quote_val
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
             | int_val
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
             | num_val
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
             | host_variable
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_BIND_PARAM,
                                        v1 );
             }
             | dynamic_param
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_BIND_PARAM,
                                        v1 );
             }
             | built_function
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_FUNCTION,
                                        v1 );
             }
             | proc_attrib_var
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_CONST,
                                        v1 );
             }
             | user_lib_function
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_USER_LIB_FUNCTION,
                                        v1 );
             }
             | TOK_NULL
             {
                 v0 = dbmMakeParseExpr( param,
                                        DBM_PARSE_EXPR_NULL,
                                        NULL );
             }
             ;


user_lib_function: identifier_chain TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
                   {
                       v0 = dbmMakeParseUserLibFunction( param,
                                                         v1,
                                                         v3 );
                   }
                   ;


built_function: aggr_function
                {
                    v0 = v1;
                }
                | number_function
                {
                    v0 = v1;
                }
                | TOK_SYSDATE
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_SYSDATE,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | dump_function
                {
                    v0 = v1;
                }
                | mod_function
                {
                    v0 = v1;
                }
                | ceil_function
                {
                    v0 = v1;
                }
                | floor_function
                {
                    v0 = v1;
                }
                | round_function
                {
                    v0 = v1;
                }
                | trunc_function
                {
                    v0 = v1;
                }
                | string_function
                {
                    v0 = v1;
                }
                | length_function
                {
                    v0 = v1;
                }
                | ltrim_function
                {
                    v0 = v1;
                }
                | rtrim_function
                {
                    v0 = v1;
                }
                | TOK_TRIM TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_TRIM,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | lpad_function
                {
                    v0 = v1;
                }
                | rpad_function
                {
                    v0 = v1;
                }
                | substr_function
                {
                    v0 = v1;
                }
                | sequence_function
                {
                    v0 = v1;
                }
                | in_function
                {
                    v0 = v1;
                }
                | hex_function
                {
                    v0 = v1;
                }
                | digest_function
                {
                    v0 = v1;
                }
                | datetime_str_function
                {
                    v0 = v1;
                }
                | random_function
                {
                    v0 = v1;
                }
                | decode_function
                {
                    v0 = v1;
                }
                | upper_function
                {
                    v0 = v1;
                }
                | lower_function
                {
                    v0 = v1;
                }
                | nvl_function
                {
                   v0 = v1;
                }
                | instr_function
                {
                   v0 = v1;
                }
                | TOK_SESSION_ID
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_SESSION_ID,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_JSON_STRING TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_JSON_STRING,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_JSON_STRING TOK_LEFT_PAREN TOK_ASTERISK TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_JSON_STRING,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | to_date_function
                {
                    v0 = v1;
                }
                | to_timestamp_function
                {
                    v0 = v1;
                }
                | TOK_DATEDIFF TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_DATEDIFF,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                | json_function_item
                {
                    v0 = v1;
                }
                | TOK_USERENV TOK_LEFT_PAREN quote_val TOK_RIGHT_PAREN 
                {
                    dbmParseExpr   * s1 = NULL;
                    s1 = dbmMakeParseExpr( param,
                                           DBM_PARSE_EXPR_CONST,
                                           v3 );
 
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_USERENV,
                                               s1,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_EMPTY_BLOB TOK_LEFT_PAREN TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EMPTY_BLOB,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_EMPTY_CLOB TOK_LEFT_PAREN TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EMPTY_CLOB,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_HEXTORAW TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_HEXTORAW,
                                               NULL,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_POWER TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_POWER,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                | TOK_SQRT TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_SQRT,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_EXP TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EXP,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_LN TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LN,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_LOG TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LOG,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                | TOK_REPLACE TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_REPLACE,
                                               v3,
                                               v5,
                                               v7,
                                               NULL );
                }
                ;


instr_function: TOK_INSTR TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_INSTR,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                | TOK_INSTR TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_INSTR,
                                               v3,
                                               v5,
                                               v7,
                                               NULL );
                }
                | TOK_INSTR TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_INSTR,
                                               v3,
                                               v5,
                                               v7,
                                               v9 );
                }
                | TOK_EXTRACT TOK_LEFT_PAREN value_expr TOK_FROM value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_EXTRACT,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                ;


to_date_function: TOK_TO_DATE TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                  {
                      v0 = dbmMakeParseFunction( param,
                                                 DBM_PARSE_FUNCTION_TO_DATE,
                                                 v3,
                                                 NULL,
                                                 NULL,
                                                 NULL );
                  }
                  | TOK_TO_DATE TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                  {
                      v0 = dbmMakeParseFunction( param,
                                                 DBM_PARSE_FUNCTION_TO_DATE,
                                                 v3,
                                                 v5,
                                                 NULL,
                                                 NULL );
                  }
                  ;


to_timestamp_function: TOK_TO_TIMESTAMP TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                       {
                           v0 = dbmMakeParseFunction( param,
                                                      DBM_PARSE_FUNCTION_TO_TIMESTAMP,
                                                      v3,
                                                      NULL,
                                                      NULL,
                                                      NULL );
                       }
                       ;


nvl_function: TOK_NVL TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
              {
                  v0 = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_NVL,
                                             v3,
                                             v5,
                                             NULL,
                                             NULL );
              }
              ;



upper_function: TOK_UPPER TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_UPPER,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                ;


lower_function: TOK_LOWER TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LOWER,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                ;


decode_function: TOK_DECODE TOK_LEFT_PAREN value_expr TOK_COMMA decode_item_list decode_extra_item TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DECODE,
                                                v3,
                                                v5, 
                                                v6,
                                                NULL );
                 }
                 ;

decode_extra_item: /* Empty */
                   {
                       v0 = NULL;
                   }
                   | TOK_COMMA value_expr
                   {
                       v0 = v2;
                   }
                   ;

decode_item_list: decode_item
                  {
                      dbmList       * sList = NULL;

                      dbmCreateList( param->mAllocator,
                                     &sList,
                                     param->mErrorStack );

                      dbmAddList( param->mAllocator,
                                  sList,
                                  DBM_LIST_ELEM_POINTER,
                                  v1,
                                  param->mErrorStack );

                      v0 = sList;
                  }
                  | decode_item_list TOK_COMMA decode_item
                  {
                      dbmAddList( param->mAllocator,
                                  v1,
                                  DBM_LIST_ELEM_POINTER,
                                  v3,
                                  param->mErrorStack );
                      v0 = v1;
                  }
                  ;

decode_item: value_expr TOK_COMMA value_expr
             {
                 v0 = dbmMakeParseDecodeItem( param,
                                              v1, 
                                              v3 );
             }
             ;
                 

random_function: TOK_RANDOM TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_RANDOM,
                                                v3,
                                                v5, 
                                                NULL,
                                                NULL );
                 }
                 ;

datetime_str_function: TOK_DATETIME_STR TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                       {
                           v0 = dbmMakeParseFunction( param,
                                                      DBM_PARSE_FUNCTION_DATETIME_STR,
                                                      v3,
                                                      NULL, 
                                                      NULL, 
                                                      NULL );
                       }
                       ;

ltrim_function: TOK_LTRIM TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LTRIM,
                                               v3,
                                               NULL, 
                                               NULL, 
                                               NULL );
                }
                | TOK_LTRIM TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_LTRIM,
                                               v3,
                                               v5, 
                                               NULL,
                                               NULL );
                }
                ;

rtrim_function: TOK_RTRIM TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_RTRIM,
                                               v3,
                                               NULL, 
                                               NULL, 
                                               NULL );
                }
                | TOK_RTRIM TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_RTRIM,
                                               v3,
                                               v5, 
                                               NULL,
                                               NULL );
                }
                ;


lpad_function: TOK_LPAD TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LPAD,
                                              v3,
                                              v5, 
                                              v7,
                                              NULL );
               }
               ;

rpad_function: TOK_RPAD TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_RPAD,
                                              v3,
                                              v5, 
                                              v7,
                                              NULL );
               }
               ;

length_function: TOK_LENGTH TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_LENGTH,
                                                v3,
                                                NULL,
                                                NULL,
                                                NULL );
                 }
                 ;


digest_function: TOK_DIGEST TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DIGEST,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
                 }
                 ;

hex_function: TOK_HEX TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
              {
                  v0 = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_HEX,
                                             v3,
                                             NULL,
                                             NULL,
                                             NULL );
              }
              ;



in_function: identifier_chain TOK_IN TOK_LEFT_PAREN value_expr_list TOK_RIGHT_PAREN
             {
                 dbmParseExpr * sArg;
                 sArg = dbmMakeParseExpr( param,
                                          DBM_PARSE_EXPR_IDENTIFIER,
                                          v1 );

                 v0 = dbmMakeParseFunction( param,
                                            DBM_PARSE_FUNCTION_IN,
                                            sArg,
                                            v4,
                                            NULL,
                                            NULL );
             }
             ;


string_function: TOK_CONCAT TOK_LEFT_PAREN const_value TOK_COMMA const_value TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_CONCAT,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
                 }
                 | const_value TOK_CONCAT_OPER const_value
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_CONCAT,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
                 ;


substr_function: TOK_SUBSTR TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_SUBSTR,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
                 }
                 |
                 TOK_SUBSTR TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_SUBSTR,
                                                v3,
                                                v5,
                                                v7,
                                                NULL );
                 }
                 ;


dump_function: TOK_DUMP TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DUMP,
                                                v3,
                                                NULL,
                                                NULL,
                                                NULL );
               }
               | TOK_DUMP TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
               {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DUMP,
                                                v3,
                                                v5,
                                                NULL,
                                                NULL );
               }
               ;

mod_function: TOK_MOD TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
              {
                  v0 = dbmMakeParseFunction( param,
                                             DBM_PARSE_FUNCTION_MOD,
                                             v3,
                                             v5,
                                             NULL,
                                             NULL );
              };


ceil_function: TOK_CEIL TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_CEIL,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               };


floor_function: TOK_FLOOR TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_FLOOR,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                };


round_function: TOK_ROUND TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_ROUND,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_ROUND TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_ROUND,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                ;

trunc_function: TOK_TRUNC TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_TRUNC,
                                               v3,
                                               NULL,
                                               NULL,
                                               NULL );
                }
                | TOK_TRUNC TOK_LEFT_PAREN value_expr TOK_COMMA value_expr TOK_RIGHT_PAREN
                {
                    v0 = dbmMakeParseFunction( param,
                                               DBM_PARSE_FUNCTION_TRUNC,
                                               v3,
                                               v5,
                                               NULL,
                                               NULL );
                }
                ;


number_function: const_value TOK_PLUS const_value
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_PLUS,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
                 | TOK_LEFT_PAREN const_value TOK_PLUS const_value TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_PLUS,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
                 | const_value TOK_MINUS const_value
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MINUS,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
                 | TOK_LEFT_PAREN const_value TOK_MINUS const_value TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MINUS,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
                 | const_value TOK_ASTERISK const_value
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MULTIPLE,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
                 | TOK_LEFT_PAREN const_value TOK_ASTERISK const_value TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_MULTIPLE,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
                 | const_value TOK_SOLIDUS const_value
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DIVIDE,
                                                v1,
                                                v3,
                                                NULL,
                                                NULL );
                 }
                 | TOK_LEFT_PAREN const_value TOK_SOLIDUS const_value TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_DIVIDE,
                                                v2,
                                                v4,
                                                NULL,
                                                NULL );
                 }
                 | TOK_ABS TOK_LEFT_PAREN const_value TOK_RIGHT_PAREN
                 {
                     v0 = dbmMakeParseFunction( param,
                                                DBM_PARSE_FUNCTION_ABS,
                                                v3,
                                                NULL,
                                                NULL,
                                                NULL );
                 }
                 ;


aggr_function: TOK_COUNT TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_COUNT,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
               | TOK_COUNT TOK_LEFT_PAREN TOK_ASTERISK TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_COUNT,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL );
               }
               | TOK_SUM TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_SUM,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
               | TOK_AVG TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_AVG,
                                              v3,
                                              v3,
                                              v3,
                                              NULL );
               }
               | TOK_MAX TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_MAXVAL,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
               | TOK_MIN TOK_LEFT_PAREN value_expr TOK_RIGHT_PAREN
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_MINVAL,
                                              v3,
                                              NULL,
                                              NULL,
                                              NULL );
               }
               ;


comp_function: const_value TOK_EQ const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_EQ,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_GE const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_GE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_GT const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_GT,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_LE const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_LT const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LT,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_NE const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_NE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_LIKE const_value
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_LIKE,
                                              v1,
                                              v3,
                                              NULL,
                                              NULL );
               }
               | const_value TOK_IS TOK_NULL
               {
                   v0 = dbmMakeParseFunction( param,
                                              DBM_PARSE_FUNCTION_ISNULL,
                                              v1,
                                              NULL,
                                              NULL,
                                              NULL );
               }
               ;


sequence_function: identifier_chain TOK_PERIOD TOK_NEXTVAL
                   {
                       dbmParseExpr *sExpr = NULL;
                       sExpr = dbmMakeParseExpr( param,
                                                 DBM_PARSE_EXPR_IDENTIFIER,
                                                 v1 );
                       v0 = dbmMakeParseFunction( param,
                                                  DBM_PARSE_FUNCTION_NEXTVAL,
                                                  sExpr,
                                                  NULL,
                                                  NULL,
                                                  NULL );
                   }
                   | identifier_chain TOK_PERIOD TOK_CURRVAL
                   {
                       dbmParseExpr *sExpr = NULL;
                       sExpr = dbmMakeParseExpr( param,
                                                 DBM_PARSE_EXPR_IDENTIFIER,
                                                 v1 );
                       v0 = dbmMakeParseFunction( param,
                                                  DBM_PARSE_FUNCTION_CURRVAL,
                                                  sExpr,
                                                  NULL,
                                                  NULL,
                                                  NULL );
                   }
                   ;

alter_gsb_stmt: create_gsb_node
                {
                    v0 = v1;
                }
                | drop_gsb_node
                {
                    v0 = v1;
                }
                | create_gsb_monitor
                {
                    v0 = v1;
                }
                | drop_gsb_monitor
                {
                    v0 = v1;
                }
                | create_gsb_server_group
                {
                    v0 = v1;
                }
                | drop_gsb_server_group
                {
                    v0 = v1;
                }
                | create_gsb_server
                {
                    v0 = v1;
                }
                | drop_gsb_server
                {
                    v0 = v1;
                }
                | create_gsb_service
                {
                    v0 = v1;
                }
                | drop_gsb_service
                {
                    v0 = v1;
                }
                | alter_gsb_process_count
                {
                    v0 = v1;
                }
                ;

gsb_name : identifier
           {
               v0 = v1;
           }
           ;

gsb_node_name : identifier
                {
                    v0 = v1;
                }
                ;

gsb_server_grp_name : identifier
                {
                    v0 = v1;
                }
                ;


gsb_server_name : identifier
                {
                    v0 = v1;
                }
                ;


gsb_library : quote_val
              {
                  v0 = v1;
              }
              ;


gsb_function : identifier
               {
                   v0 = v1;
               }
               ;

gsb_port : int_val
           {
               v0 = v1;
           }
           ;

gsb_client_min : int_val
                 {
                     v0 = v1;
                 }
                 ;


gsb_client_cnt : int_val
                 {
                     v0 = v1;
                 }
                 ;

gsb_client_max : int_val
                 {
                     v0 = v1;
                 }
                 ;

gsb_process_max : int_val
                  {
                      v0 = v1;
                  }
                  ;


gsb_process_count : int_val
                    {
                        v0 = v1;
                    }
                    ;


gsb_q_size : int_val
             {
                 v0 = v1;
             }
             ;

gsb_influx_ip : quote_val
              {
                  v0 = v1;
              }
              ;

gsb_influx_port : int_val
                {
                    v0 = v1;
                }
                ;

gsb_influx_database : quote_val
                    {
                        v0 = v1;
                    }
                    ;


create_gsb_node: TOK_CREATE TOK_GSB TOK_NODE gsb_name 
                 TOK_LEFT_PAREN 
                 gsb_port TOK_COMMA
                 gsb_client_max TOK_COMMA
                 gsb_process_max
                 TOK_RIGHT_PAREN
                 {
                    v0 = dbmMakeCreateGsbNodeStmt( param, v4, v6, v8, v10 );
                 }
                 ;

drop_gsb_node: TOK_DROP TOK_GSB TOK_NODE gsb_name 
               {
                    v0 = dbmMakeDropGsbNodeStmt( param, v4 );
               }
               ;


create_gsb_monitor: TOK_CREATE TOK_GSB TOK_MONITOR gsb_name
                    TOK_LEFT_PAREN 
                    gsb_node_name TOK_COMMA
                    gsb_influx_ip TOK_COMMA
                    gsb_influx_port TOK_COMMA
                    gsb_influx_database
                    TOK_RIGHT_PAREN
                    {
                       v0 = dbmMakeCreateGsbMonitorStmt( param, v4, v6, v8, v10, v12 );
                    }
                    ;

drop_gsb_monitor: TOK_DROP TOK_GSB TOK_MONITOR gsb_name 
                  {
                       v0 = dbmMakeDropGsbMonitorStmt( param, v4 );
                  }
                  ;


create_gsb_server_group: TOK_CREATE TOK_GSB TOK_SERVER TOK_GROUP gsb_name 
                         TOK_LEFT_PAREN 
                         gsb_node_name
                         TOK_RIGHT_PAREN
                         {
                             v0 = dbmMakeCreateGsbSvrGrpStmt( param, v5, v7 );
                         }
                         ;


drop_gsb_server_group: TOK_DROP TOK_GSB TOK_SERVER TOK_GROUP gsb_name 
                       {
                           v0 = dbmMakeDropGsbSvrGrpStmt( param, v5 );
                       }
                       ;

create_gsb_server: TOK_CREATE TOK_GSB TOK_SERVER gsb_name 
                   TOK_LEFT_PAREN 
                   gsb_server_grp_name TOK_COMMA
                   gsb_client_min TOK_COMMA
                   gsb_client_cnt TOK_COMMA
                   gsb_client_max TOK_COMMA
                   gsb_q_size
                   TOK_RIGHT_PAREN
                   {
                       v0 = dbmMakeCreateGsbSvrStmt( param, v4, v6, v8, v10, v12, v14 );
                   }
                   ;


drop_gsb_server: TOK_DROP TOK_GSB TOK_SERVER gsb_name 
                 {
                     v0 = dbmMakeDropGsbSvrStmt( param, v4 );
                 }
                 ;



create_gsb_service: TOK_CREATE TOK_GSB TOK_SERVICE gsb_name 
                    TOK_LEFT_PAREN 
                    gsb_server_name TOK_COMMA
                    gsb_library TOK_COMMA
                    gsb_function
                    TOK_RIGHT_PAREN
                    {
                        v0 = dbmMakeCreateGsbSvcStmt( param, v4, v6, v8, v10 );
                    }
                    ;


drop_gsb_service: TOK_DROP TOK_GSB TOK_SERVICE gsb_name 
                  {
                      v0 = dbmMakeDropGsbSvcStmt( param, v4 );
                  }
                  ;


alter_gsb_process_count: TOK_ALTER TOK_GSB identifier 
                         TOK_PROCESS TOK_COUNT TOK_EQ gsb_process_count
                         {
                             v0 = dbmMakeAlterGsbProcCntStmt( param, v3, v7 );
                         }
                         ;





%%


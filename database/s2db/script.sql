select * from TABLE_STATISTICS;

show leaf status extended;

select * from information_schema.MV_PROCESSLIST order by state desc;

show variables extended like '%columnstore_segment_rows%';
set global general_log = off;
set global enable_columnstore_ingest_management = ON;
select * From information_schema.mv_global_variables;

show variables like 'columnstore_segment_rows';
set global columnstore_segment_rows = 1024;
set global columnstore_segment_rows = default;

show tables like '%PROCESS%';
SHOW PLANCACHE;

select * from mv_queries;
desc mv_queries;
SELECT 
    QUERY_TEXT,
    START_TIME,
    USER_NAME,
    CLIENT_HOST,
    RUNTIME_MS
FROM 
    information_schema.MV_QUERIES
ORDER BY 
    START_TIME DESC
LIMIT 100;

SELECT 
    USER,
    HOST,
    DB,
    COMMAND,
    TIME,
    STATE,
    INFO
FROM 
    information_schema.PROCESSLIST
WHERE 
    COMMAND != 'Sleep';


select * from SESSION_VARIABLES;
show create table information_schema.columnar_segments;
SNAPSHOT DATABASE test;
select count(*) From test.emp;
select * from test.emp limit 1;

truncate table test.emp;
delete from test.emp;
drop table test.emp;
select 'testxxxx : database page ' from dual;


SHOW STATUS EXTENDED like '%Columnstore_ingest%';
show variables like '%ingest%';
show status extended like '%ingest%';
show tables like '%TABLE_STAT%';
select * From information_schema.TABLE_STATISTICS;

select * from information_schema.MV_PROCESSLIST where node_id = 1 order by state desc; 
show tables like '%PROCESS%';
show status extended like '%PROCE%';
select * From WORKLOAD_MANAGEMENT_QUEUE;

SELECT
        t.table_schema AS databaseName,
        t.table_name AS tableName,
        ANY_VALUE(t.table_type) AS tableType,
        IFNULL(ANY_VALUE(s.partition_type) != "Reference", FALSE) AS isSharded,
        ANY_VALUE(s.storage_type) AS tableStorage
    FROM
        information_schema.tables AS t
        LEFT JOIN information_schema.table_statistics AS s
        ON t.table_schema = s.database_name AND t.table_name = s.table_name
    WHERE t.table_schema like '%'
    GROUP BY
        t.table_schema,
        t.table_name;

SELECT
        DATABASE_NAME AS databaseName,
        TABLE_NAME AS tableName,
        INDEX_NAME AS indexName,
        SUM(COMPRESSED_SIZE) AS totalSize
    FROM
        INFORMATION_SCHEMA.MV_COLUMNAR_SEGMENT_INDEX
    GROUP BY
        DATABASE_NAME,
        TABLE_NAME,
        INDEX_NAME;


        CREATE TABLE query_log (
    id INT AUTO_INCREMENT PRIMARY KEY,
    query_text TEXT,
    user_name VARCHAR(255),
    client_host VARCHAR(255),
    execution_time DATETIME,
    runtime_ms INT
);

DELIMITER //
CREATE TRIGGER log_query AFTER INSERT ON some_table
FOR EACH ROW
BEGIN
    INSERT INTO query_log (query_text, user_name, client_host, execution_time, runtime_ms)
    VALUES (CURRENT_QUERY(), USER(), CURRENT_HOST(), NOW(), QUERY_RUNTIME());
END;
//
DELIMITER ;
[[PageOutline(1-5,Table of Contents, floated)]]

= monitor package =

== wont fix ==

=== 1. 쿼리 계산식 수정 필요함 === before {{{ #!sql lead(STAT_VALUE,1)
over(partition by MEMBER_NAME,STAT_NAME order by int_timestamp) -
STAT_VALUE lag2 }}} after {{{ #!sql STAT_VALUE-lead(STAT_VALUE,-1)
over(partition by MEMBER_NAME,STAT_NAME order by int_timestamp) diff }}}

== Build == wiki:shotgoal_1 == test version ==

goldilocks : 21.1.22\\ mariadb : 10.8.2\\ telegraf : 1.26.0-86cd0c0c (
shotgoal fork version )\\ grafana : 9.3.6\\ == telegraf packages ==
support mariadb output [[BR]]

[raw-attachment:telegraf_1.26.tar.gz:wiki:goya/telegraf
telegraf_1.26.tar.gz]

== initdata.sql ==

{{{ #!sql

DROP TABLE IF EXISTS TELEGRAF_METRIC_SETTINGS; CREATE TABLE
TELEGRAF_METRIC_SETTINGS ( SERIES_NAME VARCHAR (100 )PRIMARY KEY, QUERY
VARCHAR (4000 )NOT NULL, TAGS VARCHAR (1024 )NULL, FIELDS VARCHAR (1024
)NULL, PIVOT_KEY VARCHAR (100 )NULL, PIVOT INT NOT NULL DEFAULT 0 );

DROP TABLE IF EXISTS TELEGRAF_GLOBAL_SETTINGS; CREATE TABLE
TELEGRAF_GLOBAL_SETTINGS ( SETTING_KEY VARCHAR(100) PRIMARY KEY,
SETTING_VALUE INT NOT NULL );

– TELEGRAF_GLOBAL_SETTINGS INSERT INTO TELEGRAF_GLOBAL_SETTINGS VALUES (
‘CLUSTER_MODE’, 0);

– TELEGRAF_METRIC_SETTINGS INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_session_stat’, ‘SELECT \* FROM MONITOR_SESSION_STAT@LOCAL’,
‘CLUSTER_NAME|MEMBER_NAME’,
‘TOTAL_SESSION_COUNT|ACTIVE_SESSION_COUNT|TOTAL_STATEMENT_COUNT|LONG_RUNNING_STATEMENT_COUNT|TOTAL_TRANSACTION_COUNT|LONG_RUNNING_TRANSACTION_COUNT’,
NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_instance_stat’,
‘SELECT \* FROM MONITOR_INSTANCE@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME’,
‘RELEASE_VERSION|STARTUP_TIME_SEC|INSTANCE_STATUS’, NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_sql_stat’,
‘SELECT \* FROM MONITOR_SQL_STAT@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME|STAT_NAME’, ‘STAT_VALUE’, null , 0
FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_cluster_dispatcher_stat’, ‘SELECT \* FROM
MONITOR_CLUSTER_DISPATCHER@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME’,
‘RX_BYTES|TX_BYTES|RX_JOBS|TX_JOBS’, NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_tablespace_stat’, ‘SELECT \* FROM
MONITOR_TABLESPACE_STAT@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME|NAME’,
‘TOTAL_BYTES|USED_BYTES|USED_PCT’, NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_ager_stat’,
‘SELECT \* FROM MONITOR_AGER_STAT@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME’, ‘GLOBAL_GAP|GROUP_GAP|LOCAL_GAP’,
NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_lock_wait’,
‘SELECT \* FROM MONITOR_LOCK_WAIT@LOCAL’,
‘CLUSTER_NAME|GRANTED_MEMBER_NAME|REQUESTED_ID’,
‘GRANTED_ID|GRANTED_SERIAL|GRANTED_PROGRAM|GRANTED_PROCESS_ID|REQUESTED_MEMBER_NAME|REQUESTED_SERIAL|REQUESTED_PROGRAM|REQUESTED_PROCESS_ID’,
NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_cluster_queue_stat’, ‘SELECT \* FROM
MONITOR_CLUSTER_QUEUE@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME|NAME’,
‘QUEUED|QUEUE_SIZE|FULL_COUNT|WAIT_COUNT|TOTALQ|MISS’, NULL, 0 FROM DUAL
;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_cluster_server’,
‘SELECT \* FROM MONITOR_CLUSTER_SERVER@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME|NAME’,
‘PROCESSED_JOBS|NUMA_STREAM_ID|STATUS|DRIVER_SESSION_ID|DRIVER_MEMBER_POS|ENTER_MEMBER_POS’,
NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_transaction_stat’, ‘SELECT \* FROM
MONITOR_TRANSACTION_STAT@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME|STATE’,
‘DRIVER_MEMBER_ID|DRIVER_TRANS_ID|SLOT_ID|USED_UNDO_PAGE_COUNT’, NULL, 0
FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_disk_buffer_stat’, ‘SELECT \* FROM
MONITOR_DISK_BUFFER_STAT@LOCAL’, ‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME’,
‘BUFFER_LOOKUPS|BUFFER_HIT|BUFFER_MISS|TOTAL_WRITES|TOTAL_READS|MOVED_TO_HOT_REGION|MOVED_TO_COLD_REGION|FREE_BUFFER_WAIT|READ_COMPLETE_WAIT’,
NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_scn_stat’,
‘SELECT \* FROM MONITOR_SCN_STAT@LOCAL’,
‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME|NAME’,
‘GLOBAL_SCN|GROUP_SCN|LOCAL_SCN’, NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT ‘goldilocks_mem_stat’,
‘SELECT \* FROM MONITOR_MEM_STAT@LOCAL’,
‘CLUSTER_NAME|MEMBER_NAME|NAME’, ‘TOTAL_MB|USED_MB’, NULL, 0 FROM DUAL ;

INSERT INTO TELEGRAF_METRIC_SETTINGS SELECT
‘goldilocks_plan_cache_stat’, ‘SELECT \* FROM
MONITOR_PLAN_CACHE_STAT@LOCAL’, ‘CLUSTER_NAME|GROUP_NAME|MEMBER_NAME’,
‘TOTAL_MB|USED_MB’, NULL, 0 FROM DUAL ; }}}

== monitoringview.sql == {{{ #!sh

| MONITOR_INSTANCE=” CREATE OR REPLACE VIEW MONITOR_INSTANCE (
  CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , RELEASE_VERSION ,
  STARTUP_TIME_SEC , INSTANCE_STATUS ) AS SELECT ‘$VAR_CLUSTER_NAME’
  CLUSTER_NAME , inst.CLUSTER_GROUP_NAME , inst.CLUSTER_MEMBER_NAME ,
  inst.VERSION
| , DATEDIFF(second,inst.STARTUP_TIME,sysdate)
| , DECODE(inst.STATUS,‘LOCAL OPEN’,1,‘OPEN’,2,NULL) FROM
  FIXED_TABLE_SCHEMA.X$INSTANCE@GLOBAL[IGNORE_INACTIVE_MEMBER] AS inst ;
  ”

MONITOR_SESSION_STAT=” CREATE OR REPLACE VIEW MONITOR_SESSION_STAT (
CLUSTER_NAME , MEMBER_NAME , TOTAL_SESSION_COUNT , ACTIVE_SESSION_COUNT
, BAD_SESSION_COUNT , TOTAL_STATEMENT_COUNT ,
LONG_RUNNING_STATEMENT_COUNT , TOTAL_TRANSACTION_COUNT ,
LONG_RUNNING_TRANSACTION_COUNT ) AS SELECT ‘$VAR_CLUSTER_NAME’
CLUSTER_NAME , X.MEMBER_NAME , TOTAL_SESSION_COUNT ,
ACTIVE_SESSION_COUNT , BAD_SESSION_COUNT , TOTAL_STATEMENT_COUNT ,
NVL(LONG_RUNNING_STATEMENT_COUNT,0) , NVL(TOTAL_TRANSACTION_COUNT,0) ,
NVL(LONG_RUNNING_TRANSACTION_COUNT,0) FROM ( SELECT CLUSTER_MEMBER_NAME
MEMBER_NAME , COUNT(*) TOTAL_SESSION_COUNT , COUNT(CASE WHEN STATUS IN (
‘SIGNALED’, ‘SNIPED’, ‘DEAD’ ) THEN ID END) BAD_SESSION_COUNT FROM
X$SESSION WHERE USER_ID > 0 AND PROGRAM != ‘gmaster’ GROUP BY
CLUSTER_MEMBER_NAME ) X LEFT JOIN ( SELECT CLUSTER_MEMBER_NAME
MEMBER_NAME , COUNT(DISTINCT CASE WHEN X.VIEW_SCN != ‘-1.-1.-1’ THEN
SESSION_ID END) ACTIVE_SESSION_COUNT , COUNT(*) TOTAL_STATEMENT_COUNT ,
COUNT(CASE WHEN DATEDIFF (SECOND, X.START_TIME, SYSTIMESTAMP ) > 5 AND
X.VIEW_SCN != ‘-1.-1.-1’ THEN 1 END) LONG_RUNNING_STATEMENT_COUNT FROM
X$STATEMENT X GROUP BY CLUSTER_MEMBER_NAME ) Y ON x.member_name =
y.member_name LEFT JOIN ( SELECT CLUSTER_MEMBER_NAME MEMBER_NAME ,
COUNT(\*) TOTAL_TRANSACTION_COUNT , COUNT(CASE WHEN ABS(DATEDIFF
(SECOND, X.BEGIN_TIME, SYSTIMESTAMP )) > 5 THEN 1 END)
LONG_RUNNING_TRANSACTION_COUNT FROM X$TRANSACTION X GROUP BY
CLUSTER_MEMBER_NAME ) Z ON Y.MEMBER_NAME=Z.MEMBER_NAME ; ”

MONITOR_TABLESPACE_STAT=” CREATE OR REPLACE VIEW MONITOR_TABLESPACE_STAT
( CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , ATTR , NAME , TOTAL_BYTES ,
USED_BYTES , USED_PCT ) AS SELECT ‘$VAR_CLUSTER_NAME’ CLUSTER_NAME ,
X.G_NAME GROUP_NAME , X.M_NAME MEMBER_NAME , TBS_ATTR , TBS_NAME NAME ,
X.TOTAL_EXT_COUNT \* X.EXT_SIZE TOTAL_BYTES , (X.USED_DATA_EXT_COUNT +
X.USED_META_EXT_COUNT ) \* X.EXT_SIZE USED_BYTES , ROUND (
(X.USED_DATA_EXT_COUNT + X.USED_META_EXT_COUNT ) \* 100/
X.TOTAL_EXT_COUNT , 2) USED_PCT FROM (SELECT CLUSTER_GROUP_NAME G_NAME,
CLUSTER_MEMBER_NAME M_NAME, T.\* FROM X$TABLESPACE_STAT T ) X INNER JOIN
V$TABLESPACE Y ON X.TBS_ID = Y.TBS_ID ; ”

MONITOR_AGER_STAT=” CREATE OR REPLACE VIEW MONITOR_AGER_STAT (
CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , GLOBAL_GAP , GROUP_GAP ,
LOCAL_GAP ) AS SELECT ‘$VAR_CLUSTER_NAME’ , CLUSTER_GROUP_NAME ,
CLUSTER_MEMBER_NAME , TO_NUMBER ( SPLIT_PART( AGABLE_SCN_GAP, ‘.’, 1 ))
, TO_NUMBER ( SPLIT_PART( AGABLE_SCN_GAP, ‘.’, 2 )) , TO_NUMBER (
SPLIT_PART( AGABLE_SCN_GAP, ‘.’, 3 )) FROM
X$AGABLE_INFO@GLOBAL[IGNORE_INACTIVE_MEMBER]; ”

MONITOR_SQL_STAT=” CREATE OR REPLACE VIEW MONITOR_SQL_STAT (
CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , STAT_NAME , STAT_VALUE ) AS
SELECT ‘$VAR_CLUSTER_NAME’ , sysexec.CLUSTER_GROUP_NAME ,
sysexec.CLUSTER_MEMBER_NAME , CAST( sysexec.STMT_TYPE AS VARCHAR(128
OCTETS) ) – STAT_NAME , CAST( sysexec.EXECUTE_COUNT AS NUMBER ) –
STAT_VALUE FROM
FIXED_TABLE_SCHEMA.X$SQL_SYSTEM_STAT_EXEC_STMT@GLOBAL[IGNORE_INACTIVE_MEMBER]
AS sysexec ; ”

MONITOR_CLUSTER_DISPATCHER=” CREATE OR REPLACE VIEW
MONITOR_CLUSTER_DISPATCHER ( CLUSTER_NAME , GROUP_NAME , MEMBER_NAME ,
RX_BYTES , TX_BYTES , RX_JOBS , TX_JOBS ) AS SELECT ‘$VAR_CLUSTER_NAME’
, CLUSTER_GROUP_NAME GROUP_NAME , CLUSTER_MEMBER_NAME MEMBER_NAME , SUM(
RX_BYTES ) , SUM( TX_BYTES ) , SUM( RX_JOBS ) , SUM( TX_JOBS ) FROM
X$CLUSTER_DISPATCHER GROUP BY CLUSTER_GROUP_NAME, CLUSTER_MEMBER_NAME ;
”

| MONITOR_LOCK_WAIT=” CREATE OR REPLACE VIEW MONITOR_LOCK_WAIT (
  CLUSTER_NAME , GRANTED_MEMBER_NAME , GRANTED_ID , GRANTED_SERIAL ,
  GRANTED_PROGRAM , GRANTED_PROCESS_ID , REQUESTED_MEMBER_NAME ,
  REQUESTED_ID , REQUESTED_SERIAL , REQUESTED_PROGRAM ,
  REQUESTED_PROCESS_ID ) AS select
  ‘\ *VAR*\ :sub:`C`\ *LUSTER*\ :sub:`N`\ *AME*\ ′ − −\ *NVLforstandalone*, *x*.\ *cluster*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame*, *x*.\ *id*, *x*.\ *serial*, *x*.\ *program*, *x*.\ *client*\ :sub:`p`\ *rocess*, *y*.\ *request*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame*, *to*\ :sub:`c`\ *har*\ (*y*.\ *id*, ′99999′), *y*.\ *serial*, *y*.\ *program*, *y*.\ *client*\ :sub:`p`\ *rocessfromx*\ $\ *sessionx*, (*select* − −\ *forclusteri*.\ *local*\ :sub:`m`\ *ember*\ :sub:`n`\ *amegranted*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame*, *gs*.\ *driver*\ :sub:`s`\ *ession*\ :sub:`i`\ *d*, *gs*.\ *driver*\ :sub:`s`\ *ession*\ :sub:`s`\ *erial*, *lw*.\ *cluster*\ :sub:`m`\ *ember*\ :sub:`n`\ *amerequest*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame*, *rs*.\ *id*, *rs*.\ *serial*, *rs*.\ *program*, *rs*.\ *client*\ :sub:`p`\ *rocessfromx*\ $\ *sessiongs*, *x*\ $\ *sessionrs*, *x*\ $\ *lock*\ :sub:`w`\ *aitlw*, *x*\ $\ *instanceiwherelw*.\ *cluster*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame* = *gs*.\ *cluster*\ :sub:`m`\ *ember*\ :sub:`n`\ *ameandgs*.\ *id* = *lw*.\ *granted*\ :sub:`t`\ *ransaction*\ :sub:`s`\ *lot*\ :sub:`i`\ *dandrs*.\ *id* = *lw*.\ *request*\ :sub:`t`\ *ransaction*\ :sub:`s`\ *lot*\ :sub:`i`\ *dandgs*.\ *driver*\ :sub:`m`\ *ember*\ :sub:`p`\ *os* = *i*.\ *local*\ :sub:`m`\ *ember*\ :sub:`p`\ *ositionandgs*.\ *driver*\ :sub:`m`\ *ember*\ :sub:`p`\ *os* > 0\ *unionallselect* − −\ *forstandalone*, *andgranted*, *requestonsamemember*\ (*cluster*)\ *NVL*\ (*gs*.\ *cluster*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame*, ′\ VAR_MEMBER_NAME’
  ) , gs.id , gs.serial , NVL( gs.cluster_member_name,
  ‘\ *VAR*\ :sub:`M`\ *EMBER*\ :sub:`N`\ *AME*\ ′), *rs*.\ *id*, *rs*.\ *serial*, *rs*.\ *program*, *rs*.\ *client*\ :sub:`p`\ *rocessfromx*\ $\ *sessiongs*, *x*\ $\ *sessionrs*, *x*\ $\ *lock*\ :sub:`w`\ *aitlwwheregs*.\ *id* = *lw*.\ *granted*\ :sub:`t`\ *ransaction*\ :sub:`s`\ *lot*\ :sub:`i`\ *dandrs*.\ *id* = *lw*.\ *request*\ :sub:`t`\ *ransaction*\ :sub:`s`\ *lot*\ :sub:`i`\ *dandgs*.\ *driver*\ :sub:`m`\ *ember*\ :sub:`p`\ *os* = −1)\ *ywhere* − −\ *NVLforstandaloneNVL*\ (*x*.\ *cluster*\ :sub:`m`\ *ember*\ :sub:`n`\ *ame*, ′\ VAR_MEMBER_NAME’
  ) = NVL( y.granted_member_name , ‘$VAR_MEMBER_NAME' ) and x.id =
  y.driver_session_id and x.serial = y.driver_session_serial and
  x.program != 'cluster peer' and y.program != 'cluster peer' and
  x.program != 'telegraf' and y.program != 'telegraf' ; "
  MONITOR_CLUSTER_QUEUE=" CREATE OR REPLACE VIEW MONITOR_CLUSTER_QUEUE (
  CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , NAME , QUEUED , QUEUE_SIZE ,
  FULL_COUNT , WAIT_COUNT , TOTALQ , MISS ) AS SELECT
  '$VAR_CLUSTER_NAME’ , CLUSTER_GROUP_NAME GROUP_NAME ,
  CLUSTER_MEMBER_NAME MEMBER_NAME , NAME , QUEUED , QUEUE_SIZE ,
  FULL_COUNT , WAIT_COUNT
| , TOTALQ , MISS FROM X$CLUSTER_QUEUE@GLOBAL[IGNORE_INACTIVE_MEMBER] ;
  ”

| MONITOR_CLUSTER_SERVER=” CREATE OR REPLACE VIEW MONITOR_CLUSTER_SERVER
  ( CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , NAME , PROCESSED_JOBS ,
  NUMA_STREAM_ID , STATUS , DRIVER_SESSION_ID
| , DRIVER_MEMBER_POS , ENTER_MEMBER_POS ) AS SELECT ‘$VAR_CLUSTER_NAME’
  , CLUSTER_GROUP_NAME GROUP_NAME , CLUSTER_MEMBER_NAME MEMBER_NAME ,
  NAME , PROCESSED_JOBS , NUMA_STREAM_ID , STATUS , DRIVER_SESSION_ID
| , DRIVER_MEMBER_POS , ENTER_MEMBER_POS FROM
  X$CLUSTER_SERVER@GLOBAL[IGNORE_INACTIVE_MEMBER] ; ”

MONITOR_TRANSACTION_STAT=” CREATE OR REPLACE VIEW
MONITOR_TRANSACTION_STAT ( CLUSTER_NAME , GROUP_NAME , MEMBER_NAME ,
STATE , DRIVER_MEMBER_ID , DRIVER_TRANS_ID , SLOT_ID ,
USED_UNDO_PAGE_COUNT ) AS SELECT ‘$VAR_CLUSTER_NAME’ ,
CLUSTER_GROUP_NAME GROUP_NAME , CLUSTER_MEMBER_NAME MEMBER_NAME , STATE
, DRIVER_MEMBER_ID , DRIVER_TRANS_ID , SLOT_ID , USED_UNDO_PAGE_COUNT
FROM X$TRANSACTION@GLOBAL[IGNORE_INACTIVE_MEMBER] ; ”

| MONITOR_DISK_BUFFER_STAT=” CREATE OR REPLACE VIEW
  MONITOR_DISK_BUFFER_STAT ( CLUSTER_NAME , GROUP_NAME , MEMBER_NAME ,
  BUFFER_LOOKUPS , BUFFER_HIT , BUFFER_MISS , TOTAL_WRITES , TOTAL_READS
| , MOVED_TO_HOT_REGION , MOVED_TO_COLD_REGION , FREE_BUFFER_WAIT ,
  READ_COMPLETE_WAIT ) AS SELECT ‘$VAR_CLUSTER_NAME’ ,
  CLUSTER_GROUP_NAME GROUP_NAME , CLUSTER_MEMBER_NAME MEMBER_NAME ,
  BUFFER_LOOKUPS , BUFFER_HIT , BUFFER_MISS , TOTAL_WRITES , TOTAL_READS
| , MOVED_TO_HOT_REGION , MOVED_TO_COLD_REGION , FREE_BUFFER_WAIT ,
  READ_COMPLETE_WAIT FROM X$BUFFER_STAT@GLOBAL[IGNORE_INACTIVE_MEMBER] ;
  ”

MONITOR_SCN_STAT=” CREATE OR REPLACE VIEW MONITOR_SCN_STAT (
CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , NAME , GLOBAL_SCN , GROUP_SCN
, LOCAL_SCN ) AS SELECT ‘$VAR_CLUSTER_NAME’ , CLUSTER_GROUP_NAME
GROUP_NAME , CLUSTER_MEMBER_NAME MEMBER_NAME , NAME , TO_NUMBER (
SPLIT_PART( VALUE_STR, ‘.’, 1 )) GLOBAL_SCN , TO_NUMBER ( SPLIT_PART(
VALUE_STR, ‘.’, 2 )) GROUP_SCN , TO_NUMBER ( SPLIT_PART( VALUE_STR, ‘.’,
3 )) LOCAL_SCN FROM X$SM_SYSTEM_INFO@GLOBAL[IGNORE_INACTIVE_MEMBER]
WHERE NAME IN (‘GLOBAL_SCN’,‘LOCAL_SCN’) ; ”

MONITOR_MEM_STAT=” CREATE OR REPLACE VIEW MONITOR_MEM_STAT (
CLUSTER_NAME , MEMBER_NAME , NAME , TOTAL_MB , USED_MB ) AS SELECT
‘$VAR_CLUSTER_NAME’, p. *FROM ( SELECT TS.ORIGIN_MEMBER_NAME,
TS.TBS_NAME NAME, TRUNC(SUM(TS.TOTAL_EXT_COUNT* TS.EXTENT_SIZE / 1024 /
1024), 0) TOTAL_MB , TRUNC(SUM(TS.USED_DATA_EXT_COUNT \* TS.EXTENT_SIZE
/ 1024 / 1024), 0) USED_MB FROM
GV$TABLESPACE_STAT@GLOBAL[IGNORE_INACTIVE_MEMBER] TS,
GV$TABLESPACE@GLOBAL[IGNORE_INACTIVE_MEMBER] TBS WHERE
TS.ORIGIN_MEMBER_NAME = TBS.ORIGIN_MEMBER_NAME AND TS.TBS_NAME =
TBS.TBS_NAME AND TBS.TBS_ATTR LIKE ‘MEMORY%’ GROUP BY
TS.ORIGIN_MEMBER_NAME, TS.TBS_NAME

UNION ALL

SELECT X.CLUSTER_MEMBER_NAME, ‘SSA’, ( SELECT TRUNC(P.VALUE / 1024 /
1024, 0) TOTAL_MB FROM X$PROPERTY P WHERE P.PROPERTY_NAME =
‘SHARED_MEMORY_STATIC_SIZE’ AND X.CLUSTER_MEMBER_NAME =
CLUSTER_MEMBER_NAME ) TOTAL_MB , TRUNC(SUM(X.VALUE)/ 1024 / 1024, 0)
USED_MB FROM X$KN_SYSTEM_INFO@GLOBAL[IGNORE_INACTIVE_MEMBER] X WHERE
NAME IN (‘FIXED_STATIC_ALLOC_SIZE’, ‘VARIABLE_STATIC_ALLOC_SIZE’) GROUP
BY CLUSTER_MEMBER_NAME

UNION ALL

::

   SELECT
      XKPS.CLUSTER_MEMBER_NAME MEMBER_NAME,
      'PSA',
      ( SELECT TRUNC(XP.VALUE / 1024 / 1024, 0)
      FROM
          X\$PROPERTY@GLOBAL[IGNORE_INACTIVE_MEMBER] XP
      WHERE
          MEMBER_NAME = CLUSTER_MEMBER_NAME
          AND XP.PROPERTY_NAME = 'PRIVATE_STATIC_AREA_SIZE' ) LIMIT_PSA_PROP,
      ROUND(SUM(XKPS.VALUE)/ 1024 / 1024, 0) ALLOC_PSA_MEGA

FROM X$KN_PROC_STAT@GLOBAL[IGNORE_INACTIVE_MEMBER] XKPS,
X$KN_PROC_ENV@GLOBAL[IGNORE_INACTIVE_MEMBER] XKPE,
X$SESSION@GLOBAL[IGNORE_INACTIVE_MEMBER] XS WHERE 1 = 1 AND
NVL(XKPS.CLUSTER_MEMBER_NAME, ‘STANDALONE’) =
NVL(XKPE.CLUSTER_MEMBER_NAME, ‘STANDALONE’) AND
NVL(XKPS.CLUSTER_MEMBER_NAME, ‘STANDALONE’) =
NVL(XS.CLUSTER_MEMBER_NAME, ‘STANDALONE’) AND
NVL(XKPE.CLUSTER_MEMBER_NAME, ‘STANDALONE’) =
NVL(XS.CLUSTER_MEMBER_NAME, ‘STANDALONE’) AND XKPS.ID = XKPE.ID AND
XKPE.OS_PROC_ID = XS.SERVER_PROCESS AND XS.TOP_LAYER != 12 AND
XS.PROGRAM != ‘CLUSTER PEER’ AND XKPS.NAME LIKE ‘%TOTAL%’ GROUP BY
XKPS.CLUSTER_MEMBER_NAME ) as p ; ”

MONITOR_PLAN_CACHE_STAT=” CREATE OR REPLACE VIEW MONITOR_PLAN_CACHE_STAT
( CLUSTER_NAME , GROUP_NAME , MEMBER_NAME , TOTAL_MB , USED_MB ) AS
SELECT ‘$VAR_CLUSTER_NAME’ CLUSTER_NAME , X.CLUSTER_GROUP_NAME ,
X.CLUSTER_MEMBER_NAME , TRUNC(P.VALUE / 1024 / 1024, 0) TOTAL_MB ,
TRUNC(X.VALUE / 1024 / 1024, 0) USED_MB FROM
X$KN_SYSTEM_INFO@GLOBAL[IGNORE_INACTIVE_MEMBER] X,
X$PROPERTY@GLOBAL[IGNORE_INACTIVE_MEMBER] P WHERE NAME =
‘PLAN_CACHE_TOTAL_SIZE’ AND X.CLUSTER_MEMBER_NAME =
P.CLUSTER_MEMBER_NAME AND P.PROPERTY_NAME = ‘PLAN_CACHE_SIZE’ ; ”

}}} == createview.sh == {{{ #!sh

if [ $# -eq 4 ] then USER=“$1” PWD=“$2” DSN=“$3” VAR_CLUSTER_NAME=“$4”
else echo “Usage : createview.sh ” exit -1 fi

source ./monitoringview.sql

GSQL=“gsqlnet $USER *PWD* − −\ *dsn*\ =\ DSN”

create_view() { $GSQL << EOF > ${DSN}\_$1.log $2 EOF

grep “View created.” ${DSN}\_$1.log > /dev/null

if [ $? -eq 1 ] then printf “ERR” else printf “OK” rm ${DSN}\_$1.log fi

}

ignore_list=“MONITOR_SHARD_TAB_DISTRIBUTION
MONITOR_SHARD_IND_DISTRIBUTION”

for view_name in ``grep CREATE monitoringview.sql | awk '{print $5 }'``
do is_ignore=“FALSE” for ignore in $ignore_list do if [ $view_name =
$ignore ] then is_ignore=“TRUE” break fi

::

   done


   if [ "$is_ignore" = "TRUE" ]
   then
       continue
   fi
   printf "> VIEW : %-35s ... [" $view_name
   create_view $view_name "${!view_name}"
   printf "]\n"

done }}}

== create view == {{{ #!sh

$ sh createview.sh Usage : createview.sh

$ sh createview.sh monitor monitor goldilocks pdb > VIEW :
MONITOR_INSTANCE … [OK] > VIEW : MONITOR_SESSION_STAT … [OK] > VIEW :
MONITOR_TABLESPACE_STAT … [OK] > VIEW : MONITOR_AGER_STAT … [OK] > VIEW
: MONITOR_SQL_STAT … [OK] > VIEW : MONITOR_CLUSTER_DISPATCHER … [OK] >
VIEW : MONITOR_LOCK_WAIT … [OK] > VIEW : MONITOR_CLUSTER_QUEUE … [OK] >
VIEW : MONITOR_CLUSTER_SERVER … [OK] > VIEW : MONITOR_TRANSACTION_STAT …
[OK] > VIEW : MONITOR_DISK_BUFFER_STAT … [OK] > VIEW : MONITOR_SCN_STAT
… [OK] > VIEW : MONITOR_MEM_STAT … [OK] > VIEW : MONITOR_PLAN_CACHE_STAT
… [OK] }}}

== grafana json model == {{{ { “annotations”: { “list”: [ { “builtIn”:
1, “datasource”: { “type”: “datasource”, “uid”: “grafana” }, “enable”:
true, “hide”: true, “iconColor”: “rgba(0, 211, 255, 1)”, “name”:
“Annotations & Alerts”, “target”: { “limit”: 100, “matchAny”: false,
“tags”: [], “type”: “dashboard” }, “type”: “dashboard” } ] },
“editable”: true, “fiscalYearStartMonth”: 0, “graphTooltip”: 0, “id”: 2,
“links”: [], “liveNow”: false, “panels”: [ { “collapsed”: false,
“datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” }, “gridPos”: { “h”:
1, “w”: 24, “x”: 0, “y”: 0 }, “id”: 61, “panels”: [], “targets”: [ {
“datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” }, “refId”: “A” } ],
“title”: “SYSTEM USED”, “type”: “row” }, { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: {
“mode”: “thresholds” }, “decimals”: 2, “displayName”: ““,”mappings”: [],
“thresholds”: { “mode”: “absolute”, “steps”: [ { “color”: “rgba(50, 172,
45, 0.97)”, “value”: null }, { “color”: “rgba(237, 129, 40, 0.89)”,
“value”: 60 }, { “color”: “rgba(245, 54, 54, 0.9)”, “value”: 80 } ] },
“unit”: “percent” }, “overrides”: [ { “matcher”: { “id”: “byName”,
“options”: “Time” }, “properties”: [ { “id”: “displayName”, “value”:
“Time” }, { “id”: “unit”, “value”: “time: YYYY-MM-DD HH:mm:ss” } ] } ]
}, “gridPos”: { “h”: 3, “w”: 6, “x”: 0, “y”: 1 }, “id”: 52, “links”: [],
“options”: { “colorMode”: “background”, “graphMode”: “area”,
“justifyMode”: “auto”, “orientation”: “auto”, “reduceOptions”: {
“calcs”: [ “lastNotNull” ], “fields”: ““,”values”: false }, “textMode”:
“auto” }, “pluginVersion”: “9.3.6”, “targets”: [ { “alias”: “$tag_host",
"dataset": "telegraf", "datasource": { "type": "mysql", "uid":
"QFZ_gIB4k" }, "editorMode": "code", "format": "time_series", "groupBy":
[ { "params": [ "$\__interval” ], “type”: “time” }, { “params”: [ “host”
], “type”: “tag” } ], “hide”: false, “measurement”: “mem”,
“orderByTime”: “DESC”, “policy”: “default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,host,used_percenttelegraf.mem where $\__timeFilter(int_timestamp+
interval 9 hour)\\ngroup by time,host", "refId": "A", "resultFormat":
"time_series", "select": [ [ { "params": [ "used_percent" ], "type":
"field" }, { "params": [], "type": "last" } ] ], "sql": { "columns": [ {
"parameters": [ { "name": "host", "type": "functionParameter" } ],
"type": "function" }, { "parameters": [ { "name": "used_percent",
"type": "functionParameter" } ], "type": "function" } ], "groupBy": [ {
"property": { "name": "host", "type": "string" }, "type": "groupBy" } ],
"limit": 50 }, "table": "mem", "tags": [] } ], "title": "Memory Usage
Percent", "transformations": [], "type": "stat" }, { "datasource": {
"type": "mysql", "uid": "QFZ_gIB4k" }, "fieldConfig": { "defaults": {
"color": { "mode": "palette-classic" }, "custom": { "axisCenteredZero":
false, "axisColorMode": "text", "axisLabel": "", "axisPlacement":
"auto", "barAlignment": 0, "drawStyle": "line", "fillOpacity": 10,
"gradientMode": "none", "hideFrom": { "legend": false, "tooltip": false,
"viz": false }, "lineInterpolation": "linear", "lineWidth": 1,
"pointSize": 5, "scaleDistribution": { "type": "linear" }, "showPoints":
"never", "spanNulls": true, "stacking": { "group": "A", "mode": "none"
}, "thresholdsStyle": { "mode": "off" } }, "mappings": [], "max": 100,
"thresholds": { "mode": "absolute", "steps": [ { "color": "green",
"value": null }, { "color": "red", "value": 80 } ] }, "unit": "percent"
}, "overrides": [] }, "gridPos": { "h": 9, "w": 6, "x": 6, "y": 1 },
"id": 2, "links": [], "options": { "legend": { "calcs": [],
"displayMode": "list", "placement": "bottom", "showLegend": false },
"tooltip": { "mode": "single", "sort": "none" } }, "pluginVersion":
"8.3.0", "targets": [ { "alias": "$tag_host”, “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “groupBy”: [ { “params”: [ “$\__interval” ], “type”:
“time” }, { “params”: [ “host” ], “type”: “tag” }, { “params”: [ “none”
], “type”: “fill” } ], “measurement”: “cpu”, “orderByTime”: “ASC”,
“policy”: “default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,host,100-usage_idletelegraf.cpuwhere $\__timeFilter(int_timestamp+
interval 9 hour)\\ngroup by time,host", "refId": "A", "resultFormat":
"time_series", "select": [ [ { "params": [ "usage_idle" ], "type":
"field" }, { "params": [], "type": "mean" }, { "params": [ "\* -1 +100"
], "type": "math" } ] ], "sql": { "columns": [ { "parameters": [],
"type": "function" } ], "groupBy": [ { "property": { "type": "string" },
"type": "groupBy" } ], "limit": 50 }, "tags": [ { "key": "cpu",
"operator": "=", "value": "cpu-total" } ] } ], "title": "CPU", "type":
"timeseries" }, { "datasource": { "type": "mysql", "uid": "QFZ_gIB4k" },
"fieldConfig": { "defaults": { "color": { "mode": "palette-classic" },
"custom": { "axisCenteredZero": false, "axisColorMode": "text",
"axisLabel": "", "axisPlacement": "auto", "barAlignment": 0,
"drawStyle": "line", "fillOpacity": 10, "gradientMode": "none",
"hideFrom": { "legend": false, "tooltip": false, "viz": false },
"lineInterpolation": "linear", "lineWidth": 1, "pointSize": 5,
"scaleDistribution": { "type": "linear" }, "showPoints": "never",
"spanNulls": true, "stacking": { "group": "A", "mode": "none" },
"thresholdsStyle": { "mode": "off" } }, "mappings": [], "thresholds": {
"mode": "absolute", "steps": [ { "color": "green", "value": null }, {
"color": "red", "value": 80 } ] }, "unit": "bytes" }, "overrides": [] },
"gridPos": { "h": 9, "w": 6, "x": 12, "y": 1 }, "id": 7, "links": [],
"options": { "legend": { "calcs": [ "mean", "max" ], "displayMode":
"list", "placement": "right", "showLegend": false }, "tooltip": {
"mode": "single", "sort": "none" } }, "pluginVersion": "8.3.0",
"targets": [ { "alias": "$tag_host.$tag_interface", "datasource": {
"type": "mysql", "uid": "QFZ_gIB4k" }, "editorMode": "code", "format":
"time_series", "groupBy": [ { "params": [ "$\__interval” ], “type”:
“time” }, { “params”: [ “host” ], “type”: “tag” }, { “params”: [
“interface” ], “type”: “tag” }, { “params”: [ “null” ], “type”: “fill” }
], “hide”: false, “measurement”: “net”, “orderByTime”: “ASC”, “policy”:
“default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,host,interface,lead(bytes_sent,1) over(partition by host,interface
order by int_timestamp) - bytes_sent send,lead(bytes_recv,1)
over(partition by host,interface order by int_timestamp) - bytes_recv
recvtelegraf.net where $\__timeFilter(int_timestamp+ interval 9
hour)\\ngroup by time,host,interface\\n", "refId": "A", "resultFormat":
"time_series", "select": [ [ { "params": [ "bytes_recv" ], "type":
"field" }, { "params": [], "type": "mean" }, { "params": [ "1s" ],
"type": "derivative" } ] ], "sql": { "columns": [ { "parameters": [],
"type": "function" } ], "groupBy": [ { "property": { "type": "string" },
"type": "groupBy" } ], "limit": 50 } } ], "title": "NETWORK", "type":
"timeseries" }, { "datasource": { "type": "mysql", "uid": "QFZ_gIB4k" },
"fieldConfig": { "defaults": { "color": { "mode": "palette-classic" },
"custom": { "axisCenteredZero": false, "axisColorMode": "text",
"axisLabel": "", "axisPlacement": "auto", "barAlignment": 0,
"drawStyle": "line", "fillOpacity": 10, "gradientMode": "none",
"hideFrom": { "legend": false, "tooltip": false, "viz": false },
"lineInterpolation": "linear", "lineWidth": 1, "pointSize": 5,
"scaleDistribution": { "type": "linear" }, "showPoints": "never",
"spanNulls": true, "stacking": { "group": "A", "mode": "none" },
"thresholdsStyle": { "mode": "off" } }, "mappings": [], "thresholds": {
"mode": "absolute", "steps": [ { "color": "green", "value": null }, {
"color": "red", "value": 80 } ] }, "unit": "bytes" }, "overrides": [] },
"gridPos": { "h": 9, "w": 6, "x": 18, "y": 1 }, "id": 31, "links": [],
"options": { "legend": { "calcs": [], "displayMode": "list",
"placement": "bottom", "showLegend": false }, "tooltip": { "mode":
"single", "sort": "none" } }, "pluginVersion": "8.3.0", "targets": [ {
"alias": "$tag_host.$tag_name.READ", "datasource": { "type": "mysql",
"uid": "QFZ_gIB4k" }, "editorMode": "code", "format": "time_series",
"groupBy": [ { "params": [ "$\__interval” ], “type”: “time” }, {
“params”: [ “host” ], “type”: “tag” }, { “params”: [ “name” ], “type”:
“tag” }, { “params”: [ “none” ], “type”: “fill” } ], “measurement”:
“diskio”, “orderByTime”: “ASC”, “policy”: “default”, “rawQuery”: true,
“rawSql”: “SELECT$\__timeGroup(int_timestamp + interval 9
hour,‘1m’,previous) time,host,name,lead(write_bytes,1) over(partition by
host,name order by int_timestamp) - write_bytes
writeb,lead(read_bytes,1) over(partition by host,name order by
int_timestamp) - read_bytes difftelegraf.diskiowhere
$\__timeFilter(int_timestamp+ interval 9 hour)\\ngroup by
time,host,name", "refId": "A", "resultFormat": "time_series", "select":
[ [ { "params": [ "read_bytes" ], "type": "field" }, { "params": [],
"type": "mean" }, { "params": [ "1s" ], "type":
"non_negative_derivative" } ] ], "sql": { "columns": [ { "parameters":
[], "type": "function" } ], "groupBy": [ { "property": { "type":
"string" }, "type": "groupBy" } ], "limit": 50 }, "tags": [] } ],
"title": "DISK IO", "type": "timeseries" }, { "datasource": { "type":
"mysql", "uid": "QFZ_gIB4k" }, "fieldConfig": { "defaults": { "color": {
"mode": "thresholds" }, "decimals": 2, "displayName": "", "mappings":
[], "thresholds": { "mode": "absolute", "steps": [ { "color": "rgba(50,
172, 45, 0.97)", "value": null }, { "color": "rgba(237, 129, 40, 0.89)",
"value": 60 }, { "color": "rgba(245, 54, 54, 0.9)", "value": 80 } ] },
"unit": "percent" }, "overrides": [ { "matcher": { "id": "byName",
"options": "Time" }, "properties": [ { "id": "displayName", "value":
"Time" }, { "id": "unit", "value": "time: YYYY-MM-DD HH:mm:ss" } ] } ]
}, "gridPos": { "h": 6, "w": 6, "x": 0, "y": 4 }, "id": 74, "links": [],
"options": { "colorMode": "background", "graphMode": "area",
"justifyMode": "auto", "orientation": "auto", "reduceOptions": {
"calcs": [ "lastNotNull" ], "fields": "", "values": false }, "textMode":
"auto" }, "pluginVersion": "9.3.6", "targets": [ { "alias": "$tag_host”,
“dataset”: “telegraf”, “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “editorMode”: “code”, “format”: “time_series”, “groupBy”:
[ { “params”: [ “$\__interval” ], “type”: “time” }, { “params”: [ “host”
], “type”: “tag” } ], “hide”: false, “measurement”: “mem”,
“orderByTime”: “DESC”, “policy”: “default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,host,used_percent,pathtelegraf.diskwhere
$\__timeFilter(int_timestamp+ interval 9 hour)\\ngroup by
time,host,path\\t", "refId": "A", "resultFormat": "time_series",
"select": [ [ { "params": [ "used_percent" ], "type": "field" }, {
"params": [], "type": "last" } ] ], "sql": { "columns": [ {
"parameters": [ { "name": "host", "type": "functionParameter" } ],
"type": "function" }, { "parameters": [ { "name": "used_percent",
"type": "functionParameter" } ], "type": "function" } ], "groupBy": [ {
"property": { "name": "host", "type": "string" }, "type": "groupBy" } ],
"limit": 50 }, "table": "mem", "tags": [] } ], "title": "Disk Usage
Percent", "transformations": [], "type": "stat" }, { "collapsed": false,
"datasource": { "type": "mysql", "uid": "QFZ_gIB4k" }, "gridPos": { "h":
1, "w": 24, "x": 0, "y": 10 }, "id": 59, "panels": [], "targets": [ {
"datasource": { "type": "mysql", "uid": "QFZ_gIB4k" }, "refId": "A" } ],
"title": "GOLDILOCKS DB", "type": "row" }, { "datasource": { "type":
"mysql", "uid": "QFZ_gIB4k" }, "fieldConfig": { "defaults": { "color": {
"mode": "continuous-GrYlRd" }, "mappings": [ { "options": { "0": {
"color": "red", "index": 2, "text": "CLOSE" }, "1": { "color": "orange",
"index": 1, "text": "LOCAL OPEN" }, "2": { "color": "green", "index": 0,
"text": "OPEN" } }, "type": "value" } ], "thresholds": { "mode":
"absolute", "steps": [ { "color": "green", "value": null }, { "color":
"red", "value": 80 } ] } }, "overrides": [] }, "gridPos": { "h": 2, "w":
24, "x": 0, "y": 11 }, "id": 67, "options": { "colorMode": "background",
"graphMode": "none", "justifyMode": "auto", "orientation": "auto",
"reduceOptions": { "calcs": [ "lastNotNull" ], "fields": "", "values":
false }, "textMode": "auto" }, "pluginVersion": "9.3.6", "targets": [ {
"alias": "$tag_MEMBER_NAME”, “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “editorMode”: “code”, “format”: “time_series”, “groupBy”:
[ { “params”: [ “10s” ], “type”: “time” }, { “params”: [ “MEMBER_NAME”
], “type”: “tag” }, { “params”: [ “null” ], “type”: “fill” } ],
“measurement”: “monitor_open”, “orderByTime”: “ASC”, “policy”:
“default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,cluster_name,MEMBER_NAME,INSTANCE_STATUS
valuetelegraf.goldilocks_instance_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by
time,cluster_name,MEMBER_NAME”, “refId”: “A”, “resultFormat”:
“time_series”, “select”: [ [ { “params”: [ “STATUS” ], “type”: “field”
}, { “params”: [], “type”: “last” } ] ], “sql”: { “columns”: [ {
“parameters”: [], “type”: “function” } ], “groupBy”: [ { “property”: {
“type”: “string” }, “type”: “groupBy” } ], “limit”: 50 }, “tags”: [] }
], “title”: “Open Status”, “type”: “stat” }, { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: {
“mode”: “palette-classic” }, “custom”: { “axisCenteredZero”: false,
“axisColorMode”: “text”, “axisLabel”: ““,”axisPlacement”: “auto”,
“barAlignment”: 0, “drawStyle”: “line”, “fillOpacity”: 0,
“gradientMode”: “none”, “hideFrom”: { “legend”: false, “tooltip”: false,
“viz”: false }, “lineInterpolation”: “linear”, “lineWidth”: 1,
“pointSize”: 5, “scaleDistribution”: { “type”: “linear” }, “showPoints”:
“auto”, “spanNulls”: false, “stacking”: { “group”: “A”, “mode”: “none”
}, “thresholdsStyle”: { “mode”: “off” } }, “mappings”: [], “thresholds”:
{ “mode”: “absolute”, “steps”: [ { “color”: “green”, “value”: null }, {
“color”: “red”, “value”: 80 } ] } }, “overrides”: [] }, “gridPos”: {
“h”: 6, “w”: 11, “x”: 0, “y”: 13 }, “id”: 81, “options”: { “legend”: {
“calcs”: [], “displayMode”: “list”, “placement”: “bottom”, “showLegend”:
false }, “tooltip”: { “mode”: “single”, “sort”: “none” } },
“pluginVersion”: “9.3.6”, “targets”: [ { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,TOTAL_SESSION_COUNTtelegraf.goldilocks_session_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by time,MEMBER_NAME”,
“refId”: “A”, “sql”: { “columns”: [ { “parameters”: [], “type”:
“function” } ], “groupBy”: [ { “property”: { “type”: “string” }, “type”:
“groupBy” } ], “limit”: 50 } } ], “title”: “Total Session Count”,
“type”: “timeseries” }, { “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: { “mode”:
“palette-classic” }, “custom”: { “axisCenteredZero”: false,
“axisColorMode”: “text”, “axisLabel”: ““,”axisPlacement”: “auto”,
“barAlignment”: 0, “drawStyle”: “line”, “fillOpacity”: 0,
“gradientMode”: “none”, “hideFrom”: { “legend”: false, “tooltip”: false,
“viz”: false }, “lineInterpolation”: “linear”, “lineWidth”: 1,
“pointSize”: 5, “scaleDistribution”: { “type”: “linear” }, “showPoints”:
“auto”, “spanNulls”: false, “stacking”: { “group”: “A”, “mode”: “none”
}, “thresholdsStyle”: { “mode”: “off” } }, “mappings”: [], “thresholds”:
{ “mode”: “absolute”, “steps”: [ { “color”: “green”, “value”: null }, {
“color”: “red”, “value”: 80 } ] } }, “overrides”: [] }, “gridPos”: {
“h”: 6, “w”: 13, “x”: 11, “y”: 13 }, “id”: 92, “options”: { “legend”: {
“calcs”: [], “displayMode”: “list”, “placement”: “bottom”, “showLegend”:
false }, “tooltip”: { “mode”: “single”, “sort”: “none” } },
“pluginVersion”: “9.3.6”, “targets”: [ { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,TOTAL_STATEMENT_COUNTtelegraf.goldilocks_session_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)\\ngroup by
time,MEMBER_NAME", "refId": "A", "sql": { "columns": [ { "parameters":
[], "type": "function" } ], "groupBy": [ { "property": { "type":
"string" }, "type": "groupBy" } ], "limit": 50 } } ], "title": "Total
Statement Count", "type": "timeseries" }, { "datasource": { "type":
"mysql", "uid": "QFZ_gIB4k" }, "fieldConfig": { "defaults": { "color": {
"mode": "palette-classic" }, "custom": { "axisCenteredZero": false,
"axisColorMode": "text", "axisLabel": "", "axisPlacement": "auto",
"barAlignment": 0, "drawStyle": "line", "fillOpacity": 0,
"gradientMode": "none", "hideFrom": { "legend": false, "tooltip": false,
"viz": false }, "lineInterpolation": "smooth", "lineWidth": 1,
"pointSize": 5, "scaleDistribution": { "type": "linear" }, "showPoints":
"auto", "spanNulls": false, "stacking": { "group": "A", "mode": "none"
}, "thresholdsStyle": { "mode": "off" } }, "mappings": [], "thresholds":
{ "mode": "absolute", "steps": [ { "color": "green", "value": null }, {
"color": "red", "value": 80 } ] } }, "overrides": [] }, "gridPos": {
"h": 12, "w": 11, "x": 0, "y": 19 }, "id": 75, "links": [], "options": {
"legend": { "calcs": [], "displayMode": "list", "placement": "bottom",
"showLegend": true }, "tooltip": { "mode": "single", "sort": "none" } },
"pluginVersion": "9.3.6", "targets": [ { "alias":
"$tag_MEMBER_NAME.$tag_STAT_NAME", "dataset": "telegraf", "datasource":
{ "type": "mysql", "uid": "QFZ_gIB4k" }, "editorMode": "code", "format":
"time_series", "groupBy": [ { "params": [ "$\__interval” ], “type”:
“time” }, { “params”: [ “STAT_NAME” ], “type”: “tag” }, { “params”: [
“MEMBER_NAME” ], “type”: “tag” }, { “params”: [ “none” ], “type”: “fill”
} ], “hide”: false, “measurement”: “monitor_sql_stat”, “orderByTime”:
“ASC”, “policy”: “default”, “query”: “SELECT
non_negative_derivative(mean("STAT_VALUE"), 1s) FROM "monitor_sql_stat"
WHERE ("STAT_NAME" = ‘SELECT’) AND
*timeFilterGROUPBYtime*\ (\ \__interval), "STAT_NAME", "MEMBER_NAME"
fill(none)“,”rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,STAT_NAME,lead(STAT_VALUE,1) over(partition by
MEMBER_NAME,STAT_NAME order by int_timestamp) -STAT_VALUE
difftelegraf.goldilocks_sql_statwhere $\__timeFilter(int_timestamp+
interval 9 hour)\\ngroup by time,MEMBER_NAME,STAT_NAME\\n", "refId":
"A", "resultFormat": "time_series", "select": [ [ { "params": [
"STAT_VALUE" ], "type": "field" }, { "params": [], "type": "mean" }, {
"params": [ "1s" ], "type": "non_negative_derivative" } ] ], "sql": {
"columns": [ { "alias": "\\"time\\"", "parameters": [ { "name":
"int_timestamp", "type": "functionParameter" } ], "type": "function" },
{ "parameters": [ { "name": "MEMBER_NAME", "type": "functionParameter" }
], "type": "function" }, { "parameters": [ { "name": "STAT_NAME",
"type": "functionParameter" } ], "type": "function" }, { "alias":
"\\"value\\"", "parameters": [ { "name": "STAT_VALUE", "type":
"functionParameter" } ], "type": "function" } ], "groupBy": [ {
"property": { "name": "int_timestamp", "type": "string" }, "type":
"groupBy" }, { "property": { "name": "MEMBER_NAME", "type": "string" },
"type": "groupBy" }, { "property": { "name": "STAT_NAME", "type":
"string" }, "type": "groupBy" } ], "orderBy": { "property": { "name": [
"int_timestamp" ], "type": "string" }, "type": "property" },
"orderByDirection": "ASC", "whereJsonTree": { "children1": [ { "id":
"9aa998aa-4567-489a-bcde-f187225d28ab", "properties": { "field":
"STAT_NAME", "operator": "equal", "value": [ "SELECT" ], "valueSrc": [
"value" ], "valueType": [ "text" ] }, "type": "rule" } ], "id":
"8ba89ab9-89ab-4cde-b012-3187224f774c", "type": "group" },
"whereString": "STAT_NAME = 'SELECT'" }, "table": "goldilocks_sql_stat",
"tags": [ { "condition": "AND", "key": "STAT_NAME", "operator": "=~",
"value": "/^SELECT.*/" }, { "condition": "AND", "key": "STAT_NAME",
"operator": "!=", "value": "SELECT .. INTO .. FOR UPDATE" } ] } ],
"title": "SQL Stat", "transformations": [], "type": "timeseries" }, {
"datasource": { "type": "mysql", "uid": "QFZ_gIB4k" }, "fieldConfig": {
"defaults": { "color": { "mode": "palette-classic" }, "custom": {
"axisCenteredZero": false, "axisColorMode": "text", "axisLabel": "",
"axisPlacement": "auto", "barAlignment": 0, "drawStyle": "line",
"fillOpacity": 10, "gradientMode": "none", "hideFrom": { "legend":
false, "tooltip": false, "viz": false }, "lineInterpolation": "linear",
"lineWidth": 1, "pointSize": 5, "scaleDistribution": { "type": "linear"
}, "showPoints": "never", "spanNulls": true, "stacking": { "group": "A",
"mode": "none" }, "thresholdsStyle": { "mode": "off" } }, "mappings":
[], "max": 100, "min": 0, "thresholds": { "mode": "absolute", "steps": [
{ "color": "green", "value": null }, { "color": "red", "value": 80 } ]
}, "unit": "percent" }, "overrides": [] }, "gridPos": { "h": 12, "w": 7,
"x": 11, "y": 19 }, "id": 48, "links": [], "options": { "legend": {
"calcs": [], "displayMode": "table", "placement": "right", "showLegend":
false }, "tooltip": { "mode": "single", "sort": "none" } },
"pluginVersion": "8.3.0", "targets": [ { "alias":
"$tag_MEMBER_NAME.$tag_TABLESPACE_NAME", "datasource": { "type":
"mysql", "uid": "QFZ_gIB4k" }, "editorMode": "code", "format":
"time_series", "groupBy": [ { "params": [ "$\__interval” ], “type”:
“time” }, { “params”: [ “MEMBER_NAME” ], “type”: “tag” }, { “params”: [
“TABLESPACE_NAME” ], “type”: “tag” }, { “params”: [ “none” ], “type”:
“fill” } ], “measurement”: “monitor_tablespace”, “orderByTime”: “ASC”,
“policy”: “default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,member_name,NAME,USED_PCTtelegraf.goldilocks_tablespace_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by time,member_name,name”,
“refId”: “A”, “resultFormat”: “time_series”, “select”: [ [ { “params”: [
“USE_PERCENTAGE” ], “type”: “field” }, { “params”: [], “type”: “mean” }
] ], “sql”: { “columns”: [ { “parameters”: [], “type”: “function” } ],
“groupBy”: [ { “property”: { “type”: “string” }, “type”: “groupBy” } ],
“limit”: 50 }, “tags”: [ { “condition”: “AND”, “key”: “TABLESPACE_NAME”,
“operator”: “=”, “value”: “UAP_DAT” } ] } ], “title”: “Tablespace”,
“type”: “timeseries” }, { “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: { “mode”:
“palette-classic” }, “custom”: { “hideFrom”: { “legend”: false,
“tooltip”: false, “viz”: false } }, “mappings”: [], “unit”: “decmbytes”
}, “overrides”: [ { “\__systemRef”: “hideSeriesFrom”, “matcher”: { “id”:
“byNames”, “options”: { “mode”: “exclude”, “names”: [ “used_mb
{member_name="G1N1", name="PSA"}”, “used_mb {member_name="G1N1",
name="DICTIONARY_TBS"}”, “used_mb {member_name="G1N1", name="SSA"}”,
“used_mb {member_name="G1N1", name="MEM_UNDO_TBS"}”, “used_mb
{member_name="G1N1", name="MEM_TEMP_TBS"}”, “used_mb
{member_name="G1N1", name="MEM_DATA_TBS"}” ], “prefix”: “All except:”,
“readOnly”: true } }, “properties”: [ { “id”: “custom.hideFrom”,
“value”: { “legend”: false, “tooltip”: false, “viz”: false } } ] } ] },
“gridPos”: { “h”: 12, “w”: 6, “x”: 18, “y”: 19 }, “id”: 79, “options”: {
“displayLabels”: [ “percent” ], “legend”: { “displayMode”: “list”,
“placement”: “bottom”, “showLegend”: true, “values”: [] }, “pieType”:
“pie”, “reduceOptions”: { “calcs”: [ “lastNotNull” ], “fields”:
““,”values”: false }, “tooltip”: { “mode”: “single”, “sort”: “none” } },
“pluginVersion”: “9.3.6”, “targets”: [ { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,member_name,name,used_mbtelegraf.goldilocks_mem_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)\\n and member_name =
'$member_name’by time,member_name,name”, “refId”: “A”, “sql”: {
“columns”: [ { “parameters”: [], “type”: “function” } ], “groupBy”: [ {
“property”: { “type”: “string” }, “type”: “groupBy” } ], “limit”: 50 } }
], “title”: “Memory Usage”, “type”: “piechart” }, { “datasource”: {
“type”: “mysql”, “uid”: “QFZ_gIB4k” }, “fieldConfig”: { “defaults”: {
“color”: { “mode”: “palette-classic” }, “custom”: { “axisCenteredZero”:
false, “axisColorMode”: “text”, “axisLabel”: ““,”axisPlacement”: “auto”,
“barAlignment”: 0, “drawStyle”: “line”, “fillOpacity”: 10,
“gradientMode”: “none”, “hideFrom”: { “legend”: false, “tooltip”: false,
“viz”: false }, “lineInterpolation”: “linear”, “lineWidth”: 1,
“pointSize”: 5, “scaleDistribution”: { “type”: “linear” }, “showPoints”:
“never”, “spanNulls”: true, “stacking”: { “group”: “A”, “mode”: “none”
}, “thresholdsStyle”: { “mode”: “off” } }, “mappings”: [], “thresholds”:
{ “mode”: “absolute”, “steps”: [ { “color”: “green”, “value”: null }, {
“color”: “red”, “value”: 80 } ] }, “unit”: “short” }, “overrides”: [] },
“gridPos”: { “h”: 8, “w”: 6, “x”: 0, “y”: 31 }, “id”: 86, “links”: [],
“options”: { “legend”: { “calcs”: [], “displayMode”: “list”,
“placement”: “bottom”, “showLegend”: false }, “tooltip”: { “mode”:
“single”, “sort”: “none” } }, “pluginVersion”: “8.3.0”, “targets”: [ {
“alias”: “$tag_host", "datasource": { "type": "mysql", "uid":
"QFZ_gIB4k" }, "editorMode": "code", "format": "time_series", "groupBy":
[ { "params": [ "$\__interval” ], “type”: “time” }, { “params”: [ “host”
], “type”: “tag” }, { “params”: [ “none” ], “type”: “fill” } ],
“measurement”: “monitor_session_stat”, “orderByTime”: “ASC”, “policy”:
“default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,STATE,COUNT(\*)
cnttelegraf.goldilocks_transaction_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)\\ngroup by
time,MEMBER_NAME,STATE\\n", "refId": "A", "resultFormat": "time_series",
"select": [ [ { "params": [ "LOCK_WAIT_COUNT" ], "type": "field" }, {
"params": [], "type": "mean" } ] ], "sql": { "columns": [ {
"parameters": [], "type": "function" } ], "groupBy": [ { "property": {
"type": "string" }, "type": "groupBy" } ], "limit": 50 }, "tags": [] }
], "title": "Transaction Status", "type": "timeseries" }, {
"datasource": { "type": "mysql", "uid": "QFZ_gIB4k" }, "fieldConfig": {
"defaults": { "color": { "mode": "palette-classic" }, "custom": {
"axisCenteredZero": false, "axisColorMode": "text", "axisLabel": "",
"axisPlacement": "auto", "barAlignment": 0, "drawStyle": "line",
"fillOpacity": 10, "gradientMode": "none", "hideFrom": { "legend":
false, "tooltip": false, "viz": false }, "lineInterpolation": "linear",
"lineWidth": 1, "pointSize": 5, "scaleDistribution": { "type": "linear"
}, "showPoints": "never", "spanNulls": true, "stacking": { "group": "A",
"mode": "none" }, "thresholdsStyle": { "mode": "off" } }, "mappings":
[], "thresholds": { "mode": "absolute", "steps": [ { "color": "green",
"value": null }, { "color": "red", "value": 80 } ] }, "unit": "short" },
"overrides": [] }, "gridPos": { "h": 8, "w": 5, "x": 6, "y": 31 }, "id":
45, "links": [], "options": { "legend": { "calcs": [], "displayMode":
"list", "placement": "bottom", "showLegend": false }, "tooltip": {
"mode": "single", "sort": "none" } }, "pluginVersion": "8.3.0",
"targets": [ { "alias": "$tag_host”, “datasource”: { “type”: “mysql”,
“uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”: “time_series”,
“groupBy”: [ { “params”: [ “$\__interval” ], “type”: “time” }, {
“params”: [ “host” ], “type”: “tag” }, { “params”: [ “none” ], “type”:
“fill” } ], “measurement”: “monitor_session_stat”, “orderByTime”: “ASC”,
“policy”: “default”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,GRANTED_MEMBER_NAME,count(\*)
lock_cnttelegraf.goldilocks_lock_waitwhere $\__timeFilter(int_timestamp+
interval 9 hour)by time,GRANTED_MEMBER_NAME”, “refId”: “A”,
“resultFormat”: “time_series”, “select”: [ [ { “params”: [
“LOCK_WAIT_COUNT” ], “type”: “field” }, { “params”: [], “type”: “mean” }
] ], “sql”: { “columns”: [ { “parameters”: [], “type”: “function” } ],
“groupBy”: [ { “property”: { “type”: “string” }, “type”: “groupBy” } ],
“limit”: 50 }, “tags”: [] } ], “title”: “Lock Wait Count”, “type”:
“timeseries” }, { “datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” },
“fieldConfig”: { “defaults”: { “color”: { “mode”: “palette-classic” },
“custom”: { “axisCenteredZero”: false, “axisColorMode”: “text”,
“axisLabel”: ““,”axisPlacement”: “auto”, “barAlignment”: 0, “drawStyle”:
“line”, “fillOpacity”: 10, “gradientMode”: “none”, “hideFrom”: {
“legend”: false, “tooltip”: false, “viz”: false }, “lineInterpolation”:
“linear”, “lineWidth”: 1, “pointSize”: 5, “scaleDistribution”: { “type”:
“linear” }, “showPoints”: “never”, “spanNulls”: true, “stacking”: {
“group”: “A”, “mode”: “none” }, “thresholdsStyle”: { “mode”: “off” } },
“mappings”: [], “thresholds”: { “mode”: “absolute”, “steps”: [ {
“color”: “green”, “value”: null }, { “color”: “red”, “value”: 80 } ] },
“unit”: “short” }, “overrides”: [] }, “gridPos”: { “h”: 8, “w”: 7, “x”:
11, “y”: 31 }, “id”: 4, “links”: [], “options”: { “legend”: { “calcs”: [
“min” ], “displayMode”: “list”, “placement”: “bottom”, “showLegend”:
false }, “tooltip”: { “mode”: “single”, “sort”: “none” } },
“pluginVersion”: “8.3.0”, “targets”: [ { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “hide”: false, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,NAME,lead(local_scn,1) over(partition by
MEMBER_NAME,NAME order by int_timestamp) -local_scn
local_diff,lead(group_scn,1) over(partition by MEMBER_NAME,NAME order by
int_timestamp) -group_scn group_diff,lead(global_scn,1) over(partition
by MEMBER_NAME,NAME order by int_timestamp) -global_scn
global_difftelegraf.goldilocks_scn_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by time,MEMBER_NAME,NAME”,
“refId”: “A”, “sql”: { “columns”: [ { “parameters”: [], “type”:
“function” } ], “groupBy”: [ { “property”: { “type”: “string” }, “type”:
“groupBy” } ], “limit”: 50 } } ], “title”: “System Commit Number”,
“type”: “timeseries” }, { “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: { “mode”:
“palette-classic” }, “custom”: { “axisCenteredZero”: false,
“axisColorMode”: “text”, “axisLabel”: ““,”axisPlacement”: “auto”,
“barAlignment”: 0, “drawStyle”: “line”, “fillOpacity”: 10,
“gradientMode”: “none”, “hideFrom”: { “legend”: false, “tooltip”: false,
“viz”: false }, “lineInterpolation”: “linear”, “lineWidth”: 1,
“pointSize”: 5, “scaleDistribution”: { “type”: “linear” }, “showPoints”:
“never”, “spanNulls”: true, “stacking”: { “group”: “A”, “mode”: “none”
}, “thresholdsStyle”: { “mode”: “off” } }, “mappings”: [], “thresholds”:
{ “mode”: “absolute”, “steps”: [ { “color”: “green”, “value”: null }, {
“color”: “red”, “value”: 80 } ] }, “unit”: “short” }, “overrides”: [] },
“gridPos”: { “h”: 8, “w”: 6, “x”: 18, “y”: 31 }, “id”: 77, “links”: [],
“options”: { “legend”: { “calcs”: [], “displayMode”: “list”,
“placement”: “bottom”, “showLegend”: false }, “tooltip”: { “mode”:
“single”, “sort”: “none” } }, “pluginVersion”: “8.3.0”, “targets”: [ {
“datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”:
“code”, “format”: “time_series”, “hide”: false, “rawQuery”: true,
“rawSql”: “SELECT$\__timeGroup(int_timestamp + interval 9
hour,‘1m’,previous)
time,MEMBER_NAME,local_gap,group_gap,global_gaptelegraf.goldilocks_ager_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by time,MEMBER_NAME”,
“refId”: “A”, “sql”: { “columns”: [ { “parameters”: [], “type”:
“function” } ], “groupBy”: [ { “property”: { “type”: “string” }, “type”:
“groupBy” } ], “limit”: 50 } } ], “title”: “Ager Stat”, “type”:
“timeseries” }, { “collapsed”: true, “gridPos”: { “h”: 1, “w”: 24, “x”:
0, “y”: 39 }, “id”: 88, “panels”: [ { “datasource”: { “type”: “mysql”,
“uid”: “QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: { “mode”:
“palette-classic” }, “custom”: { “axisCenteredZero”: false,
“axisColorMode”: “text”, “axisLabel”: ““,”axisPlacement”: “auto”,
“axisSoftMin”: -2, “barAlignment”: 0, “drawStyle”: “line”,
“fillOpacity”: 10, “gradientMode”: “none”, “hideFrom”: { “legend”:
false, “tooltip”: false, “viz”: false }, “lineInterpolation”: “linear”,
“lineWidth”: 1, “pointSize”: 5, “scaleDistribution”: { “type”: “linear”
}, “showPoints”: “auto”, “spanNulls”: false, “stacking”: { “group”: “A”,
“mode”: “none” }, “thresholdsStyle”: { “mode”: “off” } }, “mappings”:
[], “thresholds”: { “mode”: “absolute”, “steps”: [ { “color”: “green”,
“value”: null }, { “color”: “red”, “value”: 80 } ] }, “unit”:
“decmbytes” }, “overrides”: [] }, “gridPos”: { “h”: 8, “w”: 12, “x”: 0,
“y”: 40 }, “id”: 90, “options”: { “legend”: { “calcs”: [],
“displayMode”: “list”, “placement”: “bottom”, “showLegend”: true },
“tooltip”: { “mode”: “single”, “sort”: “none” } }, “pluginVersion”:
“9.3.6”, “targets”: [ { “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “editorMode”: “code”, “format”: “time_series”,
“rawQuery”: true, “rawSql”: “SELECT$\__timeGroup(int_timestamp +
interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,TOTAL_MB,USED_MBtelegraf.goldilocks_plan_cache_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by time,MEMBER_NAME”,
“refId”: “A”, “sql”: { “columns”: [ { “parameters”: [], “type”:
“function” } ], “groupBy”: [ { “property”: { “type”: “string” }, “type”:
“groupBy” } ], “limit”: 50 } } ], “title”: “Plan Cache”, “type”:
“timeseries” }, { “datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” },
“fieldConfig”: { “defaults”: { “color”: { “mode”: “palette-classic” },
“custom”: { “axisCenteredZero”: false, “axisColorMode”: “text”,
“axisLabel”: ““,”axisPlacement”: “auto”, “barAlignment”: 0, “drawStyle”:
“line”, “fillOpacity”: 3, “gradientMode”: “none”, “hideFrom”: {
“legend”: false, “tooltip”: false, “viz”: false }, “lineInterpolation”:
“linear”, “lineWidth”: 1, “pointSize”: 5, “scaleDistribution”: { “type”:
“linear” }, “showPoints”: “auto”, “spanNulls”: false, “stacking”: {
“group”: “A”, “mode”: “none” }, “thresholdsStyle”: { “mode”: “off” } },
“mappings”: [], “thresholds”: { “mode”: “absolute”, “steps”: [ {
“color”: “green”, “value”: null }, { “color”: “red”, “value”: 80 } ] }
}, “overrides”: [] }, “gridPos”: { “h”: 8, “w”: 12, “x”: 12, “y”: 40 },
“id”: 91, “options”: { “legend”: { “calcs”: [], “displayMode”: “list”,
“placement”: “bottom”, “showLegend”: true }, “tooltip”: { “mode”:
“single”, “sort”: “none” } }, “pluginVersion”: “9.3.6”, “targets”: [ {
“datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”:
“code”, “format”: “time_series”, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,lead(BUFFER_HIT,1) over(partition by MEMBER_NAME order
by int_timestamp) - BUFFER_HIT hit,lead(BUFFER_MISS,1) over(partition by
MEMBER_NAME order by int_timestamp) - BUFFER_MISS
misstelegraf.goldilocks_disk_buffer_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by
time,MEMBER_NAME“,”refId”: “A”, “sql”: { “columns”: [ { “parameters”:
[], “type”: “function” } ], “groupBy”: [ { “property”: { “type”:
“string” }, “type”: “groupBy” } ], “limit”: 50 } } ], “title”: “Disk
Buffer Hit & Miss”, “type”: “timeseries” } ], “title”: “Cache Hit”,
“type”: “row” }, { “collapsed”: true, “gridPos”: { “h”: 1, “w”: 24, “x”:
0, “y”: 40 }, “id”: 85, “panels”: [ { “datasource”: { “type”: “mysql”,
“uid”: “QFZ_gIB4k” }, “fieldConfig”: { “defaults”: { “color”: { “mode”:
“continuous-GrYlRd” }, “custom”: { “fillOpacity”: 70, “lineWidth”: 0,
“spanNulls”: false }, “mappings”: [], “thresholds”: { “mode”:
“absolute”, “steps”: [ { “color”: “green”, “value”: null }, { “color”:
“red”, “value”: 80 } ] } }, “overrides”: [] }, “gridPos”: { “h”: 8, “w”:
24, “x”: 0, “y”: 41 }, “id”: 83, “links”: [], “options”: { “alignValue”:
“right”, “legend”: { “displayMode”: “list”, “placement”: “bottom”,
“showLegend”: true }, “mergeValues”: true, “rowHeight”: 0.9,
“showValue”: “auto”, “tooltip”: { “mode”: “single”, “sort”: “none” } },
“pluginVersion”: “9.3.6”, “targets”: [ { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “hide”: false, “rawQuery”: true, “rawSql”:
“SELECTint_timestamp time,MEMBER_NAME,NAME,COUNT(\*)
cnttelegraf.goldilocks_cluster_serverwhere $\__timeFilter(int_timestamp+
interval 9 hour)and status != ‘WAIT’by time,MEMBER_NAME,NAME“,”refId”:
“A”, “sql”: { “columns”: [ { “parameters”: [], “type”: “function” } ],
“groupBy”: [ { “property”: { “type”: “string” }, “type”: “groupBy” } ],
“limit”: 50 } } ], “title”: “Cluster Server”, “type”: “state-timeline”
}, { “datasource”: { “type”: “mysql”, “uid”: “QFZ_gIB4k” },
“fieldConfig”: { “defaults”: { “color”: { “mode”: “palette-classic” },
“custom”: { “axisCenteredZero”: false, “axisColorMode”: “text”,
“axisLabel”: ““,”axisPlacement”: “auto”, “barAlignment”: 0, “drawStyle”:
“line”, “fillOpacity”: 10, “gradientMode”: “none”, “hideFrom”: {
“legend”: false, “tooltip”: false, “viz”: false }, “lineInterpolation”:
“linear”, “lineWidth”: 1, “pointSize”: 5, “scaleDistribution”: { “type”:
“linear” }, “showPoints”: “never”, “spanNulls”: true, “stacking”: {
“group”: “A”, “mode”: “none” }, “thresholdsStyle”: { “mode”: “off” } },
“mappings”: [], “thresholds”: { “mode”: “absolute”, “steps”: [ {
“color”: “green”, “value”: null }, { “color”: “red”, “value”: 80 } ] },
“unit”: “bytes” }, “overrides”: [] }, “gridPos”: { “h”: 10, “w”: 24,
“x”: 0, “y”: 49 }, “id”: 76, “links”: [], “options”: { “legend”: {
“calcs”: [], “displayMode”: “list”, “placement”: “bottom”, “showLegend”:
false }, “tooltip”: { “mode”: “single”, “sort”: “none” } },
“pluginVersion”: “8.3.0”, “targets”: [ { “datasource”: { “type”:
“mysql”, “uid”: “QFZ_gIB4k” }, “editorMode”: “code”, “format”:
“time_series”, “hide”: false, “rawQuery”: true, “rawSql”:
“SELECT$\__timeGroup(int_timestamp + interval 9 hour,‘1m’,previous)
time,MEMBER_NAME,lead(RX_BYTES,1) over(partition by MEMBER_NAME order by
int_timestamp) - RX_BYTES diff_Recv,lead(TX_BYTES,1) over(partition by
MEMBER_NAME order by int_timestamp) - TX_BYTES
diff_Sendtelegraf.goldilocks_cluster_dispatcher_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)\\ngroup by
time,MEMBER_NAME\\n", "refId": "A", "sql": { "columns": [ {
"parameters": [], "type": "function" } ], "groupBy": [ { "property": {
"type": "string" }, "type": "groupBy" } ], "limit": 50 } } ], "title":
"Cluster Dispatcher", "type": "timeseries" }, { "datasource": { "type":
"mysql", "uid": "QFZ_gIB4k" }, "description": "", "fieldConfig": {
"defaults": { "color": { "mode": "continuous-GrYlRd" }, "custom": {
"fillOpacity": 70, "lineWidth": 0, "spanNulls": false }, "mappings": [],
"thresholds": { "mode": "absolute", "steps": [ { "color": "green",
"value": null }, { "color": "red", "value": 80 } ] } }, "overrides": []
}, "gridPos": { "h": 19, "w": 24, "x": 0, "y": 59 }, "id": 64, "links":
[], "options": { "alignValue": "right", "legend": { "displayMode":
"list", "placement": "bottom", "showLegend": true }, "mergeValues":
true, "rowHeight": 0.9, "showValue": "auto", "tooltip": { "mode":
"single", "sort": "none" } }, "pluginVersion": "9.3.6", "targets": [ {
"alias": "$tag_MEMBER_NAME”, “datasource”: { “type”: “mysql”, “uid”:
“QFZ_gIB4k” }, “editorMode”: “code”, “format”: “time_series”, “groupBy”:
[ { “params”: [ “$\__interval” ], “type”: “time” }, { “params”: [
“MEMBER_NAME” ], “type”: “tag” }, { “params”: [ “none” ], “type”: “fill”
} ], “measurement”: “monitor_cluster_queue_sum”, “orderByTime”: “ASC”,
“policy”: “default”, “query”: “SELECT derivative(mean("TOTALQ"), 1s)
FROM "monitor_cluster_queue" WHERE ("NAME" = ‘MASTER_IN’ OR "NAME" =
‘MASTER_OUT’) AND *timeFilterGROUPBYtime*\ (\ \__interval),
"MEMBER_NAME", "NAME" fill(none)“,”rawQuery”: true, “rawSql”:
“SELECTint_timestamp
time,MEMBER_NAME,NAME,QUEUEDtelegraf.goldilocks_cluster_queue_statwhere
$\__timeFilter(int_timestamp+ interval 9 hour)by
time,MEMBER_NAME,NAME“,”refId”: “A”, “resultFormat”: “time_series”,
“select”: [ [ { “params”: [ “TOTALQ” ], “type”: “field” }, { “params”:
[], “type”: “mean” }, { “params”: [ “1s” ], “type”:
“non_negative_derivative” } ] ], “sql”: { “columns”: [ { “parameters”:
[], “type”: “function” } ], “groupBy”: [ { “property”: { “type”:
“string” }, “type”: “groupBy” } ], “limit”: 50 }, “tags”: [] } ],
“title”: “Cluster Queue”, “type”: “state-timeline” } ], “title”:
“Cluster Traffic”, “type”: “row” } ], “refresh”: “30s”, “schemaVersion”:
37, “style”: “dark”, “tags”: [], “templating”: { “list”: [ { “current”:
{ “selected”: false, “text”: “G2N1”, “value”: “G2N1” }, “datasource”: {
“type”: “mysql”, “uid”: “QFZ_gIB4k” }, “definition”: “select member_name
from goldilocks_session_stat”, “hide”: 0, “includeAll”: false, “multi”:
false, “name”: “member_name”, “options”: [], “query”: “select
member_name from goldilocks_session_stat”, “refresh”: 1, “regex”:
““,”skipUrlSync”: false, “sort”: 0, “type”: “query” } ] }, “time”: {
“from”: “now-15m”, “to”: “now” }, “timepicker”: { “refresh_intervals”: [
“5s”, “10s”, “30s”, “1m”, “5m”, “15m”, “30m”, “1h”, “2h”, “1d” ],
“time_options”: [ “5m”, “15m”, “1h”, “6h”, “12h”, “24h”, “2d”, “7d”,
“30d” ] }, “timezone”: ““,”title”: “goldilocks_dashboard_maria”, “uid”:
“goldilocks_dashboard_maria”, “version”: 83, “weekStart”: “” } }}}

== telegraf.conf for mysql == {{{ # Global tags can be specified here in
key=“value” format. [global_tags] # dc = “us-east-1” # will tag all
metrics with dc=us-east-1 # rack = “1a” ## Environment variables can be
used as tags, and throughout the config file # user = “$USER”

Configuration for telegraf agent
================================

[agent] ## Default data collection interval for all inputs interval =
“20s” ## Rounds collection interval to ‘interval’ ## ie, if
interval=“10s” then always collect on :00, :10, :20, etc. round_interval
= true

## Telegraf will send metrics to outputs in batches of at most ##
metric_batch_size metrics. ## This controls the size of writes that
Telegraf sends to output plugins. metric_batch_size = 1000

## Maximum number of unwritten metrics per output. Increasing this value
## allows for longer periods of output downtime without dropping metrics
at the ## cost of higher maximum memory usage. metric_buffer_limit =
100000

## Collection jitter is used to jitter the collection by a random
amount. ## Each plugin will sleep for a random time within jitter before
collecting. ## This can be used to avoid many plugins querying things
like sysfs at the ## same time, which can have a measurable effect on
the system. collection_jitter = “0s”

## Collection offset is used to shift the collection by the given
amount. ## This can be be used to avoid many plugins querying constraint
devices ## at the same time by manually scheduling them in time. #
collection_offset = “0s”

## Default flushing interval for all outputs. Maximum flush_interval
will be ## flush_interval + flush_jitter flush_interval = “10s” ##
Jitter the flush interval by a random amount. This is primarily to avoid
## large write spikes for users running a large number of telegraf
instances. ## ie, a jitter of 5s and interval 10s means flushes will
happen every 10-15s flush_jitter = “0s”

## Collected metrics are rounded to the precision specified. Precision
is ## specified as an interval with an integer + unit (e.g. 0s, 10ms,
2us, 4s). ## Valid time units are “ns”, “us” (or “µs”), “ms”, “s”. ## ##
By default or when set to “0s”, precision will be set to the same ##
timestamp order as the collection interval, with the maximum being 1s:
## ie, when interval = “10s”, precision will be “1s” ## when interval =
“250ms”, precision will be “1ms” ## ## Precision will NOT be used for
service inputs. It is up to each individual ## service input to set the
timestamp at the appropriate precision. precision = “0s”

## Log at debug level. # debug = false ## Log only error level messages.
# quiet = false

## Log target controls the destination for logs and can be one of
“file”, ## “stderr” or, on Windows, “eventlog”. When set to “file”, the
output file ## is determined by the “logfile” setting. # logtarget =
“file”

## Name of the file to be logged to when using the “file” logtarget. If
set to ## the empty string then logs are written to stderr. # logfile =
“”

## The logfile will be rotated after the time interval specified. When
set ## to 0 no time based rotation is performed. Logs are rotated only
when ## written to, if there is no log activity rotation may be delayed.
# logfile_rotation_interval = “0h”

## The logfile will be rotated when it becomes larger than the specified
## size. When set to 0 no size based rotation is performed. #
logfile_rotation_max_size = “0MB”

## Maximum number of rotated archives to keep, any older logs are
deleted. ## If set to -1, no archives are removed. #
logfile_rotation_max_archives = 5

## Pick a timezone to use when logging or type ‘local’ for local time.
## Example: America/Chicago log_with_timezone = “Asia/Seoul”

## Override default hostname, if empty use os.Hostname() hostname = “”
## If set to true, do no set the “host” tag in the telegraf agent.
omit_hostname = false

# # Save metrics to an SQL Database [[outputs.sql]] ## Database driver
## Valid options: mssql (Microsoft SQL Server), mysql (MySQL), pgx
(Postgres), ## sqlite (SQLite3), snowflake (snowflake.com) clickhouse
(ClickHouse) driver = “mysql”

## Data source name ## The format of the data source name is different
for each database driver. ## See the plugin readme for details.
data_source_name = “tele:tele@tcp(192.168.0.120:9125)/telegraf”

## Timestamp column name timestamp_column = “int_timestamp”

## Table creation template ## Available template variables: ## {TABLE} -
table name as a quoted identifier ## {TABLELITERAL} - table name as a
quoted string literal ## {COLUMNS} - column definitions (list of quoted
identifiers and types) table_template = “CREATE TABLE
{TABLE}({COLUMNS})”

## Table existence check template ## Available template variables: ##
{TABLE} - tablename as a quoted identifier table_exists_template =
“SELECT 1 FROM {TABLE} LIMIT 1”

## Initialization SQL init_sql = “SET sql_mode=‘ANSI_QUOTES’ ,time_zone
= ‘Asia/Seoul’” # #init_sql = “SET time_zone = ‘Asia/Seoul’”

## Metric type to SQL type conversion ## The values on the left are the
data types Telegraf has and the values on ## the right are the data
types Telegraf will use when sending to a database. ## ## The database
values used must be data types the destination database ## understands.
It is up to the user to ensure that the selected data type is ##
available in the database they are using. Refer to your database ##
documentation for what data types are available and supported.
[outputs.sql.convert] integer = “INT” real = “DOUBLE” text = “TEXT”
timestamp = “TIMESTAMP” defaultvalue = “TEXT” unsigned = “UNSIGNED” bool
= “BOOL”

## This setting controls the behavior of the unsigned value. By default
the ## setting will take the integer value and append the unsigned value
to it. The other ## option is “literal”, which will use the actual value
the user provides to ## the unsigned option. This is useful for a
database like ClickHouse where ## the unsigned value should use a value
like “uint64”. # conversion_style = “unsigned_suffix”

## Maximum amount of time a connection may be idle. “0s” means
connections are ## never closed due to idle time. #
connection_max_idle_time = “0s”

## Maximum amount of time a connection may be reused. “0s” means
connections ## are never closed due to age. # connection_max_lifetime =
“0s”

## Maximum number of connections in the idle connection pool. 0 means
unlimited. # connection_max_idle = 2

## Maximum number of open connections to the database. 0 means
unlimited. # connection_max_open = 0

INPUT PLUGINS
=============

Read metrics about cpu usage
============================

[[inputs.cpu]] ## Whether to report per-cpu stats or not percpu = true
## Whether to report total system cpu stats or not totalcpu = true ## If
true, collect raw CPU time metrics collect_cpu_time = false ## If true,
compute and report the sum of all non-idle CPU states report_active =
false ## If true and the info is available then add core_id and
physical_id tags core_tags = false

Read metrics about disk usage by mount point
============================================

[[inputs.disk]] ## By default stats will be gathered for all mount
points. ## Set mount_points will restrict the stats to only the
specified mount points. # mount_points = [“/”]

## Ignore mount points by filesystem type. ignore_fs = [“tmpfs”,
“devtmpfs”, “devfs”, “iso9660”, “overlay”, “aufs”, “squashfs”]

## Ignore mount points by mount options. ## The ‘mount’ command reports
options of all mounts in parathesis. ## Bind mounts can be ignored with
the special ‘bind’ option. # ignore_mount_opts = []

Read metrics about disk IO by device
====================================

[[inputs.diskio]] # Get kernel statistics from /proc/stat

[[inputs.kernel]] # no configuration

Read metrics about memory usage
===============================

[[inputs.mem]]

[[inputs.net]] ignore_protocol_stats = true # no configuration

Get the number of processes and group them by status
====================================================

[[inputs.processes]] # no configuration

Read metrics about swap memory usage
====================================

#[[inputs.swap]] # no configuration

Read metrics about system load & uptime
=======================================

#[[inputs.system]] # # no configuration

[[inputs.goldilocks]] ### specify connection string
goldilocks_odbc_driver_path =
“/home/goya3/tele/telegraf_1.26/lib/libgoldilockscs-ul64.so”
goldilocks_host = “192.168.0.119” goldilocks_port = 30011
goldilocks_user = “monitor” goldilocks_password = “monitor” }}}

== grafana preview ==

[[Image(System_usage.jpg,100%)]] [[Image(Goldilocks_db.jpg,100%)]]
[[Image(Cache_hit.jpg,100%)]] [[Image(Cluster_traffic.jpg,100%)]]

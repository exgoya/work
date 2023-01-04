#!/bin/bash

GOLDILOCKS_HOME=/home/goya/goldilocks_home
PATH=$GOLDILOCKS_HOME/bin:/home/goya/bin:$PATH
workdir='/home/goya/work/shell/rebuild/'
log="./rebuild_index.log"

cd $workdir

session="${GOLDILOCKS_HOME}/bin/gsqlnet sys gliese --no-prompt"
sql1="SELECT '#ALTER INDEX '||TAB_SCHEMA||'.'||IDX_NAME||' REBUILD;' FROM TECH_INDEX WHERE IDX_NAME != '[GLOBAL INDEX]'";
sql2="SELECT '#ALTER TABLE '||TAB_SCHEMA||'.'||TAB_NAME||' REBUILD GLOBAL SECONDARY INDEX;' FROM TECH_INDEX WHERE IDX_NAME = '[GLOBAL INDEX]'";
stime=`date +%H:%M:%S`

function OUT_sql
{
$session << EOF
set linesize 1024
set pagesize 10000
set timing on
set time off
set heading off
$1;
quit
EOF
}

function _for
{
while read line
do
    echo "$line"
    OUT_sql "$line"
done < temp
}

echo "" >> $log
echo "[`date +%Y/%m/%d` $stime ] index rebuild start!" >> $log

OUT_sql "$sql1"|grep "^#" |sed 's/^#//' > temp
_for >> $log
OUT_sql "$sql2"|grep "^#" |sed 's/^#//' > temp
_for >> $log

etime=`date +%H:%M:%S`
echo "[`date +%Y/%m/%d` $stime ~ $etime ] index rebuild all done!" >> $log
echo "" >> $log

rm temp

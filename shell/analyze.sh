#!/bin/bash

GSQL='gsqlnet sys gliese --no-prompt '

doSQLPrint()
{
$GSQL << EOF
set timing off;
set linesize 1111;
set heading off;
$1
EOF
}

doSQL()
{
$GSQL << EOF
set timing on;
set linesize 1111;
alter session set query_timeout = 600;
$1
EOF
}

analyzeTable()
{
while read line
do
    echo "analyze table $line;"
    doSQL "analyze table $line;"
done < $1
}

doSQLPrint "SELECT TABLE_SCHEMA||'.'||TABLE_NAME FROM DBA_CLUSTER_TABLES;" |grep -v selected|grep -v '^$' > temp1

echo "====================================="
date
echo "analyze table start"
echo "====================================="

date

analyzeTable temp1

rm temp1
rm temp2

echo "====================================="
date
echo "analyze table done"
echo "====================================="



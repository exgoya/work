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
$1
EOF
}

indexReuild()
{
while read line
do
    echo "alter index $line rebuild;"
    doSQL "alter index $line rebuild;"
done < $1
}

gsiIndexReuild()
{
while read line
do
    echo "alter table $line rebuild global secondary index;"
    doSQL "alter table $line rebuild global secondary index;"
done < $1
}

doSQLPrint "SELECT INDEX_SCHEMA||'.'||INDEX_NAME FROM USER_INDEXES;" |grep -v selected|grep -v '^$' > temp1
doSQLPrint "select distinct TABLE_SCHEMA||'.'||TABLE_NAME from USER_GSI_PLACE where TABLE_SCHEMA != 'DICTIONARY_SCHEMA';" |grep -v selected |grep -v '^$'> temp2

echo "====================================="
date
echo "index rebuild start"
echo "====================================="

indexReuild temp1
gsiIndexReuild temp2

rm temp1
rm temp2

echo "====================================="
date
echo "index rebuild done"
echo "====================================="



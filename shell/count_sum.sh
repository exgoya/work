#!/bin/sh

GOLDILOCKS_HOME=/data/sunje/product/goldilocks_home
GOLDILOCKS_DATA=/data/sunje/product/goldilocks_data
PATH=${GOLDILOCKS_HOME}/bin:${PATH}

#USER Argument $1:user $2:passwd
USER=$1
PASS=$2

TABLE_SCRIPT=/data/sunje/DBA/shell/table_count.sql
TABLE_DIFF=/data/sunje/DBA/shell/table_diff.log
TABLE_COUNT=/data/sunje/DBA/shell/table_count.log

rm -f $TABLE_SCRIPT
rm -f $TABLE_DIFF
rm -f $TABLE_COUNT

SQL="gsqlnet ${USER} ${PASS} --no-prompt"

scan_tbl()
{
    echo "
    SELECT  '#', TABLE_NAME FROM USER_TABLES ORDER BY TABLE_NAME;
    quit;
    "
}

tbl_script()
{
    if [ $# -eq 0 ]
    then
        echo "Waring : can't get index list"
    fi
    for TBL_NAME in $*
    do
        echo "SELECT COUNT(*) FROM ${TBL_NAME};" >> ${TABLE_SCRIPT}
    done
}


if [ $# -eq 0 ]
then
    echo "$0 [user][passwd]"
    exit 1;
fi


tbl_script `scan_tbl| ${SQL}  |grep "^#" |awk '{print $2}'`
tbl_list=`scan_tbl| ${SQL}  |grep "^#" |awk '{print $2}'`
total_count=0

for tbl_name in $tbl_list
do
    tbl_count_sql=`grep -w $tbl_name $TABLE_SCRIPT`
#    echo [$tbl_count_sql]
    g_tbl_count=`echo "$tbl_count_sql
                     quit;" | ${SQL} | grep -v "1 row"|grep -v "Elapsed" |grep -o [0-9]* |tr -d ' '`
    echo "[$g_tbl_count]"

    echo "[$tbl_name] : g[$g_tbl_count]" >> $TABLE_COUNT
    total_count=`expr $total_count + $g_tbl_count`
done

echo "##### [success : $total_count] #########"


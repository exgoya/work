#!/bin/sh

GOLDILOCKS_HOME=/data/sunje/product/goldilocks_home
GOLDILOCKS_DATA=/data/sunje/product/goldilocks_data
PATH=${GOLDILOCKS_HOME}/bin:${PATH}

#USER Argument $1:user $2:passwd
USER=$1
PASS=$2

TABLE_SCRIPT=/data/sunje/DBA/shell/table_count.sql
TABLE_DIFF=/data/sunje/DBA/shell/table_diff.log
TABLE_SUCCESS=/data/sunje/DBA/shell/table_success.log
rm -f $TABLE_SCRIPT
rm -f $TABLE_DIFF
rm -f $TABLE_SUCCESS

SQL="gsqlnet ${USER} ${PASS} --no-prompt"
O_SQL="sqlplus -S ${USER}/${PASS}@vci_conv"

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
diff_fail=0
diff_success=0
diff_total=0

for tbl_name in $tbl_list
do
    tbl_count_sql=`grep -w $tbl_name $TABLE_SCRIPT`
#    echo [$tbl_count_sql]
    g_tbl_count=`echo "$tbl_count_sql
                     quit;" | ${SQL} | grep -v "1 row"|grep -v "Elapsed" |grep -o [0-9]* |tr -d ' '`
    o_tbl_count=`echo "set heading off;
                       $tbl_count_sql
                       quit;" | ${O_SQL} |grep -o [0-9]* |tr -d ' '`
#    echo "[$g_tbl_count]"
#    echo "[$o_tbl_count]"

    if [ $g_tbl_count -eq $o_tbl_count ]
    then
        echo "[$tbl_name] : g[$g_tbl_count] / o[$o_tbl_count]"  >> $TABLE_SUCCESS
        diff_success=`expr $diff_success + 1`
    else
        echo "[$tbl_name] : g[$g_tbl_count] / o[$o_tbl_count]"  >> $TABLE_DIFF
        diff_fail=`expr $diff_fail + 1`
    fi

    diff_total=`expr $diff_total + 1`
done

echo "##### [mig diff ] #########"
echo "total   : [$diff_total]"
echo "success : [$diff_success]"
echo "failure : [$diff_fail]"
echo "###########################"


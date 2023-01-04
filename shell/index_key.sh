#!/bin/bash

GSQL='gsqlnet vn vn --no-prompt'


list_Table()
{
IndArr=(`$GSQL << EOF
\set timing off;
\set heading off;
--select table_name from user_tables where table_name like 'TB%' order by table_name;
select table_name from user_tables  order by table_name;
EOF`)

for((i=0;i<${#IndArr[@]}-3;i++));
do
    echo ${IndArr[i]}
done
}

list_Index()
{
IndArr=(`$GSQL << EOF
\set timing off;
\set heading off;
SELECT INDEX_NAME FROM USER_INDEXES WHERE TABLE_NAME = '$1';
EOF`)

for((i=0;i<${#IndArr[@]}-3;i++));
do
    echo ${IndArr[i]}
done
}

Index_check()
{
$GSQL << EOF    
\set timing off;
\set heading off;
select TOTAL_KEY_COUNT, ACTIVE_KEY_COUNT, NODE_LEVEL, '$1' from d\$btree_header('$1');
EOF
}


doIt()
{
    echo "============================================================="
    echo "TOTAL_KEY_COUNT, ACTIVE_KEY_COUNT, NODE_LEVEL, INDEX_NAME    "
    echo "============================================================="

    Arr_Table=(`list_Table`)

    for TABLE_NAME in ${Arr_Table[@]}
    do
#        echo "table name[$TABLE_NAME]"

        Arr_Index=(`list_Index $TABLE_NAME`)
#        echo "data : ${Arr_Index[@]}"
        
        for INDEX in ${Arr_Index[@]}
        do
#            echo "index : $INDEX"
#            Index_check $INDEX | grep "TB_"
            Index_check $INDEX
        done
    done
}

### Long Time Usage X
#doIt

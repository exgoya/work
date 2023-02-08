LOG=./rebuild.log
GSQL='gsqlnet sys gliese --no-prompt'
TABLE=$1
sStatement=V\$STATEMENT

tablespace()
{
IndArr=(`$GSQL << EOF
\set timing off;
\set heading off;
SELECT * FROM TECH_TABLESPACE WHERE TABLESPACE_NAME = 'MEM_TEMP_TBS';
EOF`)
}


list_InTable()
{
IndArr=(`$GSQL << EOF
\set timing off;
\set heading off;
SELECT INDEX_NAME FROM USER_INDEXES WHERE TABLE_NAME = '$1' ORDER BY BLOCKS;
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
SELECT INDEX_NAME FROM USER_INDEXES ORDER BY BLOCKS;
EOF`)

for((i=0;i<${#IndArr[@]}-3;i++));
do
  echo ${IndArr[i]}
done
}

list_SecIndex()
{
IndArr=(`$GSQL << EOF
\set timing off;
\set heading off;
SELECT distinct TABLE_NAME FROM USER_INDEXES;
EOF`)

for((i=0;i<${#IndArr[@]}-3;i++));
do
  echo ${IndArr[i]}
done
}
reBuild()
{
# CompVal = (잔여 TBS) - (해당 인덱스)

CompVal=(`$GSQL << EOF
\set timing off;
\set heading off;
SELECT TRUNC(
(
  SELECT MIN( TO_NUMBER( FREE_MEGABYTE ))
    FROM TECH_TABLESPACE
   WHERE TABLESPACE_NAME = 'MEM_TEMP_TBS'
) - TO_NUMBER( LOC_USE_MBYTE ) , 0 )
  FROM TECH_INDEX
 WHERE IDX_NAME = '$1'
;
EOF`)

# ComVal > 1024M
if [ ${CompVal} -gt 300 ]; then

    echo "============================="
    echo "$1 INDEX REBUILD.."

    $GSQL << EOF
    \set timing off;
    ALTER INDEX $1 REBUILD;
    COMMIT;
EOF
    echo "============================="
else
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- [ERROR] $1 is too BIG!! :: TEMP_TBS's FREE - INDEX $1's Mbyte = $CompVal. " >> $LOG
fi
}

Table_reBuild()
{
echo "============================="
echo "$1 GLOBAL SECONDARY INDEX REBUILD.."
echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $1 Global Secondary INDEX REBUILD.." >> $LOG
$GSQL << EOF
\set timing off;
ALTER TABLE $1 REBUILD GLOBAL SECONDARY INDEX;
COMMIT;
EOF
echo "============================="
}

doIt()
{
echo `tablespace` >> $LOG
if [[ ${TABLE^^} == "ALL" ]]; then
    echo "============================="
    echo "ALL INDEX REBUILD"
    echo "============================="
    
    Arr=(`list_Index`)
    
    for INDEX in ${Arr[@]}
    do
      echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $INDEX Start" >> $LOG
      reBuild $INDEX
      echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $INDEX End" >> $LOG
    done

    Arr=(`list_SecIndex`)
    
    for TABLE in ${Arr[@]}
    do
      echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $TABLE Start" >> $LOG
      Table_reBuild $TABLE
      echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $TABLE End" >> $LOG
    done
else

    echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $1 secondary index Start" >> $LOG
    Table_reBuild $1
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $1 secondary index End" >> $LOG
    
    Arr=(`list_InTable $TABLE`)
    
    for INDEX in ${Arr[@]}
    do
      echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $INDEX Start" >> $LOG
      reBuild $INDEX
      echo "[$(date '+%Y-%m-%d %H:%M:%S')] -- $INDEX End" >> $LOG
    done
fi
echo `tablespace` >> $LOG
}

doIt $1

#example : sh index_rebuild.sh ALL
#example : sh index_rebuild.sh clob_test
#global secondary index rebuild
#ALTER TABLE T1 DROP GLOBAL SECONDARY INDEX;
#ALTER TABLE T1 ADD GLOBAL SECONDARY INDEX;



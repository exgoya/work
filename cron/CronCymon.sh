#!/bin/bash

export GOLDILOCKS_HOME=/home2/godb/godb1/goldilocks_home
export PATH=$GOLDILOCKS_HOME/bin:$PATH

GSQLNET='gsqlnet gold_ss gold_ss1234 --no-prompt'
# crontab 2분 설정
gMaxNoActiveCount=4
gLoopCount=28
gSleepTime=4

exSelect_Table()
{
sSelectFirst=(`$GSQLNET << EOF
\set timing off;
\set heading off;
select GROUP_NAME, REDO_LOG_BLOCKSEQ, CAPTURE_BLOCKSEQ, APPLY_BLOCKSEQ
from CYCLONE_MONITOR_INFO
order by GROUP_NAME;
EOF`)

sleep $gSleepTime

sSelectSecond=(`$GSQLNET << EOF
\set timing off;
\set heading off;
select GROUP_NAME, REDO_LOG_BLOCKSEQ, CAPTURE_BLOCKSEQ, APPLY_BLOCKSEQ
from CYCLONE_MONITOR_INFO
order by GROUP_NAME;
EOF`)
}

group_name_arr=()
slave_no_active_arr=()
slave_no_active_cnt_arr=()
slave_nok_arr=()

slave_no_active_arr=()
slave_no_active_cnt_arr=()
slave_nok_arr=()

isfirst=1

# select 결과를 array 에 담는다
genArr()
{
redo_log_data_arr_1=()
redo_log_data_arr_2=()
capture_data_arr_1=()
capture_data_arr_2=()
apply_data_arr_1=()
apply_data_arr_2=()


for (( i=0; i< `expr ${#sSelectFirst[@]} - 3`; i++ )) do
  if [ `expr $i % 4` -eq 0 ]; then
    if [ $isfirst -eq 1 ]; then
      group_name_arr+=("${sSelectFirst[$i]}")

      ### 초기화 group 갯수별
      master_no_active_cnt_arr+=("0")
      master_no_active_arr+=("NONE")
      master_nok_arr+=("NONE")

      slave_no_active_cnt_arr+=("0")
      slave_no_active_arr+=("NONE")
      slave_nok_arr+=("NONE")
   fi
  elif [ `expr $i % 4` -eq 1 ]; then
    redo_log_data_arr_1+=("${sSelectFirst[$i]}")
  elif [ `expr $i % 4` -eq 2 ]; then
    capture_data_arr_1+=("${sSelectFirst[$i]}")
  elif [ `expr $i % 4` -eq 3 ]; then
    apply_data_arr_1+=("${sSelectFirst[$i]}")
  fi
done

for (( i=0; i<`expr ${#sSelectSecond[@]} - 3`; i++ )) do
  if [ `expr $i % 4` -eq 1 ]; then
    redo_log_data_arr_2+=("${sSelectSecond[$i]}")
  elif [ `expr $i % 4` -eq 2 ]; then
    capture_data_arr_2+=("${sSelectSecond[$i]}")
  elif [ `expr $i % 4` -eq 3 ]; then
    apply_data_arr_2+=("${sSelectSecond[$i]}")
  fi
done
isfirst=0
}

#check 후no_active, nok array를 설정한다
checkOk()
{
for (( i=0; i< ${#group_name_arr[@]}; i++ )) do

  #master active check
  if [ ${capture_data_arr_1[$i]} -eq ${capture_data_arr_2[$i]} ]; then
    master_no_active_cnt_arr[$i]=$((${master_no_active_cnt_arr[$i]}+1))
    master_no_active_arr[$i]="NOACTIVE"
  else
    master_no_active_cnt_arr[$i]=0
    master_no_active_arr[$i]="ACTIVE"
  fi

  # master NOK check
  if [ ${master_no_active_cnt_arr[$i]} -ge ${gMaxNoActiveCount} ]; then
    master_nok_arr[$i]="NOK"
  else
    master_nok_arr[$i]="OK"
  fi

  # slave check
  if [ ${apply_data_arr_1[$i]} -eq ${apply_data_arr_2[$i]} ]; then
    slave_no_active_cnt_arr[$i]=$((${slave_no_active_cnt_arr[$i]}+1))
    slave_no_active_arr[$i]="NOACTIVE"
  else
    slave_no_active_cnt_arr[$i]=0
    slave_no_active_arr[$i]="ACTIVE"
  fi

  # slave NOK check
  if [ ${slave_no_active_cnt_arr[$i]} -ge ${gMaxNoActiveCount} ]; then
    slave_nok_arr[$i]="NOK"
  else
    slave_nok_arr[$i]="OK"
  fi

done
}

debug()
{
echo "-----------------------------------------------"
echo "result array count : ${#sSelectFirst[@]}"
echo "-----------------------------------------------"
echo "group name array count : ${#group_name_arr[@]}"
echo "-----------------------------------------------"
echo "group name    : ${group_name_arr[@]}"
echo "-----------------------------------------------"
echo "master is active     :${master_no_active_arr[@]}"
echo "slave is active      :${slave_no_active_arr[@]}"
echo "-----------------------------------------------"
echo "master no active cnt : ${master_no_active_cnt_arr[@]}"
echo "slave no active cnt  : ${slave_no_active_cnt_arr[@]}"
echo "-----------------------------------------------"
echo "master is nok :${master_nok_arr[@]}"
echo "slave  is nok :${slave_nok_arr[@]}"
echo "-----------------------------------------------"
echo "redo 1        :${redo_log_data_arr_1[@]}"
echo "redo 2        :${redo_log_data_arr_2[@]}"
echo "-----------------------------------------------"
echo "capture 1     :${capture_data_arr_1[@]}"
echo "capture 2     :${capture_data_arr_2[@]}"
echo "-----------------------------------------------"
echo "apply 1       :${apply_data_arr_1[@]}"
echo "apply 2       :${apply_data_arr_2[@]}"
echo "-----------------------------------------------"
}

printLog()
{
dt=$(date '+%Y-%m-%d %H:%M:%S')

for (( i=0; i< ${#group_name_arr[@]}; i++ )) do
  echo "$dt,${group_name_arr[$i]},MASTER,${master_no_active_arr[$i]},${master_nok_arr[$i]}"
  echo "$dt,${group_name_arr[$i]},SLAVE,${slave_no_active_arr[$i]},${slave_nok_arr[$i]}"
done
}


DATE=$(date '+%Y%m%d')
BACKDIR="$HOME/DBA/log"

doIt()
{
for ((i=0; i < $gLoopCount;i++))
do
  exSelect_Table
  genArr
  checkOk
  debug >> ${BACKDIR}/Debug_CronCymon_${DATE}.log
  printLog
done
}

doIt >> ${BACKDIR}/CronCymon_${DATE}.log

find ${BACKDIR}/ -name '*CronCymon_*.log' -mtime +14 -exec ls -lt {} \; >> ${BACKDIR}/CronCymon_del.log
find ${BACKDIR}/ -name '*CronCymon_*.log' -mtime +14 -exec rm -f {} \;


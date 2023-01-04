#!/bin/bash

if [ $# -le 0 ] ; then
    echo "Usage: " ${0} " [master|slave] [group name(ex: g1)]"
    exit 0
fi

gsql="gsql test test --no-prompt"
APP_NAME="cyclone"
args=("$@")
masterSlave=${args[0]}
groupName=${args[1]}

function status(){
    pinfo=$(ps -fu $UID | grep "${masterSlave}" | grep "\-\-start" | grep ${APP_NAME})
    pid=$(ps -fu $UID | grep "${masterSlave}" | grep "\-\-start" | grep ${APP_NAME}| awk {'print $2'})
    if [ ! -z "${pid}" ]; then
        echo "running(${masterSlave}):"  ${pid} 
        echo "$pinfo"
    else
        echo "stopped"
    fi
}

function start(){
    statRes=`status`
    echo "$statRes"

    sql="select count(1) from gv\$session@${groupName}[ignore_inactive_member] where program_name ='cyclone';"
    sqlRes=`echo "$sql"|$gsql|grep -v selected |grep -v Elapsed|grep -v COUNT|grep -v "\-\-\-\-"|grep -v Warning|tr -d ' '`
    err=`echo $sqlRes|grep "ERR-HY000(11031)"|wc -l` # ERR-HY000(11031): Unable to attach the shared memory segment : sthAttach() returned errno(2)

    if [ "$statRes" == "stopped" ]; then # local 에cyclone 프로세스가 없으면
        if [ "${masterSlave}" == "slave" ]; then # slave 이고 그룹에 cyclone session 이 있으면 기동하지 않음
            if [ "${sqlRes}" -eq "0" ]; then
                cyclone --${masterSlave} --start
	        else
		        echo "cyclone ${masterSlave} alrady running.."
            fi
        else # master면 무조건 기동
            echo "go ${masterSlave} start.."
            cyclone --${masterSlave} --start
        fi
    else # local 에cyclone 프로세스가 있으면
        echo "cyclone ${masterSlave} already running.."
        if [ "${masterSlave}" == "slave" ]; then # slave 이면
		    if [ "${err}" -ne "0" ]; then # local 에 접속이 안되면cyclone slave 종료
		        echo "error count : $err" 
                cyclone --${masterSlave} --stop
            fi
        fi
    fi
}

while :
do
start
sleep 10
done


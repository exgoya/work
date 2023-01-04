#!/bin/bash

shmmax=`cat /proc/sys/kernel/shmmax`
gshmmax=`cat /proc/sys/kernel/shmmax | awk ' {printf "%.0f\n", $1/1024/1024/1024}'` #GB
shmmni=`cat /proc/sys/kernel/shmmni`
shmall=`cat /proc/sys/kernel/shmall`
semmsi=`cat /proc/sys/kernel/sem | awk '{print $1}'`
semmni=`cat /proc/sys/kernel/sem | awk '{print $2}'`
semopm=`cat /proc/sys/kernel/sem | awk '{print $3}'`
semmns=`cat /proc/sys/kernel/sem | awk '{print $4}'`
ipc=`grep RemoveIPC /etc/systemd/logind.conf`

totalmem=`free -b |grep Mem |awk '{print $2}'`
gtotalmem=`free -b |grep Mem |awk '{print $2}'| awk ' {printf "%.0f\n", $1/1024/1024/1024}'` #GB

echo ""
echo "==============================="
echo "Current kernel value"
echo "==============================="
echo "/etc/sysctl.conf"


#shmmax check
xxshmmax=$((`expr $gshmmax - $gtotalmem` + 0))
#echo "$gshmmax (shmmax gb) - $gtotalmem (totalmem gb) = $xxshmmax GB"

printf "kernel.shmmax ="
[ $xxshmmax -ge 0 ] || [ $gshmmax -ge 100 ] && printf " " || printf " *"
echo "$shmmax"

# shmmni check

xxshmmni=$((shmmni + 0 ))

printf "kernel.shmmni ="
[ $xxshmmni -ge 4096 ] && printf " " || printf " *"
echo "$shmmni"

xxshmall=`echo $shmmax | awk ' {printf "%.0f\n", $1/4096}'`
reshmall=`free -b |grep Mem |awk '{print $2}'| awk ' {printf "%.0f\n", $1/4096}'`

printf "kernel.shmall ="
[ $xxshmall -ge $reshmall ] && printf " " || printf " *"
echo "$shmall"


printf "kernel.sem ="
[ $semmsi -gt 250 ] && printf " " || printf " *"
printf "$semmsi"
[ $semmns -gt 32000 ] && printf " " || printf " *"
printf "$semmns"
[ $semopm -gt 100 ] && printf " " || printf " *"
printf "$semopm"
[ $semmni -gt 128 ] && printf " " || printf " *"
printf "$semmni\n"
echo "==============================="
echo "/etc/systemd/logind.conf"
echo $ipc
echo ""

echo "==============================="
echo "Goldilocks kernel recommend"
echo "==============================="
echo "/etc/sysctl.conf"

echo "kernel.shmmax = $totalmem"
echo "kernel.shmmni = 4096"
echo "kernel.shmall = $reshmall"
echo "kernel.sem = 250 32000 100 128"

echo "==============================="
echo "/etc/systemd/logind.conf"
echo "RemoveIPC=no"

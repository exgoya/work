#!/bin/sh

ps -ef | grep "gmon" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gmaster" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gserver" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gdispatcher" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gbalancer" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "cdispatcher" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "cserver" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gsql" | grep $LOGNAME | kill -9 `awk '{print $2}'`

ipcs -m | grep $LOGNAME | awk '{print "ipcrm -m " $2}' | sh -v
ipcs -q | grep $LOGNAME | awk '{print "ipcrm -q " $2}' | sh -v
ipcs -s | grep $LOGNAME | awk '{print "ipcrm -s " $2}' | sh -v
echo ""

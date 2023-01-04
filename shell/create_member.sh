CLEAN_DB()
{
ps -ef | grep "gmaster" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gserver" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gdispatcher" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gbalancer" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "glsnr" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "cserver" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "cdispatcher" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ps -ef | grep "gsql" | grep $LOGNAME | kill -9 `awk '{print $2}'`
ipcs -m | grep $LOGNAME | awk '{print "ipcrm -m " $2}' | sh
ipcs -q | grep $LOGNAME | awk '{print "ipcrm -q " $2}' | sh
ipcs -s | grep $LOGNAME | awk '{print "ipcrm -s " $2}' | sh

rm ${GOLDILOCKS_DATA}/db/*.dbf 2> /dev/null
rm ${GOLDILOCKS_DATA}/wal/*.ctl 2> /dev/null
rm ${GOLDILOCKS_DATA}/wal/*.log 2> /dev/null
rm ${GOLDILOCKS_DATA}/archive_log/*.log 2> /dev/null
rm ${GOLDILOCKS_DATA}/backup/*.inc 2> /dev/null
rm ${GOLDILOCKS_DATA}/trc/opt_* 2> /dev/null
rm ${GOLDILOCKS_DATA}/conf/sundb.properties.binary 2> /dev/null
rm ${GOLDILOCKS_DATA}/tmp/* 2> /dev/null
}

GROUP_CREATE_ONLY()
{
gcreatedb --cluster
gsql sys gliese --as sysdba --no-prompt <<EOF
\startup
ALTER SYSTEM OPEN GLOBAL DATABASE;
\q
EOF

glsnr --start
}

CLEAN_DB
GROUP_CREATE_ONLY

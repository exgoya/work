#*/1 * * * * sh /GOLDILOCKS/cron/check_and_rm_archive.sh >> /GOLDILOCKS/cron/check_and_rm_archive.log 2>&1
 
#!/bin/bash
 
pct=`df -h|grep GOLDI_LOG|awk '{print $5}'|grep -o '[0-9]*'`
 
if [ $pct -ge 80 ]
then
        rmcount=`rm -vif /GOLDI_LOG/archive_log/archive_* |wc -l`
        echo "[`date`] $rmcount archive file deleted!"
else
        echo "[`date`] GOLDI_LOG : $pct %"
fi


source ~/.bash_profile

$HOME/bin/stop.sh

glsnr --stop

rm -rf $GOLDILOCKS_DATA/db/*
rm -rf $GOLDILOCKS_DATA/wal/*
rm -rf $GOLDILOCKS_DATA/archive_log/*
rm -rf $GOLDILOCKS_DATA/backup/*

export GOLDILOCKS_DATABASE_INSTANCE_NAME=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER

gcreatedb --cluster --member=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER --host=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER_HOST --port=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER_PORT

gsql sys gliese --as sysdba --no-prompt << EOF
startup;
alter system open global database;
EOF

glsnr --start


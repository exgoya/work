source ~/.bash_profile

gcreatedb --cluster --member=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER --host=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER_HOST --port=$GOLDILOCKS_LOCAL_CLUSTER_MEMBER_PORT

gsql sys gliese --no-prompt << EOF
startup;

alter system open global database;

EOF

glsnr --start


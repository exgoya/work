RESET_MEMBER()
{
gsqlnet sys gliese --as sysdba --dsn=G2N2 --no-prompt <<EOF
--shutdown abort;
startup;
alter database reset local cluster member;
alter system open global database;
\q
EOF
gsqlnet sys gliese --as sysdba --dsn=G2N1 --no-prompt <<EOF
--shutdown abort;
startup;
alter database reset local cluster member;
alter system open global database;
\q
EOF
gsqlnet sys gliese --as sysdba --dsn=G1N2 --no-prompt <<EOF
--shutdown abort;
startup;
alter database reset local cluster member;
alter system open global database;
\q
EOF
gsqlnet sys gliese --as sysdba --dsn=G1N1 --no-prompt <<EOF
--shutdown abort;
startup;
alter database reset local cluster member;
alter system open global database;
\q
EOF
}
GROUP_CREATE_ONLY()
{
gsql sys gliese --as sysdba --no-prompt <<EOF
create cluster group g1 cluster member g1n1 host '10.10.11.101' port 10101;
create cluster group g2 cluster member g2n1 host '10.10.11.201' port 10101;
alter cluster group g1 add cluster member g1n2 host '10.10.11.102' port 10101;
alter cluster group g2 add cluster member g2n2 host '10.10.11.202' port 10101;
\q
EOF

#gsql sys gliese --as sysdba --import $GOLDILOCKS_HOME/admin/cluster/DictionarySchema.sql
#gsql sys gliese --as sysdba --import $GOLDILOCKS_HOME/admin/cluster/InformationSchema.sql
#gsql sys gliese --as sysdba --import $GOLDILOCKS_HOME/admin/cluster/PerformanceViewSchema.sql

}

RESET_MEMBER
#GROUP_CREATE_ONLY

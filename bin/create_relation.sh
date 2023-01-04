GROUP_CREATE_ONLY()
{
gsql sys gliese --as sysdba --no-prompt <<EOF
create cluster group g1 cluster member g1n1 host '192.168.0.119' port 25103;
alter cluster group g1 add cluster member g1n2 host '192.168.0.119' port 25303;
create cluster group g2 cluster member g2n1 host '192.168.0.119' port 25203;
alter cluster group g2 add cluster member g2n2 host '192.168.0.119' port 25403;
\q
EOF

gsql sys gliese --as sysdba --import $GOLDILOCKS_HOME/admin/cluster/DictionarySchema.sql --silent
gsql sys gliese --as sysdba --import $GOLDILOCKS_HOME/admin/cluster/InformationSchema.sql --silent
gsql sys gliese --as sysdba --import $GOLDILOCKS_HOME/admin/cluster/PerformanceViewSchema.sql --silent

for list in `ls $GOLDILOCKS_HOME/script/*.sql`
do
	gsql sys gliese --as sysdba -i $list --silent
done

}

GROUP_CREATE_ONLY


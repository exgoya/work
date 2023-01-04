doIt()
{
gsqlnet test test --dsn=GOLDILOCKS<< EOF
truncate table T_PG_ADS_LTE_SESSION_INFO;
commit;
\q
EOF
}

doIt

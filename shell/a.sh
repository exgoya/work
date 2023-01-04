doIt()
{
sqlplus -S vn/vn@vci_conv<< EOF
set heading off
select count(*) from DLM01M00_S;
EOF
}

doIt |grep [0-9]
#doIt |grep -o [0-9]* 

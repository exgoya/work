source ~/.bash_profile

gsql sys gliese --no-prompt << EOF
SELECT PROPERTY_NAME,PROPERTY_VALUE FROM V\$PROPERTY WHERE PROPERTY_NAME LIKE '%$1%';
EOF

#!/bin/sh

function Print_Table_From_Database(){
gsqlnet sys gliese --as sysdba --no-prompt << EOF
\set linesize 10000
\set pagesize 10000
\set timing off
SELECT '"' || TABLE_SCHEMA || '"."' || TABLE_NAME || '"' AS TABLE_LIST FROM ALL_ALL_TABLES WHERE TABLE_SCHEMA NOT IN ('DEFINITION_SCHEMA', 'DICTIONARY_SCHEMA') ORDER BY 1;
\quit
EOF
}

function Print_Db(){
gsqlnet sys gliese --as sysdba --no-prompt << EOF
\set linesize 10000
\set pagesize 10000
\set timing off
ddl_db
\quit
EOF
}

function Modify_File(){
        QUOTATION=\"
        while read line; do
                CHECK_QUOTATION=${line:0:1}
                if [ "${CHECK_QUOTATION}" = "${QUOTATION}" ]; then
                        echo "${line}" >> 2_MODIFY_TABLE_LIST.txt
                fi
        done < 1_DATABASE_TABLE_LIST.txt

        sed 's/\"//g' 2_MODIFY_TABLE_LIST.txt > 3_MODIFY_TABLE_LIST.txt
}

function Make_Folder(){
        mkdir -p gloader_${DATE}/sh
        mkdir -p gloader_${DATE}/import_log
        mkdir -p gloader_${DATE}/export_log
        mkdir -p gloader_${DATE}/data
        mkdir -p gloader_${DATE}/control
        mkdir -p gloader_${DATE}/history
        mkdir -p gloader_${DATE}/schema
}

function Make_File(){
        while read line; do
                echo "TABLE ${line}" > ${line}.ctl
                echo "FIELDS TERMINATED BY '^Cc__Cc^'" >> ${line}.ctl
                echo "LINES TERMINATED BY '^Rr__Rr^%n'" >> ${line}.ctl
                echo "gloadernet SYS gliese -i -c ../control/${line}.ctl -d ../data/${line}.dat" -l ../import_log/${line}.log -b ../import_log/${line}.bad -a 1000 -C 10000 -A -p 6 >> import.sh
                echo "gloadernet SYS gliese -e -c ../control/${line}.ctl -d ../data/${line}.dat" -l ../export_log/${line}.log -b ../export_log/${line}.bad -a 1000 -C 10000 -A >> export.sh
        done < 3_MODIFY_TABLE_LIST.txt
}

function Move_File(){
        mv *.ctl gloader_${DATE}/control
        mv *.txt gloader_${DATE}/history
        mv import.sh export.sh gloader_${DATE}/sh
        mv db.sql gloader_${DATE}/schema
}

DATE=$(date '+%Y%m%d_%H%M%S')

Print_Db > db.sql
Print_Table_From_Database > 1_DATABASE_TABLE_LIST.txt
Modify_File
Make_Folder
Make_File
Move_File

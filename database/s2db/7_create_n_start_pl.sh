#!/bin/bash

if [ $# -ne 3 ]; then
	echo "USAGE: $0 <sql_dir> <data_dir> <scale_factor>"
	exit 1
fi


CONFIG_FILE="0_config_db.ini"
function get_config() {
    key=$1
    line=$(grep -s "${key}" $CONFIG_FILE | sed -e 's/^[[:space:]]*//' | grep -v "^#" | head -1)
    value=${line#*=}
    echo $value
}


DB_HOST=$(get_config "DB_HOST")
DB_PORT=$(get_config "DB_PORT")
DB_USER=$(get_config "DB_USER")
DB_PASS=$(get_config "DB_PASS")
DB_NAME=$(get_config "DB_NAME")
DB_PARTITIONS=$(get_config "DB_PARTITIONS")


DIR_SQL="$1"
DIR_DATA="$2"
SF="$3"

DIR_SQL_ABS="$(realpath ${DIR_SQL})"
if [ ! -d ${DIR_SQL_ABS} ]; then
	echo "[WARN] Directory does not exist!! : ${DIR_SQL_ABS}"
	exit 1;
fi

DIR_DATA_ABS="$(realpath ${DIR_DATA})"
if [ ! -d ${DIR_DATA_ABS} ]; then
	echo "[WARN] Directory does not exist!! : ${DIR_DATA_ABS}"
	exit 1;
fi


echo "------------------------------"
echo "DB_HOST       : [$DB_HOST]"
echo "DB_PORT       : [$DB_PORT]"
echo "DB_USER       : [$DB_USER]"
echo "DB_PASS       : [${DB_PASS:0:1}...]"
echo "DB_NAME       : [$DB_NAME]"
echo "DB_PARTITIONS : [$DB_PARTITIONS]"
echo "DIR_SQL       : [$DIR_SQL] = [$DIR_SQL_ABS]"
echo "DIR_DATA      : [$DIR_DATA] = [$DIR_DATA_ABS]"
echo "------------------------------"

echo -n "Would you like to continue? [y/N]: "
read -r CONFIRM

if [ "$CONFIRM" != "y" -a "$CONFIRM" != "Y" ]; then
    echo "▒~\~X [$0 $*] aborted"
    exit 1;
fi

echo ""
echo "########## TRUNCATE TABLE ##########"

SQLFILE_TRUNCATE="${DIR_SQL_ABS}/truncate.sql"

singlestore -N -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" << _EOI_

use $DB_NAME

select concat("    -- TRUNCATE TABLE (BEGIN) : ", now()) as "";
source ${SQLFILE_TRUNCATE}
select concat("    -- TRUNCATE TABLE   (END) : ", now()) as "";

_EOI_
echo ""
echo "########## DROP_PIPELINE ##########"

for TBL_NM in customer lineitem nation orders part partsupp region supplier
do

singlestore --local-infile -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" << _EOI_
use $DB_NAME

DROP PIPELINE tpch_${SF}_${TBL_NM};

select concat("    -- DROP PIPELINE   (DONE : ${TBL_NM}) : ", now()) as "";

_EOI_

done


echo ""
echo "########## CREATE_PIPELINE ##########"

for TBL_NM in customer lineitem nation orders part partsupp region supplier
do

singlestore --local-infile -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" << _EOI_
use $DB_NAME

CREATE OR REPLACE PIPELINE tpch_${SF}_${TBL_NM}
	AS LOAD DATA FS "${DIR_DATA_ABS}/${TBL_NM}.tbl*"
	SKIP DUPLICATE KEY ERRORS
	INTO TABLE ${TBL_NM}
	FIELDS TERMINATED BY '|'
	LINES TERMINATED BY '|\n';

select concat("    -- CREATE PIPELINE   (DONE : ${TBL_NM}) : ", now()) as "";

_EOI_

done

for TBL_NM in customer lineitem nation orders part partsupp region supplier
do

singlestore --local-infile -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" << _EOI_
use $DB_NAME

select concat("    -- START PIPELINE (BEGIN : ${TBL_NM}) : ", now()) as "";
select now(6) into @begin;

start pipeline tpch_${SF}_${TBL_NM} foreground;

select now(6) into @end;
select concat("       elapae_time : ", timediff(@end, @begin)) as "";
select concat("    -- END PIPELINE   (END : ${TBL_NM}) : ", now()) as "";

_EOI_

done




#!/bin/bash


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


echo "----------------------------------------"
echo "DB_HOST       : [$DB_HOST]"
echo "DB_PORT       : [$DB_PORT]"
echo "DB_USER       : [$DB_USER]"
echo "DB_PASS       : [${DB_PASS:0:1}...]"
echo "DB_NAME       : [$DB_NAME]"
echo "----------------------------------------"

echo -n "Would you like to continue? [y/N]: "
read -r CONFIRM

if [ "$CONFIRM" != "y" -a "$CONFIRM" != "Y" ]; then
	echo "✘ [$0] aborted"
	exit 1;
fi

if [ "${DB_NAME}" != "tpch" ]; then
	echo -n "[WARN] Are you sure [DROP DATABASE ${DB_NAME};]? [y/N]: "
	read -r CONFIRM
	if [ "$CONFIRM" != "y" -a "$CONFIRM" != "Y" ]; then
		echo "✘ [$0] aborted"
		exit 1
	fi
fi


echo ""
echo "########## DROP DATABASE ##########"

singlestore -sN -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" 2> /dev/null << _EOI_

select now(6) into @begin;

drop database $DB_NAME;

select now(6) into @end;
select concat("    ELAPSE_TIME: ", timediff(@end, @begin)) as "";

_EOI_

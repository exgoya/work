#!/bin/bash

if [ $# -ne 6 ]; then
	echo "USAGE: $0 <db_host> <db_port> <db_db> <db_user> <db_pw> <query_file.sql>"
	exit 1
fi


DB_HOST="$1"
DB_PORT="$2"
DB_NAME="$3"
DB_USER="$4"
DB_PASS="$5"
QUERY_FILE="$6"

singlestore -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" $DB_NAME << _EOI_
select "${QUERY_FILE}" as "\n== QUERY_FILE ==";
select "---------- result:" as "";

select now(6) into @begin;
source $QUERY_FILE
select now(6) into @end;

select concat("    ", timediff(@end, @begin)) as "\n== ELAPSE_TIME ==";
_EOI_

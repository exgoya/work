#!/bin/bash
# References) https://github.com/sjp38/tpch-mariadb/blob/master/powertest.sh

IS_VERBOSE=0
if [ $1 = "-v" ]; then
	IS_VERBOSE=1
	shift 1
fi

if [ $# -ne 2 ] || ! [[ $1 =~ ^[0-9]+$ ]] || ! [[ $2 =~ ^[0-9]+$ ]] ; then
	echo "USAGE: $0 <sacle_factor(#number)> <number_of_query_sets(#number)>"
	exit 1
fi


SF=$1
NOS=$2

CONFIG_FILE="0_config_db.ini"
function get_config() {
    key=$1
    line=$(grep -sw "${key}" $CONFIG_FILE | sed -e 's/^[[:space:]]*//' | grep -v "^#" | head -1)
    value=${line#*=}
    echo $value
}

DB_HOST=$(get_config "DB_HOST")
DB_PORT=$(get_config "DB_PORT")
DB_USER=$(get_config "DB_USER")
DB_PASS=$(get_config "DB_PASS")
DB_NAME=$(get_config "DB_NAME")


Q_FILE_PREFIX="query"


function ms() {
	echo $((`date +%s%N` / 1000000))
}

function msec_to_sec() {
	MSECS=$1
	SECS=$(($MSECS / 1000))
	MSECS=$(($MSECS - $SECS * 1000))
	printf %d.%03d $SECS $MSECS
}


SF_DIR=data/sf$SF
declare -a ARR_CUM_DURATION
declare -a ARR_CNT
CUM_TOTAL_MSEC=0

for S_NUM in `seq 1 $NOS`
do
	printf "\n[SET#%04d]----------------------------------------" $S_NUM
	DURATION=0
	TOTAL_MSEC=0

	for Q_NUM in {1..22}
	do
		Q_FILE="${SF_DIR}/queries/${Q_FILE_PREFIX}${S_NUM}-${Q_NUM}.sql"
		if [ ! -f "$Q_FILE" ]; then
			printf "\n  [%02d] %-28s : NOT FOUND!!" $Q_NUM $Q_FILE
			continue;
		fi

		START=`ms`
		if [ $IS_VERBOSE -eq 1 ]; then
			./3-1_run_qry_one.sh "$DB_HOST" "$DB_PORT" "$DB_NAME" "$DB_USER" "$DB_PASS" "${Q_FILE}"
		else
			./3-1_run_qry_one.sh "$DB_HOST" "$DB_PORT" "$DB_NAME" "$DB_USER" "$DB_PASS" "${Q_FILE}" > /dev/null 2>&1
		fi
		END=`ms`

		DURATION=$(( $END - $START ))
		printf "\n  [%02d] %-28s : %8s s" $Q_NUM $Q_FILE "`msec_to_sec $DURATION`"

		ARR_CUM_DURATION[$Q_NUM]=$(( ${ARR_CUM_DURATION[$Q_NUM]} + $DURATION ))
		ARR_CNT[$Q_NUM]=$(( ${ARR_CNT[$Q_NUM]} + 1 ))
		TOTAL_MSEC=$(( $TOTAL_MSEC + $DURATION ))
	done

	printf "\n--------------------------------------------------"
	printf "\n  [SET#%04d] SUB TOTAL(%6s)      : %8s s\n\n" $S_NUM $SF_DIR `msec_to_sec $TOTAL_MSEC`

	CUM_TOTAL_MSEC=$(( $CUM_TOTAL_MSEC + $TOTAL_MSEC ))

done


printf "\n---------------------------------------------"
printf "\n| %5s | %5s | %10s | %12s |" "QUERY" "# SET" "TOTAL(sec)" "AVERAGE(sec)"
printf "\n---------------------------------------------"

for Q_NUM in {1..22}
do
	AVG=$(( ${ARR_CUM_DURATION[$Q_NUM]} / ${ARR_CNT[$Q_NUM]} ))
	printf "\n| %5s | %5s | %10s | %12s |" "$Q_NUM" "${ARR_CNT[$Q_NUM]}" "`msec_to_sec ${ARR_CUM_DURATION[$Q_NUM]}`" "`msec_to_sec $AVG`"
done

printf "\n---------------------------------------------"
C_AVG=$(( $CUM_TOTAL_MSEC / $NOS ))
printf "\n| TOTAL | %5s | %10s | %12s |" "$NOS" "`msec_to_sec $CUM_TOTAL_MSEC`" "`msec_to_sec $C_AVG`"
printf "\n---------------------------------------------\n\n"

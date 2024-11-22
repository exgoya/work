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


echo "----------------------------------------"
echo "DB_HOST_MA : [$DB_HOST]"
echo "DB_PORT_MA : [$DB_PORT]"
echo "DB_USER    : [$DB_USER]"
echo "DB_PASS    : [${DB_PASS:0:1}...]"
echo "----------------------------------------"

CONFIRM="N"
echo -n "[WARN] Are you sure [DROP ALL FROM PLANCACHE;]? [y/N]: "
read -r CONFIRM

if [ "$CONFIRM" != "y" -a  "$CONFIRM" != "Y" ]; then
	exit 1;
fi

singlestore -h$DB_HOST -P$DB_PORT -u$DB_USER -p"$DB_PASS" -sN -e "show aggregators; show leaves;" 2>&1 | grep -v "insecure" | cut -f1,2 |
while read -r line
do
node=($line)

singlestore -h${node[0]} -P${node[1]} -p"$DB_PASS" -sN -e "DROP ALL FROM PLANCACHE;" 2>&1 | grep -v "insecure"
echo "    Excuted [DROP ALL FROM PLANCACHE;] on node ${node[0]}:${node[1]}"

done

echo ""

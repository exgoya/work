#!/bin/bash

if [ $# -ne 2 ] || ! [[ $1 =~ ^[0-9]+$ ]] || ! [[ $2 =~ ^[0-9]+$ ]] ; then
	echo "USAGE: $0 <scale_factor(#number)> <number_of_sets(#number)>"
	exit 1
fi

SF=$1
NOS=$2
Q_DIR=data/sf${SF}/queries

echo "########## BEGIN GENERATE : [$Q_DIR] ##########"

CONFIRM="N"
if [ 0 -ne `\ls ${Q_DIR}/*.sql 2> /dev/null | wc -l` ]; then
	echo -n "[WARN] File[${Q_DIR}/*.sql] exists!! Would you like to continue? [y/N]: "
	read -r CONFIRM

	if [ "$CONFIRM" != "y" -a "$CONFIRM" != "Y" ]; then
		echo "✘ [$0 $*] aborted"
		exit 1;
	fi
fi

mkdir -p $Q_DIR
export DSS_QUERY=dbgen/queries

for loop in `seq 1 $NOS`; do
	for i in {1..22}; do
		dbgen/qgen -s $SF $i -b dbgen/dists.dss > ${Q_DIR}/query${loop}-${i}.sql
	done
done

pwd
ls -rtl ${Q_DIR}/*.sql
echo "########## END   GENERATE : [$Q_DIR] ##########"

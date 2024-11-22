#!/bin/bash

if [ $# -ne 1 ] || ! [[ $1 =~ ^[0-9]+$ ]]; then
	echo "USAGE: $0 <scale_factor(#number)>"
	exit 1
fi

SF=$1
D_DIR=data/sf$SF

echo "########## BEGIN GENERATE : [$D_DIR] ##########"

CONFIRM="N"
if [ 0 -ne `\ls ${D_DIR}/*.tbl 2> /dev/null | wc -l` ]; then
	echo -n "[WARN] File[${D_DIR}/*.tbl] exists!! Would you like to continue? [y/N]: "
	read -r CONFIRM

	if [ "$CONFIRM" != "y" -a "$CONFIRM" != "Y" ]; then
		echo "✘ [$0 $*] aborted"
		exit 1;
	fi
fi

ROOT_DIR=$(realpath .)
mkdir -p $D_DIR
cd $D_DIR
$ROOT_DIR/dbgen/dbgen -vf -b $ROOT_DIR/dbgen/dists.dss -s $SF

echo ""
echo "#############################################"
pwd
ls -rtl *.tbl
echo "########## END   GENERATE : [$D_DIR] ##########"

#!/bin/bash

if [ $# -ne 2 ] || ! [[ $1 =~ ^[0-9]+$ ]] || ! [[ $2 =~ ^[0-9]+$ ]] ; then
	echo "USAGE: $0 <scale_factor(#number)> <number_of_query_sets(#number)>"
	exit 1
fi

SF=$1
NOS=$2

./1-1_dbgen.sh $SF

echo ""
./1-2_qgen.sh $SF $NOS

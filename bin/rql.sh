#!/bin/bash

while true
do
    date
    echo "$1;"  |  gsqlnet sys gliese --no-prompt
    sleep ${2}s
    clear
done

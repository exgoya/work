#!/bin/bash

### Set Connection Information ###
REMOTE_HOST="localhost"
REMOTE_USER="godb1"
#REMOTE_PASSWORD="pms5124"

### Set Variables for remote Environment Variable ###
GOLDILOCKS_DATA="GOLDILOCKS_DATA"
GOLDILOCKS_DATA_PATH="\$HOME/goldilocks_data"

### Define functions ###
function getListenerStatus() {
sshpass -v ssh $REMOTE_USER@$REMOTE_HOST "
export $GOLDILOCKS_DATA=$GOLDILOCKS_DATA_PATH
./goldilocks_home/bin/glsnr --status
exit
"
}

function getListenerPort() {
	getListenerStatus | grep Port| awk '{print $4}'
	#getListenerStatus | grep Port | awk '{print $8}'
}

### Run ###
echo "Listener port : "`getListenerPort`

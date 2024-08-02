#!/bin/bash

# user 와 listen port는 배열 순서에 맞춰서 입력이 필요합니다.
# user 는 필수로 입력이 필요하고
# listen_ports는 입력하지 않으면 ssh 로 확인하는 절차가 추가 됩니다.

USERS=()
LISTEN_PORTS=()
CLUSTER_MEMBERS=()
HOSTS=()

ODBC_FILE="$HOME/.odbc.ini"
LOCATOR_FILE="$HOME/.locator.ini"
CLOCATOR_FILE="$HOME/.clocator.ini"
LOCATION_FILE="$GOLDILOCKS_DATA/wal/location.ctl"
GDUMP_FILE="$HOME/location_output.txt"

GOLDILOCKS_DATA_PATH="\$HOME/goldilocks_data"

###############################################################

read_location_file() {
	if [ ! -f "$LOCATION_FILE" ]; then
		echo "location 파일을 찾을 수 없습니다: $LOCATION_FILE "
		exit 1
	fi

	gdump location "$LOCATION_FILE" > "$GDUMP_FILE"

	local current_group=""
	while IFS=':' read -r line; do
		if [[ "$line" =~ \[G.*\] ]]; then
			current_group=$(echo "$line" | tr -d '[]' | tr -d ' ')
			CLUSTER_MEMBERS+=("$current_group")
		elif [[ "$line" =~ CLUSTER_MEMBER_HOST ]]; then
			host=$(echo "$line" | awk -F ': ' '{print $2}')
			HOSTS+=("$host")
		fi
	done < "$GDUMP_FILE"

	rm -f "$GDUMP_FILE"
}

sshpass_user_check() {
	if ! sshpass -V &> /dev/null; then
		echo "Error: sshpass is not installed."

		read -p "Please enter listen_ports : " USER_PORTS

		IFS=',' read -ra LISTEN_PORTS <<< "$USER_PORTS"
	else

		getListenerStatus() {
			local user=$1
			local host=$2
			local status=$(sshpass ssh $user@$host "
			export GOLDILOCKS_DATA=$GOLDILOCKS_DATA_PATH
			./goldilocks_home/bin/glsnr --status
			exit")
			echo "$status"
		}

		getListenerPort() {
			local user=$1
			local host=$2
			local status=$(getListenerStatus "$user" "$host" )
			local port=$(echo "$status" | grep unix-glsnr|awk -F. '{print $2}')
			echo "$port"     
		}

		if [ $(( ${#USERS[@]} )) -eq 1 ]; then
			host_count=$(( ${#HOSTS[@]} ))
			for i in $(seq 0 $((host_count-1))); do
				local user=${USERS[0]}
				local host=${HOSTS[$i]}
				printf "plaese input password ( $user@$host ) : "
				local port=$(getListenerPort "$user" "$host" )
				LISTEN_PORTS+=("$port")
				echo "Listener Port for ${HOSTS[$i]}: $port"
			done
		else
			host_count=$(( ${#HOSTS[@]} ))
			for i in $(seq 0 $((host_count-1))); do
				local user=${USERS[$i]}
				local host=${HOSTS[$i]}
				printf "plaese input password ( $user@$host ) : "
				local port=$(getListenerPort "$user" "$host" )
				LISTEN_PORTS+=("$port")
				echo "Listener Port for ${HOSTS[$i]}: $port"
			done
		fi
	fi
}

generate_locator_file() {
	if [ -f "$LOCATOR_FILE" ]; then
		rm "$LOCATOR_FILE"
	fi

	locator_count=$(( ${#HOSTS[@]} ))
	for i in $(echo "$(seq 0 $((locator_count-1)))" | tr ' ' '\n' | sort); do
		local host=${HOSTS[$i]}
		local port=${LISTEN_PORTS[$i]}
		echo -e "\n[${CLUSTER_MEMBERS[$i]}]" >> "$LOCATOR_FILE"
		echo "HOST=${HOSTS[$i]}" >> "$LOCATOR_FILE"
		if [ $(( ${#LISTEN_PORTS[@]} )) -eq 1 ]; then
			echo "PORT=${LISTEN_PORTS[0]}" >> "$LOCATOR_FILE"
		else
			echo "PORT=${LISTEN_PORTS[$i]}" >> "$LOCATOR_FILE"
		fi
	done

	if [ -f "$CLOCATOR_FILE" ]; then
		rm "$CLOCATOR_FILE"
	fi

	for i in $(echo "$(seq 0 $((locator_count-1)))" | tr ' ' '\n' | sort); do
		local host=${HOSTS[$i]}
		local port=${LISTEN_PORTS[$i]}
		echo -e "\n[${CLUSTER_MEMBERS[$i]}]" >> "$CLOCATOR_FILE"
		echo "HOST=${HOSTS[$i]}" >> "$CLOCATOR_FILE"
		if [ $(( ${#LISTEN_PORTS[@]} )) -eq 1 ]; then
			echo "PORT=${LISTEN_PORTS[0]}" >> "$CLOCATOR_FILE"
		else
			echo "PORT=${LISTEN_PORTS[$i]}" >> "$CLOCATOR_FILE"
		fi
	done
}

generate_odbc_file() {
	if [ ! -f "$ODBC_FILE" ]; then
		echo "[GOLDILOCKS]" > "$ODBC_FILE"
		echo "PROTOCOL=TCP" >> "$ODBC_FILE"
		echo "HOST=${HOSTS[0]}" >> "$ODBC_FILE"
		echo "PORT=${LISTEN_PORTS[0]}" >> "$ODBC_FILE"
		echo "LOCATOR_DSN=LOCATOR" >> "$ODBC_FILE"

		odbc_count=$(( ${#HOSTS[@]} ))
		for i in $(echo "$(seq 0 $((odbc_count-1)))" | tr ' ' '\n' | sort); do
			local cluster_member="${CLUSTER_MEMBERS[$i]}"
			local host=${HOSTS[$i]}
			local port=${LISTEN_PORTS[$i]}
			echo -e "\n[$cluster_member]" >> "$ODBC_FILE"
			echo "PROTOCOL=TCP" >> "$ODBC_FILE"
			echo "HOST=${HOSTS[$i]}" >> "$ODBC_FILE"
			if [ $(( ${#LISTEN_PORTS[@]} )) -eq 1 ]; then
				echo "PORT=${LISTEN_PORTS[0]}" >> "$ODBC_FILE"
			else
				echo "PORT=${LISTEN_PORTS[$i]}" >> "$ODBC_FILE"
			fi
			echo "LOCATOR_DSN=LOCATOR" >> "$ODBC_FILE"
		done

		echo -e "\n[CSTARTUP]" >> "$ODBC_FILE"
		echo "PROTOCOL=TCP" >> "$ODBC_FILE"
		echo "HOST=${HOSTS[0]}" >> "$ODBC_FILE"
		echo "PORT=${LISTEN_PORTS[0]}" >> "$ODBC_FILE"
		echo "LOCATOR_DSN=CLOCATOR" >> "$ODBC_FILE"
		
		echo -e "\n[LOCATOR]" >> "$ODBC_FILE"
		echo "FILE=$LOCATOR_FILE" >> "$ODBC_FILE"
		
		echo -e "\n[CLOCATOR]" >> "$ODBC_FILE"
		echo "FILE=$CLOCATOR_FILE" >> "$ODBC_FILE"

	gsqlnet sys gliese --dsn CSTARTUP --as sysdba <<EOF
	cstartup;
	quit;
EOF

	else
		if grep -q "\[CSTARTUP\]" "$ODBC_FILE" && grep -q "\[CLOCATOR\]" "$ODBC_FILE"; then
			gsqlnet sys gliese --dsn CSTARTUP --as sysdba <<EOF
			cstartup;
			quit;
EOF
		else
			echo -e "\n[CSTARTUP]" >> "$ODBC_FILE"
			echo "PROTOCOL=TCP" >> "$ODBC_FILE"
			echo "HOST=${HOSTS[0]}" >> "$ODBC_FILE"
			echo "PORT=${LISTEN_PORTS[0]}" >> "$ODBC_FILE"
			echo "LOCATOR_DSN=CLOCATOR" >> "$ODBC_FILE"

			echo -e "\n[CLOCATOR]" >> "$ODBC_FILE"
			echo "FILE=$CLOCATOR_FILE" >> "$ODBC_FILE"
			gsqlnet sys gliese --dsn CSTARTUP --as sysdba <<EOF
			cstartup;
			quit;
EOF
		fi
	fi
}

main() {
	read_location_file
	if [ $(( ${#LISTEN_PORTS[@]} )) -eq 0 ]; then
		sshpass_user_check
	fi
	generate_locator_file
	generate_odbc_file
}

main

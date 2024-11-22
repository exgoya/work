#!/bin/bash

# Usage check
if [ $# -ne 2 ] || ! [[ $1 =~ ^[0-9]+$ ]]; then
    echo "USAGE: $0 <scale_factor(#number)> <chunks(#number)>"
    exit 1
fi

SF=$1
CHUNKS=$2
ROOT_DIR=$(realpath .)       # Current directory absolute path
D_DIR="data/sf$SF"           # Data directory
MAX_PARALLEL=$(nproc)        # Dynamically set based on CPU cores

# Record script start time
SCRIPT_START_TIME=$(date +%s)

echo "########## BEGIN GENERATE : [$D_DIR] ##########"

# Function: Check and confirm existing files
check_existing_files() {
    if find "$D_DIR" -type f -name "*.tbl*" 2>/dev/null | grep -q .; then
        echo "[WARN] Files already exist in [$D_DIR]."
        read -p "Would you like to continue? [y/N]: " CONFIRM
        [[ "$CONFIRM" =~ ^[yY]$ ]] || { echo "Aborted by user."; exit 1; }
    fi
}

# Function: Wait for available job slots
wait_for_slot() {
    while (( $(jobs -rp | wc -l) >= MAX_PARALLEL )); do
        sleep 0.1
    done
}

# Function: Process execution
run_dbgen() {
    local id=$1
    echo "[PROCESS $id] Starting dbgen..."
    stdbuf -oL $ROOT_DIR/dbgen/dbgen -vf -b $ROOT_DIR/dbgen/dists.dss -s $SF -S $id -C $CHUNKS 2>&1 | \
    sed "s/^/[PROCESS $id] /"
    if [[ $? -eq 0 ]]; then
        echo "[PROCESS $id] Completed successfully."
    else
        echo "[PROCESS $id] Failed!"
        return 1
    fi
}

# Main logic
mkdir -p "$D_DIR"
cd $D_DIR
check_existing_files

# Start processes and monitor failures
FAILURE_COUNT=0

for ((i=1; i<=CHUNKS; i++)); do
    wait_for_slot
    run_dbgen "$i" || ((FAILURE_COUNT++)) &
done

# Wait for all jobs to complete
wait

# Record script end time and calculate duration
SCRIPT_END_TIME=$(date +%s)
TOTAL_SCRIPT_DURATION=$((SCRIPT_END_TIME - SCRIPT_START_TIME))

# Display results
echo ""
echo "#############################################"
echo "Generated files in: $D_DIR"
find . -type f -name "*.tbl*" -exec du -h {} + | sort -h 

# Summary and total execution time
echo ""
echo "Total execution time: $TOTAL_SCRIPT_DURATION seconds"
if [[ $FAILURE_COUNT -eq 0 ]]; then
    echo "All processes completed successfully!"
else
    echo "$FAILURE_COUNT process(es) failed. Check above output for details."
fi
echo "########## END   GENERATE : [$D_DIR] ##########"

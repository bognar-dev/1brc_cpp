#!/bin/bash
export TIMEFORMAT='%2R'
BRANCH_NAME=$(git rev-parse --abbrev-ref HEAD)
TIMESTAMP=$(date +%Y%m%d%H%M%S)

# Navigate to the project directory
cd ./cmake-build-debug

TIMES=""

echo "Running 1_brc_cpp_${BRANCH_NAME}"
for n in {1..5}; do
    TIMES+="$({ time ./1brc_cpp > /dev/null; } 2>&1 ) "
    echo "1_brc_cpp_${BRANCH_NAME} run $n of 5"
    sleep 1
done

echo -e $TIMES | awk "BEGIN { RS = \" \"; sum = 0.0; } {  sum += \$1; } END { printf \"1_brc runtime=[ %s] average=%.2fs\t\n\", \"$TIMES\", sum/5.0 }" | tee "../perf/1_brc_perf_${BRANCH_NAME}.txt"
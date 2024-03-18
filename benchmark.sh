#!/bin/bash
export TIMEFORMAT='%2R'
# Navigate to the project directory
cd /home/bognar/projects/1brc_cpp/cmake-build-debug

# Run the perf command
/usr/lib/linux-tools/5.15.0-100-generic/perf record --freq=997 --call-graph dwarf -q -o /mnt/c/Users/Niklas/AppData/Local/Temp/clion1203125129335040069perf /home/bognar/projects/1brc_cpp/cmake-build-debug/1brc_cpp

    TIMES=""
    for n in {1..5}; do
        TIMES+="$({ time /home/bognar/projects/1brc_cpp/cmake-build-debug/1brc_cpp > /dev/null; } 2>&1 ) "
        sleep 1
    done

echo -e $TIMES | awk "BEGIN { RS = \" \"; sum = 0.0; } {  sum += \$1; } END { printf \"1_brc runtime=[ %s] average=%.2fs\t\n\", \"$TIMES\", sum/5.0 }"

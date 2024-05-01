#!/bin/bash
export TIMEFORMAT='%2R'


PROGRAMS=(
    "hashmap"
    "parse-double"
    "fread-chunks"
    "loop-unrolling"
    #"parallelize"
    #"mmap"
)

DESCRIPTIONS=(
    ""
    "linear-search by city name (baseline)"
    "hashmap with linear probing"
    "custom temperature float parser instead of strod"
    "fread with 64MB chunks instead of line-by-line"
    "unroll parsing of city name and generating hash"
    "parallelize across 16 threads"
    "mmap entire file instead of fread in chunks"
)

# Array of line counts
line_counts=(1000 10000 100000 1000000 10000000 100000000 1000000000)

# Create an array of filenames based on the line counts
FILES=()
for lines in "${line_counts[@]}"; do
    FILES+=("../data/measurement_${lines}_lines.txt")
done

# Create a CSV file to store the runtimes
echo "File,Program,Description,Runtime1,Runtime2,Runtime3" > runtimes.csv
cd cmake-build-debug || exit
make hashmap parse-double fread-chunks loop-unrolling
# Loop over all files in the FILES array
for FILE in "${FILES[@]}"; do
    if [ -f "$FILE" ]; then
        for PROGRAM in "${PROGRAMS[@]}"; do


            # run each program 3 times, capturing time output
            TIMES=()
            for n in {1..3}; do
                TIMES+=("$({ time ./"$PROGRAM" "$FILE" > /dev/null; } 2>&1 )")
                sleep 1
            done

            # Print the data to the console
            printf "$FILE,$PROGRAM,${DESCRIPTIONS[$PROGRAM]},${TIMES[0]},${TIMES[1]},${TIMES[2]}\n"

            # Write the data to the CSV file
            echo "$FILE,$PROGRAM,${DESCRIPTIONS[$PROGRAM]},${TIMES[0]},${TIMES[1]},${TIMES[2]}" >> runtimes.csv
        done
    else
        echo "File $FILE does not exist."
    fi
done
#!/bin/bash
export TIMEFORMAT='%2R'
BRANCH_NAME=v1
TIMESTAMP=$(date +%Y%m%d%H%M%S)


# Define an array of file lengths
file_lengths="100_000 1_000_000 10_000_000 100_000_000"


mkdir -p /project/data

for length in $file_lengths
do
   # Run the Python script with the current file length and a fixed name
   python3 /project/create_measurements.py --rows "$length" --name "meassurements_$length"
done


# Create a CSV file and write the header
mkdir -p /project/perf
echo "File,Run,Time" > "/project/perf/1_brc_perf_${BRANCH_NAME}.csv"

echo "Running 1_brc_cpp_${BRANCH_NAME}"
# Loop over all text files in the data directory
for FILE in /project/data/*.txt; do
    echo "Running tests on $FILE"

    # run the program once, capturing time output
    TIME="$({ time ./1brc_cpp $FILE > /dev/null; } 2>&1 )"
    echo "Time: $TIME"
    # Write the filename, run number, and time to the CSV file
    echo "$FILE,1,$TIME" >> "/project/perf/1_brc_perf_${BRANCH_NAME}.csv"
    sleep 1
done

# Calculate average time and append to the CSV file
awk -F, '{sum[$1] += $3; count[$1]++} END {for (i in sum) print i, sum[i]/count[i]}' "/project/perf/1_brc_perf_${BRANCH_NAME}.csv" | awk 'BEGIN {OFS=","} {print $1, $2}' >> "/project/perf/1_brc_perf_${BRANCH_NAME}.csv"
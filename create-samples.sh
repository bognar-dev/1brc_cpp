#!/bin/bash

# Array of line counts
line_counts=(1000 10000 100000 1000000 10000000 100000000 1000000000)
cd cmake-build-debug || exit
make create-sample
# Loop over the line counts
for lines in "${line_counts[@]}"; do
     # Create a sample file with the given number of lines
     echo "Creating sample file with $lines lines..."
    ./create-sample $lines
done

echo "Files created."
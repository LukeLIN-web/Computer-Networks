#!/bin/bash

# Create a directory for log files (if it doesn't exist)
log_dir="log_results"
# mkdir -p "$log_dir"

# Loop through all .log files in the current directory
for file in *.log; do
    if [ -f "$file" ]; then
        # Define the log file name for this input file
        log_file="$log_dir/${file%.log}_results.log"
        
        echo "Processing $file and writing results to $log_file"
        
        # Run the awk command and redirect the output to the log file
        awk '/\[ *[0-9]+\]/{print "Bitrate:", $7, "Cwnd:", $10, $11}' "$file" > "$log_file"
        
        echo "---------------------"
    fi
done

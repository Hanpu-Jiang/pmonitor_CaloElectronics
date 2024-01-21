#!/bin/bash

# Check if two arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 FirstNumber LastNumber"
    exit 1
fi

# Read arguments
num1=$1
num2=$2

# Ensure that firstNumber is less than or equal to secondNumber
if [ "$num1" -gt "$num2" ]; then
    echo "Usage: $0 FirstNumber LastNumber"
    exit 1
fi

# Step 1: Go to directory macro/ and do make
cd macro
make

# Step 2: Run make_runlist.sh with num1 and num2
sh make_runlist.sh "$num1" "$num2"

# Step 3: Run do_analysis.sh
sh do_analysis.sh

echo "Done all analysis."

# Step 4: Run do_summary.sh
sh do_summary.sh

echo
echo "COMPLETE!"
echo
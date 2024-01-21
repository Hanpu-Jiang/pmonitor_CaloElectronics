#!/bin/bash

echo
echo "Starting runlist generation."
echo

# Check if two arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 FirstNumber LastNumber"
    exit 1
fi

# Read arguments
firstNumber=$1
secondNumber=$2

# Ensure that firstNumber is less than or equal to secondNumber
if [ "$firstNumber" -gt "$secondNumber" ]; then
    echo "Usage: $0 FirstNumber LastNumber"
    exit 1
fi

# Write numbers to runnumber.list
for (( num=$firstNumber; num<=$secondNumber; num++ )); do
    echo $num
done > runnumber.list

echo "Done runlist generation."
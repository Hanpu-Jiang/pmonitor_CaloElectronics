#!/bin/bash

hot_tower_list_file="hot_tower_list.txt"
> "$hot_tower_list_file"

echo
echo "Starting summarization."
echo

for file in ../run_result/run_info_*.txt; do
    runnumber=$(basename "$file" .txt | sed 's/run_info_//')
    while IFS= read -r line; do
        echo "$runnumber $line" >> "$hot_tower_list_file"
    done < "$file"
done

echo "Starting hot tower counting."

root -l -q -b count_hot_tower.C

rm "$hot_tower_list_file"

echo
echo "Done all summarization."
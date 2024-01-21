#!/bin/bash

run_numbers_file="runnumber.list"
general_info_file="../general_info.txt"

echo
echo "Starting analysis."
echo

while IFS= read -r run_number; do
    file_list="../run_result/runfile_${run_number}.list"
    > "$file_list"

    echo "Run ${run_number}:" >> "$general_info_file"

    echo "Starting analysis for run ${run_number}."
    echo "Checking EMCal files."
    ls /sphenix/lustre01/sphnxpro/commissioning/emcal/junk/*-000${run_number}-0000.prdf >> "$file_list"
    echo "Checking HCal files."
    ls /sphenix/lustre01/sphnxpro/commissioning/HCal/junk/*-000${run_number}-0000.prdf >> "$file_list"
    echo "Checking MBD files."
    ls /sphenix/lustre01/sphnxpro/commissioning/mbd/junk/*-000${run_number}-0000.prdf >> "$file_list"
    echo "Checking SEPD & ZDC files."
    ls /sphenix/lustre01/sphnxpro/commissioning/ZDC/junk/*-000${run_number}-0000.prdf >> "$file_list"

    line_count=$(wc -l < "$file_list")
    echo "Number of files: $line_count"
    echo "Number of files: $line_count" >> "$general_info_file"

    while IFS= read -r file_address; do
        sh saHCal.sh "$file_address"
    done < "$file_list"

    mv ../run_result/run_info.txt ../run_result/run_info_${run_number}.txt
    mv ../run_result/run_hist.root ../run_result/run_hist_${run_number}.root

    echo
    echo "Run ${run_number} is done."
    echo
    echo

    echo "Run ${run_number} is done." >> "$general_info_file"
    echo >> "$general_info_file"
    rm "$file_list"

done < "$run_numbers_file"
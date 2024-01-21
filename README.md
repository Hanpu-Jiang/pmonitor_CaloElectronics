
# Usage

```bash
sh run.sh FirstRunNumber LastRunNumber
```

## Output Files

1. `general_info.txt`: The general file health and run status check. `run.sh` will only update this file, instead of recreating.
2. `hot_tower_summary.txt`: Hot tower information of all runs in `run_result`.
3. `run_result/run_hist_*.root`: The hot tower's signal figure.
4. `run_result/run_info_*.txt`: Packet number, channel number, and N_entry for each run.

## Notes

1. The hot tower is identified with the following rules: 
   - hot signal case 1: 12 samples' RMS of a single event > 6.
   - hot signal case 2: 12 samples' mean of a single event > 7000 ADC.
   - 1% (10 out of 1000) events has hot signal. 
You can change the threshold in `saHCal.h`. For the 1% frequency, you have to change the `frequency_threshold` in `saHCal.h` and the `prun(#events)` in `saHCal.C`.

2. If you want to analyze a particular run list, please change the `runnumber.list` in the `macro/` directory. The format is that each line contains one run number. The `make_runlist.sh` script can help generate the run list and can be used as: 

```bash
sh make_runlist.sh FirstRunNumber LastRunNumber
```


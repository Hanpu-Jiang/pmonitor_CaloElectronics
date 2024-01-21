#! /bin/bash

FILE="$1"

if [ -z "$FILE" ] ; then

    root -l -q -b saHCal.C\(0\)
else

    root -l -q -b saHCal.C\(\"$FILE\"\)
fi
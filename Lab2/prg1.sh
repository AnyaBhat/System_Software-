#!/bin/bash
#script.sh : Simple shell script
echo “Today’s date: `date`”
echo “This month’s calendar:”
month=$(date "+%m")
year=$(date "+%Y")
echo "This month's calendar:"
cal "$month" "$year"

echo “My shell: $SHELL”

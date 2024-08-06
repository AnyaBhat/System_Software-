#!/bin/bash

# Check if the correct number of arguments are provided
if [ $# -ne 3 ]; then
  echo "Usage: $0 filename start_line end_line"
  exit 1
fi

# Assign arguments to variables
filename=$1
start_line=$2
end_line=$3

# Check if the file exists
if [ ! -f "$filename" ]; then
  echo "File '$filename' does not exist."
  exit 1
fi

# Display lines from start_line to end_line
sed -n "${start_line},${end_line}p" "$filename"

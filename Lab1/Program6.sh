#!/bin/bash

# Check if the correct number of arguments are provided
if [ $# -ne 3 ]; then
  echo "Usage: $0 filename start_line end_line"
  exit 1
fi

file1=$1
file2=$2
file3=$3

op_file="concat.txt"
sort_file="sorted.txt"


for file in "$file1" "$file2" "$file3" do 
  if[!-f "$file"];then
    echo"File '$file' does not exist"
    exit 1
  fi
done
cat "$file1""$file2""$file3">"$op_file"

sort "$op_file">"$sorted_file"
echo "Concatenation file created:$op_file"
echo "Sorted file created:$sort_file"

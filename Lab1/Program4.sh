#!/bin/bash

# Prompt the user to enter the file name
echo "Enter the file name:"
read filename

# Check if the file exists in the current directory
if [ -f "$filename" ]; then
  # Display all lines in the file containing the word "manipal"
  echo "Lines containing the word 'manipal' in the file '$filename':"
  grep -i "manipal" "$filename"
else
  # Print an error message if the file does not exist
  echo "File '$filename' does not exist in the current directory."
fi

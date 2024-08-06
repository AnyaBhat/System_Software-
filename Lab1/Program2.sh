#!/bin/bash

# Prompt the user to enter the directory name
echo "Enter the directory name:"
read dirname

# Check if the directory exists
if [ -d "$dirname" ]; then
  # List all .c files in the specified directory
  echo "Files ending with .c in the directory '$dirname':"
  ls "$dirname"/*.c 2>/dev/null
else
  # Print an error message if the directory does not exist
  echo "Directory '$dirname' does not exist."
fi

#!/bin/sh

# List all files in the current directory with read, write, and execute permissions for the user
echo "Files with read, write, and execute permissions for the user:"

for file in *; do
  if [ -f "$file" ] && [ -r "$file" ] && [ -w "$file" ] && [ -x "$file" ]; then
    echo "$file"
  fi
done

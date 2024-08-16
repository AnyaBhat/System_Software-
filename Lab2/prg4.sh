#!/bin/bash
printf "%-10s %-10s %-30s %-20s %-20s\n" "Permissions" "Size" "Filename" "Mod Time" "Access Time"
for file in "$@"; do
    if [ -e "$file" ]; then
        # Get permissions, size, and modification time with ls
        ls_output=$(ls -l "$file")
        perms=$(echo "$ls_output" | awk '{print $1}')
        size=$(echo "$ls_output" | awk '{print $5}')
        filename=$(echo "$ls_output" | awk '{print $9}')
        mtime=$(echo "$ls_output" | awk '{print $6, $7, $8}')
        
        # Get the last access time with stat
        atime=$(stat -c "%x" "$file")
        
        # Print the results
        printf "%-10s %-10s %-30s %-20s %-20s\n" "$perms" "$size" "$filename" "$mtime" "$atime"
    else
        echo "File '$file' not found."
    fi
done

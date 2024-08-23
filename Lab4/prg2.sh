#!/bin/bash
echo "Enter a filename"
read file

fd="$file"
if [ ! -e "$fd" ];then
	echo "Error File does not exist"
	exit 1
fi 

echo "File information for '$fd' (GNU stat):"
stat "$fd"

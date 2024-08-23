#!/bin/bash
echo "Enter a filename"
read file

fd="$file"
if [ ! -e "$fd" ];then
	echo "Error File does not exist"
	exit 1
fi 
inode_number=$(ls -i "$fd" | awk '{print $1}')
echo "The inode number of '$fd' is : $inode_number"

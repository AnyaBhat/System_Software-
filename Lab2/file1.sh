#!/bin/bash
#file1.sh: Uses command line arguments
#
echo “Program: $0 The number of arguments specified is $# The arguments are
$*”
grep “$1” $2
echo “\n Job Over”

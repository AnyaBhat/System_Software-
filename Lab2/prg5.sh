#!/bin/bash
echo "Enter a Number"
read n

fact=1
if [ "$n" -lt 0 ];then
	echo "Factorial is not defined for negative numbers"
	exit 1
fi
og_n=$n
while [ "$n" -gt 1 ];do 
	fact=$((fact * n))
	n=$((n - 1))
done
echo " Factorial of $og_n is $fact "

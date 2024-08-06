#!/bin/bash

# Display the current date and time
echo "Current Date and Time:"
date

# Display the number of users currently logged in
echo "Number of users currently logged in:"
who | wc -l

#!/bin/bash

clear 
declare -i e=10

# prints top rows 
printf "%3s" " "
for let in {a..j}
do
    printf "%3s " $let
done
printf "\n%4s" " "
for val in {1..40}
do
    printf "-"
done

# prints board
echo
for val1 in $(eval echo "{1..$e}")
do
    # prints row
    printf "%3d" $val1
    for val in $(eval echo "{1..$e}")
    do
        printf "| . "
    done
    printf "|\n%3s" " "
    # prints row divider 
    for val in {1..40}
    do
        printf "-"
    done
    printf "-"
    echo
done

# NEXT TASK:
# make board resizable 

# Notes:
# have 2 arrays, one to hold whether it is 
# a bomb/number, and one to hold its display state

#! /usr/bin/env bash

cd ./OS_PJ1_Test

for i in $(ls | grep "^SJF"); do
    name=$(echo "$i" | cut -d'.' -f1)
    echo "$name"
    dmesg --clear
    ../main.out < "$i" > "../output/${name}_stdout.txt"
    touch "../output/${name}_dmesg.txt"
    dmesg | grep Project1 > "../output/${name}_dmesg.txt"
done
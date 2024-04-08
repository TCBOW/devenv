#!/bin/bash
PWD=$(pwd)
FILE_NAME=${PWD}/tasklist.txt
while read LINE
do
    bash ${LINE}
done < ${FILE_NAME}

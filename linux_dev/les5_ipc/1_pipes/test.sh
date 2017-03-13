#/bin/bash

n=0
if [ -n "$1" ]
then
n=$1
fi

for i in $(seq $n)
do
echo 0r0100020300
echo test
echo 00 11 00
done

#!/bin/bash
for((j=10000;j<100000;j+=10000))
do
	echo "$j"
	echo -e "worst\n$j" | ./rnd
	for((i=0;i<3;i++))
	do
		./out
	done
	echo ""
done
for((j=100000;j<1000001;j+=100000))
do
	echo "$j"
	echo -e "worst\n$j" | ./rnd
	for((i=0;i<3;i++))
	do
		./out
	done
	echo ""
done

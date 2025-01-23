#!/bin/bash
g++ -o rnd rng.cpp
g++ -o out template.cpp
for((j=1000;j<10000;j+=1000))
do
	echo "$j"
	echo -e "random\n$j" | ./rnd
	for((i=0;i<3;i++))
	do
		./out
	done
	echo ""
done
for((j=10000;j<100001;j+=10000))
do
	echo "$j"
	echo -e "random\n$j" | ./rnd
	for((i=0;i<3;i++))
	do
		./out
	done
	echo ""
done

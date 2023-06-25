#!/bin/bash

for filename in "$@"; do

	if [ filename != bucket ]
	then
		echo $filename
		./$filename data1.dat
		./$filename data2.dat
		./$filename data3.dat
		./$filename data4.dat
		./$filename data5.dat
		./$filename data6.dat
		./$filename data7.dat
		./$filename data8.dat
		echo 
	else
		echo $filename
		./$1 data1.dat
	        ./$1 data2.dat
        	./$1 data3.dat
	        ./$1 data4.dat
	        ./$1 data5.dat
	        ./$1 data6.dat
        	./$1 data7.dat
		echo 
	fi
done



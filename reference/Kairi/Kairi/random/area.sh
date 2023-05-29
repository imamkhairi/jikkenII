#!/bin/bash

let myval=10000

echo "total pi gosa"
for i in {0..12};
    do 
        for j in {1..10};
        do
            bin/area $myval 
            sleep 0.90;
        done
        let myval+=40000
    done

for j in {1..10};
do
    bin/area 500000
    sleep 0.90;
done

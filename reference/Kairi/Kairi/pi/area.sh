#!/bin/bash

let myval=1000

echo "total area gosa"
for i in {0..4};
    do 
        for j in {1..10};
        do
            bin/area $myval 
            sleep 0.90;
        done
        let myval*=10
    done


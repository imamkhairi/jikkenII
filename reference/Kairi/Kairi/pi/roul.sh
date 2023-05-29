#!/bin/bash
echo "N win lose"
let myval=8192000
for i in {0..1};
    do 
        for j in {1..10};
        do
            bin/roullete $myval 
            sleep 0.90;
        done
        let myval+=myval
    done
  
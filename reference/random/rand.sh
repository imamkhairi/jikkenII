#!/bin/bash

let myval=10000

echo "success total percentage gosa"
for i in {0..13};
    do 
        for j in {1..10};
        do
            bin/rand $myval 
            sleep 0.90;
        done
        let myval+=myval
    done
  
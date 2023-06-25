#!/bin/bash

let myval=10

echo "total percentage true"
for i in {0..8};
    do 
        for j in {1..10};
        do
            bin/height $myval 
            sleep 0.90;
        done
        let myval*=10
    done
  
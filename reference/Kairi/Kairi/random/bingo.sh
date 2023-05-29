#!/bin/bash
echo "kaisuu min mid max"
let myval=10000
for i in {0..4};
    do 
        for j in {1..10};
        do
            bin/bingo $myval 
            sleep 0.90;
        done
        let myval*=10
    done
#!/bin/bash

    for N in {1000,2500,5000}
    do
        for k in {1..7}
        do
            Gram-Schmidt $N $N >> GS-"$N"-results.txt
            Gram-Schmidt-GE $N >> GS-GE-"$N"-results.txt
        done
        for i in {1..8}
        do
            export OMP_NUM_THREADS=$i
                for j in {1..7}
                do
                    Gram-Schmidt-OMP $N $N >> GS-OMP-"$N"-results.txt
                    Gram-Schmidt-OMP-GE $N >> GS-OMP-GE-"$N"-results.txt
                done
        done
    done           

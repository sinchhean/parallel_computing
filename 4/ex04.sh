#!/usr/bin/bash
#/usr/local/gnu/bin/bash
for b in {1..8}; do
    # Change the block size bSize as 2, 4, 8, 16, 32, 64, 128, 256
    bSize=$((2 ** b))
    echo "--------------------------------------------------------------------"
    echo "blocksize=$bSize "

    for((i=$b; i<=11; i++)) do
        # Change the matrix size n as 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048
        n=$((2 ** i))
        printf "$n "

        if [ -f "tmp" ]; then
            rm tmp
        fi
        # Repeat the measurement of computation time 5 times
         for j in {1..10}; do
             ./bmmtest -o ijk -d $n -b $bSize | tail -n +2 >> tmp
         done
        #./bmmtest -o ijk -d $n -b $bSize | tail -n +2 >> tmp &
        #./bmmtest -o ijk -d $n -b $bSize | tail -n +2 >> tmp &
        #./bmmtest -o ijk -d $n -b $bSize | tail -n +2 >> tmp &
        #./bmmtest -o ijk -d $n -b $bSize | tail -n +2 >> tmp &
        #./bmmtest -o ijk -d $n -b $bSize | tail -n +2 >> tmp

        # Calculate and display average elapsed time
        #cat tmp
        cat tmp | awk '{fsum += $3} {bfsum += $4} {dsum += $5} {bdsum += $6} END {print fsum/NR FS bfsum/NR FS dsum/NR FS bdsum/NR}'
    done
done

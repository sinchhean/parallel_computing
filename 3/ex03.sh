#/usr/bin/bash
#!/usr/local/gnu/bin/bash
echo "----------------------------------------"
echo "Size Float_etime Double_etime"
for i in {10..11}; do
    # Change the matrix size n as 8 16 32 64 128 256 512 1024 2048
    n=$((2 ** i))
    printf "$n "
    
    if [ -f "tmp" ]; then
        rm tmp
    fi
    # Repeat the measurement of computation time 5 times
    for j in {1..5}; do
        ./mxmtestO2 -o jki -d $n >> tmp
    done
    
    # Calculate and display average elapsed time
    cat tmp | awk '{sum1 += $2} {sum2 += $3} END {print sum1/NR FS sum2/NR}'
done
echo "----------------------------------------"


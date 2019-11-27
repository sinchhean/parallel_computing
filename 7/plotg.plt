set term pngcairo
set output "error.png"
set title "Error rate of mypi (-np 4)"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
plot "error.dat" using 1:2 title "Double Precision" with lines,\
    "error.dat" using 1:3 title "Single Precision" with lines
set term pngcairo
set output "error.png"
set title "Error rate of mypi (-np 4)"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
#set xrange [1:2048]
set logscale x 2
plot "error.dat" using 1:($2) title "Double Precision" with lines,\
    "error.dat" using 1:($3) title "Single Precision" with lines
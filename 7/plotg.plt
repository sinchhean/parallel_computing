set term pngcairo
set key left top
set output "error.png"
set title "Error rate of mypi (-np 4)"
set xlabel "Value of n"
set ylabel "Error rate"
set logscale x 10
set logscale y 15
plot "error.dat" using 1:2 title "Double Precision" with lp,\
    "error.dat" using 1:3 title "Single Precision" with lp

set term pngcairo
set output "double_loop_order_O2.png"
set title "Performance for matrix-multiplication as double precision and \nloop orders with -O2 optimization"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
#set xrange [1:2048]
set logscale x 2
plot "double_O2.dat" using 1:(2*$1*$1*$1/$2/1.0e6) title "ijk" with lines,\
    "double_O2.dat" using 1:(2*$1*$1*$1/$3/1.0e6) title "jki" with lines,\
    "double_O2.dat" using 1:(2*$1*$1*$1/$4/1.0e6) title "kij" with lines

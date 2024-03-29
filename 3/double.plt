set term pngcairo
set output "double2.png"
set title "Performance for matrix-multiplication as double precision"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
#set xrange [1:2048]
set logscale x 2
plot "ijk_double.dat" using 1:(2*$1*$1*$1/$2/1.0e6) title "-O0" with lines,\
    "ijk_double.dat" using 1:(2*$1*$1*$1/$3/1.0e6) title "-O2" with lines

set term pngcairo
set output "ex04_1.png"
set title "Performance for matrix-multiplication with the blocking algorithm as double precision"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
set style histogram clustered gap 4
set style fill solid border linecolor rgb "black"
set key outside
plot "ex04_1.dat" using (2*$1*$1*$1/$2/1.0e6):xtic(1) title "naive" with histogram,\
     "ex04_1.dat" using (2*$1*$1*$1/$3/1.0e6)         title "b = 2" with histogram

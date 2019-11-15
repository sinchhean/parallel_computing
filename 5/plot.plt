set term pngcairo
set output "ex05.png"
set title "MPI Elapse Time Comparison"
set xlabel "x value"
set ylabel "Elapse Time (s)"
set style histogram clustered gap 4
set logscale y 10
set style fill solid border linecolor rgb "black"
set key outside
plot "ex05.dat" using ($2):xtic(1) title "-np1" with histogram,\
     "ex05.dat" using ($3)         title "-np2" with histogram,\
     "ex05.dat" using ($4)         title "-np3" with histogram,\
     "ex05.dat" using ($5)         title "-np4" with histogram

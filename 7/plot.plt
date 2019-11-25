set term pngcairo
set output "double.png"
set title "MPI Elapse Time Comparison of Double Precision"
set xlabel "n value"
set ylabel "Elapse Time (s)"
set style histogram clustered gap 4
set logscale y 10
set style fill solid border linecolor rgb "black"
set key outside
plot "doubledata.dat" using ($2):xtic(1) title "-np1" with histogram,\
     "doubledata.dat" using ($3)         title "-np2" with histogram,\
     "doubledata.dat" using ($4)         title "-np3" with histogram,\
     "doubledata.dat" using ($5)         title "-np4" with histogram

set term pngcairo size 1024,768
set output "ex04_1_1.png"
set title "Performance for matrix-multiplication with\nthe blocking algorithm as float precision -O2 ijk"
set xlabel "Size of matrix"
set ylabel "Performance improvement ratio"
set yrange [0:]
set style histogram clustered gap 4
set style fill solid border linecolor rgb "black"
set key outside
plot "float2.dat" using ($2/$2):xtic(1) title "naive" with histogram,\
     "float2.dat" using ($3/$2)         title "b = 2" with histogram,\
     "float2.dat" using ($4/$2)         title "b = 4" with histogram,\
     "float2.dat" using ($5/$2)         title "b = 8" with histogram,\
     "float2.dat" using ($6/$2)         title "b = 16" with histogram,\
     "float2.dat" using ($7/$2)         title "b = 32" with histogram,\
     "float2.dat" using ($8/$2)         title "b = 64" with histogram,\
     "float2.dat" using ($9/$2)         title "b = 128" with histogram,\
     "float2.dat" using ($10/$2)         title "b = 256" with histogram

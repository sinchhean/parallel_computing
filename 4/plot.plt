set term pngcairo size 1024,768
set output "ex04_2.png"
set title "Performance for matrix-multiplication with the\nblocking algorithm as double precision -O2 ijk"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
set style histogram clustered gap 4
set style fill solid border linecolor rgb "black"
set key outside
plot "double.dat" using (2*$1*$1*$1/$2/1.0e6):xtic(1) title "naive" with histogram,\
     "double.dat" using (2*$1*$1*$1/$3/1.0e6)         title "b = 2" with histogram,\
     "double.dat" using (2*$1*$1*$1/$4/1.0e6)         title "b = 4" with histogram,\
     "double.dat" using (2*$1*$1*$1/$5/1.0e6)         title "b = 8" with histogram,\
     "double.dat" using (2*$1*$1*$1/$6/1.0e6)         title "b = 16" with histogram,\
     "double.dat" using (2*$1*$1*$1/$7/1.0e6)         title "b = 32" with histogram,\
     "double.dat" using (2*$1*$1*$1/$8/1.0e6)         title "b = 64" with histogram,\
     "double.dat" using (2*$1*$1*$1/$9/1.0e6)         title "b = 128" with histogram,\
     "double.dat" using (2*$1*$1*$1/$10/1.0e6)         title "b = 256" with histogram

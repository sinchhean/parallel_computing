set term pngcairo size 1024,768
set output "ex04_2.png"
set title "Performance for matrix-multiplication with the\nblocking algorithm as float precision -O2 ijk"
set xlabel "Size of matrix"
set ylabel "Performance/MFLOPS"
set logscale x 3
set logscale y 2
set key outside
plot "float.dat" using (2*$1*$1*$1/$2/1.0e6):xtic(1) title "naive" with lines,\
     "float.dat" using (2*$1*$1*$1/$3/1.0e6) title "b = 2" with lines,\
     "float.dat" using (2*$1*$1*$1/$4/1.0e6) title "b = 4" with lines,\
     "float.dat" using (2*$1*$1*$1/$5/1.0e6) title "b = 8" with lines,\
     "float.dat" using (2*$1*$1*$1/$6/1.0e6) title "b = 16" with lines,\
     "float.dat" using (2*$1*$1*$1/$7/1.0e6) title "b = 32" with lines,\
     "float.dat" using (2*$1*$1*$1/$8/1.0e6) title "b = 64" with lines,\
     "float.dat" using (2*$1*$1*$1/$9/1.0e6) title "b = 128" with lines,\
     "float.dat" using (2*$1*$1*$1/$10/1.0e6) title "b = 256" with lines

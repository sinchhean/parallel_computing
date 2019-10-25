set xlabel "value of n"
set ylabel "elapse time"
 

 
set key left

set term png enhanced size 1000,1000 font "Arial,20"
set logscale x
set logscale y
set output "p1-2-2.png"
 
 
plot "p1_O0.txt" using 1:2 title "-O0" w lp, \
     "p1_O1.txt" using 1:2 title "-O1" w lp, \
     "p1_O2.txt" using 1:2 title "-O2" w lp, \
     "p1_O3.txt" using 1:2 title "-O3" w lp

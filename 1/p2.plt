set xlabel "value of n"
set ylabel "elapse time"
 
 
set key left
#set term png size 640,480
set term png enhanced size 1000,1000 font "Arial,20"
set logscale x
set logscale y
set output "p2.png"
 
 
plot "p2.txt" using 1:2 title "Elapse Time" w lp

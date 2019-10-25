set xlabel "value of n"
set ylabel "elapse time"
 
#set xrange[0:300000] #x軸の範囲
 
set key left
#set term png size 640,480
set term png enhanced size 1000,1000 font "Arial,20"
set logscale x
set logscale y
 
set output "p1-1.png"
 
 
plot "p1_etime.txt" using 1:2 title "Elapse Time" w lp

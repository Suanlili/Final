set terminal png;
set output "graph4.png";
set xlabel "Iteration time";
set ylabel "Root";
set yrange [0:0.5];
set ytics 0,0.1,1.5;
plot "data7.dat" using 1:2 w lp pt 2 title "Bisection [0,1.5]","data7.dat" using 1:3 w lp pt 7 title "Newton, x_0=0";

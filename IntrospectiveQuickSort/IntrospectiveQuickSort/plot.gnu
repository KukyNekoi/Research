set encoding utf8
set terminal postscript color eps "Helvetica" 20
set output "ctimesummary.eps"
# set key below
set key at screen 0.9 ,screen 0.7 #for example
set logscale y 10
#set logscale x 10
set format y "10^{%L}"
#set format x "10^{%L}"
set xtics ("0" 1, "10e5" 100000, "2.5*10e5" 250000, "5*10e5" 500000, "7.5*10e5" 750000, "10e6" 999998)
set xlabel "amount of selected elements k"
set ylabel "CPU time [nanoseconds]"
set title "IQS accumulated CPU time m = 1e+6”
plot [1: 999998] [] \
     "< awk -F: '{if(int($1) % 30000 == 0){print $0}}' case6e.log" using 1:2 title "IQS RANDOM" with linespoints lt rgb "green" lw 1.3 pt 1 ps 1.5, \
     "< awk -F: '{if(int($1) % 30000 == 0){print $0}}' case6e.log" using 1:4 title "IQS INCREASING" with linespoints lt rgb "red" lw 1.3 pt 2 ps 1.5, \
     "< awk -F: '{if(int($1) % 30000 == 0){print $0}}' case6e.log" using 1:6 title "IQS DECREASING" with linespoints lt rgb "brown" lw 1.3 pt 3 ps 1.5, \
     "< awk -F: '{if(int($1) % 30000 == 0){print $0}}' case6e.log" using 1:3 title "IIQS RANDOM" with linespoints lt rgb "black" lw 1.3 pt 4 ps 1.5, \
     "< awk -F: '{if(int($1) % 30000 == 0){print $0}}' case6e.log" using 1:5 title "IIQS INCREASING" with linespoints lt rgb "purple" lw 1.3 pt 6 ps 1.5, \
     "< awk -F: '{if(int($1) % 30000 == 0){print $0}}' case6e.log" using 1:7 title "IIQS INCREASING" with linespoints lt rgb "blue" lw 1.3 pt 8 ps 1.5

#!/usr/bin/gnuplot
#
# Plots cubes like the example at http://pgfplots.sourceforge.net/h_example_82.pdf
#
# AUTHOR: Hagen Wierstorf
#
# Modified by: Fang Qiao (April, 2016)
#
# gnuplot 4.6 patchlevel 6

reset

set terminal qt size 700,524 enhanced font 'Verdana,10'

# color definitions
set cbrange [1:10]
set style fill transparent solid 0.3
set palette defined (\
1 '#ff4c4d',\
2 '#ce4c7d',\
3 '#ae559e',\
4 '#df866d',\
5 '#ffb66d',\
6 '#ffe7cf',\
7 '#cecece',\
8 '#6d6d6d',\
9 '#4c4c8e',\
10 '#4c4cef')
set style line  1 lc rgb '#ff2727' lt 1 lw 0.5
set style line  2 lc rgb '#b90046' lt 1 lw 0.5
set style line  3 lc rgb '#8b0b74' lt 1 lw 0.5
set style line  4 lc rgb '#d1512e' lt 1 lw 0.5
set style line  5 lc rgb '#ff972f' lt 1 lw 0.5
set style line  6 lc rgb '#ffddba' lt 1 lw 0.5
set style line  7 lc rgb '#b9b9b9' lt 1 lw 0.5
set style line  8 lc rgb '#2e2e2e' lt 1 lw 0.5
set style line  9 lc rgb '#00005d' lt 1 lw 0.5
set style line 10 lc rgb '#0000e8' lt 1 lw 0.5

unset key
#set border 0
unset border
unset tics
unset colorbox
#set view 58,29,1.5
set view equal xyz
#uset xyplane at 0
#set xlabel "x" offset 10,0,0
#set ylabel "y" offset 0,0,10
#set zlabel "z" offset 5,0,0

# load block function
load 'block.fct'

set pm3d depthorder hidden3d
set pm3d implicit
unset hidden3d

set lmargin 2
set rmargin 0
set bmargin 0
set tmargin 0
# get block positions from file
add_block(x,y,z,h,l,w,c) = sprintf('block(%f,%f,%f,%f,%f,%f,%i) w l ls %i,',x,y,z,h,l,w,c,c)
CMD = ''
stats 'coner.link.blocks.txt' u 1:(CMD = CMD.add_block($1,$2,$3,$4,$5,$6,$7)) nooutput
set xrange [0:4]
set yrange [0:4]
set zrange [0:3]
CMD = 'splot '.CMD.'1/0 w l ls 2'
# plot block
eval(CMD)

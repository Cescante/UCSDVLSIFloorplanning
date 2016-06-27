#!/usr/bin/gnuplot
#
# Plots graphs
#
# AUTHOR: Fang Qiao (June, 2016)
#
# gnuplot 4.6 patchlevel 6

reset

set terminal qt size 700,524 enhanced font 'Verdana,10'

# color definitions
# set cbrange [1:10]
# set style fill transparent solid 0.3
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

set style line 51 lc rgb 'black' lt 1 lw 2

set style arrow 1 head filled size screen 0.01,20,10 ls 51

# unset key
# unset tics
# unset colorbox
set view equal xy
set xyplane at 0

# load block function
# load 'block.fct'

# set pm3d depthorder hidden3d
# set pm3d implicit
# unset hidden3d
set style fill empty border
set border lw 0.5

set lmargin 2
set rmargin 2
set bmargin 2
set tmargin 2
# set xrange [0:25]
# set yrange [0:25]
plot \
  'graph.nodes.txt' u 1:2:(1):3 with circles lc pal notitle, \
  'graph.nodes.txt' using 1:2:4 with labels font "arial bold, 14" offset char 0,0 notitle, \
  'graph.edges.txt' u 1:2:3:4 with vectors arrowstyle 1 notitle \


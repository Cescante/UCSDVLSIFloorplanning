set cbrange [0.9:1]
set style fill transparent solid 0.5
set palette defined (1 '#ce4c7d')
set style line 1 lc rgb '#b90046' lt 1 lw 0.5

unset colorbox
set view 58,27,2
set view equal xyz

set pm3d depthorder hidden3d
set pm3d implicit
unset hidden3d
splot 'cube.txt' u 1:2:3:(1) w l ls 1

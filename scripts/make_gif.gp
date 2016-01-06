set term gif animate optimize
set out 'vicsek.gif'
set xrange[-10:110]
set yrange[-10:110]
set key off
set size ratio 1.0

do for [i=0:100:1]{
    plot 'vicsek.dat' index i using 2:3:4:5 with vector
}

set xrange[-10:110]
set yrange[-10:110]
set key off
set size ratio 1.0

do for [i=0:200:1]{
    plot 'vicsek.dat' index i*5 using 2:3:4:5 with vector
}

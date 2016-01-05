set xrange[-10:110]
set yrange[-10:110]
set key off

do for [i=0:100:1]{
    plot 'vicsek.dat' index i using 2:3:4:5 with vector
}

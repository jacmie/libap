set terminal windows font "Calibri,14"
#
set style line 1 lw 2 dt 1 lc "black"
set style line 2 lw 2 dt 1 lc "red"
set style line 3 lw 2 dt 3 lc "blue"
set style line 4 lw 2 dt 4 lc "dark-green"
set style line 10 lw 1 dt 3 lc "black"
set style line 11 lw 1 dt 1 lc "black"
set style line 20 lw 1 dt 1 lc "black"
set style line 21 lw 1 dt 3 lc "gray"
set style line 22 lw 1 dt 1 lc "gray80"
#set style fill pattern 5 noborder
# 
#unset key
set key at 3.85,-0.25
set key font ",13"
set key width -4.6
set key box ls 22
set size ratio 0.55
set key opaque
#
set samples 10000, 10000
set xrange [ 0 : 7 ] noreverse writeback
set yrange [ -1.0 : 1.0 ] noreverse writeback
set grid back ls 21
set border back ls 20
set xtics font ",16" textcolor "black"
set ytics font ",16" textcolor "black"
set xzeroaxis ls 11
#
#set title "{/:Bold Short Period}" font ",20" norotate
set xlabel "t [s]" font ",18"
set ylabel "pitch rate [deg/s]" font ",18" offset 1.2
set label 1 "{/:Bold control to force oscillation}" font ",16" at 1.4, 0.85, 0.0 left norotate front
set label 2 "{/:Bold short period}\n{/:Bold oscillation area}" font ",16" at 1.75, 0.35, 0.0 left norotate front
set label 3 "{/:Bold short period}\n{/:Bold oscillation area}" font ",16" at 5.65, 0.35, 0.0 left norotate front
set arrow 1 from 1.32, 0.85, 0.0 to 0.8425, 0.85, 0.0 head ls 1 filled size 0.12,20 front
set arrow 2 from 3.45, 0.85, 0.0 to 3.95, 0.85, 0.0 head ls 1 filled size 0.12,20 front
set arrow 3 from 1.58, 0.35, 0.0 to 1.25, 0.11, 0.0 head ls 1 filled size 0.16,11 front
set arrow 4 from 1.58, 0.35, 0.0 to 1.65, 0.35, 0.0 nohead ls 1 front
set arrow 5 from 5.48, 0.35, 0.0 to 5.15, 0.11, 0.0 head ls 1 filled size 0.16,11 front
set arrow 6 from 5.48, 0.35, 0.0 to 5.55, 0.35, 0.0 nohead ls 1 front
#
plot \
'Fill_1.txt' using 1:2 notitle with filledcurves y1=-1.0 ls 22 fillstyle pattern 7, \
'Fill_2.txt' using 1:2 notitle with filledcurves y1=-1.0 ls 22 fillstyle pattern 7, \
'NORD_Short_Period_3.txt' using 1:3 ls 1 title "Flight Data" with lines, \
'NORD_Short_Period_3_short.txt' using 1:4 ls 2 title "Approx. Model" with lines, \
'NORD_Short_Period_3_short.txt' using 2:4 ls 2 notitle with lines, \
'NORD_Short_Period_3_short.txt' using 1:5 ls 3 title "Design" with lines, \
'NORD_Short_Period_3_short.txt' using 2:5 ls 3 notitle with lines, \
'NORD_Short_Period_3_short.txt' using 1:6 ls 4 title "Design With Mass Correction" with lines, \
'NORD_Short_Period_3_short.txt' using 2:6 ls 4 notitle with lines, \
'NORD_Short_Period_3_short.txt' using 1:7 ls 10 notitle with lines, \
'NORD_Short_Period_3_short.txt' using 1:8 ls 10 notitle with lines, \
'NORD_Short_Period_3_short.txt' using 2:7 ls 10 notitle with lines, \
'NORD_Short_Period_3_short.txt' using 2:8 ls 10 notitle with lines, \

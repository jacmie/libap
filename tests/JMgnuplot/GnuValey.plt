set style dat linespoints
set pm3d implicit at s
set isosamples 50, 50
#  set pm3d scansbackward  
#  set hidden3d back offset 1 trianglepattern 3 undefined 1 altdiagonal bentover
#  set pm3d interpolate 1,1 flush begin noftriangles hidden3d 100 corners2color mean
splot 'GnuValey.dat'


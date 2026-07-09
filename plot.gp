# Configuración de salida
set terminal pngcairo size 1000,800 enhanced font 'Verdana,10'
set datafile separator ";"

#Estilos de lineas
set style line 1 lc rgb '#E66101' lt 1 lw 2 pt 7 ps 1  # Control
set style line 2 lc rgb '#B2ABD2' lt 1 lw 2 pt 5 ps 1  # STD
set style line 3 lc rgb '#5E3C99' lt 1 lw 2 pt 9 ps 1  # Chaining
set style line 4 lc rgb '#2CA02C' lt 1 lw 2 pt 11 ps 1 # Linear Probing
set style line 5 lc rgb '#D62728' lt 1 lw 2 pt 13 ps 1 # QuadraticProbing


set output 'results/timehash.png'
set title "Tiempo de ejecución promedio vs cantidad de tweets (user\\_id)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Tiempo de ejecución promedio (us)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set autoscale yfix
set key left top box title "Estructuras de datos"
plot \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "Control" ? $3 : NaN) smooth unique title "Control" w lp ls 1, \
  'results/timesll.csv' using 1:(stringcolumn(2)eq "STD" ? $3 : NaN) smooth unique title "STD" w lp ls 2, \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) smooth unique title "Chaining" w lp ls 3, \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) smooth unique title "Linear Probing" w lp ls 4, \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) smooth unique title "Quadratic Probing" w lp ls 5



set output 'results/timehash2.png'
set title "Tiempo de ejecución promedio vs cantidad de tweets (user\\_screen\\_name)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Tiempo de ejecución promedio (us)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set autoscale yfix
set key left top box title "Estructuras de datos"
plot \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "Control" ? $3 : NaN) smooth unique title "Control" w lp ls 1, \
  'results/timesstr.csv' using 1:(stringcolumn(2)eq "STD" ? $3 : NaN) smooth unique title "STD" w lp ls 2, \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) smooth unique title "Chaining" w lp ls 3, \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) smooth unique title "Linear Probing" w lp ls 4, \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) smooth unique title "Quadratic Probing" w lp ls 5




set output 'results/spacehash.png'
set title "Memoria utilizada promedio vs cantidad de tweets (user\\_id)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Memoria utilizada promedio (B)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set autoscale yfix
set key left top box title "Estructuras de datos"
plot \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "Control" ? $4 : NaN) smooth unique title "Control" w lp ls 1, \
  'results/timesll.csv' using 1:(stringcolumn(2)eq "STD" ? $4 : NaN) smooth unique title "STD" w lp ls 2, \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "Chaining" ? $4 : NaN) smooth unique title "Chaining" w lp ls 3, \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $4 : NaN) smooth unique title "Linear Probing" w lp ls 4, \
  'results/timesll.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $4 : NaN) smooth unique title "Quadratic Probing" w lp ls 5


set output 'results/spacehash2.png'
set title "Memoria utilizada promedio vs cantidad de tweets (user\\_screen\\_name)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Memoria utilizada promedio (B)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set autoscale yfix
set key left top box title "Estructuras de datos"
plot \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "Control" ? $4 : NaN) smooth unique title "Control" w lp ls 1, \
  'results/timesstr.csv' using 1:(stringcolumn(2)eq "STD" ? $4 : NaN) smooth unique title "STD" w lp ls 2, \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "Chaining" ? $4 : NaN) smooth unique title "Chaining" w lp ls 3, \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $4 : NaN) smooth unique title "Linear Probing" w lp ls 4, \
  'results/timesstr.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $4 : NaN) smooth unique title "Quadratic Probing" w lp ls 5


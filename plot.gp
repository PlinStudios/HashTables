set terminal pngcairo size 1000,800 enhanced font 'Verdana,10'
set datafile separator ";"
set datafile missing "NaN"

# Estilos de líneas comunes
set style line 1 lc rgb '#E66101' lt 1 lw 2 pt 7 ps 1 
set style line 2 lc rgb '#B2ABD2' lt 1 lw 2 pt 5 ps 1 
set style line 3 lc rgb '#5E3C99' lt 1 lw 2 pt 9 ps 1 
set style line 4 lc rgb '#2CA02C' lt 1 lw 2 pt 11 ps 1
set style line 5 lc rgb '#D62728' lt 1 lw 2 pt 13 ps 1
set style line 6 lc rgb '#5327d6' lt 1 lw 2 pt 3 ps 1

#  tiempo por id
set output 'results/timehash.png'
set title "Tiempo de ejecución vs cantidad de tweets (user\\_id)" font "Arial,14,Bold"
set ylabel "Tiempo neto (us)" font "Arial,11,Bold"
plot \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN) title "STD" w lp ls 2, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) title "Chaining" w lp ls 3, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) title "Linear Probing" w lp ls 4, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) title "Quadratic Probing" w lp ls 5, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN) title "Double Hashing" w lp ls 6

# memoria por id
set output 'results/spacehash.png'
set title "Memoria utilizada vs cantidad de tweets (user\\_id)" font "Arial,14,Bold"
set ylabel "Memoria neta (B)" font "Arial,11,Bold"
plot \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "STD" ? $4 : NaN) title "STD" w lp ls 2, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "Chaining" ? $4 : NaN) title "Chaining" w lp ls 3, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $4 : NaN) title "Linear Probing" w lp ls 4, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $4 : NaN) title "Quadratic Probing" w lp ls 5, \
  'results/timesll_neto.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $4 : NaN) title "Double Hashing" w lp ls 6

  # tiempo por name
set output 'results/timehash2.png'
set title "Tiempo de ejecución vs cantidad de tweets (user\\_screen\\_name)" font "Arial,14,Bold"
set ylabel "Tiempo (us)" font "Arial,11,Bold"
plot \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN) title "STD" w lp ls 2, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) title "Chaining" w lp ls 3, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) title "Linear Probing" w lp ls 4, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) title "Quadratic Probing" w lp ls 5, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN) title "Double Hashing" w lp ls 6

# memoria por name
set output 'results/spacehash2.png'
set title "Memoria utilizada vs cantidad de tweets (user\\_screen\\_name)" font "Arial,14,Bold"
set ylabel "Memoria (B)" font "Arial,11,Bold"
plot \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "STD" ? $4 : NaN) title "STD" w lp ls 2, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "Chaining" ? $4 : NaN) title "Chaining" w lp ls 3, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $4 : NaN) title "Linear Probing" w lp ls 4, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $4 : NaN) title "Quadratic Probing" w lp ls 5, \
  'results/timesstr_neto.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $4 : NaN) title "Double Hashing" w lp ls 6
#codigo parcialmente hecho con gemini
# Configuración de salida
set terminal pngcairo size 1000,800 enhanced font 'Verdana,10'
set datafile separator ";"


# Estilos de líneas
set style line 1 lc rgb '#E66101' lt 1 lw 2 pt 7 ps 1 
set style line 2 lc rgb '#B2ABD2' lt 1 lw 2 pt 5 ps 1 
set style line 3 lc rgb '#5E3C99' lt 1 lw 2 pt 9 ps 1 
set style line 4 lc rgb '#2CA02C' lt 1 lw 2 pt 11 ps 1
set style line 5 lc rgb '#D62728' lt 1 lw 2 pt 13 ps 1
set style line 6 lc rgb '#4169E1' lt 1 lw 2 pt 15 ps 1

set output 'results/timehash_des.png'
set title "Tiempo de ejecución promedio y Desviación Estándar (user\\_id)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Tiempo de ejecución (us)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set key left top box title "Estructuras de datos"

# Graficar usando directamente las columnas procesadas de C++
# Columna 1: X (n_tweet)
# Columna 3: Y (promedio)
# Columna 4: Delta (desviación estándar)
plot \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN) title "STD" w linespoints ls 2, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN):4 notitle w errorbars ls 2, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) title "Chaining" w linespoints ls 3, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN):4 notitle w errorbars ls 3, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) title "Linear Probing" w linespoints ls 4, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN):4 notitle w errorbars ls 4, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) title "Quadratic Probing" w linespoints ls 5, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN):4 notitle w errorbars ls 5, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN) title "Double Hashing" w linespoints ls 6, \
  'results/tiempos_estadisticos.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN):4 notitle w errorbars ls 6


set output 'results/spacehash_des.png'
set title "Memoria utilizada promedio y Desviación Estándar (user\\_id)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Memoria utilizada (B)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set key left top box title "Estructuras de datos"

# Graficar usando directamente las columnas procesadas de C++
# Columna 1: X (n_tweet)
# Columna 3: Y (promedio)
# Columna 4: Delta (desviación estándar)
plot \
 'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN) title "STD" w linespoints ls 2, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN):4 notitle w errorbars ls 2, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) title "Chaining" w linespoints ls 3, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN):4 notitle w errorbars ls 3, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) title "Linear Probing" w linespoints ls 4, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN):4 notitle w errorbars ls 4, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) title "Quadratic Probing" w linespoints ls 5, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN):4 notitle w errorbars ls 5, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN) title "Double Hashing" w linespoints ls 6, \
  'results/memoria_estadistica.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN):4 notitle w errorbars ls 6




set output 'results/timehash_des2.png'
set title "Tiempo de ejecución promedio y Desviación Estándar (user\\_screen\\_name)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Tiempo de ejecución (us)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set key left top box title "Estructuras de datos"

# Graficar usando directamente las columnas procesadas de C++
# Columna 1: X (n_tweet)
# Columna 3: Y (promedio)
# Columna 4: Delta (desviación estándar)
plot \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN) title "STD" w linespoints ls 2, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN):4 notitle w errorbars ls 2, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) title "Chaining" w linespoints ls 3, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN):4 notitle w errorbars ls 3, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) title "Linear Probing" w linespoints ls 4, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN):4 notitle w errorbars ls 4, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) title "Quadratic Probing" w linespoints ls 5, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN):4 notitle w errorbars ls 5, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN) title "Double Hashing" w linespoints ls 6, \
  'results/tiempos_estadisticos2.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN):4 notitle w errorbars ls 6


set output 'results/spacehash_des2.png'
set title "Memoria utilizada promedio y Desviación Estándar (user\\_screen\\_name)" font "Arial,14,Bold"
set grid xtics ytics ls 12 lc rgb '#dddddd' lt 1
set xlabel "Cantidad de tweets (n\\_tweet)" font "Arial,11,Bold"
set ylabel "Memoria utilizada (B)" font "Arial,11,Bold"
set format x "%.0f"
set format y "%.0f"
set key left top box title "Estructuras de datos"

# Graficar usando directamente las columnas procesadas de C++
# Columna 1: X (n_tweet)
# Columna 3: Y (promedio)
# Columna 4: Delta (desviación estándar)
plot \
 'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN) title "STD" w linespoints ls 2, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "STD" ? $3 : NaN):4 notitle w errorbars ls 2, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN) title "Chaining" w linespoints ls 3, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "Chaining" ? $3 : NaN):4 notitle w errorbars ls 3, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN) title "Linear Probing" w linespoints ls 4, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "LinearProbing" ? $3 : NaN):4 notitle w errorbars ls 4, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN) title "Quadratic Probing" w linespoints ls 5, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "QuadraticProbing" ? $3 : NaN):4 notitle w errorbars ls 5, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN) title "Double Hashing" w linespoints ls 6, \
  'results/memoria_estadistica2.csv' using 1:(stringcolumn(2) eq "DoubleHashing" ? $3 : NaN):4 notitle w errorbars ls 6



 
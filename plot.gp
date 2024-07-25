set terminal png size 800,600
set output 'output.png'
set title "Resultados do Algoritmo"
set xlabel "Algoritmo"
set ylabel "Valores (log scale)"
set logscale y

# Definir estilos de linha com cores fortes e espessura maior
set style line 1 lc rgb '#ff0000' lw 3 lt 1  # Merge Sort
set style line 2 lc rgb '#00ff00' lw 3 lt 1  # Quick Sort
set style line 3 lc rgb '#0000ff' lw 3 lt 1  # Heap Sort
set style line 4 lc rgb '#ffa500' lw 3 lt 1  # Merge Sort sem recursão
set style line 5 lc rgb '#800080' lw 3 lt 1  # Quick Sort sem recursão
set style line 6 lc rgb '#00ffff' lw 3 lt 1  # Heap Sort sem recursão

# Ajustar o estilo dos gráficos para linhas preenchidas
set style data lines

plot 'resultados_gnuplot.txt' using 0:2 title 'Merge Sort' with lines linestyle 1, \
     '' using 0:3 title 'Quick Sort' with lines linestyle 2, \
     '' using 0:4 title 'Heap Sort' with lines linestyle 3, \
     '' using 0:5 title 'Merge Sort SR' with lines linestyle 4, \
     '' using 0:6 title 'Quick Sort SR' with lines linestyle 5, \
     '' using 0:7 title 'Heap Sort SR' with lines linestyle 6


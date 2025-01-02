#!/bin/bash

# Número de nodos que deseas ejecutar (por defecto 3 nodos si no se pasa como argumento)
NUM_NODOS=${1:-3}

# Ruta del script del coordinador y de los nodos
COORDINADOR_SCRIPT="./coordinador.js"  # Ajusta la ruta según tu estructura de archivos
NODO_SCRIPT="./nodo.js"                # Ajusta la ruta según tu estructura de archivos

# Función para ejecutar el coordinador
ejecutar_coordinador() {
  echo "Iniciando Coordinador..."
  node "$COORDINADOR_SCRIPT" &
  COORDINADOR_PID=$!
}

# Función para ejecutar los nodos
ejecutar_nodos() {
  for ((i = 0; i < NUM_NODOS; i++)); do
    echo "Iniciando Nodo $i..."
    node "$NODO_SCRIPT" $i &
    NODO_PIDS[$i]=$!
  done
}

# Función para esperar a que todos los procesos terminen
esperar_procesos() {
  wait $COORDINADOR_PID
  for pid in "${NODO_PIDS[@]}"; do
    wait $pid
  done
}

# Iniciar el coordinador y los nodos
ejecutar_coordinador
ejecutar_nodos

# Esperar a que todos los procesos terminen
esperar_procesos

echo "Todos los procesos han terminado."

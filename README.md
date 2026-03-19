# CPU Scheduling Simulator
## Valentina Feijoo, Juan Carlos Díaz, Nicolas Zapata y Santiago Guevara

## Descripción

Este programa simula algoritmos de planificación de CPU.

Actualmente implementa:
- Round Robin (RR)
- Shortest Job First (SJF)
- First Come Fist Served (FCFS)
- Preemptive Shortest Job First (PSJF)

El programa lee procesos desde un archivo `.txt`, ejecuta el algoritmo seleccionado y muestra:
- Diagrama de ejecución
- Tabla con métricas (AT, BT, CT, TAT, WT, RT)
- Promedios

---

## Estructura del Proyecto

```
.
├── main.cpp
├── inputs/
│   ├── input1.txt
│   ├── input2.txt
    ├── input3.txt
└── src/
├── process.h
├── utils.h
├── utils.cpp
├── roundrobin.h
├── roundrobin.cpp
├── fcfs.h
├── fcfs.cpp
├── sjf.h
├── sjf.cpp
├── psjf.h
└── psjf.cpp
```

---

## Formato de Entrada

Cada línea del archivo `.txt` debe tener:

```
ID; BT; AT; Q; PRIORITY
```

Ejemplo:

```
P0; 3; 0; 1; 1
P1; 4; 0; 1; 1
P2; 2; 0; 1; 1
```

---

## Compilación

Ubicado en la carpeta del proyecto:

```
g++ main.cpp src/*.cpp -o scheduler
```

---

## Ejecución

### Round Robin

```
./scheduler -rr archivo.txt quantum
```

Ejemplo:

```
./scheduler -rr inputs/input1.txt 2
```

---

### SJF

```
./scheduler -sjf archivo.txt
```

Ejemplo:

```
./scheduler -sjf inputs/input1.txt
```

---
### PSJF

```
./scheduler -psjf archivo.txt
```

Ejemplo:

```
./scheduler -psjf inputs/input1.txt
```

---

### FCFS

```
./scheduler -fcfs archivo.txt
```

Ejemplo:

```
./scheduler -fcfs inputs/input1.txt
```

---

## Funcionamiento

1. El programa lee el archivo con los procesos
2. Según el parámetro (`-rr`, `-sjf`, `-psjf` o `-fcfs`), ejecuta el algoritmo
3. Calcula:
   - CT (Completion Time)
   - TAT (Turnaround Time)
   - WT (Waiting Time)
   - RT (Response Time)
4. Imprime:
   - Diagrama de ejecución
   - Tabla de resultados
   - Promedios

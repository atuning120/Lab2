# Lab2
**Conecta 4**

Este taller fue realizado en visual studio code.
para compilar use el siguiente comando por consola: g++ -o main main.cpp

para ejecutar el archivo compilado use el siguiente comando por consola: ./main.exe

El tablero es 6x7 constituido por vector<vector<int>> donde los espacios vacíos del tablero se representan con un 0, las fichas del jugador con un -1 y las fichas de la maquina con un 1.
al principio de despliega un menú donde el usuario puede elegir las siguientes opciones:
1. nueva partida (se da a elegir el tipo de pensamiento de la CPU, con poda o sin poda y también se da a elegir la dificultad, fácil, medio y difícil)
2. continuar partida guardada (solo se puede continuar la última partida que se dejó a medias [sin ganador ni empate])
3. ver puntuación (se muestra la cantidad de partidas jugadas y las estadísticas de partidas ganadas por el jugador, maquina o empate. Todo esto por cada dificultad)
4. salir

Respecto al análisis de la máquina, se ocupó un algoritmo de minimax, donde hay 2 tipos, una que implementa la poda alfa-beta y otra que no aplica la poda alfa-beta, la/s diferencias de estos modos son:
1. sin poda alfa-beta, la maquina debe analizar todas las ramas del árbol de casos, dependiendo de la profundidad dada por la dificultad, este tipo de lógica tiene una complejidad algorítmica de
   O(7^profundidad). para la modalidad fácil tiene una complejidad de O(7^2), medio de O(7^4) y difícil de O(7^6).

2. Con poda alfa-beta, el análisis de la maquina se optimiza y se ocupa menos espacio en memoria, la complejidad algorítmica de este es O(b^(d/2)) donde b es la cantidad de hijos que puede tener el árbol, este
   va variando, dependiendo del estado de la columna y d representa la profundidad del árbol. la característica principal de este algoritmo es que los cosas donde la maquina gana estas cortan el proceso de análisis de
   las ramas que seguían y tienen un mayor puntaje, lo que ayuda a la maquina a elegir la mejor opción de manera más optima.

Cada elemento del árbol es representado por una clase llamada Nodo que tiene como atributos el puntaje y la columna, con geters y seters para estos atributos.


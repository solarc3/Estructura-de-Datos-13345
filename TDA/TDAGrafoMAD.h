#include "TDAcola.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void inicializar_random() { srand(time(NULL)); }

// Estructura para matriz de ad
// Grafo dirigido y ponderado
// operaciones elementales inicio
struct grafo {
  int **Mad;
  int n; // cantidad de nodos/vertices
  int m; // cantidad de aristas (inicial es 0)
};
typedef struct grafo Grafo;

struct arista {
  int v, w;
  int peso;
};
typedef struct arista Arista;

Arista *crear_arista(int nodo1, int nodo2, int peso) {
  Arista *Salida;
  Salida = (Arista *)malloc(sizeof(Arista)); // reserva de memoria
  Salida->v = nodo1;
  Salida->w = nodo2;
  Salida->peso = peso;

  return Salida;
}

void print_Arista(Arista *arista) {
  printf("Vértice v: %d\n", arista->v);
  printf("Vértice w: %d\n", arista->w);
  printf("Peso: %d\n", arista->peso);
}
void MostrarArista(Arista *Conexion) {
  printf("%d - %d -> %d\n", Conexion->v, Conexion->peso, Conexion->w);
}

Grafo *crear_grafo(int n) {
  Grafo *Grafonuevo = (Grafo *)malloc(sizeof(Grafo)); // creacion memoria grafo
  Grafonuevo->Mad =
      (int **)malloc(sizeof(int *) * n); // creacion memoria matriz
  for (int i = 0; i < n; i++) {
    Grafonuevo->Mad[i] = (int *)malloc(sizeof(int) * n);
    for (int j = 0; j < n; j++) {
      Grafonuevo->Mad[i][j] = 0; // rellenamos con 0
    }
  }
  Grafonuevo->n = n;
  Grafonuevo->m = 0; // 0 ya que no hay vertices agregados
  return Grafonuevo;
}
void mostrar_grafo(Grafo *Gma) {
  printf("    ");

  for (int j = 0; j < Gma->n; j++) {
    printf("%d   ", j);
  }
  printf("\n");

  for (int j = 0; j < Gma->n; j++) {
    printf("----");
  }
  printf("\n");

  for (int i = 0; i < Gma->n; i++) {

    printf("%d | ", i);

    for (int j = 0; j < Gma->n; j++) {
      printf("%d   ", Gma->Mad[i][j]);
    }
    printf("\n");
  }
}

void insertar_arista(Grafo *Grafo, Arista *Conexion, bool es_dirigido) {
  // in range
  if (Conexion->v >= Grafo->n) {
    printf("Primer nodo de la conexion no existe.\n");
    return;
  } else if (Conexion->w >= Grafo->n) {
    printf("Segundo nodo de la conexion no existe.\n");
    return;
  }

  // Insertar la arista  v -> w
  Grafo->Mad[Conexion->v][Conexion->w] = Conexion->peso;

  // Si no es dirigido, insertamos en opuesta tbm w -> v
  if (!es_dirigido) {
    Grafo->Mad[Conexion->w][Conexion->v] = Conexion->peso;
  }
}

void eliminar_arista(Grafo *Grafo, Arista *conexion, bool es_dirigido) {
  // Verificacion
  if (conexion->v >= Grafo->n) {
    printf("Primer nodo de la conexion no existe.\n");
    return;
  } else if (conexion->w >= Grafo->n) {
    printf("Segundo nodo de la conexion no existe.\n");
    return;
  }

  // Eliminar la arista v -> w
  Grafo->Mad[conexion->v][conexion->w] = 0;

  // Si no es dirigido, tambien sacar la otra direccion
  if (!es_dirigido) {
    Grafo->Mad[conexion->w][conexion->v] = 0;
  }
}
void agregar_nodo(Grafo *g) {
  // size +1
  int n = g->n + 1;

  // memoria nueva matriz
  int **newMad = (int **)malloc(sizeof(int *) * n);
  for (int i = 0; i < n; i++) {
    newMad[i] = (int *)malloc(sizeof(int) * n);
  }

  // copiamos y rellenamos con 0 las posiciones nuevas
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == g->n || j == g->n) {
        newMad[i][j] = 0;
      } else {
        newMad[i][j] = g->Mad[i][j];
      }
    }
  }

  // actualizamos
  g->n = n;
  // free matrix
  for (int i = 0; i < g->n - 1; i++) {
    free(g->Mad[i]);
  }
  free(g->Mad);
  g->Mad = newMad; // update to new matrix
}

void eliminar_nodo(Grafo *g) {
  // update size
  int n = g->n - 1;
  // memory new matrix
  int **newMad = (int **)malloc(sizeof(int *) * n);
  for (int i = 0; i < n; i++) {
    newMad[i] = (int *)malloc(sizeof(int) * n);
  }
  // con la nueva matriz agregamos los valores de la matriz anterior
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newMad[i][j] = g->Mad[i][j];
    }
  }
  // actualizamos
  g->n = n;
  // free old matrix
  for (int i = 0; i < g->n + 1; i++) {
    free(g->Mad[i]);
  }
}

bool existe_vertice(Grafo *g, int v) {
  if (v < g->n)
    return true;
  else
    return false;
}

int grado_nodo(Grafo *g, int v) {
  int cuenta = 0;
  if (existe_vertice(g, v)) { // existe vertice?, no es necesario verificar
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[v][j] != 0)
        cuenta = cuenta + 1;
    }
  }
  return cuenta;
}

Arista **obtenerAristas(Grafo *g) {
  int i, j, r, amount;
  Arista **aristas;
  // contar la cantidad de aristas de la matriz
  amount = 0;
  for (i = 0; i < g->n; i++) {
    for (j = 0; j < g->n; j++) {
      if (g->Mad[i][j] != 0) {
        amount++;
      }
    }
  }
  // Arreglo de aristas
  aristas = (Arista **)malloc(sizeof(Arista *) * amount);
  r = 0;
  for (i = 0; i < g->n; i++) {
    for (j = 0; j < g->n; j++) {
      if (g->Mad[i][j] != 0) {
        aristas[r] = crear_arista(i, j, g->Mad[i][j]);
        r++;
      }
    }
  }
  return aristas;
}
void mostrar_adyacentes(Grafo *g, int v) {
  // Asumimos que antes de llamar a esta operación se ha validado que el nodo v
  // existe
  printf("Nodos adyacentes al nodo %d:", v);
  for (int j = 0; j < g->n; j++) {
    if (g->Mad[v][j] != 0) { // Si el peso es diferente de 0, hay adyacencia
      printf(" %d", j);
    }
  }
  printf("\n");
}
void imprimirNumeroDeArcos(Grafo *g, bool es_dirigido) {
  int contador_de_arcos = 0;
  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[i][j] != 0) {
        contador_de_arcos++;
      }
    }
  }
  // Si no es dirigido, cada arista se cuenta dos veces
  if (!es_dirigido) {
    contador_de_arcos /= 2;
  }
  printf("El numero de arcos en el grafo es: %d\n", contador_de_arcos);
}

// funcion que retorne los nodos adyecentes a un nodo dado
// misma funcion del TDA Grafo que se utiliza en catedra
int *nodosAdyecentes(Grafo g, int v) {
  int *nodos;
  int i, j, r, amount;
  // contar la cantidad de nodos adyecentes
  amount = 0;
  for (i = 0; i < g.n; i++) {
    if (g.Mad[v][i] != 0) {
      amount++;
    }
  }
  // Arreglo de nodos
  nodos = (int *)malloc(sizeof(int) * amount);
  r = 0;
  for (i = 0; i < g.n; i++) {
    if (g.Mad[v][i] != 0) {
      nodos[r] = i;
      r++; // agregamos un tercer contador ya que no necesariamente se agregan
           // todos, solo se agregan los vali Hudos
    }
  }
  return nodos;
}

void mostrarAdyacentesDeTodosLosNodos(Grafo *g) {
  for (int i = 0; i < g->n; i++) {
    printf("Nodos adyacentes al nodo %d: ", i);
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[i][j] != 0) { // si es que hay conexion
        printf("%d ", j);
      }
    }
    printf("\n");
  }
}

// retoranada verdadero si el grafo es completo
bool es_completo(Grafo *g) {
  int i, j;
  for (i = 0; i < g->n; i++) {
    for (j = i + 1; j < g->n; j++) {
      if (g->Mad[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

void DFSUtil(Grafo *g, int v, bool visitado[]) {
  // Marcar el nodo actual como visitado y mostrarlo
  visitado[v] = true;
  printf("%d ", v);
  // Recorrer vertices adyecentes al nodo actual
  for (int i = 0; i < g->n; i++) {
    if (g->Mad[v][i] && !visitado[i]) {
      DFSUtil(g, i, visitado);
    }
  }
}

void DFS(Grafo *g, int v) {
  // arreglo de booleanos de visitados, tamaño total
  bool *visitado = (bool *)malloc(g->n * sizeof(bool));
  for (int i = 0; i < g->n; i++) {
    visitado[i] = false;
  } // hacer esto en vez de hacer calloc

  // display dfs to run, recursion!!!!
  DFSUtil(g, v, visitado);

  // Liberar memoria
  free(visitado);
}
Grafo *generar_grafo_random(int n, bool es_dirigido) {
  Grafo *g = crear_grafo(n);

  for (int i = 0; i < n; i++) {
    // hack del año, operador terninario, para ver si es dirigido o no, asi
    // parte de 0 o de i
    for (int j = (es_dirigido ? 0 : i); j < n; j++) {
      if (i != j) {                       // si no esta en la diagonal
        int conexion_random = rand() % 2; // Genera 0 o 1 aleatoriamente.
        g->Mad[i][j] = conexion_random;
        if (!es_dirigido) {
          // Si el grafo no es dirigido, la conexión es simétrica.
          g->Mad[j][i] = conexion_random;
        }
      } else {
        g->Mad[i][j] = 0; // No hay bucles en el grafo, ponemos 0.
      }
    }
  }

  return g;
}
void ponderar_grafo(Grafo *g) {
  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[i][j] == 1) {           // Si existe una arista
        g->Mad[i][j] = (rand() % 8) + 1; // Peso aleatorio entre 1 y 10
      }
    }
  }
}

// labs del semestre pasado

void nodo_sumidero(Grafo *g) {
  for (int i = 0; i < g->n; i++) {
    int entrantes = 0;
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[j][i] != 0) { // Si hay un nodo de j a i
        entrantes++;
        break; // si encuentra algo, implica que no es sumidero
      }
    }

    // si no tiene aristas, es sumidero
    if (entrantes == 0) {
      printf("El vertice %d es un vertice sumidero.\n", i);
    }
  }
}

void nodo_fuente(Grafo *g) {
  for (int i = 0; i < g->n; i++) {
    int salientes = 0;
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[i][j] != 0) { // Si hay un nodo de i a j
        salientes++;
        break; // si encuentra algo, implica que no es fuente
      }
    }

    // si no tiene aristas, es fuente
    if (salientes == 0) {
      printf("El vertice %d es un vertice fuente.\n", i);
    }
  }
}

bool esConexo(Grafo *g) {
  int inicio = 0; // inicio que sea el origen
  bool *visitado = (bool *)calloc(g->n, sizeof(bool)); // calloc para 0 en todo

  // Realiza DFS desde el nodo de inicio
  DFSUtil(g, inicio, visitado);

  // Verifica si todos los nodos fueron visitados
  for (int i = 0; i < g->n; i++) {
    if (!visitado[i]) { // Si algun nodo no fue visitado, el grafo no es conexo
      free(visitado);
      return false;
    }
  }
  free(visitado);
  return true;
}
// problemas de la guia de ejercicios

// este revisa si todos tienen el mismo grado
bool esRegular(Grafo *g) {
  if (g->n == 0) {
    // Un grafo sin nodos no es regular.
    return false;
  }

  // primer nodo como base
  int grado = grado_nodo(g, 0);

  // verificar mismo grado
  for (int i = 1; i < g->n; i++) {
    if (grado_nodo(g, i) != grado) {
      // si alguno es diferente, no es regular
      return false;
    }
  }
  // Si todos los nodos tienen el mismo grado, el grafo es regular.
  return true;
}

double gradoPromedio(Grafo *g) {
  int totalGrados = 0;
  for (int i = 0; i < g->n; i++) {
    totalGrados += grado_nodo(g, i);
  }
  return (double)totalGrados / g->n;
}
// considerando lo que esta en el main.c
bool esCamino(Grafo *g, int *secuencia, int longitudSecuencia) {
  for (int i = 0; i < longitudSecuencia - 1; i++) {
    // Comprobar si existe una arista entre secuencia[i] y secuencia[i + 1]
    printf("probando camino: %d a -> %d\n", i, i + 1);
    if (g->Mad[secuencia[i]][secuencia[i + 1]] == 0) {

      // Si no hay arista, entonces no es un camino válido
      return false;
    }
  }
  // Si todas las aristas existen, entonces es un camino válido
  return true;
}

// Función para obtener todas las aristas del grafo
// misma funcion del TDA Grafo que se utiliza en catedra
Arista **obtenerTodasLasAristas(Grafo *g, int *numAristas) {
  int totalAristas = 0;
  for (int i = 0; i < g->n; i++) {
    for (int j = i + 1; j < g->n;
         j++) { // Para evitar duplicados en grafo no dirigido
      if (g->Mad[i][j] != 0) {
        totalAristas++;
      }
    }
  }

  Arista **aristas = (Arista **)malloc(totalAristas * sizeof(Arista *));
  int k = 0;
  for (int i = 0; i < g->n; i++) {
    for (int j = i + 1; j < g->n; j++) {
      if (g->Mad[i][j] != 0) {
        aristas[k++] = crear_arista(i, j, g->Mad[i][j]);
      }
    }
  }

  *numAristas = totalAristas;
  return aristas;
}

void imprimirAristas(Grafo *g, bool es_dirigido) {
  printf("Aristas del grafo:\n");
  for (int i = 0; i < g->n; i++) {
    for (int j = (es_dirigido ? 0 : i + 1); j < g->n; j++) {
      if (g->Mad[i][j] != 0) {
        printf("Arista desde %d hacia %d con peso %d\n", i, j, g->Mad[i][j]);
        if (!es_dirigido) {
          // Para grafos no dirigidos, cada arista se imprime una sola vez
          printf("Arista desde %d hacia %d con peso %d\n", j, i, g->Mad[i][j]);
        }
      }
    }
  }
}

void matriz_complemento(Grafo *g) {
  printf("    ");
  for (int j = 0; j < g->n; j++) {
    printf("%d   ", j);
  }
  printf("\n");

  // divisor
  for (int j = 0; j < g->n; j++) {
    printf("----");
  }
  printf("\n");

  // Matriz de adyacencia del grafo complemento
  for (int i = 0; i < g->n; i++) {
    // indice lindo de la fila
    printf("%d | ", i);

    for (int j = 0; j < g->n; j++) {
      // Imprimir 1 si no hay arista en el grafo original y no estamos en la
      // diagonal (i != j)
      if (g->Mad[i][j] == 0 && i != j) {
        printf("1   ");
      } else {
        printf("0   ");
      }
    }
    printf("\n");
  }
}

// ultima funcion del TDA Grafo que falta por implementar
/* Dado un arista, verificar si existe en el grafo
Como tenemos el grafo podemos, podemos revisar el v,w de la arista y ver si
tiene un valor distinto a 0, eso implica que existe en el grafo*/
bool pertenece_arista(Grafo *g, Arista *a) {
  // si el peso de la arista es 0 no existe simplemente
  if (a->peso == 0) {
    return false;
  }
  // como v,w son ints de la posicion, puedo ponerlo en la matriz
  // reviso tambien si v y w son menos que n, pero nose si sera necesario, pq
  // la posicion tampoco existiria, lo dejo pq igual se podria usar para
  // verificar
  if (g->Mad[a->v][a->w] == 0 && a->v < g->n && a->w < g->n) {
    return false;
  }
  return true;
}

/* ----------------BFS----------------- */

void BFS(Grafo *G, int origen) {
  // Asigna y inicializa en false usando calloc
  bool *visitados = (bool *)calloc(G->n, sizeof(bool));

  Cola *Q = crear_cola();

  visitados[origen] = true;
  enqueue(Q, origen); // Encolamos el origen

  printf("Recorrido BFS desde el vértice %d:\n", origen);

  while (!cola_vacia(Q)) {   // si no esta vacia
    int actual = dequeue(Q); // tomamos el valor del tope de la cola
    printf("%d ", actual);   // mostramos el desencolado

    // recorremos los vertices adyacentes al que estamos usando
    for (int i = 0; i < G->n; i++) {
      // Si el vertice no esta visitado y hay una arista
      if (!visitados[i] && G->Mad[actual][i] != 0) {
        visitados[i] = true; // lo marcamos como visitado
        enqueue(Q, i);       // lo encolamos
      }
    }
  }

  printf("\n");
  free(Q);         // liberar memoria o replit se enoja
  free(visitados); // liberar memoria o replit se enoja
}

void BFScamino(Grafo *G, int origen, int destino) {
  // Asigna y inicializa en false usando calloc
  bool *visitados = (bool *)calloc(G->n, sizeof(bool));
  int *previo = (int *)malloc(G->n * sizeof(int)); // Para rastrear el camino

  for (int i = 0; i < G->n; i++)
    previo[i] = -1; // Inicializamos previo con -1

  Cola *Q = crear_cola();

  visitados[origen] = true;
  enqueue(Q, origen); // Encolamos el origen

  printf("Recorrido BFS desde el vértice %d hasta %d:\n", origen, destino);

  while (!cola_vacia(Q)) {   // Mientras la cola no esté vacía
    int actual = dequeue(Q); // Tomamos el vértice del frente de la cola
    printf("%d ", actual);   // Mostramos el vértice recién desencolado

    if (actual ==
        destino) { // Si hemos llegado al destino, terminamos la búsqueda
      printf("\nSe ha alcanzado el destino %d\n", destino);
      break;
    }

    // Recorremos los vértices adyacentes al vértice actual
    for (int i = 0; i < G->n; i++) {
      // Si el vértice no está visitado y hay una arista
      if (!visitados[i] && G->Mad[actual][i] != 0) {
        visitados[i] = true; // Lo marcamos como visitado
        previo[i] = actual;  // Rastreamos el nodo previo para el camino
        enqueue(Q, i);       // Lo encolamos
      }
    }
  }

  // Opcional: imprimir el camino si se ha alcanzado el destino
  if (visitados[destino]) {
    printf("Camino del origen al destino: ");
    int n = destino;
    Cola *camino = crear_cola(); // Usamos una cola para imprimir el camino en
                                 // el orden correcto
    while (n != -1) {
      enqueue(camino, n);
      n = previo[n];
    }
    while (!cola_vacia(camino)) {
      printf("%d ", dequeue(camino));
    }
    free(camino);
    printf("\n");
  }

  free(Q);         // No olvidar liberar la memoria de la cola
  free(visitados); // Liberar memoria del arreglo de visitados
  free(previo);    // Liberar memoria del arreglo de previos
}

/* ------------------Articulaciones---------------------- */
/* Se define punto de articulación de un grafo G, conexo, como aquel nodo del
grafo que al eliminarlo transforma G en desconexo. Construya un algoritmo para
identificar todos los puntos de articulación de un grafo
*/
/* mi idea es que voy a remover todas las aristas del nodo del grafo y aplicar
 * DFS al nuevo grafo o usar la funcion conexo, si me retorna algun elemento
 * falso de la lista de visitado o esConexo retorna falso, no sera conexo e
 * implica que es articulacion */
/*
Para cada nodo i en el grafo:
Realizar una copia del grafo sin el nodo i.
Ejecutar DFS desde un nodo inicio (asegurándose de que no sea el nodo i).
Verificar si algún otro nodo no fue visitado.
Si se encuentra algún nodo no visitado, marcar el nodo i como un punto de
articulación.
*/
void articulaciones(Grafo *g) {
  bool *puntos = (bool *)calloc(g->n, sizeof(bool));

  // creacion de matriz copia temporal
  // nodo pivote
  for (int i = 0; i < g->n; i++) {
    // creamos un grafo para cada nodo nuevo
    Grafo *copia = crear_grafo(g->n);
    // ahora copiamos todos
    for (int x = 0; x < g->n; x++) {
      for (int y = 0; y < g->n; y++) {
        // copiamos lainfo que queremos exceptuando la del nodo pivote
        // usamos ternario, si es que estamos en la posicion distinta de i,
        // copiamos, sino sera 0
        copia->Mad[x][y] = (x != i && y != i) ? g->Mad[x][y] : 0;
      }
    }
    // saliendo de la copia de la matriz, realizamos DFS
    bool *visitado = (bool *)calloc(copia->n, sizeof(bool));
    // ternario para ver valor utilizamos, consideramos el 0 exceptuando cuando
    // revisamos el mismo 0
    int inicio = (i == 0) ? 1 : 0;
    // aplicamos DFS
    DFSUtil(copia, inicio, visitado);
    // ahhora que DFS fue aplicado, la lista de visitados se actualiza,
    // revisamos
    for (int j = 0; j < copia->n; j++) {
      // hay que revisar que no estemos buscando el mismo (i) y ademas
      // que sea falso
      if (j != i && !visitado[j]) {
        // si cumple ambas cosas, sera un punto de articulacion
        puntos[j] = true;
        // encontramos el punto asi que break, ya no es necesario seguir
        break;
      }
    }
    // Liberar la memoria de la copia del grafo
    for (int k = 0; k < copia->n; k++) {
      free(copia->Mad[k]);
    }
    free(copia->Mad);
    free(copia);
    free(visitado);
  }
  // termianmos de ciclar para cada punto, imprimimos
  printf("Puntos de articulacion del grafo: ");
  for (int i = 0; i < g->n; i++) {
    if (puntos[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");

  free(puntos);
}

bool esFuertementeConectado(Grafo *g) {
  for (int i = 0; i < g->n; i++) {
    bool *visitado = (bool *)calloc(g->n, sizeof(bool));

    // dfs para cada vertice
    DFSUtil(g, i, visitado);

    // revisamos si es que visito todos
    for (int j = 0; j < g->n; j++) {
      if (!visitado[j]) {
        free(visitado);
        return false;
      }
    }

    free(visitado);
  }
  // si es que todos visitaron cada nodo,
  return true;
}

/* debil conectado */
/* dado un grafo digirido, pasarlo a no dirigido y aplicarle DFS, si es que hay
 * alguno que no este visitado cago */

/* conjunto de nodos que tengan todo el resto de nodos adyacentes, se puede
 * repetir que ambos tengan un adyacente */

bool *conjuntoDominanteMinimoGoloso(Grafo *g) {
  bool *dominante = (bool *)malloc(g->n * sizeof(bool));
  bool *cubierto = (bool *)malloc(g->n * sizeof(bool));

  for (int i = 0; i < g->n; i++) {
    dominante[i] = false;
    cubierto[i] = false;
  }

  while (true) {
    int maxVecinos = -1;
    int nodoElegido = -1;

    for (int i = 0; i < g->n; i++) {
      if (!dominante[i]) {
        int contadorVecinos = 0;

        for (int j = 0; j < g->n; j++) {
          if (g->Mad[i][j] != 0 && !cubierto[j]) {
            contadorVecinos++;
          }
        }

        if (contadorVecinos > maxVecinos) {
          maxVecinos = contadorVecinos;
          nodoElegido = i;
        }
      }
    }

    if (maxVecinos == -1) {
      break;
    }

    dominante[nodoElegido] = true;
    for (int j = 0; j < g->n; j++) {
      if (g->Mad[nodoElegido][j] != 0) {
        cubierto[j] = true;
      }
    }
  }

  free(cubierto);
  return dominante;
}
/*--------Training DFS,BFS y DIJKSTRA-------*/

int find(int i, int parent[]) {
  if (i == parent[i])
    return i;
  return find(parent[i], parent);
}

void union1(int i, int j, int parent[]) {
  int a = find(i, parent);
  int b = find(j, parent);
  parent[a] = b;
}

int compare(const void *a, const void *b) {
  Arista *aristaA = *(Arista **)a;
  Arista *aristaB = *(Arista **)b;
  return aristaA->peso > aristaB->peso;
}

void kruskalMST(Grafo *g) {
  int V = g->n;
  Arista *resultado[V]; // Almacena el árbol de expansión mínima resultante
  int e = 0;            // Índice variable, usado para resultado[]
  int i = 0;            // Índice variable, usado para aristas ordenadas

  // Paso 1: Ordenar todas las aristas en orden no decreciente de su peso
  int numAristas;
  Arista **aristas = obtenerTodasLasAristas(g, &numAristas);
  qsort(aristas, numAristas, sizeof(Arista *), compare);

  int parent[V];

  // Crear V subconjuntos con elementos individuales
  for (int v = 0; v < V; ++v) {
    parent[v] = v;
  }

  // Número de aristas a tomar es igual a V-1
  while (e < V - 1 && i < numAristas) {
    // Paso 2: Elegir la arista más pequeña. Incrementar el índice para la
    // próxima iteración
    Arista *next_edge = aristas[i++];

    int x = find(next_edge->v, parent);
    int y = find(next_edge->w, parent);

    // Si incluir esta arista no causa ciclo, incluirla en el resultado y
    // aumentar el índice de resultado para la próxima arista
    if (x != y) {
      resultado[e++] = next_edge;
      union1(x, y, parent);
    }
    // De lo contrario, descartar la arista
  }

  // Imprimir el árbol de expansión mínima resultante
  for (i = 0; i < e; ++i)
    printf("%d -- %d == %d\n", resultado[i]->v, resultado[i]->w,
           resultado[i]->peso);
  return;
}
int minKey(int key[], bool mstSet[], int n) {
  int min = INT_MAX, min_index;
  for (int v = 0; v < n; v++)
    if (mstSet[v] == false && key[v] < min)
      min = key[v], min_index = v;
  return min_index;
}

void printMST(int parent[], int n, int **graph) {
  printf("Arista \tPeso\n");
  for (int i = 1; i < n; i++)
    printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void primMST(Grafo *g) {
  int parent[g->n]; // Array para almacenar el árbol de expansión construido
  int key[g->n]; // Valores clave usados para seleccionar el mínimo peso de la
                 // arista
  bool mstSet[g->n]; // Representa el conjunto de vértices aún no incluidos en
                     // el MST

  // Inicialización de todas las claves como infinitas y mstSet[] como falso
  for (int i = 0; i < g->n; i++) {
    key[i] = INT_MAX, mstSet[i] = false;
  }

  // Incluir siempre el primer vértice en el MST
  key[0] = 0;
  parent[0] = -1; // El primer nodo siempre es la raíz del MST

  for (int count = 0; count < g->n - 1; count++) {
    // Selecciona el vértice mínimo de key[] que no está en mstSet[]
    int u = minKey(key, mstSet, g->n);

    mstSet[u] = true; // Añadir el vértice seleccionado al conjunto del MST

    // Actualizar los valores de clave y el índice del padre de los vértices
    // adyacentes al vértice seleccionado
    for (int v = 0; v < g->n; v++) {
      // g->Mad[u][v] es no cero solo para los vértices adyacentes de m
      // mstSet[v] es falso para los vértices no incluidos en el MST
      // Actualiza la clave solo si g->Mad[u][v] es más pequeño que key[v]
      if (g->Mad[u][v] && mstSet[v] == false && g->Mad[u][v] < key[v])
        parent[v] = u, key[v] = g->Mad[u][v];
    }
  }

  // Imprimir el árbol de expansión mínimo construido
  printMST(parent, g->n, g->Mad);
}
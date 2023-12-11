#include "TDA_Lista_Enlazada.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/*
// estructura de datos del TDA lista

struct nodo {
  int info;
  struct nodo *Sig;
};
typedef struct nodo Nodo;

struct lista {
  Nodo *head;
  int n; // cantidad de elementos que tiene la lista
};
typedef struct lista Lista; */
/* funciones basicas del TDAgrafo, necesarias
- CrearGrafo( V, E) -> grafo
- ObtenerAdyacentes(G, v) ->aristas[]
- crearArista(vertice,vertice) ->arista
- insertarArista(grafo,arista) ->
- mostrarGrafo(grafo)
- removerArista(grafo,arista) ->
- perteceArista(grafo,arista) -> bool
- obtenerAristas(grafo) -> aristas[]
- gradoVertice(grafo,vertice) -> num
*/
struct grafo {
  Lista **Lad;
  int n; // cantidad de nodos/vertices
};
typedef struct grafo Grafo;

struct arista {
  int v, w;
  int peso;
};
typedef struct arista Arista;

Arista *crearArista(int v, int w, int peso) {
  Arista *Salida = (Arista *)malloc(sizeof(Arista));
  Salida->v = v;
  Salida->w = w;
  Salida->peso = peso;
  return Salida;
}

Grafo *crearGrafo(int n) {
  Grafo *grafo;
  int i;
  grafo = (Grafo *)malloc(sizeof(Grafo));
  grafo->n = n;
  grafo->Lad = (Lista **)malloc(sizeof(Lista) * n);
  for (i = 0; i < n; i++) {
    grafo->Lad[i] = crear_lista();
  }
  return grafo;
}

void insertarArista(Grafo *grafo, Arista *a) {
  insertar_nodo_ini(grafo->Lad[a->v], a->w);
}

void mostrarGrafo(Grafo *g) {
  printf("Listas de adyacencia del grafo:\n");
  for (int i = 0; i < g->n; i++) {
    printf("Vertice %i: ", i);
    print_lista(g->Lad[i]);
    printf("\n"); // Cambio de línea después de imprimir todos los adyacentes
                  // del vértice i
  }
}
#include <stdio.h>
#include <stdlib.h>

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
typedef struct lista Lista;

// crear lista inicial
Lista *crear_lista() {
  Lista *L = (Lista *)malloc(sizeof(Lista));
  // como *L es tipo lista hay que definiar su head y n
  L->head = NULL;
  L->n = 0;
  return L;
}

// lista vacia?

int lista_vacia(Lista *L) {
  if (L->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

Nodo *crear_nodo(int valor) {
  Nodo *nodo;
  nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->info = valor;
  nodo->Sig = NULL;
  return nodo;
}

void insertar_nodo_ini(Lista *L, int valor) {
  // crear nodo que se quiere agregar
  Nodo *Nodo_nuevo = crear_nodo(valor);
  if (!(lista_vacia(L))) {     // si la lista no esta vacia
    Nodo_nuevo->Sig = L->head; // la nueva cabecera sera el nodo creado
  }
  L->head = Nodo_nuevo;
  L->n = L->n + 1;
}

void insertar_nodo_fin(Lista *L, int valor) {
  Nodo *Nodo_nuevo = crear_nodo(valor);
  if (!(lista_vacia(L))) {
    // nuevo nodo se iguala con la cabecera
    Nodo *aux;
    aux = L->head; // nodo nuevo se posiciona en la cabecera
    while (aux->Sig != NULL) {
      aux = aux->Sig;
    }
    aux->Sig = Nodo_nuevo; // estamos en la ultima posicion, agregamos el nodo
  }
  // si es que esta vacia
  else {
    L->head = Nodo_nuevo; // como esta vacia, el ultimo elemento es el nodo
  }
  L->n = L->n + 1;
}

void agregar_nodo(Lista *L, int valor, int posicion) {
  // hay que ver primero si se puede agregar ese valor
  if (L->n >= posicion && posicion > 0) {
    Nodo *Nuevo_nodo = crear_nodo(valor);
    if (posicion == 0) {
      insertar_nodo_ini(L, valor);
      return;
    }
    if (posicion == L->n) {
      insertar_nodo_fin(L, valor);
      return;
    }
    // si se cumple podemos empezar a buscar la posicion a la que queremos
    // llegar

    Nodo *anterior, *actual; // nodos para recorrer
    anterior = NULL;
    actual = L->head;
    int i = 0;
    while (i < posicion) {
      anterior = actual;
      actual = actual->Sig;
      i++;
    }
    anterior->Sig = Nuevo_nodo;
    Nuevo_nodo->Sig = actual;
    L->n = L->n + 1;
  } else {
    printf("Posicion no valida");
    return;
  }
}

void print_lista(Lista *L) {
  Nodo *aux;
  if (!lista_vacia(L)) {
    aux = L->head;
    printf("\n");
    while (aux != NULL) {
      printf("->%d", aux->info);
      aux = aux->Sig;
    }
  }
}

void eliminar_nodo_inicio(Lista *L) {
  Nodo *aux = L->head;
  L->head = L->head->Sig;
  free(aux);
  L->n = L->n - 1;
}

void eliminar_nodo_final(Lista *L) {
  if (L->head == NULL)
    return; // caso que la lista este vacia
  // si hay solo un nodo
  if (L->head->Sig == NULL) { // si el siguiente nodo esta vacio
    free(L->head);
    L->head = NULL;
  } else {
    Nodo *anterior = NULL;
    Nodo *actual = L->head;
    // recorremos hasta el final de la lsita
    while (actual->Sig != NULL) {
      anterior = actual;
      actual = actual->Sig;
    }
    // como ya llegamos hasta el final, liberamos la ultima posicion y free de
    // actual
    anterior->Sig = NULL;
    free(actual);
  }
}

void invertir_lista(Lista *L) {
  Nodo *anterior = NULL;
  Nodo *actual = L->head; // nos ponemos en la cabecera
  Nodo *siguiente = NULL;

  while (actual != NULL) {
    siguiente = actual->Sig;

    actual->Sig = anterior;

    anterior = actual;
    actual = siguiente;
  }

  L->head = anterior;
}

void contarOcurrencias(Lista *L1, Lista *L2) {
  Nodo *nodo1 = L1->head;
  while (nodo1 != NULL) {
    int contador = 0;
    Nodo *nodo2 = L2->head;
    while (nodo2 != NULL) {
      if (nodo1->info == nodo2->info) {
        contador++;
      }
      nodo2 = nodo2->Sig;
    }
    printf("Valor: %d, Ocurrencias en L2: %d\n", nodo1->info, contador);
    nodo1 = nodo1->Sig;
  }
}
int obtener_valor(Lista *L, int pos) {
  // Si la posición es inválida
  if (pos < 0 || pos >= L->n) {
    printf("Posición inválida.\n");
    return -1; // Puedes retornar un valor especial para indicar error, en este
               // caso -1.
  }

  // Recorremos la lista hasta llegar a la posición deseada
  Nodo *aux = L->head;
  int i = 0;
  while (i < pos) {
    aux = aux->Sig;
    i++;
  }

  // Retornamos el valor en la posición solicitada
  return aux->info;
}

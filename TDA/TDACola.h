#include <stdio.h>
#include <stdlib.h>

// estructura de datos del TDA Cola

struct nodo {
  int info;
  struct nodo *Sig;
};
typedef struct nodo Nodo;

struct cola {
  Nodo *front; // inicio de la cola
  Nodo *rear;  // final de la cola
  int n;       // cantidad de elementos que tiene la cola
};
typedef struct cola Cola;

Cola *crear_cola() {
  Cola *Q = (Cola *)malloc(sizeof(Cola));
  Q->front = NULL;
  Q->rear = NULL;
  Q->n = 0;
  return Q;
}

int cola_vacia(Cola *Q) { return Q->front == NULL; }

Nodo *crear_nodo(int valor) {
  Nodo *nodo;
  nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->info = valor;
  nodo->Sig = NULL;
  return nodo;
}

void enqueue(Cola *Q, int valor) {
  Nodo *Nodo_nuevo = crear_nodo(valor);
  if (cola_vacia(Q)) {
    Q->front = Nodo_nuevo;
    Q->rear = Nodo_nuevo;
  } else {
    Q->rear->Sig = Nodo_nuevo;
    Q->rear = Nodo_nuevo;
  }
  Q->n++;
}

int dequeue(Cola *Q) {
  if (cola_vacia(Q)) {
    printf("Error: La cola está vacía.\n");
    exit(1); // O puedes manejar el error de otra manera
  }

  Nodo *temp = Q->front;
  int valor = temp->info;
  Q->front = Q->front->Sig;

  if (Q->front == NULL) { // Si despues de remover, la cola queda vacia
    Q->rear = NULL;
  }

  free(temp);
  Q->n--;

  return valor; // Retornamos el valor desencolado
}

void mostrar_cola(Cola *Q) {
  if (Q == NULL || Q->n == 0) {
    printf("Cola está vacía.\n");
    return;
  }

  Cola *temp = crear_cola();

  // Desencolando de la cola original y encolando en la temporal mientras
  // imprimimos
  printf("Cola: ");
  while (!cola_vacia(Q)) {
    int valor = dequeue(Q);
    enqueue(temp, valor);
    printf("%d ", valor);
  }
  printf("\n");

  // Copiando de nuevo la cola temporal a la original
  while (!cola_vacia(temp)) {
    int valor = dequeue(temp);
    enqueue(Q, valor);
  }

  // Liberar memoria de la cola temporal
  free(temp);
}
/*
void duplicar_valor_pares(Cola *Q) {
  if (Q == NULL || Q->n == 0) {
    return; // La cola está vacía o es nula
  }

  Cola *temp = crear_cola();

  while (!cola_vacia(Q)) {
    int valor = dequeue(Q);
    if (valor % 2 == 0) { // Si es par, duplicamos su valor
      valor *= 2;
    }
    enqueue(temp, valor);
  }

  // Copiamos de nuevo la cola temporal a la original
  while (!cola_vacia(temp)) {
    int valor = dequeue(temp);
    enqueue(Q, valor);
  }

  // Liberar memoria de la cola temporal
  free(temp);
}
*/
Cola *extraer_pares(Cola *Q) {
  if (Q == NULL || Q->n == 0) {
    return NULL; // La cola está vacía o es nula
  }

  Cola *temp = crear_cola();
  Cola *pares = crear_cola();

  while (!cola_vacia(Q)) {
    int valor = dequeue(Q);
    if (valor % 2 == 0) { // Si es par, encolamos en la cola de pares
      enqueue(pares, valor);
    }
    enqueue(temp,
            valor); // Encolamos en la cola temporal para restaurar la original
  }

  // Restauramos la cola original
  while (!cola_vacia(temp)) {
    int valor = dequeue(temp);
    enqueue(Q, valor);
  }

  // Liberar memoria de la cola temporal
  free(temp);

  return pares; // Retornamos la cola con los valores pares
}

void duplicar_valor_pares_sinColaAux(Cola *Q) {
  if (Q == NULL || Q->front == NULL) {
    return; // La cola está vacía o es nula
  }

  Nodo *ultimo_original = Q->rear;
  Nodo *nodo_actual = NULL;

  do {
    int valor = dequeue(Q);
    if (valor % 2 == 0) { // Si es par, duplicamos su valor antes de encolar
      valor *= 2;
    }
    enqueue(Q, valor);

    // Si es la primera iteración, asignamos nodo_actual a la nueva cola
    if (nodo_actual == NULL) {
      nodo_actual = Q->rear;
    } else {
      nodo_actual = NULL; // nodo_actual->Sig;
    }
  } while (nodo_actual != ultimo_original);
}

void invertir_cola_sin_auxiliar(Cola *Q) {
  if (cola_vacia(Q)) {
    return;
  }

  // Desencolar un elemento
  int valor = dequeue(Q);

  // Invertir recursivamente el resto de la cola
  invertir_cola_sin_auxiliar(Q);

  // Encolar el elemento desencolado
  enqueue(Q, valor);
}

void remover_mayor(Cola *Q) {
  if (Q == NULL || Q->n == 0) {
    return; // La cola está vacía o es nula
  }
  int INT_MIN;
  int mayor = INT_MIN; // Usamos el menor valor posible para inicializar

  Cola *temp = crear_cola();

  // Identificar el mayor
  while (!cola_vacia(Q)) {
    int valor = dequeue(Q);
    if (valor > mayor)
      mayor = valor;
    enqueue(temp, valor);
  }

  // Reconstruir la cola sin el mayor
  while (!cola_vacia(temp)) {
    int valor = dequeue(temp);
    if (valor != mayor) {
      enqueue(Q, valor);
    }
  }

  // Liberar memoria de la cola temporal
  free(temp);
}

void remover_menor(Cola *Q) {
  if (Q == NULL || Q->n == 0) {
    return; // La cola está vacía o es nula
  }
  int INT_MAX;
  int menor = INT_MAX; // Usamos el mayor valor posible para inicializar

  Cola *temp = crear_cola();

  // Identificar el menor
  while (!cola_vacia(Q)) {
    int valor = dequeue(Q);
    if (valor < menor)
      menor = valor;
    enqueue(temp, valor);
  }

  // Reconstruir la cola sin el menor
  while (!cola_vacia(temp)) {
    int valor = dequeue(temp);
    if (valor != menor) {
      enqueue(Q, valor);
    }
  }

  // Liberar memoria de la cola temporal
  free(temp);
}

float calcular_promedio(Cola *Q) {
  if (Q == NULL || Q->n == 0) {
    printf("Error: La cola está vacía o es nula.\n");
    return 0.0; // Devuelve 0 si la cola está vacía o es nula
  }

  int suma = 0;
  int cantidad = 0;
  Cola *temp = crear_cola();

  // Recorremos la cola, sumando sus elementos y contando cuántos hay
  while (!cola_vacia(Q)) {
    int valor = dequeue(Q);
    suma += valor;
    cantidad++;
    enqueue(temp, valor);
  }

  // Restauramos la cola original
  while (!cola_vacia(temp)) {
    int valor = dequeue(temp);
    enqueue(Q, valor);
  }

  // Liberar memoria de la cola temporal
  free(temp);

  return (float)suma / cantidad; // Devuelve el promedio
}

void remover_menores_que_valor(Cola *Q, int valor) {
  if (Q == NULL || Q->n == 0) {
    return; // La cola está vacía o es nula
  }

  Cola *temp = crear_cola();

  // Desencolar cada elemento y verificar si es menor que el valor dado
  while (!cola_vacia(Q)) {
    int elemento = dequeue(Q);
    if (elemento >= valor) {
      enqueue(temp, elemento); // Encolar en cola temporal si es mayor o igual
    }
  }

  // Reconstruir la cola original con los elementos restantes
  while (!cola_vacia(temp)) {
    int elemento = dequeue(temp);
    enqueue(Q, elemento);
  }

  // Liberar memoria de la cola temporal
  free(temp);
}

Cola *mezclar(Cola *L1, Cola *L2) {
  Cola *mezclada = crear_cola();

  while (!cola_vacia(L1) || !cola_vacia(L2)) {
    if (!cola_vacia(L1)) {
      enqueue(mezclada, dequeue(L1));
    }
    if (!cola_vacia(L2)) {
      enqueue(mezclada, dequeue(L2));
    }
  }

  return mezclada;
}

Cola *ordenarCola(Cola *L, int orden) {
  Cola *aux = crear_cola();
  int INT_MAX;
  int INT_MIN;

  while (!cola_vacia(L)) {
    int seleccionado = (orden == 1) ? INT_MAX : INT_MIN;
    Cola *temp = crear_cola();

    // Encuentra el menor/mayor elemento en L, dependiendo de 'orden'
    while (!cola_vacia(L)) {
      int valor = dequeue(L);
      if ((orden == 1 && valor <= seleccionado) ||
          (orden == 2 && valor >= seleccionado)) {
        if ((orden == 1 && valor == seleccionado) ||
            (orden == 2 && valor == seleccionado)) {
          enqueue(
              temp,
              valor); // Volver a encolar el valor si es igual al seleccionado
        } else {
          if (seleccionado != ((orden == 1) ? INT_MAX : INT_MIN)) {
            enqueue(temp, seleccionado); // Volver a encolar el valor
                                         // previamente seleccionado
          }
          seleccionado = valor;
        }
      } else {
        enqueue(temp, valor);
      }
    }

    // Encola el elemento seleccionado en aux
    enqueue(aux, seleccionado);

    // Copia temp de vuelta a L
    while (!cola_vacia(temp)) {
      enqueue(L, dequeue(temp));
    }
    free(temp);
  }

  // Copia aux de vuelta a L
  while (!cola_vacia(aux)) {
    enqueue(L, dequeue(aux));
  }
  free(aux);

  return L;
}

/*
// Crear una pila auxiliar
struct Stack {
  Nodo *top;
} stack;
typedef struct Stack Stack;

// Funciones auxiliares para la pila
void push(int valor) {
  Nodo *nuevo = crear_nodo(valor);
  nuevo->Sig = stack.top;
  stack.top = nuevo;
}

int pop() {
  if (stack.top == NULL) {
    printf("Error: La pila está vacía.\n");
    exit(1);
  }
  Nodo *temp = stack.top;
  int valor = temp->info;
  stack.top = stack.top->Sig;
  free(temp);
  return valor;
}

void invertir_cola_con_auxiliar(Cola *Q) {

  // Desencolar todos los elementos y apilarlos
  while (!cola_vacia(Q)) {
    push(dequeue(Q));
  }

  // Desapilar y encolar todos los elementos
  while (stack.top != NULL) {
    enqueue(Q, pop());
  }
}
*/
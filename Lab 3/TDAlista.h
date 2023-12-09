#include <stdio.h>
#include <stdlib.h>


struct nodo{
  int info;
  struct nodo *sig;
};
typedef struct nodo Nodo;

struct lista{    //encabezado de lista con puntero y contador
  Nodo *head;
  int n; //Número nodo de nodos agregados a la lista
};
typedef struct lista Lista;

Lista *crearListaVacia(){
  Lista *lista=(Lista*)malloc(sizeof(Lista));
  lista->head=NULL;
  lista->n=0;
  return lista;
}

int esListaVacia(Lista *lista){
  if (lista->head == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(Lista *lista){
  if (!esListaVacia(lista))
  {
    Nodo* auxiliar=lista->head;
    while (auxiliar!=NULL)
    {
      printf("%d ",auxiliar->info);
      auxiliar=auxiliar->sig;
    }
    printf("\n");
  }
  else
    printf("La lista esta vacia\n");
}

void insertarInicio(Lista *lista, int dato){
  Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
  nuevo->info=dato;
  nuevo->sig=lista->head;
  lista->head=nuevo;
  lista->n=lista->n+1;
}

void insertarFin(Lista *lista, int dato){
  Nodo* nuevo;
  Nodo *aux;

	//crear Nodo nuevo
	nuevo=(Nodo*)malloc(sizeof(Nodo));
	nuevo->info=dato;
	nuevo->sig = NULL;
  
	//buscar fin de lista
	
	//1. lista vacia
	if(lista->head == NULL){
		lista->head = nuevo;
		lista->n=lista->n+1;
		return; 
	}

	//2. lista con un elemento
	if(lista->head->sig == NULL){
		lista->head->sig = nuevo;
		lista->n=lista->n+1;
		return; 
	}

	//3. lista con mas de un elemento
	aux = lista->head;
	while(aux->sig != NULL)
		aux = aux->sig;
	
	aux->sig = nuevo;
	lista->n=lista->n+1;
	return; 
}

void eliminarInicio(Lista *lista){
  Nodo *auxiliar;
  if(!esListaVacia(lista))
  {
    auxiliar=lista->head;
    lista->head=(lista)->head->sig;
    free(auxiliar);
	lista->n=lista->n-1;
  }
}

void liberarLista(Lista* lista){

	while(!esListaVacia(lista)){
		eliminarInicio(lista);	
	}		

}


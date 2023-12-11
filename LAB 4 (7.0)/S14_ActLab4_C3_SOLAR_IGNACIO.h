#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/* no se cambio niguna funcionalidad del TDA, solo se quitaron los espacios, agrupando*/
/* Estructura de Datos ABO */
typedef struct nodoABO{
	int dato;
	struct nodoABO *izq;
	struct nodoABO *der;
}NodoABO;
typedef struct arbol{
  NodoABO  *raiz;
}Arbol;

/* Encabezados  */
Arbol *crear_arbol();
NodoABO  *crear_nodo(int val);
NodoABO  *insertarDato(NodoABO  *r, int val); 
NodoABO  *buscarDato(NodoABO  *aux, int val);
void preOrden(NodoABO * n);
void inOrden(NodoABO * n);
void postOrden(NodoABO * n);
NodoABO  *eliminarDato(NodoABO  *aux, int val);
NodoABO  *buscarSucesor(NodoABO  *aux);

/* OPERACIONES */
Arbol *crear_arbol(){
  Arbol *a;
  a = (Arbol*) malloc(sizeof(Arbol));
  a->raiz = NULL;
  return a;
}
NodoABO  *crear_nodo(int val){
	NodoABO  *nuevo;
	nuevo = (NodoABO *)malloc(sizeof(NodoABO ));
	nuevo->dato = val;
	nuevo->izq = NULL; 
	nuevo->der = NULL;
  return nuevo;
}
bool es_hoja(NodoABO  *aux){
	if (aux == NULL )
		return false;
	else 
		if ( (aux->izq == NULL)  && (aux->der == NULL) )
			return true;
		else 
			return false;
}
NodoABO  *insertarDato(NodoABO  *aux, int val ){
	if (aux == NULL)
		return crear_nodo(val);
	else
		if (val<= aux->dato)/* avanza por la izquierda */
 			aux->izq = insertarDato(aux->izq, val);
		else if (val > aux->dato) /* o lo crea en el lado derecho */
			aux->der = insertarDato(aux->der,val); 
	return aux;
}
NodoABO  *buscarDato(NodoABO  *aux, int val){
	if (aux == NULL)
        return NULL;
    else
        if (val == aux->dato)
            return aux;
        else
            if (val < aux->dato)
                return buscarDato(aux->izq, val);
            else
                return buscarDato(aux->der, val);
}
void preOrden(NodoABO  *aux){
	if(aux == NULL) 
		return;
	else {
		printf("%d, ", aux->dato);
		preOrden(aux->izq);
		preOrden(aux->der);
	}	
}
void inOrden(NodoABO  *aux){
	if(aux != NULL) {
		inOrden(aux->izq);
		printf("%d, ",aux->dato);
		inOrden(aux->der);
	}	
}
void postOrden(NodoABO  *aux){
	if(aux == NULL) 
		return;
	else {
		postOrden(aux->izq);
		postOrden(aux->der);
		printf("%d, ", aux->dato);
	}	
}
NodoABO  *eliminarDato(NodoABO  *aux, int val){
	//aux = buscar(aux,val);
	if (aux == NULL){ 
		return NULL;
		//printf("Elemento no existe. No se pudo eliminar");
	}else{
    if (val < aux->dato) 
         aux->izq = eliminarDato(aux->izq, val); //engancha el �rbol al eliminar
    else if( val > aux->dato) 
         aux->der = eliminarDato(aux->der, val); //engancha el �rbol al eliminar
    else{ /*LO ENCUENTRA*/		
		if (es_hoja(aux)){			
			free(aux); 
			aux = NULL;
		}else{
			NodoABO *auxe = aux;
			if ( (auxe->der == NULL) && (auxe->izq != NULL)){ // eliminar nodo con UN HIJO(izquierdo)
				aux = auxe-> izq; // aux apunta al hijo izq
				free(auxe); 
				auxe = NULL;
			}else if ( (auxe->der != NULL) && (auxe->izq == NULL)){ // eliminar nodo con UN HIJO(derecho)
				aux = auxe-> der; // aux apunta al hijo derecho 
				free(auxe); 
				auxe = NULL;
				}else{/* CASO  DOS HIJOS */
					NodoABO *suc;
					suc = buscarSucesor(aux->der); 
					if (suc != NULL){
						aux->dato = suc->dato; /*Copia el sucesor al nodo a eliminar */
						aux->der = eliminarDato(aux->der, suc->dato); /*pasa el sub arbol derecho para que busque el nodo a eliminar*/
					}
				}
			}
		}
	}
	return aux;
}
NodoABO *buscarSucesor(NodoABO *aux){ //Buscar nodo Menor de los mayores 
    if(aux == NULL) 
			return NULL;
	else
  		if(aux->izq != NULL)
			return buscarSucesor(aux->izq);
		else
			return aux; /* lleg� al sucesor */		
}
//ARBOL-BORRAR//
void *borrarArbol (NodoABO *raiz){
    if (raiz == NULL){
        free (raiz);
        raiz = NULL;
		}else{
        borrarArbol(raiz->izq);
        borrarArbol(raiz->der);
    }
}


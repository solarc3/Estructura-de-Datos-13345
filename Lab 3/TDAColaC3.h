#include <stdio.h>
#include <stdlib.h>

//Usa TDALista.h


typedef struct cola{
	int n;
	Lista *cola; 
} ColaC3;

ColaC3 *crearColaC3(){
	
	ColaC3 *nuevo;
	
	nuevo = (ColaC3 *)malloc(sizeof(ColaC3));
	nuevo->n = 0;
	nuevo->cola = crearListaVacia();	
}

int esColaVacia(ColaC3 *C){
	if(C->n == 0)
		return 1;
	else
		return 0;
}

void mostrarColaC3(ColaC3 *C){
	
	printf("\n\nMostrando ColaC3\n");
	recorrerLista(C->cola);
	
}

void encolarC3(ColaC3 *C, int dato){

	insertarFin(C->cola, dato);
	C->n++;
	
}

int desencolarC3(ColaC3 *C){

	int dato;
	
	dato = C->cola->head->info;
	eliminarInicio(C->cola);
	C->n--;
	return dato;
}
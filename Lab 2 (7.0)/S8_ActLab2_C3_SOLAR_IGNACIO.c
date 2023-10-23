#include <stdlib.h>
#include <stdio.h>

/* Agregue el TDA que va a utilizar en esta actividad*/
#include "S8_TDALista_C3_SOLAR_IGNACIO.h"

/* Agregue aquí las funciones requeridas para resolver la actividad */
//Funcion problema 4
Listac3 *solo_impares(Listac3 *L1) {
  Listac3 *L_impares = c3crear_lista(); // lista nueva para impares
  Nodoc3 *nodo_actual = L1->headc3;     // aux nodo, se apodera de lista entrada
  while (nodo_actual != NULL) {
    if (nodo_actual->infoc3 % 2 != 0) { // si la info es impar %2==1 tbm sirve
      c3insertar_nodo_fin(L_impares, nodo_actual->infoc3);
    }
    nodo_actual = nodo_actual->sigc3; // iterador
  }
  return L_impares;
}
//Funcion problema 5
//Para el problema 5, simplemente recorremos k veces eliminar el elemento medio
void eliminarKCentrales(Listac3 *L3, int k) {
	int i = 0;
	while(i<k){
		eliminarCentral(L3);//llamada funcion central dentro del ciclo
		i++;
		}
}


int main(int argc,  char *argv[]) {
	
	/* DECLARACIÓN DE VARIABLES 
	  Declare aquí las variables necesarias para resolver los problemas de la actividad */
	Listac3 *L1 = c3crear_lista(); //lista original
	Listac3 *L2; //lista para impares
	int size;// size para el tamano de la lista

	printf("\n");

	/* PROBLEMA 1. 
		   Utilizando las funciones de agregar inicio y fin, vamos agregando segun piden, e imprimiendo*/
    printf("Resultados del problema 1:\n");			
	c3insertar_nodo_fin(L1,15);
    c3mostrar_lista(L1);
    c3insertar_nodo_fin(L1,30);
    c3mostrar_lista(L1);
    c3insertar_nodo_ini(L1,20);
    c3mostrar_lista(L1);
    c3insertar_nodo_fin(L1,1);
    c3mostrar_lista(L1);
    c3insertar_nodo_fin(L1,4);
    c3mostrar_lista(L1);
    c3insertar_nodo_ini(L1,8);
    c3mostrar_lista(L1);
    c3insertar_nodo_ini(L1,3);
    c3mostrar_lista(L1);
    c3insertar_nodo_fin(L1,5);
    c3mostrar_lista(L1);
    printf("\n");
    printf("\n");

		/* PROBLEMA 2. 
		   ya que la estructura de datos ya contiene el largo, simplemente lo imprimimos
		   * las funciones anteriores actualizan el largo*/
    printf("Resultados del problema 2:\n");		
	size = contarElementos(L1);
	printf("Hay %d elementos en la lista",size);
    printf("\n");
    printf("\n");
		/* PROBLEMA 3. 
			LLamamos la funcion solo_impares para hacer el calculo e imprimimos*/
    printf("Resultados del problema 3:\n");
    L2=solo_impares(L1);
    printf("Lista 1 original");
    c3mostrar_lista(L1);
    printf("\n");
    printf("\n");
    printf("Lista 2 Solo impares");
    c3mostrar_lista(L2);
    printf("\n");
    printf("\n");
		/* PROBLEMA 4. 
			LLamamos la funcion eliminarCentral para hacer lo requerido e imprimimos*/
    printf("Resultados del problema 4:\n");
    printf("Elemento 30 sera eliminado de la lista");		
	eliminarCentral(L1);
	c3mostrar_lista(L1);
    printf("\n");
    printf("\n");
		/* PROBLEMA 5. 
			Hay que llamar la funcion del problema 4 k veces, se hace otra funcion para hacer eso*/
			//ojo que aqui ya se elimino el elemento 30, se utiliza sobre la misma lista L1
    printf("Resultados del problema 5:\n");
    printf("Removido los 4 elementos medios");
	eliminarKCentrales(L1,4);
	c3mostrar_lista(L1);
    printf("\n");
    printf("\n");
		return 0;
}

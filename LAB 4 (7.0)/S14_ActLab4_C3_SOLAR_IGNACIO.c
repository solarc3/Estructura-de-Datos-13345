#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "S14_ActLab4_C3_SOLAR_IGNACIO.h"
void printLeaves(NodoABO *raiz) {
    if (raiz == NULL) {
        return;//si es que esta vacio, no retornamos -1 porque es tipo void
    }
    if (es_hoja(raiz)) {//si se llega a un hoja
        printf("%d ", raiz->dato);
    }
    printLeaves(raiz->izq);//recursivo
    printLeaves(raiz->der);//recursivo
}
int heightTree(NodoABO* raiz){
    if (raiz == NULL){
        return -1; //si es que esta vacio, -1 para representar eso
    } else if (es_hoja(raiz)){//usamos la funcion del TDA
        return 1; //se retorna 1 para ir sumando, si un arbol tiene un unico nodo, ese mismo es hijo, por lo tanto es 1 default
    } else {
        int alturaIzq = heightTree(raiz->izq);//recursivo
        int alturaDer = heightTree(raiz->der);//recursivo
        return alturaIzq > alturaDer ? alturaIzq + 1 : alturaDer + 1; //ternario para ver cual camino se sigue y se le va sumando a la recursion
    }
}
int heightNode(NodoABO* raiz, int dato){
    if (raiz == NULL){
        return -1; //si es que esta vacio, -1 para representar que esta vacio
    }//buscamos el nodo que queremos encontrar, se asume el primero que se encuentra (sin repetidos)
    NodoABO * target = buscarDato(raiz, dato);//llamamos la funcion del TDA
    if (target == NULL){
        return -1;//lo mismo, si no existe -1 para representar que no esta
    }
    return heightTree(target);//en vez de partir en el la raiz, partimos del nodo que queriamos, usando la misma funcion del problema anterior
}
int main() {
    /* PROBLEMA 1*/
    FILE* archivo = fopen("datos40_1-1000.txt", "r"); 
    //por instrucciones de la profe, no se deja como parametro de entrada, se le asigna aca el archivo a leer
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1; //caso de borde
    }
    Arbol* arbolito = crear_arbol(); //se crea tipo arbol pero usamos la raiz de este siempre usando funcion del TDA
    int dato,n,i;//asignamos memoria, para poner el dato, la cantidad de datos y el iterador
    fscanf(archivo, "%d", &n); //primer valor que nos da la cantidad total, en vez de usar EOF en un while 
    printf("PROBLEMA 1: LEER ARCHIVO E INORDEN DEL ARBOL\n");
    for (i = 0; i < n; i++) {
        fscanf(archivo, "%d", &dato);
        arbolito->raiz = insertarDato(arbolito->raiz, dato);//agregamos datos desde la raiz usando la funcion del TDA
        if(i % 8 == 0){//modulo 8 para que no se imprima muchas veces
            inOrden(arbolito->raiz); //recorrido usando la funcion del TDA
            printf("\n\n\n"); //espacios extra para que no tenga tanto cluster de numeros al imprimir
        }//como se imprime el 247 en el primer print, implica que quedo como raiz y luego queda en el centro y ademas que se printean de menor a mayor
    }
    inOrden(arbolito->raiz);//ultimo recorrido, cuando ya estan todos los datos
    printf("\n\n\n");
    fclose(archivo);//se le asigno memoria al arbol, no es necesario dejarlo abierto
    
    
    /* PROBLEMA 2 */
    printf("PROBLEMA 2: HOJAS DEL ARBOL\n");
    printf("las hojas del arbol son: ");
    printLeaves(arbolito->raiz);
    
    
    /* PROBLEMA 3*/
    printf("\n\n");
    printf("PROBLEMA 3: ALTURA DEL ARBOL\n");
    int altura = heightTree(arbolito->raiz);
    printf("la altura del arbol es: %d", altura);
    printf("\n\n");
    
    
    /*PROBLEMA 4*/
    printf("PROBLEMA 4: ALTURA DE UN NODO\n");
    int alturaNodo = heightNode(arbolito->raiz, 534);
    printf("la altura del nodo 534 es: %d", alturaNodo);
    printf("\n\n");
    
    
    /* ya se utilizo el arbol, se vacia memoria*/
    borrarArbol(arbolito->raiz);
    return 0;
}
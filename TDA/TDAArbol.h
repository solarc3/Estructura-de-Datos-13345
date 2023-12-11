#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
struct nodo {
    int dato;
    struct nodo* padre; // Opcional, depende de la implementación
    struct nodo* hijoIzquierdo;
    struct nodo* hijoDerecho;
};
typedef struct nodo nodo;
nodo* crear_raiz(int dato){
    nodo* raiz = (nodo*)malloc(sizeof(nodo));
    raiz->dato = dato;
    raiz->padre = NULL;
    raiz->hijoIzquierdo = NULL;
    raiz->hijoDerecho = NULL;
    return raiz;
}

nodo* crear_nodo(int dato){
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->padre = NULL;
    nuevo->hijoIzquierdo = NULL;
    nuevo->hijoDerecho = NULL;
    return nuevo;
}

/*---------- operaciones -----------------*/
// insercion de nodos con relleno de niveles antes de continuar al otro
void insertar(nodo* raiz, int dato){
    nodo* nuevo = crear_nodo(dato);
    nodo* aux = raiz;
    while (aux->hijoIzquierdo != NULL && aux->hijoDerecho != NULL){
        if (aux->hijoIzquierdo != NULL){
            aux = aux->hijoIzquierdo;
        } else {
            aux = aux->hijoDerecho;
        }
    }
    if (aux->hijoIzquierdo == NULL){
        aux->hijoIzquierdo = nuevo;
        nuevo->padre = aux;
    } else {
        aux->hijoDerecho = nuevo;
        nuevo->padre = aux;
    }
}

bool esVacio(nodo* raiz){
    return raiz == NULL;
}
// buscar valor
nodo* buscar(nodo* raiz, int dato){
    nodo* aux = raiz;
    while (aux != NULL){
        printf("Buscando dato: %d\n", dato); // Print to track the search
        if (aux->dato == dato){
            return aux;
        } else if (aux->dato > dato){
            printf("Dato actual: %d, Moviendo hacia el hijo izquierdo\n", aux->dato); // Print to track the movement
            aux = aux->hijoIzquierdo;
        } else {
            printf("Dato actual: %d, Moviendo hacia el hijo derecho\n", aux->dato); // Print to track the movement
            aux = aux->hijoDerecho;
        }
    }
    return NULL;
}

bool eshoja(nodo* raiz){
    return raiz->hijoIzquierdo == NULL && raiz->hijoDerecho == NULL;
}

int contarHojas(nodo* raiz){
    if (esVacio(raiz)){
        return 0;
    } else if (eshoja(raiz)){
        return 1;
    } else {
        return contarHojas(raiz->hijoIzquierdo) + contarHojas(raiz->hijoDerecho);
    }
}

int alturaNodo(nodo* raiz){
    if (esVacio(raiz)){
        return -1;
    } else if (eshoja(raiz)){
        return 1;
    } else {
        int alturaIzq = alturaNodo(raiz->hijoIzquierdo);
        int alturaDer = alturaNodo(raiz->hijoDerecho);
        if (alturaIzq > alturaDer){
            return alturaIzq + 1;
        } else {
            return alturaDer + 1;
        }
    }
}

int profunidadNodo(nodo* raiz){
    if (esVacio(raiz)){
        return 0;
    } else if (raiz->padre == NULL){
        return 1;
    } else {
        return profunidadNodo(raiz->padre) + 1;
    }
}

bool isBST(nodo* raiz){
    if (esVacio(raiz)){
        return true;
    } else if (eshoja(raiz)){
        return true;
    } else {
        if (raiz->hijoIzquierdo != NULL){
            if (raiz->dato < raiz->hijoIzquierdo->dato){
                return false;
            }
        }
        if (raiz->hijoDerecho != NULL){
            if (raiz->dato > raiz->hijoDerecho->dato){
                return false;
            }
        }
        return isBST(raiz->hijoIzquierdo) && isBST(raiz->hijoDerecho);
    }
}

void inorder(nodo* raiz){
    if (esVacio(raiz)){
        return;
    } else {
        inorder(raiz->hijoIzquierdo);
        printf("%d ", raiz->dato);
        inorder(raiz->hijoDerecho);
    }
}
void preorder(nodo* raiz){
    if (esVacio(raiz)){
        return;
    } else {
        printf("%d ", raiz->dato);
        preorder(raiz->hijoIzquierdo);
        preorder(raiz->hijoDerecho);
    }

}
void postorder(nodo* raiz){
    if (esVacio(raiz)){
        return;
    } else {
        postorder(raiz->hijoIzquierdo);
        postorder(raiz->hijoDerecho);
        printf("%d ", raiz->dato);
    }
}
nodo* invertBST(nodo* raiz){
    if (esVacio(raiz)){
        return;
    } else {
        nodo *left = invertBST(raiz->hijoIzquierdo);
        nodo *right = invertBST(raiz->hijoDerecho);
        raiz->hijoIzquierdo = right;
        raiz->hijoDerecho = left;
        return raiz;
    }
}

void invertBST2(nodo* raiz){
    if (esVacio(raiz)){
        return;
    } else {
        invertBST2(raiz->hijoIzquierdo);
        invertBST2(raiz->hijoDerecho);
        nodo *temp = raiz->hijoIzquierdo;
        raiz->hijoIzquierdo = raiz->hijoDerecho;
        raiz->hijoDerecho = temp;
    }
}
//----------------------create tree from preorder and inorder---------------------//
int preIndex = 0;
int buscaInorden(int inorden[], int inicio, int fin, int valor) {
    int i;
    for (i = inicio; i <= fin; i++) {
        if (inorden[i] == valor)
            break;
    }
    return i;
}
nodo* buildTree(int preorden[], int inorden[], int inStart, int inEnd) {
    if (inStart > inEnd) {
        return NULL;
    }
    nodo* raiz = crear_nodo(preorden[preIndex++]);
    if (inStart == inEnd) {
        return raiz;
    }
    int inIndex = buscaInorden(inorden, inStart, inEnd, raiz->dato);

    // subarboles izq y der
    raiz->hijoIzquierdo = buildTree(preorden, inorden, inStart, inIndex - 1);
    raiz->hijoDerecho = buildTree(preorden, inorden, inIndex + 1, inEnd);

    return raiz;
}
//-----------------------------------------------------------------//
int sumarHijos(nodo*raiz){
    if (esVacio(raiz)){
        return 0;
    } else {
        return raiz->dato + sumarHijos(raiz->hijoIzquierdo) + sumarHijos(raiz->hijoDerecho);
    }
}
void insertBST(nodo*raiz, int dato){
    if (esVacio(raiz)){
        raiz = crear_nodo(dato);
    }
    else{
        if (dato < raiz->hijoDerecho->dato){
            insertBST(raiz->hijoIzquierdo, dato);
        } else {
            insertBST(raiz->hijoDerecho, dato);
        }
    }
}
int obtener_peso(nodo*raiz){
    if (esVacio(raiz)){
        return 0;
    } else {
        return 1 + obtener_peso(raiz->hijoIzquierdo) + obtener_peso(raiz->hijoDerecho);
    }
}

int sumarHojas(nodo* raiz){
    if (esVacio(raiz)){
        return 0;
    } else if (eshoja(raiz)){
        return raiz->dato;
    } else {
        return sumarHojas(raiz->hijoIzquierdo) + sumarHojas(raiz->hijoDerecho);
    }
}

nodo *arbol_de_archivo(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    nodo *raiz = NULL;
    int dato;
    while (fscanf(archivo, "%d", &dato) != EOF){
        if (raiz == NULL){
            raiz = crear_raiz(dato);
        } else {
            insertar(raiz, dato);
        }
    }
    fclose(archivo);
    return raiz;
}
void fullNode(nodo*raiz){
    if(raiz == NULL) return;
    if(raiz->hijoIzquierdo != NULL && raiz->hijoDerecho != NULL){
        printf("%d ", raiz->dato);
    }
    fullNode(raiz->hijoIzquierdo);
    fullNode(raiz->hijoDerecho);
}
// dado un arbol binario, construya un algoritmo en pseudocódigo que retorne la suma de los elementos que sean multiplos de 3
int sumaMultiplos3(nodo*raiz){
    if(raiz == NULL) return 0;
    if(raiz->dato % 3 == 0){
        return raiz->dato + sumaMultiplos3(raiz->hijoIzquierdo) + sumaMultiplos3(raiz->hijoDerecho);
    }
    return sumaMultiplos3(raiz->hijoIzquierdo) + sumaMultiplos3(raiz->hijoDerecho);
}
//ahora un ABO
int sumaMultiplos3ABO(nodo*raiz){
    if(raiz == NULL) return 0;
    if(raiz->dato % 3 == 0){
        return raiz->dato + sumaMultiplos3(raiz->hijoIzquierdo) + sumaMultiplos3(raiz->hijoDerecho);
    }
    if(raiz->dato % 3 > 0){
        return sumaMultiplos3(raiz->hijoIzquierdo) + sumaMultiplos3(raiz->hijoDerecho);
    }
    return sumaMultiplos3(raiz->hijoIzquierdo) + sumaMultiplos3(raiz->hijoDerecho);
}

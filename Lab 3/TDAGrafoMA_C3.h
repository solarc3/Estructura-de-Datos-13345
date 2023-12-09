#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>


/*------------- estructura de datos -------------*/

typedef struct matrizGrafo{
	int n; 						//cantidad de vertices
	int m; 						//cantidad de aristas
	int **MAdy; 				//matriz con adyacencias
} TDAgrafoC3;


/*----------------- operaciones -----------------*/

TDAgrafoC3* crearGrafoVacioC3(int vertices) 
{
	TDAgrafoC3* grafo = (TDAgrafoC3*)malloc(sizeof(TDAgrafoC3));
	grafo->n= vertices;
	grafo->m= 0;
	grafo->MAdy = (int**)malloc(vertices * sizeof(int*));
	int i,j;
	for (i = 0; i < vertices; i++) 
	{
		grafo->MAdy[i] = (int*)malloc(vertices * sizeof(int));
		//Inicializa en cero
		for(j=0;j<vertices;j++){
			grafo->MAdy[i][j] = 0;
		}	
	}
	return grafo;
}


void mostrar_grafoC3(TDAgrafoC3* grafo) 
{
	int i, j;

	printf("\n\nGrafo:\n");

	for (i = 0; i < grafo->n; i++) 
	{
		for (j = 0; j < grafo->n; j++) 
		{
			printf("%d ", grafo->MAdy[i][j]);
		}
		printf("\n");
	}
}

void agregar_aristaNDC3(TDAgrafoC3 * grafo, int vertA, int vertB)
{
	grafo->MAdy[vertA][vertB] = 1;
	grafo->MAdy[vertB][vertA] = 1;
	grafo->m=grafo->m+1;
}

//NoDirigido NoPonderado
TDAgrafoC3 *leerGrafoNoDirigidoC3(char *nombreArchivo){
	
	TDAgrafoC3 *G;
	FILE*pf;		   //para abrir archivo
	int n_vertices, m_aristas;
	int i,j,k;
	
	
	pf = fopen(nombreArchivo,"r");

	if (pf==NULL){
		printf("Error de archivo\n");
		return NULL;
	}else{
	//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		

		//Crear grafo con n_vertices
		G=crearGrafoVacioC3(n_vertices);
		//dependiendo de las lineas de archivo
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d",&i, &j);
			agregar_aristaNDC3(G,i,j);
		}
		fclose(pf);
	}
	
	return G;
}


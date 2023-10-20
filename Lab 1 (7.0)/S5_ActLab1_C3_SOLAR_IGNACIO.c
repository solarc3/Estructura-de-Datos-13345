#include <stdio.h>
#include <stdlib.h>

//struct de almacenamiento
typedef struct{
	char nombre[50];
	int year;
	int city;
}Persona;

Persona personas[1000];
int people_count = 0; //aunque tengamos size, se lee para saber y utilizarlo globalmente


int contar_adultos(){
	int contador = 0;
	for(int i =0; i < people_count;i++){
		// si es que la persona es mayor a 18 se lee
		if( 2023 - personas[i].year >18){
			contador++;
			}
		}
	return contador;
}
void remover_menoresedad(){
	int j = 0;
	for (int i = 0; i < people_count; i++) {
        if (2023 - personas[i].year >= 18) {
            personas[j] = personas[i]; //sobreescribimos posicion para eliminar y no tener q poner un 0 para cambiar
            j++;
        }
    }
    people_count = j;
}
int promedio_ciudades(){
	int sum = 0;
	for (int i = 0; i < people_count; i++){
		sum += personas[i].city;
		}
	return sum / people_count;
	}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("uso: %s <archivo_ingreso> <archivo_salida>\n", argv[0]);
        return -1;}
    printf("Archivo de entrada: %s\n", argv[1]);
    printf("Archivo de salida: %s\n", argv[2]); //problema 1
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("error de entrada de archivo");
        return -1;
    }
    // leemos size para que el struct no lea el 13
    int size;
    fscanf(file, "%d", &size); //primer valor para saber el tamaño
    // guardamos informacion en struct, Problema 4
	while (fscanf(file, "%s %d %d", personas[people_count].nombre, &personas[people_count].year, &personas[people_count].city) != EOF) {
        people_count++;
    }
    fclose(file); // se cierra archivo

    // imprimimos todo, Problema 2
    printf("%d \n", people_count);
    for (int i = 0; i < size; i++){
		printf("%s %d %d \n", personas[i].nombre, personas[i].year, personas[i].city);
	}
	printf("cantidad de adultos en el archivo %d \n", contar_adultos()); 
	printf("promedio de cuidades %d\n", promedio_ciudades());
	remover_menoresedad();
	// problema 5
	// formato de salida 
	FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("error al abrir el archivo de salida");
        return -1;
    }
    //chao menores de edad
    printf("###############\n");
    printf("Archivo sin menores de edad \n");
    printf("%d \n", people_count);
    for (int i = 0; i < size; i++){
		printf("%s %d %d \n", personas[i].nombre, personas[i].year, personas[i].city);
	}
    // ya que pide el mismo formato de salida, se agrega primero la cantidad de elementos, que ya fue actualizado en la 
    // funcion de eliminar menores asi que es llegar y agregar
    fprintf(output,"%d \n", people_count);
    for (int i = 0; i < people_count; i++) {
        fprintf(output, "%s %d %d\n", personas[i].nombre, personas[i].year, personas[i].city);
    }
    fclose(output); //se cierra file
    return 0;
}

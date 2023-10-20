#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombre[50];
    int year;
    int city;
} Persona;

int contar_adultos(Persona* personas, int people_count) {
    int contador = 0;
    for (int i = 0; i < people_count; i++) {
        if (2023 - personas[i].year > 18) {
            contador++;
        }
    }
    return contador;
}

void remover_menoresedad(Persona* personas, int* people_count) {
    int j = 0;
    for (int i = 0; i < *people_count; i++) {
        if (2023 - personas[i].year >= 18) {
            personas[j] = personas[i];
            j++;
        }
    }
    *people_count = j;
}

int promedio_ciudades(Persona* personas, int people_count) {
    int sum = 0;
    for (int i = 0; i < people_count; i++) {
        sum += personas[i].city;
    }
    return sum / people_count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("uso: %s <archivo_ingreso> <archivo_salida>\n", argv[0]);
        return -1;
    }

    Persona* personas = NULL;
    int people_count = 0;

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("error de entrada de archivo");
        return -1;
    }
    
    int size;
    fscanf(file, "%d", &size);

    personas = malloc(size * sizeof(Persona));
    if (personas == NULL) {
        printf("Error allocating memory.\n");
        fclose(file);
        return -1;
    }

    while (fscanf(file, "%s %d %d", personas[people_count].nombre, &personas[people_count].year, &personas[people_count].city) != EOF) {
        people_count++;
    }
    fclose(file);

    printf("%d \n", people_count);
    for (int i = 0; i < size; i++) {
        printf("%s %d %d \n", personas[i].nombre, personas[i].year, personas[i].city);
    }
    printf("cantidad de adultos en el archivo %d \n", contar_adultos(personas, people_count)); 
    printf("promedio de ciudades %d\n", promedio_ciudades(personas, people_count));
    remover_menoresedad(personas, &people_count);

    printf("###############\n");
    printf("Archivo sin menores de edad \n");
    printf("%d \n", people_count);
    for (int i = 0; i < people_count; i++) {
        printf("%s %d %d \n", personas[i].nombre, personas[i].year, personas[i].city);
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("error al abrir el archivo de salida");
        free(personas);
        return -1;
    }

    fprintf(output, "%d \n", people_count);
    for (int i = 0; i < people_count; i++) {
        fprintf(output, "%s %d %d\n", personas[i].nombre, personas[i].year, personas[i].city);
    }
    fclose(output);

    free(personas);
    return 0;
}

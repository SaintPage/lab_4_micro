/*
* ------------------------------------------------------------
* dp_ompco.c
* dot product with omp leaf strategy and cut-off limit
* -------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Programación de Microprocesadores
*
* Introducción OpenMP
* Descripción: Este código utiliza OpenMp para lograr paralelizar la inicialiazción de un array "X" y otro
* array "y" con números pares usando la fórmula y= 1/2 a + x^2, donde el usuario escoge el número de hilos
*que desea ejecutar el programa, mostrando en pantalla los resultados en dos columnas "x" y "y"
* Autor:	  Ángel de Jesús Mérida 
* Fecha:	   Agosto 19, 2024.
* -------------------------------------------------------------
*/

#include <stdio.h>
#include <omp.h>
#include <math.h>

int main() {
    int num_hilos;
    
    // Pedir al usuario que indique el número de hilos
    printf("Indique el numero de hilos (8, 16 o 32): ");
    scanf("%d", &num_hilos);

    // Verificar que el número de hilos sea 8, 16 o 32
    if (num_hilos != 8 && num_hilos != 16 && num_hilos != 32) {
        printf("Numero de hilos invalido. Solo se permiten 8, 16 o 32.\n");
        return 1;
    }

    int x[num_hilos];
    double y[num_hilos];
    int a = 5;

    // Rellenar el array 'x' con números pares a partir de 2
    #pragma omp parallel for num_threads(num_hilos)
    for (int i = 0; i < num_hilos; i++) {
        x[i] = 2 * (i + 1);
    }

    // Calcular el valor de 'y' para cada elemento de 'x'
    #pragma omp parallel for num_threads(num_hilos)
    for (int i = 0; i < num_hilos; i++) {
        y[i] = (0.5) * a + pow(x[i], 2);
    }

    // Imprimir los resultados en una tabla
    printf("\nTabla de resultados:\n");
    printf("|   x   |     y     |\n");
    printf("|-------|-----------|\n");
    for (int i = 0; i < num_hilos; i++) {
        printf("|  %3d  | %9.2f |\n", x[i], y[i]);
    }

    return 0;
}

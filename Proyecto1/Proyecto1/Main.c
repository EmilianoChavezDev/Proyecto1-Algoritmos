#include <stdio.h>
#include "pq.h"

int main() {
    // Crear la cola de prioridad
    PQ* pq = pq_create();

    // Agregar algunos elementos a la cola de prioridad
    int valor1 = 10;
    int valor2 = 20;
    int valor3 = 5;
    int valor4 = 15;

    pq_add(pq, &valor1, 2);
    pq_add(pq, &valor2, 4);
    pq_add(pq, &valor3, 1);
    pq_add(pq, &valor4, 3);

    // Imprimir la lista de elementos en la cola de prioridad
    printf("Lista de elementos en la cola de prioridad:\n");
    imprimir_lista(pq);
    printf("\n");

    // Sacar el valor de menor prioridad de la cola de prioridad
    void* retVal;
    pq_remove(pq, &retVal);
    printf("Valor removido de la cola de prioridad: %d\n", *(int*)retVal);

    // Imprimir la lista de elementos en la cola de prioridad después de la eliminación
    printf("\nLista de elementos en la cola de prioridad después de la eliminación:\n");
    imprimir_lista(pq);
    printf("\n");


    leer_archivo("test1.txt", pq);

    // Destruir la cola de prioridad
    pq_destroy(pq);

    return 0;
}

#include <stdio.h>
#include "pq.h"

int main() {
    // Crear la cola de prioridad
    PQ* pq = pq_create();


    leer_archivo("test1.txt", pq);

    imprimir_lista(pq);
    printf("\n");


    return 0;
}

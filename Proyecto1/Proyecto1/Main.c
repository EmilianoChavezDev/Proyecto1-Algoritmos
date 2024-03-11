#include <stdio.h>
#include "pq.h"

int main() {
    PQ* pq = pq_create();


    leer_archivo("test1.txt", pq);

    imprimir_lista(pq);
    printf("\n");


    printf_s("Nueva lista\n");
    void* retVal = NULL;
    pq_remove(pq, &retVal);

    pq_remove(pq, &retVal);

    pq_remove(pq, &retVal);

    imprimir_lista(pq);


    return 0;
}

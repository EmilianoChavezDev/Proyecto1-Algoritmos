#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main() {
    PQ* pq = pq_create();

    // Leer y mostrar el contenido de un archivo de texto
    read_txt("test1.txt", pq);

    print_list(pq);


    //printf_s("%d \n", pq_size(pq));

    return 0;
}

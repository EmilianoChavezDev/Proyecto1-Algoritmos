#include "pq.h"
#include <stdlib.h>
#include <stdio.h>


/* Crea la cola de prioridad PQ e inicializa sus atributos
retorna un puntero a la cola de prioridad 
retorna NULL si hubo error*/
PQ pq_create() {
	 PQ pq = (PQ)malloc(sizeof(PQ));
	 confirmNotNull(pq, "Error al crear la cola de prioridad")
	 pq->cap = 10;
	 pq->size = 0;
	 pq->arr = (void*)malloc(sizeof(void*) * pq->cap);
	return pq;
}

/*
Agrega un valor a la cola con la prioridad dada

retorna TRUE si tuvo exito, FALSE si no
*/
BOOLEAN pq_add(PQ pq, void* valor, int prioridad) {
	confirmNotNull(pq, "Error al obtener el valor de la cola de prioridad");
	confirmNotNull(valor, "Error al obtener el valor");

	if (pq->size == pq->cap - 1) {
		redimensionar(pq);
	}

	PrioValue pv = value_create(valor, prioridad);
	pq->size++;
	pq->arr[pq->size] = pv;
	return TRUE;
}

/* 
  Saca el valor de menor prioridad (cima del monticulo) y lo guarda en la posicion retVal (paso por referencia)
  retorna FALSE si tiene un error
  retorna TRUE si tuvo EXITO
*/
BOOLEAN pq_remove(PQ pq, void** retVal) {
	confirmNotNull(pq, "Error al obtener el valor de la cola de prioridad");
	confirmNotNull(retVal, "Error al obtener el valor");
	*retVal = pq->arr[1]->value;
	pq->arr[1] = pq->arr[pq->size]->value;
	pq->size--;
   return TRUE;
}

/* retorna el tamaño de la cola de prioridad, 
   retorna 0 si hubo error 
 */
int pq_size(PQ pq) {
	confirmNotNull(pq, "Error al obtener el tamanho");
	return pq->size;
}

/* Destruye la cola de prioridad, 
retorna TRUE si tuvo exito
retorna FALSE si tuvo error*/
BOOLEAN pq_destroy(PQ pq) {
	confirmNotNull(pq, "Error al intentar destruir la cola de prioridad");
	free(pq->arr);
	free(pq);
	return TRUE;
}


/*Funciones implementadas*/

/*Crea el contorno prioValue*/
PrioValue value_create(void* value, int prioridad) {
	confirmNotNull(value, "Error al obtener el valor");
	PrioValue prioValue = (PrioValue)malloc(sizeof(PrioValue));
	confirmNotNull(prioValue, "Error al crear el contenedor prioValue");
	prioValue->prio = prioridad;
	prioValue->value = value;
	return prioValue;
}


/* Imprime los valores de la lista*/
BOOLEAN print_list(PQ pq) {
	confirmNotNull(pq, "Error la lista de prioridad esta vacia");
	for (int i = 1; i < pq->size; i++) {
		printf("%s", pq->arr[i]->value);
	}
	return TRUE;
}

void read_txt(char* archivo, PQ pq) {
	FILE* f = fopen(archivo, "r");

	int i = 0;

	while (1) {
		char c = fgetc(f);
		if (feof(f)) {
			break;
		}



		//recorrer el archivo, ver cuantas veces se repite
		//ese es su prioridad
		pq_add(pq, c, i);
		i++;

	}
	fclose(f);


}



BOOLEAN redimensionar(PQ pq) {
	confirmNotNull(pq, "Error al intentar acceder al arreglo");
	PQ aux = pq_create();
	aux->cap = pq->cap * 2;
	aux->arr = (void*)malloc(sizeof(void*) * aux->cap);


	for (int i = 1; i < pq->cap; i++) {
		aux->arr[i] = pq->arr[i];

	}

	free(aux->arr);
	pq->arr = aux->arr;
	pq->cap = aux->cap;

	return TRUE;

}
#include "pq.h"
#include <stdlib.h>
#include <math.h> 
#include <stdio.h>
#include <string.h>



/* Crea la cola de prioridad PQ e inicializa sus atributos
retorna un puntero a la cola de prioridad
retorna NULL si hubo error*/
PQ* pq_create() {
	PQ* pq = (PQ*)malloc(sizeof(struct Heap));
	confirmNotNull(pq, "Error al crear la cola de prioridad");
	pq->cap = 2;
	pq->size = 1;
	pq->arr = (void*)malloc(sizeof(void*) * pq->cap);
	return pq;
}

/*
Agrega un valor a la cola con la prioridad dada

retorna TRUE si tuvo exito, FALSE si no
*/
BOOLEAN pq_add(PQ* pq, void* valor, int prioridad) {
	confirmNotNull(pq, "Error al obtener el valor de la cola de prioridad");
	confirmNotNull(valor, "Error al obtener el valor");

	if (pq->size - 1 >= pq->cap) {
		redimensionar(pq);
	}

	PrioValue pv = value_create(valor, prioridad);


	pq->arr[pq->size] = pv;
	pq->size++;

	propagarArriba(pq, pq->size - 1);

	return TRUE;
}

/*
  Saca el valor de menor prioridad (cima del monticulo) y lo guarda en la posicion retVal (paso por referencia)
  retorna FALSE si tiene un error
  retorna TRUE si tuvo EXITO
*/
BOOLEAN pq_remove(PQ* pq, void** retVal) {
	confirmNotNull(pq, "Error al obtener el valor de la cola de prioridad");

	if (pq->size == 1) {
		return FALSE;
	}
	*retVal = pq->arr[1]->value;// guarda el valor 

	pq->arr[1] = pq->arr[pq->size - 1];
	pq->size--;

	propagarAbajo(pq, 1);

	return TRUE;
}

/* retorna el tamaño de la cola de prioridad,
   retorna 0 si hubo error
 */
int pq_size(PQ* pq) {
	confirmNotNull(pq, "Error al obtener el tamanho");
	return pq->size - 1;
}

/* Destruye la cola de prioridad,
retorna TRUE si tuvo exito
retorna FALSE si tuvo error*/
BOOLEAN pq_destroy(PQ* pq) {
	confirmNotNull(pq, "Error al intentar destruir la cola de prioridad");
	free(pq->arr);
	free(pq);
	return TRUE;
}



/*Funciones implementadas*/

/*Crea el contorno prioValue*/
PrioValue value_create(void* value, int prioridad) {
	confirmNotNull(value, "Error al obtener el valor");
	PrioValue prioValue = (PrioValue)malloc(sizeof(struct _PrioValue));
	confirmNotNull(prioValue, "Error al crear el contenedor prioValue");
	prioValue->prio = prioridad;
	prioValue->value = value;

	return prioValue;

}


BOOLEAN redimensionar(PQ* pq) {
	confirmNotNull(pq, "Error al obtener el arreglo");


	int capacidadNueva = (int)pq->cap * 2;
	PQ* aux = pq_create();
	aux->arr = (void*)malloc(sizeof(void*) * capacidadNueva);
	confirmNotNull(aux, "Error al crear el arreglo auxiliar");

	aux->cap = capacidadNueva;
	aux->size = pq->size;

	for (int i = 1; i <= pq->size; i++) {
		aux->arr[i] = pq->arr[i];
	}
	pq->arr = aux->arr;
	pq->cap = aux->cap;


	free(aux);
	return TRUE;
}


BOOLEAN imprimir_lista(PQ* pq) {
	for (int i = 1; i <= pq->size - 1; i++) {
		char caracter = pq->arr[i]->value;
		int prio = pq->arr[i]->prio;
		printf_s("%c , %i \n", caracter, prio);
	}
	return TRUE;
}

void leer_archivo(char* archivo, PQ* pq) {
	FILE* f = fopen(archivo, "r");
	confirmNotNull(archivo, "Error al obtener el archivo");

	//Arreglo para los caracteres ASCII
	int contador[128] = { 0 };
	char c;


	//Incrementar el contador en la posicion ASCII  del caracter
	do {

		c = fgetc(f);

		//Mientras el archivo siga abierto
		if (c != EOF) contador[(int)c]++;
	} while (!feof(f));



	//Agrego a la lista de prioridad
	for (int i = 0; i < 128; i++) {
		if (contador[i] > 0) pq_add(pq, (char)i, contador[i]);// Agrego el valor del caracter tanto las veces que se repite dentro del archivo

	}

	fclose(f);
}

BOOLEAN propagarArriba(PQ* pq, int index) {
	confirmNotNull(pq, "Error al obtener el arreglo");
	int padre = round((double)index / 2);

	if (padre == 1 && index == 1) {
		return TRUE;
	}



	if (pq->arr[padre]->prio > pq->arr[index]->prio) {
		PrioValue aux = pq->arr[padre];
		pq->arr[padre] = pq->arr[index];
		pq->arr[index] = aux;


		propagarArriba(pq, padre);
	}

}


BOOLEAN propagarAbajo(PQ* pq, int index) {
	int hijoDerecho = (2 * index) + 1;
	int hijoIzquierdo = 2 * index;
	int padre = index;


	if (hijoIzquierdo <= pq->size - 1 && pq->arr[hijoIzquierdo]->prio < pq->arr[padre]->prio) {
		PrioValue aux = pq->arr[padre];
		pq->arr[padre] = pq->arr[hijoIzquierdo];
		pq->arr[hijoIzquierdo] = aux;
		propagarAbajo(pq, hijoIzquierdo);
	}

	if (hijoDerecho <= pq->size - 1 && pq->arr[hijoDerecho]->prio < pq->arr[padre]->prio) {
		PrioValue aux = pq->arr[padre];
		pq->arr[padre] = pq->arr[hijoDerecho];
		pq->arr[hijoDerecho] = aux;
		propagarAbajo(pq, hijoDerecho);
	}


	return TRUE;

}
#include "pq.h"
#include <stdlib.h>
#include <math.h> 
#include <stdio.h>



/* Crea la cola de prioridad PQ e inicializa sus atributos
retorna un puntero a la cola de prioridad
retorna NULL si hubo error*/
PQ* pq_create() {
	PQ* pq = (PQ*)malloc(sizeof(struct Heap));
	confirmNotNull(pq, "Error al crear la cola de prioridad");
	pq->cap = 30;
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

	pq->arr[1] = pq->arr[pq->size-1];
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


	int capacidadNueva = pq->cap * 2;
	PQ* aux = pq_create();
	aux->arr = (PQ*)malloc(sizeof(PQ*) * capacidadNueva);
	confirmNotNull(aux, "Error al crear el arreglo auxiliar");

	aux->cap = capacidadNueva;
	aux->size = pq->size;

	for (int i = 1; i <= pq->size; i++) {
		aux->arr[i] = pq->arr[i];
	}

	free(pq->arr);
	pq->arr = aux->arr;
	pq->cap = aux->cap;


	free(aux);
	return TRUE;
}


BOOLEAN imprimir_lista(PQ* pq) {
	for (int i = 1; i <= pq->size - 1; i++) {
		PrioValue pv = pq->arr[i];
		printf("Prioridad: %d, Valor: %d\n", pv->prio, *(int*)(pv->value));
	}

}

void leer_archivo(char* archivo, PQ* pq) {
	FILE* f = fopen(archivo, "r");

	int i = 0;

	while (1) {
		char c = fgetc(f);
		if (feof(f)) {
			break;
		}

		//printf_s("%c", c);

		//pq_add(pq, c, i);
		i++;

	}
	fclose(f);


}


void propagarArriba(PQ* pq, int index) {
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
	int hijoDerecho = 2 * index + 1;
	int hijoIzquierdo = 2 * index;
	int actual = index;
	//index se pasa como 1

	if (hijoIzquierdo <= pq->size - 1 && pq->arr[hijoIzquierdo]->prio < pq->arr[actual]->prio) {
		PrioValue aux = pq->arr[actual];
		pq->arr[actual] = pq->arr[hijoIzquierdo];
		pq->arr[hijoIzquierdo] = aux;
		actual = hijoIzquierdo;
		return propagarAbajo(pq, hijoIzquierdo);
	}

	if (hijoDerecho <= pq->size - 1 && pq->arr[hijoDerecho]->prio < pq->arr[index]->prio) {
		PrioValue aux = pq->arr[actual];
		pq->arr[actual] = pq->arr[hijoDerecho];
		pq->arr[hijoDerecho] = aux;
		actual = hijoDerecho;
		return propagarAbajo(pq, hijoDerecho);
	}


	return TRUE;

}
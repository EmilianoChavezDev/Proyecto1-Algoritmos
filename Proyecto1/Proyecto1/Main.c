#include <stdio.h>
#include "pq.h"

void main() {
	PQ* pq = pq_create();


	leer_archivo("test1.txt", pq);
	void* retVal = NULL;

	while (pq->size != 1)
	{
		pq_remove(pq, &retVal);
		PrioValue pv = retVal;
		printf("valor removido: %c -> prioridad: %i\n", pv->value, pv->prio);
	}



}

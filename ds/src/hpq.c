/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer: Yoav        		*
*								*
*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "hpq.h" /* it_t */
#include "heap.h" /* it_t */

struct pq
{
	heap_t *heap;
};

pq_t *PQCreate(pqpriority_f PriorityFunction)
{
	pq_t *pq = (pq_t *)malloc(sizeof(pq_t));
	if(NULL == pq)
	{
		return NULL;
	}
	
	pq->heap = HeapCreate(PriorityFunction);
	if(NULL == pq->heap)
	{
		free(pq);
		return NULL;
	}
	
	return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapDestroy(pq->heap);

	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);

	return HeapPush(pq->heap, data);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->heap);
}

int PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	HeapPop(pq->heap);
	
	return 0;
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->heap);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->heap);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

int PQErase(pq_t *pq, const void *key, pqcmp_f ShouldErase)
{
	assert(NULL != pq);
	
	return HeapRemove(pq->heap, ShouldErase, key);
}

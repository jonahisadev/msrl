#ifndef MSRL_MEM_H
#define MSRL_MEM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct MSRLMemNode MSRLMemNode;

struct MSRLMemNode {
	MSRLMemNode* prev;
	MSRLMemNode* next;
	void* start;
	int size;
};

typedef struct MSRLMemPool {
	void* memory;
	// MSRLMemNodeList* blocks;
	MSRLMemNode* head;
} MSRLMemPool;

MSRLMemNode* msrl_mem_node_new(
	MSRLMemNode* prev,
	MSRLMemNode* next,
	void* start,
	int size
);

MSRLMemPool* msrl_pool(int size);
void* msrl_alloc(MSRLMemPool* pool, int size);
void msrl_free(MSRLMemPool* pool, void* ptr);
void msrl_pool_free(MSRLMemPool* pool);

//
//
//	IMPLEMENTATION
//
//

//
//	MemNode
//

MSRLMemNode* msrl_mem_node_new(
	MSRLMemNode* prev,
	MSRLMemNode* next,
	void* start,
	int size)
{
	MSRLMemNode* node = (MSRLMemNode*) malloc(sizeof(MSRLMemNode));
	node->prev = prev;
	node->next = next;
	node->start = start;
	node->size = size;
	return node;
}

//
//	MemPool
//

MSRLMemPool* msrl_pool(int size) {
	MSRLMemPool* pool = (MSRLMemPool*) malloc(sizeof(MSRLMemPool));
	pool->memory = (void*) malloc(size);
	// pool->blocks = msrl_mem_node_list_new(1);
	// msrl_mem_node_list_add(pool->blocks, msrl_mem_node_new(NULL, NULL, &pool->memory, 0));
	pool->head = msrl_mem_node_new(NULL, NULL, &pool->memory, 0);
	return pool;
}

void* msrl_alloc(MSRLMemPool* pool, int size) {
	if (size == 0) return NULL;

	if (pool->head->next == NULL) {
		// printf("first allocation\n");
		MSRLMemNode* node = msrl_mem_node_new(pool->head, NULL, pool->head->start, size);
		pool->head->next = node;
		return pool->head->start;
	} else {
		MSRLMemNode* h = pool->head->next;
		while (h->next != NULL) {
			if (h->next->start - (h->start + h->size) >= size) {
				// printf("we have space in the middle\n");
				MSRLMemNode* n = msrl_mem_node_new(h, h->next, h->start + h->size, size);
				h->next->prev = n;
				h->next = n;
				return n->start;
			}
			h = h->next;
		}
		// printf("we don't have space in the middle\n");
		MSRLMemNode* n = msrl_mem_node_new(h, NULL, h->start + h->size, size);
		h->next = n;
		return n->start;
	}

	return NULL;
}

void msrl_free(MSRLMemPool* pool, void* ptr) {
	MSRLMemNode* n = pool->head;
	while (n->next != NULL) {
		if (n->start == ptr) {
			n->prev->next = n->next;
			n->next->prev = n->prev;
			// printf("freed %p successfully\n", ptr);
			return;
		}
		n = n->next;
	}
	fprintf(stderr, "Can not free address %p\n", ptr);
}

void msrl_pool_free(MSRLMemPool* pool) {
	// Free pool memory
	free(pool->memory);

	// Free each node
	MSRLMemNode* n = pool->head;
	MSRLMemNode* temp = NULL;
	while (n->next != NULL) {
		temp = n->next;
		free(n);
		n = temp;
	}

	// Free pool struct
	free(pool);
}

#endif // MSRL_MEM_H
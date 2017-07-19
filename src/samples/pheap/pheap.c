#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libpmemobj.h>

#define PATH "pheap_file"

#define	HEAP_SIZE 1048576

struct pheap {
	int freespace;				// free heap space (in bytes)
	void *base_address;
	// FIXME: can pmemobj_open be forced to map always to the same base address?
	void *next_free;			// pointer to next free allocation space
	char data[HEAP_SIZE];		// heap contents
};

POBJ_LAYOUT_BEGIN(pheap_layout);
POBJ_LAYOUT_ROOT(pheap_layout, struct pheap);
POBJ_LAYOUT_END(pheap_layout);

static PMEMobjpool *pop;	// PMEM object pool
static PMEMoid root;		// root PMEMoid
static struct pheap *pheap;		// root direct pointer

/*
 * allocation function
 */
void* ph_malloc(int len) {
	void* ret_addr;
	TX_BEGIN(pop) {
		ret_addr = pheap->next_free;
		pheap->next_free += len;
		pmemobj_tx_add_range_direct(pheap->next_free, sizeof(void*));
		pheap->freespace -= len;
		pmemobj_tx_add_range_direct(&pheap->freespace, sizeof(int));
		TX_MEMSET((char*)ret_addr, 0, len);
	} TX_END
	
	return ret_addr;
}

/*
 * Heap dump function
 */
int dump_heap() {
	printf("Base address: %p\n", pheap);
	printf("Free space: %d\n", pheap->freespace);
	printf("Next free: %p\n", pheap->next_free);
}

/*
 * Simple heap example, without ability to reuse free space or compaction.
 */
int main(int argc, char *argv[])
{
	int heap_size = HEAP_SIZE; 
	
	if(heap_size < PMEMOBJ_MIN_POOL)
		heap_size = PMEMOBJ_MIN_POOL;
	printf("1\n");
	
	if (access(PATH, F_OK) != 0) {
	printf("2\n");
		if ((pop = pmemobj_create(PATH, POBJ_LAYOUT_NAME(pheap_layout), heap_size, 0666)) == NULL) {
			printf("failed to create pool\n");
			return 1;
		}
		printf("3\n");
		root = pmemobj_root(pop, HEAP_SIZE);
		printf("3.1\n");
		pheap = (struct pheap*) pmemobj_direct(root);
		printf("3.2\n");
		pheap->freespace = HEAP_SIZE;
		printf("3.3\n");
		pheap->next_free = pheap->data;
		printf("4\n");
		
		pheap->base_address = pheap;

	} else {
		if ((pop = pmemobj_open(PATH, POBJ_LAYOUT_NAME(pheap_layout))) == NULL) {
			printf("failed to open pool\n");
			return 1;
		}
		printf("5\n");
		root = pmemobj_root(pop, HEAP_SIZE);
		pheap = (struct pheap*) pmemobj_direct(root);
		if(pheap->base_address != pheap)
			printf("base address are different\n");
		printf("6\n");
	}
	printf("7\n");
	// allocate example
	dump_heap();
	char* c1 = ph_malloc(12);
	dump_heap();
	char* c2 = ph_malloc(15);
	dump_heap();
	
	// clean up
	pmemobj_close(pop);
}


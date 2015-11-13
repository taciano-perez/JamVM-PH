// JaPHa Modification
#include "layout.h"

int initialiseRoot() {
    pop = pmemobj_create("SFB_LIST", POBJ_LAYOUT_NAME(SFB_LIST), PMEMOBJ_MIN_POOL, 0666);
    pop_heap = pmemobj_create("HEAP_POOL", POBJ_LAYOUT_NAME(HEAP_POOL), PMEMOBJ_MIN_POOL, 0666);
    if(pop == NULL) {
        pop = pmemobj_open("SFB_LIST", POBJ_LAYOUT_NAME(SFB_LIST));
        pop_heap = pmemobj_open("HEAP_POOL", POBJ_LAYOUT_NAME(HEAP_POOL));
        if(pop == NULL || pop_heap == NULL) {
        	perror("pmemobj_open");
            return FALSE;
        }
    }
    return TRUE;
}

void item_construct(PMEMobjpool *pop, void *ptr, void *ptr_2) {
	FBList *fb_l = ptr;
	FBEntry *fb_e = ptr_2;
	pmemobj_memcpy_persist(pop, fb_l->id, fb_e->id, strlen(fb_e->id) + 1);
	pmemobj_memcpy_persist(pop, &(fb_l->fb), &(fb_e->fb), sizeof(FieldBlock));
}
// End of modification

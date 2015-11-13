// JaPHa Modification
#include "jam.h"
#include <libpmemobj.h>

typedef struct root Root;
typedef struct fb_entry FBEntry;
typedef struct fb_list FBList;

POBJ_LAYOUT_BEGIN(HEAP_POOL);
POBJ_LAYOUT_END(HEAP_POOL);

POBJ_LAYOUT_BEGIN(SFB_LIST);
POBJ_LAYOUT_ROOT(SFB_LIST, Root);
POBJ_LAYOUT_TOID(SFB_LIST, FBList);
POBJ_LAYOUT_END(SFB_LIST);

TOID_DECLARE(Class, 0);

struct fb_entry {
	FieldBlock fb;
	char id[];
};

struct fb_list {
    FieldBlock fb;
    POBJ_LIST_ENTRY(FBList) items;
    char id[];
};

struct root {
	POBJ_LIST_HEAD(items, FBList) head;
};

PMEMobjpool *pop, *pop_heap;
TOID(Root) root;
PMEMmutex tx_mutex;
int tx_monitor, main_started, persistent;
//char *id;
//TOID(FBList) iter;
FBEntry *fb_e;

extern int initialiseRoot();
//extern void item_construct(PMEMobjpool *pop, void *ptr, void *ptr_2);
// End of modification

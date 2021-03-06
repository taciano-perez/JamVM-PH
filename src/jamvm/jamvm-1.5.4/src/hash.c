/*
 * Copyright (C) 2003, 2004, 2005, 2006, 2007
 * Robert Lougher <rob@jamvm.org.uk>.
 *
 * This file is part of JamVM.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <string.h>
#include <stdlib.h>
#include "jam.h"
#include "hash.h"

void lockHashTable0(HashTable *table, Thread *self) {
    if(!tryLockVMLock(table->lock, self)) {
        disableSuspend(self);
        lockVMLock(table->lock, self);
        enableSuspend(self);
    }
    fastDisableSuspend(self);
}

void unlockHashTable0(HashTable *table, Thread *self) {
    fastEnableSuspend(self);
    unlockVMLock(table->lock, self);
}

/* XXX NVM CHANGE 006.002 - Resize Hash */
void resizeHash(HashTable *table, int new_size, char* name , int create_file) {
	// FIXME: resize implementation is messed up --- need to rethink and refactor it
//	if (strcmp(HT_NAME_ZIP, name) != 0) {
		printf("WARNING: resizeHash on %s being invoked, if this is a persistent HT, there is trouble ahead.\n", name);
//	}
    /* XXX NVM CHANGE 005.001.011 - Resize Hash*/
    HashEntry *new_table = (HashEntry*)gcMemMalloc(sizeof(HashEntry)*new_size, name, create_file);
    int i;

    memset(new_table, 0, sizeof(HashEntry)*new_size);

    for(i = table->hash_size-1; i >= 0; i--) {
        void *ptr = table->hash_table[i].data;
        if(ptr != NULL) {
            int hash = table->hash_table[i].hash;
            int new_index = hash & (new_size - 1);

            while(new_table[new_index].data != NULL)
                new_index = (new_index+1) & (new_size - 1);

            new_table[new_index].hash = hash;
            new_table[new_index].data = ptr;
        }
    }

    gcMemFree(table->hash_table);
    table->hash_table = new_table;
    table->hash_size = new_size;
}

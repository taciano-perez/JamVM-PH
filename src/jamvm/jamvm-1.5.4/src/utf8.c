/*
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009
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
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "jam.h"
#include "hash.h"

#define HASHTABSZE 1<<10
#define HASH(ptr) utf8Hash(ptr)
#define COMPARE(ptr1, ptr2, hash1, hash2) (ptr1 == ptr2) || \
                  ((hash1 == hash2) && utf8Comp(ptr1, ptr2))
#define PREPARE(ptr) ptr
#define SCAVENGE(ptr) FALSE
#define FOUND(ptr1, ptr2) ptr2

HashTable *hash_table;
char *FILENAME_UTF8 = "utf8.ht";
char *SEP_UTF8 = "\n";
int persistent_heap_utf8 = FALSE;
int testing_mode_utf8 = FALSE;
FILE *hash_file_utf8;
int file_exists_utf8 = FALSE;


#define GET_UTF8_CHAR(ptr, c)                         \
{                                                     \
    int x = *ptr++;                                   \
    if(x & 0x80) {                                    \
        int y = *ptr++;                               \
        if(x & 0x20) {                                \
            int z = *ptr++;                           \
            c = ((x&0xf)<<12)+((y&0x3f)<<6)+(z&0x3f); \
        } else                                        \
            c = ((x&0x1f)<<6)+(y&0x3f);               \
    } else                                            \
        c = x;                                        \
}

int utf8Len(char *utf8) {
    int count;

    for(count = 0; *utf8; count++) {
        int x = *utf8;
        utf8 += (x & 0x80) ? ((x & 0x20) ? 3 : 2) : 1;
    }

    return count;
}

void convertUtf8(char *utf8, unsigned short *buff) {
    while(*utf8)
        GET_UTF8_CHAR(utf8, *buff++);
}

int utf8Hash(char *utf8) {
    int hash = 0;

    while(*utf8) {
        unsigned short c;
        GET_UTF8_CHAR(utf8, c);
        hash = hash * 37 + c;
    }

    return hash;
}

int utf8Comp(char *ptr, char *ptr2) {
    while(*ptr && *ptr2) {
        unsigned short c, c2;

        GET_UTF8_CHAR(ptr, c);
        GET_UTF8_CHAR(ptr2, c2);
        if(c != c2)
            return FALSE;
    }
    if(*ptr || *ptr2)
        return FALSE;

    return TRUE;
}

char *findHashedUtf8Persintent(char *string, int add_if_absent, int class_to_save){
	    char *interned = NULL;

	    findHashEntry((*hash_table), string, interned, FALSE, FALSE, FALSE);

	    if(interned != NULL){
	    	return interned;
	    }
	    unsigned short string_lenght = strlen(string) + 1;

		/* Add if absent, no scavenge, locked */
	    findHashEntry((*hash_table), string, interned, add_if_absent, FALSE, TRUE);
	    if(class_to_save){
	    	if(add_if_absent){
	    		fwrite(&string_lenght, sizeof(unsigned short), 1, hash_file_utf8);
	    		fwrite(string, sizeof(char), string_lenght, hash_file_utf8);
	    	}
	    }
	    return interned;
}

char *findHashedUtf8(char *string, int add_if_absent, int class_to_save) {
    char *interned = NULL;

    if(persistent_heap_utf8 == TRUE){
    	interned = findHashedUtf8Persintent(string, add_if_absent, class_to_save);
    }
    else{
    	/* Add if absent, no scavenge, locked */
    	findHashEntry((*hash_table), string, interned, add_if_absent, FALSE, TRUE);

    }

    return interned;
}

char *copyUtf8(char *string) {
    char *buff = strcpy(sysMalloc(strlen(string) + 1), string);
    char *found = findHashedUtf8(buff, TRUE, FALSE);

    if(found != buff)
        sysFree(buff);

    return found;
}

char *slash2dots(char *utf8) {
    int len = strlen(utf8);
    char *conv = sysMalloc(len+1);
    int i;

    for(i = 0; i <= len; i++)
        if(utf8[i] == '/')
            conv[i] = '.';
        else
            conv[i] = utf8[i];

    return conv;
}

char *slash2dots2buff(char *utf8, char *buff, int buff_len) {
    char *pntr = buff;

    while(*utf8 != '\0' && --buff_len) {
        char c = *utf8++;
        *pntr++ = c == '/' ? '.' : c;
    }

    *pntr = '\0';
    return buff;
}

void initialiseUtf8Persistent(){
	int countHashEntries = 0;

	if(access (FILENAME_UTF8, F_OK) != -1) {
		file_exists_utf8 = TRUE;
	}



	// Adding entries to hash table since file exists
	if(file_exists_utf8 == TRUE) {
		hash_file_utf8 = fopen (FILENAME_UTF8, "rb");
		if(hash_file_utf8 == NULL) {
			exit(EXIT_FAILURE);
		}
		size_t len = 0;


		unsigned short string_length = 0;
		len = fread(&string_length, sizeof(unsigned short), 1, hash_file_utf8);

		while (len == 1) {
			char *interned = NULL;
			char *to_add = (char*)calloc(1, string_length * sizeof(char));
			int count = fread(to_add, sizeof(char), string_length, hash_file_utf8);
			do {
				addHashEntry((*hash_table), to_add, interned);
				interned = NULL;
				findHashEntry((*hash_table), to_add, interned, FALSE, FALSE, TRUE);
			}while(interned == NULL);

			countHashEntries++;
			len = fread(&string_length, sizeof(unsigned short), 1, hash_file_utf8);

		}

	fclose(hash_file_utf8);
	}
	hash_file_utf8 = fopen (FILENAME_UTF8, "a+b");
	// Unit tests
	if(testing_mode_utf8) {
		log_test_results("initaliseUTF8_fileExists", file_exists_utf8);
		if(countHashEntries == hash_table->hash_count){
			log_test_results("initaliseUTF8_recoverUTF8", TRUE);
		} else {
			log_test_results("initaliseUTF8_recoverUTF8", FALSE);
		}
	}
	hash_file_utf8 = fopen (FILENAME_UTF8, "a+b");
}

void initialiseUtf8(InitArgs *args) {
    /* Init hash table, and create lock */
	hash_table = sysMalloc(sizeof(HashTable));
	initHashTable((*hash_table), HASHTABSZE, TRUE);

	if(args->persistent_heap){
		persistent_heap_utf8 = args->persistent_heap;
		testing_mode_utf8 = args->testing_mode;
		initialiseUtf8Persistent();
	}

}

#ifndef NO_JNI
/* Functions used by JNI */


int utf8CharLen(unsigned short *unicode, int len) {
    int count = 0;
    for(; len > 0; len--) {
        unsigned short c = *unicode++;
        count += c == 0 || c > 0x7f ? (c > 0x7ff ? 3 : 2) : 1;
    }

    return count;
}

char *unicode2Utf8(unsigned short *unicode, int len, char *utf8) {
    char *ptr = utf8;

    for(; len > 0; len--) {
        unsigned short c = *unicode++;
        if((c == 0) || (c > 0x7f)) {
            if(c > 0x7ff) {
                *ptr++ = (c >> 12) | 0xe0;
                *ptr++ = ((c >> 6) & 0x3f) | 0x80;
            } else
                *ptr++ = (c >> 6) | 0xc0;
            *ptr++ = (c&0x3f) | 0x80;
        } else
            *ptr++ = c;
    }

    *ptr = '\0';
    return utf8;
}
#endif

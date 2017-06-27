#ifndef __SYSY_LIB_H__
#define __SYSY_LIB_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <string.h>

#include "hash_table.h"


# define YASSERT(exp)                                                   \
    do {                                                                \
        if (!(exp)) {                                                   \
            printf("!!!!!!!!!!assert fail!!!!!!!!!!!!!!!\n");           \
            abort();                                                    \
        }                                                               \
    } while (0)



/* mem.c */

extern int ymalloc(void **ptr, size_t size);
extern int yrealloc(void **_ptr, size_t size, size_t newsize);
extern int yfree(void **ptr);

extern int ymalloc1(void **ptr, size_t size);
extern int yfree1(void **ptr);

/* hash.c */
extern uint32_t hash_str(const char *str);
extern uint32_t hash_mem(const void *mem, int size);

/* hash_table.c */
extern hashtable_t hash_create_table(int (*compare_func)(const void *, const void *),
                                             uint32_t (*key_func)(const void *), const char *name);
extern void *hash_table_find(hashtable_t, const void *comparator);
extern int hash_table_insert(hashtable_t, void *value, void *comparator,
                                     int overwrite);
extern int hash_table_remove(hashtable_t, const void *comparator, void **value);
extern int hash_iterate_table_entries(hashtable_t tab, int (*handler)(void *, void *),
                                               void *arg);
extern void hash_filter_table_entries(hashtable_t, int (*handler)(void *, void *),
                                              void *arg, void (*thunk)(void *));
extern void hash_destroy_table(hashtable_t, void (*thunk)(void *));
int hashtable_resize(hashtable_t t, int size);
int hashtable_size(hashtable_t t);

#endif

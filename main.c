#include <stdio.h>
#include <string.h>

#include "sysy_lib.h"
#include "hash_table.h"
#include "pool_proto.h"

static uint32_t __name_key(const void *args)
{
        return hash_str((char *)args);
}

static int __name_cmp(const void *v1, const void *v2)
{
        const entry_t *ent = (entry_t *)v1;

        printf("cmp %s %s\n", ent->name, (const char *)v2);

        return strcmp(ent->name, (const char *)v2);
}

static int __mkpool(struct __pool_proto *pool, const char *parent, const char *name)
{
        printf("\nmkpool -> p name : %s,\n parent : %s,\nname :%s\n", pool->name, parent, name);
        entry_t *ent;
        ent = hash_table_find(pool->name_tab, (void *)name);
        if(ent) {
                printf("exist\n");
                return -1;
        }

        ymalloc((void **)&ent, sizeof(*ent));
        ymalloc((void **)&ent->name, strlen(name) + 1);
        memcpy(ent->name, name, strlen(name) + 1);

        hash_table_insert(pool->name_tab, (void *)ent, ent->name, 0);

        return 0;
}

static int __rmpool(struct __pool_proto *pool, const char *name)
{
        return 0;
}

static int __lookup(struct __pool_proto *pool, const char *name)
{
        printf("\nlookup -> p name : %s,\nname :%s\n", pool->name, name);
        entry_t *ent;
        ent = hash_table_find(pool->name_tab, (void *)name);
        if(ent == NULL) {
                printf("not exist\n");
                return 0;
        }
        printf("ent %s\n", ent->name);
        return 0;
}

static int __listpool(struct __pool_proto *pool)
{
        return 0;
}

static int __mkvol(struct __pool_proto *pool, char *parent, const char *name)
{
        return 0;
}

static int __unlink(struct __pool_proto *pool, const char *name)
{
        return 0;
}


static int pool_init(pool_proto_t **_pool)
{
        int ret;
        pool_proto_t *pool;
        char name[MAX_NAME_LEN];

        ret = ymalloc((void **)&pool, sizeof(*pool));
        memset(pool, 0x0, sizeof(*pool));

        memset(name, 0, sizeof(name));
        sprintf(name, "dir name : %s", "td");

        sprintf(pool->name, "/");
        pool->name_tab = hash_create_table(__name_cmp, __name_key, name);
        pool->mkpool = __mkpool;
        pool->rmpool = __rmpool;
        pool->lookup = __lookup;
        pool->listpool = __listpool;
        pool->mkvol = __mkvol;
        pool->unlink = __unlink;

        *_pool = pool;

        return 0;
}

static int get_pool(pool_proto_t **pool)
{
        static pool_proto_t *p;

        if(p == NULL) { 
                pool_init(&p);
        } 

        *pool = p;

        return 0;
}

static int pool_mkpool(pool_proto_t *p, const char *parent, const char *name)
{
        p->mkpool(p, parent, name);
        return 0;
}

static int pool_lookup_pool(pool_proto_t *p, const char *name)
{
        p->lookup(p, name);
        return 0;
}

int main(int argc, char *argv[])
{
        pool_proto_t *p;
        get_pool(&p);
        pool_mkpool(p, "/", "pool0");
        pool_lookup_pool(p, "pool0");
        return 0;
}

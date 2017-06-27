#ifndef __POOL_PROTO_H__
#define __POOL_PROTO_H__


typedef struct {
        uint32_t loc;
        uint32_t idx;
} loc_t;


typedef struct {
        loc_t loc;
        char *name;
        int chkinfo;
} pool_proto_entry_t;

typedef pool_proto_entry_t entry_t;


typedef struct __pool_proto {
        char name[256];
        hashtable_t name_tab;

        int (*mkpool)(struct __pool_proto *, const char *parent, const char *name);

        int (*lookup)(struct __pool_proto *, const char *name);
        int (*listpool)(struct __pool_proto *);

        int (*mkvol)(struct __pool_proto *, char *parent, const char *name);
        int (*rmpool)(struct __pool_proto *, const char *name);
        int (*unlink)(struct __pool_proto *, const char *name);

} pool_proto_t;

#endif

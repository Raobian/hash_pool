
#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "sysy_lib.h"
#include "hash_table.h"

int ymalloc(void **_ptr, size_t size)
{
        int ret, i;
        void *ptr;

        if (size == 0) {
                *_ptr = NULL;
                return 0;
        }

        if (size > 4096)
                printf("big mem %u\n", (int)size);

        for (i = 0; i < 3; i++) {
                ptr = calloc(1, size);
                if (ptr != NULL)
                        goto out;
        }

        ret = ENOMEM;
        goto err_ret;

out:
        *_ptr = ptr;

        return 0;
err_ret:
        return ret;
}

int yrealloc(void **_ptr, size_t size, size_t newsize)
{
        int ret, i;
        void *ptr;

        if (*_ptr == NULL && size == 0) /*malloc*/ {
                ret = ymalloc(&ptr, newsize);
                if (ret)
                        goto err_ret;

                memset(ptr, 0x0, newsize);

                *_ptr = ptr;
                return 0;
        }

        if (newsize == 0)
                return yfree(_ptr);

        if (newsize < size) {
                ptr = *_ptr;
                memset(ptr + newsize, 0x0, size - newsize);
        }

        ret = ENOMEM;
        for (i = 0; i < 3; i++) {
                ptr = realloc(*_ptr, newsize);
                if (ptr != NULL)
                        goto out;
        }
        goto err_ret;

out:
        if (newsize > size)
                memset(ptr + size, 0x0, newsize - size);

        *_ptr = ptr;

        return 0;
err_ret:
        return ret;
}

int yfree(void **ptr)
{

        if (*ptr != NULL) {
                free(*ptr);
        } else {
                YASSERT(0);
        }

        *ptr = NULL;

        return 0;
}

#if 1
int ymalloc1(void **_ptr, size_t size)
{
        int ret, i;
        void *ptr;

        if (size == 0) {
                *_ptr = NULL;
                return 0;
        }

        if (size > 4096)
                printf("big mem %u\n", (int)size);

        for (i = 0; i < 3; i++) {
                ptr = calloc(1, size);
                if (ptr != NULL)
                        goto out;
        }

        ret = ENOMEM;
        goto err_ret;

out:
        *_ptr = ptr;

        return 0;
err_ret:
        return ret;
}

int yfree1(void **ptr)
{
        if (*ptr != NULL) {
                free(*ptr);
        } else  {
                YASSERT(0);
        }

        *ptr = NULL;

        return 0;
}
#endif


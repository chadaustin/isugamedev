
#include "zutil.h"

const char *z_errmsg[10] = {
"need dictionary",     /* Z_NEED_DICT       2  */
"stream end",          /* Z_STREAM_END      1  */
"",                    /* Z_OK              0  */
"file error",          /* Z_ERRNO         (-1) */
"stream error",        /* Z_STREAM_ERROR  (-2) */
"data error",          /* Z_DATA_ERROR    (-3) */
"insufficient memory", /* Z_MEM_ERROR     (-4) */
"buffer error",        /* Z_BUF_ERROR     (-5) */
"incompatible version",/* Z_VERSION_ERROR (-6) */
""};

#ifndef STDC
extern void*  calloc (unsigned int items, unsigned int size);
extern void   free   (void* ptr);
#endif

void* zcalloc (opaque, items, size)
    void* opaque;
    unsigned items;
    unsigned size;
{
    if (opaque) items += size - size; /* make compiler happy */
    return (void*)calloc(items, size);
}

void  zcfree (opaque, ptr)
    void* opaque;
    void* ptr;
{
    free(ptr);
    if (opaque) return; /* make compiler happy */
}


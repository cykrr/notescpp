#include "membuf.h"

void
membuf_init(struct membuf* buf, size_t new_asize)
{
    buf->size = 0;
    buf->asize = new_asize;
    buf->data = (char*)malloc(buf->asize);
    if(buf->data == NULL) {
        fprintf(stderr, "membuf_init: malloc() failed.\n");
        exit(1);
    }
}

void
membuf_fini(struct membuf* buf)
{
    if(buf->data)
        free(buf->data);
}

void
membuf_grow(struct membuf* buf, size_t new_asize)
{
    buf->data = (char*)realloc(buf->data, new_asize);
    if(buf->data == NULL) {
        fprintf(stderr, "membuf_grow: realloc() failed.\n");
        exit(1);
    }
    buf->asize = new_asize;
}

void
membuf_append(struct membuf* buf, const char* data, size_t size)
{
    if(buf->asize < buf->size + size)
        membuf_grow(buf, buf->size + buf->size / 2 + size);
    memcpy(buf->data + buf->size, data, size);
    buf->size += size;
}

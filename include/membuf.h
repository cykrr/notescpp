#ifndef membuf_h
#define membuf_h
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct membuf {
    char *data;
    size_t asize;
    size_t size;

} membuf;

void
membuf_init(struct membuf* buf, size_t new_asize);

void
membuf_fini(struct membuf* buf);

void
membuf_grow(struct membuf* buf, size_t new_asize);

void
membuf_append(struct membuf* buf, const char* data, size_t size);

#endif // !membuf_h

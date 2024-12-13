#ifndef HEAP_H_
#define HEAP_H_

#include<stdint.h>

#define HEAP_CAP_BYTES 64000

extern char heap[HEAP_CAP_BYTES];

#define CHUNK_CAP 1024

typedef struct {
    bool in_use;
    size_t size;
    char* ptr;
} Chunk;

typedef struct {
    size_t count;
    Chunk chunks[CHUNK_CAP];
} Chunk_List;

extern Chunk_List chunk_list;

void print_chunk_list(void);

void* heap_alloc(size_t size);
void heap_free(void* ptr);

void chunk_list_merge_unused(void);
void chunk_list_insert(void* ptr, size_t size, bool in_use);
int chunk_list_find(void* ptr);
void chunk_list_remove(size_t index);

#endif // HEAP_H_

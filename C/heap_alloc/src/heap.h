#ifndef HEAP_H_
#define HEAP_H_

#include<stdint.h>

#define HEAP_CAP_BYTES 64000
#define HEAP_CAP_WORDS (HEAP_CAP_BYTES / sizeof(uintptr_t))

extern uintptr_t heap[HEAP_CAP_WORDS];

#define CHUNK_CAP 1024

typedef struct {
    bool in_use;
    size_t size;
    uintptr_t* ptr;
} Chunk;

typedef struct {
    size_t count;
    Chunk chunks[CHUNK_CAP];
} Chunk_List;

extern Chunk_List chunk_list;

void print_chunk_list(void);

void* heap_alloc(size_t size);
void heap_free(void* ptr);

void chunk_list_insert(void* ptr, size_t size);
int chunk_list_find(uintptr_t* ptr);
void chunk_list_remove(size_t index);

#endif // HEAP_H_

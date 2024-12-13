#include <stdio.h>
#include <stdbool.h>
#include "heap.h"

#define btoa(b) (b ? "true" : "false")

uintptr_t heap[HEAP_CAP_WORDS] = {0};

Chunk_List chunk_list = {
    .count = 1,
    .chunks = {
        {
            .ptr = heap,
            .size = sizeof(heap),
            .in_use = false
        }
    }
};

void print_chunk_list(void) {
    printf("Chunk list: count=%zu\n", chunk_list.count);
    for (size_t i = 0; i < chunk_list.count; ++i) {
        printf("Chunk %zu: in_use=%s, size=%zu, ptr=%p\n", i, btoa(chunk_list.chunks[i].in_use), chunk_list.chunks[i].size, (void*)chunk_list.chunks[i].ptr);
    }
}

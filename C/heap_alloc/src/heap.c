#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "heap.h"

#define btoa(b) (b ? "true" : "false")

char heap[HEAP_CAP_BYTES] = {0};

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
        printf("- Chunk %2zu: in_use=%5s, size=%5zu, ptr=%p\n", i, btoa(chunk_list.chunks[i].in_use), chunk_list.chunks[i].size, (void*)chunk_list.chunks[i].ptr);
    }
}

void* heap_alloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    chunk_list_merge_unused();

    for (size_t i = 0; i < chunk_list.count; ++i) {
        Chunk* chunk = &chunk_list.chunks[i];
        if (chunk->in_use) {
            continue;
        }

        if (chunk->size < size) {
            continue;
        }

        chunk->in_use = true;
        const size_t tail_size = chunk->size - size;
        chunk->size = size;

        if (tail_size > 0) {
            chunk_list_insert(chunk->ptr + size, tail_size, false);
        }

        return chunk->ptr;
    }

    return NULL;
}

void heap_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    const int index = chunk_list_find(ptr);
    assert(index >= 0);
    assert(ptr == chunk_list.chunks[index].ptr);
    assert(chunk_list.chunks[index].in_use);
    chunk_list.chunks[index].in_use = false;
}

void chunk_list_merge_unused(void) {
    for (size_t i = 0; i < chunk_list.count - 1; ++i) {
        if (chunk_list.chunks[i].in_use) {
            continue;
        }
        if (chunk_list.chunks[i + 1].in_use) {
            continue;
        }
        chunk_list.chunks[i].size += chunk_list.chunks[i + 1].size;
        chunk_list_remove(i + 1);
        --i;
    }
}

void chunk_list_insert(void* ptr, size_t size, bool in_use) {
    assert(chunk_list.count < CHUNK_CAP);

    chunk_list.chunks[chunk_list.count].ptr = ptr;
    chunk_list.chunks[chunk_list.count].size = size;
    chunk_list.chunks[chunk_list.count].in_use = in_use;

    for (size_t i = chunk_list.count; i > 0 && chunk_list.chunks[i].ptr < chunk_list.chunks[i - 1].ptr; --i) {
            const Chunk tmp = chunk_list.chunks[i];
            chunk_list.chunks[i] = chunk_list.chunks[i - 1];
            chunk_list.chunks[i - 1] = tmp;
    }

    ++chunk_list.count;
}

int chunk_list_find(void* ptr) {
    for (size_t i = 0; i < chunk_list.count; ++i) {
        if (chunk_list.chunks[i].ptr == ptr) {
            return (int)i;
        }
    }

    return -1;
}

void chunk_list_remove(size_t index) {
    assert(index < chunk_list.count);

    for (size_t i = index; i < chunk_list.count - 1; ++i) {
        chunk_list.chunks[i] = chunk_list.chunks[i + 1];
    }

    --chunk_list.count;
}

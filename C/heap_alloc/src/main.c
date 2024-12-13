#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include "heap.h"

int main(void) {
    void* a = heap_alloc(1);
    void* b = heap_alloc(2);
    void* c = heap_alloc(3);
    print_chunk_list();

    heap_free(a);
    heap_free(b);
    heap_free(c);
    print_chunk_list();

    heap_alloc(4);
    
    print_chunk_list();
    return 0;
}

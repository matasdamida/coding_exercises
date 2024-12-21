# Custom C malloc exercise based on [tsoding's memalloc](https://github.com/tsoding/memalloc)

## Quick Start

### NMake + Clang

```console
> mkdir Release
> cd Release
> cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_BUILD_TYPE=Release ..
> make
> ./bin/heap_alloc.exe
```


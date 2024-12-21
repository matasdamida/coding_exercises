# Custom C++ vector

## Quick Start

### MinGW_Make + Clang

```console
> mkdir Release
> cd Release
> cmake -G "MinGW Makefiles" -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_BUILD_TYPE=Release ..
> make
> ./bin/vector.exe
```
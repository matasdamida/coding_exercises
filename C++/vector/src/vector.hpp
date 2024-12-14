#pragma once

#define VECTOR_STARTING_CAP 8
#define VECTOR_MULT 2

template<typename T>
class vector {
    T *data;
    size_t size;
    size_t capacity;

    size_t next_multiple_of(size_t n, size_t m);

public:
    vector();
    vector(size_t capacity);
    vector(T* data, size_t size);
    vector(const vector &other);
    ~vector();
    void push_back(T value);
    T pop_back();
    T& operator[](size_t index);
};

#include <algorithm>
#include <iterator>
#include <cassert>
#include "vector.hpp"

template<typename T>
size_t vector<T>::next_multiple_of(size_t n, size_t m) {
    return n * (m / (n + 1) + 1);
}

template<typename T>
vector<T>::vector() {
    data = new T[VECTOR_STARTING_CAP];
    size = 0;
    capacity = VECTOR_STARTING_CAP;
}

template<typename T>
vector<T>::vector(size_t capacity) {
    data = new T[capacity];
    size = 0;
    this->capacity = capacity;
}

template<typename T>
vector<T>::vector(T* data, size_t size) {
    this->data = data;
    this->size = size;
    this->capacity = vector::next_multiple_of(VECTOR_STARTING_CAP, size);
}

template<typename T>
vector<T>::vector(const vector &other) {
    data = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    std::copy(other.data, other.data + other.size, data);
}

template<typename T>
vector<T>::~vector() {
    delete[] data;
}

template<typename T>
void vector<T>::push_back(T value) {
    if (size == capacity) {
        capacity = next_multiple_of(VECTOR_STARTING_CAP, size + 1);
        T* newData = new T[capacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
    }
    data[size++] = value;
}

template<typename T>
T vector<T>::pop_back() {
    assert(size > 0);
    return data[--size];
}

template<typename T>
T& vector<T>::operator[](size_t index) {
    assert(index < size);
    return data[index];
}

#include "vector.inl"

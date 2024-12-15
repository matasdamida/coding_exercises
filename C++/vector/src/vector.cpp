#include <algorithm>
#include <iterator>
#include <cassert>
#include "vector.hpp"

template<typename T>
size_t vector<T>::next_multiple_of(size_t n, size_t m) {
    return n * (m / (n + 1) + 1);
}

template<typename T>
vector<T>::vector(): _data(new T[VECTOR_STARTING_CAP]), _size(0), _capacity(VECTOR_STARTING_CAP) {}

template<typename T>
vector<T>::vector(size_t capacity): _data(new T[capacity]), _size(0), _capacity(capacity) {}

template<typename T>
vector<T>::vector(T* data, size_t size): _data(data), _size(size), _capacity(vector::next_multiple_of(VECTOR_STARTING_CAP, size)) {}

template<typename T>
vector<T>::vector(const vector &other): _data(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
    std::copy(other._data, other._data + other._size, _data);
}

template<typename T>
vector<T>::~vector() {
    delete[] _data;
}

template<typename T>
void vector<T>::push_back(T value) {
    if (_size == _capacity) {
        _capacity = next_multiple_of(VECTOR_STARTING_CAP, _size + 1);
        T* newData = new T[_capacity];
        std::copy(_data, _data + _size, newData);
        delete[] _data;
        _data = newData;
    }
    _data[_size++] = value;
}

template<typename T>
T vector<T>::pop_back() {
    assert(_size > 0);
    return _data[--_size];
}

template<typename T>
T& vector<T>::operator[](size_t index) {
    assert(index < _size);
    return _data[index];
}

template<typename T>
size_t vector<T>::size() {
    return _size;
}

template<typename T>
size_t vector<T>::capacity() {
    return _capacity;
}

#include "vector.inl"

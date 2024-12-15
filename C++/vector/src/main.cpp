#include <iostream>
#include <cassert>
#include "vector.hpp"
#include "../../../C/lib/custom_testing.h"

int vector_test_starting_size_zero(void) {
    printf("test vector_test_starting_size_zero ... ");
    vector<int> v;
    assert_eq(v.size(), 0);
    return 0;
}

int vector_test_push_back(void) {
    printf("test vector_test_push_back ... ");
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    assert_eq(v.size(), 10);
    return 0;
}

int vector_test_pop_back(void) {
    printf("test vector_test_pop_back ... ");
    vector<int> v;
    const int length = 10;
    for (int i = 0; i < length; ++i) {
        v.push_back(i);
    }
    for (int i = length - 1; i >= 0; --i) {
        assert_eq(v.pop_back(), i);
    }
    assert_eq(v.size(), 0);
    return 0;
}

int main(void) {
    int (*tests[])(void) = {vector_test_starting_size_zero, vector_test_push_back, vector_test_pop_back};
    return test_all(tests, 3);
}

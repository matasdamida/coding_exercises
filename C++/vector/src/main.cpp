#include<iostream>
#include "vector.hpp"

int main(void) {
    vector v = vector<int>();

    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << v[i] << (i < 9 ? ", " : "");
    }
    std::cout << std::endl;

    return 0;
}
#pragma once
#include<stdio.h>
//#define assert_eq(a, b) ((void) ((a) == (b) || (printf("Assertion failed: %s:%d: %s == %s\n", __FILE__, __LINE__, #a, #b))))
#define assert_eq(a, b) { \
    if ((a) != (b)) { \
        printf("FAILED\n\tAssertion failed: %s:%d: %s == %s\n", __FILE__, __LINE__, #a, #b); \
        return 1; \
    } \
}

int test_all(int (*tests[])(void), size_t count) {
    printf("\nrunning %zu tests\n", count);
    int passed = 0, failed = 0;
    for (size_t i = 0; i < count; i++) {
        if (tests[i]() == 0) {
            passed += 1;
            printf("ok\n");
        } else {
            failed += 1;
        }
    }
    printf("\ntest result: %s. %d passed; %d failed;\n\n", (size_t)passed == count ? "ok" : "FAILED", passed, failed);
    return failed;
}

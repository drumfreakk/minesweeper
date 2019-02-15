#include <iostream>
#include "Field.h"

//TODO: add valgrind/memcheck


int main() {
    Field f(7, 7);

    f[4][3] = 3;

    f.setupField(5);

    std::cout << f;

    return 0;
}
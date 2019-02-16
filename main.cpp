#include <iostream>
#include "Field.h"


int main() {
    Field f(5, 5);

    f.setupField(3);

    std::cout << "\n\n\n" << f <<'\n';

    int xclick;
    int yclick;

    bool alive = true;

    while (alive) {

        std::cout << "\nx: ";
        std::cin >> xclick;
        std::cout << "\ny: ";
        std::cin >> yclick;

        alive = f.click(xclick, yclick);

        std::cout << f;
    }

    std::cout << "BOOM!\n";

    return 0;
}

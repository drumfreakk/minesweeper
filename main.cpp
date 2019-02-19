#include <iostream>
#include "Field.h"

//TODO: INPUT VALIDATION!!!

int main() {
	TermField f(5, 5);

	f.setupField(3);

	std::cout << "\n\n\n" << f <<'\n';

	int xclick;
	int yclick;

	char type;

	Return status = RETURN_ALIVE;

	while (status == RETURN_ALIVE) {
		do {
			std::cout << "\nclick/flag: ";
			std::cin >> type;

			std::cout << "\nx: ";
			std::cin >> xclick;
			std::cout << "\ny: ";
			std::cin >> yclick;

			status = f.click(xclick, yclick, type);

			std::cout << f;
		} while(status == RETURN_FALSE_CLICK);

	}

	if(status == RETURN_DEAD) {
		std::cout << "BOOM!\n";
	} else if(status == RETURN_WIN){
		std::cout << "\nYOU WIN!\n";
	}

	return 0;
}

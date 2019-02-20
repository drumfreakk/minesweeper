#include <iostream>
#include "Field.h"

int main() {
	TermField f(5, 5);

	f.setupField(3);

	std::cout << "\n\n\n" << f <<'\n';

	int x;
	int y;

	Click type;

	Return status = RETURN_ALIVE;

	while (status == RETURN_ALIVE) {
		do {
			type = f.getTypeInput();

			x = f.getPosInput(CLICK_X);
			y = f.getPosInput(CLICK_Y);

			status = f.click(x, y, type);

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

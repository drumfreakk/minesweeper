#include <iostream>
#include "../include/field.h"

int getInput(std::string msg){
	int out;

	while (1)
	{

		std::cout << msg;
		std::cin >> out;

		if (std::cin.fail()) // no extraction took place
		{
			std::cin.clear(); // reset the state bits back to goodbit so we can use ignore()
			std::cin.ignore(32767, '\n'); // clear out the bad input from the stream
			continue; // try again
		}

		std::cin.ignore(32767, '\n'); // clear out any additional input from the stream
		if (std::cin.gcount() > 1)
			continue;


		if(out < 1)
			continue;

		break;
	}

	return out;
}

int main() {

	int x = 7;//getInput("Field width: ");
	int y = 7;//getInput("Field height: ");
	int bombs = 3;//getInput("Amount of Bombs: ");

	TermField f(x, y);

	f.setSize(x -2, y -2);

	if(!f.setupField(bombs)){
		std::cerr << " Too many bombs!";
		return 0;
	}

	std::cout << "\n\n\n" << f << '\n';

	Click type;

	Return status = RETURN_ALIVE;

	while (status == RETURN_ALIVE) {
		do {
			type = f.getTypeInput();

			x = f.getPosInput(CLICK_X);
			y = f.getPosInput(CLICK_Y);

			status = f.click(x, y, type);

			std::cout << f;
		} while (status == RETURN_FALSE_CLICK);

	}

	if (status == RETURN_DEAD) {
		std::cout << "BOOM!\n";
	} else if (status == RETURN_WIN) {
		std::cout << "\nYOU WIN!\n";
	}
	return 0;
}



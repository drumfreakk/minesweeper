#include <iostream>
#include "libs/Field.h"

#define TERM

#ifdef SFML
int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	SFMLField map(5, 5);
	// run the main loop
	while (window.isOpen()) {
		// handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// draw the map
		window.clear();
		window.draw(map);
		window.display();
	}
	return 0;
}
#endif

#ifdef TERM

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


		if(out < 0)
			continue;

		break;
	}

	return out;
}

int main() {

	int x = getInput("Field width: ");
	int y = getInput("Field height: ");
	int bombs = getInput("Amount of Bombs: ");

	TermField f(y, x);

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

#endif

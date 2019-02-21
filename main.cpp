#include <iostream>
#include "libs/Field.h"

#define TERM

int main() {

#ifdef SFML

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


	SFMLField map(5, 5);

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// draw the map
		window.clear();
		window.draw(map);
		window.display();
	}

#endif

#ifdef TERM
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
#endif

	return 0;
}

#include <iostream>
#include "libs/Field.h"

#define SFML


#ifdef SFML

#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(700, 700), "Minesweeper");

	SFMLGame field;

	field.setSize(20, 20);
	field.setWindowSize(sf::Vector2f(50, 50), sf::Vector2f(650, 650));
	field.setupField(50);

	field.font.loadFromFile("/home/kip/CLionProjects/minesweeper/assets/bitcrusher.ttf");

	sf::Text& endText = field.endText;
	sf::Text& bombs = field.bombs;

	Return status = RETURN_ALIVE;

	bombs.setString(std::to_string(field.getBombsLeft()) + "/" + std::to_string(field.getBombs()));

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if(status == RETURN_ALIVE || status == RETURN_FALSE_CLICK || status == RETURN_ERROR) {
					if (event.mouseButton.button == sf::Mouse::Right) {
						status = field.click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y,
						                     CLICK_FLAG);
					}
					if (event.mouseButton.button == sf::Mouse::Left) {
						status = field.click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y,
						                     CLICK_CLICK);
					}
				}
				bombs.setString(std::to_string(field.getBombsLeft()) + "/" + std::to_string(field.getBombs()));
			}
		}


		if(status == RETURN_DEAD) {
			endText.setString("You Lose!");
		}
		if(status == RETURN_WIN){
			endText.setString("You Win!");
		}

		window.clear(field.defaultBackground());

		window.draw(field);
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

#endif


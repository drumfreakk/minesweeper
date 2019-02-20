#include "Field.h"

//TODO: INPUT VALIDATION!!!

BaseField::~BaseField() {
	for (int count = 0; count < m_height; ++count)
		delete[] m_field[count];
	delete[] m_field;
	m_field = nullptr;

	for (int count = 0; count < m_height; ++count)
		delete[] m_visibleField[count];
	delete[] m_visibleField;
	m_visibleField = nullptr;

	for (int count = 0; count < m_height; ++count)
		delete[] m_clicked[count];
	delete[] m_clicked;
	m_clicked = nullptr;
}

TermField::~TermField() {
	for (int count = 0; count < m_height; ++count)
		delete[] m_playerField[count];
	delete[] m_playerField;
	m_playerField = nullptr;
}

std::ostream& operator<< (std::ostream &out, TermField &field) {
	for(int y = 0; y < field.m_height; y++){
		for(int x = 0; x < field.m_width; x++){     //m_width
			out << '\t' << field.m_playerField[y][x];
		}
		out << "\n\n";
	}
	return out;
}

int* BaseField::operator[](const int row){
	return m_field[row];
}

void BaseField::setupField(const int bombs){

	BaseField::m_bombs = bombs;

	bool nuffbombs = false;
	int doneBombs = 0;

	while(!nuffbombs){
		int x = m_randXPos(m_rndgen);
		int y = m_randYPos(m_rndgen);

		if(m_field[y][x] != CODE_MINE) {

			m_field[y][x] = CODE_MINE;

			doneBombs += 1;
		}

		if(doneBombs >= m_bombs){
			nuffbombs = true;
		}

	}

	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			if(m_field[y][x] == CODE_MINE){

				for(int xb = x - 1; xb < x + 2; xb++){
					if(xb >= 0 && xb < m_width) {

						for (int yb = y - 1; yb < y + 2; yb++) {
							if(yb >= 0 && yb < m_height && m_field[yb][xb] != CODE_MINE) {

								m_field[yb][xb] += 1;
							}
						}
					}
				}
			}
		}
	}
}

Return BaseField::click(const int x, const int y, Click type){
	Return ret;
	if (type == CLICK_CLICK) {
		ret = clickMain(x, y);
	} else if (type == CLICK_FLAG) {
		ret = flag(x, y);
	} else {
		return RETURN_ERROR;
	}

	int doneBombs = 0;

	for(int x = 0; x < m_width; x++){
		for(int y = 0; y < m_height; y++){
			if(m_field[y][x] == CODE_MINE && m_visibleField[y][x] == CODE_FLAG){
				doneBombs += 1;
			}
		}
	}

	if(doneBombs >= m_bombs){
		return RETURN_WIN;
	}

	return ret;
}

Return BaseField::clickMain(const int x, const int y){
	if(m_clicked[y][x] == false && m_visibleField[y][x] != CODE_FLAG) {
		if (m_field[y][x] == CODE_MINE) {
			m_clicked[y][x] = true;
			for (int x = 0; x < m_width; x++) {
				for (int y = 0; y < m_height; y++) {
					showTile(x, y);
				}
			}
			return RETURN_DEAD;
		} else {
			pClick(x, y);
			return RETURN_ALIVE;
		}
	} else {
		return RETURN_FALSE_CLICK;
	}

}

void BaseField::pClick(const int x, const int y){
	m_clicked[y][x] = true;
	showTile(x, y);
	if(m_field[y][x] == 0){
		for(int xb = x - 1; xb < x + 2; xb++){
			if(xb >= 0 && xb < m_width) {
				for (int yb = y - 1; yb < y + 2; yb++) {
					if(yb >= 0 && yb < m_height && m_clicked[yb][xb] == false) {
						pClick(xb, yb);
					}
				}
			}
		}
	}
}

Return BaseField::flag(const int x, const int y){
	if(m_clicked[y][x] == false){
		if(m_visibleField[y][x] != CODE_FLAG) {
			m_visibleField[y][x] = CODE_FLAG;
		} else if(m_visibleField[y][x] == CODE_FLAG){
			m_visibleField[y][x] = CODE_LINE;
		}
		mainShowTile(x, y);
		return RETURN_ALIVE;
	} else {
		return RETURN_FALSE_CLICK;
	}
}

void BaseField::showTile(const int x, const int y){
	if(m_field[y][x] >= CODE_MINE){
		m_visibleField[y][x] = m_field[y][x];
	}

	mainShowTile(x, y);
}

void TermField::mainShowTile(const int x, const int y) {
	switch(m_visibleField[y][x]) {
		case CODE_MINE:
			m_playerField[y][x] = m_mine;
			break;
		case CODE_FLAG:
			m_playerField[y][x] = m_flag;
			break;
		case CODE_LINE:
			m_playerField[y][x] = m_line;
			break;
		case 0:
			m_playerField[y][x] = '0';
			break;
		case 1:
			m_playerField[y][x] = '1';
			break;
		case 2:
			m_playerField[y][x] = '2';
			break;
		case 3:
			m_playerField[y][x] = '3';
			break;
		case 4:
			m_playerField[y][x] = '4';
			break;
		case 5:
			m_playerField[y][x] = '5';
			break;
		case 6:
			m_playerField[y][x] = '6';
			break;
		case 7:
			m_playerField[y][x] = '7';
			break;
		case 8:
			m_playerField[y][x] = '8';
			break;
	}
}


int TermField::getPosInput(Click type){
	int pos;

	std::string msg;
	int max;

	if(type == CLICK_Y){
		msg = m_yMsg;
		max = m_height;
	} else if(type == CLICK_X){
		msg = m_xMsg;
		max = m_width;
	}

	while (1)
	{

		std::cout << msg;
		std::cin >> pos;

		if (std::cin.fail()) // no extraction took place
		{
			std::cin.clear(); // reset the state bits back to goodbit so we can use ignore()
			std::cin.ignore(32767, '\n'); // clear out the bad input from the stream
			continue; // try again
		}

		std::cin.ignore(32767, '\n'); // clear out any additional input from the stream
		if (std::cin.gcount() > 1)
			continue;


		if(pos < 0 || pos > max)
			continue;

		break;
	}

	return pos;
}

Click TermField::getTypeInput(){
	std::string type;

	while (1)
	{
		// Get user's name
		std::cout << m_typeMsg;
		std::getline(std::cin, type);

		if(type == "c")
			return CLICK_CLICK;
		if(type == "f")
			return CLICK_FLAG;

	}
}
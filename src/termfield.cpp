#include "../include/termfield.h"

TermField::~TermField() {
	for (int count = 0; count < m_height; ++count)
		delete[] m_playerField[count];
	delete[] m_playerField;
	m_playerField = nullptr;
}

std::ostream& operator<< (std::ostream &out, TermField &field) {
	for(int y = 0; y < field.m_height; y++){
		for(int x = 0; x < field.m_width; x++){
			out << '\t' << field.m_playerField[y][x];
		}
		out << "\n\n";
	}

	out << "\n\n";
	return out;
}

void TermField::showPlayerTile(const int x, const int y) {
	switch(m_visibleField[y][x]) {
		case CODE_POSSIBLE_FLAG:
			m_playerField[y][x] = m_possibleFlag;
			break;
		case CODE_WRONG_FLAG:
			m_playerField[y][x] = m_wrongFlag;
			break;
		case CODE_EXPLODED_MINE:
			m_playerField[y][x] = m_explodedMine;
			break;
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

	while(true){

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


		if(pos < 0 || pos > max){
			continue;
		}

		break;
	}

	return pos;
}

Click TermField::getTypeInput(){
	std::string type;

	while (true)
	{
		std::cout << m_typeMsg;
		std::getline(std::cin, type);

		if(type == "c")
			return CLICK_CLICK;
		if(type == "f")
			return CLICK_FLAG;

	}
}

void TermField::setSize(const int x, const int y){
	BaseField::setSize(x, y);

	delete[] m_playerField;
	m_playerField = new char*[m_height];
	for (int count = 0; count < m_height; ++count) {
		m_playerField[count] = new char[m_width]; // these are our columns
	}

	for(int xb = 0; xb < m_width; xb++) {
		for (int yb = 0; yb < m_height; yb++) {
			m_playerField[yb][xb] = m_line;
		}
	}
}

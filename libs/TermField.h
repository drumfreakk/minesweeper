#ifndef MINESWEEPER_TERMFIELD_H
#define MINESWEEPER_TERMFIELD_H

#include <iostream>
#include <cctype>
#include <string>

#include "Enums.h"
#include "BaseField.h"

class TermField : public BaseField {
private:
	char **m_playerField;

	const char m_mine = 'm';
	const char m_line = '-';
	const char m_flag = 'f';
	const char m_wrongFlag = 'w';
	const char m_possibleFlag = '?';
	const char m_explodedMine = 'e';

	std::string m_typeMsg = "CLick or Flag (c/f): ";
	std::string m_xMsg = "x: ";
	std::string m_yMsg = "y: ";

	virtual void showPlayerTile(const int x, const int y);

public:
	TermField(const int height, const int width)
			: BaseField(height, width)
	{
		m_playerField = new char*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_playerField[count] = new char[m_width]; // these are our columns
		}

		for(int x = 0; x < m_width; x++) {
			for (int y = 0; y < m_height; y++) {
				m_playerField[y][x] = m_line;
			}
		}
	}

	~TermField();

	int getPosInput(Click type);
	Click getTypeInput();

	std::string& typeMsg();
	std::string& xMsg();
	std::string& yMsg();

	friend std::ostream& operator<< (std::ostream &out, TermField &field);
};


#endif

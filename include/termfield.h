#ifndef MINESWEEPER_TERMFIELD_H
#define MINESWEEPER_TERMFIELD_H

#include <iostream>
#include <cctype>
#include <string>

#include "enums.h"
#include "basefield.h"

class TermField : public BaseField {
private:
	char **m_playerField;

	const char m_mine = 'm';
	const char m_line = '-';
	const char m_flag = 'f';
	const char m_wrongFlag = 'w';
	const char m_possibleFlag = '?';
	const char m_explodedMine = 'm';

	std::string m_typeMsg = "Click or Flag (c/f): ";
	std::string m_xMsg = "x: ";
	std::string m_yMsg = "y: ";

	virtual void showPlayerTile(int x, int y);

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

	TermField()
		: BaseField()
	{

		m_playerField = new char*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_playerField[count] = new char[m_width]; // these are our columns
		}
	}

	~TermField();

	void setSize(int x, int y);

	int getPosInput(Click type);
	Click getTypeInput();

	friend std::ostream& operator<< (std::ostream &out, TermField &field);
};


#endif

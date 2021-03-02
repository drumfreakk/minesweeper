#ifndef MINESWEEPER_BASEFIELD_H
#define MINESWEEPER_BASEFIELD_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "enums.h"


//#include <iostream>

typedef struct {
	// Private
	int pvt_bombs;
	int pvt_bombs_left;

	// Protected
	int p_height;
	int p_width;
	
	int** p_field;
	int** p_visible_field;
	bool** p_clicked;
} basefield;

ret_code initialize(basefield* base, int height, int width); // Is using a pointer right here?

ret_code destruct(basefield* base);

bool setup_field(basefield* base, int bombs); // Virtual

ret_code click(basefield* base, int x, int y, click_type type); // Virtual

void set_size(basefield* base, int height, int width);

int get_bombs(basefield* base);
int get_bombs_left(basefield* base);

int* get_element(basefield* base, int x, int y);	//TODO: is this one really necessary now? 
													//TODO: imean im going to do a general restructure so probably see then



/*
class BaseField {
private:

	int m_bombs = 0;
	int m_bombsLeft = 0;

	std::mt19937 m_rndgen;
	std::uniform_int_distribution<> m_randXPos;
	std::uniform_int_distribution<> m_randYPos;

protected:
	int m_height;
	int m_width;

	int **m_field;
	int **m_visibleField;
	bool **m_clicked;

	void showTile(int x, int y);
	void showTilesOnDeath(int x, int y);

	virtual void showPlayerTile(int x, int y) = 0;

	void shovelNums(int x, int y);
	Return flag(int x, int y);
	Return shovelWithMines(int x, int y);
	Return shovelFromNum(int x, int y);

public:
	BaseField(const int height, const int width)
			: m_height(height), m_width(width), m_randXPos(0, width - 1), m_randYPos(0, height - 1), m_rndgen(static_cast<unsigned int>(std::time(nullptr)))
	{

		m_field = new int*[m_height];
		for (int count = 0; count < m_height; ++count)
			m_field[count] = new int[m_width];

		m_visibleField = new int*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_visibleField[count] = new int[m_width];
		}

		m_clicked = new bool*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_clicked[count] = new bool[m_width];
		}

		for(int x = 0; x < m_width; x++){
			for(int y = 0; y < m_height; y++) {
				m_visibleField[y][x] = CODE_LINE;
			}
		}

		for(int x = 0; x < m_width; x++){
			for(int y = 0; y < m_height; y++){
				m_field[y][x] = 0;
			}
		}

	}

	/// if you use this initializer, you must call setSize before anything else
	BaseField()
		: m_rndgen(static_cast<unsigned int>(std::time(nullptr))), m_height(1), m_width(1)
	{
		m_field = new int*[m_height];
		for (int count = 0; count < m_height; ++count)
			m_field[count] = new int[m_width]; // these are our columns

		m_visibleField = new int*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_visibleField[count] = new int[m_width]; // these are our columns
		}

		m_clicked = new bool*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_clicked[count] = new bool[m_width]; // these are our columns
		}
	}

	~BaseField();

	virtual bool setupField(int bombs);

	virtual Return click(int x, int y, Click type);

	void setSize(int height, int width);

	int getBombs();
	int getBombsLeft();

	void debug(std::string msg, int **field);

	int* operator[](int row);

};
*/
#endif

#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <iostream>
#include <random>
#include <ctime>


//TODO: INPUT VALIDATION!!!


enum Return{
    RETURN_ALIVE,
    RETURN_DEAD,
    RETURN_FALSE_CLICK,
    RETURN_ERROR,
    RETURN_WIN
};

enum Codes{
	////CODE_MINE must be the largest number
	CODE_MINE = -1,
	CODE_FLAG = -2,
	CODE_LINE = -3
};

class BaseField {
private:

	int m_bombs;

	std::mt19937 m_rndgen;
	std::uniform_int_distribution<> m_randXPos;
	std::uniform_int_distribution<> m_randYPos;

protected:
    int m_height;
    int m_width;

    int **m_field;
    int **m_visibleField;
    bool **m_clicked;

    void showTile(const int x, const int y);

    virtual void mainShowTile(const int x, const int y) = 0;

    void pClick(const int x, const int y);
    Return flag(const int x, const int y);
    Return clickMain(const int x, const int y);

public:
	BaseField(const int height, const int width)
        : m_height(height), m_width(width), m_randXPos(0, width - 1), m_randYPos(0, height - 1), m_rndgen(static_cast<unsigned int>(std::time(nullptr)))
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

    void setupField(const int bombs);

    Return click(const int x, const int y, char type);

    int* operator[](const int row);

};

class TermField : public BaseField {
private:
	char **m_playerField;

	const char m_mine = 'm';
	const char m_line = '-';
	const char m_flag = 'f';

	virtual void mainShowTile(const int x, const int y);

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

	friend std::ostream& operator<< (std::ostream &out, TermField &field);
};



#endif

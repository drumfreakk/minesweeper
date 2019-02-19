#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <iostream>
#include <random>
#include <ctime>

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
protected:
    int height;
    int width;
    int **field;
    int **pField;

    bool **clicked;


    int bombs;

    std::mt19937 rndgen;
    std::uniform_int_distribution<> randx;
    std::uniform_int_distribution<> randy;

    void showTile(const int x, const int y);

    virtual void mainShowTile(const int x, const int y) = 0;

    void pClick(const int x, const int y);
    Return flag(const int clickx, const int clicky);
    Return clickMain(const int clickx, const int clicky);

public:
	BaseField(const int height, const int width)
        : height(height), width(width), randx(0, width - 1), randy(0, height - 1), rndgen(static_cast<unsigned int>(std::time(nullptr)))
    {
        field = new int*[height];
        for (int count = 0; count < height; ++count)
            field[count] = new int[width]; // these are our columns

        pField = new int*[height];
        for (int count = 0; count < height; ++count) {
            pField[count] = new int[width]; // these are our columns
        }

        clicked = new bool*[height];
        for (int count = 0; count < height; ++count) {
            clicked[count] = new bool[width]; // these are our columns
        }
    }

    ~BaseField();

    void setupField(const int bombs);

    Return click(const int clickx, const int clicky, char type);

    int operator() (const char* var);

    int* operator[](const int row);

};

class TermField : public BaseField {
private:
	char **t_pField;

	char t_mine = 'm';
	char t_line = '-';
	char t_flag = 'f';

	virtual void mainShowTile(const int x, const int y);

public:
	TermField(const int height, const int width)
	: BaseField(height, width)
	{
		t_pField = new char*[height];
		for (int count = 0; count < height; ++count) {
			t_pField[count] = new char[width]; // these are our columns
		}

		for(int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				t_pField[y][x] = t_line;
			}
		}
	}

	~TermField();

	friend std::ostream& operator<< (std::ostream &out, TermField &field);
};



#endif

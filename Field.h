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

class Field {
private:
    int height;
    int width;
    int **field;
    char **pField;

    bool **clicked;

    int mine = -1;

    int bombs;

    std::mt19937 rndgen;
    std::uniform_int_distribution<> randx;
    std::uniform_int_distribution<> randy;

    void showTile(const int x, const int y);

    void pClick(const int x, const int y);
    Return flag(const int clickx, const int clicky);
    Return clickMain(const int clickx, const int clicky);

public:
    Field(int height, int width)
        : height(height), width(width), randx(0, width - 1), randy(0, height - 1), rndgen(static_cast<unsigned int>(std::time(nullptr)))
    {
        field = new int*[height];
        for (int count = 0; count < height; ++count)
            field[count] = new int[width]; // these are our columns

        pField = new char*[height];
        for (int count = 0; count < height; ++count) {
            pField[count] = new char[width]; // these are our columns
        }

        clicked = new bool*[height];
        for (int count = 0; count < height; ++count) {
            clicked[count] = new bool[width]; // these are our columns
        }

        for(int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                pField[y][x] = '-';
            }
        }



    }

    ~Field();

    void setupField(const int bombs);

    Return click(const int clickx, const int clicky, char type);

    int& operator() (const char* var);

    int* operator[](const int row);

    friend std::ostream& operator<< (std::ostream &out, Field &field);

};



#endif

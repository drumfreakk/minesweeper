#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <iostream>
//#include <stdlib.h>
//#include <time.h>

#include <random>

class Field {
private:
    int height;
    int width;
    int **field;
    int mine = -1;

public:
    Field(int height, int width)
        : height(height), width(width)
    {
      //  srand (time(NULL));
        //Field::field = new int[height * width];
        field = new int*[height];
        for (int count = 0; count < height; ++count)
            field[count] = new int[width]; // these are our columns
    }

    ~Field();

    void setupField(const int bombs);

    int getSingleIndex(int row, int col);

    int& operator() (const char* var);

    int* operator[](const int row);

    friend std::ostream& operator<< (std::ostream &out, Field &field);

};



#endif

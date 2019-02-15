#include "Field.h"


Field::~Field() {
    for (int count = 0; count < Field::height; ++count)
        delete[] Field::field[count];
    delete[] Field::field; // this needs to be done last
    Field::field = nullptr;
}

int Field::getSingleIndex(const int row, const int col) {
    return (row * Field::width) + col;
}

std::ostream& operator<< (std::ostream &out, Field &field) {
    for(int y = 0; y < field.height; y++){
        for(int x = 0; x < field.width; x++){     //width
            out << " " << field[y][x];
        }
        out << '\n';
    }
    return out;
}

int& Field::operator() (const char* val){
    if(val == "height"){
        return Field::height;
    }
    else if(val == "width"){
        return Field::width;
    }
    return Field::mine;
}

int* Field::operator[](const int row){
    return Field::field[row];
}

void Field::setupField(const int bombs){
    int *xpos = new int[bombs];
    int *ypos = new int[bombs];

    bool nuffbombs = false;
    int doneBombs = 0;

    while(!nuffbombs){
        int x = rand() % Field::width;
        int y = rand() % Field::height;

        for(int i = 0; i < bombs; i++){

            if(x != xpos[i] && y != ypos[i]){

                Field::field[y][x] = mine;
                doneBombs += 1;

                xpos[i] = x;
                ypos[i] = y;
            }
        }

        if(doneBombs >= bombs){
            nuffbombs = true;
        }

    }

    delete[] xpos;
    delete[] ypos;
}
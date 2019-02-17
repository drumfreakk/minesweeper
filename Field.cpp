#include "Field.h"



Field::~Field() {
    for (int count = 0; count < Field::height; ++count)
        delete[] Field::field[count];
    delete[] Field::field;
    Field::field = nullptr;

    for (int count = 0; count < Field::height; ++count)
        delete[] Field::pField[count];
    delete[] Field::pField;
    Field::pField = nullptr;

    for (int count = 0; count < Field::height; ++count)
        delete[] Field::clicked[count];
    delete[] Field::clicked;
    Field::clicked = nullptr;
}

std::ostream& operator<< (std::ostream &out, Field &field) {
    for(int y = 0; y < field.height; y++){
        for(int x = 0; x < field.width; x++){     //width
            out << '\t' << field.pField[y][x];
        }
        out << "\n\n";
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

    Field::bombs = bombs;

    bool nuffbombs = false;
    int doneBombs = 0;

    while(!nuffbombs){
        int x = randx(rndgen);
        int y = randy(rndgen);

        if(Field::field[y][x] != mine) {

            Field::field[y][x] = mine;

            doneBombs += 1;
        }

        if(doneBombs >= bombs){
            nuffbombs = true;
        }

    }

    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(Field::field[y][x] == mine){

                for(int xb = x - 1; xb < x + 2; xb++){
                    if(xb >= 0 && xb < width) {

                        for (int yb = y - 1; yb < y + 2; yb++) {
                            if(yb >= 0 && yb < height && Field::field[yb][xb] != mine) {

                                Field::field[yb][xb] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

Return Field::click(const int clickx, const int clicky, char type){
    Return ret;
    if (type == 'c') {
        ret = Field::clickMain(clickx, clicky);
    } else if (type == 'f') {
        ret = Field::flag(clickx, clicky);
    } else {
        return RETURN_ERROR;
    }

    int doneBombs = 0;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(Field::field[y][x] == mine && Field::pField[y][x] == 'f'){
                doneBombs += 1;
            }
        }
    }

    if(doneBombs >= Field::bombs){
        return RETURN_WIN;
    }

    return ret;
}

Return Field::clickMain(const int clickx, const int clicky){
    if(Field::clicked[clicky][clickx] == false && Field::pField[clicky][clickx] != 'f') {
        if (Field::field[clicky][clickx] == mine) {
            Field::clicked[clicky][clickx] = true;
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    showTile(x, y);
                }
            }
            return RETURN_DEAD;
        } else {
            pClick(clickx, clicky);
            return RETURN_ALIVE;
        }
    } else {
        return RETURN_FALSE_CLICK;
    }

}

void Field::pClick(const int x, const int y){
    Field::clicked[y][x] = true;
    showTile(x, y);
    if(Field::field[y][x] == 0){
        for(int xb = x - 1; xb < x + 2; xb++){
            if(xb >= 0 && xb < Field::width) {
                for (int yb = y - 1; yb < y + 2; yb++) {
                    if(yb >= 0 && yb < Field::height && Field::clicked[yb][xb] == false) {
                        pClick(xb, yb);
                    }
                }
            }
        }
    }
}

Return Field::flag(const int clickx, const int clicky){
    if(Field::clicked[clicky][clickx] == false){
        if(Field::pField[clicky][clickx] != 'f') {
            Field::pField[clicky][clickx] = 'f';
        } else if(Field::pField[clicky][clickx] == 'f'){
            Field::pField[clicky][clickx] = '-';
        }
        return RETURN_ALIVE;
    } else {
        return RETURN_FALSE_CLICK;
    }
}

//TODO: neaten this?
void Field::showTile(const int x, const int y){
    switch(Field::field[y][x]) {
        case -1:
            Field::pField[y][x] = 'm';
            break;
        case 0:
            Field::pField[y][x] = '0';
            break;
        case 1:
            Field::pField[y][x] = '1';
            break;
        case 2:
            Field::pField[y][x] = '2';
            break;
        case 3:
            Field::pField[y][x] = '3';
            break;
        case 4:
            Field::pField[y][x] = '4';
            break;
        case 5:
            Field::pField[y][x] = '5';
            break;
        case 6:
            Field::pField[y][x] = '6';
            break;
        case 7:
            Field::pField[y][x] = '7';
            break;
        case 8:
            Field::pField[y][x] = '8';
            break;
    }
}

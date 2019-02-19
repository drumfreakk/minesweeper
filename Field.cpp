#include "Field.h"



BaseField::~BaseField() {
    for (int count = 0; count < height; ++count)
        delete[] field[count];
    delete[] field;
	field = nullptr;

    for (int count = 0; count < height; ++count)
        delete[] pField[count];
    delete[] pField;
	pField = nullptr;

    for (int count = 0; count < height; ++count)
        delete[] clicked[count];
    delete[] clicked;
	clicked = nullptr;
}

TermField::~TermField() {
    for (int count = 0; count < height; ++count)
        delete[] t_pField[count];
    delete[] t_pField;
    t_pField = nullptr;
}

std::ostream& operator<< (std::ostream &out, TermField &field) {
    for(int y = 0; y < field.height; y++){
        for(int x = 0; x < field.width; x++){     //width
            out << '\t' << field.t_pField[y][x];
        }
        out << "\n\n";
    }
    return out;
}

int BaseField::operator() (const char* val){
    if(val == "height"){
        return height;
    }
    else if(val == "width"){
        return width;
    }
    return RETURN_ERROR;
}

int* BaseField::operator[](const int row){
    return field[row];
}

void BaseField::setupField(const int bombs){

	BaseField::bombs = bombs;

    bool nuffbombs = false;
    int doneBombs = 0;

    while(!nuffbombs){
        int x = randx(rndgen);
        int y = randy(rndgen);

        if(field[y][x] != CODE_MINE) {

	        field[y][x] = CODE_MINE;

            doneBombs += 1;
        }

        if(doneBombs >= bombs){
            nuffbombs = true;
        }

    }

    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(field[y][x] == CODE_MINE){

                for(int xb = x - 1; xb < x + 2; xb++){
                    if(xb >= 0 && xb < width) {

                        for (int yb = y - 1; yb < y + 2; yb++) {
                            if(yb >= 0 && yb < height && field[yb][xb] != CODE_MINE) {

	                            field[yb][xb] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

Return BaseField::click(const int clickx, const int clicky, char type){
    Return ret;
    if (type == 'c') {
        ret = clickMain(clickx, clicky);
    } else if (type == 'f') {
        ret = flag(clickx, clicky);
    } else {
        return RETURN_ERROR;
    }

    int doneBombs = 0;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(field[y][x] == CODE_MINE && pField[y][x] == CODE_FLAG){
                doneBombs += 1;
            }
        }
    }

    if(doneBombs >= bombs){
        return RETURN_WIN;
    }

    return ret;
}

Return BaseField::clickMain(const int clickx, const int clicky){
    if(clicked[clicky][clickx] == false && pField[clicky][clickx] != CODE_FLAG) {
        if (field[clicky][clickx] == CODE_MINE) {
	        clicked[clicky][clickx] = true;
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

void BaseField::pClick(const int x, const int y){
	clicked[y][x] = true;
    showTile(x, y);
    if(field[y][x] == 0){
        for(int xb = x - 1; xb < x + 2; xb++){
            if(xb >= 0 && xb < width) {
                for (int yb = y - 1; yb < y + 2; yb++) {
                    if(yb >= 0 && yb < height && clicked[yb][xb] == false) {
                        pClick(xb, yb);
                    }
                }
            }
        }
    }
}

Return BaseField::flag(const int clickx, const int clicky){
    if(clicked[clicky][clickx] == false){
        if(pField[clicky][clickx] != CODE_FLAG) {
            pField[clicky][clickx] = CODE_FLAG;
        } else if(pField[clicky][clickx] == CODE_FLAG){
            pField[clicky][clickx] = CODE_LINE;
        }
        mainShowTile(clickx, clicky);
        return RETURN_ALIVE;
    } else {
        return RETURN_FALSE_CLICK;
    }
}

void BaseField::showTile(const int x, const int y){
	if(field[y][x] >= CODE_MINE){
		pField[y][x] = field[y][x];
	}

    mainShowTile(x, y);
}

void TermField::mainShowTile(const int x, const int y) {
    switch(pField[y][x]) {
        case CODE_MINE:
            t_pField[y][x] = t_mine;
            break;
        case CODE_FLAG:
            t_pField[y][x] = t_flag;
            break;
        case CODE_LINE:
            t_pField[y][x] = t_line;
            break;
        case 0:
            t_pField[y][x] = '0';
            break;
        case 1:
            t_pField[y][x] = '1';
            break;
        case 2:
            t_pField[y][x] = '2';
            break;
        case 3:
            t_pField[y][x] = '3';
            break;
        case 4:
            t_pField[y][x] = '4';
            break;
        case 5:
            t_pField[y][x] = '5';
            break;
        case 6:
            t_pField[y][x] = '6';
            break;
        case 7:
            t_pField[y][x] = '7';
            break;
        case 8:
            t_pField[y][x] = '8';
            break;
    }
}

#include "BaseField.h"

BaseField::~BaseField() {
	for (int count = 0; count < m_height; ++count)
		delete[] m_field[count];
	delete[] m_field;
	m_field = nullptr;

	for (int count = 0; count < m_height; ++count)
		delete[] m_visibleField[count];
	delete[] m_visibleField;
	m_visibleField = nullptr;

	for (int count = 0; count < m_height; ++count)
		delete[] m_clicked[count];
	delete[] m_clicked;
	m_clicked = nullptr;
}

int* BaseField::operator[](const int row){
	return m_field[row];
}

void BaseField::setupField(const int bombs){

	BaseField::m_bombs = bombs;

	bool nuffbombs = false;
	int doneBombs = 0;

	while(!nuffbombs){
		int x = m_randXPos(m_rndgen);
		int y = m_randYPos(m_rndgen);

		if(m_field[y][x] != CODE_MINE) {

			m_field[y][x] = CODE_MINE;

			doneBombs += 1;
		}

		if(doneBombs >= m_bombs){
			nuffbombs = true;
		}

	}

	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			if(m_field[y][x] == CODE_MINE){

				for(int xb = x - 1; xb < x + 2; xb++){
					if(xb >= 0 && xb < m_width) {

						for (int yb = y - 1; yb < y + 2; yb++) {
							if(yb >= 0 && yb < m_height && m_field[yb][xb] != CODE_MINE) {

								m_field[yb][xb] += 1;
							}
						}
					}
				}
			}
		}
	}
}

Return BaseField::click(const int x, const int y, Click type){
	Return ret;
	if (type == CLICK_CLICK) {
		ret = shovelWithMines(x, y);
	} else if (type == CLICK_FLAG) {
		ret = flag(x, y);
	} else {
		return RETURN_ERROR;
	}

	int doneBombs = 0;
	bool falseFlags = false;

	for(int x = 0; x < m_width; x++){
		for(int y = 0; y < m_height; y++){
			if(m_field[y][x] == CODE_MINE && m_visibleField[y][x] == CODE_FLAG){
				doneBombs += 1;
			}
			if((m_visibleField[y][x] == CODE_FLAG || m_visibleField[y][x] == CODE_POSSIBLE_FLAG) && m_field[y][x] != CODE_MINE){
				falseFlags = true;
			}
		}
	}

	if(doneBombs >= m_bombs && !falseFlags){
		return RETURN_WIN;
	}

	return ret;
}

Return BaseField::shovelWithMines(const int x, const int y){
	if(m_clicked[y][x] == false && m_visibleField[y][x] != CODE_FLAG && m_visibleField[y][x] != CODE_POSSIBLE_FLAG) {
		if (m_field[y][x] == CODE_MINE) {
			m_clicked[y][x] = true;

			showTilesOnDeath(x, y);

			return RETURN_DEAD;
		} else {
			shovelNums(x, y);
			return RETURN_ALIVE;
		}
	} else {
		return RETURN_FALSE_CLICK;
	}

}

void BaseField::shovelNums(const int x, const int y){
	m_clicked[y][x] = true;
	showTile(x, y);
	if(m_field[y][x] == 0){
		for(int xb = x - 1; xb < x + 2; xb++){
			if(xb >= 0 && xb < m_width) {
				for (int yb = y - 1; yb < y + 2; yb++) {
					if(yb >= 0 && yb < m_height && m_clicked[yb][xb] == false) {
						shovelNums(xb, yb);
					}
				}
			}
		}
	}
}

Return BaseField::flag(const int x, const int y){
	if(m_clicked[y][x] == false){
		if(m_visibleField[y][x] == CODE_LINE) {
			m_visibleField[y][x] = CODE_FLAG;
		} else if(m_visibleField[y][x] == CODE_FLAG){
			m_visibleField[y][x] = CODE_POSSIBLE_FLAG;
		} else if(m_visibleField[y][x] == CODE_POSSIBLE_FLAG){
			m_visibleField[y][x] = CODE_LINE;
		}
		showPlayerTile(x, y);
		return RETURN_ALIVE;
	} else {
		return RETURN_FALSE_CLICK;
	}
}

void BaseField::showTilesOnDeath(const int x, const int y) {
	for(int xb = 0; xb < m_width; xb++){
		for(int yb = 0; yb < m_height; yb++){
			int& visTile = m_visibleField[yb][xb];
			int& tile = m_field[yb][xb];

			if(tile == CODE_MINE){
				if(yb == y && xb == x){
					visTile = CODE_EXPLODED_MINE;
				} else if(visTile != CODE_FLAG){
					visTile = CODE_MINE;
				}
			} else if(visTile == CODE_FLAG){
				visTile = CODE_WRONG_FLAG;
			}

			showPlayerTile(xb, yb);

		}
	}
	//showTile(x, y);
}

void BaseField::showTile(const int x, const int y){
	if(m_field[y][x] > CODE_MINE){
		m_visibleField[y][x] = m_field[y][x];
	}

	showPlayerTile(x, y);
}

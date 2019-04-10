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

bool BaseField::setupField(const int bombs){
	if(bombs > (m_height * m_width)){
		return false;
	}

	BaseField::m_bombs = bombs;
	BaseField::m_bombsLeft = 0;

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

	return true;
}

Return BaseField::click(const int x, const int y, Click type) {

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
	if(m_visibleField[y][x] != CODE_FLAG && m_visibleField[y][x] != CODE_POSSIBLE_FLAG) {
		if (!m_clicked[y][x]) {
			if (m_field[y][x] == CODE_MINE) {
				m_clicked[y][x] = true;

				showTilesOnDeath(x, y);

				return RETURN_DEAD;
			} else {
				shovelNums(x, y);
				return RETURN_ALIVE;
			}
		} else {
			shovelFromNum(x, y);
			return RETURN_FALSE_CLICK;
		}
	} else {
		return RETURN_FALSE_CLICK;
	}
}

Return BaseField::shovelFromNum(const int x, const int y) {
	int flaggedBombs = 0;
	for (int xb = x - 1; xb < x + 2; xb++) {
		if (xb >= 0 && xb < m_width) {
			for (int yb = y - 1; yb < y + 2; yb++) {
				if (yb >= 0 && yb < m_height && m_visibleField[yb][xb] == CODE_FLAG) {
					flaggedBombs += 1;
				}
			}
		}
	}
	if(flaggedBombs == m_field[y][x]){
		for (int xb = x - 1; xb < x + 2; xb++) {
			if (xb >= 0 && xb < m_width) {
				for (int yb = y - 1; yb < y + 2; yb++) {
					if (yb >= 0 && yb < m_height && !m_clicked[yb][xb]) {
						if(shovelWithMines(xb, yb) == RETURN_DEAD){
							return RETURN_DEAD;
						}
					}
				}
			}
		}
	}
	return RETURN_ALIVE;
}


void BaseField::shovelNums(const int x, const int y){
	m_clicked[y][x] = true;
	showTile(x, y);
	if (m_field[y][x] == 0) {
		for (int xb = x - 1; xb < x + 2; xb++) {
			if (xb >= 0 && xb < m_width) {
				for (int yb = y - 1; yb < y + 2; yb++) {
					if (yb >= 0 && yb < m_height && !m_clicked[yb][xb]) {
						shovelNums(xb, yb);
					}
				}
			}
		}
	}
}

Return BaseField::flag(const int x, const int y){
	if(!m_clicked[y][x]){
		if(m_bombsLeft < m_bombs) {
			if (m_visibleField[y][x] == CODE_LINE) {
				m_visibleField[y][x] = CODE_FLAG;
				m_bombsLeft += 1;
			} else if(m_visibleField[y][x] == CODE_FLAG){
				m_visibleField[y][x] = CODE_POSSIBLE_FLAG;
				m_bombsLeft -= 1;
			} else if(m_visibleField[y][x] == CODE_POSSIBLE_FLAG){
				m_visibleField[y][x] = CODE_LINE;
			}
		} else if (m_visibleField[y][x] == CODE_LINE) {
			m_visibleField[y][x] = CODE_POSSIBLE_FLAG;
		} else {
			if(m_visibleField[y][x] == CODE_FLAG){
				m_visibleField[y][x] = CODE_POSSIBLE_FLAG;
				m_bombsLeft -= 1;
			} else if(m_visibleField[y][x] == CODE_POSSIBLE_FLAG){
				m_visibleField[y][x] = CODE_LINE;
			}
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

void BaseField::setSize(const int height, const int width) {

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

	m_height = height;
	m_width = width;

	m_rndgen = std::mt19937(static_cast<unsigned int>(std::time(nullptr)));

	m_randXPos = std::uniform_int_distribution<>(0, width - 1);
	m_randYPos = std::uniform_int_distribution<>(0, height - 1);


	m_field = new int*[m_height];
	for (int count = 0; count < m_height; ++count) {
		m_field[count] = new int[m_width]; // these are our columns
	}

	m_visibleField = new int*[m_height];
	for (int count = 0; count < m_height; ++count) {
		m_visibleField[count] = new int[m_width]; // these are our columns
	}

	m_clicked = new bool*[m_height];
	for (int count = 0; count < m_height; ++count) {
		m_clicked[count] = new bool[m_width]; // these are our columns
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

void BaseField::debug(const std::string msg, int **field){
#ifdef NDEBUG
	{
		std::cout << msg;

		for(int y = 0; y < m_height; y++){
			for(int x = 0; x < m_width; x++){
				std::cout << '\t' << field[y][x];
			}
			std::cout << "\n\n";
		}
		std::cout << "\n\n\n\n";
	}
#endif
}

int BaseField::getBombs(){
	return m_bombs;
}

int BaseField::getBombsLeft(){
	return m_bombsLeft;
}

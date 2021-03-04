#include "basefield.h"

// Protected functions
static void base_show_tile(basefield* base, int x, int y);
/*
static void base_show_tiles_on_death(basefield* base, int x, int y);

static ret_code base_flag(basefield* base, int x, int y);
static ret_code base_shovelWithMines(basefield* base, int x, int y);
static ret_code base_shovelFromNum(basefield* base, int x, int y);

static void base_showPlayerTile(basefield* base, int x, int y); // Virtual
*/


//TODO Error handling
basefield* initialize(int height, int width){ // Is using a pointer right here?
	basefield* base = (basefield*) malloc(sizeof(basefield));

	base->p_field = NULL;
	base->p_visible_field = NULL;
	base->p_clicked = NULL;

	set_size(base, height, width);

	srandom(time(NULL));

	return base;
}

ret_code destruct(basefield* base){
	for (int i = 0; i < base->p_height; i++){
		free(base->p_field[i]);
		free(base->p_visible_field[i]);
		free(base->p_clicked[i]);
	}
	free(base->p_field);
	free(base->p_visible_field);
	free(base->p_clicked);

	base->p_field = NULL;
	base->p_visible_field = NULL;
	base->p_clicked = NULL;

	free(base);
	base = NULL;

	return RETURN_NOERR;
}

int* get_element(basefield* base, int x, int y){
	return &(base->p_field[y][x]);
}

bool setup_field(basefield* base, int bombs){ // Virtual
	if(bombs > (base->p_height * base->p_width)){
		return false;
	}

	base->pvt_bombs = bombs;
	base->pvt_bombs_left = bombs;  //USED TO BE 0, ITS SWITCHED

	int done_bombs = 0;

	while(true){
		int x = random()%base->p_width;
		int y = random()%base->p_height;

		if(base->p_field[y][x] != CODE_MINE) {

			base->p_field[y][x] = CODE_MINE;
			done_bombs++;
		
			// Set the number of mines around each one
			for(int xb = x - 1; xb <= x + 1; xb++){
				if(xb >= 0 && xb < base->p_width) {
					for (int yb = y - 1; yb <= y + 1; yb++) {
						if(yb >= 0 && yb < base->p_height && base->p_field[yb][xb] != CODE_MINE) {
							base->p_field[yb][xb]++;
						}
					}
				}
			}
		}

		if(done_bombs >= bombs){
			break;
		}
	}
	
	return true;
}

void set_size(basefield* base, int height, int width){
	base->p_height = height;
	base->p_width = width;
	
	base->p_field = (int**) realloc(base->p_field, height * sizeof(int*));
	base->p_visible_field = (int**) realloc(base->p_visible_field, height * sizeof(int*));
	base->p_clicked = (bool**) realloc(base->p_clicked, height * sizeof(bool*));

	for (int i = 0; i < height; i++){
		base->p_field[i] = (int*) realloc(base->p_field[i], width * sizeof(int));
		base->p_visible_field[i] = (int*) realloc(base->p_visible_field[i], width * sizeof(int));	
		base->p_clicked[i] = (bool*) realloc(base->p_clicked[i], width * sizeof(bool));
	}

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++) {
			base->p_visible_field[y][x] = CODE_LINE;
			base->p_field[y][x] = 0;
		}
	}
}

static void base_show_tile(basefield* base, int x, int y){
	if(base->p_field[y][x] > CODE_MINE){
		base->p_visible_field[y][x] = base->p_field[y][x];
	}
//TODO: whenever a function calls (a function that) will call this, after that update your own field

//	void (*ptr)(basefield*,int) = test;
//	ptr(base, 3);
//	showPlayerTile(x, y);
}

/*
ret_code click(basefield* base, int x, int y, click_type type); // Virtual


int get_bombs(basefield* base);
int get_bombs_left(basefield* base);

*/


/*
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

	for(int xb = 0; xb < m_width; xb++){
		for(int yb = 0; yb < m_height; yb++){
			if(m_field[yb][xb] == CODE_MINE && m_visibleField[yb][xb] == CODE_FLAG){
				doneBombs += 1;
			}
			if((m_visibleField[yb][xb] == CODE_FLAG || m_visibleField[yb][xb] == CODE_POSSIBLE_FLAG) && m_field[yb][xb] != CODE_MINE){
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

Return BaseField::shovelFromNum(const int x, const int y){
	int flaggedBombs = 0;
	int aroundPosses[8][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
	int count = 0;
	for (int xb = x - 1; xb < x + 2; xb++){
		if (xb >= 0 && xb < m_width){
			for (int yb = y - 1; yb < y + 2; yb++){
				if (yb >= 0 && yb < m_height){
					if(m_visibleField[yb][xb] == CODE_FLAG){
						flaggedBombs += 1;
					}
					aroundPosses[count][0] = xb;
					aroundPosses[count][1] = yb;
					count += 1;
				}
			}
		}
	}
	for(int* pos : aroundPosses){
		if(flaggedBombs == m_field[y][x]){
			if(pos[0] != -1 && pos[1] != -1){
				if(!m_clicked[pos[1]][pos[0]] && shovelWithMines(pos[0], pos[1]) == RETURN_DEAD){
					return RETURN_DEAD;
				}
			}
		}
	}
	return RETURN_ALIVE;
}

void BaseField::shovelNums(const int x, const int y){
	m_clicked[y][x] = true;
	showTile(x, y);
	if (m_field[y][x] == 0){
		for (int xb = x - 1; xb < x + 2; xb++){
			if (xb >= 0 && xb < m_width) {
				for (int yb = y - 1; yb < y + 2; yb++){
					if (yb >= 0 && yb < m_height && !m_clicked[yb][xb]){
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
}



int BaseField::getBombs(){
	return m_bombs;
}

int BaseField::getBombsLeft(){
	return m_bombsLeft;
}


*/

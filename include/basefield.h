#ifndef MINESWEEPER_BASEFIELD_H
#define MINESWEEPER_BASEFIELD_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "enums.h"


//#include <iostream>

typedef struct {
	// Private
	int pvt_bombs;
	int pvt_bombs_left;

	// Protected
	int p_height;
	int p_width;
	
	int** p_field;
	int** p_visible_field;
	bool** p_clicked;
} basefield;

basefield* initialize(int height, int width);

ret_code destruct(basefield* base);

bool setup_field(basefield* base, int bombs); // Virtual

ret_code click(basefield* base, int x, int y, click_type type); // Virtual

void set_size(basefield* base, int height, int width);

int get_bombs(basefield* base);
int get_bombs_left(basefield* base);

int* get_element(basefield* base, int x, int y);	//TODO: is this one really necessary now? 
													//TODO: imean im going to do a general restructure so probably see then

#endif

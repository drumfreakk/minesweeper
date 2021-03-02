#ifndef MINESWEEPER_ENUMS_H
#define MINESWEEPER_ENUMS_H

typedef enum{
	RETURN_ALIVE,
	RETURN_DEAD,
	RETURN_FALSE_CLICK,
	RETURN_ERROR,
	RETURN_WIN,
	RETURN_NOERR
} ret_code;

typedef enum{
	////CODE_MINE must be the largest number
	CODE_MINE = -1,
	CODE_FLAG = -2,
	CODE_LINE = -3,
	CODE_POSSIBLE_FLAG = -4,
	CODE_WRONG_FLAG = -5,
	CODE_EXPLODED_MINE = -6
} tile_type;

typedef enum{
	CLICK_X,
	CLICK_Y,
	CLICK_FLAG,
	CLICK_CLICK
} click_type;


#endif

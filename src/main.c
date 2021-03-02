#include <stdio.h>
#include "field.h"

int getInput();

int main() {
	basefield base;
	initialize(&base, 5, 5);
	setup_field(&base, 7);

	for(int y = 4; y >=0; y--){
		for(int x = 0; x < 5; x++){
			printf("%i\t", base.p_field[y][x]);
		}
		printf("\n\n\n");
	}


	destruct(&base);

//	int x = 7;//getInput("Field width: ");
//	int y = 7;//getInput("Field height: ");
//	int bombs = 3;//getInput("Amount of Bombs: ");

/*
	TermField f(x, y);

	f.setSize(x -2, y -2);

	if(!f.setupField(bombs)){
		fprintf(stderr, "Too many bombs!");
		return 0;
	}

//	Prints the field
//	std::cout << "\n\n\n" << f << '\n';

	Click type;

	Return status = RETURN_ALIVE;

	while (status == RETURN_ALIVE) {
		do {
			type = f.getTypeInput();

			x = f.getPosInput(CLICK_X);
			y = f.getPosInput(CLICK_Y);

			status = f.click(x, y, type);

//			Prints the field
//			std::cout << f;
		} while (status == RETURN_FALSE_CLICK);

	}

	if (status == RETURN_DEAD) {
		printf("BOOM!\n");
	} else if (status == RETURN_WIN) {
		printf("\nYOU WIN!\n");
	}
*/
	return 0;
}

int getInput(){
	int out;

	while (1){
		//TODO: this doesnt do errorchecking and is shite basically, dont use it

		int res = scanf("%d", &out);
		
		if(res == EOF){
			out = -1;
		}

		if(out < 1){
			continue;
		}

		break;
	}

	return out;
}



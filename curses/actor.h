#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <vector>
#include "tile.h"

class actor {
	int _row, _col;
	char _symbol;
public:
	// Create a actor
	actor(char symbol, int row_0, int col_0);
	// Change the actor position
	void pos(int row_0, int col_0);
	// Get actor's row (y) position
	int row();
	// Get actor's col (x) position
	int col();
	// Get the symbol of the actor
	char symbol();
};

#endif // ACTOR_H_INCLUDED

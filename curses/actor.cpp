#include "actor.h"

// Create a actor
actor::actor(char symbol, int row_0, int col_0) {
	_symbol = symbol;
	_row = row_0;
	_col = col_0;
}

// Change the actor position
void actor::pos(int row_0, int col_0) {
	_row = row_0;
	_col = col_0;
}

// Get actor's row (y) position
int actor::row() {
	return _row;
}

// Get actor's col (x) position
int actor::col() {
	return _col;
}

// Get the symbol of the actor
char actor::symbol() {
	return _symbol;
}

#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "actor.h"
#include "include/curses.h"

class Screen {
	int _height, _width;
public:
	// Initialize the ncurses library
	Screen();
	// Clear ncurses
	~Screen();
	// Print a message on the screen
	void add(const char *message);
	// Get the screen height and width
	int height();
	int width();
	// Don't wait for the user to press a key (non-blocking I/O)
	void zerodelay();
	// Wait for the user to press a key (blocking I/O this is the default when ncurses starts)
	void delay();
};

class Frame {
	// Frame dimensions
	int _height, _width;
	// Frame position
	int _row, _col;
	// Boolean - FALSE for a window and TRUE for a subwindow (viewport)
	bool _has_super;
	// Pointer to an ncurses WINDOW
	WINDOW *_w;
	// Pointer to an ncurses WINDOW, this will be NULL for a window and will point to the parent window
	// for a subwindow
	WINDOW *_super;
public:
	// Get the window
	WINDOW *win();
	// Get the parent window
	WINDOW *super();
	// Initialize a main window (no parent)
	Frame(int nr_rows, int nr_cols, int row_0, int col_0);
	// Initialize a subwindow (viewport) with a parent window
	Frame(Frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);
	~Frame();
	// Get window type, if TRUE we have a subwindow, if FALSE we have a main window
	bool has_super();
	// Get the height of the window
	int height();
	// Get the width of the window
	int width();
	// Get the row (y) position of the window
	int row();
	// Get the row (y) position of the window
	int col();
	// Fill a window with numbers - the window is split in four equal regions,
	// each region is filled with a single number, so 4 regions and 4 numbers.
	// This is a suggestion of how this will look:
	//         0 | 1
	//         -----
	//         2 | 3
	// This function is used only for debugging purposes.
	void fill_window();
	// Refresh the window
	void refresh();
	// Move a window in a new position (r, c)
	void move(int r, int c);
	// Add a actor to the window
	void add(actor &x);
	// Define the "erase" actor, use an empty actor for cleaning a cell or a
	// visible actor for showing the trace of a game actor
	void erase(actor &x);
	// Add a actor at a specific position to the window
	void add(actor &x, int row_0, int col_0);
	// Center the viewport around a actor
	void center(actor &x);
	// Generate a game map using a Perlin noise function
	void gen_Perlin(const unsigned int &seed);
	// Check if the target position is free
	bool target_position(int row_0, int col_0);
};

#endif // WINDOW_H_INCLUDED

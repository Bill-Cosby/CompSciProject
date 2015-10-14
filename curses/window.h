#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "include/curses.h"
#include "actor.h"


class Frame
{
    int height,width;
    int row,col;
    bool has_super;
    WINDOW *_w;
    WINDOW *_super;
public:
    //main window(no parent)
    Frame(int nr_rows, int nr_cols, int row_0, int col_0);
    //initalize subwindow (viewport) with parent window
    Frame(Frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);

    ~Frame();
    /*
    Fill a window with numbers - the window is split in four equal regions,
    each region is filled with a single number, so 4 regions and 4 numbers.
    this is a suggestion of how it will look
                0|1
                ---
                2|3
    this function is only for debugging
    */
    void fill_window();

    void add(actor &x);
    void center(actor &x);
};

#endif // WINDOW_H_INCLUDED

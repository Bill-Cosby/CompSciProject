#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "actor.h"
#include "include/curses.h"
#include <string>

class screen{
    int _w,_h;
public:
    WINDOW* win;
    screen(int,int);

    void add(const char*);

    int width(){return _w;}
    int height(){return _h;}
};

class frame{
    int _w,_h;
public:
    WINDOW* sub;

    frame(WINDOW* parent, int w, int h)
};

#endif // WINDOW_H_INCLUDED

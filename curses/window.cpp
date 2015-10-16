#include "window.h"
#include <iostream>

screen::screen(int w,int h)
{
    _w=w;
    _h=h;
    win=initscr();
    noecho();
    curs_set(0);
    resize_term(h,w);
}

void screen::add(const char* _print)
{
    mvwaddstr(win,0,0,_print);
    wrefresh(win);
}

frame::frame(WINDOW* parent, int w, int h)
{
    sub=derwin(parent,w,h,0,0);
}

void frame::draw(const char* thing)
{
    mvwaddstr(sub,0,0,thing);
}

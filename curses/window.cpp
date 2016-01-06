#include "window.h"
#include <iostream>

#define COLOR_LIGHTGREEN 10

screen::screen(int w,int h)
{
    _w=w;
    _h=h;
    win=initscr();
    keypad(win,true);
    curs_set(0);
    resize_term(h,w);
    subwindow=frame(win,h,w);
    wborder(win,0,0,0,0,0,0,0,0);
    noecho();
    cbreak();
    halfdelay(1);
    //nodelay(win,false);
    start_color();
    init_color(COLOR_PLAYER,0,200,500);
    init_color(COLOR_DOG,1000,0,0);
}

void screen::add(const char* _print)
{
    touchwin(win);
    mvwaddstr(win,1,1,_print);
    wrefresh(win);
}

void screen::drawStats(int health){
    std::stringstream ss;
    ss << health;
    std::string str = ss.str();
    mvaddstr(10,60,str.c_str());
    wrefresh(win);
    wrefresh(subwindow.sub);
}

frame::frame(WINDOW* parent, int h, int w)
{
    _h=h/2;
    _w=w/2;
    sub=newwin(_h,_w,parent->_begx,parent->_begy);
    examineWindow=newwin(_h,15,parent->_begy,parent->_begx+w-15);
    inventoryWindow=newwin(_h+2,17,parent->_begy,parent->_begx);
    equipmentWindow=newwin(_h+2,17,parent->_begy,parent->_begx+17);
    itemDescriptionWindow=newwin(30,40,0,0);

    wborder(examineWindow,0,0,0,0,0,0,0,0);
    wborder(sub,0,0,0,0,0,0,0,0);
    wrefresh(sub);
    init_color(COLOR_PLAYER,0,200,500);
    init_color(COLOR_DOG,1000,0,0);
}

void frame::draw(const char* thing)
{
    touchwin(sub);
    mvwaddstr(sub,1,1,thing);
    wrefresh(sub);
}



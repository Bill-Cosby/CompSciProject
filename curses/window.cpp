#include "window.h"
#include <iostream>

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
    wrefresh(win);
    noecho();
    cbreak();
    nodelay(win,true);
}

void screen::add(const char* _print)
{
    touchwin(win);
    mvwaddstr(win,1,1,_print);
    wrefresh(win);
}

void screen::drawGameworld(std::vector<std::vector<tile> > _map, std::vector<actor> actors)
{
    touchwin(subwindow.sub);
    coordinate startingposition;
    coordinate charplaced;
    for (int i=0;i<actors.size();i++)
    {
        if (actors[i].player==true)
        {
            startingposition=coordinate(actors[i].col(),actors[i].row());
        }
    }
    charplaced=coordinate(startingposition.x-(subwindow.width()-(subwindow.width()/2)),startingposition.y-(subwindow.height()-(subwindow.height()/2)));
    for (int y=1;y<subwindow.height()-1;y++)
    {
        for (int x=1;x<subwindow.width()-1;x++)
        {
            if (y+charplaced.y>0 and y+charplaced.y<_map.size() and x+charplaced.x>0 and x+charplaced.x<_map[0].size())
            {
                mvwaddch(subwindow.sub,y,x,_map[y+charplaced.y][x+charplaced.x].defaultchar);
            }
            for (actor _a: actors)
            {
                if (coordinate(_a.col(),_a.row())==coordinate(x+charplaced.x,y+charplaced.y))
                {
                    mvwaddch(subwindow.sub,y,x,_a.symbol());
                }
            }
        }
    }
    wrefresh(subwindow.sub);
}

frame::frame(WINDOW* parent, int h, int w)
{
    _h=h/2;
    _w=w/2;
    sub=newwin(_h,_w,parent->_begx,parent->_begy);
    wborder(sub,0,0,0,0,0,0,0,0);
    wrefresh(sub);
}

void frame::draw(const char* thing)
{
    touchwin(sub);
    mvwaddstr(sub,1,1,thing);
    wrefresh(sub);
}

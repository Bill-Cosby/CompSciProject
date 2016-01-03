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
    nodelay(win,false);
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
}

void screen::drawGameworld(std::vector<std::vector<tile*> > _map, std::vector<actor*> *actors)
{
    touchwin(subwindow.sub);
    wclear(subwindow.sub);
    init_pair(3,COLOR_PLAYER,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);


    coordinate startingposition;
    coordinate charplaced;
    std::vector<actor*> temp=*actors;

            startingposition=coordinate((temp[0])->col(),(temp[0])->row());

                    attron(COLOR_PAIR(2));
    charplaced=coordinate(startingposition.x-(subwindow.width()/2),startingposition.y-(subwindow.height()/2));
    //charplaced=coordinate(0,0);
    wborder(win,0,0,0,0,0,0,0,0);
    wborder(subwindow.sub,0,0,0,0,0,0,0,0);
    for (int y=1;y<subwindow.height()-1;y++)
    {
        for (int x=1;x<subwindow.width()-1;x++)
        {
            if (y+charplaced.y>=0 and y+charplaced.y<_map.size() and x+charplaced.x>=0 and x+charplaced.x<_map[0].size())
            {
                mvwaddch(subwindow.sub,y,x,_map[y+charplaced.y][x+charplaced.x]->drawTile());
            }
            for (actor* _a: *actors)
            {
                if (coordinate(_a->col(),_a->row())==coordinate(x+charplaced.x,y+charplaced.y))
                {
                    attron(COLOR_PAIR(2));
                    mvwaddch(subwindow.sub,y,x,_a->symbol());
                    attroff(COLOR_PAIR(2));
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
    start_color();
    init_color(COLOR_PLAYER,0,200,500);
    init_color(COLOR_DOG,1000,0,0);
}

void frame::draw(const char* thing)
{
    touchwin(sub);
    mvwaddstr(sub,1,1,thing);
    wrefresh(sub);
}



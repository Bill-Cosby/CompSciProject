#include "window.h"
#include <iostream>
#include "include/curses.h"

screen::screen(int w,int h)
{
    win=initscr();
    start_color();
    init_pair(1,COLOR_CYAN, COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_YELLOW,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7,COLOR_WHITE,COLOR_BLACK);

    _w=w;
    _h=h;
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

void screen::drawStats(int health){
    std::stringstream ss;
    ss << health;
    std::string str = ss.str();
    mvaddstr(10,60,str.c_str());
}

void screen::drawGameworld(tiles _map, std::vector<actor> actors)
{
    touchwin(subwindow.sub);
    coordinate startingposition;
    coordinate charplaced;
    for (int i=0;i<actors.size();i++)
    {
        if (actors[i].controlled==true)
        {
            startingposition=coordinate(actors[i].col(),actors[i].row());
        }
    }
    charplaced=coordinate(startingposition.x-(subwindow.width()/2),startingposition.y-(subwindow.height()/2));
    for (int y=1;y<subwindow.height()-1;y++)
    {
        for (int x=1;x<subwindow.width()-1;x++)
        {
            if (y+charplaced.y>0 and y+charplaced.y<_map.tileMap[0].size() and x+charplaced.x>0 and x+charplaced.x<_map.tileMap[0].size())
            {

                wattron(subwindow.sub,COLOR_PAIR(_map.tileMap[y+charplaced.y][x+charplaced.x].color));
                mvwaddch(subwindow.sub,y,x,_map.tileMap[y+charplaced.y][x+charplaced.x].defaultchar);
                wattroff(subwindow.sub,COLOR_PAIR(_map.tileMap[y+charplaced.y][x+charplaced.x].color));
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
    getch();
    wrefresh(subwindow.sub);
}

void screen::drawMenu(custom_menu menuToDraw)
{
    int position=1;
    for (menu_button _b : menuToDraw.listOfButtons){
        if (menuToDraw.verticle==true){
            _b.y=position;
            _b.x=10;
            position+=height()/menuToDraw.listOfButtons.size();
        }
        else
        {
            _b.x=position;
            _b.y=height()-10;
            position+=width()/menuToDraw.listOfButtons.size();
        }
        if (_b.selected==true){
            mvwaddstr(win,10,width()-50,_b.description.c_str());
            attron(A_REVERSE);
        }
        mvwaddstr(win,_b.y,_b.x,_b.name.c_str());
        attroff(A_REVERSE);
    }
    refresh();
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

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
    announcementWindow=newwin(h*.75,w*.5,h*.25,w*.5);
    wborder(announcementWindow,0,0,0,0,0,0,0,0);
    announcementWindowHeight=h*.75;
    noecho();
    cbreak();
    //halfdelay(2);
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

void screen::drawStats(int health)
{
    std::stringstream ss;
    ss << health;
    std::string str = ss.str();
    mvaddstr(10,60,str.c_str());
    wborder(announcementWindow,0,0,0,0,0,0,0,0);
    wrefresh(win);
    wrefresh(subwindow.sub);
}

void screen::drawAnnouncements()
{
    int temp=announcementWindowHeight-1;
    werase(announcementWindow);
    wborder(announcementWindow,0,0,0,0,0,0,0,0);
    wattron(announcementWindow,A_UNDERLINE);
    for (int i=announcements.size()-1;i>=0;i--){
        temp--;
        mvwaddstr(announcementWindow,temp,1,announcements[i].c_str());;
    }
    wattroff(announcementWindow,A_UNDERLINE);
    wrefresh(announcementWindow);
}

void screen::addAnnouncement(std::string announcementToAdd)
{
    announcements.push_back(announcementToAdd);
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

    init_color(COLOR_PLAYER,0,200,500);
    init_color(COLOR_DOG,1000,0,0);
}

void frame::draw(const char* thing)
{
    touchwin(sub);
    mvwaddstr(sub,1,1,thing);
    wrefresh(sub);
}



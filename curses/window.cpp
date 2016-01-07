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

}

void screen::windowRefresh()
{
    wrefresh(subwindow.sub);
    wrefresh(announcementWindow);
}

void screen::add(const char* _print)
{
    mvwaddstr(win,1,1,_print);
}

void screen::drawStats(int health)
{
    std::stringstream ss;
    ss << health;
    std::string str = ss.str();
    mvwaddstr(win,10,60,str.c_str());
}

void screen::drawAnnouncements()
{
    int temp=announcementWindowHeight-1;
    werase(announcementWindow);
    wborder(announcementWindow,0,0,0,0,0,0,0,0);
    for (int i=announcements.size()-1;i>=0;i--){
        temp--;
        mvwaddstr(announcementWindow,temp,1,announcements[i].c_str());;
    }
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
    examineWindow=newwin(_h,25,parent->_begy,parent->_begx+w-25);
    inventoryWindow=newwin(_h+2,17,parent->_begy,parent->_begx);
    equipmentWindow=newwin(_h+2,17,parent->_begy,parent->_begx+17);
    itemDescriptionWindow=newwin(30,40,0,0);

}

void frame::draw(const char* thing)
{
    touchwin(sub);
    mvwaddstr(sub,1,1,thing);
}



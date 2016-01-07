#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "tile.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "include/curses.h"



#define COLOR_PLAYER 11
#define COLOR_DOG 12


class frame{
    int _w,_h;
public:
    WINDOW* sub;
    WINDOW* inventoryWindow;
    WINDOW* equipmentWindow;
    WINDOW* examineWindow;
    WINDOW* itemDescriptionWindow;

    frame(WINDOW* parent, int w, int h);
    frame(){};
    void draw(const char*);

    int width(){return _w;}
    int height(){return _h;}
};

class screen{
    int _w,_h;
    int announcementWindowHeight;
public:
    WINDOW* win;
    WINDOW* announcementWindow;
    frame subwindow;
    std::vector<std::string> announcements;


    screen(int,int);
    void add(const char*);

    void drawStats(int);
    void drawAnnouncements();
    void addAnnouncement(std::string);

    int width(){return _w;}
    int height(){return _h;}
};


#endif // WINDOW_H_INCLUDED

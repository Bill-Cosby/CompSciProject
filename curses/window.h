#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "actor.h"
#include <string>

class frame{
    int _w,_h;
public:
    WINDOW* sub;

    frame(WINDOW* parent, int w, int h);
    frame(){};
    void draw(const char*);

    int width(){return _w;}
    int height(){return _h;}
};

class screen{
    int _w,_h;
public:
    WINDOW* win;
    frame subwindow;

    screen(int,int);
    void add(const char*);

    void drawGameworld(std::vector<std::vector<tile> > _map, std::vector<actor> actors);

    int width(){return _w;}
    int height(){return _h;}
};



#endif // WINDOW_H_INCLUDED
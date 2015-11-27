#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "include/curses.h"
#include "aStar.h"

class actor
{
    int x,y;
    char _symbol;
    coordinate memory;
public:
    void movement(std::vector<std::vector<tile> >, char);
    void aiMovement(std::vector<std::vector<tile> >, coordinate);
    actor();
    actor(int);
    bool player;
    bool musttouch;
    std::vector<coordinate> path;

    int row(){return y;}
    int col(){return x;}
    char symbol(){return _symbol;}
    void pos(int _y,int _x){x=_x;y=_y;}
};

#endif // ACTOR_H_INCLUDED

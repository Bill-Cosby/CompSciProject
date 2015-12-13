#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "aStar.h"

class actor
{
protected:
    char _symbol;
    int x,y;
public:
    bool controlled;
    int row(){return y;}
    int col(){return x;}

    char symbol(){return _symbol;}
    void pos(int _y,int _x){x=_x;y=_y;}
};

class player : public actor
{
public:
    void movement(std::vector<std::vector<tile> >, char);
    player();
};

class monster : public actor
{
    coordinate memory;
    coordinate post;
public:
    std::vector<coordinate> path;
    int speed;
    int counter;
    bool musttouch;
    void aiMovement(std::vector<std::vector<tile> >, coordinate, std::vector<actor>);
    bool canSee(std::vector<std::vector<tile> >, coordinate);
    monster(int,char);
    void setPost(int x, int y){post=coordinate(x,y);}
};

#endif // ACTOR_H_INCLUDED

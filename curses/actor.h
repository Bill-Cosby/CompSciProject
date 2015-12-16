#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "aStar.h"

class actor
{
protected:
    char _symbol;

    bool sprinting=0;

    int x,y;
public:
    int counter;
    int speed;
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
    int getCounter(){return counter;}
    int getSpeed(){return speed-(.5*speed)-1;}
    int raiseCounter(){counter++;}
};

class monster : public actor
{
    coordinate memory;
    coordinate post;
public:
    std::vector<coordinate> path;
    bool musttouch;
    void aiMovement(std::vector<std::vector<tile> >, coordinate, std::vector<actor>);
    bool canSee(std::vector<std::vector<tile> >, coordinate);
    monster(int,char);
    void setPost(int x, int y){post=coordinate(x,y);}
};

#endif // ACTOR_H_INCLUDED

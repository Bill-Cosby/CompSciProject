#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED
#include <random>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <fstream>

class xyspot
{
public:
    int x,y;
    xyspot(int _x,int _y){x=_x;y=_y;}
    xyspot(){};
};

class dungeon
{
private:
    xyspot directions[4]={xyspot(0,-1),xyspot(1,0),xyspot(0,1),xyspot(-1,0)};
    int w,h;
public:
    xyspot mazeBegin;
    std::vector<std::vector<bool> > dungeon_grid;
    dungeon();
    void hallwayMaker();
    int Passable(int,int);
};


#endif // DUNGEON_H_INCLUDED

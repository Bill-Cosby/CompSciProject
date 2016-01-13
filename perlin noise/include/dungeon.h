#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED
#include <random>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <fstream>
#include "../window.h"

class dungeon
{
private:
    coordinate directions[4]={coordinate(0,-1),coordinate(1,0),coordinate(0,1),coordinate(-1,0)};
    int w,h;
public:
    coordinate mazeBegin;
    std::vector<std::vector<bool> > dungeon_grid;
    dungeon();
    void hallwayMaker();
};


#endif // DUNGEON_H_INCLUDED

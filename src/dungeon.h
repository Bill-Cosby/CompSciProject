#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <functional>
#include <stack>

class coordinate
{
public:
    int x,y;
    coordinate(int,int);
    coordinate();
};

class room
{
public:
    int x,y,w,h;
    room(int,int,int,int);
};

class dungeons
{
public:
    int w,h;
    coordinate mazebegin;
    std::vector<std::vector<bool> > dungeon_grid;
    std::vector<room> rooms;
    dungeons();
    void hallwaymaker();
};

bool mazeAdjacency(std::vector<std::vector<bool> >, coordinate);

#endif // DUNGEON_H_INCLUDED

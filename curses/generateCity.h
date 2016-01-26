#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>

class road
{
coordinate * Point1;
coordinate * Point2;
int size;
bool vertical;
void makeRoad();
};


class box
{
box(){blank.resize(2);};
box * subBox1;
box * subBox2;
double right;
double left;
double bottom;
double top;
std::vector<coordinate *> blank;
void divideBox();
};

class city: public box
{
int tileMap[50][50];
std::vector <road *> roads;
void deleteTileMap50();
void setTileMap();
city(){left=0; bottom=0; right=50; top=50; setTileMap();}
generateCity();
makeCity();
drawCity();
};




#endif // GENERATECITY_H_INCLUDED

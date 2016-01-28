#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>

class road
{
    public:
coordinate * Point1;
coordinate * Point2;
int size;
bool vertical;

};


class box
{
public:

box * subBox1;
box * subBox2;
double right;
double left;
double bottom;
double top;
std::vector<coordinate *> blank;

box(){blank.resize(2);}
void divideBox(int);
};

class city: public box
{
std::vector<std::vector<tile*> > tileMap;
std::vector <road *> roads;

city(){left=0; bottom=0; right=50; top=50; setTileMap();}
void setTileMap();
void deleteTileMap50();
void generateCity(vector<actor *> *,vector<item*> *, screen*);
void makeCity();
void drawCity();
void makeRoad(road*);
};




#endif // GENERATECITY_H_INCLUDED

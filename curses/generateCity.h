#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>
#include "actor.h"
#include <SFML/Graphics.hpp>



class road
{
    public:
coordinate * Point1;
coordinate * Point2;
int Size;
bool vertical;

};


class box
{
public:

box * subBox1;
box * subBox2;
int right;
int left;
int bottom;
int top;
std::vector<coordinate *> blank;

box(){blank.resize(2);}
void divideBox(int, std::vector<std::vector<tile*> > &);
void makeRoad(road*, std::vector<std::vector<tile*> > &);
};

class city: box
{
    public:
std::vector<std::vector<tile*> > tileMap;
int tileMapSize;
void setTileMap();
city(){tileMapSize=50; left=0; bottom=0; right=tileMapSize-1; top=tileMapSize-1; }
void generateCity();
void deleteTileMap();
};



#endif // GENERATECITY_H_INCLUDED

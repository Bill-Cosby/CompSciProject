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

box(){blank.resize(2);left = 0;right =0;top=0;bottom=0;}
~box();
void divideBox(int, std::vector<std::vector<std::vector<tile*> > > &, std::string, std::default_random_engine);
void makeLine(road*, std::vector<std::vector<std::vector<tile*> > > &, int, std::string);
void makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap,std::default_random_engine);
};


class city: public box
{
    public:
std::vector<std::vector<std::vector<tile*> > > tileMap;
int tileMapSize;
void setTileMap();
city(){tileMapSize=100; left=0; bottom=0; right=tileMapSize-1; top=tileMapSize-1; }
void generateCity();
void deleteTileMap();
};



#endif // GENERATECITY_H_INCLUDED

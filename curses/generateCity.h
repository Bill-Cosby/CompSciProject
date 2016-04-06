#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>
#include "actor.h"
#include <SFML/Graphics.hpp>
#include <chrono>




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

box(){left = 0;right =0;top=0;bottom=0;}
~box();
void divideBox(int, std::vector<std::vector<std::vector<tile*> > > &, std::string, std::mt19937 &,std::vector<actor*> &actors);
void makeLine(road*, std::vector<std::vector<std::vector<tile*> > > &, int, std::string, std::mt19937 &);
void makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap, std::mt19937 &,std::vector<actor*> &actors);
};


class city: public box
{
    bool oneSmallStepForMan;
    public:
 std::mt19937 generator;
unsigned seed;
std::vector<std::vector<std::vector<tile*> > > tileMap;
int tileMapSize;
void setTileMap();
city(){tileMapSize=100; left=0; bottom=0; right=tileMapSize-1; top=tileMapSize-1; seed=std::chrono::system_clock::now().time_since_epoch().count(); generator.seed(seed);}
void generateCity(std::vector<actor*> &actors);
void deleteTileMap();
};



#endif // GENERATECITY_H_INCLUDED

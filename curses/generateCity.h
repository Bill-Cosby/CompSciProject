#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <random>

void generateCity(std::vector<std::vector<tile*> > _map)
{
    int lengthOfRoad=_map.size();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> locationOnMap(1,_map.size());
    std::uniform_int_distribution<int> lengthOfGennedRoad(1,lengthOfRoad);
    std::uniform_int_distribution<int> lengthOfGennedRoad(1,lengthOfRoad);


    auto positionInCity = std::bind(locationOnMap, generator);
    auto generateRoad = std::bind(lengthOfGennedRoad,generator);


}

#endif // GENERATECITY_H_INCLUDED

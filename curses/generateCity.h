#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>

void generateCity(std::vector<std::vector<tile*> > *_map, bool verticle, int numberOfRoads, bool firstGen, coordinate startingPosition, int numberOfIterations)
{int beginning,goTo;
    std::mt19937 generator(time(NULL));
    std::uniform_int_distribution<int> locationOnMap(1,_map->size());
    std::uniform_int_distribution<int> numberOfRoadsToMake(1,5);
    std::uniform_int_distribution<int> coinToss(0,100);

    if (numberOfIterations==0){
        return;
    }

    if (firstGen==true){
        for (int i=0;i<_map->size();i++){
            (*_map)[i][startingPosition.x]=new tile('.',0,stone);
            (*_map)[i][startingPosition.x+1]=new tile('.',0,stone);
            (*_map)[i][startingPosition.x-1]=new tile('.',0,stone);
        }
        generateCity(_map,false, numberOfRoadsToMake(generator), false,startingPosition,numberOfIterations);
    }
    for (int * R = new int(0); *R < numberOfRoads; *R++){
        if (verticle==false){
        if (coinToss(generator)<50){
            std::uniform_int_distribution<int> positionOfNewRoad(1,startingPosition.y);
            startingPosition.y=positionOfNewRoad(generator);
            for (int i=startingPosition.x;i>0;i--){
                (*_map)[startingPosition.y][i] = new tile('.',0,stone);
            }
        }
        else{
            std::uniform_int_distribution<int> positionOfNewRoad(startingPosition.y,_map->size());
            startingPosition.y=positionOfNewRoad(generator);
            for (int i=startingPosition.x;i<_map->size();i++){
                (*_map)[startingPosition.y][i] = new tile('.',0,stone);
            }
        }
        generateCity(_map,1-verticle, numberOfRoadsToMake(generator), false,startingPosition,numberOfIterations-1);
    }
    else{
        if (coinToss(generator)<50){
            std::uniform_int_distribution<int> positionOfNewRoad(1,startingPosition.x);
            startingPosition.x=positionOfNewRoad(generator);
            for (int i=startingPosition.y;i>0;i--){
                (*_map)[i][startingPosition.x] = new tile('.',0,stone);
            }
        }
        else{
            std::uniform_int_distribution<int> positionOfNewRoad(startingPosition.x,_map->size());
            startingPosition.x=positionOfNewRoad(generator);
            for (int i=startingPosition.y;i<_map->size();i++){
                (*_map)[i][startingPosition.x] = new tile('.',0,stone);
            }
        }
        generateCity(_map,1-verticle, numberOfRoadsToMake(generator), false,startingPosition,numberOfIterations-1);
    }
    }

    return;
}

#endif // GENERATECITY_H_INCLUDED

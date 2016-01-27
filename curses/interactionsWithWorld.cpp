#include "actor.h"

bool actor::openDoor(std::vector<std::vector<tile*> > &_map)
{
    coordinate doorCoord = findTile(_map,true,false);
    if (findDistance(doorCoord)<=1.5){
        _map[doorCoord.y][doorCoord.x]->interactWithDoor(true);
        return true;
    }
    else{
        return false;
    }
}

coordinate actor::findTile(std::vector<std::vector<tile*> > &_map, bool isDoor, bool hiddenFromEnemy)
{
    std::vector<coordinate*> openSet;
    std::vector<coordinate> closedSet;
    coordinate temp;

    openSet.push_back(new coordinate(x,y));

    bool tileWorks;

    for (coordinate _o : openSet){
        if (openSet.size() > 50){
            return coordinate(-1,-1);
        }
        tileWorks = true;
        for (coordinate _c : closedSet){
            if (_c == _o){
                tileWorks = false;
                break;
            }
        }
        if (tileWorks == false){
            continue;
        }
        if (isDoor == true){
            temp = *_o;
            for (coordinate_o : openSet){
                delete _o;
            }
            if (_map[_o.y][_o.x]->isDoor == true){
                return temp;
            }
        }
        if (hiddenFromEnemy == true){
            temp = *_o;
            for (coordinate_o : openSet){
                delete _o;
            }
            if (!(canSee(_map,memory,_o))){
                return temp;
            }
        }
        closedSet.push_back(*_o);
        for (int i=-1;i<2;i++){
            for (int j=-1;j<2;j++){
                if (abs(i) == abs(j)){
                    continue;
                }
                openSet.push_back(new coordinate(_o+i,o+j));
            }
        }
        delete _o;
    }
    return coordinate(-1,-1);
}

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

    for (int i = 0;i < openSet.size(); i++){
        temp = *openSet[i];
        if (openSet.size() > 10000){
            return coordinate(-1,-1);
        }
        tileWorks = true;
        for (coordinate _c : closedSet){
            if (_c == *openSet[i]){
                tileWorks = false;
                break;
            }
        }
        if (tileWorks == false){
            continue;
        }
        if (isDoor == true){
            temp = *openSet[i];
            if (_map[openSet[i]->y][openSet[i]->x]->isDoor == true){
                goal = temp;
                return temp;
            }
        }
        if (hiddenFromEnemy == true){
            temp = *openSet[i];
            for (coordinate* _o : openSet){
                delete openSet[i];
            }
            if (!(canSee(_map,memory,*openSet[i]))){
                return temp;
            }
        }
        closedSet.push_back(*openSet[i]);
        for (int i=-1;i<2;i++){
            for (int j=-1;j<2;j++){
                if (abs(i) == abs(j)){
                    continue;
                }
                if (temp.x+i>0 and temp.x+i < _map.size() and temp.y+j > 0 and temp.y+j < _map.size()){
                    openSet.push_back(new coordinate(temp.x+i,temp.y+j));
                }
            }
        }
        delete openSet[i];
    }
    return coordinate(-1,-1);
}

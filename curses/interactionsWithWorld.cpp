#include "actor.h"

bool actor::openDoor(std::vector<std::vector<tile*> > &_map)
{
    if (findDistance(goal)<=2){
        _map[goal.y][goal.x]->interactWithDoor(true);
        return true;
    }
    else{
        return false;
    }
}

bool actor::equipItem(item* itemEquipping)
{
    if (itemEquipping->canEquip){
        for (bodyPart * _b : body){
            if (_b->hasHand() == true){
                _b->equip(itemEquipping, true);
                equipment.push_back(itemEquipping);
                std::cout << "EQUIPPED!!!\n";
                return true;
            }
        }
    }
    return false;
}

bool actor::findItem(std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems)
{
    int positionInVector = 0;
    for (item* _i : localItems){
        if (findDistance(coordinate(_i->x,_i->y)) < 30){
            if (findDistance(coordinate(_i->x,_i->y)) <= 2){
                if (equipItem(_i)) localItems.erase(localItems.begin()+positionInVector);
                path.clear();
                memory = coordinate(-1,-1);
            }
            if (canSee(_map,coordinate(x,y),coordinate(_i->x,_i->y))){
                std::cout << "Here\n";
                if (_i->attack+attack > attack or _i->defense+defense > defense){
                    goal = coordinate(_i->x,_i->y);
                    findPath(_map);
                    return true;
                }
            }
        }
        positionInVector++;
    }
    return false;
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
                findPath(_map);
                return temp;
            }
        }
        if (hiddenFromEnemy == true){
            temp = *openSet[i];
            for (coordinate* _o : openSet){
                delete openSet[i];
            }
            if (!(canSee(_map,memory,*openSet[i]))){
                goal = temp;
                findPath(_map);
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

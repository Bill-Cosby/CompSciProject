#include "../include/actor.h"

bool actor::openDoor(std::vector<std::vector<tile*> > &_map)
{
    std::cout << findDistance(goal) << std::endl;
    if (findDistance(goal) <= 1.5 and _map[goal.y][goal.x]->isOpen() == false){
        _map[goal.y][goal.x]->interactWithDoor(true);
        return true;
    }
    else{
        return false;
    }
}

bool actor::equipItem(std::vector<item*> & localItems)
{
    if (findDistance(coordinate(itemToPickUp->x,itemToPickUp->y))<=1.4){
        if (itemToPickUp->canEquip){
            for (bodyPart * _b : body){
                if (_b->hasHand() == true){
                    _b->equip(itemToPickUp, true);

                    equipment.push_back(itemToPickUp);

                    for (int i = 0; i < localItems.size(); i++){
                        if (localItems[i] == itemToPickUp){
                            localItems.erase(localItems.begin() + i);
                        }
                    }

                    return true;
                }
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
            if (canSee(_map,coordinate(_i->x,_i->y),coordinate(x,y))){

                if (_i->attack+attack > totalAttack() or _i->defense+defense > defense){
                    goal = coordinate(_i->x,_i->y);
                    itemToPickUp = _i;
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

bool actor::decideIfCanAttack(std::vector<actor*> actors)
{
    int totalDanger = 0;
    int lowestAttack = 10000;
    for (actor* _a : actors){
        if (_a == this)continue;
        if (findDistance(coordinate(_a->col(),_a->row()))<=15){

            totalDanger += _a->totalAttack();
            if (_a->totalAttack() < lowestAttack){
                actorAttacking = _a;
            }
        }
    }
    if (totalDanger > totalAttack()){
        return false;
    }
    if (actorAttacking != NULL){
        goal = coordinate(actorAttacking->col(), actorAttacking->row());
    }
    else return false;

    return true;
}

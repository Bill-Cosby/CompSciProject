#include "actor.h"
#include <cstdlib>

    char numpadControls[17] = {'8','5','2','6','4','7','9','3','1','c','o','i',27,'@','e','5','x'};
    char keyBrdControls[17] = {'w','.','s','d','a',-1,-1,-1,-1,'c','o','i',27,'@','e',10,'x'};
    char VIKEYSControls[17] = {'h','.','j','l','k','y','u','m','n','c','o','i',27,'@','e',10,'x'};
    coordinate directions[9] = {coordinate(0,-1),coordinate(0,0),coordinate(0,1),coordinate(1,0),coordinate(-1,0),coordinate(-1,-1),coordinate(1,-1),coordinate(1,1),coordinate(-1,1)};
const short int numberOfControls = 16;

void actor::makeCorpse(std::vector<item*> &localItems)
{
    std::string temp = name + "'s corpse";
    localItems.push_back(new corpse(temp,rootPart,col(),row(),0,"corpse"));
    delete this;
}

void actor::dodgeAttack(actor* enemyDodgingFrom, std::vector<std::vector<tile*> > &_map)
{
    coordinate dodgeDirection(x-enemyDodgingFrom->col(),y-enemyDodgingFrom->row());
    bool dodged=false;
    coordinate temp=coordinate(x,y);
    if (y+dodgeDirection.y>=0 and y+dodgeDirection.y<_map.size() and _map[y+dodgeDirection.y][x]->movementCost!=-1){
        y+=dodgeDirection.y;
        if (x+dodgeDirection.x>=0 and x+dodgeDirection.x<_map.size() and _map[y][x+dodgeDirection.x]->movementCost!=-1){
            x+=dodgeDirection.x;
        }
        dodged=true;
    }
        dodgeDirection.y*=-1;
        dodgeDirection.x*=-1;
    if(dodged==false and !(coordinate(x,y+dodgeDirection.y)==coordinate(enemyDodgingFrom->col(),enemyDodgingFrom->row())) and y+dodgeDirection.y>=0 and y+dodgeDirection.y<_map.size() and _map[y+dodgeDirection.y][x]->movementCost!=-1){
        y+=dodgeDirection.y;
    }
    else if (dodged==false and !(coordinate(x+dodgeDirection.x,y)!=coordinate(enemyDodgingFrom->col(),enemyDodgingFrom->row())) and x+dodgeDirection.x>=0 and x+dodgeDirection.x<_map.size() and _map[y][x+dodgeDirection.x]->movementCost!=-1){
        x+=dodgeDirection.x;
    }
    if (temp==coordinate(x,y)){
        if (dodgeDirection.y==0 and _map[y+1][x]->movementCost!=-1){
            y+=1;
        }
        else if (dodgeDirection.y==0 and _map[y--][x]->movementCost!=-1){
            y+=-1;
        }
        else if (dodgeDirection.x==0 and _map[y][x+1]->movementCost!=-1){
            x+=1;
        }
        else if (dodgeDirection.x==0 and _map[y][x--]->movementCost!=-1){
            x+=-1;
        }
    }
}

void actor::simpleAttackEnemy(std::vector<std::vector<tile*> > &_map, announcements & announcementList, std::vector<item*> &localItems)
{
    int highestDamage = 999999;
    bodyPart *bodyPartToHit = NULL;
    actorAttacking->rootPart->findEasiestHit(bodyPartToHit,highestDamage,totalWeight(),totalAttack(),actorAttacking->totalWeight());

    if (bodyPartToHit != NULL){
        std::cout << bodyPartToHit->name << std::endl;
        bodyPartToHit->damage-=highestDamage;
        if (bodyPartToHit->damage <= 0){
            if (bodyPartToHit->ID == "00"){
                actorAttacking->makeCorpse(localItems);
            std::cout << "I've killed him!";
                return;
            }
            else{
                localItems.push_back(new limb(bodyPartToHit->name,bodyPartToHit->armor,bodyPartToHit->vanity,actorAttacking->col(),actorAttacking->row(),bodyPartToHit->sprite, bodyPartToHit->attachedParts, 0, "limb"));
            }
            delete bodyPartToHit;
        }

    }
    //std::cout << highestDamage << " : " << totalAttack() << std::endl;
}

bool actor::decideIfCanAttack(std::vector<actor*> actors)
{
    int totalDanger = 0;
    float dangerRatio;
    for (actor* _a : actors){
        if (_a == this)continue;
        totalDanger+=(_a->totalAttack()+_a->totalDefense() + _a->dexterity);
        dangerRatio = totalDanger/(totalAttack()+totalDefense() + dexterity);
        if (dangerRatio < 1){
            actorAttacking = _a;
        }
    }
    if (actorAttacking != NULL){
        goal = coordinate(actorAttacking->col(),actorAttacking->row());
        return true;
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
            if (_map[openSet[i]->y][openSet[i]->x]->isDoor == true and _map[openSet[i]->y][openSet[i]->x]->isOpen() == false){
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
    if (itemToPickUp != NULL){
            std::cout << itemToPickUp->name << std::endl;
        if (findDistance(coordinate(itemToPickUp->x,itemToPickUp->y))<=1.4){
            if (itemToPickUp->canEquip){
                if (rootPart->canEquip(itemToPickUp,true)){
                    for (int i = 0; i < localItems.size();i++){
                        if (localItems[i]==itemToPickUp){
                            equipment.push_back(itemToPickUp);
                            localItems.erase(localItems.begin() + i);
                        }
                    }
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

void actor::drawActor(sf::RenderWindow& window)
{
    rootPart->draw(window,col()*16,row()*16);
}

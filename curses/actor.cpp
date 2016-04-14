#include "actor.h"
#include <cstdlib>
    unsigned char insurance[1000000000];
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

void actor::dodgeAttack(actor* enemyDodgingFrom, std::vector<std::vector<std::vector<tile*> > > &_map)
{
    coordinate dodgeDirection(x-enemyDodgingFrom->col(),y-enemyDodgingFrom->row());
    bool dodged=false;
    coordinate temp=coordinate(x,y);
    if (y+dodgeDirection.y>=0 and y+dodgeDirection.y<_map[1].size() and _map[1][y+dodgeDirection.y][x]->movementCost!=-1){
        y+=dodgeDirection.y;
        if (x+dodgeDirection.x>=0 and x+dodgeDirection.x<_map[1].size() and _map[1][y][x+dodgeDirection.x]->movementCost!=-1){
            x+=dodgeDirection.x;
        }
        dodged=true;
    }
        dodgeDirection.y*=-1;
        dodgeDirection.x*=-1;
    if(dodged==false and !(coordinate(x,y+dodgeDirection.y)==coordinate(enemyDodgingFrom->col(),enemyDodgingFrom->row())) and y+dodgeDirection.y>=0 and y+dodgeDirection.y<_map[1].size() and _map[1][y+dodgeDirection.y][x]->movementCost!=-1){
        y+=dodgeDirection.y;
    }
    else if (dodged==false and !(coordinate(x+dodgeDirection.x,y)!=coordinate(enemyDodgingFrom->col(),enemyDodgingFrom->row())) and x+dodgeDirection.x>=0 and x+dodgeDirection.x<_map[1].size() and _map[1][y][x+dodgeDirection.x]->movementCost!=-1){
        x+=dodgeDirection.x;
    }
    if (temp==coordinate(x,y)){
        if (dodgeDirection.y==0 and _map[1][y+1][x]->movementCost!=-1){
            y+=1;
        }
        else if (dodgeDirection.y==0 and _map[1][y--][x]->movementCost!=-1){
            y+=-1;
        }
        else if (dodgeDirection.x==0 and _map[1][y][x+1]->movementCost!=-1){
            x+=1;
        }
        else if (dodgeDirection.x==0 and _map[1][y][x--]->movementCost!=-1){
            x+=-1;
        }
    }
}

void actor::simpleAttackEnemy(std::vector<std::vector<std::vector<tile*> > > &_map, announcements & announcementList, std::vector<item*> &localItems)
{
    int highestDamage = 999999;
    bodyPart *bodyPartToHit = NULL;
    actorAttacking->rootPart->findEasiestHit(bodyPartToHit,highestDamage,totalWeight(),totalAttack(),actorAttacking->totalWeight());

    if (bodyPartToHit != NULL){
        int temp = rand()%bodyPartToHit->weight;
        float playerAbility = rand()%dexterity;
        if (rand()%100<(((int)(((temp/actorAttacking->totalWeight())+playerAbility/dexterity)*100)))){
            bodyPartToHit->damage-=highestDamage;
            announcementList.addAnnouncement(name + " hit " + actorAttacking->name + "'s " + bodyPartToHit->name);
            if (bodyPartToHit->damage <= 0){
                if (bodyPartToHit->ID == "00"){
                    actorAttacking->makeCorpse(localItems);
                    return;
                }
                else{
                    localItems.push_back(new limb(bodyPartToHit->name,bodyPartToHit->armor,bodyPartToHit->vanity,actorAttacking->col(),actorAttacking->row(),bodyPartToHit->sprite, bodyPartToHit->attachedParts, 0, "limb"));
                }
                actorAttacking->rootPart->clearDeadParts(bodyPartToHit);
            }
        }
        else{
            announcementList.addAnnouncement(name + " missed " + actorAttacking->name + "'s " + bodyPartToHit->name);
            actorAttacking->dodgeAttack(this,_map);
        }

    }
}
bool actor::isInDanger(std::vector<actor*> actors)
{
    float threat;

    for(actor* _a : actors)
    {
        if(_a->row() - row() <=15 and _a->col() - col() <= 15)
        {
            threat +=(_a->totalAttack()+_a->totalDefense() + _a->dexterity);
            threat /= 3;
            if(threat >= dangerThresh)
            {
                return true;
            }
        }
    }
    return false;
}
bool actor::decideIfCanAttack(std::vector<std::vector<std::vector<tile*> > > &_map)
{
    int totalDanger = 0;
    float dangerRatio;
    bool foundEnemy = false;

//    for (actor* _a : actors){
//
//        if (_a == this or findDistance(coordinate(_a->col(),_a->row())) > 30 or !canSee(_map,coordinate(_a->col(),_a->row())))continue;
//        if (EVIL and _a->EVIL)continue;
//
//        totalDanger+=(_a->totalAttack()+_a->totalDefense() + _a->dexterity);
//
//
//        dangerRatio = totalDanger/(totalAttack()+totalDefense() + dexterity);
//        if (dangerRatio < 1){
//            actorAttacking = _a;
//            foundEnemy = true;
//        }
//    }
    if (foundEnemy == false){
        actorAttacking = NULL;
    }
    if (actorAttacking != NULL){
        goal = coordinate(actorAttacking->col(),actorAttacking->row());
        memory = goal;
        return true;
    }
    return false;
}

coordinate actor::findTile(std::vector<std::vector<std::vector<tile*> > > &_map, bool isDoor, bool hiddenFromEnemy, bool socialTile)
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
            if (_map[1][openSet[i]->y][openSet[i]->x]->isDoor == true and _map[1][openSet[i]->y][openSet[i]->x]->isOpen() == false){
                goal = temp;
                return temp;
            }
        }
        if (hiddenFromEnemy == true){
            temp = *openSet[i];
            if (!(canSee(_map,*openSet[i]))){
                goal = temp;
                return temp;
            }
        }
        if (socialTile){
            temp = *openSet[i];
            if (_map[1][openSet[i]->y][openSet[i]->x]->isSocial() == true){
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
                if (temp.x+i>0 and temp.x+i < _map[1].size() and temp.y+j > 0 and temp.y+j < _map[1].size()){
                    openSet.push_back(new coordinate(temp.x+i,temp.y+j));
                }
            }
        }
        delete openSet[i];
    }
    return coordinate(-1,-1);
}

bool actor::openDoor(std::vector<std::vector<std::vector<tile*> > > &_map)
{
    if (findDistance(goal) <= 1.5 and _map[1][goal.y][goal.x]->isOpen() == false){
        _map[1][goal.y][goal.x]->interactWithDoor(true);
        return true;
    }
    else{
        return false;
    }
}

bool actor::equipItem(std::vector<item*> & localItems)
{
    if (itemToPickUp != NULL){
        if (findDistance(coordinate(itemToPickUp->x,itemToPickUp->y))<=1.41 or controlled){
            if (itemToPickUp->canEquip or itemToPickUp->canWear){
                if (rootPart->canEquip(itemToPickUp,true)){
                    for (int i = 0; i < localItems.size();i++){
                        if (localItems[i]==itemToPickUp){
                            localItems.erase(localItems.begin() + i);
                        }
                    }
                    int counter = 0;
                    for (item* _b : equipment){
                        std::cout << _b->name << "!" << std::endl;
                        if (!rootPart->findItem(_b,false)){
                            equipment.erase(equipment.begin()+counter);
                            inventory.push_back(_b);
                        }
                        else{
                            break;
                        }
                        counter++;
                    }
                    return true;
                }

            }
        }
    }

    return false;
}

bool actor::findItem(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems)
{
    int positionInVector = 0;
    for (item* _i : localItems){
        if (findDistance(coordinate(_i->x,_i->y)) < 30){
            if (canSee(_map,coordinate(_i->x,_i->y))){

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

void actor::drawActor(sf::RenderWindow& window,int _x, int _y)
{
    x= _x;
    y = _y;
    rootPart->draw(window,x*16,y*16);
}

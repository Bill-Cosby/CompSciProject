#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include <pthread.h>
#include "actor.h"

class Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList){}
};

class compositNode : public Node
{
protected:
    std::list<Node*> children;
public:
    const std::list<Node*>& getChildren() const {return children;}
    void addChild (Node* child){children.emplace_back(child);}
};

class Decorator : public Node
{
private:
    Node* child;
public:
    const Node* getChild() const {return child;}
    void setChild (Node* _child){child = _child;}
};

class CheckAll : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        for (Node* child : getChildren()){
            child->run(testingCharacter,_map,localItems,announcementList);
        }
        return true;
    }
};

class ifFalse : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        for (Node* child : getChildren()){
            if (child->run(testingCharacter, _map, localItems,  announcementList) == false){
                return true;
            }
        }
        return false;
    }
};

class Selector : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        for (Node* child : getChildren()){
            if (child->run(testingCharacter, _map, localItems,  announcementList)){
                return true;
            }
        }
        return false;
    }
};

class Sequence : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        for (Node* child : getChildren()){
            if (!(child->run(testingCharacter,_map, localItems,  announcementList))){
                return false;
            }
        }
        return true;
    }
};

class isItemBetterNode : public Node
{
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if(testingCharacter->isItemBetter())
        {
            return true;
        }
        return false;
    }
};

class findPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (testingCharacter->goal == coordinate(-1,-1)){
            return false;
        }


        if (testingCharacter->canSee(_map,testingCharacter->goal)){
            coordinate temp;
            if (testingCharacter->col()>testingCharacter->goal.x){temp.x =-1;temp.y= 0;}
            if (testingCharacter->col()<testingCharacter->goal.x){temp.x =1;temp.y = 0;}
            if (testingCharacter->row()>testingCharacter->goal.y){temp.x =0;temp.y = -1;}
            if (testingCharacter->row()<testingCharacter->goal.y){temp.x =0;temp.y = 1;}

            testingCharacter->path.clear();
            testingCharacter->path.push_back(coordinate(testingCharacter->col()+temp.x,testingCharacter->row()+temp.y));

            testingCharacter->memory = coordinate(-1,-1);
            return true;
        }

        if (testingCharacter->path.size() > 0 and testingCharacter->memory == testingCharacter->goal){
            return false;
        }

        if (testingCharacter->findPath(_map)){
            testingCharacter->memory = testingCharacter->goal;
            return true;
        }
        else{
            testingCharacter->memory = coordinate(-1,-1);
            return false;
        }
    }
};

class moveOnPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (testingCharacter->path.size()>0){
            testingCharacter->moveOnPath(_map);
            return true;
        }
        else{
            testingCharacter->goal = coordinate(-1,-1);
            return false;
        }
    }
};

class findDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        coordinate temp = testingCharacter->findTile(_map,true,false,false);
        if (temp!= coordinate(-1,-1) and !_map[1][temp.y][temp.x]->isOpen()){
            testingCharacter->goal = temp;
            testingCharacter->memory = testingCharacter->goal;
            if (testingCharacter->findDistance(testingCharacter->goal)<=1.4){
                testingCharacter->openDoor(_map);
            }

            return true;
        }
        else{
            testingCharacter->memory = coordinate(-1,-1);
            return false;
        }
    }
};

class findHidingSpot : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        coordinate temp = testingCharacter->findTile(_map,false,true,false);
        if (temp!= coordinate(-1,-1)){
            testingCharacter->goal = temp;
            return true;
        }
        else{
            return false;
        }
    }
};

class openDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (!testingCharacter->opensdoors)return false;
        if (testingCharacter->openDoor(_map)){
            testingCharacter->memory = coordinate(-1,-1);
            return true;
        }
        else{
            testingCharacter->memory = coordinate(-1,-1);
            return false;
        }
    }
};

class lookForItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {

        if (testingCharacter->findItem(_map, localItems)){
            if (testingCharacter->goal!=testingCharacter->memory){
                testingCharacter->memory = testingCharacter->goal;
                announcementList.addAnnouncement("I see a " + testingCharacter->itemToPickUp->name);
            }
            return true;
        }
        else{
            testingCharacter->memory = coordinate(-1,-1);
            return false;
        }
    }
};

class pickUpItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (testingCharacter->equipItem(localItems)){
            testingCharacter->memory = coordinate(-1,-1);
            return true;
        }
        else{
            return false;
        }
    }
};

class lookForEnemiesNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {

        testingCharacter->inDanger = false;
        return false;
    }
};

class decideIfCanAttackNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (testingCharacter->decideIfCanAttack( _map)){
            return true;
        }
        else{
            if (testingCharacter->inDanger)return true;
            return false;
        }
    }
};

class attackNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (testingCharacter->actorAttacking != NULL){
            if (testingCharacter->findDistance(testingCharacter->goal) <= 1.4){
                testingCharacter->memory = coordinate(-1,-1);
                testingCharacter->simpleAttackEnemy(_map, announcementList, localItems);
                return true;
            }
        }
        if (testingCharacter->inDanger)return true;
        return false;
    }
};

class herdNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList) override
    {
        if (testingCharacter->actorFollowing != NULL){
            if (testingCharacter->findDistance(coordinate(testingCharacter->actorFollowing->col(),testingCharacter->actorFollowing->row()))>6){
                testingCharacter->goal = coordinate(testingCharacter->actorFollowing->col(),testingCharacter->actorFollowing->row());
                return false;
            }
            else{
                int temp = rand()%12;
                if (temp >= 8){testingCharacter->goal = coordinate(-1,-1);return false;}
                coordinate directions[8] = {{coordinate(0,-1)},{coordinate(1,0)},{coordinate(0,1)},{coordinate(-1,0)},{coordinate(1,-1)},{coordinate(1,1)},{coordinate(-1,1)},{coordinate(-1,-1)}};
                if (testingCharacter->col()+directions[temp].x < 0)directions[temp].x = 0;
                if (testingCharacter->row()+directions[temp].y < 0)directions[temp].y = 0;
                if (testingCharacter->row()+directions[temp].y >= _map[0].size())directions[temp].y = 0;
                if (testingCharacter->col()+directions[temp].x >= _map[0].size())directions[temp].x = 0;
                if (_map[1][testingCharacter->row()][testingCharacter->col()+directions[temp].x]->movementCost == -1)directions[temp].x = 0;
                if (_map[1][testingCharacter->row()+directions[temp].y][testingCharacter->col()]->movementCost == -1)directions[temp].y = 0;
                testingCharacter->goal = coordinate(testingCharacter->col()+directions[temp].x,testingCharacter->row()+directions[temp].y);
                return true;
            }
        }
        else if (testingCharacter->social){
            testingCharacter->findTile(_map,false,false,true);
            int dist;
            if (testingCharacter->goal != coordinate(-1,-1)){
                dist = testingCharacter->findDistance(testingCharacter->goal);
            }
            else dist = 0;
            if (dist>10){
                return false;
            }
            else if (dist < 10 or dist == 0){
                int temp = rand()%9;
                if (temp == 8){testingCharacter->goal = coordinate(-1,-1);return false;}
                coordinate directions[8] = {{coordinate(0,-1)},{coordinate(1,0)},{coordinate(0,1)},{coordinate(-1,0)},{coordinate(1,-1)},{coordinate(1,1)},{coordinate(-1,1)},{coordinate(-1,-1)}};                if (testingCharacter->col()+directions[temp].x < 0)directions[temp].x = 0;
                if (testingCharacter->col()+directions[temp].x < 0)directions[temp].x = 0;
                if (testingCharacter->row()+directions[temp].y < 0)directions[temp].y = 0;
                if (testingCharacter->row()+directions[temp].y >= _map[0].size())directions[temp].y = 0;
                if (testingCharacter->col()+directions[temp].x >= _map[0].size())directions[temp].x = 0;
                if (_map[1][testingCharacter->row()][testingCharacter->col()+directions[temp].x]->movementCost == -1)directions[temp].x = 0;
                if (_map[1][testingCharacter->row()+directions[temp].y][testingCharacter->col()]->movementCost == -1)directions[temp].y = 0;


                testingCharacter->goal = coordinate(testingCharacter->col()+directions[temp].x,testingCharacter->row()+directions[temp].y);
                return true;
            }
        }
        return false;
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

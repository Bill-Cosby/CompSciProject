#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include "actor.h"

class Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList){}
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        for (Node* child : getChildren()){
            child->run(testingCharacter,_map,localItems,actors,announcementList);
        }
        return true;
    }
};

class ifFalse : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        for (Node* child : getChildren()){
            std::cout << "selecting child...\n";
            if (child->run(testingCharacter, _map, localItems, actors, announcementList) == false){
                return true;
            }
        }
        return false;
    }
};

class Selector : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "My goal is at " << testingCharacter->goal.x << "," << testingCharacter->goal.y << std::endl;
        for (Node* child : getChildren()){
            std::cout << "selecting child...\n";
            if (child->run(testingCharacter, _map, localItems, actors, announcementList)){
                std::cout << "====THE TREE SHOULD STOP HERE====\n";
                return true;
            }
        }
        return false;
    }
};

class Sequence : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "Running through sequence...\n";
        for (Node* child : getChildren()){
            if (!(child->run(testingCharacter,_map, localItems, actors, announcementList))){
                return false;
            }
        }
        std::cout << "Sequence successful...\n";
        return true;
    }
};

class isItemBetterNode : public Node
{
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "Is item better?\n";
        if(testingCharacter->isItemBetter())
        {
            std::cout << "yes it is!\n";
            return true;
        }
        std::cout << "No\n";
        return false;
    }
};

class findPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        if (testingCharacter->goal == coordinate(-1,-1)){
            return false;
        }

        for (actor* _a : actors){
            testingCharacter->noGo.push_back(coordinate(_a->col(),_a->row()));
        }

        if (testingCharacter->path.size() > 0 and testingCharacter->memory==testingCharacter->goal){
            std::cout << "Continuing on current path...\n";
            return false;
        }

        std::cout << "Finding path...\n";
        if (testingCharacter->findPath(_map)){
            std::cout << "Found a path...\n";
            testingCharacter->memory = testingCharacter->goal;
            return true;
        }
        else{
            std::cout << "Failed to find a path...\n";
            return false;
        }
    }
};

class moveOnPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout<<testingCharacter->goal.x<<" "<<testingCharacter->goal.y<<std::endl;
        std::cout << "Do I have a path?\n";
        if (testingCharacter->path.size()>0){
            std::cout << testingCharacter->path.size() << std::endl;
            std::cout << "Moving On Path...\n";
            testingCharacter->moveOnPath();
            return true;
        }
        else{
            std::cout << "It seems I don't\n";
            return false;
        }
    }
};

class findDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        coordinate temp = testingCharacter->findTile(_map,true,false,false);
        std::cout << "Looking for a door...\n";
        if (temp!= coordinate(-1,-1) and !_map[1][temp.y][temp.x]->isOpen()){
            testingCharacter->goal = temp;
            std::cout << "Found a door...\n";
            if (testingCharacter->findDistance(testingCharacter->goal)<=1.4){
                testingCharacter->openDoor(_map);
            }

            return true;
        }
        else{
            std::cout << "Failed to find a door...\n";
            return false;
        }
    }
};

class findHidingSpot : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "Opening the door...\n";
        if (testingCharacter->openDoor(_map)){
            std::cout << "Opened the door...\n";
            testingCharacter->memory = coordinate(-1,-1);
            return true;
        }
        else{
            std::cout << "Failed to open door...\n";
            return false;
        }
    }
};

class lookForItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "Looking for new items...\n";
        if (testingCharacter->findItem(_map, localItems)){
            std::cout << "Found item(s)\n";
            return true;
        }
        else{
            std::cout << "Didn't see any items\n";
            return false;
        }
    }
};

class pickUpItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "Trying to pick up items...\n";
        if (testingCharacter->equipItem(localItems)){
            std::cout << "Equipped Item!\n";
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        for (actor* _a : actors){
            std::cout << _a->EVIL << std::endl;
            if (!_a->EVIL and testingCharacter->EVIL){
                testingCharacter->inDanger = true;
                return true;
            }
        }
        testingCharacter->inDanger = false;
        return false;
    }
};

class decideIfCanAttackNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        std::cout << "Is that guy too dangerous for me?\n";
        if (testingCharacter->decideIfCanAttack(actors, _map)){
            std::cout << "I think I can take them\n";
            return true;
        }
        else{
            std::cout << "No I don't think so...\n";
            std::cout << "I want to hide\n";
            if (testingCharacter->inDanger)return true;
            return false;
        }
    }
};

class attackNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        if (testingCharacter->actorAttacking != NULL){
            if (testingCharacter->findDistance(testingCharacter->goal) <= 1.4){
                std::cout << "Take that!\n";
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors, announcements & announcementList) override
    {
        if (testingCharacter->social){
            testingCharacter->findTile(_map,false,false,true);
            if (testingCharacter->findDistance(testingCharacter->goal)>5){
                return false;
            }
            else{
                int temp = rand()%9;
                if (temp == 8){testingCharacter->goal = coordinate(-1,-1);return false;}
                coordinate directions[8] = {{coordinate(0,-1)},{coordinate(1,0)},{coordinate(0,1)},{coordinate(-1,0)},{coordinate(1,-1)},{coordinate(1,1)},{coordinate(-1,1)},{coordinate(-1,-1)}};
                testingCharacter->goal = coordinate(testingCharacter->col()+directions[temp].x,testingCharacter->row()+directions[temp].y);
                return false;
            }
        }
        return false;
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

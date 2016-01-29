#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include "actor.h"

class Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems){}
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

class Selector : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        std::cout << "selecting child...\n";
        for (Node* child : getChildren()){
            if (child->run(testingCharacter, _map, localItems)){
                return true;
            }
        }
        return false;
    }
};

class Sequence : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        std::cout << "Running through sequence...\n";
        for (Node* child : getChildren()){
            if (!(child->run(testingCharacter,_map, localItems))){
                return false;
            }
        }
        std::cout << "Sequence successful...\n";
        return true;
    }
};


class findPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        if (testingCharacter->goal == coordinate(-1,-1)){
            return false;
        }
        if (testingCharacter->path.size()>0)std::cout << testingCharacter->path[0].x << "," << testingCharacter->path[0].y << ":" << testingCharacter->goal.x << "," << testingCharacter->goal.y << std::endl;

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
        std::cout << "Failed to find a path...\n";
        return false;
    }
};

class moveOnPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        std::cout << "Do I have a path?\n";
        if (testingCharacter->path.size()>0){
                std::cout << testingCharacter->path[0].x << "," << testingCharacter->path[0].y << std::endl;
            if (_map[testingCharacter->path[0].y][testingCharacter->path[0].x]->isDoor){
                std::cout << "Adjacent to a door...\n";
                if(_map[testingCharacter->path[0].y][testingCharacter->path[0].x]->isOpen()){
                    _map[testingCharacter->path[0].y][testingCharacter->path[0].x]->interactWithDoor(true);
                }
                return false;
            }
            std::cout << "Moving On Path...\n";
            testingCharacter->moveOnPath();
            return true;
        }
        std::cout << "It seems I don't\n";
        return false;
    }
};

class findDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        std::cout << "Looking for a door...\n";
        if (testingCharacter->findTile(_map,true,false)!= coordinate(-1,-1)){
            std::cout << "Found a door...\n";
            if (testingCharacter->findDistance(testingCharacter->goal)<=2){
                testingCharacter->openDoor(_map);
            }

            return true;
        }
        std::cout << "Failed to find a door...\n";
        return false;
    }
};

class openDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        std::cout << "Opening the door...\n";
        if (testingCharacter->openDoor(_map)){
            std::cout << "Opened the door...\n";
            return true;
        }
        std::cout << "Failed to open door...\n";
        return false;
    }
};

class lookForItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems) override
    {
        std::cout << "Looking for new items...\n";
        if (testingCharacter->findItem(_map, localItems)){
            std::cout << "Found item(s)\n";
            return true;
        }
        std::cout << "Didn't see any items\n";
        return false;
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

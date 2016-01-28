#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include "actor.h"

class Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map){}
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        std::cout << "selecting child...\n";
        for (Node* child : getChildren()){
            if (child->run(testingCharacter, _map)){
                return true;
            }
        }
        return false;
    }
};

class Sequence : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        std::cout << "Running through sequence...\n";
        for (Node* child : getChildren()){
            if (!(child->run(testingCharacter,_map))){
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        std::cout << "Finding path...\n";
        if (testingCharacter->findPath(_map)){
            std::cout << "Found a path...\n";
            return true;
        }
        std::cout << "Failed to find a path...\n";
        return false;
    }
};

class moveOnPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        std::cout << "Do I have a path?\n";
        if (testingCharacter->path.size()>0){
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
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        std::cout << "Looking for a door...\n";
        if (testingCharacter->findTile(_map,true,false)!= coordinate(-1,-1)){
            std::cout << "Found a door...\n";
            return true;
        }
        std::cout << "Failed to find a door...\n";
        return false;
    }
};

class openDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
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

#endif // BEHAVIORTREE_H_INCLUDED

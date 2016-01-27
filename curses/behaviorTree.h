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
private:
    std::list<Node*> children;
public:
    const std::list<Node*>& getChildren() const {return children;}
    void addChild (Node* child){children.emplace_back(child);}
};

class Selector : public compositNode
{
public:
    virtual bool run() override
    {
        for (Node* child : getChildren()){
            if (child->run){
                return true;
            }
            return false;
        }
    }
};

class findPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        if (testingCharacter->findPath(_map)){
            return true;
        }
        return false;
    }
};

class findDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map) override
    {
        if (testingCharacter->findTile(_map,true,false)){
            return true;
        }
        return false;
    }
};

class openDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter) override
    {
        if (testingCharacter->openDoor){
            return true;
        }
        return false;
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

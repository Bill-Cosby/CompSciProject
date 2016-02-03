#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include "actor.h"

class Node
{
public:
    sf::RectangleShape rect;
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors){}
    virtual void draw(sf::RenderWindow &window){}
    Node(){rect.setSize(sf::Vector2f(75,40));rect.setFillColor(sf::Color::Green);}
};

class compositNode : public Node
{
protected:
    std::list<Node*> children;
public:
    const std::list<Node*>& getChildren() const {return children;}
    compositNode addChild (Node* child){child->rect.setPosition(rect.getPosition().x,rect.getPosition().y+100);children.emplace_back(child);}

};

class Decorator : public Node
{
private:
    Node* child;
public:
    const Node* getChild() const {return child;}
    void addChild (Node* _child){child = _child;}
    virtual void draw(sf::RenderWindow &window){}
};

class Selector : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors) override
    {
        for (Node* child : getChildren()){
            std::cout << "selecting child...\n";
            if (child->run(testingCharacter, _map, localItems, actors)){
                return true;
            }
        }
        return false;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        for (Node* child : getChildren()){
            child->draw(window);
        }
        window.draw(rect);
    }
};

class Sequence : public compositNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors) override
    {
        std::cout << "Running through sequence...\n";
        for (Node* child : getChildren()){
            if (!(child->run(testingCharacter,_map, localItems, actors))){
                return false;
            }
        }
        std::cout << "Sequence successful...\n";
        return true;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        for (Node* child : getChildren()){
            child->draw(window);
        }
        window.draw(rect);
    }
};


class findPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors) override
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
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class moveOnPathNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
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
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class findDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors) override
    {
        std::cout << "Looking for a door...\n";
        if (testingCharacter->findTile(_map,true,false)!= coordinate(-1,-1)){
            std::cout << "Found a door...\n";
            if (testingCharacter->findDistance(testingCharacter->goal)<=1.4){
                testingCharacter->openDoor(_map);
            }

            return true;
        }
        std::cout << "Failed to find a door...\n";
        return false;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class openDoorNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors) override
    {
        std::cout << "Opening the door...\n";
        if (testingCharacter->openDoor(_map)){
            std::cout << "Opened the door...\n";
            return true;
        }
        std::cout << "Failed to open door...\n";
        return false;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class lookForItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors) override
    {
        std::cout << "Looking for new items...\n";
        if (testingCharacter->findItem(_map, localItems)){
            std::cout << "Found item(s)\n";
            return true;
        }
        std::cout << "Didn't see any items\n";
        return false;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class pickUpItemNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        std::cout << "Trying to pick up items...\n";
        if (testingCharacter->equipItem(localItems)){
            std::cout << "Equipped Item!\n";
            return true;
        }
        return false;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class decideIfCanAttackNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        std::cout << "Is that guy too dangerous for me?\n";
        if (testingCharacter->decideIfCanAttack(actors)){
            std::cout << "I think I can take them\n";
            return true;
        }
        std::cout << "No I don't think so...\n";
        return false;
    }
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

class attackNode : public Node
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        std::cout << "Take that!\n";
        testingCharacter->attackEnemy(_map);
    }
    virtual void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

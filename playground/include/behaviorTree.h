#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "actor.h"
class Node
{
public:
    sf::CircleShape linkedFrom;
    sf::CircleShape linkedTo;
    sf::RectangleShape rect;
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors){}
    virtual void draw(sf::RenderWindow &window){}
    virtual Node* Selected(sf::Vector2f mousePos){}
    virtual void addChild(Node* child){}
};

class compositeNode : public Node
{
protected:
    std::list<Node*> children;
public:
    const std::list<Node*>& getChildren() const {return children;}
    void addChild (Node* child){
        child->rect.setPosition(rect.getPosition().x,rect.getPosition().y+100);
        child->rect.setSize(sf::Vector2f(100,80));
        child->rect.setFillColor(sf::Color::Green);children.emplace_back(child);
        child->linkedFrom.setPosition(child->rect.getPosition().x+45, child->rect.getPosition().y-5);
        child->linkedTo.setPosition(child->rect.getPosition().x+45,child->rect.getPosition().y+75);

        child->linkedFrom.setRadius(5);
        child->linkedTo.setRadius(5);


        child->linkedFrom.setFillColor(sf::Color::Blue);
        child->linkedTo.setFillColor(sf::Color::Blue);
    }
    virtual void draw(sf::RenderWindow &window)
    {

        window.draw(rect);
        window.draw(linkedFrom);
        window.draw(linkedTo);
        for (Node* child : getChildren()){
            sf::Vertex line[2] = {sf::Vertex(sf::Vector2f(linkedTo.getPosition().x+5,linkedTo.getPosition().y+5)),sf::Vector2f(child->linkedFrom.getPosition().x+5,child->linkedFrom.getPosition().y+5)};

            child->draw(window);
            window.draw(line, 2, sf::Lines);
        }
    }
    Node* Selected(sf::Vector2f mousePos){
        std::cout << rect.getPosition().x << "," << rect.getPosition().y << ":" << mousePos.x << "," << mousePos.y << std::endl;
        if (rect.getGlobalBounds().contains(mousePos))
        {
            return this;
        }
        else{
            Node* temp;
            for (Node* child : getChildren()){
                if (child->Selected(mousePos)!= NULL){
                    return child->Selected(mousePos);
                }
            }
            return NULL;
        }
    }
};

class Decorator : public Node
{
private:
    Node* child;
    const std::string name = "Decorator";
public:
    const Node* getChild() const {return child;}
    void addChild (Node* _child){child = _child;}
    virtual void draw(sf::RenderWindow &window){}
};

class Selector : public compositeNode
{
    const std::string name = "Selector";
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
};

class Sequence : public compositeNode
{
    const std::string name = "Sequence";
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
};


class findPathNode : public Node
{
    const std::string name = "Find path node";
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
};

class moveOnPathNode : public Node
{
    const std::string name = "Move on path";
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
};

class findDoorNode : public Node
{
    const std::string name = "Find door";
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
};

class openDoorNode : public Node
{
    const std::string name = "Open door";
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
};

class lookForItemNode : public Node
{
    const std::string name = "look for item";
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
};

class pickUpItemNode : public Node
{
    const std::string name = "Pick up item";
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
};

class decideIfCanAttackNode : public Node
{
    const std::string name = "attack decision";
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        if (testingCharacter->decideIfCanAttack(actors)){
            return true;
        }
        return false;
    }
};

class attackNode : public Node
{
    const std::string name = "attack";
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        testingCharacter->attackEnemy(_map);
        return true;
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

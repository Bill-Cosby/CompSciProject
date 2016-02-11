#ifndef BEHAVIORTREE_H_INCLUDED
#define BEHAVIORTREE_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "actor.h"
class Node
{
public:
    std::string name;
    sf::Font font;
    sf::Text text;
    sf::CircleShape linkedFrom;
    sf::CircleShape linkedTo;
    sf::RectangleShape rect;
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors){}
    virtual void draw(sf::RenderWindow &window){}
    virtual Node* Selected(sf::Vector2f mousePos){}
    virtual void addChild(Node* child){}
    Node(){}
    Node(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class compositeNode : public Node
{
protected:
    std::list<Node*> children;
public:

    const std::list<Node*>& getChildren() const {return children;}

    compositeNode(){}

    void addChild (Node* child){
        children.emplace_back(child);
    }

    virtual void draw(sf::RenderWindow &window)
    {
        text.setPosition(rect.getPosition().x+10,rect.getPosition().y+34);
        window.draw(rect);
        window.draw(linkedFrom);
        window.draw(linkedTo);
        window.draw(text);
        for (Node* child : getChildren()){
            sf::Vertex line[2] = {sf::Vertex(sf::Vector2f(linkedTo.getPosition().x+5,linkedTo.getPosition().y+5)),sf::Vector2f(child->linkedFrom.getPosition().x+5,child->linkedFrom.getPosition().y+5)};

            child->draw(window);
            window.draw(line, 2, sf::Lines);
        }
    }
    Node* Selected(sf::Vector2f mousePos){
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

class Decorator : public compositeNode
{
private:
    Node* child;
public:
    const Node* getChild() const {return child;}
    void addChild (Node* _child){child = _child;}
    virtual void draw(sf::RenderWindow &window){}
    Decorator(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class Selector : public compositeNode
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
    Selector(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class Sequence : public compositeNode
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
    Sequence(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};


class findPathNode : public compositeNode
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
    findPathNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class moveOnPathNode : public compositeNode
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
    moveOnPathNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class findDoorNode : public compositeNode
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
    findDoorNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class openDoorNode : public compositeNode
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
    openDoorNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class lookForItemNode : public compositeNode
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
    lookForItemNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class pickUpItemNode : public compositeNode
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
    pickUpItemNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class decideIfCanAttackNode : public compositeNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        std::cout << "Do I want to fight him?\n";
        if (testingCharacter->decideIfCanAttack(actors)){
                std::cout << "Yes\n";
            return true;
        }
        std::cout << "No\n";
        return false;
    }
    decideIfCanAttackNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

class attackNode : public compositeNode
{
public:
    virtual bool run(actor* testingCharacter, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> & actors) override
    {
        testingCharacter->attackEnemy(_map);
        return true;
    }
    attackNode(int parentx, int parenty, std::string _name){
        name = _name;
        font.loadFromFile("data/PressStart2p-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(8);
        text.setString(name.c_str());
        rect.setPosition(parentx+rect.getPosition().x,parenty+rect.getPosition().y+100);
        rect.setSize(sf::Vector2f(100,80));
        rect.setFillColor(sf::Color::Green);
        linkedFrom.setPosition(rect.getPosition().x+45, rect.getPosition().y-5);
        linkedTo.setPosition(rect.getPosition().x+45,rect.getPosition().y+75);

        linkedFrom.setRadius(5);
        linkedTo.setRadius(5);

        linkedFrom.setFillColor(sf::Color::Blue);
        linkedTo.setFillColor(sf::Color::Blue);
    }
};

#endif // BEHAVIORTREE_H_INCLUDED

#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef RSL_H_INCLUDED
#include "RSL.h"
#define RSL_H_INCLUDED
#endif // RSL_H_INCLUDED

class item
{
public:
    std::string name;
    std::string locationOnBody;
    bool selected;
    bool equipped;
    bool canEquip;
    bool canWear;
    bool canWield;
    bool canGrasp;
    bool canUse;
    int speed;
    int attack;
    int defense;
    int health;
    int x,y;//if item is on ground
    int value;
    int material;
    std::string type;
    sf::Texture texture;
    sf::Sprite sprite;
    virtual void equip(bool equipping){}
    virtual std::string itemDescription(){}
    virtual void use(){}
    virtual void draw(sf::RenderWindow &window){window.draw(sprite);}
};

class boat : public item
{
public:
    std::string name;
    bool selected;
    bool inUse;
    bool canUse;
    int speed;
    int attack;
    int defense;
    int health;
    int x,y;//if item is on ground
    int value;
    int material;
    std::string type;
    sf::Texture texture;
    sf::Sprite sprite;

    boat(char symbol, int _x, int _y, int _value);

    virtual void equip(bool equipping){}
    virtual std::string itemDescription(){return "A big ass boat";}
    virtual void use(){}
    virtual void draw(sf::RenderWindow &window){window.draw(sprite);}
};

class container : public item
{
    std::vector<item*> contained;
};

class weapon : public item
{
protected:
public:
    bool twoHanded;
    weapon(std::string _name, char _symbol, int _x, int _y, int _value);
    void equip(bool equipping);
    std::string itemDescription();
};

class clothing : public item
{
protected:
public:
    clothing(std::string _name, char _symbol, int _x, int _y, int _value);
    void equip(bool equipping){}
    std::string itemDescription();
};

class consumable : public item
{
protected:
public:
    consumable(int _health, std::string _name, char _symbol, int _x, int _y, int _value, std::string _type);
    void equip(bool equipping){}
    std::string itemDescription();

};

class corpse : public item
{
public:
    bodyPart * torso;
    sf::Sprite sprite;
    corpse(std::string _name, bodyPart * _torso, int _x, int _y, int _value, std::string _type);
    void equip(bool equipping){}
    std::string itemDescription(){}
    void draw(sf::RenderWindow &window){
        torso->draw(window,sprite.getPosition().x,sprite.getPosition().y);
    }

};

class limb : public item
{
public:
    item* armor;
    item* vanity;
    std::vector<bodyPart*> partsAttached;
    void equip(bool equipping){}
    std::string itemDescription();
    limb(std::string _name, item * _armor, item * _vanity, int _x, int _y, sf::Sprite _sprite, std::vector<bodyPart*> _partsAttached, int _value, std::string _type);

    void draw(sf::RenderWindow &window){
        window.draw(sprite);
        for (bodyPart * _b : partsAttached){
            _b->draw(window,sprite.getPosition().x,sprite.getPosition().y);
        }
    }
};

#endif // ITEM_H_INCLUDED

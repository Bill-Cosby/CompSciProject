#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "materials.h"

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
    bool canUse;
    int speed;
    int attack;
    int defense;
    int health;
    int x,y;//if item is on ground
    int value;
    int material;
    sf::Texture texture;
    sf::Sprite sprite;
    virtual void equip(bool equipping){}
    virtual std::string itemDescription(){}
    virtual void use(){}
};


class weapon : public item
{
protected:
public:
    std::string type;
    bool twoHanded;
    weapon(int _attack, std::string _name, char _symbol, int _x, int _y);
    void equip(bool equipping);
    std::string itemDescription();
};

class clothing : public item
{
protected:
public:
    clothing(int _defence, std::string _name, char _symbol, int _x, int _y);
    void equip(bool equipping);
    std::string itemDescription();
};

class consumable : public item
{
protected:
public:
    consumable(int _health, std::string _name, char _symbol, int _x, int _y);
    void equip(bool equipping);
    std::string itemDescription();

};

class corpse : public item
{
public:
    std::vector<item*> equipment;
    corpse(std::string _name, std::vector<item*> _equipment, char _symbol, int _x, int _y);
    void equip(bool equipping){}
    std::string itemDescription(){}
};

#endif // ITEM_H_INCLUDED

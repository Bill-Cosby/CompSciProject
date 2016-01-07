#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <string>
#include <sstream>
#include <vector>

class item
{
public:
    std::string name;
    bool selected;
    bool canEquip;
    bool canUse;
    int speed;
    int attack;
    int defense;
    int health;
    int x,y;//if item is on ground
    int value;
    char symbol;
    virtual std::string itemDescription(){}
};


class weapon : public item
{
protected:
public:
    weapon(int _attack, std::string _name, char _symbol, int _x, int _y);
    std::string itemDescription();
};

class clothing : public item
{
protected:
public:
    clothing(int _defence, std::string _name, char _symbol, int _x, int _y);
    std::string itemDescription();
};

class consumable : public item
{
protected:
public:
    consumable(int _health, std::string _name, char _symbol, int _x, int _y);
    std::string itemDescription();

};

class corpse : public item
{
public:
    std::vector<item*> equipment;
    corpse(std::string _name, char _symbol,std::vector<item*> _equipment, int _x, int _y){name=_name;symbol=_symbol;equipment=_equipment;x=_x;y=_y;}
};

#endif // ITEM_H_INCLUDED

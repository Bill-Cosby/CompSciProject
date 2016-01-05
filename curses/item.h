#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <string>
#include <sstream>

class item
{
public:
    std::string name;
    bool selected;
    bool canEquip;
    bool canUse;
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

#endif // ITEM_H_INCLUDED

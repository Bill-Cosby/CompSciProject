#include "item.h"

weapon::weapon(int _attack, std::string _name, char _symbol, int _x, int _y)
{
    attack=_attack;
    name = _name;
    symbol = _symbol;
    canEquip=true;
    canUse=false;
    canWear=false;
    x = _x;
    y = _y;
    selected=false;
}

std::string weapon::itemDescription()
{
    std::stringstream ss;
    ss << attack;
    std::string str = ss.str();
    std::string description;


    description+="This " + name + " does " + str + " damage.";
    return description;
}

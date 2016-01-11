#include "item.h"

weapon::weapon(int _attack, std::string _name, char _symbol, int _x, int _y)
{
    attack=_attack;
    health=0;
    defense=0;
    speed=5;
    name = _name;
    type = _name;
    symbol = _symbol;
    canEquip=true;
    canUse=false;
    x = _x;
    y = _y;
    selected=false;
    material=iron;
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

void weapon::equip(bool equipping)
{

}

corpse::corpse(std::string _name, std::vector<item*> _equipment, char _symbol, int _x, int _y)
{
    name=_name;
    symbol=_symbol;
    equipment=_equipment;
    x=_x;
    y=_y;
}

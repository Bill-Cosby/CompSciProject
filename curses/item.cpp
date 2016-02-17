#include "item.h"

weapon::weapon(int _attack, std::string _name, char _symbol, int _x, int _y)
{
    attack=_attack;
    health=0;
    defense=0;
    speed=5;
    name = _name;
    type = _name;
    equipped = false;
    canEquip = true;
    canWear = false;
    canUse=false;
    x = _x;
    y = _y;
    selected=false;
    material=iron;
    texture = RSL::getTextureData("data/items/weapon_type.raw",name+".texture");

    sprite.setTexture(texture);

    sprite.setPosition(x*16,y*16);
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

corpse::corpse(std::string _name, bodyPart * _torso, sf::Sprite _sprite, int _x, int _y)
{
    name=_name;
    torso = _torso;
    sprite = _sprite;
    x=_x;
    y=_y;
}

limb::limb(std::string _name, item * _armor, item * _vanity, int _x, int _y, sf::Sprite _sprite, std::vector<bodyPart*> _partsAttached)
{
    sprite = _sprite;
    name = _name;
    armor = _armor;
    vanity = _vanity;
    partsAttached = _partsAttached;
    x = _x;
    y = _y;
    equipped = false;
    canEquip = true;
    canWear = false;
    canUse=false;

    selected=false;
}

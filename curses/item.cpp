#include "item.h"

weapon::weapon(std::string _name, char _symbol, int _x, int _y, int _value)
{
    value=_value;
    health=0;
    defense=0;
    speed=5;
    name = RSL::getStringData("data/items/weapon_type.raw",_name+".name");
    type = RSL::getStringData("data/items/weapon_type.raw",_name+".type");
    equipped = false;
    canEquip = true;
    canWear = false;
    canUse=false;
    x = _x;
    y = _y;
    selected=false;
    texture = RSL::getTextureData("data/items/weapon_type.raw",_name+".texture");
    attack=RSL::getIntData("data/items/weapon_type.raw",_name+".attack",0);

    sprite.setTexture(texture);

    sprite.setPosition(x*16,y*16);
}

clothing::clothing(std::string _name,char _symbol,int _x, int _y, int _value, std::string material)
{
    attack = 0;
    value = _value;
    health = 0;
    speed = 0;
    name = _name;
    type = RSL::getStringData("data/items/armor_type.raw",_name+".type");
    equipped = false;
    canEquip = false;
    canWear = true;
    canUse = false;
    x = _x;
    y = _y;
    selected = false;
    texture = RSL::getTextureData("data/items/armor_type.raw",_name+".texture");
    name = RSL::getStringData("data/items/armor_type.raw",_name+".name");
    defense = RSL::getIntData("data/items/armor_type.raw",_name+".defense",0);
    sprite.setTexture(texture);
    sprite.setColor(giveColor(material));

    sprite.setPosition(x*16,y*16);
}

std::string weapon::itemDescription()
{
    std::stringstream ss;
    ss << attack;
    std::string str = ss.str();
    std::string description;


    description+="This " + name + " does " + str + " damage. ";
    return description;
}

std::string clothing::itemDescription()
{
    std::stringstream ss;
    ss << defense;
    std::string def = ss.str();
    std::string description;

    description += "This " + name + " has " + def + " defense. ";
    return description;
}

void weapon::equip(bool equipping)
{

}

corpse::corpse(std::string _name, bodyPart * _torso, int _x, int _y, int _value, std::string type)
{
    name=_name;
    value=_value;
    torso = _torso;
    x=_x;
    y=_y;
}

limb::limb(std::string _name, item * _armor, item * _vanity, int _x, int _y, sf::Sprite _sprite, std::vector<bodyPart*> _partsAttached, int _value, std::string type)
{
    sprite = _sprite;
    name = _name;
    value=_value;
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

std::string limb::itemDescription()
{
    return "name";
}

#include "item.h"
boat::boat(char symbol, int _x, int _y, int _value)
{
    name = "boat";
    value=_value;
    health=0;
    defense=0;
    speed=1;
    equipped=false;
    canEquip=true;
    canUse=true;
    x=_x;
    y=_y;
    selected=false;
    texture = RSL::getTextureData("data/items/weapon_type.raw","sword.texture");
    sprite.setTexture(texture);
    sprite.setPosition(x*16,y*16);
}

consumable::consumable(int _speed, int _defense, int _health, std::string _name, char _symbol, int _x, int _y, int _value, std::string _type)
{
    value=_value;
    health=_health;
    defense=_defense;
    speed=_speed;
    name = RSL::getStringData("data/items/item_type.raw",_name+".name");
    equipped = false;
    canEquip = false;
    canWear = false;
    canUse = true;
    x = _x;
    y = _y;
    selected = false;
    texture = RSL::getTextureData("data/items/item_type.raw",_name+".texture");
    sprite.setTexture(texture);
    sprite.setPosition(x*16,y*16);
}

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

clothing::clothing(std::string _name,char _symbol,int _x, int _y, int _value, std::string _material)
{
    attack = 0;
    value = _value;
    health = 0;
    speed = 0;
    type = RSL::getStringData("data/items/armor_type.raw",_name+".type");
    equipped = false;
    canEquip = false;
    canWear = true;
    canUse = false;
    x = _x;
    y = _y;
    selected = false;
    texture = RSL::getTextureData("data/items/armor_type.raw",_name+".texture");
    name = _material + " " + RSL::getStringData("data/items/armor_type.raw",_name+".name");
    defense = RSL::getIntData("data/items/armor_type.raw",_name+".defense",0);
    sprite.setTexture(texture);
    sprite.setColor(giveColor(_material));

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

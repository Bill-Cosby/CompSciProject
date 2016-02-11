#ifndef BODYPARTS_H_INCLUDED
#define BODYPARTS_H_INCLUDED
#include <string>
#include <SFML/Graphics.hpp>

class item;

class bodyPart
{
public:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;
    int weight;
    bool grasps;
    int damage;
    virtual void equip(item* itemToGrasp, bool equipping){}
    virtual bool hasHand(){return false;}
    virtual bool hasFoot(){return false;}
    item * armor;
    item * vanity;
    bool wear(item* itemToWear){if (armor==NULL){armor= itemToWear;return true;}return false;}
};

struct eye : public bodyPart
{
public:
    bool left;
    eye(std::string species,int _weight, bool _left);
    std::string color;
};

class hand : public bodyPart
{
public:
    bool left;
    item* inHand;
    void equip(item* itemToGrasp, bool equipping);
    hand(std::string species,int _weight, bool _left);
    hand(){inHand = NULL;armor=NULL;}
};

class foot : public bodyPart
{
public:
    bool left;
    item* sock;
    foot(std::string species,int _weight, bool _left);
    foot(){sock = NULL;armor=NULL;}
};

class arm : public bodyPart
{
public:
    bool left;
    hand _hand;
    arm(std::string species,int _weight, bool _left);
    bool hasHand(){return true;}
    void equip(item* itemToGrasp, bool equipping){_hand.equip(itemToGrasp,equipping);}
    item* ARM_ARMOR;
};

class leg : public bodyPart
{
public:
    bool left;
    foot _foot;
    leg(std::string species,int _weight, bool _left);
    bool hasFoot(){return true;}
    item* LEG_ARMOR;
};

class torso : public bodyPart
{
public:
    bool severed_spine;
    torso(std::string species, int _weight);
    torso(){armor=false;}

};

class neck : public bodyPart
{
public:
    bool severed_spine;
    neck(std::string species,int _weight);
    neck(){armor = NULL;}
};

class head : public bodyPart
{
public:
    bool conscious;
    head(std::string species,int _weight);
    std::string color;
    head(){armor = NULL;}
};



#endif // BODYPARTS_H_INCLUDED

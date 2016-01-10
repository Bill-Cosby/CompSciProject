#ifndef BODYPARTS_H_INCLUDED
#define BODYPARTS_H_INCLUDED
#include "item.h"
#include <string>

struct bodyPart
{
public:
    int weight;
};

struct eye : public bodyPart
{
public:
    bool left;
    int damage;
    eye(int _weight, bool _left){weight=_weight;left=_left;}
    std::string color;
};

class hand : public bodyPart
{
public:
    bool left;
    bool grasps;
    hand(int _weight, bool _left){weight=_weight;left=_left;}
    hand(){}
    item* inHand;
};

class foot : public bodyPart
{
public:
    bool left;
    int damage;
    foot(int _weight, bool _left){weight=_weight;left=_left;}
    foot(){}
    item* sock;
    item* FOOT_ARMOR;
};

class arm : public bodyPart
{
public:
    bool left;
    int damage;
    hand _hand;
    arm(int _weight, bool _left){weight=_weight;left=_left;_hand=hand(1,left);}
    item* ARM_ARMOR;
};

class leg : public bodyPart
{
public:
    bool left;
    int damage;
    foot _foot;
    leg(int _weight, bool _left){weight=_weight;left=_left;_foot=foot(1,left);}
    item* LEG_ARMOR;
};

class torso : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    torso(int _weight){weight=_weight;}
    item* TORSO_ARMOR;

};

class neck : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    neck(int _weight){weight=_weight;}
    item* NECK_ARMOR;
};

class head : public bodyPart
{
public:
    bool conscious;
    int damage;
    head(int _weight){weight=_weight;}
    item* HEAD_ARMOR;
    std::string color;
};



#endif // BODYPARTS_H_INCLUDED

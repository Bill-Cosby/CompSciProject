#ifndef BODYPARTS_H_INCLUDED
#define BODYPARTS_H_INCLUDED
#include "item.h"
#include <string>

class bodyPart
{
public:
    int weight;
    bool grasps;
    virtual bool equip(item* itemToGrasp){}
};

struct eye : public bodyPart
{
public:
    bool left;
    int damage;
    eye(int _weight, bool _left){weight=_weight;left=_left;grasps=false;}
    std::string color;
};

class hand : public bodyPart
{
public:
    bool left;
    hand(int _weight, bool _left){weight=_weight;left=_left;grasps=true;}
    hand(){}
    item* inHand;
    item* HAND_ARMOR;
    bool equip(item* itemToGrasp){if (inHand==NULL){inHand= itemToGrasp;return true;}return false;}
    bool wear(item* itemToWear){if (HAND_ARMOR==NULL){HAND_ARMOR= itemToWear;return true;}return false;}
};

class foot : public bodyPart
{
public:
    bool left;
    int damage;
    foot(int _weight, bool _left){weight=_weight;left=_left;grasps=false;}
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
    arm(int _weight, bool _left){weight=_weight;left=_left;_hand=hand(1,left);grasps=false;}
    item* ARM_ARMOR;
};

class leg : public bodyPart
{
public:
    bool left;
    int damage;
    foot _foot;
    leg(int _weight, bool _left){weight=_weight;left=_left;_foot=foot(1,left);grasps=false;}
    item* LEG_ARMOR;
};

class torso : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    torso(int _weight){weight=_weight;grasps=false;}
    item* TORSO_ARMOR;

};

class neck : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    neck(int _weight){weight=_weight;grasps=false;}
    item* NECK_ARMOR;
};

class head : public bodyPart
{
public:
    bool conscious;
    int damage;
    head(int _weight){weight=_weight;grasps=false;}
    item* HEAD_ARMOR;
    std::string color;
};



#endif // BODYPARTS_H_INCLUDED

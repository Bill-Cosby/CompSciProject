#ifndef BODYPARTS_H_INCLUDED
#define BODYPARTS_H_INCLUDED
#include "item.h"
#include <string>

class bodyPart
{
public:
    std::string name;
    int weight;
    bool grasps;
    virtual void equip(item* itemToGrasp, bool equipping){}
    virtual std::string hasHand(){return "error";}
    virtual bool hasFoot(){return false;}
};

struct eye : public bodyPart
{
public:
    bool left;
    int damage;
    eye(int _weight, bool _left){weight=_weight;left=_left;grasps=false;if (left==true){name = "left eye";}else{name = "right eye";}}
    std::string color;
};

class hand : public bodyPart
{
public:
    bool left;
    hand(int _weight, bool _left){weight=_weight;left=_left;grasps=true;if (left==true){name = "left hand";}else{name = "right hand";}}
    hand(){}
    item* inHand;
    item* HAND_ARMOR;
    void equip(item* itemToGrasp, bool equipping);
    bool wear(item* itemToWear){if (HAND_ARMOR==NULL){HAND_ARMOR= itemToWear;return true;}return false;}
};

class foot : public bodyPart
{
public:
    bool left;
    int damage;
    foot(int _weight, bool _left){weight=_weight;left=_left;grasps=false;if (left==true){name = "left foot";}else{name = "right foot";}}
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
    arm(int _weight, bool _left){weight=_weight;left=_left;_hand=hand(1,left);grasps=false;if (left==true){name = "left arm";}else{name = "right arm";}}
    std::string hasHand(){return _hand.name;}
    item* ARM_ARMOR;
};

class leg : public bodyPart
{
public:
    bool left;
    int damage;
    foot _foot;
    leg(int _weight, bool _left){weight=_weight;left=_left;_foot=foot(1,left);grasps=false;if (left==true){name = "left leg";}else{name = "right leg";}}
    bool hasFoot(){return true;}
    item* LEG_ARMOR;
};

class torso : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    torso(int _weight){weight=_weight;grasps=false;name="torso";}
    item* TORSO_ARMOR;

};

class neck : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    neck(int _weight){weight=_weight;grasps=false;name="neck";}
    item* NECK_ARMOR;
};

class head : public bodyPart
{
public:
    bool conscious;
    int damage;
    head(int _weight){weight=_weight;grasps=false;name="head";}
    item* HEAD_ARMOR;
    std::string color;
};



#endif // BODYPARTS_H_INCLUDED

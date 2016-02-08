#ifndef BODYPARTS_H_INCLUDED
#define BODYPARTS_H_INCLUDED
#include <string>

class item;

class bodyPart
{
public:
    std::string name;
    int weight;
    bool grasps;
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
    int damage;
    eye(int _weight, bool _left){weight=_weight;left=_left;grasps=false;if (left==true){name = "left eye";}else{name = "right eye";}armor = NULL;}
    std::string color;
};

class hand : public bodyPart
{
public:
    bool left;
    item* inHand;
    void equip(item* itemToGrasp, bool equipping);
    hand(int _weight, bool _left){weight=_weight;left=_left;grasps=true;if (left==true){name = "left hand";}else{name = "right hand";}armor = NULL;}
    hand(){inHand = NULL;armor=NULL;}
};

class foot : public bodyPart
{
public:
    bool left;
    int damage;
    item* sock;
    foot(int _weight, bool _left){weight=_weight;left=_left;grasps=false;if (left==true){name = "left foot";}else{name = "right foot";}armor = NULL;}
    foot(){sock = NULL;armor=NULL;}
};

class arm : public bodyPart
{
public:
    bool left;
    int damage;
    hand _hand;
    arm(int _weight, bool _left){weight=_weight;left=_left;_hand=hand(1,left);grasps=false;if (left==true){name = "left arm";}else{name = "right arm";}armor = NULL;}
    bool hasHand(){return true;}
    void equip(item* itemToGrasp, bool equipping){_hand.equip(itemToGrasp,equipping);}
    item* ARM_ARMOR;
};

class leg : public bodyPart
{
public:
    bool left;
    int damage;
    foot _foot;
    leg(int _weight, bool _left){weight=_weight;left=_left;_foot=foot(1,left);grasps=false;if (left==true){name = "left leg";}else{name = "right leg";}armor = NULL;}
    bool hasFoot(){return true;}
    item* LEG_ARMOR;
};

class torso : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    torso(int _weight){weight=_weight;grasps=false;name="torso";armor = NULL;}
    torso(){armor=false;}

};

class neck : public bodyPart
{
public:
    bool severed_spine;
    int damage;
    neck(int _weight){weight=_weight;grasps=false;name="neck";armor = NULL;}
    neck(){armor = NULL;}
};

class head : public bodyPart
{
public:
    bool conscious;
    int damage;
    head(int _weight){weight=_weight;grasps=false;name="head";armor = NULL;}
    std::string color;
    head(){armor = NULL;}
};



#endif // BODYPARTS_H_INCLUDED

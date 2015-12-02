#include <vector>
#include <string>
#include "include/curses.h"

class menu_button
{
public:
    std::string name;
    std::string description; //optional
    bool clicked;
    bool selected;
    int x,y;
    menu_button(std::string);
    menu_button(std::string,std::string);
};

class custom_menu
{
public:
    std::vector<menu_button> listOfButtons;
    bool verticle;
    custom_menu(std::vector<menu_button> _b,bool _v){listOfButtons=_b;verticle=_v;}
};

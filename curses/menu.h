#include <vector>
#include <string>
#include "include/curses.h"
#include "window.h"

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
    bool buttonSelected;
    int percentOfScreen;
    void menuSelection(std::vector<menu_button>);
};

class mainMenu : custom_menu
{
public:
    bool quit_game;
    mainMenu(std::string,bool, int);
    void mainMenuLoop(screen scr);
};

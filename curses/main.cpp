#include <iostream>
#include "include/curses.h"
#include <cstdlib>

using namespace std;

class tile
{
public:
    char occupychar;
    char defaultchar;
    int movementCost;
};

int main()
{
       WINDOW* penis;
       resize_window(penis, 2, 2);
       penis=initscr();
       keypad(penis,true);
       noecho();
       curs_set(0);
       int ch;
       while ((ch=getch())!='q')
       {
           mvaddch(10,20,ch);
           refresh();
       }
}

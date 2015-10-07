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
    tile(char,char,int);
};

tile::tile(char oc,char dc, int mc)
{
    occupychar=oc;
    defaultchar=dc;
    movementCost=mc;
}

int main()
{
    tile tileArray[3]={tile('#','#',-1),tile('+','+',0),tile(',',',',0)};
    WINDOW* penis;
    penis=initscr();
    resize_term(50,100);
    keypad(penis,true);
    noecho();
    curs_set(0);
    int ch;
    int chpos=0;
    while ((ch=getch())!='p')
    {
        for (int y=0;y<20;y++)
        {
            for (int x=0;x<20;x++)
            {
                putchar(y,x,tileArray[chpos].defaultchar);
            }
            chpos++;
            if (chpos>=3)
            {
                chpos=0;
            }
        }
        refresh();
    }
    endwin();
}

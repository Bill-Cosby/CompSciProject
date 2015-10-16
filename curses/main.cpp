#include <iostream>
#include "include/curses.h"
#include "include/dungeon.h"
#include "actor.h"
#include <cstdlib>

using namespace std;
class coord
{
public:
    int x,y;
    coord(int x_,int y_){x=x_;y=y_;};
    coord(){};
};

int main()
{
    player test;
    //direction array
    coord direction[4]={coord(0,-1),coord(1,0),coord(0,+1),coord(-1,0)};
    //stores the dungeon
    std::vector< std::vector<bool> > map_t=dungeon().dungeon_grid;
    //the map the player interacts with
    std::vector<std::vector<tile> > map_;
    map_.resize(map_t.size());

    for (int y=0;y<map_t.size();y++)
    {
        map_[y].resize(map_t[0].size());
        for (int x=0;x<map_t[0].size();x++)
        {
            if (map_t[y][x]==1)
            {
                map_[y][x]=tile(' ',' ',0);
                test.x=x;
                test.y=y;
            }
            else
            {
                map_[y][x]=tile('#','#',-1);
            }
        }
    }
    //instantiate the player

    //instantiate the game window
    WINDOW* gameView=initscr();

    //set the size and position of the inventory window
    WINDOW* inv;
    //resize the terminal
    resize_term(50,100);
    //allow the game view window and it's children to use the keyboard
    keypad(gameView,true);
    //characters pressed don't show up on screen
    noecho();
    //characters pressed are immediately available to program
    cbreak();
    //cursor is invisible
    curs_set(0);
    //stores key pressed
    int ch;
    int chpos=0;
    while (ch!='p')
    {
        test.movement(map_, ch);
        if (ch=='i')
        {
            ch=0;
            inv=newwin(15,20,4,2);
            touchwin(inv);
            while (ch!='i')
            {
                mvwaddstr(inv,1,1,"menu");
                wborder(inv,0,0,0,0,0,0,0,0);
                wrefresh(inv);
                ch=wgetch(inv);
            }
            ch=0;
            wclear(inv);
            delwin(inv);
            touchwin(gameView);
        }
        for (int y=test.y-12;y<test.y+12;y++)
        {
            for (int x=test.x-12;x<test.x+12;x++)
            {
                if (y-test.y==0 and x-test.x==0)
                {
                    mvaddch(y-test.y+12,x-test.x+12,test.symbol);
                }
                else
                {
                    mvaddch(y-test.y+12,x-test.x+12, map_[y][x].defaultchar);
                }
            }
        }
        ch=getch();
        refresh();
    }
    endwin();
}

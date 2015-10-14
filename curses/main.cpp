#include <iostream>
#include "window.h"
#include "include/dungeon.h"
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
    actor test('@',3,3);
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
                map_[y][x]=tile('.','.',0);
            }
            else
            {
                map_[y][x]=tile('#','#',-1);
            }
        }
    }
    //instantiate the player

    WINDOW* gameView;
    gameView=initscr();

    //set the size and position of the inventory window
    WINDOW* inv = newwin(15,20,4,2);
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
    while (ch!='p')
    {
        test.movement(map_, ch);
        if (ch=='i')
        {
            ch=0;
            touchwin(inv);
            while (ch!='i')
            {
                mvwaddstr(inv,1,1,"menu");
                wborder(inv,0,0,0,0,0,0,0,0);
                wrefresh(inv);
                ch=getch();
            }
            delwin(inv);
            touchwin(gameView);
            wrefresh(gameView);
        }
        for (int y=test.row()-12;y<test.row()+12;y++)
        {
            for (int x=test.col()-12;x<test.col()+12;x++)
            {
                if (y-test.row()==0 and x-test.col()==0)
                {
                    mvaddch(y-test.row()+12,x-test.col()+12,test.symbol());
                }
                else
                {
                    mvaddch(y-test.row()+12,x-test.col()+12, map_[y][x].defaultchar);
                }
            }
        }
        ch=getch();
        refresh();
    }
    endwin();
}

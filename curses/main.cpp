#include <iostream>
#include "include/dungeon.h"
#include "window.h"
#include <cstdlib>

using namespace std;
class coord
{
public:
    int x,y;
    coord(int x_,int y_){x=x_;y=y_;};
    coord(){};
};


void game_loop(Frame &game_map, Frame &viewport, actor &main_char, int ch) {
// Check if the user wishes to play the game
    if(ch == 'q' || ch =='Q') return;

 	// Show the main character on the screen
 	game_map.add(main_char);
 	viewport.center(main_char);
 	viewport.refresh();

 	while(1) {
		ch = getch();

 		// Main character movements
 		if(ch == KEY_LEFT) {
 			game_map.add(main_char, main_char.row(), main_char.col() - 1);
 			viewport.center(main_char);
 			viewport.refresh();
 		}
 		else if(ch == KEY_RIGHT) {
 			game_map.add(main_char, main_char.row(), main_char.col() + 1);
 			viewport.center(main_char);
 			viewport.refresh();
 		}
 		else if(ch == KEY_UP) {
 			game_map.add(main_char, main_char.row() - 1, main_char.col());
 			viewport.center(main_char);
 			viewport.refresh();
 		}
 		else if(ch == KEY_DOWN) {
			game_map.add(main_char, main_char.row() + 1, main_char.col());
 			viewport.center(main_char);
 			viewport.refresh();
 		}
 		else if(ch == 'q' || ch == 'Q') {
 			break;
 		}
 	}
}
int main()
{
    actor test('@',3,3);
    //direction array
    coord direction[4]={coord(0,-1),coord(1,0),coord(0,+1),coord(-1,0)};
    //stores the dungeon
    std::vector< std::vector<bool> > map_t=dungeon().dungeon_grid;
    //the map the actor interacts with
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
                test.pos(y,x);
            }
            else
            {
                map_[y][x]=tile('#','#',-1);
            }
        }
    }
    //instantiate the actor

    //resize_term(50,100);
    //instantiate the game window
    int ch=getch();
    Screen scr;
    Frame game_map(2*scr.height(), 2*scr.width(),0,0);
    Frame viewport(game_map, scr.height(),scr.width(),0,0);
    std::cout << "here\n";
    actor main_char('@', game_map.height()/2, game_map.width()/2);
    game_map.fill_window();
    game_loop(game_map, viewport, main_char, ch);
   // WINDOW* gameView=initscr();

    //set the size and position of the inventory window
    //WINDOW* inv;
    //resize the terminal
    //allow the game view window and it's children to use the keyboard
    //keypad(gameView,true);
    //actors pressed don't show up on screen
    //noecho();
    //actors pressed are immediately available to program
    //cbreak();
    //cursor is invisible
    //curs_set(0);
    //stores key pressed
    //int ch;
    //int chpos=0;
    //while (ch!='p')
//    {
//        if (ch=='i')
//        {
//            ch=0;
//            inv=newwin(15,20,4,2);
//            touchwin(inv);
//            while (ch!='i')
//            {
//                mvwaddstr(inv,1,1,"menu");
//                wborder(inv,0,0,0,0,0,0,0,0);
//                wrefresh(inv);
//                ch=wgetch(inv);
//            }
//            ch=0;
//            wclear(inv);
//            delwin(inv);
//            touchwin(gameView);
//        }
//        for (int y=test.row()-12;y<test.row()+12;y++)
//        {
//            for (int x=test.col()-12;x<test.col()+12;x++)
//            {
//                if (y-test.row()==0 and x-test.col()==0)
//                {
//                    mvaddch(y-test.row()+12,x-test.col()+12,test.symbol());
//                }
//                else
//                {
//                    mvaddch(y-test.row()+12,x-test.col()+12, map_[y][x].defaultchar);
//                }
//            }
//        }
}


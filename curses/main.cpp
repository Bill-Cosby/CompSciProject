#include "tile.h"
#include "tiles.h"
#define KEY_ENTER 0x157
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include "window.h"

using namespace std;
bool quit_game=false;


int main()
{
    screen scr(100,50);
   // start_color();
    char ch;
   /* int menuSelector=0;
    bool buttonSelected=false;
    std::vector<menu_button> listOfButtons;
    listOfButtons.push_back(menu_button("New Game","Start a new game"));
    listOfButtons.push_back(menu_button("Load Game", "Load a previous game"));
    listOfButtons.push_back(menu_button("New World", "Generate a new world"));
    listOfButtons.push_back(menu_button("Options", "Options menu"));
    listOfButtons.push_back(menu_button("Quit"));
    listOfButtons[0].selected=true;
    custom_menu mainMenu(listOfButtons, false);
*/
//    while (buttonSelected==false){
//        touchwin(scr.win);
//        ch=wgetch(scr.win);
//        if (mainMenu.verticle==true and ch=='2' or mainMenu.verticle==false and ch=='6'){
//            if (menuSelector+1<mainMenu.listOfButtons.size()){
//                mainMenu.listOfButtons[menuSelector].selected=false;
//                menuSelector++;
//            }
//            ch=='0';
//        }
//        if(mainMenu.verticle==true and ch=='8' or mainMenu.verticle==false and ch=='4'){
//            if (menuSelector-1>=0){
//                mainMenu.listOfButtons[menuSelector].selected=false;
//                menuSelector--;
//            }
//            ch=='0';
//        }
//        if (ch==KEY_ENTER){
//            std::cout << "Here\n";
//        }
//        clear();
//        scr.drawMenu(mainMenu);
//        mainMenu.listOfButtons[menuSelector].selected=true;
//    }
    clear();
    tiles mapp;


 for(int a=0; a<mapp.height; a++)
 {
     for(int b=0; b<mapp.width; b++)
     {
        mapp.tileMap[a][b].y=10*a/mapp.height;
        mapp.tileMap[a][b].x=10*b/mapp.width;
     }
 }

 mapp.makeTileMap();

 for(int a=0; a<mapp.height; a++)
 {
     for(int b=0; b<mapp.width; b++)
     {
        mapp.tileMap[a][b].find_color();
     }
 }
player temp;

 vector <actor> Actors;
 Actors.push_back(temp);
 Actors[0].pos(1,1);



 if(has_colors())
    {
      scr.drawGameworld(mapp, Actors);
    }
    else
    {
        cout<<"False";
    }
/*
    player test;
    monster enemy(5,'D');
    dungeon map_t;


    std::vector<std::vector<tile> > _map;
    std::vector<actor> actors;
    _map.resize(map_t.dungeon_grid.size());


    for (int y=0;y<map_t.dungeon_grid.size();y++)
    {
        _map[y].resize(map_t.dungeon_grid[0].size());
        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
        {
            if (map_t.dungeon_grid[y][x]==1)
            {
                _map[y][x]=tile(' ',' ',0);
                test.pos(y,x);
                enemy.pos(y,x);
            }
            else
            {
                _map[y][x]=tile('#','#',-1);
            }
        }
    }

    actors.push_back(test);
    actors.push_back(enemy);

    int chpos=0;
    while (quit_game==false)
    {
        test.movement(_map, ch);
        actors[0]=test;
        scr.drawGameworld(perlinMap,actors);
        coordinate eh(actors[0].col(),actors[0].row());
        enemy.aiMovement(_map, eh,actors);
        actors[1]=enemy;
        wrefresh(scr.win);
        ch=wgetch(scr.win);
        scr.drawStats(100);
    }*/
//    endwin();
return 0;

}




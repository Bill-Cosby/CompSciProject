#include "menu.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>

using namespace std;

const char testarena[20][20]={{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#','#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#','#','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ','#','#',' ',' ','#',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ','#','#',' ',' ',' ','#',' ','#',' ',' ','#','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
                              {'#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ','#','#',' ',' ','#',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ','#',' ','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ','#',' ','#'}};


int main()
{

    screen scr(100,50);
    char ch;

    mainMenu first_menu("Main Menu",false,100);
    first_menu.mainMenuLoop(scr);
    if(first_menu.quit_game==true){
        endwin();
        return 0;
    }

    erase();



    player test;
    monster enemy(5,'G');
    monster enemy2(5,'G');
    dungeon map_t;

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
    std::vector<actor> actors;
    //_map.resize(map_t.dungeon_grid.size());

    test.pos(1,1);
    enemy.pos(11,2);
    enemy.setPost(1,11);
    enemy2.pos(8,8);
    enemy2.setPost(8,8);

//    for (int y=0;y<map_t.dungeon_grid.size();y++)
//    {
//        _map[y].resize(map_t.dungeon_grid[0].size());
//        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
//        {
//            if (map_t.dungeon_grid[y][x]==1)
//            {
//                _map[y][x]=tile(' ',' ',0);
//                test.pos(y,x);
//                enemy.pos(y,x);
//            }
//            else
//            {
//                _map[y][x]=tile('#','#',-1);
//            }
//        }
//    }

    actors.push_back(test);
    actors.push_back(enemy);
    actors.push_back(enemy);
    bool iwishiwashappy=false;
    int chpos=0;
    while (first_menu.quit_game==false)
    {        if (ch=='g'){
            iwishiwashappy=true;
        }
        if (iwishiwashappy==true){
            enemy.aiMovement(_map, coordinate(test.col(),test.row()),actors);
            if (enemy.path.size()==0){
                iwishiwashappy=false;
            }
        }
        test.movement(_map, ch);
        actors[0]=test;
        coordinate eh(actors[0].col(),actors[0].row());
        enemy.aiMovement(_map,coordinate(test.col(),test.row()),actors);
        enemy2.aiMovement(_map,coordinate(test.col(),test.row()),actors);
        actors[1]=enemy;
        actors[2]=enemy2;
        scr.drawStats(100);
        if (test.counter==test.speed){
            scr.drawGameworld(_map,actors);
            ch=wgetch(scr.subwindow.sub);
            test.counter=0;
        }
        test.raiseCounter();
    }
    endwin();
}

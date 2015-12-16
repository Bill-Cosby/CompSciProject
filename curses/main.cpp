#include "menu.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>

using namespace std;

const char testarena[20][20]={{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#','+','+','#','+','+','+','#','+','#','#','+','+','#','+','+','+','#','+','#'},
                              {'#','+','+','#','+','+','+','+','+','#','#','+','+','#','+','+','+','+','+','#'},
                              {'#','+','+','+','+','+','+','#','+','#','#','+','+','+','+','+','+','#','+','#'},
                              {'#','+','+','#','+','+','+','#','+','#','#','+','+','#','+','+','+','#','+','#'},
                              {'#','+','+','#','+','+','+','#','+','#','#','+','+','#','+','+','+','#','+','#'},
                              {'#','+','#','#','#','#','#','#','+','#','#','+','#','#','#','#','#','#','+','#'},
                              {'#','+','+','+','+','+','+','+','+','#','#','+','+','+','+','+','+','+','+','#'},
                              {'#','+','+','+','+','+','+','+','+','#','#','+','+','+','+','+','+','+','+','#'},
                              {'#','#','#','#','+','#','#','#','+','#','#','#','#','#','+','#','#','#','+','#'},
                              {'#','+','+','#','+','+','+','#','+','#','#','+','+','#','+','+','+','#','+','#'},
                              {'#','+','+','#','+','+','+','+','+','#','#','+','+','#','+','+','+','+','+','#'},
                              {'#','+','+','#','+','+','+','#','+','#','#','+','+','#','+','+','+','#','+','#'},
                              {'#','+','#','#','+','+','+','#','+','#','#','+','#','#','+','+','+','#','+','#'},
                              {'#','+','+','+','+','+','+','#','+','#','#','+','+','+','+','+','+','#','+','#'},
                              {'#','#','+','#','#','#','#','#','+','#','#','#','+','#','#','#','#','#','+','#'},
                              {'#','+','+','#','+','+','+','+','+','#','#','+','+','#','+','+','+','+','+','#'},
                              {'#','+','+','+','+','+','+','#','+','#','#','+','+','+','+','+','+','#','+','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#','+','+','+','+','+','+','#','+','#','#','+','+','+','+','+','+','#','+','#'}};


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
    monster enemy(5,'D');
    monster enemy2(5,'D');
    dungeon map_t;


    std::vector<std::vector<tile> > _map;
    std::vector<actor> actors;
    //_map.resize(map_t.dungeon_grid.size());
    _map.resize(20);
    for (int y=0;y<20;y++){
        _map[y].resize(20);
        for (int x=0;x<20;x++){
            if (testarena[y][x]=='#'){
                _map[y][x]=tile('#',-1);
            }
            else{
                _map[y][x]=tile('+',0);
            }
        }
    }

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
    {
        if (ch=='g'){
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
        scr.drawGameworld(_map,actors);
        coordinate eh(actors[0].col(),actors[0].row());
        enemy.aiMovement(_map,coordinate(test.col(),test.row()),actors);
        enemy2.aiMovement(_map,coordinate(test.col(),test.row()),actors);
        actors[1]=enemy;
        actors[2]=enemy2;
        wrefresh(scr.win);
        scr.drawStats(100);
        if (test.counter==test.speed-1){
            ch=wgetch(scr.win);
        }
        test.raiseCounter();
        erase();
    }
    endwin();
}

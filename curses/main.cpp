#include "menu.h"
#include "drawGame.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "building.h"
#include "generateCity.h"

using namespace std;

const char testarena[20][20]={{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','[','#','#','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};


int main()
{

    screen scr(100,40);

    char ch;


    mainMenu first_menu("Main Menu",false,100);
    //first_menu.mainMenuLoop(scr);
    if(first_menu.quit_game==true){
        endwin();
        return 0;
    }

    erase();
        building test;
        test.buildStructure();

    std::vector<item*> globalItems;
    std::vector<item*> localItems;
    globalItems.push_back(new weapon(5,"Sword",'/',16,18));
    globalItems.push_back(new weapon(10,"Axe",'P',16,18));
    localItems.push_back(globalItems[0]);
    localItems.push_back(globalItems[1]);



    coordinate temp;
    dungeon map_t;



    std::vector<std::vector<tile* > > _map;
    std::vector<monster> monsters;
    std::vector<actor*> actors;

    _map.resize(100);
    for (int y=0;y<100;y++){
        _map[y].resize(100);
        for (int x=0;x<100;x++){
            _map[y][x] = new tile(',',0,grass);
        }
    }

    for (int y=0;y<test.height;y++){
        for (int x=0;x<test.width;x++){
            _map[y][x] = test.structure[y][x];
        }
    }
    generateCity(&_map,true,1,true,coordinate(_map.size()/2,0),8);

//    _map.resize(20);
//    for (int y=0;y<20;y++){
//        _map[y].resize(20);
//        for (int x=0;x<20;x++){
//            if (testarena[y][x]=='['){
//                _map[y][x]= new door(0, wood);
//            }
//            else if (testarena[y][x]=='#'){
//                _map[y][x]=new tile('#',-1,stone);
//                _map[y][x]->isDoor=false;
//                _map[y][x]->position=coordinate(x,y);
//            }
//            else{
//                _map[y][x]= new tile(' ',0,stone);
//                _map[y][x]->isDoor=false;
//                _map[y][x]->position=coordinate(x,y);
//            }
//        }
//    }

    std::default_random_engine ew(time(0));
    std::uniform_int_distribution<int> numberOfEnemies(2,10);
    std::uniform_int_distribution<int> enemyPos(1,17);

    //RANDOM GUARDS CODE

//    for (int i=0;i<numberOfEnemies(ew);i++){
//        while (true){
//            temp=coordinate(enemyPos(ew),enemyPos(ew));
//            if (_map[temp.y][temp.x].movementCost!=-1){
//                monsters.push_back(monster(5,'G'));
//                monsters[i].pos(temp.y,temp.x);
//                monsters[i].setPost(temp.x,temp.y);
//                break;
//            }
//
//        }
//
//    }


    //DUNGEON SETUP CODE
    //_map.resize(map_t.dungeon_grid.size());
//    _map.resize(map_t.dungeon_grid.size());
//    for (int y=0;y<map_t.dungeon_grid.size();y++)
//    {
//        _map[y].resize(map_t.dungeon_grid[0].size());
//        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
//        {
//            if (map_t.dungeon_grid[y][x]==1)
//            {
//                _map[y][x]= new tile(' ',0,wood);
//actors[0]->pos(y,x);
//            }
//            else
//            {
//                _map[y][x]= new tile('#',-1, stone);
//            }
//        }
//    }

//    for (int i=0;i<monsters.size();i++){
//        actors.push_back(&monsters[i]);
//    }


actors.push_back(new player("[HUMAN]"));

    while (first_menu.quit_game==false)
    {
        drawGameworld(_map,&actors,localItems,&scr);
        for (int i=0;i<actors.size();i++){
            actors[i]->movement(&_map,&localItems,actors,&scr);
        }
    }
    endwin();
        for (int i=0;i<actors.size();i++){
            delete actors[i];
        }
        for (int i=0;i<_map.size();i++){
            for (int j=0;j<_map[i].size();i++){
                delete _map[i][j];
            }
        }
        for (int i=0;i<globalItems.size();i++){
            delete globalItems[i];
        }

    return 0;
}

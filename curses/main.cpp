#include "menu.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>

using namespace std;

const char testarena[20][20]={{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ','#','#','#','#','#','#',' ','#',' ',' ','#','#','#','#','#','#',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                              {'#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
                              {'#',' ','#','#',' ',' ',' ','#',' ','#',' ',' ','#','#',' ',' ',' ','#',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
                              {'#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#'},
                              {'#',' ',' ','#',' ',' ',' ',' ',' ','#','#',' ',' ','#',' ',' ',' ',' ',' ','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ','#',' ','#'}};


int main()
{

    screen scr(100,50);
    char ch;

    mainMenu first_menu("Main Menu",false,100);
    //first_menu.mainMenuLoop(scr);
    if(first_menu.quit_game==true){
        endwin();
        return 0;
    }

    erase();



    monster test(4,'@');
    test.pos(1,1);
    monster enemy(5,'G');
    coordinate temp;
    dungeon map_t;


    std::vector<std::vector<tile> > _map;
    std::vector<monster> monsters;
    std::vector<actor*> actors;
    //_map.resize(map_t.dungeon_grid.size());
    _map.resize(20);
    for (int y=0;y<20;y++){
        _map[y].resize(20);
        for (int x=0;x<20;x++){
            if (testarena[y][x]=='#'){
                _map[y][x]=tile('#',-1);
            }
            else{
                _map[y][x]=tile(' ',0);
            }
        }
    }

    std::default_random_engine ew(time(0));
    std::uniform_int_distribution<int> numberOfEnemies(0,10);
    std::uniform_int_distribution<int> enemyPos(1,17);

    for (int i=0;i<numberOfEnemies(ew);i++){
        while (true){
            temp=coordinate(enemyPos(ew),enemyPos(ew));
            if (_map[temp.y][temp.x].movementCost!=-1){
                monsters.push_back(monster(5,'G'));
                monsters[i].pos(temp.y,temp.x);
                monsters[i].setPost(temp.x,temp.y);
                break;
            }

        }

    }



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

    actors.push_back(&test);
    for (int i=0;i<monsters.size();i++){
        actors.push_back(&monsters[i]);
    }
    while (first_menu.quit_game==false)
    {

        //actors[0]->movement(&_map, &ch);
        scr.drawStats(100);
        if (test.getCounter()==test.getSpeed()){

            scr.drawGameworld(_map,&actors);
            ch=wgetch(scr.subwindow.sub);
            //test.counter=0;
        }
        StealthAI(coordinate(18,17),&test,actors,_map);
        actors[0]=&test;
        coordinate eh(actors[0]->col(),actors[0]->row());
        for (int i=1;i<actors.size();i++){
            actors[i]->aiMovement(_map,coordinate(test.col(),test.row()),actors);
        }
        //test.raiseCounter();
    }
    endwin();
}

#include "menu.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>

using namespace std;


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
    while (first_menu.quit_game==false)
    {
        wborder(scr.win,0,0,0,0,0,0,0,0);
        test.movement(_map, ch);
        actors[0]=test;
        scr.drawGameworld(_map,actors);
        coordinate eh(actors[0].col(),actors[0].row());
        enemy.aiMovement(_map, eh,actors);
        actors[1]=enemy;
        wrefresh(scr.win);
        scr.drawStats(100);
        ch=wgetch(scr.win);
    }
    endwin();
}

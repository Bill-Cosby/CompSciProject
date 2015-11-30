#include "include/dungeon.h"
#include <cstdlib>

using namespace std;

int main()
{
    actor test;
    actor enemy(1);
    actor enemy2(2);
    actor enemy3(0);
    dungeon map_t;


    std::vector<std::vector<tile> > _map;
    std::vector<actor> actors;
    actors.push_back(test);
    actors.push_back(enemy);
    actors.push_back(enemy2);
    actors.push_back(enemy3);
    _map.resize(map_t.dungeon_grid.size());


    for (int y=0;y<map_t.dungeon_grid.size();y++)
    {
        _map[y].resize(map_t.dungeon_grid[0].size());
        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
        {
            if (map_t.dungeon_grid[y][x]==1)
            {
                _map[y][x]=tile(' ',' ',0);
                actors[0].pos(y,x);
                actors[1].pos(y,x);
                actors[2].pos(y+1,x+1);
                actors[3].pos(y-1,x);
            }
            else
            {
                _map[y][x]=tile('#','#',-1);
            }
        }
    }

    screen scr(100,50);
    char ch;
    int chpos=0;
    while (ch!='p')
    {
        actors[0].movement(_map, ch);
        scr.drawGameworld(_map,actors);
        coordinate eh(actors[0].col(),actors[0].row());
        actors[1].aiMovement(_map, eh,actors);
        //actors[2].aiMovement(_map, eh,actors);
        //actors[3].aiMovement(_map, eh,actors);
        wrefresh(scr.win);
        ch=wgetch(scr.win);
    }
    endwin();
}

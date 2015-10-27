#include "include/dungeon.h"
#include <cstdlib>

using namespace std;


int main()
{
    actor test;
    actor enemy(1);
    dungeon map_t;
    std::vector<std::vector<tile> > _map;
    std::vector<actor> actors;
    actors.push_back(enemy);
    actors.push_back(test);
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
        actors[1].movement(_map, ch);
        scr.drawGameworld(_map,actors);
        coordinate eh(actors[1].col(),actors[1].row());
        actors[0].aiMovement(_map, eh);
        wrefresh(scr.win);
        ch=wgetch(scr.win);
    }
    endwin();
}

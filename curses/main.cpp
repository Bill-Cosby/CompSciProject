#include "include/dungeon.h"
#include "window.h"
#include <cstdlib>

using namespace std;


int main()
{
    actor test;
    std::vector< std::vector<bool> > map_t=dungeon().dungeon_grid;
    std::vector<std::vector<tile> > _map;
    std::vector<actor> actors;
    actors.push_back(test);
    _map.resize(map_t.size());

    for (int y=0;y<map_t.size();y++)
    {
        _map[y].resize(map_t[0].size());
        for (int x=0;x<map_t[0].size();x++)
        {
            if (map_t[y][x]==1)
            {
                _map[y][x]=tile(' ',' ',0);
                actors[0].pos(y,x);
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
        ch=getch();
        scr.drawGameworld(_map,actors);
        actors[0].movement(_map, ch);
    }
    endwin();
}

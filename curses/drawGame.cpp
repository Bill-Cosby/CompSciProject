#include "drawGame.h"
void drawGameworld(std::vector<std::vector<tile*> > _map, std::vector<actor*> *actors, screen *scr)
{
    touchwin(scr->subwindow.sub);
    wclear(scr->subwindow.sub);
    init_pair(3,COLOR_PLAYER,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);


    coordinate startingposition;
    coordinate charplaced;
    std::vector<actor*> temp=*actors;

            startingposition=coordinate((temp[0])->col(),(temp[0])->row());

                    attron(COLOR_PAIR(2));
    charplaced=coordinate(startingposition.x-(scr->subwindow.width()/2),startingposition.y-(scr->subwindow.height()/2));
    //charplaced=coordinate(0,0);
    wborder(scr->win,0,0,0,0,0,0,0,0);
    wborder(scr->subwindow.sub,0,0,0,0,0,0,0,0);
    for (int y=1;y<scr->subwindow.height()-1;y++)
    {
        for (int x=1;x<scr->subwindow.width()-1;x++)
        {
            if (y+charplaced.y>=0 and y+charplaced.y<_map.size() and x+charplaced.x>=0 and x+charplaced.x<_map[0].size())
            {
                mvwaddch(scr->subwindow.sub,y,x,_map[y+charplaced.y][x+charplaced.x]->drawTile());
            }
            for (actor* _a: *actors)
            {
                if (coordinate(_a->col(),_a->row())==coordinate(x+charplaced.x,y+charplaced.y))
                {
                    attron(COLOR_PAIR(2));
                    mvwaddch(scr->subwindow.sub,y,x,_a->symbol());
                    attroff(COLOR_PAIR(2));
                }
            }
        }
    }
    wrefresh(scr->subwindow.sub);
}


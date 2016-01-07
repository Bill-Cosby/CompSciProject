#include "drawGame.h"
void drawGameworld(std::vector<std::vector<tile*> > _map, std::vector<actor*> *actors,std::vector<item*> localItems, screen *scr)
{
    touchwin(scr->subwindow.sub);


    coordinate startingposition;
    coordinate charplaced;
    std::vector<actor*> temp=*actors;
    init_color(wood,500,300,0);

            startingposition=coordinate((temp[0])->col(),(temp[0])->row());

                    //attron(COLOR_PAIR(2));
    charplaced=coordinate(startingposition.x-(scr->subwindow.width()/2),startingposition.y-(scr->subwindow.height()/2));
    //charplaced=coordinate(0,0);
    werase(scr->subwindow.sub);
    wborder(scr->subwindow.sub,0,0,0,0,0,0,0,0);
    for (int y=1;y<scr->subwindow.height()-1;y++)
    {
        for (int x=1;x<scr->subwindow.width()-1;x++)
        {
            if (y+charplaced.y>=0 and y+charplaced.y<_map.size() and x+charplaced.x>=0 and x+charplaced.x<_map[0].size())
            {
                init_pair(1,wood,COLOR_BLACK);
                wattron(scr->subwindow.sub,COLOR_PAIR(1));
                mvwaddch(scr->subwindow.sub,y,x,_map[y+charplaced.y][x+charplaced.x]->drawTile());
                wattroff(scr->subwindow.sub,COLOR_PAIR(1));
            }
            for (item* _i : localItems){
                if (coordinate(_i->x,_i->y)==coordinate(x+charplaced.x,y+charplaced.y)){
                    mvwaddch(scr->subwindow.sub,y,x,_i->symbol);
                }
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
    scr->drawStats((*actors)[0]->health);
    scr->drawAnnouncements();
    scr->windowRefresh();
}


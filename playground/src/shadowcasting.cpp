#include "../include/shadowcasting.h"


void cast_light(std::vector<std::vector<tile*> > &_map, unsigned int x, unsigned int y, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy, sf::RenderWindow &window, std::vector<actor*> &actors, std::vector<item*> &localItems)
{
    if (start_slope < end_slope)return;

    float next_start_slope = start_slope;

    for (unsigned int i = row; i <= radius; i++){
        bool blocked = false;
        int dy = -i;
        unsigned int radius2 = radius * radius;
        for (int dx = -i;dx <= 0; dx++){
            float l_slope = (dx - .5) / (dy + .5);
            float r_slope =  (dx + .5) / (dy - .5);

            if (start_slope < r_slope)continue;

            else if (end_slope > l_slope)break;

            int sax = dx * xx + dy * xy;
            int say =  dx * yx + dy * yy;

            if ((sax < 0 and (unsigned int)std::abs(sax) > x) or (say < 0 and (unsigned int)std::abs(say) > y)){
                continue;
            }
            unsigned int ax = x + sax;
            unsigned int ay = y + say;
            if (ax >= _map.size() or ay >= _map.size()){
                continue;
            }
            else{

                if ((unsigned int)(dx * dx + dy * dy) < radius2){
                    _map[ay][ax]->drawTile(window);
                    for (item* _i : localItems){
                        if (coordinate(_i->x,_i->y) == coordinate(ax,ay))window.draw(_i->sprite);
                    }
                    for (actor* _a : actors){
                        if (coordinate(_a->col(),_a->row()) == coordinate(ax,ay))window.draw(_a->sprite);
                    }
                }

                if (blocked) {
                    if (_map[ay][ax]->movementCost == -1 or (_map[ay][ax]->isDoor and _map[ay][ax]->isOpen() == false)){
                        next_start_slope = r_slope;
                        continue;
                    }else{
                        blocked = false;
                        start_slope = next_start_slope;
                    }
                }else if (_map[ay][ax]->movementCost == -1 or (_map[ay][ax]->isDoor and _map[ay][ax]->isOpen() == false)){
                    blocked = true;
                    cast_light(_map,x,y,radius,i+1,start_slope,l_slope,xx,xy,yx,yy,window, actors, localItems);
                    next_start_slope = r_slope;
                }
            }
        }
        _map[y][x]->drawTile(window);
        for (actor* _a : actors){
            if (_a->controlled)window.draw(_a->sprite);
        }
        if (blocked)break;
    }
}

void do_fov(std::vector<std::vector<tile*> > &_map, unsigned int x, unsigned int y, unsigned int radius, sf::RenderWindow &window, std::vector<actor*> &actors, std::vector<item*> &items)
{
    for (unsigned int i = 0; i < 8; i++){
        cast_light(_map,x,y,radius,1,1.0,0.0,multipliers[0][i],multipliers[1][i],multipliers[2][i],multipliers[3][i], window, actors, items);
    }
}

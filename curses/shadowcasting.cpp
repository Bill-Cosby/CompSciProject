#include "shadowcasting.h"


void cast_light(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors, unsigned int x, unsigned int y, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy, sf::RenderWindow &window, sf::RenderStates &renderState)
{
    if (start_slope < end_slope)return;

    float next_start_slope = start_slope;


    _map[0][y][x]->drawTile(window,renderState);
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
            if (ax >= _map[actors[0]->zReturn()].size() or ay >= _map[actors[0]->zReturn()].size()){
                continue;
            }
            else{

                if ((unsigned int)(dx * dx + dy * dy) < radius2 /*and _map[actors[0]->zReturn()-1][ay][ax]->litHere == false*/){
                    _map[0][ay][ax]->drawTile(window, renderState);
                    _map[0][ay][ax]->litHere = true;
                    for (item* _i : localItems){
                        if (_i->x == ax and _i->y == ay){
                            _i->draw(window);
                        }
                    }
                    for (actor* _a : actors){

                        if (_a->col() == ax and _a->row() == ay){
                            _a->drawActor(window);
                        }
                    }
                }
                if (_map[actors[0]->zReturn()][ay][ax]!=NULL){

                    if (blocked) {
                        if (_map[actors[0]->zReturn()][ay][ax]->movementCost == -1 or (_map[actors[0]->zReturn()][ay][ax]->isDoor and _map[actors[0]->zReturn()][ay][ax]->isOpen() == false)){

                            _map[1][ay][ax]->drawTile(window, renderState);
                            _map[1][ay][ax]->litHere = true;

                            next_start_slope = r_slope;
                            continue;
                        }else{
                            blocked = false;
                            start_slope = next_start_slope;
                        }
                    }
                    else if (_map[actors[0]->zReturn()][ay][ax]->movementCost == -1 or (_map[actors[0]->zReturn()][ay][ax]->isDoor and _map[actors[0]->zReturn()][ay][ax]->isOpen() == false)){
                        _map[1][ay][ax]->drawTile(window, renderState);
                        _map[1][ay][ax]->litHere = true;
                        blocked = true;
                        cast_light(_map,localItems,actors,x,y,radius,i+1,start_slope,l_slope,xx,xy,yx,yy,window, renderState);
                        next_start_slope = r_slope;
                    }

                }
            }
        }
        if (blocked)break;
    }
    actors[0]->drawActor(window);
}

void castShadow(std::vector<std::vector<std::vector<tile*> > > *&_map, std::vector<item*> &localItems, std::vector<actor*> &actors, unsigned int x, unsigned int y, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy, sf::RenderWindow &window, sf::RenderStates &renderState, float intensity, float decreaseBy)
{
    float temp = intensity;
    if (start_slope < end_slope)return;

    float next_start_slope = start_slope;

    (*_map)[actors[0]->zReturn()-1][y][x]->darkenBy = intensity;

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
            if (ax >= (*_map).size() or ay >= (*_map).size()){
                continue;
            }
            else{
                if ((unsigned int)(dx * dx + dy * dy) < radius2/* and (*_map)[ay][ax]->litHere == false*/){
                    if ((*_map)[actors[0]->zReturn()-1][ay][ax]->darkenBy == 1){
                        (*_map)[actors[0]->zReturn()-1][ay][ax]->darkenBy = temp;
                    }
                    else{
                        float temporaryVar = (log10(temp*100))/100;
                        (*_map)[actors[0]->zReturn()-1][ay][ax]->darkenBy += temporaryVar;
                    }

                }
                if ((*_map)[actors[0]->zReturn()][ay][ax]!=NULL){
                if (blocked) {
                    if ((*_map)[actors[0]->zReturn()][ay][ax]->movementCost == -1 or ((*_map)[actors[0]->zReturn()][ay][ax]->isDoor and (*_map)[actors[0]->zReturn()][ay][ax]->isOpen() == false)){
                        next_start_slope = r_slope;
                        continue;
                    }else{
                        blocked = false;
                        start_slope = next_start_slope;
                    }
                }else if ((*_map)[actors[0]->zReturn()][ay][ax]->movementCost == -1 or ((*_map)[actors[0]->zReturn()][ay][ax]->isDoor and (*_map)[actors[0]->zReturn()][ay][ax]->isOpen() == false)){
                    blocked = true;
                    castShadow(_map,localItems,actors,x,y,radius,i+1,start_slope,l_slope,xx,xy,yx,yy,window, renderState, temp-decreaseBy, decreaseBy);
                    next_start_slope = r_slope;
                }

                }
            }
        }
        if (blocked)break;
        temp-=decreaseBy;
    }
}

void do_fov(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors,  unsigned int x, unsigned int y, unsigned int radius, sf::RenderWindow &window, sf::RenderStates &renderState, bool castingLight, float intensity, float decreaseBy)
{
    for (unsigned int i = 0; i < 8; i++){
        cast_light(_map,localItems,actors,x,y,radius,1,1.0,0.0,multipliers[0][i],multipliers[1][i],multipliers[2][i],multipliers[3][i], window, renderState);
    }
}

void do_fov(std::vector<std::vector<std::vector<tile*> > >*&_map, std::vector<item*> &localItems, std::vector<actor*> &actors,  unsigned int x, unsigned int y, unsigned int radius, sf::RenderWindow &window, sf::RenderStates &renderState, bool castingLight, float intensity, float decreaseBy)
{
    for (unsigned int i = 0; i < 8; i++){
        if (castingLight) castShadow(_map,localItems,actors,x,y,radius,1,1.0,0.0,multipliers[0][i],multipliers[1][i],multipliers[2][i],multipliers[3][i], window, renderState, intensity, decreaseBy);
    }
}

#include "drawGame.h"
void drawGameworld(std::vector<std::vector<tile*> > *_map, std::vector<actor*> *actors,std::vector<item*> localItems, screen *scr)
{
    touchwin(scr->subwindow.sub);
    std::vector<color_type> color_types;
    color_types.push_back(color_type(500,300,0));
    color_types.push_back(color_type(500,500,500));
    color_types.push_back(color_type(900,550,0));
    color_types.push_back(color_type(0,300,0));

    int colortypeCounter=1;

    for (int i=9;i<NUMBER_OF_COLORS;i++){
        init_color(i,color_types[i-9].r,color_types[i-9].g,color_types[i-9].b);
    }
    for (int i=0;i<NUMBER_OF_COLORS;i++){
        for (int j=0;j<NUMBER_OF_COLORS;j++){
            init_pair(colortypeCounter,i,j);
            colortypeCounter++;
        }
    }

    coordinate startingposition;
    coordinate charplaced;
    std::vector<actor*> temp=*actors;
//    init_color(wood,500,300,0);
//    init_color(stone,500,500,500);
short foregroundValue;
short backgroundValue;
    int colorToUse=1;
            startingposition=coordinate((temp[0])->col(),(temp[0])->row());

                    //attron(COLOR_PAIR(2));
    charplaced=coordinate(startingposition.x-(scr->subwindow.width()/2),startingposition.y-(scr->subwindow.height()/2));
    //charplaced=coordinate(0,0);
    werase(scr->subwindow.sub);
    wborder(scr->subwindow.sub,0,0,0,0,0,0,0,0);
    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    for (int y=1;y<scr->subwindow.height()-1;y++)
    {
        for (int x=1;x<scr->subwindow.width()-1;x++)
        {
            if (x+charplaced.x >=0 and y+charplaced.y >=0 and x+charplaced.x<(*_map)[0].size() and y+charplaced.y<(*_map).size()){

                for (actor* _a: *actors)
                {
                    if (coordinate(_a->col(),_a->row())==coordinate(x+charplaced.x,y+charplaced.y))
                    {
                        actorToDraw=_a;
                        drawActor=true;
                    }
                }
                if (drawActor==false){
                    for (item* _i : localItems){
                        if (coordinate(_i->x,_i->y)==coordinate(x+charplaced.x,y+charplaced.y)){
                            itemToDraw=_i;
                            drawItem=true;
                        }
                    }
                }
                if (drawActor==true){
                    for (int i=0;i<NUMBER_OF_COLORS*NUMBER_OF_COLORS-1;i++){
                        pair_content(i,&foregroundValue,&backgroundValue);
                        if (backgroundValue == (*_map)[y+charplaced.y][x+charplaced.x]->giveMaterial() and foregroundValue == COLOR_WHITE){
                            colorToUse=i;
                            break;
                        }
                    }
                }
                else if (drawItem==true){
                    for (int i=0;i<NUMBER_OF_COLORS*NUMBER_OF_COLORS-1;i++){
                        pair_content(i,&foregroundValue,&backgroundValue);
                        if (backgroundValue == (*_map)[y+charplaced.y][x+charplaced.x]->giveMaterial() and foregroundValue == itemToDraw->material){
                            colorToUse=i;
                            break;
                        }
                    }
                }
                else{
                    for (int i=0;i<NUMBER_OF_COLORS*NUMBER_OF_COLORS;i++){
                        pair_content(i,&foregroundValue,&backgroundValue);
                        if (backgroundValue == (*_map)[y+charplaced.y][x+charplaced.x]->giveMaterial() and foregroundValue == COLOR_BLACK){
                            colorToUse=i;
                            break;
                        }
                        if ((*_map)[y+charplaced.y][x+charplaced.x]->movementCost!=-1){
                            wattron(scr->subwindow.sub,A_BOLD);
                        }
                    }
                }
                wattron(scr->subwindow.sub,COLOR_PAIR(colorToUse));
                if (drawActor==true){
                        mvwaddch(scr->subwindow.sub,y,x,actorToDraw->symbol());
                        drawActor=false;
                }
                else if (drawItem==true){
                    mvwaddch(scr->subwindow.sub,y,x,itemToDraw->symbol);
                    drawItem=false;
                }
                else{
                    mvwaddch(scr->subwindow.sub,y,x,(*_map)[y+charplaced.y][x+charplaced.x]->drawTile());
                }
                wattroff(scr->subwindow.sub,COLOR_PAIR(colorToUse));
                            wattroff(scr->subwindow.sub,A_BOLD);
            }
        }
    }
    scr->drawAnnouncements();
    scr->windowRefresh();
}


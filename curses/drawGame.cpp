#include "drawGame.h"
void drawGameworld(std::vector<std::vector<tile*> > *_map, std::vector<actor*> *actors,std::vector<item*> localItems, sf::RenderWindow & window)
{

    int colortypeCounter=1;

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
    //charplaced=coordinate(0,0);
    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    window.clear();

    for (int y=0;y<25;y++)
    {
        for (int x=0;x<25;x++)
        {
            if (x+charplaced.x >=0 and y+charplaced.y >=0 and x+charplaced.x<(*_map)[0].size() and y+charplaced.y<(*_map).size()){
                for (item* _i : localItems){
                    window.draw(_i->sprite);
                }
                for (actor* _a: *actors)
                {
                    window.draw(_a->sprite);
                }
                (*_map)[y][x]->drawTile(window);
            }
        }
    }
    window.display();
}


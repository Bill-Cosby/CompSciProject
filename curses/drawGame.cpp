#include "drawGame.h"
void gameWorld::drawGameworld(std::vector<std::vector<tile*> > &_map, std::vector<actor*> &actors,std::vector<item*> &localItems, sf::RenderWindow & window, announcements & announcementList)
{


    startingposition=coordinate((actors[0])->col(),(actors[0])->row());


    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    window.clear();

    do_fov(_map,localItems,actors,actors[0]->col(),actors[0]->row(),15,window);

//    for (int y=0;y<25;y++)
//    {
//        for (int x=0;x<25;x++)
//        {
//            if (x+charplaced.x >=0 and y+charplaced.y >=0 and x+charplaced.x<_map[0].size() and y+charplaced.y<_map.size()){
//                for (item* _i : localItems){
//                    _i->draw(window);
//                }
//                for (actor* _a: actors)
//                {
//                    _a->drawActor(window);
//                }
//                actors[0]->drawActor(window);
//                //_map[y][x]->drawTile(window);
//            }
//        }
//    }
    window.setView(window.getDefaultView());
    announcementBorder.setPosition(window.getView().getCenter().x+window.getSize().x/10,window.getView().getCenter().y-window.getSize().y/5);
    window.draw(announcementBorder);
    announcementList.drawAnnouncements(window);
    window.display();
}

void announcements::drawAnnouncements(sf::RenderWindow & window)
{
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text menuText;
    menuText.setCharacterSize(8);
    menuText.setFont(font);

    int x = window.getSize().x*.60+6,y = window.getSize().y - 15;
    for (std::string _s : announcementList){
        menuText.setString(_s);
        menuText.setPosition(x,y);
        window.draw(menuText);
        y-=15;
    }
}


#include "../include/drawGame.h"
void drawGameworld(std::vector<std::vector<tile*> > &_map, std::vector<actor*> &actors,std::vector<item*> localItems, sf::RenderWindow & window, announcements & announcementList, coordinate &temp)
{
    sf::RectangleShape spawnPos;

    spawnPos.setFillColor(sf::Color::Transparent);
    spawnPos.setOutlineColor(sf::Color::Red);
    spawnPos.setOutlineThickness(2);
    spawnPos.setPosition(temp.x*16,temp.y*16);
    spawnPos.setSize(sf::Vector2f(14,14));

    int colortypeCounter=1;

    coordinate startingposition;
    coordinate charplaced;
    short foregroundValue;
    short backgroundValue;
    int colorToUse=1;

    //startingposition=coordinate((actors[0])->col(),(actors[0])->row());
    startingposition = coordinate(temp.x-10,temp.y-10);

    if (startingposition.x < 0)startingposition.x = 0;
    if (startingposition.y < 0)startingposition.y = 0;


    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;


    window.clear();

    //do_fov(_map,actors[0]->col(),actors[0]->row(),15,window);
    //do_fov(_map,5,5,5,window);
    sf::FloatRect screenRect(sf::Vector2f(window.getView().getCenter().x - (window.getView().getSize().x)/2, window.getView().getCenter().y - (window.getView().getSize().y)/2) , window.getView().getSize());

    window.clear(sf::Color::Black);
    int tilesDrawn = 0;
    for(int y = 0; y < _map.size(); y++)
    {
      for(int x = 0; x < _map[0].size(); x++)
      {
        _map[y][x]->sprite.setPosition(x * 16, y * 16);
        sf::FloatRect collider(_map[y][x]->sprite.getGlobalBounds().left, _map[y][x]->sprite.getGlobalBounds().top, 16, 16);

        if(screenRect.intersects(collider))
        {
          window.draw(_map[y][x]->sprite);
          tilesDrawn++;
        }
      }
    }

window.draw(spawnPos);
//    for (int y=0;y<_map.size();y++)
//    {
//        for (int x=0;x<_map.size();x++)
//        {
//            if (x >=0 and y >=0 and x<_map[0].size() and y<_map.size()){
//                for (item* _i : localItems){
//                    window.draw(_i->sprite);
//                }
//                for (actor* _a: actors)
//                {
//                    window.draw(_a->sprite);
//                }
//                _map[y][x]->drawTile(window);
//            }
//            if (coordinate(x,y) == temp){
//            }
//        }
//    }
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


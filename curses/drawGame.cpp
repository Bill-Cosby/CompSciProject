#include "drawGame.h"
void gameWorld::drawGameworld(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, sf::RenderWindow & window, announcements & announcementList, sf::RenderStates &renderState,actor* controlledActor)
{

    renderState = sf::RenderStates::Default;
    startingposition=coordinate(controlledActor->col(),controlledActor->row());


    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    do_fov(_map, localItems, startingposition.x, startingposition.y, 15, window, renderState,false,0,0);

    window.setView(window.getDefaultView());
    announcementBorder.setPosition(window.getView().getCenter().x+window.getSize().x/10,window.getView().getCenter().y-window.getSize().y/5);
    window.draw(announcementBorder);
    announcementList.drawAnnouncements(window);
    window.clear();
                window.display();
}

void announcements::drawAnnouncements(sf::RenderWindow & window)
{
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text menuText;
    menuText.setCharacterSize(8);
    menuText.setFont(font);
    int counter = 0;

    int x = window.getSize().x*.60+6,y = window.getSize().y - 15;
    for (int i = 29; i >-1;i--){
        if (counter > announcementList.size()-1 or announcementList.size() == 0)return;
        menuText.setString(announcementList[counter]);
        menuText.setPosition(x,y);
        window.draw(menuText);
        y-=15;
        counter++;
    }
}


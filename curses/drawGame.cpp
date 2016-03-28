#include "drawGame.h"
void gameWorld::drawGameworld(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<actor*> &actors,std::vector<item*> &localItems, sf::RenderWindow & window, announcements & announcementList, sf::RenderStates &renderState)
{

    renderState = sf::RenderStates::Default;
    startingposition=coordinate((actors[0])->col(),(actors[0])->row());


    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    window.clear();

    if (actors[0]->controlled == true){
        do_fov(_map, localItems, actors, actors[0]->col(), actors[0]->row(), 15, window, renderState,false,0,0);
    }

                actors[0]->drawActor(window);
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


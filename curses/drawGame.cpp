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

//    for (int y=0;y<20;y++)
//    {
//        for (int x=0;x<20;x++)
//        {
//                _map[0][y][x]->drawTile(window,renderState);
//                if (_map[1][y][x]!=NULL)_map[1][y][x]->drawTile(window,renderState);
//        }
//    }
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

    int x = window.getSize().x*.60+6,y = window.getSize().y - 15;
    for (int i = 29; i >-1;i--){
        if (i > announcementList.size())return;
        menuText.setString(announcementList[i]);
        menuText.setPosition(x,y);
        window.draw(menuText);
        y-=15;
    }
}


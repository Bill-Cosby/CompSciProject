#include "drawGame.h"
void gameWorld::drawGameworld(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, sf::RenderWindow & window, announcements & announcementList, sf::RenderStates &renderState,actor* controlledActor)
{

    renderState = sf::RenderStates::Default;
    startingposition=coordinate(controlledActor->col(),controlledActor->row());


    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    window.clear();
    do_fov(_map, localItems, startingposition.x, startingposition.y, 15, window, renderState,false,0,0);

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text bodyPartText;
    bodyPartText.setFont(font);
    bodyPartText.setCharacterSize(12);
    std::vector<bodyPart*> bodies;
    controlledActor->rootPart->returnParts(bodies);

    std::stringstream ss;

    int counter = 0;


    window.setView(window.getDefaultView());

    for(bodyPart* a : bodies)
    {
        if (a->connectedTo != "00")continue;
        bodyPartText.setString(a->name);

        bodyPartText.setPosition(600,10+(15*counter));
        window.draw(bodyPartText);

        ss << a->damage;
        bodyPartText.setString(ss.str());
        ss.str(std::string());
        bodyPartText.setPosition(720,10+(15*counter));
        counter++;
        window.draw(bodyPartText);
    }



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
    int counter = 0;
    for (int i = announcementList.size()-1; i > 0;i--){
        if (counter == 28)return;
        if (counter > announcementList.size()-1 or announcementList.size() == 0)return;
        menuText.setString(announcementList[i]);
        menuText.setPosition(x,y);
        window.draw(menuText);
        y-=15;
        counter++;
    }
}


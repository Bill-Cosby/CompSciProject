#include <iostream>
#include "include\drawGame.h"
#include "include\tiles.h"
#include "include\behaviorTree.h"
#include "include\creationMenu.h"


using namespace std;

int main()
{
    sf::View view(sf::FloatRect(0,0,800,600));
    view.setViewport(sf::FloatRect(0.0f,0.0f,.5f,.5f));
    announcements announcementList;

    std::vector<std::vector<tile*> > _map;
    std::vector<item*> localItems;
    _map.resize(20);
    for (int y = 0; y<20; y++){
        _map[y].resize(20);
        for (int x = 0; x < 20; x++){
            _map[y][x] = new tile('1',0,grass);
            _map[y][x]->position=coordinate(x,y);
            _map[y][x]->sprite.setPosition(x*16,y*16);
        }
    }


    std::vector<std::string> actorlist = RSL::getNames("data/creatures/creature_standard.raw");
    std::vector<std::string> tilelist = RSL::getNames("data/textures/tiles.raw");
    std::vector<std::string> itemlist = RSL::getNames("data/items/weapon_type.raw");

    std::vector<std::vector<std::string> > lists;
    std::vector<actor*> actors;
    lists.push_back(actorlist);
    lists.push_back(tilelist);
    lists.push_back(itemlist);
    sf::RenderWindow window(sf::VideoMode(800,600), "tests");

    bool keyrelease = true;

    char ch;


    coordinate temp;

    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if(event.type == sf::Event::KeyReleased){
                keyrelease = true;
            }
        }
        view.setCenter(temp.x*16,temp.y*16);
        window.setView(view);
        drawGameworld(_map,actors,localItems,window,announcementList, temp);
        window.setView(window.getDefaultView());
        drawCreationMenu(window, lists, keyrelease, temp, actors,_map,localItems);

    }
}

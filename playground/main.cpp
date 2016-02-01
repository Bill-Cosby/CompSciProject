#include <iostream>
#include "include\drawGame.h"
#include "include\tiles.h"
#include "include\behaviorTree.h"
#include "include\creationMenu.h"


using namespace std;

int main()
{
    announcements announcementList;
    sf::View view;

    view.reset(sf::FloatRect(0,0,400,200));
    view.setViewport(sf::FloatRect(0.f,0.f,0.5f,1.f));

    std::vector<std::vector<tile*> > _map;
    std::vector<item*> localItems;
    _map.resize(20);
    for (int y = 0; y<20; y++){
        _map[y].resize(20);
        for (int x = 0; x < 20; x++){
            _map[y][x] = new tile('.',0,grass);
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
        window.setView(view);
        drawGameworld(_map,actors,localItems,window,announcementList);
        drawCreationMenu(window, lists, keyrelease);

    }
}

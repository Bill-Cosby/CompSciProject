#include "drawGame.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "generateCity.h"
#include "tiles.h"
#include "behaviorTree.h"
#include "menu.h"

using namespace std;


int main()
{
    std::default_random_engine generator(time(NULL));
    std::uniform_int_distribution<int> temp (0,time(NULL));


    srand(rand()%temp(generator));
    sf::RenderWindow window(sf::VideoMode(800,600), "Curses!");
    sf::View view(sf::FloatRect(0,0,window.getSize().x*.60,window.getSize().y*.70));
    view.setViewport(sf::FloatRect(0,0,0.6f,0.7f));

    coordinate viewSizeInTiles = coordinate(view.getSize().x/16,view.getSize().y/16);


    city myCity;
    myCity.generateCity();


    sf::Shader lightingShader;
    sf::RenderStates renderState;

    int counter = 0;

    gameWorld gameworld(window);
    announcements announcementList;


    CheckAll * root = new CheckAll;

    Selector * thoughtProcess = new Selector;


    Sequence * danger = new Sequence;
        Selector * fightOrFlight = new Selector;
            Sequence * tryToAttack = new Sequence;
                tryToAttack->addChild(new decideIfCanAttackNode);
                tryToAttack->addChild(new attackNode);
            fightOrFlight->addChild(tryToAttack);
            fightOrFlight->addChild(new findHidingSpot);
        danger->addChild(fightOrFlight);

    Sequence * lookForItems = new Sequence;
        lookForItems->addChild(new lookForItemNode);
        lookForItems->addChild(new pickUpItemNode);

    Sequence * openDoors = new Sequence;
        openDoors->addChild(new findDoorNode);
        openDoors->addChild(new openDoorNode);

    thoughtProcess->addChild(danger);
    thoughtProcess->addChild(lookForItems);
    //thoughtProcess->addChild(openDoors);

    root->addChild(thoughtProcess);
    root->addChild(new herdNode);
    root->addChild(new findPathNode);
    root->addChild(new moveOnPathNode);

    //window.setFramerateLimit(60);

    std::vector<std::vector<std::vector<tile* > > > _map;
    _map = myCity.tileMap;



    std::vector<item*> localItems;;
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(50);
    title.setPosition(220,100);
    title.setString("Curses!");

    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setCharacterSize(10);
    subtitle.setPosition(275,300);
    subtitle.setString("Press 'ENTER' to begin!");

    while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) == false)
    {
        window.clear(sf::Color::Black);

        window.draw(title);
        window.draw(subtitle);

        window.display();
    }

    //char ch;


    actor* controlledActor = characterCreationMenu(window);
    _map[1][1][1]->occupied = controlledActor;


    std::vector<item*> globalItems;
    std::vector<lightSource*> lights;
    lights.push_back(new lightSource);
    lights[0]->intensity = 1;
    lights[0]->decreaseBy = .1;
    lights[0]->position = coordinate(18,18);
    lights.push_back(new lightSource);
    lights[1]->intensity = 1;
    lights[1]->decreaseBy = .1;
    lights[1]->position = coordinate(1,10);
    lights.push_back(new lightSource);
    lights[2]->intensity = 1;
    lights[2]->decreaseBy = .1;
    lights[2]->position = coordinate(18,14);
    lights.push_back(new lightSource);
    lights[3]->intensity = 1;
    lights[3]->decreaseBy = .1;
    lights[3]->position = coordinate(12,1);

    std::vector<std::vector<std::vector<tile* > > > * lightmap;

bool keyrelease = true;
bool waitforplayer = false;
    sf::Event event;
    actor* actorProcessing = NULL;
    while (window.isOpen())
    {

        if (controlledActor->embarking){
            fillInDungeon(_map);

            while (1){
                int x = rand()%2000,y = rand()%2000;
                if (_map[1][y][x]->movementCost != -1){
                    controlledActor->pos(y,x);
                    _map[1][y][x]->occupied = controlledActor;
                    break;
                }
            }
            controlledActor->embarking = false;
        }

        if (controlledActor->col()*16 - view.getSize().x/2 >= 0)view.setCenter(controlledActor->col()*16,view.getCenter().y);
        if (controlledActor->row()*16 - view.getSize().y/2 >= 0)view.setCenter(view.getCenter().x, controlledActor->row()*16);

        while (view.getCenter().x != (controlledActor->col()*16) and view.getCenter().x - view.getSize().x/2 < 0){
            view.setCenter(view.getCenter().x-1,view.getCenter().y);
        }
        while (view.getCenter().y != (controlledActor->row()*16) and view.getCenter().y - view.getSize().y/2 < 0){
            view.setCenter(view.getCenter().x,view.getCenter().y-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) and keyrelease == true){view.zoom(0.5f);keyrelease=false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) and keyrelease == true){view.zoom(2);keyrelease=false;}

        int activeAI =0;


        if (controlledActor->movement(_map, localItems, window, keyrelease, announcementList, waitforplayer)){
            for (int y = controlledActor->row()-14;y<=controlledActor->row()+14;y++){
                for (int x = controlledActor->col()-14;x<=controlledActor->col()+14;x++){
                    if (coordinate(x,y) == coordinate(controlledActor->col(),controlledActor->row())) continue;
                    if (y < 0 or x < 0 or y > _map[0].size()-1 or x > _map[0].size()-1)continue;
                    if(_map[1][y][x]->occupied and _map[1][y][x]->occupied!=controlledActor){
                                activeAI++;
                            _map[1][y][x]->occupied->increaseCounter();
                            if (_map[1][y][x]->occupied->counter == _map[1][y][x]->occupied->speed()){
                                _map[1][y][x]->occupied->resetCounter();
                                root->run(_map[1][y][x]->occupied,_map,localItems,announcementList);
                            }
                    }
                }
            }
        }

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyReleased){
            }
                keyrelease = true;
        }
        int ystart = controlledActor->row() - (viewSizeInTiles.y/2);
        int xstart = controlledActor->col() - (viewSizeInTiles.x/2);
        int yend   = controlledActor->row() + (viewSizeInTiles.y/2);
        int xend   = controlledActor->col() + (viewSizeInTiles.x/2);
        window.setView(view);
                gameworld.drawGameworld(_map, localItems,window,announcementList, renderState,controlledActor);
    }
     myCity.deleteTileMap();

        for (int i=0;i<globalItems.size();i++){
            delete globalItems[i];
        }



    return 0;
}

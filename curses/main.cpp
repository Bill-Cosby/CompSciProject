#include "drawGame.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "generateCity.h"
#include "tiles.h"
#include "behaviorTree.h"
#include "menu.h"
#include <noise/noise.h>

using namespace std;



int main()
{
   signed int gridx=0;
   signed int gridy=0;
    sf::RenderWindow window(sf::VideoMode(800,600), "Curses!");
    sf::View view(sf::FloatRect(0,0,window.getSize().x*.60,window.getSize().y*.70));
    view.setViewport(sf::FloatRect(0,0,0.6f,0.7f));

    coordinate viewSizeInTiles = coordinate(view.getSize().x/16,view.getSize().y/16);


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


    std::vector<item*> globalItems;
    std::vector<item*> localItems;

    localItems.push_back(new boat('B',1,1,0));

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


//    city myCity;
//    myCity.generateCity();
//    _map[0].resize(20);
//    _map[1].resize(20);
//
//    for (int y=0;y<20;y++){
//        _map[0][y].resize(20);
//        for (int x=0;x<20;x++){
//            if (y>=16 and x>=14)_map[0][y][x] = new tile(woodfloor,0,"wood");
//            else _map[0][y][x] = new tile(grass,0,"grass");
//            _map[0][y][x]->position=coordinate(x,y);
//        }
//    }

//    for (int y=0;y<20;y++){
//        _map[1][y].resize(20);
//        for (int x=0;x<20;x++){
//            if (x >= 14 and y == 16){
//                if (x == 17)_map[1][y][x] = new door(true,closeddoor,0,"wood");
//                else _map[1][y][x] = new tile(stonewall,-1,"stone");
//            }
//            else if (x == 14 and y >=16){
//                _map[1][y][x] = new tile(stonewall,-1,"stone");
//            }
//            else if (y == 0 or y == 19){
//                _map[1][y][x] = new tile(stonewall,-1,"stone");
//            }
//            else if (x == 0 or x == 19){
//                _map[1][y][x] = new tile(stonewall,-1,"stone");
//            }
//            else{
//                _map[1][y][x] = new tile;
//            }
//            _map[1][y][x]->position = coordinate(x,y);
//        }
//    }
    std::default_random_engine ew(time(0));
    std::uniform_int_distribution<int> numberOfEnemies(2,10);
    std::uniform_int_distribution<int> enemyPos(1,17);

    //RANDOM GUARDS CODE

//    for (int i=0;i<numberOfEnemies(ew);i++){
//        while (true){
//            temp=coordinate(enemyPos(ew),enemyPos(ew));
//            if (_map[temp.y][temp.x].movementCost!=-1){
//                monsters.push_back(monster(5,'G'));
//                monsters[i].pos(temp.y,temp.x);
//                monsters[i].setPost(temp.x,temp.y);
//                break;
//            }
//
//        }
//
//    }


    //DUNGEON SETUP CODE
//    dungeon map_t;
//    _map.resize(map_t.dungeon_grid.size());
//    _map.resize(map_t.dungeon_grid.size());
//    for (int y=0;y<map_t.dungeon_grid.size();y++)
//    {
//        _map[y].resize(map_t.dungeon_grid[0].size());
//        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
//        {
//            if (map_t.dungeon_grid[y][x]==1)
//            {
//                _map[y][x]= new tile(stonewall,0,"stone");
//                actors[0]->pos(y,x);
//            }
//            else
//            {
//                _map[y][x]= new tile(stonefloor,-1,"stone");
//            }
//            _map[y][x]->position = coordinate(x,y);
//        }
//    }

tiles myWorld;

myWorld.tileMap[1][1][1]->occupied = controlledActor;
controlledActor->pos(1,1);
bool keyrelease = true;
bool waitforplayer = false;
    sf::Event event;
    actor* actorProcessing = NULL;
    while (window.isOpen())
    {
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


        if (controlledActor->movement(&myWorld.tileMap, localItems, window, keyrelease, announcementList, waitforplayer,myWorld.waterBelow)){
            //std::cout<<controlledActor->col()<<", "<<controlledActor->row()<<std::endl;
            for (int y = controlledActor->row()-14;y<=controlledActor->row()+14;y++){
                for (int x = controlledActor->col()-14;x<=controlledActor->col()+14;x++){
                    if (coordinate(x,y) == coordinate(controlledActor->col(),controlledActor->row())) continue;
                    if (y < 0 or x < 0 or y > myWorld.tileMap[1].size()-1 or x > myWorld.tileMap[1].size()-1)continue;
//                    if(myWorld.tileMap[1][y][x]->occupied and myWorld.tileMap[1][y][x]->occupied!=controlledActor){
//                                activeAI++;
//                            myWorld.tileMap[1][y][x]->occupied->increaseCounter();
//                            if (myWorld.tileMap[1][y][x]->occupied->counter == myWorld.tileMap[1][y][x]->occupied->speed()){
//                                myWorld.tileMap[1][y][x]->occupied->resetCounter();
//                                root->run(myWorld.tileMap[1][y][x]->occupied,myWorld.tileMap,localItems,announcementList);
//                            }
//                    }
                }
            }
        }
        sf::Event event;

        if(controlledActor->col()/myWorld.mesh!=gridx or controlledActor->row()/myWorld.mesh!=gridy)
        {
                myWorld.updateTileMap(gridx,gridy,(controlledActor->col())/myWorld.mesh,(controlledActor->row())/myWorld.mesh);
                gridx=(controlledActor->col())/myWorld.mesh; gridy=(controlledActor->row())/myWorld.mesh;        }
        if (controlledActor->col()*16 - view.getSize().x/2 >= 0)view.setCenter(controlledActor->col()*16,view.getCenter().y);
        if (controlledActor->row()*16 - view.getSize().y/2 >= 0)view.setCenter(view.getCenter().x, controlledActor->row()*16);

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
        gameworld.drawGameworld(myWorld.tileMap, localItems,window,announcementList, renderState, controlledActor);
    }
        /*for (int i=0;i<myCity.tileMap.size();i++){
            for (int j=0;j<myCity.tileMap.size();i++){
                delete _map[i][j];
            }
        }*/


        for (int i=0;i<globalItems.size();i++){
            delete globalItems[i];
        }



    return 0;
}


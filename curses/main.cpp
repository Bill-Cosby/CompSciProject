#include "drawGame.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "generateCity.h"
//#include "tiles.h"
#include "behaviorTree.h"
#include "menu.h"

using namespace std;


int main()
{
    std::mt19937 generator(time(NULL));
    std::uniform_int_distribution<int> temp (0,time(NULL));


    srand(temp(generator));
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
        danger->addChild(new lookForEnemiesNode);
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

    //thoughtProcess->addChild(danger);
    //thoughtProcess->addChild(lookForItems);
    //thoughtProcess->addChild(openDoors);

    root->addChild(thoughtProcess);
    root->addChild(new herdNode);
    root->addChild(new findPathNode);
    root->addChild(new moveOnPathNode);


    std::vector<std::vector<std::vector<tile* > > > _map;
    city myCity;
    myCity.generateCity();
    _map = myCity.tileMap;

    //actor* controlledActor = characterCreationMenu(window);
    actor* controlledActor = new player("human");
    _map[1][1][1]->occupied = controlledActor;

    std::vector<item*> localItems;;



    //window.setFramerateLimit(60);


    //char ch;





    std::vector<item*> globalItems;
//    localItems.push_back(new weapon("Sword",'/',10,18,7));
//    localItems.push_back(new clothing("platearmor",'C',5,5,0,"iron"));
//    localItems.push_back(new clothing("plateleg",'C',5,5,0,"iron"));
//    localItems.push_back(new clothing("plateleg",'C',5,5,0,"iron"));
//    localItems.push_back(new clothing("plateboot",'C',5,5,0,"iron"));
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

    //coordinate temp;
    std::vector<std::vector<std::vector<tile* > > > * lightmap;


//    _map.resize(2);
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
//
//    for (int y=0;y<20;y++){
//        _map[1][y].resize(20);
//        for (int x=0;x<20;x++){
//            if (x >= 14 and y == 16){
//                if (x == 17)_map[1][y][x] = new door(false,closeddoor,0,"wood");
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
//
//    _map[1][10][10] = new socialTile(closeddoor,-1,"wood");
//    _map[1][10][10]->position = coordinate(10,10);
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
//////    dungeon map_t;
//////    int whatever = 0;
//////    _map.resize(2);
//////    _map[0].resize(map_t.dungeon_grid.size());
//////    _map[1].resize(map_t.dungeon_grid.size());
//////    for (int y=0;y<map_t.dungeon_grid.size();y++)
//////    {
//////        _map[0][y].resize(map_t.dungeon_grid[0].size());
//////        _map[1][y].resize(map_t.dungeon_grid[0].size());
//////        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
//////        {
//////            if (map_t.dungeon_grid[y][x])
//////            {
//////                whatever++;
//////                _map[1][y][x]= new tile;
//////                _map[0][y][x]= new tile(stonefloor,0,"stone");
//////                _map[0][y][x]->position = coordinate(x,y);
//////                controlledActor->pos(y,x);
//////            }
//////            else
//////            {
//////
//////                _map[1][y][x]= new tile(stonewall,-1,"stone");
//////                _map[0][y][x]= new tile(stonefloor,0,"stone");
//////                _map[1][y][x]->position = coordinate(x,y);
//////                _map[0][y][x]->position = coordinate(x,y);
//////            }
//////        }
//////    }

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

        controlledActor->movement(_map, localItems, window, keyrelease, announcementList, waitforplayer);
        std::thread AI(run,root,actorProcessing,std::ref(_map),std::ref(localItems),std::ref(announcementList));
        for (int y = controlledActor->row()-14;y<=controlledActor->row()+14;y++){
            for (int x = controlledActor->col()-14;x<=controlledActor->col()+14;x++){
                if (coordinate(x,y) == coordinate(controlledActor->col(),controlledActor->row())) continue;
                if (y < 0 or x < 0 or y > _map[0].size() or x > _map[0].size())continue;
                if(_map[1][y][x]->occupied)actorProcessing = _map[1][y][x]->occupied;
            }
        }
        AI.join();
        int activeAI =0;

//        lightmap = &_map;
//        do_fov(lightmap,localItems,actors,controlledActor->col(),controlledActor->row(),1/.1,window,renderState,true,1,.1);
//        for (lightSource * _l : lights){
//            do_fov(lightmap,localItems,actors,_l->position.x,_l->position.y,_l->intensity/_l->decreaseBy,window,renderState,true,_l->intensity,_l->decreaseBy);
//        }
////        for (lightSource * _l : lights){
////            do_fov(lightmap,localItems,actors,_l->position.x,_l->position.y,_l->intensity/_l->decreaseBy,window,renderState,true,_l->intensity,_l->decreaseBy);
////        for (lightSource * _l : lights){
////            do_fov(lightmap,localItems,actors,_l->position.x,_l->position.y,_l->intensity/_l->decreaseBy,window,renderState,true,_l->intensity,_l->decreaseBy);
////        }
////        for (lightSource * _l : lights){
////            do_fov(lightmap,localItems,actors,_l->position.x,_l->position.y,_l->intensity/_l->decreaseBy,window,renderState,true,_l->intensity,_l->decreaseBy);
////        }
//        _map = (*lightmap);

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyReleased){
                keyrelease = true;
            }
        }
        int ystart = controlledActor->row() - (viewSizeInTiles.y/2);
        int xstart = controlledActor->col() - (viewSizeInTiles.x/2);
        int yend   = controlledActor->row() + (viewSizeInTiles.y/2);
        int xend   = controlledActor->col() + (viewSizeInTiles.x/2);

//        if (xstart < 0)xstart = 0;
//        if (ystart < 0)ystart = 0;
//        if (xend >= _map[0][0].size())xend = _map[0][0].size()-1;
//        if (yend >= _map[0].size())yend = _map[0].size()-1;
//
//        for (ystart;ystart <= yend;ystart++){
//            for (int x = xstart;x<=xend;x++){
//                _map[0][ystart][x]->litHere = false;
//                _map[1][ystart][x]->litHere = false;
//            }
//        }
        window.setView(view);
        gameworld.drawGameworld(_map, localItems,window,announcementList, renderState,controlledActor);
    }
        /*for (int i=0;i<myCity.tileMap.size();i++){
            for (int j=0;j<myCity.tileMap.size();i++){
                delete _map[i][j];
            }
        }*/
     myCity.deleteTileMap();

        for (int i=0;i<globalItems.size();i++){
            delete globalItems[i];
        }



    return 0;
}

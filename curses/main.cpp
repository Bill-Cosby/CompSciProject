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
    sf::RenderWindow window(sf::VideoMode(800,600), "Curses!");
    sf::View view(sf::FloatRect(0,0,window.getSize().x*.60,window.getSize().y*.70));
    view.setViewport(sf::FloatRect(0,0,0.6f,0.7f));
    characterCreationMenu(window);

    coordinate viewSizeInTiles = coordinate(view.getSize().x/16,view.getSize().y/16);

    sf::Shader lightingShader;
    sf::RenderStates renderState;


    int counter = 0;

    gameWorld gameworld(window);
    srand(time(NULL));
    srand(rand()%time(NULL));
    CheckAll * root = new CheckAll;
    announcements announcementList;

    Selector* decisionMaker = new Selector;
    Selector* actionPerformer = new Selector;

    Sequence * doorSequence = new Sequence;
            doorSequence->addChild(new findDoorNode);

    Sequence * itemSequence = new Sequence;
            itemSequence->addChild(new lookForItemNode);
            itemSequence->addChild(new isItemBetterNode);

    Sequence * attackSequence = new Sequence;
            attackSequence->addChild(new decideIfCanAttackNode);

    Selector * movement = new Selector;
            movement->addChild(new moveOnPathNode);
            movement->addChild(new findPathNode);

        actionPerformer->addChild(new attackNode);
        actionPerformer->addChild(new pickUpItemNode);
        actionPerformer->addChild(new openDoorNode);
        actionPerformer->addChild(movement);


    decisionMaker->addChild(attackSequence);
    decisionMaker->addChild(itemSequence);
    decisionMaker->addChild(doorSequence);

    root->addChild(decisionMaker);
    root->addChild(actionPerformer);


    //window.setFramerateLimit(60);


   // bool keyrelease=true;
std::vector<actor*> actors;
actors.push_back(new player("human"));



    //char ch;

    actors[0]->pos(1,1);




    std::vector<item*> globalItems;
    std::vector<item*> localItems;
    localItems.push_back(new weapon("Sword",'/',10,18,7));
    localItems.push_back(new clothing("cottonshirt",'C',5,5,0,"cotton"));
    localItems.push_back(new clothing("cottonpants",'C',5,5,0,"cotton"));
    localItems.push_back(new clothing("cottonpants",'C',5,5,0,"cotton"));
    localItems.push_back(new clothing("plateboot",'C',5,5,0,"iron"));
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

    std::vector<std::vector<std::vector<tile* > > > _map;

    _map.resize(2);
    _map[0].resize(20);
    _map[1].resize(20);

    for (int y=0;y<20;y++){
        _map[0][y].resize(20);
        for (int x=0;x<20;x++){
            if (y>=16 and x>=14)_map[0][y][x] = new tile(woodfloor,0,"wood");
            else _map[0][y][x] = new tile(grass,0,"grass");
            _map[0][y][x]->position=coordinate(x,y);
        }
    }

    for (int y=0;y<20;y++){
        _map[1][y].resize(20);
        for (int x=0;x<20;x++){
            if (x >= 14 and y == 16){
                if (x == 17)_map[1][y][x] = new door(true,closeddoor,0,"wood");
                else _map[1][y][x] = new tile(stonewall,-1,"stone");
            }
            else if (x == 14 and y >=16){
                _map[1][y][x] = new tile(stonewall,-1,"stone");
            }
            else if (y == 0 or y == 19){
                _map[1][y][x] = new tile(stonewall,-1,"stone");
            }
            else if (x == 0 or x == 19){
                _map[1][y][x] = new tile(stonewall,-1,"stone");
            }
            else{
                _map[1][y][x] = new tile;
            }
            _map[1][y][x]->position = coordinate(x,y);
        }
    }
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


bool keyrelease = true;
    while (window.isOpen())
    {


        sf::Event event;

        if (keyrelease == false){
            for (int i=0;i<actors.size();i++){
                if (actors[i]->counter >= actors[i]->speed() and actors[i]->controlled == false){
                    std::cout << "_______________________________________\n";
                    root->run(actors[i],_map,localItems,actors,announcementList);
                    actors[i]->resetCounter();
                }
                actors[i]->increaseCounter();
            }
        }
        else actors[0]->movement(_map, localItems, actors, window, keyrelease, announcementList);
        if (actors[0]->col()*16 - view.getSize().x/2 >= 0)view.setCenter(actors[0]->col()*16,view.getCenter().y);
        if (actors[0]->row()*16 - view.getSize().y/2 >= 0)view.setCenter(view.getCenter().x, actors[0]->row()*16);


//        lightmap = &_map;
//        do_fov(lightmap,localItems,actors,actors[0]->col(),actors[0]->row(),1/.1,window,renderState,true,1,.1);
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
            }
                keyrelease = true;
        }
        int ystart = actors[0]->row() - (viewSizeInTiles.y/2);
        int xstart = actors[0]->col() - (viewSizeInTiles.x/2);
        int yend   = actors[0]->row() + (viewSizeInTiles.y/2);
        int xend   = actors[0]->col() + (viewSizeInTiles.x/2);

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
        gameworld.drawGameworld(_map, actors, localItems,window,announcementList, renderState);
    }


        for (int i=0;i<actors.size();i++){
            delete actors[i];
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

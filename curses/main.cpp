#include "drawGame.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "building.h"
#include "generateCity.h"
#include "tiles.h"
#include "behaviorTree.h"

using namespace std;

const char testarena[20][20]={{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1','2','1','1','1','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1'},
                              {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1'},
                              {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}};


int main()
{

    sf::RenderWindow window(sf::VideoMode(800,600), "Curses!");
    sf::View view(sf::FloatRect(0,0,window.getSize().x*.60,window.getSize().y*.70));
    view.setViewport(sf::FloatRect(0,0,0.6f,0.7f));

    RSL::setupMenu("data/menus/mainMenu.raw", window);

    int counter = 0;

    gameWorld gameworld(window);
    srand(time(NULL));
    srand(rand()%time(NULL));
    CheckAll * root = new CheckAll;
    city myCity;
    announcements announcementList;

    Selector* decisionMaker = new Selector;
    //Defining the tree

    Sequence * doorSequence = new Sequence;
            doorSequence->addChild(new findDoorNode);
            doorSequence->addChild(new openDoorNode);

    Sequence * itemSequence = new Sequence;
            itemSequence->addChild(new lookForItemNode);
            itemSequence->addChild(new isItemBetterNode);
            itemSequence->addChild(new pickUpItemNode);

    Sequence * attackSequence = new Sequence;
            attackSequence->addChild(new decideIfCanAttackNode);
            attackSequence->addChild(new attackNode);

    Selector * movement = new Selector;
            movement->addChild(new moveOnPathNode);
            movement->addChild(new findPathNode);


    decisionMaker->addChild(attackSequence);
    decisionMaker->addChild(itemSequence);
    decisionMaker->addChild(doorSequence);

    root->addChild(decisionMaker);
    root->addChild(movement);


    //window.setFramerateLimit(60);


   // bool keyrelease=true;
std::vector<actor*> actors;
actors.push_back(new player("human"));
actors.push_back(new monster("human"));



    //char ch;

    actors[0]->pos(18,18);
    actors[1]->pos(2,2);



    std::vector<item*> globalItems;
    std::vector<item*> localItems;
    globalItems.push_back(new weapon(10,"Axe",'P',16,18,10,"weapon"));
    globalItems.push_back(new weapon(5,"Sword",'/',10,18,7,"weapon"));
    localItems.push_back(globalItems[0]);
    localItems.push_back(globalItems[1]);

    //coordinate temp;



    std::vector<std::vector<tile* > > _map;
    _map.resize(20);
    for (int y=0;y<20;y++){
        _map[y].resize(20);
        for (int x=0;x<20;x++){
            if (testarena[y][x]=='2'){
                _map[y][x]=new door(0,0);
            }
            else if (testarena[y][x]=='1'){
                _map[y][x]=new tile('0',-1,0);
                _map[y][x]->isDoor=false;
            }
            else{
                _map[y][x]= new tile('1',0,0);
                _map[y][x]->isDoor=false;
            }
            _map[y][x]->position=coordinate(x,y);
            _map[y][x]->sprite.setPosition(x*16,y*16);
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
    //_map.resize(map_t.dungeon_grid.size());
//    _map.resize(map_t.dungeon_grid.size());
//    for (int y=0;y<map_t.dungeon_grid.size();y++)
//    {
//        _map[y].resize(map_t.dungeon_grid[0].size());
//        for (int x=0;x<map_t.dungeon_grid[0].size();x++)
//        {
//            if (map_t.dungeon_grid[y][x]==1)
//            {
//                _map[y][x]= new tile(' ',0,wood);
//actors[0]->pos(y,x);
//            }
//            else
//            {
//                _map[y][x]= new tile('#',-1, stone);
//            }
//        }
//    }

//    for (int i=0;i<monsters.size();i++){
//        actors.push_back(&monsters[i]);
//    }


myCity.generateCity();


bool keyrelease = true;
    while (window.isOpen())
    {
        if (actors[0]->col()*16 - view.getSize().x/2 > 0)view.setCenter(actors[0]->col()*16,view.getCenter().y);
        if (actors[0]->row()*16 - view.getSize().y/2 > 0)view.setCenter(view.getCenter().x, actors[0]->row()*16);
window.setView(view);

        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyReleased){
                keyrelease = true;
            }
        }

        actors[0]->movement(_map, localItems, actors, window, keyrelease, announcementList);
        for (int i=1;i<actors.size();i++){
            if (actors[i]->counter >= actors[i]->speed()){
                std::cout << "_______________________________________\n";
                root->run(actors[i],_map,localItems,actors,announcementList);
                actors[i]->resetCounter();
            }
            else{
                actors[i]->increaseCounter();
            }
        }

        gameworld.drawGameworld(_map, actors, localItems,window,announcementList);
    }

        for (int i=0;i<actors.size();i++){
            delete actors[i];
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

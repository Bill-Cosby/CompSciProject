#include "menu.h"
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
    Selector * root = new Selector;

    Sequence * Sequence1 = new Sequence;
    Sequence * Sequence2 = new Sequence;
    Sequence * Sequence3 = new Sequence;
    Selector * Selector1 = new Selector;

    Sequence1->addChild(new findDoorNode);
    Sequence1->addChild(new openDoorNode);

    Sequence2->addChild(new lookForItemNode);
    Sequence2->addChild(new pickUpItemNode);

    Sequence3->addChild(new decideIfCanAttackNode);
    Sequence3->addChild(new attackNode);

//===========================================

    Selector1->addChild(Sequence3);

    Selector1->addChild(Sequence1);

    Selector1->addChild(Sequence2);

    Selector1->addChild(new moveOnPathNode);

    Selector1->addChild(new findPathNode);




    root->addChild(Selector1);


    sf::RenderWindow window(sf::VideoMode(800,600), "Curses!");

    //window.setFramerateLimit(60);

    announcements announcementList;

    bool keyrelease=true;



    char ch;



    std::vector<item*> globalItems;
    std::vector<item*> localItems;
    globalItems.push_back(new weapon(10,"Axe",'P',16,18));
    globalItems.push_back(new weapon(5,"Sword",'/',16,18));
    localItems.push_back(globalItems[0]);
    localItems.push_back(globalItems[1]);


    coordinate temp;



    std::vector<std::vector<tile* > > _map;
    std::vector<actor*> actors;




    _map.resize(20);
    for (int y=0;y<20;y++){
        _map[y].resize(20);
        for (int x=0;x<20;x++){
            if (testarena[y][x]=='2'){
                _map[y][x]=new door(0,wood);
            }
            else if (testarena[y][x]=='1'){
                _map[y][x]=new tile('0',-1,stone);
                _map[y][x]->isDoor=false;
            }
            else{
                _map[y][x]= new tile('1',0,stone);
                _map[y][x]->isDoor=false;
            }
            _map[y][x]->position=coordinate(x,y);
            _map[y][x]->sprite.setPosition(x*16,y*16);
            std::cout << _map[y][x]->isDoor;
        }
        std::cout << endl;
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


    actors.push_back(new player("human"));
   // actors.push_back(new monster("goblin"));
   // actors[1]->pos(1,1);
    actors[0]->pos(17,17);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyReleased){
                keyrelease = true;
            }
        }
        actors[0]->movement(&_map, &localItems, actors, window, keyrelease, announcementList);
        for (int i=1;i<actors.size();i++){
            std::cout << "_______________________________________\n";
            root->run(actors[i],_map,localItems,actors);
        }
        drawGameworld(_map,actors,localItems,window, announcementList);
    }

        for (int i=0;i<actors.size();i++){
            delete actors[i];
        }
        for (int i=0;i<_map.size();i++){
            for (int j=0;j<_map[i].size();i++){
                delete _map[i][j];
            }
        }
        for (int i=0;i<globalItems.size();i++){
            delete globalItems[i];
        }

    return 0;
}

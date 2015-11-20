#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>
#include "pathFinder.h"

using namespace std;

int main()
{
    srand(time(NULL));

    std::default_random_engine engine(rand()%time(NULL));
    std::uniform_int_distribution<int> booler(0,10);

    std::vector<std::vector<bool> > _map;


//====================================
    _map.resize(20);
    for(std::vector<bool> vec : _map){
        vec.resize(20);
        for(bool spot : vec){
            if (booler(engine)<4){
                spot=1;
            }else{spot=0;}
            std::cout << spot;
        }
        std::cout << std::endl;
    }
//=====================================

    std::vector<node> nodeLibrary;
    node baseNode(9999999,0);
    nodeLibrary.resize(10);
    for (int i=0;i<10;i++)
    {
        nodeLibrary[i].hCost=i*10;
        baseNode.add(&nodeLibrary[i]);
    }

    for (int i=0;i<10;i++)
    {
        std::cout << baseNode.give().hCost << std::endl;
    }

}

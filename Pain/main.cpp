#include <iostream>
#include <vector>
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



}

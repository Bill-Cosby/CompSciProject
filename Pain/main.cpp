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
    for (int i=0;i<20;i++){
        _map[i].resize(20);
        for (int j=0;j<20;j++){
            if (booler(engine)<=4){
                _map[i][j]=1;
            }
            else{
                _map[i][j]=0;
            }
        }
    }
//=====================================

    pathFinder(_map,coordinate(0,0),coordinate(19,19));

}

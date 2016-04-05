#include "drawGame.h"
#include "include/dungeon.h"
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "generateCity.h"
#include "tiles.h"
#include "behaviorTree.h"

using namespace std;


int main()
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); generator.seed(seed);
   for(int x=0; x<20; x++)
   {
       std::mt19937 generator;
       std::uniform_int_distribution<int> halfChance(0,1);
       int half=halfChance(generator);
       cout<<half<<endl;
   }


    return 0;
}

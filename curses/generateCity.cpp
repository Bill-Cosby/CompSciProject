#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <random>

void building::makeHouse(vector<vector<tile*> > tileMap&)
{
    divideBox(2,tileMap&,"HOUSE")
    for(int a=left+1; a<=right-1; a++)
    {
        for(int b=bottom; b<=bottom-1; b++)
        {
            if(a=)
        }
    }
}

void city:: setTileMap()
{
    std::vector<tile*> blank1;
    blank1.resize(tileMapSize);
    tileMap.resize(tileMapSize);
  for(int a=0; a<tileMapSize; a++)
    {
        tileMap[a]=blank1;
        for(int b=0; b<tileMapSize; b++)
        {
            tileMap[a][b]=new tile('0',10,10);
            tileMap[a][b]->position = coordinate(b,a);
            tileMap[a][b]->sprite.setPosition(b*16,a*16);
            tileMap[a][b]->isDoor = false;
        }
    }

}


void city:: deleteTileMap()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap.size(); b++)
        {
            delete tileMap[a][b];
        }
    }
}

void box::makeRoad(road* myRoad, std::vector<std::vector<tile*> > & tileMap, int level)
{

 if(myRoad->vertical==true)
 {
  for(int a=0; a<=(myRoad->Point2->y-myRoad->Point1->y); a++)
  {
      for(int b=0; b<level; b++)
      {
          tileMap[(myRoad->Point1->y)+a][myRoad->Point1->x-level/2+b]=new tile('1',10,10);
      }

  }
 }

  else
  {
  for(int a=0; a<=myRoad->Point2->x-myRoad->Point1->x; a++)
   {
       for(int b=0; b<level; b++)
       {
           tileMap[myRoad->Point1->y-level/2+b][myRoad->Point1->x+a]=new tile('1',10,10);
       }

   }
  }


}


void box::divideBox(int level, std::vector<std::vector<tile*> > & tileMap, std::string type)
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> halfChance(0,1);

        building build_ing;
        build_ing.buildStructure("[HOUSE1]");


  if(level!=0)
  {

    if(halfChance(generator)==0 and right-left>level+2) //if line vertical and there is space to draw line
    {
        std::uniform_int_distribution<int> findSplitPoint(left+level/2+1, right-level/2-1);
        int splitPoint=findSplitPoint(generator);

        coordinate lowPoint(splitPoint, bottom);
        coordinate highPoint(splitPoint, top);

        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;
        makeRoad(&tempRoad, tileMap, level); //draws road on tile map

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint;
        subBox1->top=top;
        subBox1->bottom=bottom;

        subBox2->left=splitPoint;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

        subBox1->divideBox(level-1, tileMap, type);
        subBox2->divideBox(level-1, tileMap, type);
        delete subBox1;
        delete subBox2;

    }

    else if (top-bottom>level+2)
    {//line horizontal
        int splitPoint=bottom+1+level/2+rand()%(top-bottom-level-2);
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;

        makeRoad(&tempRoad, tileMap, level); //draws road on tileMap

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=right;
        subBox1->top=top;
        subBox1->bottom=splitPoint;

        subBox2->left=left;
        subBox2->right=right;
        subBox2->top=splitPoint;
        subBox2->bottom=bottom;  //forms 2 new boxes
        subBox1->divideBox(level-1, tileMap, type);
        subBox2->divideBox(level-1, tileMap, type);
        delete subBox1;
        delete subBox2;

    }

  }

 /* else if(right-left>13 and top-bottom>13)


    {
      for(int a=0;a<10; a++)
      {
          for(int b=0; b<10; b++)
          {  tile* temp_tile=
          build_ing.structure[0][0];
             tileMap[bottom+2+a][left+2+b]=temp_tile;
          }

      }

    }

*/



}

  void city::generateCity()
{
    srand(time(NULL));

setTileMap();
divideBox(4,tileMap, "ROADBOX"); //recursive box dividing and road drawing
}




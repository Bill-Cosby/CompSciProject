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
    for(int a=left; a<=R; a++)
    {
        for(int b=low; b<=top; b++)
        {
            if(a==left or a==right or b==bottom or b==top)
            {
                tileMap[b][a]=new tile('1',20,wood);
            }
            dividebox(1,tileMap,"House");
        }
    }


   /* unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution fourthChance(0,4);
    int side=fourthChance(generator);

    if(side==0)
    {

        std::normal_distribution<int> findDoor(bottom+1,top-1);
        doorPlace=findDoor(generator);
        tileMap[doorPlace][right]=new tile();
    }
    if(side==1)
    {
         std::normal_distribution<int> findDoor(left+1,right-1);
         doorPlace=findDoor(generator);
         tileMap[top][doorPlace];
    }
    if(side==2)
    {
         std::normal_distribution<int> findDoor(bottom+1,top-1);
         doorPlace=findDoor(generator);
         tileMap[doorPlace][];
    }
    if(side==3)
    {
        std::normal_distribution<int> findDoor(left+1,right-1);
        doorPlace=findDoor(generator);
    }
    */
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

void box::makeLine(road* myLine, std::vector<std::vector<tile*> > & tileMap, int level, std::string type)
{
if(type=="House")
{
    char dc='1';
    int mc=10;
    short mat=wood;
    int width=1;;
}

if(type=="RoadBox")
{
   char dc='0';
   int mc=10;
   short mat=wood;
   int width=level;
}

 if(myLine->vertical==true)
 {
  for(int a=myRoad->Point1->y; a<=myLine->Point2->y); a++)
  {
      for(int b=0; b<level; b++)
      {
          tileMap[a][myLine->Point1->x-width/2+b]=new tile(dc,mc,mat);
      }

  }
 }

  else
  {
  for(int a=myLine->Point1->x; a<=myLine->Point2->x; a++)
   {
       for(int b=0; b<level; b++)
       {
           tileMap[myLine->Point1->y-width/2+b][a]=new tile(dc,mc,mat);
       }

   }
  }


}


void box::divideBox(int level, std::vector<std::vector<tile*> > & tileMap, std::string type)
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> halfChance(0,1);

if(level==0 and type="ROADBOX")
{
   makeHouse(tileMap);
}

if(level>0)
{
    int half==halfChance(generator);

    if(half==0 and right-left>level) //if line vertical and there is space to draw line
    {
        std::normal_distribution<int> findSplitPoint(left+level/2, right-level/2);
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

        subBox1->left=left+1;
        subBox1->right=splitPoint-1;
        subBox1->top=top-1;
        subBox1->bottom=bottom+1;

        subBox2->left=splitPoint+1;
        subBox2->right=right-1;
        subBox2->top=top-1;
        subBox2->bottom=bottom+1;

        subBox1->divideBox(level-1, tileMap, type);
        subBox2->divideBox(level-1, tileMap, type);
        delete subBox1;
        delete subBox2;

    }

    else if (half==1 and top-bottom>level)
    {//line horizontal
        std::normal_distribution<int> findSplitPoint(bottom+level/2, top-level/2);
        int splitPoint=findSplitPoint(generator);
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;

        makeRoad(&tempRoad, tileMap, level); //draws road on tileMap

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left+1;
        subBox1->right=right-1;
        subBox1->top=top-1;
        subBox1->bottom=splitPoint+1;

        subBox2->left=left+1;
        subBox2->right=right-1;
        subBox2->top=splitPoint-1;
        subBox2->bottom=bottom+1;  //forms 2 new boxes
        subBox1->divideBox(level-1, tileMap, type);
        subBox2->divideBox(level-1, tileMap, type);
        delete subBox1;
        delete subBox2;

    }

}


}

  void city::generateCity()
{
    srand(time(NULL));

setTileMap();
divideBox(4,tileMap, "ROADBOX"); //recursive box dividing and road drawing
}




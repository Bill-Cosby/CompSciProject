#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <random>

void box::makeHouse(std::vector<std::vector<tile*> > & tileMap)
{
 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> halfChance(0,1);
    std::uniform_int_distribution<int> doorFinder(bottom+left,top+right);
    int half=halfChance(generator);
    int doorPlace=doorFinder(generator);

    for(int a=left; a<=right; a++)
    {
        for(int b=bottom; b<=top; b++)
        {
            if(b==bottom or a==right)
            {
                if(b+a==doorPlace and half==0)
                {
                    tileMap[b][a]=new tile(closeddoor,20,"wood");
                }
                else
                {
                    tileMap[b][a]=new tile(stonefloor,20,"stone");
                }

            }

            else if(a==left or b==top)
            {
                if(b+a==doorPlace and half==1)
                {
                    tileMap[b][a]=new tile(closeddoor,20,"wood");
                }
                else
                {
                    tileMap[b][a]=new tile(stonefloor,20,"stone");
                }
            }
            tileMap[b][a]->position = coordinate(a,b);
            divideBox(1,tileMap,"HOUSE");
        }
    }


}

void city:: setTileMap()
{
    tileMap.resize(tileMapSize);
  for(int a=0; a<tileMapSize; a++)
    {
        tileMap[a].resize(tileMapSize);
        for(int b=0; b<tileMapSize; b++)
        {
            tileMap[a][b]=new tile(grass,10,"grass");
            tileMap[a][b]->position = coordinate(b,a);
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
    std::cout << "Make a line\n";
    int a=0;
    int b=0;
    int width;

    int dc;
    int mc;
    std::string mat;

    int doorPlace;

if(type=="HOUSE")
{
    std::cout << "house wall\n";
    dc=1;
    mc=10;
    mat="wood";
    width=1;
    if(myLine->vertical)
    {
        a=myLine->Point1->y;
        b=myLine->Point2->y;

    }
    else
    {
        a=myLine->Point1->x;
        b=myLine->Point2->x;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> doorFinder(a,b);
    doorPlace=doorFinder(generator);
}

if(type=="ROADBOX")
{
   mc=10;
   mat="stone";
   width=level;
}

 if(myLine->vertical==true)
 {
  for(int c=myLine->Point1->y; c<=myLine->Point2->y; c++)
  {
      for(int d=0; d<level; d++)
      {
          signed int q=myLine->Point1->x-(level+1)/2+d;

          //tileMap[a][myLine->Point1->x-width/2+b]=new tile(stonefloor,5,"stone");
          if(type=="HOUSE" and c==doorPlace)
          {
              tileMap[c][d]=new tile(woodfloor,5,"wood");
              tileMap[c][d]->position = coordinate(d,c);
          }
          else if(0<=q and q <tileMap.size())
           {

               //tileMap[c][q]=new tile(dirt,5,"dirt");
               tileMap[c][q]->position = coordinate(c,q);
           }
      }

  }
 }


  else
  {
  for(int c=myLine->Point1->x; c<=myLine->Point2->x; c++)
   {
       for(int d=0; d<level; d++)
       {
           signed int q=myLine->Point1->y-(width+1)/2+d;

           if(type=="HOUSE" and c==doorPlace)
          {
              tileMap[d][c]=new tile(woodwall,5,"wood");
               tileMap[d][c]->position = coordinate(c,d);
          }
           else if(0<=q and q <tileMap.size())
           {

               //tileMap[q][c]=new tile(dirt,5,"dirt");
               tileMap[q][c]->position = coordinate(c,q);
           }
       }

   }
  }


}


void box::divideBox(int level, std::vector<std::vector<tile*> > & tileMap, std::string type)
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
std::uniform_int_distribution<int> halfChance(0,1);

if(level==0 and type=="ROADBOX")
{
   makeHouse(tileMap);  //many houses
}

if(level>0)
{
    int half = 0;

    if(half==0 and right-left>level) //if line vertical and there is space to draw line
    {
        std::uniform_int_distribution<int> findSplitPoint(left+level/2, right-level/2);
        int splitPoint=findSplitPoint(generator);

        coordinate lowPoint(splitPoint, bottom);
        coordinate highPoint(splitPoint, top);

        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;
        makeLine(&tempRoad, tileMap, level, type); //draws road on tile map

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

    }

    else if (half==1 and top-bottom>level)
    {//line horizontal
        std::uniform_int_distribution<int> findSplitPoint(bottom+level/2,top-level/2);
        int tempBottom=bottom;
        int tempLevel=level;
        int tempTop=top;
        int splitPoint=findSplitPoint(generator);
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;

        makeLine(&tempRoad, tileMap, level, type); //draws road on tileMap

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
    }

}


}

  void city::generateCity()
{
setTileMap();
divideBox(4,tileMap, "ROADBOX"); //recursive box dividing and road drawing
}



box::~box()
{

}


#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <random>

void box::makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap)
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
            tileMap[0][b][a]= new tile(woodfloor,0,"wood");
            if(b==bottom or a==right)
            {
                if(b+a==doorPlace and half==0)
                {
                    tileMap[1][b][a]=new door(false,closeddoor,0,"wood");
                }
                else
                {
                    tileMap[1][b][a]=new tile(stonewall,-1,"stone");
                }

                tileMap[1][b][a]->position = coordinate(a,b);
            }

            else if(a==left or b==top)
            {
                if(b+a==doorPlace and half==1)
                {
                    tileMap[1][b][a]=new door(false,closeddoor,0,"wood");
                }
                else
                {
                    tileMap[1][b][a]=new tile(stonewall,-1,"stone");
                }
                tileMap[1][b][a]->position = coordinate(a,b);
            }
            else{
                tileMap[0][b][a]->position = coordinate(a,b);
            }
            divideBox(1,tileMap,"HOUSE");
        }
    }


}

void city:: setTileMap()
{
    tileMap.resize(2);
    tileMap[0].resize(tileMapSize);
    tileMap[1].resize(tileMapSize);
  for(int a=0; a<tileMapSize; a++)
    {
        tileMap[0][a].resize(tileMapSize);
        tileMap[1][a].resize(tileMapSize);
        for(int b=0; b<tileMapSize; b++)
        {
            tileMap[0][a][b]=new tile(grass,10,"grass");
            tileMap[0][a][b]->position = coordinate(b,a);
            tileMap[0][a][b]->isDoor = false;
            tileMap[1][a][b]=new tile;
            tileMap[1][a][b]->position = coordinate(b,a);
            tileMap[1][a][b]->isDoor = false;
        }
    }
}


void city:: deleteTileMap()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap.size(); b++)
        {
            delete tileMap[0][a][b];
        }
    }
}

void box::makeLine(road* myLine, std::vector<std::vector<std::vector<tile*> > > & tileMap, int level, std::string type)
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
        dc=woodwall;
        mc=-1;
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
        dc = dirt;
        mc=10;
        mat="dirt";
        width=1;
    }

    if(myLine->vertical==true)
    {
        signed int q1=(myLine->Point1->y-(width))/2;
        signed int q2=(myLine->Point1->y+(width))/2;


        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->y; c<=myLine->Point2->y; c++)
            {
                for(int d=q1; d<q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c) tileMap[1][c][d] = new door(false,closeddoor,0,mat);

                        else tileMap[1][c][d]=new tile(dc,-1,mat);

                        tileMap[1][c][d]->position = coordinate(d,c);
                    }
                    else
                    {
                        tileMap[0][c][d]=new tile(dc,mc,mat);
                        tileMap[0][c][d]->position = coordinate(d,c);
                    }
                }
            }
        }
    }

    else //horizontal
    {
        signed int q1=myLine->Point1->x-(width)/2;
        signed int q2=myLine->Point1->x+(width)/2;

        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->x; c<=myLine->Point2->x; c++)
            {

                for(int d=q1; d<q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c)tileMap[1][d][c] = new door(false,closeddoor,0,mat);

                        else tileMap[1][d][c]=new tile(dc,-1,mat);

                        tileMap[1][d][c]->position = coordinate(c,d);
                    }

                    else
                    {
                        tileMap[0][d][c]=new tile(dc,mc,mat);
                        tileMap[0][d][c]->position = coordinate(c,d);
                    }
                }
            }
        }
    }
}





void box::divideBox(int level, std::vector<std::vector<std::vector<tile*> > > & tileMap, std::string type)
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
    int half = halfChance(generator);


    if(half==0 and right-left>level) //if line vertical and there is space to draw line
    {
        std::cout << type << std::endl;
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

    else if (half==1 and top-bottom>level+1)
    {//line horizontal
        std::uniform_int_distribution<int> findSplitPoint(bottom+level/2,top-level/2);
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
divideBox(12,tileMap, "ROADBOX"); //recursive box dividing and road drawing
}



box::~box()
{

}


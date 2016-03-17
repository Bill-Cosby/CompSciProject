#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <random>

void box::makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap, std::default_random_engine generator)
{
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
            divideBox(3,tileMap,"HOUSE", generator);
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
            delete tileMap[1][a][b];
        }
    }
}

void box::makeLine(road* myLine, std::vector<std::vector<std::vector<tile*> > > & tileMap, int width, std::string type, std::default_random_engine generator)
{
    if(myLine->vertical==true and type=="ROADBOX")
    {
        std::cout << "Make a vertical road\n";
    }
    if(myLine->vertical==false and type=="ROADBOX")
    {
        std::cout << "Make a horizontal road\n";
    }


    int a=0;
    int b=0;

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

        std::uniform_int_distribution<int> doorFinder(a,b);
        doorPlace=doorFinder(generator);
    }

    if(type=="ROADBOX")
    {
        dc = dirt;
        mc=10;
        mat="dirt";
    }

    if(myLine->vertical==true)
    {
        signed int q1=myLine->Point1->x-(width)/2;
        signed int q2=myLine->Point1->x+(width)/2;


        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->y-1; c<=myLine->Point2->y+1; c++)
            {
                for(int d=q1; d<=q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c) tileMap[1][c][d] = new door(false,closeddoor,0,mat);

                        else tileMap[1][c][d]=new tile(dc,-1,mat);

                        tileMap[1][c][d]->position = coordinate(d,c);
                    }
                    else if (type=="ROADBOX")
                    {
                         if(d==q1 or d==q2)
                        {
                            tileMap[0][c][d]=new tile(grass,0,"grass");
                        }
                        else
                            {
                            tileMap[0][c][d]->position = coordinate(d,c);
                            }
                    }
                }
            }
        }
    }

    else //horizontal
    {
        signed int q1=myLine->Point1->y-(width)/2;
        signed int q2=myLine->Point1->y+(width)/2;

        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->x-1; c<=myLine->Point2->x+1; c++)
            {
                for(int d=q1; d<=q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c)tileMap[1][d][c] = new door(false,closeddoor,0,mat);

                        else tileMap[1][d][c]=new tile(dc,-1,mat);

                        tileMap[1][d][c]->position = coordinate(c,d);
                    }

                    else if (type=="ROADBOX")
                    {
                        if(d==q1 or d==q2)
                        {
                            tileMap[0][d][c]=new tile(grass,0,"grass");
                        }
                        tileMap[0][d][c]=new tile(dc,mc,mat);
                        tileMap[0][d][c]->position = coordinate(c,d);
                    }
                }
            }
        }
    }
}





void box::divideBox(int level, std::vector<std::vector<std::vector<tile*> > > & tileMap, std::string type, std::default_random_engine generator)
{

 if (level>0)
 {
std::uniform_int_distribution<int> halfChance(0,99);
    int half = halfChance(generator);
    int width;
    if(type=="ROADBOX")
    {
        width=level;
    }
    if(type=="HOUSE")
    {
        width=1;
    }
   // std::cout<<"Half:"<<half<<std::endl;


    if(half%2==0 and right-left>level) //if line vertical and there is space to draw line
    {
        std::cout << type << std::endl;
        std::uniform_int_distribution<int> findSplitPoint(left+width/2+1, right-level/2-1);
        int splitPoint=findSplitPoint(generator);

        coordinate lowPoint(splitPoint, bottom);
        coordinate highPoint(splitPoint, top);

        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;

        makeLine(&tempRoad, tileMap, width, type, generator); //draws road on tile map

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left+1;
        subBox1->right=splitPoint-1;
        subBox1->top=top;
        subBox1->bottom=bottom;

        subBox2->left=splitPoint+1;
        subBox2->right=right-1;
        subBox2->top=top;
        subBox2->bottom=bottom;

        subBox1->divideBox(level-1, tileMap, type, generator);
        subBox2->divideBox(level-1, tileMap, type, generator);

    }

    else if (half%2==1 and top-bottom>level+1)
    {//line horizontal
        std::uniform_int_distribution<int> findSplitPoint(bottom+width/2+1,top-width/2-1);
        int splitPoint=findSplitPoint(generator);
        std::cout<<left<<" "<<right<<" "<<splitPoint<<std::endl;
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;

        makeLine(&tempRoad, tileMap, width, type, generator); //draws road on tileMap

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=right;
        subBox1->top=top-width/2-1;
        subBox1->bottom=splitPoint+width/2+1;
        subBox2->left=left;
        subBox2->right=right;
        subBox2->top=splitPoint-width/2-1;
        subBox2->bottom=bottom+width/2+1;  //forms 2 new boxes
        subBox1->divideBox(level-1, tileMap, type, generator);
        subBox2->divideBox(level-1, tileMap, type, generator);
    }
 }

 else if(level==0 and type=="ROADBOX")
{
   makeHouse(tileMap, generator);  //many houses
}

 }

  void city::generateCity()
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
setTileMap();
divideBox(5,tileMap, "ROADBOX", generator); //recursive box dividing and road drawing
}



box::~box()
{

}


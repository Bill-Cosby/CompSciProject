#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <random>

city::city(int w, int h, int X0, int Y0)
{
    x0=X0;
    y0=Y0;
width=w; height=h; left=0; 0; right=width-1; top=height-1; seed=std::chrono::system_clock::now().time_since_epoch().count(); generator.seed(seed);
setTileMap();
divideBox(5,tileMap, "ROADBOX", generator); //recursive box dividing and road drawing
}

void city::setTileMap()
{
tileMap.resize(2);
tileMap[0].resize(height);
tileMap[1].resize(height);

  for(int a=bottom; a<=top; a++)
    {
        tileMap[0][a].resize(width);
        tileMap[1][a].resize(width);
        for(int b=left; b<=right; b++)
        {
            tileMap[0][a][b]=new tile(grass,10,"grass",a,b);
            tileMap[0][a][b]->position = coordinate(b,a);
            tileMap[0][a][b]->isDoor = false;
            tileMap[0][a][b]->isCity=true;
            tileMap[1][a][b]=new tile;
            tileMap[1][a][b]->position = coordinate(b,a);
            tileMap[1][a][b]->isDoor = false;
            tileMap[1][a][b]->isCity=true;
        }
    }
}

void box::makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap, std::mt19937 & generator)
{
    std::uniform_int_distribution<int> halfChance(0,1);
    std::uniform_int_distribution<int> doorFinder(bottom+left+1,top+right-1);
    int half=halfChance(generator);
    int doorPlace=doorFinder(generator);

    int wallTex;
    int innerwallTex;
    int floorTex;
    int mc;
    std::string wallmat;
    std::string innerwallmat;
    std::string floormat;

    int type = -1; //1 = blacksmith
                   //2 = house
                   //3 = store
                   //4 = armorer

    int width = abs(right-left), height = abs(bottom-top);

    if (width < 4 or height < 4)return;

    else if (width < 15 and height > 10 and height <15){
        wallTex = stonewall;
        floorTex = stonefloor;
        wallmat = "stone";
        floormat = "stone";
        innerwallTex = stonewall;
        innerwallmat = "stone";
        type = 1;
    }

   else if (height < 15 and width > 10 and width <15){
        wallTex = stonewall;
        floorTex = stonefloor;
        wallmat = "stone";
        floormat = "stone";
        innerwallTex = stonewall;
        innerwallmat = "stone";
        type = 4;
    }
    else if (width<15 and height < 15){
        wallTex = woodwall;
        floorTex = woodfloor;
        wallmat = "wood";
        floormat = "wood";
        innerwallTex = woodwall;
        innerwallmat = "wood";
        type = 2;
    }
    else if (width < 30 and height < 30){
        wallTex = stonewall;
        floorTex = woodfloor;
        wallmat = "stone";
        floormat = "wood";
        innerwallTex = woodwall;
        innerwallmat = "wood";
        type = 3;
    }

    else return;

    bool emptyPlot = false;

    for(int a=left; a<=right; a++)
    {
        for(int b=bottom; b<=top; b++)
        {
                tileMap[0][b][a]= new tile(floorTex,0,floormat,a,b);
                if (type == 1){
                    if (rand()%400 < 10){
                        tileMap[1][b][a]->occupied = new monster("human");
                        tileMap[1][b][a]->occupied->pos(b,a);

                    }
                    if (rand()%150 < 50){
                        tileMap[1][b][a]= new furniture(woodchair,0,"wood",a,b);
                        tileMap[1][b][a]->position=coordinate(a,b);
                    }
                    if (rand()%250 < 50){
                        tileMap[1][b][a]= new furniture(chair,0,"wood",a,b);
                        tileMap[1][b][a]->position=coordinate(a,b);
                    }
                }
                if (type == 2){
                    if (rand()%300 < 10){
                        tileMap[1][b][a]->occupied = new monster("human");
                        tileMap[1][b][a]->occupied->pos(b,a);

                    }
                }
                if (type == 3){
                    if (rand()%100 < 5){
                        tileMap[1][b][a] = new furniture(bigchair,-1,"redEye",a,b);
                        tileMap[1][b][a]->position=coordinate(a,b);
                    }
                    if (rand()%300 < 10){
                        tileMap[1][b][a]->occupied = new monster("human");
                        tileMap[1][b][a]->occupied->pos(b,a);

                    }
                }
                if (type == 4){
                    if (rand()%150 < 50){
                        tileMap[1][b][a]= new furniture(woodchair,0,"wood",a,b);
                        tileMap[1][b][a]->position=coordinate(a,b);
                    }
                    if (rand()%250 < 50){
                        tileMap[1][b][a]= new furniture(chair,0,"wood",a,b);
                        tileMap[1][b][a]->position=coordinate(a,b);
                    }
                    if (rand()%300 < 10){
                        tileMap[1][b][a]->occupied = new monster("human");
                        tileMap[1][b][a]->occupied->pos(b,a);

                    }
                }
            if (emptyPlot);
            else if(b==bottom or a==right)
            {
                if(b+a==doorPlace and half==0)
                {
                    tileMap[1][b][a]=new door(false,closeddoor,0,"wood",a,b);
                }
                else
                {
                    tileMap[1][b][a]=new tile(wallTex,-1,wallmat,a,b);
                }

            }

            else if(a==left or b==top)
            {
                if(b+a==doorPlace and half==1)
                {
                    tileMap[1][b][a]=new door(false,closeddoor,0,"wood",a,b);
                }
                else
                {
                    tileMap[1][b][a]=new tile(wallTex,-1,wallmat,a,b);
                }
            }
            tileMap[0][b][a]->position = coordinate(a,b);
            tileMap[1][b][a]->position = coordinate(a,b);
            tileMap[0][b][a]->isCity=true;
            tileMap[1][b][a]->isCity=true;

        }
    }
    top--;
    bottom++;
    left++;
    right--;
    if (!emptyPlot)divideBox(3,tileMap,"HOUSE", generator);


}



/*
city::~city()
{
    for(int a=0; a<tileMap[0].size(); a++)
    {
        for(int b=0; b<tileMap[0][a].size(); b++)
        {
            delete tileMap[0][a][b];
            delete tileMap[1][a][b];
        }
    }
}
*/

void box::makeLine(road* myLine, std::vector<std::vector<std::vector<tile*> > > & tileMap, int Lwidth, std::string type, std::mt19937 & generator)
{
    int a=0;
    int b=0;

    int dc;
    int mc;
    std::string mat;

    int doorPlace;

    if(type=="HOUSE")
    {
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
        signed int q1=myLine->Point1->x-(Lwidth)/2;
        signed int q2=myLine->Point1->x+(Lwidth)/2;


        if(0<=q1 and q2<tileMap[0][0].size())
        {
            for(int c=myLine->Point1->y; c<=myLine->Point2->y; c++)
            {

                    for(int d=q1; d<=q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c) tileMap[1][c][d] = new door(false,closeddoor,0,mat,a,b);

                        else tileMap[1][c][d]=new tile(dc,-1,mat,a,b);

                        tileMap[1][c][d]->position = coordinate(d,c);
                        tileMap[1][c][d]->isCity=true;
                    }
                    else if (type=="ROADBOX")
                    {

                            tileMap[0][c][d]=new tile(dc,mc,mat,d,c);
                            tileMap[0][c][d]->position = coordinate(d,c);
                            tileMap[0][c][d]->isCity=true;
                    }
                }


            }
        }
    }

    else //horizontal
    {
        signed int q1=myLine->Point1->y-(Lwidth)/2;
        signed int q2=myLine->Point1->y+(Lwidth)/2;

        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->x; c<=myLine->Point2->x; c++)
            {
                for(int d=q1; d<=q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c)tileMap[1][d][c] = new door(false,closeddoor,0,mat,c,d);

                        else tileMap[1][d][c]=new tile(dc,-1,mat,c,d);

                        tileMap[1][d][c]->position = coordinate(c,d);
                        tileMap[1][d][c]->isCity=true;
                    }

                    else if (type=="ROADBOX")
                    {

                        tileMap[0][d][c]=new tile(dc,mc,mat,c,d);

                        tileMap[0][d][c]->position = coordinate(c,d);
                        tileMap[0][d][c]->isCity=true;
                    }
                }
            }
        }
    }
}


void box::divideBox(int level, std::vector<std::vector<std::vector<tile*> > > & tileMap, std::string type, std::mt19937 & generator)
{
 if(level>0)
 {
std::uniform_int_distribution<int> halfChance(0,1);
    int half = halfChance(generator);
    int Lwidth;
    if(type=="ROADBOX")
    {

        Lwidth=level;
    }
    if(type=="HOUSE")
    {
        Lwidth=1;
    }

    if(half==0 and right-left>Lwidth+6) //if line vertical and there is space to draw line
    {//std::cout<<"Half0"<<std::endl;
        std::uniform_int_distribution<int> findSplitPoint(left+Lwidth/2+3, right-Lwidth/2-3);
        int splitPoint=findSplitPoint(generator);

        coordinate lowPoint(splitPoint, bottom);
        coordinate highPoint(splitPoint, top);

        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;

        makeLine(&tempRoad, tileMap, Lwidth, type, generator); //draws road on tile map

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint-Lwidth/2-1;
        subBox1->top=top;
        subBox1->bottom=bottom;

        subBox2->left=splitPoint+Lwidth/2+1;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

        subBox1->divideBox(level-1, tileMap, type, generator);
        subBox2->divideBox(level-1, tileMap, type, generator);
    }

    else if(half==0)
    {
        divideBox(level-1, tileMap, type, generator);
    }

    else if (half==1 and top-bottom>Lwidth+6)
    {//line horizontal
        //std::cout<<"Half2"<<std::endl;
        std::uniform_int_distribution<int> findSplitPoint(bottom+(Lwidth)/2+3,top-(Lwidth)/2-3);
        int splitPoint=findSplitPoint(generator);
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;


        makeLine(&tempRoad, tileMap, Lwidth, type, generator); //draws road on tileMap

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=right;
        subBox1->top=top-1;
        subBox1->bottom=splitPoint+Lwidth/2+1;
        subBox2->left=left;
        subBox2->right=right;
        subBox2->top=splitPoint-Lwidth/2-1;
        subBox2->bottom=bottom+1;  //forms 2 new boxes
        subBox1->divideBox(level-1, tileMap, type, generator);
        subBox2->divideBox(level-1, tileMap, type, generator);
    }
    else if(half==1)
    {
        divideBox(level-1, tileMap, type, generator);
    }
 }

 else if(level==0 and type=="ROADBOX")
{
   makeHouse(tileMap, generator);
     //many houses
}
 }




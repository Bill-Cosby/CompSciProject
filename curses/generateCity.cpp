#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <random>


void city::generateCity( std:: vector<actor*> & actors,std::vector<item*> & localItems, sf::RenderWindow & window, announcements & Announcements)
{
divideBox(3); //recursive box dividing and road drawing
drawGameworld(tileMap,actors,localItems, window, Announcements);
}


void city::setTileMap()
{
    std::vector<tile*> blank1;
    blank1.resize(50);
    tileMap.resize(50);
  for(int a=0; a<50; a++)
    {
        tileMap[a]=blank1;
        for(int b=0; b<50; b++)
        {
            tileMap[a][b]=new tile('/',10,grass);
        }
    }
}



void city::deleteTileMap50()
{
    for(int a=0; a<50; a++)
    {
        for(int b=0; b<50; b++)
        {
            delete tileMap[a][b];
        }
    }
}



void city::makeCity()
 {
      for(int a=0; a<roads.size(); a++)
      {
         makeRoad(roads[a]);
      }
}



void box::divideBox(int level)
{
  if(level!=0)
  {
std::default_random_engine generator;
std::uniform_int_distribution<int> halfChance(0,1);
    if(halfChance(generator)==0) //if line vertical
    {

        std:: uniform_real_distribution<double> findSplitPoint(left, right);
        double splitPoint=findSplitPoint(generator);
        coordinate lowPoint(bottom, splitPoint);
        coordinate highPoint(top, splitPoint);
        tempRoad=new road;
        tempRoad->vertical=true;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        drawRoad(tempRoad); //builds list of roads
        delete tempRoad;
        delete bottomPoint;
        delete topPoint;

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint;
        subBox1->top=top;
        subBox1->bottom;
        subBox2->left=splitPoint;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

    }

    else
    {
        height=top-bottom;
        uniform_real_distribution<double>(bottom+height/10, top-height/10) splitPoint;
        coordinate leftPoint(splitPoint, left);
        coordinate rightPoint(splitPoint, right);

        tempRoad=new road;
        tempRoad->vertical=false;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        drawRoad(tempRoad); //builds list of roads
        delete tempRoad;
        delete leftPoint
        delete rightPoint;


        box1=new box;
        box2=new box;

        box1->left=left;
        box1->right=right;
        box1->top=top;
        box1->splitPoint;
        box2->left=left;
        box2->right=right;
        box2->top=splitPoint;
        box2->bottom=bottom;  //forms
    }

    box1->myCity=myCity;
    box2->myCity=myCity
    level-=1;
    box1->divideBox(level);
    box2->divideBox(level);
    delete box1;
    delete box2;

  }

  void city::makeRoad(road* myRoad)
{
 if(myRoad->vertical==true)
 {
  for(int a=0; a<=myRoad->Point2->y-myRoad->Point1->y; a++)
  {
   tileMap[myRoad->Point1->y+a][myRoad->Point2->x]=new tile('/',10,stone);
  }
 }

  if(myRoad->vertical==false)
  {
  for(int a=0; a<myRoad->Point2->x-myRoad->Point1->x; a++)
   {
   tileMap[myRoad->Point2->y][myRoad->Point1->x+a]=new tile('/',10,stone);

   }
  }


}
}



